#ifndef CLIENT_H_
#define CLIENT_H_


#include <config.h>

#include <atomic>
#include <deque>
#include <map>
#include <memory>
#include <string>
#include <core/net/http/request.h>
#include <core/net/uri.h>

#include <QJsonDocument>

/**
 * Provide a nice way to access the HTTP API.
 *
 * We don't want our scope's code to be mixed together with HTTP and JSON handling.
 */
class Client {
public:

    /**
     * The basic unit that is fetched or generated.
     */
    struct Item {
        unsigned int id;
        std::string title;
        std::string subtitle;
        std::string text;
        std::string image;
    };

    /**
     * A list of items.
     */
    typedef std::deque<Item> ItemList;

    Client(cfg::Config::Ptr config);

    virtual ~Client() = default;

    /**
     * Get items.
     */
    virtual ItemList items(const std::string &query);

    /**
     * Cancel any pending queries (this method can be called from a different thread)
     */
    virtual void cancel();

protected:
    /**
     * local request.
     */
    void getlocal(std::string query_string, ItemList &result);

    /**
     * HTTP request.
     */
    void get(const core::net::Uri::Path &path,
                     const core::net::Uri::QueryParameters &parameters, ItemList &result);


    ItemList parseresult(QJsonDocument &root);
		std::string filetostring(std::string filename);

    /**
     * Progress callback that allows the query to cancel pending HTTP requests.
     */
    core::net::http::Request::Progress::Next progress_report(
            const core::net::http::Request::Progress& progress);

    /**
     * Hang onto the configuration information
     */
    cfg::Config::Ptr config_;

    /**
     * Thread-safe cancelled flag
     */
    std::atomic<bool> cancelled_;
};

#endif // CLIENT_H_
