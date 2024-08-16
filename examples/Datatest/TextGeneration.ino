#include <AIChatbot.h>

AIChatbot chatbot;

void setup() {
    Serial.begin(115200);
    chatbot.setKey("YOUR_CHATGPT_API_KEY", "chatgpt");
    chatbot.connectWiFi("YOUR_SSID", "YOUR_PASSWORD");
    chatbot.selectAI("chatgpt", "gpt-3.5-turbo");
}

void loop() {
    if (Serial.available() > 0) {
        String incomingMessage = Serial.readString();
        String message = "Generate a text about: " + incomingMessage;
        String response = chatbot.getResponse(message);
        Serial.println("Generated Text: " + response);
    }
}
