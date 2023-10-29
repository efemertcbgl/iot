#include <ESP8266WiFi.h>

const char* ssid = "Efe Laptop";
const char* password = "EhjdG3f7";

WiFiServer server(80);

String html ="<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>Led Testi</title> </head> <body style='display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0;'> <div style=\"text-align: center;\"> <button onclick=\"javascript: alert('UYARI! Led Açıldı.')\" style=\" padding: 10px 20px; font-size: 16px; background-color: green;\">Aç</button> <button onclick=\"javascript: alert('UYARI! Led Kapatıldı.')\" style=\" padding: 10px 20px; font-size: 16px; background-color: red;\">Kapat</button> </div> </body> </html>";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println(ssid);
  Serial.println("'e Bağlanılıyor");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Bağlandı.");

  server.begin();
  Serial.println("Server Başlatıldı.");

  Serial.print("Bağlantı URL'si:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if(!client) {return;}

  Serial.println("Veri Bekleniyor...");
  while(!client.available()){delay(1);}

  String a = client.readStringUntil('\r');
  Serial.println(a);
  client.flush();

  
  client.println("");
  client.println(html);

  
  client.println("");

  delay(1);
  Serial.println("İstemci Bağlantısı Kesildi.");
  Serial.println("");
}
