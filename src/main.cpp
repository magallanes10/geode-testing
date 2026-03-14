#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/ui/Popup.hpp>

using namespace geode::prelude;

// Your custom popup class
class MyPopup : public geode::Popup {
protected:
    bool init(const std::string& value) {
        if (!Popup::init(240.f, 160.f))
            return false;

        this->setTitle("RGDPS Announcement");

        auto label = CCLabelBMFont::create(value.c_str(), "bigFont.fnt");
        m_mainLayer->addChildAtPosition(label, Anchor::Center);

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

// Modify the MenuLayer to show popup on start
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Hardcoded message
        std::string message = "hello there bruhh";
        std::string from = "Harold Hutchin";
        std::string fullMessage = message + "\n\nFrom: " + from + "\n[RGDPS Announcement]";

        // Show your custom popup
        auto popup = MyPopup::create(fullMessage);
        if (popup)
            popup->show();

        return true;
    }
};
