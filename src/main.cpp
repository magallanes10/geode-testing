#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

// Global session tracker remains outside the modify class
bool G_ANNOUNCEMENT_SHOWN = false;

class $modify(MyMenuLayer, MenuLayer) {
    // Geode Rule: All variables in a modify class MUST be inside this struct
    struct Fields {
        EventListener<web::WebTask> m_listener;
    };

    bool init() {
        // Correct way to call parent init in modern Geode
        if (!MenuLayer::init()) return false;

        if (!G_ANNOUNCEMENT_SHOWN) {
            this->fetchAnnouncement();
        }

        return true;
    }

    void fetchAnnouncement() {
        auto req = web::WebRequest();
        
        // Access fields using m_fields->
        m_fields->m_listener.bind([this](web::WebResponse* res) {
            if (res && res->ok()) {
                auto jsonResult = res->json();
                
                if (jsonResult && jsonResult.unwrap().contains("announcement")) {
                    auto ann = jsonResult.unwrap()["announcement"];
                    
                    // Fixed: asString() instead of as_string() 
                    // and unwrap() to get the string value safely
                    std::string title = ann["title"].asString();
                    std::string context = ann["context"].asString();

                    FLAlertLayer::create(
                        title.c_str(), 
                        context.c_str(), 
                        "OK"
                    )->show();

                    G_ANNOUNCEMENT_SHOWN = true;
                }
            } else {
                log::error("Failed to fetch GDPS announcement");
            }
        });

        m_fields->m_listener.setFilter(req.get("https://pastebin.com/raw/vRNYgwyL"));
    }
};
