#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h> 

const char* ssid="S";
const char* password="hayo apa";

#define BOTtoken "1399263603:AAGpMkndl_9a3-HdhOkJWhUiBi6PA55nbIs"
#define CHAT_ID "1087283724"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay=1000;
unsigned long lastTimeBotRan;

const int Aman = 2;
const int Waspada = 3;
const int Siaga = 4;
const int Bahaya = 5;
int s1 = 0; int s2 = 0; int s3 = 0; int s4 = 0; //sensor level

void setup() {
  Serial.begin(115200);
  client.setInsecure();
  
  pinMode(8, INPUT);pinMode(9, INPUT);pinMode(10, INPUT);pinMode(11, INPUT); //Modul Limit Switch & LED
  pinMode(6, OUTPUT); //Buzzer
  pinMode(Aman, OUTPUT);pinMode(Waspada, OUTPUT);pinMode(Siaga, OUTPUT);pinMode(Bahaya, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());
}

void handleNewMessages(int numNewMessages){
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Selamat datang, " + from_name + ".\n";
      welcome += "Berikut indikator yang akan disampaikan oleh sistem :.\n\n";
      welcome += "Ketinggian Level 1 AMAN \n";
      welcome += "Ketinggian Level 2 WASPADA \n";
      welcome += "Ketinggian Level 3 SIAGA \n";
      welcome += "Ketinggian Level 4 BAHAYA \n";
      bot.sendMessage(chat_id, welcome, "");
    }
    s1 = digitalRead(8); s2 = digitalRead(9); s3 = digitalRead(10); s4 = digitalRead(11);
    if(s1 == HIGH && s2 == LOW && s3 == LOW && s4 == LOW){
      digitalWrite(2, HIGH);
      digitalWrite(6, LOW);
      Serial.print(" L/hour\r\n");
      Serial.print(" Status AMAN");
      bot.sendMessage(chat_id, "Ketinggian Level 1 AMAN", "");
    }
    
    if(s1 == HIGH && s2 == HIGH && s3 == LOW && s4 == LOW){
      digitalWrite(3, HIGH);
      digitalWrite(6, LOW);
      Serial.print(" L/hour\r\n");
      Serial.print(" Status Waspada");
      bot.sendMessage(chat_id, "Ketinggian Level 2 WASPADA", "");
      }
    if(s1 == HIGH && s2 == HIGH && s3 == HIGH && s4 == LOW){
      digitalWrite(4, HIGH);
      digitalWrite(6, LOW);
      Serial.print(" L/hour\r\n");
      Serial.print(" Status Siaga");
      bot.sendMessage(chat_id, "Ketinggian Level 3 SIAGA", "");
    }
    if(s1 == HIGH && s2 == HIGH && s3 == HIGH && s4 == HIGH){
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      Serial.print(" L/hour\r\n");
      Serial.print(" Status Bahaya");
      bot.sendMessage(chat_id, "Ketinggian Level 4 BAHAYA", "");
    }
    if(s1 == LOW && s2 == LOW && s3 == LOW && s4 == LOW){
      digitalWrite(2, HIGH);
      digitalWrite(6, LOW);
      Serial.print("--System On--");
      bot.sendMessage(chat_id, "Ketinggian Level 1 AMAN", "");
    }
  }
}

void loop() { 
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
delay(100);
}
