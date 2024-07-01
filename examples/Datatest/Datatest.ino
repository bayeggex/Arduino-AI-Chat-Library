#include <AIChatbot.h>

AIChatbot chatbot;

void setup() {
    Serial.begin(115200);
    
    // Set API keys
    chatbot.setKey("YOUR_CHATGPT_API_KEY", "chatgpt");

    //Begin WiFi connection
    chatbot.connectWiFi("YOUR_SSID", "YOUR_PASSWORD");
    
    // Select AI and optionally specify version
    chatbot.selectAI("chatgpt", "gpt-3.5-turbo");
}

void loop() {
    // Update and handle incoming messages
    chatbot.update();
}