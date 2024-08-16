#ifndef AI_CHATBOT_H
#define AI_CHATBOT_H

#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif

class AIChatbot {
public:
    AIChatbot();
    void begin(long baudRate);
    bool connectWiFi(const char* ssid, const char* password, unsigned long timeoutMs = 10000);
    void update();
    void setKey(const String& key, const String& aiName);
    void selectAI(const String& aiName, const String& aiVersion = "gpt-3.5-turbo");
    String getResponse(const String& message);

private:
    String chatGPTApiKey;
    String huggingFaceApiKey;
    String selectedAI;
    String selectedAIVersion;
    String sendToChatGPT(const String& message);
    String sendToHuggingFace(const String& message);
    String makeHttpRequest(const String& url, const String& payload, const String& apiKey);
};

#endif // AI_CHATBOT_H