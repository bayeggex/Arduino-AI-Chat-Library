#include <WiFi.h>
#include <WebServer.h>
#include <AIChatbot.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
// const char* apiKey = "YOUR_CHATGPT_API_KEY"; //for OPENAI
const char* apiKey = "YOUR_HUGGING_FACE_API_KEY"; //for Hugging face
const char* model = "HuggingFaceH4/zephyr-7b-beta"

AIChatbot chatbot;
WebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 ChatBot</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color: #1e1e1e;
      color: white;
      margin: 0;
      padding: 20px;
      display: flex;
      flex-direction: column;
      align-items: center;
    }

    #chat {
      width: 100%;
      max-width: 500px;
      height: 400px;
      overflow-y: auto;
      background-color: #2c2c2c;
      padding: 10px;
      border-radius: 10px;
      border: 1px solid #444;
    }

    .message {
      max-width: 80%;
      margin: 5px;
      padding: 10px;
      border-radius: 10px;
      word-wrap: break-word;
    }

    .user {
      background-color: #007bff;
      align-self: flex-end;
      color: white;
    }

    .bot {
      background-color: #444;
      align-self: flex-start;
    }

    #inputContainer {
      display: flex;
      width: 100%;
      max-width: 500px;
      margin-top: 10px;
    }

    #messageInput {
      flex: 1;
      padding: 10px;
      border: 1px solid #444;
      background-color: #2c2c2c;
      color: white;
      border-radius: 5px;
    }

    button {
      padding: 10px;
      background-color: #007bff;
      color: white;
      border: none;
      margin-left: 10px;
      border-radius: 5px;
      cursor: pointer;
    }

    button:hover {
      background-color: #0056b3;
    }

    .typing {
      font-style: italic;
      color: #888;
    }
  </style>
</head>
<body>
  <h2> Arduino-AI-Chat-Library Interface </h2>
  <div id="chat"></div>
  
  <div id="inputContainer">
    <input type="text" id="messageInput" placeholder="Message Your Microcontroller" />
    <button onclick="sendMessage()">Send</button>
    <button onclick="exportChat()">Export Chat</button>
  </div>

  <footer>
        <p>Built with ❤️ by BayEggex | Powered by Your❤️</p>
  </footer>

  <script>
    let chatHistory = "";

    function appendMessage(sender, text) {
      var chatDiv = document.getElementById("chat");
      var messageDiv = document.createElement("div");
      messageDiv.className = "message " + sender;
      messageDiv.innerHTML = parseMarkdown(text);
      chatDiv.appendChild(messageDiv);
      chatDiv.scrollTop = chatDiv.scrollHeight;

      chatHistory += sender.toUpperCase() + ": " + text + "\n";
    }

    function sendMessage() {
      var input = document.getElementById("messageInput");
      var message = input.value.trim();
      if (message === "") return;

      appendMessage("user", message);
      input.value = "";

      var typingDiv = document.createElement("div");
      typingDiv.className = "typing";
      typingDiv.innerText = "Bot Typing...";
      document.getElementById("chat").appendChild(typingDiv);

      var xhr = new XMLHttpRequest();
      xhr.open("POST", "/chat", true);
      xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
      xhr.onreadystatechange = function () {
        if (xhr.readyState === 4) {
          document.getElementById("chat").removeChild(typingDiv);
          if (xhr.status === 200) {
            appendMessage("bot", xhr.responseText.trim());
          } else {
            appendMessage("bot", "Error");
          }
        }
      };
      xhr.send("message=" + encodeURIComponent(message));
    }

    function exportChat() {
      const blob = new Blob([chatHistory], { type: 'text/plain' });
      const link = document.createElement('a');
      link.href = window.URL.createObjectURL(blob);
      link.download = "chat_history.txt";
      link.click();
    }
    
    function parseMarkdown(text) {
      text = text.replace(/\*\*(.*?)\*\*/g, '<strong>$1</strong>');
      text = text.replace(/\*(.*?)\*/g, '<em>$1</em>');
      return text;
    }

  </script>
</body>
</html>
)rawliteral";


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Now, open your browser and type in the " + WiFi.localIP().toString() + " Address shown above.");

  chatbot.setKey(apiKey, "huggingface");
                        //tested AI MODEL AND AI
  chatbot.selectAI("huggingface", model);


  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html", index_html);
  });

  server.on("/chat", HTTP_POST, []() {
    if (server.hasArg("message")) {
      String message = server.arg("message");
      Serial.println("Received message: " + message);

      if (WiFi.status() == WL_CONNECTED) {
        String response = chatbot.getResponse(message);
        server.send(200, "text/plain", response);
      } else {
        server.send(503, "text/plain", "No Wi-Fi connection.");
      }
    } else {
      server.send(400, "text/plain", "Missing parameter: message");
    }
  });

  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient();
}