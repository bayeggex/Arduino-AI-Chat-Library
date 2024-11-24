#ifndef AI_CHATBOT_H
#define AI_CHATBOT_H

#include <Arduino.h>

#if defined(ESP32)
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#define PLATFORM_NAME "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define PLATFORM_NAME "ESP8266"
#endif


class AIChatbot {
public:
    AIChatbot();
    bool connectWiFi(const char* ssid, const char* password, unsigned long timeoutMs = 10000);
    bool validateKeys();
    void begin(long baudRate);
    void update();
    void setKey(const String& key, const String& aiName);
    void selectAI(const String& aiName, const String& aiVersion = "gpt-3.5-turbo");
    String sanitizeInput(const String& input);
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