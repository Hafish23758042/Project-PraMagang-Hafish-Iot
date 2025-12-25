#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

#define PIN_RELAY 19 
#define PIN_TRIG 5
#define PIN_ECHO 18

WiFiClient espClient;
PubSubClient client(espClient);

bool isManual = false;
unsigned long manualStartTime = 0;
const long manualDuration = 10000; 

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) { message += (char)payload[i]; }

  if (message == "ON") {
    isManual = true;
    manualStartTime = millis();
    digitalWrite(PIN_RELAY, HIGH); // SEKARANG: HIGH = NYALA
  } else if (message == "OFF") {
    isManual = true;
    manualStartTime = millis();
    digitalWrite(PIN_RELAY, LOW);  // SEKARANG: LOW = MATI
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, LOW); // Mulai dalam keadaan MATI
  
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32_Hafish_River_Final_V2")) {
      client.subscribe("sungai/kontrol");
    } else {
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  if (isManual && (millis() - manualStartTime > manualDuration)) {
    isManual = false;
  }

  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  float duration = pulseIn(PIN_ECHO, HIGH);
  float distance = (duration * 0.034) / 2;

  String statusAI = "AMAN";
  if (!isManual) {
    if (distance > 150) { // Kondisi BANJIR (jarak sensor jauh)
      statusAI = "BAHAYA";
      digitalWrite(PIN_RELAY, HIGH); // NYALA
    } else {
      statusAI = "AMAN";
      digitalWrite(PIN_RELAY, LOW);  // MATI
    }
  } else {
    statusAI = "MANUAL";
  }

  // --- SINKRONISASI TOTAL ---
  // Jika PIN bernilai HIGH, dashboard WAJIB lapor ON
  String pumpStatus = (digitalRead(PIN_RELAY) == HIGH) ? "ON" : "OFF";

  StaticJsonDocument<200> doc;
  doc["level"] = distance;
  doc["status"] = statusAI;
  doc["pump"] = pumpStatus;

  char buffer[256];
  serializeJson(doc, buffer);
  client.publish("sungai/data", buffer);
  
  Serial.print("Dist: "); Serial.print(distance);
  Serial.print(" | Pump: "); Serial.println(pumpStatus);
  delay(2000);
}