#include <query.h>
#include <templates.h>
#include <localization.h>

#include <unity/scopes/Annotation.h>
#include <unity/scopes/CategorisedResult.h>
#include <unity/scopes/CategoryRenderer.h>
#include <unity/scopes/QueryBase.h>
#include <unity/scopes/SearchReply.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>
#include <locale>

namespace sc = unity::scopes;

using namespace std;

/**
 * Needs to be in the same order as in less-settings.ini!
 */
const string Query::templates[6] = {TEMPLATE_IMAGE_TEXT_OVERLAY, TEMPLATE_SMALL_IMAGE_TITLE,
                                    TEMPLATE_SMALL_IMAGE_TEXT, TEMPLATE_IMAGE_ONLY,
                                    TEMPLATE_TEXT_ONLY, TEMPLATE_TEST};

Query::Query(const sc::CannedQuery &query, const sc::SearchMetadata &metadata,
             cfg::Config::Ptr config) :
    sc::SearchQueryBase(query, metadata), config_(config), client_(config) {
    //config_ = config;
}

void Query::loadConfig()
{
    unity::scopes::VariantMap config = settings();
    if (config.empty())
        cerr << "CONFIG EMPTY!" << endl;
    config_->theme = config["theme"].get_string();
    config_->custom_title = config["title"].get_string();
    config_->custom_subtitle = config["subtitle"].get_string();
    config_->custom_text = config["text"].get_string();
    config_->custom_image = config["image"].get_string();
    config_->layout = config["layout"].get_int();
}

void Query::cancelled() {
    client_.cancel();
}


void Query::run(sc::SearchReplyProxy const& reply) {
    try {

        // Start by getting information about the query
        const sc::CannedQuery &query(sc::SearchQueryBase::query());

        // Get the query string
        string query_string = query.query_string();

        loadConfig();

        // make the layout configurable
        string template_string;
        // home-screen mode?
        if (query_string.empty()) {
            template_string = templates[config_->layout];
        } else if (query_string == "info") {
            // info mode
            template_string = templates[2];
        } else {
            // search mode
            template_string = templates[1];
        }
        string placeholder = "%default_image";
        string default_image = "file://" + config_->scope_path + "/yoda.svg";

        /* if the user has not configured a custom image (the string equals the default value)
        if (config_->custom_image == "/home/phablet/Pictures/" || config_->custom_image == "") {
            default_image = "file://" + config_->scope_path + "/zen.jpg";
        } else {
            default_image = "file://" + config_->custom_image;
        }*/

        size_t start_pos = template_string.find(placeholder);

        if(start_pos != std::string::npos) {
            template_string.replace(start_pos, placeholder.length(), default_image);
        }

        Client::ItemList items;

        // home-screen mode?
        if (query_string.empty()) {
            query_string = config_->theme;
        }

        // Get thte current date
        string date_string;
        time_t t = std::time(nullptr);
        char mbstr[12];
        if (!strftime(mbstr, sizeof(mbstr), "%Y-%m-%d", localtime(&t))) {
             cerr << "Could not get current date!" << endl;
        }
        date_string.assign(mbstr);

        items = client_.items(query_string);

        // home-screen mode
        if (query_string == config_->theme && items.size() > 0) {
            // there should be only one item -> items.at(0)
            string title, text, subtitle;

            if (!config_->custom_title.empty()) {
                items.at(0).title = config_->custom_title;
            }

            if (!config_->custom_subtitle.empty()) {
                items.at(0).subtitle = config_->custom_subtitle;
            }

            // if the subtitle is empty replace it with the current date
            if (items.at(0).subtitle.empty()) {
                items.at(0).subtitle = date_string;
            }

            if (!config_->custom_text.empty()) {
                items.at(0).text = config_->custom_text;
            }

            // if the user has not configured a custom image (the string equals the default value)
            if (!config_->custom_image.empty() && config_->custom_image != "/home/phablet/Pictures/") {
                items.at(0).image = config_->custom_image;
            }

        }

        // Register a category for the current weather, with the title we just built
        auto location_cat = reply->register_category("current", "", "", sc::CategoryRenderer(template_string));

        for (const Client::Item &item : items) {
            // Create a single result for the current weather category
            sc::CategorisedResult res(location_cat);

            // We must have a URI
            res.set_uri(to_string(item.id));

            // Build up the description for the current weather
            stringstream ss(stringstream::in | stringstream::out);
            ss << item.title;
            res.set_title(ss.str());

            // Set the rest of the attributes, art, description, etc
            res.set_art(item.image);
            res["subtitle"] = item.subtitle;
            res["summary"] = item.text;

            // Push the result
            if (!reply->push(res)) {
                // If we fail to push, it means the query has been cancelled.
                // So don't continue;
                return;
            }
        }

    } catch (domain_error &e) {
        // Handle exceptions being thrown by the client API
        cerr << e.what() << endl;
        reply->error(current_exception());
    }
}
