#ifndef TEMPLATES_H
#define TEMPLATES_H

/**
 * Define layouts.
 */

const static std::string TEMPLATE_IMAGE_TEXT_OVERLAY =
        R"(
        {
            "schema-version": 1,
            "template": {
                "category-layout": "grid",
                "card-layout": "vertical",
                "collapsed-rows": 0,
                "card-size": "large",
                "overlay": true
            },
            "components": {
                "art" : {
                    "field" : "art",
                    "fillmode" : "fit",
                    "aspect-ratio" : 0.65,
                    "fallback": "%default_image",
                    "overlay-color": "color://.md#CCCCCC"
                },
                "title": "title",
                "subtitle": "subtitle"
            }
        }
        )";

const static std::string TEMPLATE_SMALL_IMAGE_TITLE =
        R"(
        {
            "schema-version": 1,
            "template": {
                "category-layout": "grid",
                "card-layout": "vertical",
                "collapsed-rows": 0,
                "card-size": "large"
            },
            "components": {
                "art" : {
                    "field" : "art",
                    "fillmode" : "fit",
                    "aspect-ratio" : 2,
                    "fallback": "%default_image"
                },
                "title": "title",
                "subtitle": "subtitle"
            }
        }
        )";

const static std::string TEMPLATE_SMALL_IMAGE_TEXT =
        R"(
        {
            "schema-version": 1,
            "template": {
                "category-layout": "grid",
                "card-layout": "vertical",
                "collapsed-rows": 0,
                "card-size": "large",
                "card-background":"color://.md#E9E0D6"
            },
            "components": {
                "art" : {
                    "field" : "art",
                    "fillmode" : "fit",
                    "aspect-ratio" : 2,
                    "fallback": "%default_image"
                },
                "title": "title",
                "subtitle": "subtitle",
                "summary": "summary"
            }
        }
        )";

const static std::string TEMPLATE_IMAGE_ONLY =
        R"(
        {
            "schema-version": 1,
            "template": {
                "category-layout": "grid",
                "card-layout": "vertical",
                "collapsed-rows": 0,
                "card-size": "large"
            },
            "components": {
                "art" : {
                    "field" : "art",
                    "fillmode" : "fit",
                    "aspect-ratio" : 0.65,
                    "fallback": "%default_image"
                }
            }
        }
        )";

const static std::string TEMPLATE_TEXT_ONLY =
        R"(
        {
            "schema-version": 1,
            "template": {
                "category-layout": "grid",
                "card-layout": "vertical",
                "collapsed-rows": 0,
                "card-size": "large"
            },
            "components": {
                "title": "title"
            }
        }
        )";

const static std::string TEMPLATE_TEST =
        R"(
        {
            "schema-version": 1,
            "template": {
                "category-layout": "grid",
                "card-layout": "vertical",
                "collapsed-rows": 0,
                "card-size": "large",
                "overlay": true
            },
            "components": {
                "art" : {
                    "field" : "art",
                    "fillmode" : "fit",
                    "aspect-ratio" : 0.65,
                    "fallback": "%default_image",
                    "overlay-color": "color://.md#CCCCCC"
                },
                "title": "title",
                "subtitle": "subtitle",
                "summary": "summary"
            }
        }
        )";

#endif // TEMPLATES_H
