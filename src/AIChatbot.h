#ifndef AI_CHATBOT_H
#define AI_CHATBOT_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

class AIChatbot {
public:
    AIChatbot();
    void begin(long baudRate);
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

#endif