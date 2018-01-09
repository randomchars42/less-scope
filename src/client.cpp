#include <client.h>

#include <core/net/error.h>
#include <core/net/http/client.h>
#include <core/net/http/content_type.h>
#include <core/net/http/response.h>
#include <QVariantMap>

#include <iomanip>
#include <iostream>
#include <fstream>


namespace http = core::net::http;
namespace net = core::net;

using namespace std;

Client::Client(cfg::Config::Ptr config) :
    config_(config), cancelled_(false) {

}

Client::ItemList Client::parseresult(QJsonDocument &root) {
    ItemList result;

    // Read out the items
    QVariantMap variant = root.toVariant().toMap();
    QVariantList items = variant["items"].toList();
    if (items.empty()) {
        return result;
    }

    for (const QVariant &i : items) {
        QVariantMap retrieved_item = i.toMap();

        result.emplace_back(Item {
                                retrieved_item["id"].toUInt(),
                                retrieved_item["title"].toString().toStdString(),
                                retrieved_item["subtitle"].toString().toStdString(),
                                retrieved_item["text"].toString().toStdString(),
                                retrieved_item["image"].toString().toStdString()
                            });
    }

    return result;
}

void Client::getlocal(string query_string, ItemList &result) {

    // read the "database" json-file
    ifstream file(config_->scope_path + "/data.json");
    string line;
    string file_contents;

    while (std::getline(file, line)) {
			cerr << line << endl;
      file_contents += line;
      file_contents.push_back('\n');
    }

    // Parse the JSON
    QJsonDocument root = QJsonDocument::fromJson(file_contents.c_str());

    QVariant cod = root.toVariant().toMap()["cod"];
    if ((cod.canConvert<QString>() && cod.toString() != "200")
            || (cod.canConvert<unsigned int>() && cod.toUInt() != 200)) {
        throw domain_error(root.toVariant().toMap()["message"].toString().toStdString());
    }

    result = parseresult(root);

    // filter result and change image paths
    // "all" will display all themes
    // filter by title, case-insensitive
    // so we convert title and query to lower-case
    // and cut the title to the length of the query


    // query to lower-case
    transform(query_string.begin(), query_string.end(), query_string.begin(), ::tolower);
    // will hold the title
    string title;

    //* loop through all items
    ItemList::iterator item = result.begin();

    while (item != result.end()) {
        //get the title
        title = item->title;
        if (! query_string.empty()) {
            // cut it
            title = title.substr(0, query_string.length());
            // and transform it to lower-case
            transform(title.begin(), title.end(), title.begin(), ::tolower);
        }

        cerr << title << endl;

        if (! query_string.empty() &&
						query_string != title &&
						query_string != "all") {
            item = result.erase(item);
        } else {
            // expand the image path
            item->image = config_->scope_path + "/" + item->image;
            ++item;
        }
    }
}

void Client::get(const net::Uri::Path &path,
                 const net::Uri::QueryParameters &parameters, ItemList &result) {
    // Create a new HTTP client
    auto client = http::make_client();

    // Start building the request configuration
    http::Request::Configuration configuration;

    // Build the URI from its components
    //net::Uri uri = net::make_uri(config_->apiroot, path, parameters);
    net::Uri uri = net::make_uri(config_->apiroot, path, parameters);
    configuration.uri = client->uri_to_string(uri);

    // Give out a user agent string
    configuration.header.add("User-Agent", config_->user_agent);

    // Build a HTTP request object from our configuration
    auto request = client->head(configuration);

    try {
        // Synchronously make the HTTP request
        // We bind the cancellable callback to #progress_report
        auto response = request->execute(
                    bind(&Client::progress_report, this, placeholders::_1));

        // Check that we got a sensible HTTP status code
        if (response.status != http::Status::ok) {
            throw domain_error(response.body);
        }
        // Parse the JSON from the response
        QJsonDocument root = QJsonDocument::fromJson(response.body.c_str());

        // Open weather map API error code can either be a string or int
        QVariant cod = root.toVariant().toMap()["cod"];
        if ((cod.canConvert<QString>() && cod.toString() != "200")
                || (cod.canConvert<unsigned int>() && cod.toUInt() != 200)) {
            throw domain_error(root.toVariant().toMap()["message"].toString().toStdString());
        }

        result = parseresult(root);
    } catch (net::Error &) {
    }
}

Client::ItemList Client::items(const string& query) {
    ItemList result;

    // Build a URI and get the contents.
    // The fist parameter forms the path part of the URI.
    // The second parameter forms the CGI parameters.
    //get( { query + ".json" }, { }, root);
    getlocal(query, result);
    // get( { query + ".json" }, { { "q", query } }, result);
    // e.g. http://bluesky.pixelwoelkchen.de/QUERY.json?q=QUERY

    return result;
}

http::Request::Progress::Next Client::progress_report(
        const http::Request::Progress&) {

    return cancelled_ ?
                http::Request::Progress::Next::abort_operation :
                http::Request::Progress::Next::continue_operation;
}

void Client::cancel() {
    cancelled_ = true;
}
