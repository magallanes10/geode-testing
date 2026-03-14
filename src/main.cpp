#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Ensure popup only shows once per session
        static bool shown = false;
        if (!shown) {
            shown = true;

            std::string message = "hello there bruhh";
            std::string from = "Harold Hutchin";
            std::string fullMessage = message + "\n\nFrom: " + from + "\n[RGDPS Announcement]";

            // Create the FLAlertLayer
            auto alert = FLAlertLayer::create(
                "RGDPS Announcement",  // Title
                fullMessage.c_str(),      // Message
                "OK"                      // Button text
            );

            // Show it — it will stay until the player taps OK
            alert->show();
        }

        return true;
    }
};
