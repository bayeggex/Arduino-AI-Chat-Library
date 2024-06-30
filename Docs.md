# 🤖AI Chat Library for Arduino💬

AI Chat Library for Arduino allows you to easily integrate AI chatbot capabilities into your Arduino projects. This library supports multiple AI services, including OpenAI's ChatGPT and Hugging Face APIs, making it versatile and powerful for creating intelligent interactions.

## 📋 Project Overview

The AI Chat Library simplifies the process of connecting your Arduino projects to AI chatbots. It handles API communication, enabling your devices to send messages and receive responses from AI services over the internet.

## 🛠️Installation

1. **Download the Library**: Clone or download the repository from [GitHub](https://github.com/bayeggex/Arduino-AI-Chat-Library).
   
2. **Import into Arduino IDE**:
   - Open Arduino IDE.
   - Navigate to **Sketch > Include Library > Add .ZIP Library...** and select the downloaded ZIP file.

3. **Install Dependencies**:
   - Ensure you have the `WiFi` and `HTTPClient` libraries installed in your Arduino IDE via the Library Manager.

## 🚀Usage

### 🗝️Setting Up AI Keys

Before using the AI Chat Library, you need to set your API keys for the respective AI services. Here’s how you can do it in your Arduino sketch:

```cpp
#include <AIChatbot.h>

AIChatbot chatbot;

void setup() {
    Serial.begin(115200);
    
    // Set API keys
    chatbot.setKey("YOUR_CHATGPT_API_KEY", "chatgpt");
    chatbot.setKey("YOUR_HUGGING_FACE_API_KEY", "huggingface");

    // Begin WiFi connection
    WiFi.begin("SSID", "PASSWORD");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    
    // Select AI and optionally specify version
    chatbot.selectAI("chatgpt", "gpt-3.5-turbo");
}

void loop() {
    // Update and handle incoming messages
    chatbot.update();
}
```

### 📄Functions

#### `selectAI(const String& aiName, const String& aiVersion = "gpt-3.5-turbo")`

- **Description**: Selects the AI service to use.
- **Parameters**:
  - `aiName`: Name of the AI service (e.g., "chatgpt", "huggingface").
  - `aiVersion` (optional): Version of the AI model to use (default: "gpt-3.5-turbo").
- **Example**:
  ```cpp
  chatbot.selectAI("chatgpt", "gpt-4");

#### `setKey(const String& apiKey, const String& apiName)`

- **Description**: Sets the API key for a specific AI service.
- **Parameters**:
  - `apiKey`: API key for the AI service.
  - `apiName` (optional): Name of the AI service (e.g., "chatgpt", "huggingface").
- **Example**:
  ```cpp
  chatbot.setKey("YOUR_CHATGPT_API_KEY", "chatgpt");

#### `send(const String& message)`

- **Description**: Sends a message to the selected AI service manually.
- **Parameters**:
  - `message`: Message to send to the AI service.
- **Example**:
  ```cpp
  String response = chatbot.send("Hello, how are you?");
  Serial.println("Response from AI: " + response);

#### `update()`

- **Description**: Updates the AI Chatbot instance to handle incoming messages and maintain communication.
- **Example**:
  ```cpp
  void loop() {
    chatbot.update();
  }
