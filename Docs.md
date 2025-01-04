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
    chatbot.begin(115200);
    
    // Set API keys
    chatbot.setKey("YOUR_CHATGPT_API_KEY", "chatgpt");
    chatbot.setKey("YOUR_HUGGING_FACE_API_KEY", "huggingface");

    // Connect to WiFi
    if (!chatbot.connectWiFi("SSID", "PASSWORD")) {
        Serial.println("Failed to connect to WiFi");
        while (true); // Halt if WiFi connection fails
    }
    
    // Select AI service and optionally specify version
    chatbot.selectAI("chatgpt", "gpt-3.5-turbo");
}

void loop() {
    // Update and handle incoming messages
    chatbot.update();
}
```

### 📄Functions

### `begin(long baudRate)`

- **Description**: Initializes the serial communication with the specified baud rate.
- **Parameters**:
  - `baudRate`: The baud rate for serial communication (e.g., 115200).
- **Example**:
  ```cpp
  chatbot.begin(115200);

#### `connectWiFi(const char* ssid, const char* password, unsigned long timeoutMs = 10000)`

- **Description**: Connects to a WiFi network with the given SSID and password.
- **Parameters**:
  - `ssid`: WiFi SSID(Name).
  - `password`: WiFi password.
  - `timeoutMs`:  (optional): Connection timeout in milliseconds (default is 10 seconds).
- **Example**:
  ```cpp
    if (!chatbot.connectWiFi("YourSSID", "YourPassword")) {
      Serial.println("WiFi connection failed");
    }

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

#### `getResponse(const String& message)`

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

### `sanitizeInput(const String& input)`

- **Description**: Sanitizes the input string to prevent issues with special characters.
- **Parameters**:
  - `input`:The input string to sanitize.


### 🔧 Internal Functions (Private)

These functions are used internally by the library and are not intended to be called directly by users.

`sendToChatGPT(const String& message)`

- Sends a message to the OpenAI ChatGPT API and returns the response.

`sendToHuggingFace(const String& message)`

- Sends a message to the Hugging Face API and returns the response.

`makeHttpRequest(const String& url, const String& payload, const String& apiKey)`

-Makes an HTTP POST request to the specified URL with the given payload and API key.

### 📚 Header File (AIChatbot.h)

```h
#ifndef AI_CHATBOT_H
#define AI_CHATBOT_H

#include <Arduino.h>

#if defined(ESP32)
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#define PLATFORM_NAME "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define PLATFORM_NAME "ESP8266"
#endif

class AIChatbot {
public:
    AIChatbot();
    bool connectWiFi(const char* ssid, const char* password, unsigned long timeoutMs = 10000);
    bool validateKeys();
    void begin(long baudRate);
    void update();
    void setKey(const String& key, const String& aiName);
    void selectAI(const String& aiName, const String& aiVersion = "gpt-3.5-turbo");
    String sanitizeInput(const String& input);
    String getResponse(const String& message);

private:
    String chatGPTApiKey;
    String huggingFaceApiKey;
    String selectedAI;
    String selectedAIVersion;
    String sendToChatGPT(const String& message);
    String sendToHuggingFace(const String& message);
    String makeHttpRequest(const String& url, const String& payload, const String& apiKey);
};

#endif // AI_CHATBOT_H
```

### 🔧 Example Sketches

`AITranslation.ino`: Demonstrates translation capabilities using the library.

`ChatGPT.ino`: Example of integrating with ChatGPT for general conversation.

`DataTest.ino`: Verifies communication and tests various AI responses.

`HuggingFace.ino`: Shows usage with Hugging Face models.

`QuestionAnswering.ino`: Example for question-answering tasks.

`TextGeneration.ino`: Demonstrates text generation capabilities.

`TextSummarization.ino`: Example for summarizing input text.

### 📈 Roadmap

- Add support for more AI services.

- Improve error handling and debugging tools.

- Enhance documentation with more detailed examples.

- Voice & Image Cration.

### 🛠️ Support

For [issues](https://github.com/bayeggex/Arduino-AI-Chat-Library/issues/new), [feature requests](https://github.com/bayeggex/Arduino-AI-Chat-Library/issues/new), or [Contributions](https://github.com/bayeggex/Arduino-AI-Chat-Library/pulls), please visit the [GitHub repository](https://github.com/bayeggex/Arduino-AI-Chat-Library).

This library is maintained by [BayEggex](https://github.com/bayeggex). Contributions are welcome!
