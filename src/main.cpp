#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

bool G_ANNOUNCEMENT_SHOWN = false;

class $modify(MyMenuLayer, MenuLayer) {
    struct Fields {
        // Explicitly defining the task type to avoid "no member named WebTask"
        EventListener<Task<web::WebResponse*>> m_listener;
    };

    bool init() {
        if (!MenuLayer::init()) return false;

        if (!G_ANNOUNCEMENT_SHOWN) {
            this->fetchAnnouncement();
        }

        return true;
    }

    void fetchAnnouncement() {
        auto req = web::WebRequest();
        
        m_fields->m_listener.bind([this](web::WebResponse* res) {
            if (res && res->ok()) {
                auto jsonResult = res->json();
                
                // 1. Check if JSON parsed successfully
                if (jsonResult && jsonResult.unwrap().contains("announcement")) {
                    auto ann = jsonResult.unwrap()["announcement"];
                    
                    // 2. Use unwrapOr to safely convert to std::string
                    // This fixes the "no viable conversion from Result to string" error
                    std::string title = ann["title"].asString().unwrapOr("Notice");
                    std::string context = ann["context"].asString().unwrapOr("No content found.");

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

        // 3. Start the GET request
        m_fields->m_listener.setFilter(req.get("https://pastebin.com/raw/vRNYgwyL"));
    }
};
