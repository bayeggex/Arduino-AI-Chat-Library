#include "AIChatbot.h"

AIChatbot::AIChatbot()
    : chatGPTApiKey(""), huggingFaceApiKey(""), selectedAI(""), selectedAIVersion("gpt-3.5-turbo") {}

void AIChatbot::begin(long baudRate) {
    Serial.begin(baudRate);
}

void AIChatbot::connectWiFi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void AIChatbot::update() {
    if (Serial.available() > 0) {
        String incomingMessage = Serial.readString();
        Serial.println("Received: " + incomingMessage);
        
        String response = getResponse(incomingMessage);
        Serial.println("Response: " + response);
    }
}

void AIChatbot::setKey(const String& key, const String& aiName) {
    if (aiName == "chatgpt") {
        chatGPTApiKey = key;
    } else if (aiName == "huggingface") {
        huggingFaceApiKey = key;
    }
}

void AIChatbot::selectAI(const String& aiName, const String& aiVersion) {
    selectedAI = aiName;
    if (aiVersion != "null" && aiVersion != "none") {
        selectedAIVersion = aiVersion;
    } else {
        selectedAIVersion = "gpt-3.5-turbo";
    }
}

String AIChatbot::getResponse(const String& message) {
    if (selectedAI == "chatgpt") {
        return sendToChatGPT(message);
    } else if (selectedAI == "huggingface") {
        return sendToHuggingFace(message);
    } else {
        return "AI type not selected.";
    }
}

String AIChatbot::sendToChatGPT(const String& message) {
    if (chatGPTApiKey.isEmpty()) {
        return "ChatGPT API key not set.";
    }

    String url = "https://api.openai.com/v1/chat/completions";
    String payload = "{\"model\": \"" + selectedAIVersion + "\", \"messages\": [{\"role\": \"user\", \"content\": \"" + message + "\"}]}";

    return makeHttpRequest(url, payload, chatGPTApiKey);
}

String AIChatbot::sendToHuggingFace(const String& message) {
    if (huggingFaceApiKey.isEmpty()) {
        return "Hugging Face API key not set.";
    }

    String url = "https://api-inference.huggingface.co/models/" + selectedAIVersion;
    String payload = "{\"inputs\": \"" + message + "\"}";

    return makeHttpRequest(url, payload, huggingFaceApiKey);
}

String AIChatbot::makeHttpRequest(const String& url, const String& payload, const String& apiKey) {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + apiKey);

    int httpResponseCode = http.POST(payload);
    String response;

    if (httpResponseCode > 0) {
        response = http.getString();
    } else {
        response = "Error on sending POST: " + String(httpResponseCode);
    }

    http.end();
    return response;
}
