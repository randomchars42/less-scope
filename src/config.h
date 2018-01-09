#ifndef CONFIG_H_
#define CONFIG_H_

#include <memory>
#include <string>

namespace cfg {

struct Config {
    typedef std::shared_ptr<Config> Ptr;
    // The root of all API request URLs
    std::string apiroot { "http://bluesky.pixelwoelkchen.de" };
    // The custom HTTP user agent string for this library
    std::string user_agent { "less-scope; (ubuntutouch)" };
    // The path of the scope
    std::string scope_path;
    int layout;
    std::string theme;
    std::string custom_title;
    std::string custom_subtitle;
    std::string custom_text;
    std::string custom_image;
};

}

#endif /* CONFIG_H_ */
