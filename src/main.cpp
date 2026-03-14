#include <Geode/Geode.hpp>
#include <Geode/modify/MainMenuLayer.hpp>
using namespace geode::prelude;

class $modify(MyMainMenu, MainMenuLayer) {
    bool init() {
        if (!MainMenuLayer::init()) return false;

        static bool shown = false;
        if (!shown) {
            shown = true;

            std::string message = "hello there bruhh";
            std::string from = "Harold Hutchin";
            std::string fullMessage = message + "\n\nFrom: " + from + "\n[RGDPS Announcement]";

            // Show the popup — stays until "OK" is tapped
            FLAlertLayer::create("RGDPS Announcement", fullMessage.c_str(), "OK")->show();
        }

        return true;
    }
};
