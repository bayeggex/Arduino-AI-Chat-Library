#include "AIChatbot.h"

AIChatbot::AIChatbot()
    : chatGPTApiKey(""), huggingFaceApiKey(""), selectedAI(""), selectedAIVersion("gpt-3.5-turbo") {}

void AIChatbot::begin(long baudRate) {
    Serial.begin(baudRate);
    Serial.println(F("Serial communication started."));
}

bool AIChatbot::connectWiFi(const char* ssid, const char* password, unsigned long timeoutMs) {
#if defined(ESP8266)
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
#else // ESP32
    Serial.printf(F("Connecting to WiFi: %s\n"), ssid);
#endif

    WiFi.begin(ssid, password);

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && (millis() - startAttemptTime < timeoutMs)) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
#if defined(ESP8266)
        Serial.println();
        Serial.println("WiFi Connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP().toString());
#else // ESP32
        Serial.println(F("\nWiFi Connected!"));
        Serial.printf(F("IP Address: %s\n"), WiFi.localIP().toString().c_str());
#endif
        return true;
    } else {
        Serial.println();
        Serial.println(F("WiFi Connection Failed."));
        return false;
    }
}


bool AIChatbot::validateKeys() {
    if (selectedAI == "chatgpt" && chatGPTApiKey.length() == 0) {
        Serial.println(F("Error: ChatGPT API key is not set."));
        return false;
    } else if (selectedAI == "huggingface" && huggingFaceApiKey.length() == 0) {
        Serial.println(F("Error: Hugging Face API key is not set."));
        return false;
    }

    if (selectedAI.length() == 0) {
        Serial.println(F("Error: No AI selected."));
        return false;
    }

    return true;
}

void AIChatbot::update() {
    if (Serial.available() > 0) {
        String incomingMessage = Serial.readStringUntil('\n');
        incomingMessage.trim();
        if (incomingMessage.length() > 0) {
            Serial.print(F("Received: "));
            Serial.println(incomingMessage);
            
            String response = getResponse(incomingMessage);
            
            Serial.print(F("Response: "));
            Serial.println(response);
        }
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
        Serial.println(F("Warning: Unsupported ChatGPT version. Defaulting to gpt-3.5-turbo."));
        selectedAIVersion = "gpt-3.5-turbo"; 
    }
    if (selectedAI == "huggingface" && selectedAIVersion.length() == 0) {
        Serial.println(F("Warning: Hugging Face version not set. Defaulting to HuggingFaceH4/zephyr-7b-beta"));
        selectedAIVersion = "HuggingFaceH4/zephyr-7b-beta"; //Tested with this model 2025-2-2
    }
}

String AIChatbot::getResponse(const String& message) {
    if (selectedAI == "chatgpt") {
        String rawResponse = sendToChatGPT(message);
        String cleanedResponse = sanitizeOutput(rawResponse);
        return cleanedResponse;
    } else if (selectedAI == "huggingface") {
        String rawResponse = sendToHuggingFace(message);
        String cleanedResponse = sanitizeOutput(rawResponse);
        return cleanedResponse;
    } else {
        return F("AI type not selected.");
    }
}

String AIChatbot::sanitizeInput(const String& input) {
    String sanitized = input;
    sanitized.replace("\\", "\\\\");
    sanitized.replace("\"", "\\\"");
    sanitized.replace("\n", "\\n");
    sanitized.replace("\r", "\\r");
    sanitized.replace("\t", "\\t");

    for (int i = 0; i < sanitized.length(); i++) {
        if (sanitized[i] < 32 && sanitized[i] != '\n' && sanitized[i] != '\r' && sanitized[i] != '\t') {
            sanitized.remove(i, 1);
            i--;
        }
    }

    return sanitized;
}

String AIChatbot::sanitizeOutput(const String& output) {
    String sanitized = output;

    sanitized.replace("\\n", "\n");
    sanitized.replace("\\r", "\r");
    sanitized.replace("\\t", "\t");
    sanitized.replace("\\\"", "\"");
    sanitized.replace("\\\\", "\\");

    sanitized.replace("[{", "");
    sanitized.replace("}]", "");
    sanitized.replace("{", "");
    sanitized.replace("}", "");
    sanitized.replace("\"generated_text\":", "");
    sanitized.replace("\"", "");

    sanitized.trim();

    if (sanitized.length() > 0) {
        char lastChar = sanitized.charAt(sanitized.length() - 1);
        if (lastChar != '.' && lastChar != '?' && lastChar != '!') {
            sanitized += ".";
        }
    }

    return sanitized;
}


String AIChatbot::sendToChatGPT(const String& message) {
    if (chatGPTApiKey.length() == 0) {
        return "ChatGPT API key not set.";
    }

    String url = "https://api.openai.com/v1/chat/completions";
    String sanitizedMessage = sanitizeInput(message);
    String payload = "{\"model\": \"" + selectedAIVersion + "\", \"messages\": [{\"role\": \"user\", \"content\": \"" + sanitizedMessage + "\"}]}";

    return makeHttpRequest(url, payload, chatGPTApiKey);
}

String AIChatbot::sendToHuggingFace(const String& message) {
    if (huggingFaceApiKey.length() == 0) {
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

    if (!http.begin(client, url)) {
        Serial.println("Error: HTTP begin failed.");
        return "HTTP begin failed.";
    }
    
    http.setTimeout(10000);  // Timeout = 10 seconds if not probably null response
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Accept", "application/json");
    
    String authHeader = "Bearer " + apiKey;
    Serial.print("Using Authorization header: ");
    Serial.println(authHeader);
    http.addHeader("Authorization", authHeader);

    Serial.print("POST URL: ");
    Serial.println(url);
    Serial.print("Payload: ");
    Serial.println(payload);

    int retryCount = 0;
    int maxRetries = 2;
    int httpResponseCode = -1;
    String response;
    
    while (retryCount <= maxRetries) {
        httpResponseCode = http.POST(payload);
        if (httpResponseCode > 0) {
            break;
        } else {
            Serial.print("HTTP POST failed on try ");
            Serial.print(retryCount + 1);
            Serial.print(". Error: ");
            Serial.println(http.errorToString(httpResponseCode));
            retryCount++;
            delay(1000);
        }
    }
    
    if (httpResponseCode > 0) {
        if (httpResponseCode >= 200 && httpResponseCode < 300) {
            response = http.getString();
            Serial.printf("HTTP Response code: %d\nResponse body: %s\n", httpResponseCode, response.c_str());
        } else {
            response = "HTTP POST returned code: " + String(httpResponseCode) + ". Response: " + http.getString();
            Serial.println(response);
        }
    } else {
        response = "HTTP POST failed after retries. Error: " + String(http.errorToString(httpResponseCode).c_str());
        Serial.println(response);
    }

    http.end();
    return response;
}