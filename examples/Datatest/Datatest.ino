#include "AIChatbot.h" // Include the AIChatbot library

AIChatbot chatbot; // Create an instance of the AIChatbot class

// WiFi credentials and API key
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* apiKey = "YOUR_API_KEY";

void setup() {
    Serial.begin(115200); // Initialize serial communication at 115200 baud rate
    chatbot.begin(115200); // Initialize chatbot communication at 115200 baud rate

    // Attempt to connect to WiFi
    if (chatbot.connectWiFi(ssid, password)) {
        chatbot.setKey(apiKey, "chatgpt"); // Set the API key for the chatbot
        chatbot.selectAI("chatgpt"); // Select the AI model to use
        Serial.println(" test ready. Enter any text:"); // Indicate that the is ready for input
    } else {
        Serial.println("WiFi connection failed."); // Indicate that the WiFi connection failed
    }
}

void loop() {
    // Check if there is any input from the serial monitor
    if (Serial.available() > 0) {
        String inputText = Serial.readStringUntil('\n'); // Read the input text until a newline character is encountered
        inputText.trim(); // Remove any leading or trailing whitespace

        // Check if the input text is not empty
        if (inputText.length() > 0) {
            String response = chatbot.getResponse(inputText); // Get the response from the chatbot
            Serial.println("Response: " + response); // Print the response to the serial monitor
        } else {
            Serial.println("Please enter valid text."); // Prompt the user to enter valid text
        }
    }
}
