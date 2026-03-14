#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        fetchAndShowPopup();
        return true;
    }

    void fetchAndShowPopup() {
        cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
        request->setUrl("https://pastebin.com/raw/JiRtFNBG");
        request->setRequestType(cocos2d::network::HttpRequest::Type::GET);

        request->setResponseCallback([this](cocos2d::network::HttpClient*, cocos2d::network::HttpResponse* response) {
            if (!response || !response->isSucceed()) {
                log::warn("Failed to fetch remote popup message!");
                return;
            }

            std::string data(response->getResponseData()->begin(), response->getResponseData()->end());

            try {
                auto jsonData = geode::json::parse(data);
                std::string message = jsonData.at("message").as_string();
                std::string from = jsonData.at("from").as_string();

                std::string fullMessage = message + "\n\nFrom: " + from + "\n[RGDPS Announcement]";
                FLAlertLayer::create("Geode", fullMessage.c_str(), "OK")->show();

            } catch (const std::exception& e) {
                log::warn("Failed to parse JSON: {}", e.what());
            }
        });

        cocos2d::network::HttpClient::getInstance()->send(request);
        request->release();
    }
};
