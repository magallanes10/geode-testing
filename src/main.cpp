#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Global flag for session
static bool g_popupShown = false;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Only show popup once per session
        if (!g_popupShown) {
            g_popupShown = true;

            std::string message = "Hello there bruhh\nFrom: Harold Hutchin\n[RGDPS Announcement]";

            FLAlertLayer::create(
                "RGDPS Announcement", // title
                message.c_str(),      // content
                "OK"                  // button text
            )->show();
        }

        return true;
    }
};
