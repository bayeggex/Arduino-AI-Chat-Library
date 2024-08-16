#include <AIChatbot.h>

AIChatbot chatbot;

void setup() {
    //changed to ESP32 115200 or ESP8266 9600
    Serial.begin(115200);
    
    // Set ChatGPT API key
    chatbot.setKey("YOUR_CHATGPT_API_KEY", "chatgpt");

    // Begin WiFi connection
    chatbot.connectWiFi("YOUR_SSID", "YOUR_PASSWORD");
    
    // Select AI and specify version
    chatbot.selectAI("chatgpt", "gpt-3.5-turbo");
}

void loop() {
    // Update and handle incoming messages
    chatbot.update();
}
