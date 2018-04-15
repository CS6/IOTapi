#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

#include <PubSubClient.h>

#include "DHT.h"
#define DHTPIN 14     // Connect]ed to Pin D5 in NodeMCU
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE,15);
char serverAddress[] = "http://monospace-iot.trunksys.com/";
String writeAPIKey = "5PTJZFXQ6SWD32PR";

IRsend irsend(4);  // An IR LED is controlled by GPIO pin 2 (D2)   //DIFI的IR發射器接在腳位4(D2)
int valueB = LOW;
long lastConnectionTime = 0; 
boolean lastConnected = false;
int failedCounter = 0; // variable to store information about how many times ThingSpeak connection has been failed
int socketCounter = 0;
   uint16_t irSignal[] = {
 3484, 1704, 456, 1300, 432, 428, 436, 432, 432, 432, 432, 1300, 432, 428, 436, 432, 432, 432, 436, 428, 436, 1296, 432, 432, 432, 1300, 432, 1296, 432, 432, 432, 1300, 432, 1296, 432, 1300, 432, 1296, 432, 1296, 432, 432, 436, 428, 436, 1296, 432, 432, 436, 428, 436, 428, 436, 432, 432, 432, 436, 428, 436, 1296, 432, 1296, 436, 1296, 432, 1296, 432, 432, 432, 436, 432, 432, 432, 432, 432, 432, 432, 432, 432, 432, 436, 432, 432, 432, 432, 432, 432, 432, 436, 428, 436, 432, 432, 432, 432, 432, 436, 428, 436, 432, 432, 432, 432, 432, 432, 432, 436, 428, 436, 432, 432, 432, 436, 428, 436, 428, 436, 1296, 436, 428, 436, 428, 436, 428, 436, 432, 432, 432, 436, 428, 436, 29700, 3488, 1700, 460, 1300, 428, 432, 436, 428, 436, 432, 432, 1296, 436, 432, 432, 432, 432, 432, 432, 432, 432, 1300, 432, 432, 432, 1296, 436, 1296, 432, 432, 432, 1296, 436, 1296, 432, 1296, 432, 1300, 432, 1296, 432, 432, 436, 428, 436, 1296, 432, 432, 432, 432, 432, 432, 436, 428, 436, 432, 432, 432, 432, 432, 436, 428, 436, 428, 436, 432, 432, 432, 432, 432, 436, 428, 436, 428, 436, 432, 432, 432, 432, 432, 436, 428, 436, 1296, 436, 428, 436, 428, 436, 428, 436, 428, 436, 432, 432, 432, 432, 432, 436, 428, 436, 1296, 436, 1292, 436, 1296, 432, 432, 432, 1300, 432, 432, 432, 432, 432, 432, 436, 428, 436, 428, 436, 428, 436, 432, 436, 428, 436, 428, 436, 428, 436, 432, 436, 428, 436, 428, 436, 428, 436, 432, 432, 1296, 436, 1292, 436, 432, 436, 428, 436, 428, 436, 428, 436, 428, 436, 432, 436, 428, 436, 428, 436, 428, 460, 408, 460, 404, 460, 404, 460, 404, 464, 404, 460, 404, 460, 404, 460, 404, 460, 404, 464, 400, 464, 404, 460, 404, 460, 404, 464, 400, 464, 404, 464, 400, 464, 400, 464, 400, 468, 400, 464, 400, 464, 400, 468, 396, 468, 396, 468, 400, 468, 396, 468, 396, 472, 392, 472, 392, 472, 396, 472, 392, 472, 392, 472, 392, 472, 392, 476, 392, 472, 392, 472, 392, 472, 392, 472, 392, 472, 396, 468, 396, 468, 396, 468, 396, 468, 396, 468, 400, 464, 400, 464, 400, 460, 1244, 460, 1272, 456, 432, 436, 428, 432, 432, 436, 428, 436, 428, 436, 432, 432, 432, 432, 432, 432, 432, 432, 432, 432, 432, 436, 432, 432, 432, 432, 432, 432, 432, 432, 432, 432, 1300, 432, 432, 432, 432, 432, 432, 432, 436, 408, 1320, 428, 1304, 424, 440, 404
 
}; // 請輸入按鈕A的訊號(IRremote) - RAW
     uint16_t irSignal2[] = {
 3452, 1764, 400, 1332, 396, 472, 392, 472, 396, 468, 396, 1332, 396, 472, 396, 468, 396, 468, 396, 468, 396, 1332, 400, 468, 396, 1332, 396, 1332, 400, 468, 396, 1332, 396, 1332, 400, 1332, 396, 1332, 400, 1328, 400, 468, 396, 472, 392, 1332, 400, 468, 396, 468, 396, 472, 396, 468, 396, 468, 396, 468, 396, 1332, 396, 1332, 400, 1332, 396, 1332, 400, 468, 396, 468, 396, 468, 396, 472, 396, 468, 396, 468, 396, 468, 396, 468, 396, 468, 400, 468, 396, 468, 396, 468, 396, 468, 396, 468, 400, 468, 396, 468, 396, 468, 396, 468, 400, 464, 400, 468, 396, 468, 396, 468, 396, 468, 400, 464, 400, 468, 396, 1332, 396, 468, 400, 464, 400, 468, 396, 468, 396, 468, 400, 464, 400, 29736, 3452, 1796, 364, 1332, 400, 468, 396, 468, 396, 472, 396, 1332, 396, 468, 396, 468, 396, 472, 396, 468, 396, 1332, 396, 468, 396, 1332, 400, 1332, 396, 472, 392, 1332, 400, 1332, 396, 1332, 400, 1328, 400, 1332, 400, 468, 396, 468, 396, 1332, 396, 472, 396, 468, 396, 468, 396, 468, 396, 468, 396, 472, 396, 468, 396, 468, 396, 468, 396, 468, 400, 464, 400, 464, 400, 468, 396, 468, 396, 468, 396, 468, 400, 464, 400, 468, 396, 468, 396, 468, 400, 464, 400, 468, 396, 468, 396, 468, 400, 464, 400, 464, 400, 468, 396, 1328, 404, 1328, 400, 1328, 400, 468, 400, 1328, 400, 468, 396, 468, 400, 464, 400, 464, 400, 464, 400, 464, 400, 468, 396, 468, 400, 464, 400, 464, 400, 464, 400, 468, 400, 464, 400, 464, 400, 464, 400, 1328, 404, 1328, 400, 468, 396, 468, 396, 468, 400, 464, 400, 464, 400, 464, 404, 460, 404, 464, 400, 464, 400, 464, 400, 464, 404, 464, 400, 464, 400, 464, 400, 464, 400, 464, 404, 464, 400, 464, 400, 464, 400, 464, 400, 464, 404, 464, 400, 464, 400, 464, 400, 464, 404, 460, 404, 464, 400, 464, 400, 464, 400, 464, 404, 464, 400, 464, 400, 464, 400, 464, 404, 460, 404, 464, 400, 464, 400, 464, 404, 460, 404, 460, 404, 460, 404, 464, 400, 464, 404, 460, 404, 460, 404, 460, 428, 440, 428, 436, 428, 436, 432, 432, 428, 440, 428, 436, 428, 436, 432, 432, 432, 432, 436, 1296, 436, 1296, 464, 400, 464, 400, 472, 392, 472, 392, 472, 392, 476, 392, 472, 392, 472, 392, 476, 388, 476, 392, 472, 392, 476, 388, 476, 388, 480, 384, 480, 388, 476, 388, 476, 388, 476, 388, 480, 384, 480, 388, 476, 388, 476, 1228, 500, 1228, 504, 388, 476

}; //請輸入按鈕B的訊號(IRremote) - RAW 
int khz = 38; // 38kHz(除非確定不然不要改)


