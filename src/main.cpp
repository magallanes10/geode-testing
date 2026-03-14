#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        std::string message = "hello there bruhh";
        std::string from = "Harold Hutchin";
        std::string fullMessage = message + "\n\nFrom: " + from + "\n[RGDPS Announcement]";

        // Ensure the alert is modal and requires OK
        this->scheduleOnce([this, fullMessage](float){
            auto alert = FLAlertLayer::create(
                "Geode",       // Title
                fullMessage.c_str(), // Message
                "OK"           // Button text
            );

            // Make sure it’s modal and blocks all touches until dismissed
            alert->setKeypadEnabled(true); // Optional: allow back button if on mobile
            alert->setTouchEnabled(true);
            alert->show(); // Show it on the current MenuLayer
        }, 0.1f, "show_alert");

        return true;
    }
};
