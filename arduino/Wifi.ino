/*#include <WiFi.h>*/
/*
const char ="ssid";
const char ="password";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(5, OUTPUT);

    delay(10);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    
    while (WiFi.status() ! = WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();
}

int value = 0;

void loop()
{
    WiFiClient client j= jserver.available();   //listen for incoming clients


    if (client)
    {
        Serial.prinln("New Client.");
        String currentLine = "";
        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read();
                Serial.write(c);
                if (c=='\n')
                {
                    //If the current line is blank, you got two newline characteres in a row.
                    //that's the end of the client knows what's coming, then a blank line:
                    client.println("HTTP/1.1 200 OK");
                    client.println("Contnt-type:text/html");
                    client.println();

                    //the content of the HTTP reponse ends with another blank line:
                    client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
                    client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

                    //The HTTP reponse ends with another blank line:
                    client.println();
                    //break out of the while loop:
                    break;
                }
                else
                {  //If you got a new, then clear currenLine:
                currentLine ="";
                }                
            } else if(c!= '\r') //If you got anything else but a carriage return character, 
            {
                currentLine += c;//add it to the end of the currentLine
            }

            //Check to see if the client request was "GET \H" or "GET \L":
            if (currentLine.endsWith("GET /H"))
            {
                digitalWrite(5, HIGH); // GET;H turns the LED on
            }
            if (currentLine.endsWith("GET;L"))
            {
                digitalWrite(5, LOW);
            }
        }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");    
}
*/
/* ESP32 HTTP IoT Server Example for Wokwi.com

  https://wokwi.com/arduino/projects/320964045035274834

  To test, you need the Wokwi IoT Gateway, as explained here:

  https://docs.wokwi.com/guides/esp32-wifi#the-private-gateway

  Then start the simulation, and open http://localhost:9080
  in another browser tab.

  Note that the IoT Gateway requires a Wokwi Club subscription.
*/

//============================================= EXEMPLO =====================================================
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <uri/UriBraces.h>

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
// Defining the WiFi channel speeds up the connection:
#define WIFI_CHANNEL 6

WebServer server(80);

const int LED1 = 26;
const int LED2 = 27;

bool led1State = false;
bool led2State = false;

void sendHtml() {
  String response = R"(
    <!DOCTYPE html><html>
      <head>
        <title>ESP32 Web Server Demo</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
          html { font-family: sans-serif; text-align: center; }
          body { display: inline-flex; flex-direction: column; }
          h1 { margin-bottom: 1.2em; } 
          h2 { margin: 0; }
          div { display: grid; grid-template-columns: 1fr 1fr; grid-template-rows: auto auto; grid-auto-flow: column; grid-gap: 1em; }
          .btn { background-color: #5B5; border: none; color: #fff; padding: 0.5em 1em;
                 font-size: 2em; text-decoration: none }
          .btn.OFF { background-color: #333; }
        </style>
      </head>
            
      <body>
        <h1>ESP32 Web Server</h1>

        <div>
          <h2>LED 1</h2>
          <a href="/toggle/1" class="btn LED1_TEXT">LED1_TEXT</a>
          <h2>LED 2</h2>
          <a href="/toggle/2" class="btn LED2_TEXT">LED2_TEXT</a>
        </div>
      </body>
    </html>
  )";
  response.replace("LED1_TEXT", led1State ? "ON" : "OFF");
  response.replace("LED2_TEXT", led2State ? "ON" : "OFF");
  server.send(200, "text/html", response);
}

byte wifi_status() {
  // show WiFi status
  byte status = WiFi.status();
  static byte previousStatus = WL_DISCONNECTED;
  if (status != previousStatus) {
    previousStatus = status;
    Serial.print(status);
    switch (status) {
      case WL_IDLE_STATUS: Serial.println(" WL_IDLE_STATUS"); break;
      case WL_NO_SSID_AVAIL: Serial.println(" WL_NO_SSID_AVAIL"); break;
      case WL_SCAN_COMPLETED: Serial.println(" WL_SCAN_COMPLETED"); break;
      case WL_CONNECTED: Serial.println(" WL_CONNECTED"); break;
      case WL_CONNECT_FAILED: Serial.println(" WL_CONNECT_FAILED"); break;
      case WL_CONNECTION_LOST: Serial.println(" WL_CONNECTION_LOST"); break;
      case WL_DISCONNECTED: Serial.println(" WL_DISCONNECTED"); break;
      default: Serial.println(" unknown");
    }
  }
  return status;
}