const char* ssid = "Nokia 6";
const char* password = "nullnull";
 
int ledPin = LED_BUILTIN;
WiFiServer server(80);
 

void setup() {
 
irsend.begin();
  Serial.begin(115200);
  delay(10);
    Serial.println("DHTxx test!");
 pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
void loop() {
   httpGET();
  ///////////////////////////
  delay(1000);   // Wait a few seconds between measurements.
  float h = dht.readHumidity();
  float t = dht.readTemperature();   // Read temperature as Celsius
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Humidity: ");    // show in serial monitor
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");    // show in serial monitor
  Serial.print(t);
  Serial.print(" *C \n");
  Serial.println(WiFi.localIP());

  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = HIGH;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, LOW); 
    value = LOW;
 irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array. 
  }
  
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
 irsend.sendRaw(irSignal2, sizeof(irSignal2) / sizeof(irSignal2[0]), khz); //Note the approach used to automatically calculate the size of the array. 
  }


////////////////////////////////////////////
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
    client.print("<meta charset=UTF-8>");

  client.print("Led pin is now: ");
 
    
 
  if(value == LOW) {
    client.print("On");
    //updateServer("field1="+value);
     /// char QAQ[]={"'name': 'letian', 'password': '123'"};
   /// updateServer(QAQ);
  
     client.print("updateServer(ON)");
      Serial.println("updateServer(ON)");
  } else {
    client.print("Off");
 //updateServer("field1="+value);
    client.print("updateServer(OFF)");
     Serial.println("updateServer(OFF)");
  }
 
  


client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />"); 
client.println("<h1>溫度</h1>");
if(valueB == 0) {
      client.print("By-Off");
 //updateServer("field1="+value);
    client.print("By-Server(OFF)");
     Serial.println("By-Server(OFF)");
  
  } 
if(valueB == 1)  {

       client.print("By-On");
 
     client.print("By-Server(ON)");
      Serial.println("By-Server(ON)");
  }

  client.println("</html>");
 
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");


//////////////////////////////////////
 httpPOST(value);
  

   
  
  }
void httpPOST(int value){
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
  float h = dht.readHumidity();
  float t = dht.readTemperature();   // Read temperature as Celsius
    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
  JsonObject& root=JSONbuffer.createObject();

 JsonArray& data = root.createNestedArray("data"); 
 JsonArray& data1 = data.createNestedArray();
 data1.add(h);
 data1.add(t);
 JsonArray& data2 = data.createNestedArray();
 data2.add(value);
 data2.add(value);
root.printTo(Serial); 
root.prettyPrintTo(Serial);
 
 
    char JSONmessageBuffer[300];
    root.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin("http://monospace-iot.trunksys.com/postjson");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header

    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println("AA");   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    Serial.println("BB");   //Print HTTP return code
/*



*/
    
    http.end();  //Close connection
 
  } else {
 
    Serial.println("Error in WiFi connection");
 
  }
 
 delay(3000);   //Send a request every 30 seconds
  

}
  
void httpGET()
{

 if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
  http.begin("http://monospace-iot.trunksys.com/about");      int httpCode = http.GET();                                                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload+"BY SERVER");                     //Print the response payload
  if (payload == "AA")  {
  
 valueB = 2; 
 }
 
 if (payload == "ON")  {
    digitalWrite(ledPin, LOW); 
    valueB = 1;
 irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array. 
  }
  
  if(payload == "OFF")  {
    digitalWrite(ledPin, HIGH);
    valueB = 0;
 irsend.sendRaw(irSignal2, sizeof(irSignal2) / sizeof(irSignal2[0]), khz); //Note the approach used to automatically calculate the size of the array. 
  }
      
 
    }
 
    http.end();   //Close connection
 
  }



  }

  

