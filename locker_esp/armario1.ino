#include <WiFi.h>
#include <time.h>
#include <Firebase_ESP_Client.h>
#include <SPI.h>
#include <MFRC522.h>
#include <secrets.h>

#define RST_PIN 22
#define SS_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


void setup() {

  Serial.begin(115200);
  SPI.begin(18, 19, 23, SS_PIN);
  mfrc522.PCD_Init();

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWi-Fi conectado!");


  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;


  Firebase.begin(&config, &auth);
  fbdo.setBSSLBufferSize(2048, 512);
  fbdo.setResponseSize(1024);
  Firebase.reconnectWiFi(true);

}

String lastProcessedUID = "";
String lastProcessedStatus = "";

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) return;

  String cardUID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    cardUID += String(mfrc522.uid.uidByte[i], HEX);
  }
  cardUID.toUpperCase();

  Serial.println("Cartão detectado: " + cardUID);

  String path = "/lockers/" + String(LOCKER_ID);
  String uidPath = path + "/uid";
  String statusPath = path + "/status";
  String lastAccessPath = path + "/lastAccess";
  String now = String(millis());

  if (Firebase.RTDB.getString(&fbdo, uidPath)) {
    String currentUID = fbdo.stringData();

    if (Firebase.RTDB.getString(&fbdo, statusPath)) {
      String currentStatus = fbdo.stringData();

      if (currentStatus == "open" && currentUID == "null") {

        Firebase.RTDB.setString(&fbdo, uidPath, cardUID);
        Firebase.RTDB.setString(&fbdo, statusPath, "closed");
        Firebase.RTDB.setString(&fbdo, lastAccessPath, now);

        Serial.println("Armário reservado.");

        lastProcessedUID = cardUID;
        lastProcessedStatus = "closed";

      } else if (currentUID == cardUID) {

        bool op1 = Firebase.RTDB.setString(&fbdo, uidPath, "null");
        delay(500);
        bool op2 = Firebase.RTDB.setString(&fbdo, statusPath, "open");
        delay(500);
        bool op3 = Firebase.RTDB.setString(&fbdo, lastAccessPath, now);
        delay(500);

        if (op1 && op2 && op3) {
          Serial.println("Armário liberado.");
          lastProcessedUID = "";
          lastProcessedStatus = "open";
        } else {
          Serial.println("Falha ao liberar armário.");
        }

      } else {
        Serial.println("Cartão não autorizado.");
        lastProcessedUID = "";
        lastProcessedStatus = "";
      }
    } else {
      Serial.println("Erro ao ler status: " + fbdo.errorReason());
    }
  } else {
    Serial.println("Erro ao ler UID: " + fbdo.errorReason());
  }

  mfrc522.PICC_HaltA();
  delay(2000);
}
