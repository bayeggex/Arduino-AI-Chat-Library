#include "AIChatbot.h" // Include the AIChatbot library

AIChatbot chatbot; // Create an instance of the AIChatbot class

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
// API key for Hugging Face
const char* apiKey = "YOUR_HUGGINGFACE_API_KEY";

void setup() {
    Serial.begin(115200); // Initialize serial communication at 115200 baud rate
    chatbot.begin(115200); // Initialize chatbot communication at 115200 baud rate

    // Attempt to connect to WiFi
    if (chatbot.connectWiFi(ssid, password)) {
        // Set the API key and select the AI model
        chatbot.setKey(apiKey, "huggingface");
        chatbot.selectAI("huggingface", "deepset/roberta-base-squad2");
        Serial.println("WiFi connected. Enter your question:");
    } else {
        Serial.println("WiFi connection failed.");
    }
}

void loop() {
    // Check if there is any input from the serial monitor
    if (Serial.available() > 0) {
        String question = Serial.readStringUntil('\n'); // Read the input question
        question.trim(); // Remove any leading or trailing whitespace

        // If the question is not empty, get the response from the chatbot
        if (question.length() > 0) {
            String response = chatbot.getResponse(question);
            Serial.println("Answer: " + response); // Print the response
        } else {
            Serial.println("Please enter a valid question."); // Prompt for a valid question
        }
    }
}
