#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

// We use a global variable to track if the announcement has already been shown
// this session so it doesn't pop up every time you return to the menu.
bool G_ANNOUNCEMENT_SHOWN = false;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Only fetch and show if it hasn't been shown yet this session
        if (!G_ANNOUNCEMENT_SHOWN) {
            this->fetchAnnouncement();
        }

        return true;
    }

    void fetchAnnouncement() {
        // Fetching from your Pastebin link
        web::WebRequest()
            .get("https://pastebin.com/raw/vRNYgwyL")
            .listen([this](web::WebResponse* res) {
                if (res && res->ok()) {
                    auto data = res->json();
                    
                    if (data && data.value().contains("announcement")) {
                        auto ann = data.value()["announcement"];
                        
                        std::string title = ann["title"].as_string();
                        std::string context = ann["context"].as_string();

                        // Show the popup on the main thread
                        FLAlertLayer::create(
                            title.c_str(), 
                            context.c_str(), 
                            "OK"
                        )->show();

                        // Mark as shown so it doesn't spam the user
                        G_ANNOUNCEMENT_SHOWN = true;
                    }
                } else {
                    log::error("Failed to fetch GDPS announcement");
                }
            });
    }
};
