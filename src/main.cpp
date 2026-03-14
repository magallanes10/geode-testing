#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/Button.hpp>

using namespace geode::prelude;

// Custom popup with OK button
class MyPopup : public geode::Popup {
protected:
    bool init(const std::string& value) {
        if (!Popup::init(240.f, 160.f))
            return false;

        this->setTitle("RGDPS Announcement");

        // Message text
        auto label = CCLabelBMFont::create(value.c_str(), "goldFont.fnt");
        label->setPosition({120.f, 100.f}); // slightly higher for button space
        m_mainLayer->addChild(label);

        // Add OK button
        auto okButton = SimpleButton::create("OK", [this]() {
            this->close(); // closes the popup when tapped
        });
        okButton->setPosition({120.f, 40.f}); // center bottom
        m_mainLayer->addChild(okButton);

        return true;
    }

public:
    static MyPopup* create(const std::string& text) {
        auto ret = new MyPopup();
        if (ret && ret->init(text)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

// Modify MenuLayer to show popup immediately
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        std::string message = "Hello there bruhh\nFrom: Harold Hutchin\n[RGDPS Announcement]";

        auto popup = MyPopup::create(message);
        if (popup)
            popup->show(); // shows popup; player must tap OK

        return true;
    }
};
