#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

void setup() {
  
  Serial.begin(115200);                                  //Serial connection
  pinMode(13, OUTPUT);
  WiFi.begin("SSID", "Password");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
 
}
 
void AddGeoData(float package,float longitude,float lattitude){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
   StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
   JsonObject& JSONencoder = JSONbuffer.createObject();
   JSONencoder["package"] = package;
   JSONencoder["longitude"] = longitude;
   JSONencoder["lattitude"] = lattitude;
   char JSONmessageBuffer[300];
   JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://endpoint");      //Specify request destination
   http.addHeader("Content-Type", "application/json");  //Specify content-type header
   int httpCode = http.POST(JSONmessageBuffer);   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
}

void GetGeoData(){
    if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
      HTTPClient http;    //Declare object of class HTTPClient
 
      http.begin("http://endpoint");      //Specify request destination
      int httpCode = http.GET();   //Send the request
      if(httpCode>0){
         String payload = http.getString();                  //Get the response payload
         Serial.println(payload);    //Print request response payload
      }
      http.end();  //Close connection
    }else{

       Serial.println("Error in WiFi connection");
    }
}
 
void loop() {
  //AddGeoData(1,79.934703,6.825258)
  //GetGeoData()  
  delay(2000);  //Send a request every 30 seconds
 
}