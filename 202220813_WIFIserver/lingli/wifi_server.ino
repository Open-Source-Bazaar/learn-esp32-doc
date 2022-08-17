/*
    标题：在网页里控制红绿灯（ 红绿灯实验 第三节课 ）
    作者：灵儿、诗杰、唐总
    日期：2022-08-13

    说明：
        1 在浏览器访问一个网页，点击网页的按钮，控制红绿LED显示和隐藏
        2 分别使用 IO5、IO16 作为 绿灯、红灯 控制输出口，控制红绿 LED 作为 红绿灯的替代演示。
        3 正式项目可将红绿LED替换为继电器即可。

    实验准备物料：
        1 面包板：1块
        2 杜邦线：4根（一头针，一个孔）
        3 LED：绿色1个；红色1个
        4 ESP32开发板：一个
 */

#include <WiFi.h>

const char* ssid     = "***";
const char* password = "*********";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // set the LED pin mode
    pinMode(16, OUTPUT);

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
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

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html;charset=UTF-8");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("点击 <a href=\"/gree\">这里</a> ，点亮绿灯<br>");
            client.print("点击 <a href=\"/red\">这里</a> ，点亮红灯<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /gree")) {
          digitalWrite(5, HIGH); // GET /H turns the LED on
          digitalWrite(16, LOW);
        }
        if (currentLine.endsWith("GET /red")) {
          digitalWrite(5, LOW);                // GET /L turns the LED off
          digitalWrite(16, HIGH);   
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}