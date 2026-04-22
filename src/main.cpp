#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

bool G_ANNOUNCEMENT_SHOWN = false;

class $modify(MyMenuLayer, MenuLayer) {
    // We use a TaskListener to handle the web request safely
    EventListener<web::WebTask> m_listener;

    bool init() {
        if (!MenuLayer::init()) return false;

        if (!G_ANNOUNCEMENT_SHOWN) {
            this->fetchAnnouncement();
        }

        return true;
    }

    void fetchAnnouncement() {
        // Create the request
        auto req = web::WebRequest();
        
        // Use a listener to handle the response
        m_listener.bind([this](web::WebResponse* res) {
            if (res && res->ok()) {
                // In v3, res->json() returns a geode::Result. 
                // We check if it's successful and then unwrap it.
                auto jsonResult = res->json();
                
                if (jsonResult && jsonResult.unwrap().contains("announcement")) {
                    auto ann = jsonResult.unwrap()["announcement"];
                    
                    std::string title = ann["title"].as_string();
                    std::string context = ann["context"].as_string();

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

        // Start the request and link it to the listener
        m_listener.setFilter(req.get("https://pastebin.com/raw/vRNYgwyL"));
    }
};
