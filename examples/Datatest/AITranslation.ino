#include "AIChatbot.h" // Include the AIChatbot library

AIChatbot chatbot; // Create an instance of AIChatbot

// WiFi and API credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* apiKey = "YOUR_API_KEY";

void setup() {
    Serial.begin(115200); // Initialize serial communication at 115200 baud rate
    chatbot.begin(115200); // Initialize chatbot communication at 115200 baud rate

    // Connect to WiFi
    if (chatbot.connectWiFi(ssid, password)) {
        // Set the API key and select the AI model for translation
        chatbot.setKey(apiKey, "huggingface");
        chatbot.selectAI("huggingface", "Helsinki-NLP/opus-mt-en-tr"); // English to Turkish translation
        Serial.println("WiFi connected. Enter text to translate:");
    } else {
        Serial.println("WiFi connection failed.");
    }
}

void loop() {
    if (Serial.available() > 0) {
        String inputText = Serial.readStringUntil('\n');
        inputText.trim();

        if (inputText.length() > 0) {
            String response = chatbot.getResponse(inputText);
            Serial.println("Translated Text: " + response);
        } else {
            Serial.println("Please enter valid text.");
        }
    }
}

