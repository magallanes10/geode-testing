#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        // Find the bottom menu
        auto menuNode = this->getChildByID("bottom-menu");
        if (!menuNode)
            return true;

        // Create button with GD info icon
        auto myButton = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_info_001.png"), // info icon
            this,
            menu_selector(MyMenuLayer::onMyButton)
        );

        // Unique ID for layout
        myButton->setID("my-popup-button"_spr);

        // Add button to bottom menu
        menuNode->addChild(myButton);
        menuNode->updateLayout(); // ensures proper placement

        return true;
    }

    // Button callback
    void onMyButton(CCObject*) {
        FLAlertLayer::create(
            "RGDPS Announcement",                   // title
            "Hello there bruhh!\nThis is your message.", // content
            "OK"                                     // button text
        )->show();
    }
};
