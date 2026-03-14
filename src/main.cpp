#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Hardcoded message (replace with remote JSON if native networking is available)
        std::string message = "hello there bruhh";
        std::string from = "Harold Hutchin";

        std::string fullMessage = message + "\n\nFrom: " + from + "\n[RGDPS Announcement]";

        FLAlertLayer::create("Geode", fullMessage.c_str(), "OK")->show();

        return true;
    }
};
