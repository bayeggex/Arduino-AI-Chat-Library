#include <AIChatbot.h>

AIChatbot chatbot;

void setup() {
    //changed to ESP32 115200 or ESP8266 9600
    Serial.begin(115200);
    
    // Set API keys
    chatbot.setKey("HUGGING FACE API KEY", "huggingface");

    //Begin WiFi connection
    chatbot.connectWiFi("YOUR_SSID", "YOUR_PASSWORD");
    
    // Select AI and optionally specify version
    // Tested and used google/flan-t5-small
    chatbot.selectAI("huggingface", "google/flan-t5-small");
}

void loop() {
    // Update and handle incoming messages
    chatbot.update();
}