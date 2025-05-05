
//----------------------------------------Include the NodeMCU ESP8266 Library---------------------------------------------------------------------------------------------------------------//
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

#define ON_Board_LED 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router

//----------------------------------------SSID and Password of your WiFi router-------------------------------------------------------------------------------------------------------------//
const char* ssid = "SepedaUGM"; //TP-LINK_AP_C5E7EB
const char* password = "";
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

unsigned int localPort = 2000;
IPAddress DestinationIP(192,168,0,100); //  192,168,100,4 192,168,43,31  192,168,0,100 //--> If the Destination IP is 192.168.15.10, then you can use the Destination IP 192.168.15.10 or 192.168.15.255
WiFiUDP udp; //

char packetBuffer[100];
String inString;
char replyBuffer[100];

//-----------------------------------------------------------------------------------------------SETUP--------------------------------------------------------------------------------------//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);

  WiFi.begin(ssid, password); //--> Connect to your WiFi router
//  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); 
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  //----------------------------------------Wait for connection
//  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
//    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
//  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("NodeMCU IP address : ");
  Serial.println(WiFi.localIP());
  //----------------------------------------
  udp.begin(localPort);
  Serial.print("Local Port : ");
  Serial.println(udp.localPort());
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------LOOP---------------------------------------------------------------------------------------//
void loop() {
  // put your main code here, to run repeatedly:
  receive_packet();

if (Serial.available() > 0){
 String input = Serial.readStringUntil('\n');
 
 
//  int input1 = input.indexOf(';');
//  int input2 = input.indexOf(';',input1+1);  
//
//  String dat1 = input.substring(0,input1); 
//  String dat2 = input.substring(input1+1,input2); 
//
//int arus = dat1.toInt(); 
//int rpm = dat2.toInt();
      input.toCharArray(replyBuffer, 100);
      udp.beginPacket(DestinationIP, 2000);
      udp.write(replyBuffer);
      udp.endPacket();
//      Serial.println(input);
  }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//----------------------------------------Procedure for receiving text / messages from the sender-------------------------------------------------------------------------------------------//
void receive_packet() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    IPAddress remoteIp = udp.remoteIP();
    int len = udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len] = 0;
    //Serial.print("From ");    //---|------------------------------------------------|
    //Serial.print(remoteIp);   //---| Use this to find out what IP the text is from. |
    //Serial.print(" : ");      //---|------------------------------------------------|
//    Serial.println(packetBuffer); 
  }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
