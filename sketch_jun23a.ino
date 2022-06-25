#include "CTBot.h"
CTBot robot;
int relay = 4;

String ssid_wifi = "Nama Wifi";
String password = "Kode WiFi";
String api_token = "kode Token Telegram";

void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

  // Konek ke wifi
  robot.wifiConnect(ssid_wifi, password);

  // Konek ke telegram
  robot.setTelegramToken(api_token);
  
  // Cek koneksi
  if(robot.testConnection())
    Serial.println("Terhubung :)");
  else
    Serial.println("Error!");
}

void loop() {

  TBMessage message;

  if(robot.getNewMessage(message)) {
  
    Serial.print("Ada pesan Masuk: ");
    Serial.println(message.text);     
    
    if(message.text.equalsIgnoreCase("ON")) {
      digitalWrite(relay, LOW);
      robot.sendMessage(message.sender.id, "Lampu Menyala");
    } else if(message.text.equalsIgnoreCase("OFF")) {
      digitalWrite(relay, HIGH);
      robot.sendMessage(message.sender.id, "Lampu Mati");   
    } else {
      String reply;
      reply = ("Perintah salah. Coba kirim ON atau OFF!");
      robot.sendMessage(message.sender.id, reply);
    }
    
  }
}
