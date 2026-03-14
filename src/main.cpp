#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Fetch JSON automatically and show popup
        Network::getJSON("https://pastebin.com/raw/JiRtFNBG")
            .then([](auto jsonData) {
                // Extract fields from JSON
                std::string message = jsonData["message"].as_string();
                std::string from = jsonData["from"].as_string();

                std::string fullMessage = message + "\n\nFrom: " + from + "\n[RGDPS Announcement]";

                FLAlertLayer::create("Geode", fullMessage.c_str(), "OK")->show();
            })
            .catch_error([](std::string err){
                log::warn("Failed to fetch JSON: {}", err);
            });

        return true;
    }
};