void wifi_event(WiFiEvent_t event) {
  Serial.printf("[WiFi-event] event: %d -> ", event);

  switch (event) {
    case SYSTEM_EVENT_WIFI_READY:
      Serial.println("WiFi interface ready");
      break;
    case SYSTEM_EVENT_SCAN_DONE:
      Serial.println("Completed scan for access points");
      break;
    case SYSTEM_EVENT_STA_START:
      Serial.println("WiFi client started");
      break;
    case SYSTEM_EVENT_STA_STOP:
      Serial.println("WiFi clients stopped");
      break;
    case SYSTEM_EVENT_STA_CONNECTED:
      Serial.println("Connected to access point");
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("Disconnected from WiFi access point");
      break;
    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
      Serial.println("Authentication mode of access point has changed");
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.print("Obtained IP address: ");
      Serial.println(WiFi.localIP());
      break;
    case SYSTEM_EVENT_STA_LOST_IP:
      Serial.println("Lost IP address and IP address is reset to 0");
      break;
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
      Serial.println("WiFi Protected Setup (WPS): succeeded in enrollee mode");
      break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:
      Serial.println("WiFi Protected Setup (WPS): failed in enrollee mode");
      break;
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
      Serial.println("WiFi Protected Setup (WPS): timeout in enrollee mode");
      break;
    case SYSTEM_EVENT_STA_WPS_ER_PIN:
      Serial.println("WiFi Protected Setup (WPS): pin code in enrollee mode");
      break;
    case SYSTEM_EVENT_AP_START:
      Serial.println("WiFi access point started");
      break;
    case SYSTEM_EVENT_AP_STOP:
      Serial.println("WiFi access point  stopped");
      break;
    case SYSTEM_EVENT_AP_STACONNECTED:
      Serial.println("Client connected");
      break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
      Serial.println("Client disconnected");
      break;
    case SYSTEM_EVENT_AP_STAIPASSIGNED:
      Serial.println("Assigned IP address to client");
      break;
    case SYSTEM_EVENT_AP_PROBEREQRECVED:
      Serial.println("Received probe request");
      break;
    case SYSTEM_EVENT_GOT_IP6:
      Serial.println("IPv6 is preferred");
      break;
    case SYSTEM_EVENT_ETH_START:
      Serial.println("Ethernet started");
      break;
    case SYSTEM_EVENT_ETH_STOP:
      Serial.println("Ethernet stopped");
      break;
    case SYSTEM_EVENT_ETH_CONNECTED:
      Serial.println("Ethernet connected");
      break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
      Serial.println("Ethernet disconnected");
      break;
    case SYSTEM_EVENT_ETH_GOT_IP:
      Serial.println("Obtained IP address");
      break;
    default: break;
  }
}

void setup(void) {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  WiFi.onEvent(wifi_event);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
  Serial.print("Connecting to WiFi ");
  Serial.println(WIFI_SSID);
  // Wait for connection
  while (wifi_status() != WL_CONNECTED) {
    delay(10);
  }

  server.on("/", sendHtml);

  server.on(UriBraces("/toggle/{}"), []() {
    String led = server.pathArg(0);
    Serial.print("Toggle LED #");
    Serial.println(led);

    switch (led.toInt()) {
      case 1:
        led1State = !led1State;
        digitalWrite(LED1, led1State);
        break;
      case 2:
        led2State = !led2State;
        digitalWrite(LED2, led2State);
        break;
    }

    sendHtml();
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  // if WiFi is down, try reconnecting
  unsigned long currentMillis = millis();
  static unsigned long previousReconnect = 0;
  const unsigned long interval = 5000;
  if ((wifi_status() != WL_CONNECTED) && (currentMillis - previousReconnect >= interval)) {
    previousReconnect = currentMillis;
    Serial.print(millis());

    if (0) {
      // simple reconnect doesn't ever succeed on Wokwi
      Serial.println(" Disconnecting and Reconnecting WiFi...");
      WiFi.disconnect();
      WiFi.reconnect();
    } else {
      // but removing the WiFi config and starting afresh does work
      Serial.println(" Disconnecting and removing WiFi config...");
      WiFi.disconnect(true);
      Serial.println(" Reconfiguring WiFi...");
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
    }
  }

  server.handleClient();
  delay(2);
}
