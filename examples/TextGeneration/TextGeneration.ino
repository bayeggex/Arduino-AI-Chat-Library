#include "AIChatbot.h" // Include the AIChatbot library

AIChatbot chatbot; // Create an instance of the AIChatbot class

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// API key for Hugging Face
const char* apiKey = "YOUR_HUGGINGFACE_API_KEY";

void setup() {
    Serial.begin(115200); // Initialize serial communication at 115200 baud rate
    chatbot.begin(115200); // Initialize the chatbot with the same baud rate

    // Attempt to connect to WiFi
    if (chatbot.connectWiFi(ssid, password)) {
        // Set the API key and select the AI model
        chatbot.setKey(apiKey, "huggingface");
        chatbot.selectAI("huggingface", "gpt2");
        Serial.println("WiFi connected. Enter a prompt to generate text:");
    } else {
        Serial.println("WiFi connection failed."); // Print error message if WiFi connection fails
    }
}

void loop() {
    // Check if there is any input from the serial monitor
    if (Serial.available() > 0) {
        String prompt = Serial.readStringUntil('\n'); // Read the input until a newline character
        prompt.trim(); // Remove any leading or trailing whitespace

        // Check if the prompt is not empty
        if (prompt.length() > 0) {
            String response = chatbot.getResponse(prompt); // Get the response from the chatbot
            Serial.println("Generated Text: " + response); // Print the generated text
        } else {
            Serial.println("Please enter a valid prompt."); // Prompt the user to enter a valid input
        }
    }
}
