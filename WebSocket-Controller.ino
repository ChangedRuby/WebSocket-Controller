#include <WiFi.h>
#include <WebSocketsServer.h>

// This controller uses 4 buttons to movement (Up, Down, Left, Right), feel free to change to any amount you would use or even implement a Joystick! :)
#define btn_1 0 // FIRST DIGITAL PIN HERE
#define btn_2 0 // FIRST DIGITAL PIN HERE
#define btn_3 0 // FIRST DIGITAL PIN HERE
#define btn_4 0 // FIRST DIGITAL PIN HERE

// Flags to prevent repetitive sending of information.
int flag_btn1 = 0;
int flag_btn2 = 0;
int flag_btn3 = 0;
int flag_btn4 = 0;

// Constants
// Name and Password are for the WiFi connection.
const char* ssid = ""; // CONNECTION NAME HERE
const char* password = ""; // PASSWORD HERE

// Globals
WebSocketsServer webSocket = WebSocketsServer(80);

// Called when receiving any WebSocket message
void onWebSocketEvent(uint8_t num,
                      WStype_t type,
                      uint8_t * payload,
                      size_t length) {

  // Figure out the type of WebSocket event
  switch(type) {

    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;

    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connection from ", num);
        Serial.println(ip.toString());
      }
      break;

    // Echo text message back to client
    case WStype_TEXT:
      Serial.printf("[%u] Text: %s\n", num, payload);
      webSocket.sendTXT(num, "Hello godot");
      Serial.println(num);
      break;

    // For everything else: do nothing
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
  }
}

void setup() {

// Setups pins in which the buttons are connected.
  pinMode(btn_1, INPUT_PULLUP);
  pinMode(btn_2, INPUT_PULLUP);
  pinMode(btn_3, INPUT_PULLUP);
  pinMode(btn_4, INPUT_PULLUP);

  // Start Serial port
  Serial.begin(115200);

  // Connect to access point
  Serial.println("Connecting");
  WiFi.begin(ssid, password);

  // Prints '.' untils a connection is successful.
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }

  // Print our IP address
  Serial.println("Connected!");
  Serial.print("My IP address: ");
  Serial.println(WiFi.localIP());

  // Start WebSocket server and assign callback
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
}

void loop() {

// Logic for each button, which then sends a message to the WebSocket if any change is made.
  if(flag_btn1 == 1 && debounce(flag_btn1, btn_1) == LOW){
        webSocket.sendTXT(0, "soltou 1\n");
        Serial.println("enviando LOW");
        flag_btn1 = 0;
      }

  if(flag_btn1 == 0 && debounce(flag_btn1, btn_1) == HIGH){
        webSocket.sendTXT(0, "apertou 1\n");
        Serial.println("enviando HIGH");
        flag_btn1 = 1;
      }

  if(flag_btn2 == 1 && debounce(flag_btn2, btn_2) == LOW){
        webSocket.sendTXT(0, "soltou 2\n");
        Serial.println("enviando LOW");
        flag_btn2 = 0;
      }

  if(flag_btn2 == 0 && debounce(flag_btn2, btn_2) == HIGH){
        webSocket.sendTXT(0, "apertou 2\n");
        Serial.println("enviando HIGH");
        flag_btn2 = 1;
      }

  if(flag_btn3 == 1 && debounce(flag_btn3, btn_3) == LOW){
        webSocket.sendTXT(0, "soltou 3\n");
        Serial.println("enviando LOW");
        flag_btn3 = 0;
      }

  if(flag_btn3 == 0 && debounce(flag_btn3, btn_3) == HIGH){
        webSocket.sendTXT(0, "apertou 3\n");
        Serial.println("enviando HIGH");
        flag_btn3 = 1;
      }
      
  if(flag_btn4 == 1 && debounce(flag_btn4, btn_4) == LOW){
        webSocket.sendTXT(0, "soltou 4\n");
        Serial.println("enviando LOW");
        flag_btn4 = 0;
      }

  if(flag_btn4 == 0 && debounce(flag_btn4, btn_4) == HIGH){
        webSocket.sendTXT(0, "apertou 4\n");
        Serial.println("enviando HIGH");
        flag_btn4 = 1;
      }
      
  // Look for and handle WebSocket data
  webSocket.loop();

}

// Debounce is important to prevent small inconsistencies on the hardware of the the system.
int debounce(int estado, int pino){
  int estadoAtual = digitalRead(pino);
  if(estado != estadoAtual){
    delay(5);
    estadoAtual = digitalRead(pino);
  }
  return estadoAtual;
}