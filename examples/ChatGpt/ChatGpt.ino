#include "AIChatbot.h" // Include the AIChatbot library

AIChatbot chatbot; // Create an instance of the AIChatbot class

// WiFi and ChatGPT API credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* apiKey = "YOUR_CHATGPT_API_KEY";

void setup() {
    Serial.begin(115200); // Initialize serial communication at 115200 baud rate
    chatbot.begin(115200); // Initialize chatbot communication at 115200 baud rate

    // Connect to WiFi
    if (chatbot.connectWiFi(ssid, password)) {
        // Set the API key and select the AI model
        chatbot.setKey(apiKey, "chatgpt");
        chatbot.selectAI("chatgpt", "gpt-3.5-turbo");
        Serial.println("WiFi connected. Enter your question:");
    } else {
        Serial.println("WiFi connection failed.");
    }
}

void loop() {
    // Check if there is any data available in the serial buffer
    if (Serial.available() > 0) {
        // Read the input question from the serial monitor
        String question = Serial.readStringUntil('\n');
        question.trim(); // Remove any leading or trailing whitespace

        // If the question is not empty, get the response from ChatGPT
        if (question.length() > 0) {
            String response = chatbot.getResponse(question);
            Serial.println("ChatGPT Response: " + response); // Print the response
        } else {
            Serial.println("Please enter a valid question.");
        }
    }
}
