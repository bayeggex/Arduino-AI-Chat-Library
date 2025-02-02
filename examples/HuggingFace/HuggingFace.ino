#include "AIChatbot.h"  // Include the AIChatbot library

AIChatbot chatbot;  // Create an instance of the AIChatbot class

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// API key for HuggingFace
const char* apiKey = "YOUR_HUGGINGFACE_API_KEY";

void setup() {
    Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
    chatbot.begin(115200);  // Initialize the chatbot with the same baud rate

    // Attempt to connect to WiFi
    if (chatbot.connectWiFi(ssid, password)) {
        // Set the API key and select the AI model
        chatbot.setKey(apiKey, "huggingface");
        chatbot.selectAI("huggingface", "distilbert-base-uncased");
        Serial.println("WiFi connected. Enter text:");
    } else {
        Serial.println("WiFi connection failed.");
    }
}

void loop() {
    // Check if there is any input from the serial monitor
    if (Serial.available() > 0) {
        String inputText = Serial.readStringUntil('\n');  // Read the input text until newline character
        inputText.trim();  // Remove any leading or trailing whitespace

        // If the input text is not empty, get the AI response
        if (inputText.length() > 0) {
            String response = chatbot.getResponse(inputText);
            Serial.println("AI Response: " + response);  // Print the AI response
        } else {
            Serial.println("Please enter valid text.");  // Prompt user to enter valid text
        }
    }
}
