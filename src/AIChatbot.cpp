#include "AIChatbot.h"

AIChatbot::AIChatbot()
    : chatGPTApiKey(""), huggingFaceApiKey(""), selectedAI(""), selectedAIVersion("gpt-3.5-turbo") {}

void AIChatbot::begin(long baudRate) {
    Serial.begin(baudRate);
}

bool AIChatbot::connectWiFi(const char* ssid, const char* password, unsigned long timeoutMs) {
    Serial.printf("Connecting to WiFi: %s\n", ssid);
    WiFi.begin(ssid, password);

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeoutMs) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected!");
        Serial.printf("IP Address: %s\n", WiFi.localIP().toString().c_str());
        return true;
    } else {
        Serial.println("\nWiFi Connection Failed.");
        return false;
    }
}

bool AIChatbot::validateKeys() {
    if (selectedAI == "chatgpt" && chatGPTApiKey.isEmpty()) {
        Serial.println("Error: ChatGPT API key is not set.");
        return false;
    } else if (selectedAI == "huggingface" && huggingFaceApiKey.isEmpty()) {
        Serial.println("Error: Hugging Face API key is not set.");
        return false;
    }
    return true;
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
    selectedAIVersion = (aiVersion != "null" && aiVersion != "none") ? aiVersion : "gpt-3.5-turbo";

    if (selectedAI == "chatgpt" && (selectedAIVersion != "gpt-3.5-turbo" && selectedAIVersion != "gpt-4")) {
        Serial.println("Warning: Unsupported ChatGPT version. Defaulting to gpt-3.5-turbo.");
        selectedAIVersion = "gpt-3.5-turbo";
    }
    if (selectedAI == "huggingface" && selectedAIVersion.isEmpty()) {
        Serial.println("Warning: Hugging Face version not set. Defaulting to the google/flan-t5-small.");
        selectedAIVersion = "google/flan-t5-small";
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

String AIChatbot::sanitizeInput(const String& input) {
    String sanitized = input;
    sanitized.replace("\\", "\\\\");
    sanitized.replace("\"", "\\\"");
    sanitized.replace("\n", "\\n");
    sanitized.replace("\r", "\\r");

    for (int i = 0; i < sanitized.length(); i++) {
        if (sanitized[i] < 32) { // ASCII 32
            sanitized.remove(i, 1);
            i--;
        }
    }

    return sanitized;
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

    String sanitizedMessage = sanitizeInput(message);
    String url = "https://api-inference.huggingface.co/models/" + selectedAIVersion;
    String payload = "{\"inputs\": \"" + sanitizedMessage + "\"}";

    return makeHttpRequest(url, payload, huggingFaceApiKey);
}


String AIChatbot::makeHttpRequest(const String& url, const String& payload, const String& apiKey) {
    HTTPClient http;
    WiFiClientSecure client;
    client.setInsecure();
    http.begin(client, url);

    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + apiKey);

    int httpResponseCode = http.POST(payload);
    String response = "";

    if (httpResponseCode > 0) {
        response = http.getString();
        Serial.printf("HTTP Response code: %d\nResponse body: %s\n", httpResponseCode, response.c_str());
    } else {
        response = "HTTP POST failed: " + String(http.errorToString(httpResponseCode).c_str());
        Serial.println(response);
        Serial.printf("Payload: %s\n", payload.c_str());
    }

    http.end();
    return response;
}