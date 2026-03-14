#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        std::string message = "hello there bruhh";
        std::string from = "Harold Hutchin";
        std::string fullMessage = message + "\n\nFrom: " + from + "\n[RGDPS Announcement]";

        // Use runAction to delay the pop-up
        this->runAction(CCSequence::create(
            CCDelayTime::create(0.1f),   // small delay to ensure MenuLayer is ready
            CCCallFunc::create([fullMessage, this]() {
                auto alert = FLAlertLayer::create(
                    "Geode",        // Title
                    fullMessage.c_str(), // Message
                    "OK"            // Button
                );
                alert->show(); // modal, blocks until OK is pressed
            }),
            nullptr
        ));

        return true;
    }
};
