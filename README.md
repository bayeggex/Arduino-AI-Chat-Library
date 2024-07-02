<div align="center">

# AI Chat Library for Arduino <br> 🤖💬


![GitHub](https://img.shields.io/github/license/bayeggex/Arduino-AI-Chat-Library)
![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/bayeggex/Arduino-AI-Chat-Library?include_prereleases)
![GitHub last commit](https://img.shields.io/github/last-commit/bayeggex/Arduino-AI-Chat-Library)
![GitHub issues](https://img.shields.io/github/issues-raw/bayeggex/Arduino-AI-Chat-Library)
![GitHub pull requests](https://img.shields.io/github/issues-pr-raw/bayeggex/Arduino-AI-Chat-Library)

</div>

![tenor](https://github.com/bayeggex/Arduino-AI-Chat-Library/assets/79448667/ae4451d4-2c67-43bd-b8c7-e378960c33d1)


AIChatbot is a versatile Arduino library for integrating various AI chatbot APIs. It supports connecting to OpenAI's ChatGPT, Hugging Face Api's.

## ✨ Features

- **Versatile AI Integration**: Integrate various AI chatbot APIs seamlessly into your Arduino projects.
- **Supports Multiple APIs**: Connect to OpenAI's ChatGPT, Hugging Face APIs, and more with ease.
- **Easy Setup**: Simple API key configuration and setup for quick deployment.
- **Real-time Interaction**: Handle real-time messages and responses over WiFi.
- **Flexible AI Selection**: Choose between different AI versions such as "gpt-3.5-turbo","gpt-4" (more will be integrated)
- **Community-driven**: Contributions and improvements from the community are welcomed and encouraged.

## 🔧Installation

1. **Download the Library**: Download or clone this repository.

2. **Import into Arduino IDE**:
   - Open Arduino IDE.
   - Go to **Sketch > Include Library > Add .ZIP Library...** and select the downloaded ZIP file.

3. **Dependencies**:
   - This library requires the `WiFi` and `HTTPClient` libraries for making HTTP requests. Make sure to install these libraries through the Library Manager in Arduino IDE if not already installed.

## 🚀Usage

### Setting Up AI Keys

Before using the AIChatbot library, you need to set your API keys for the respective AI services. You can do this in your sketch code:

```cpp
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
```
## 🤝 Contributing
Contributions are welcome! To contribute to AIChatbot, fork this repository, make improvements, and submit a pull request. For major changes, please open an issue first to discuss what you would like to change.

    Fork the repository.
    Create a new branch: git checkout -b feature/amazing-feature
    Commit your changes: git commit -m 'Add some amazing feature'
    Push to the branch: git push origin feature/amazing-feature
    Open a pull request.

## 📚 Documentation

For detailed documentation, please refer to [Docs.md](./Docs.md).

## 📄 License

This project is licensed under the MIT License. See the LICENSE file for more details.

If you find this project helpful or interesting, don't forget to give it a star! ⭐

Express yourself freely and elevate your chat experience with Arduino-AI-Chat-Library! 😊
