#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <cocos2d.h>
#include <network/HttpClient.h>
#include <json.hpp> // for JSON parsing
using json = nlohmann::json;

using namespace geode::prelude;
using namespace cocos2d::network;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Create the popup automatically
        fetchAndShowPopup();

        return true;
    }

    void fetchAndShowPopup() {
        auto request = new HttpRequest();
        request->setUrl("https://pastebin.com/raw/JiRtFNBG");
        request->setRequestType(HttpRequest::Type::GET);

        request->setResponseCallback([this](HttpClient* client, HttpResponse* response) {
            if (!response || !response->isSucceed()) {
                log::warn("Failed to fetch remote popup message!");
                return;
            }

            std::vector<char> *buffer = response->getResponseData();
            std::string data(buffer->begin(), buffer->end());

            try {
                auto jsonData = json::parse(data);
                std::string message = jsonData["message"];
                std::string from = jsonData["from"];

                // Add RGDPS announcement
                std::string fullMessage = message + "\n\nFrom: " + from + "\n[RGDPS Announcement]";

                // Show the popup
                FLAlertLayer::create("Geode", fullMessage.c_str(), "OK")->show();

            } catch (std::exception& e) {
                log::warn("Failed to parse JSON: {}", e.what());
            }
        });

        HttpClient::getInstance()->send(request);
        request->release();
    }
};
