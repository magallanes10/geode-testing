#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Simple message
        std::string message = "Hello there bruhh\nFrom: Harold Hutchin\n[RGDPS Announcement]";

        // Show classic FLAlertLayer with OK button
        FLAlertLayer::create(
            "RGDPS Announcement", // title
            message.c_str(),      // content
            "OK"                  // button text
        )->show();

        return true;
    }
};
