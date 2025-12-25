#include <WiFi.h>
#include <PubSubClient.h>

// Konfigurasi WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Konfigurasi MQTT
const char* mqtt_server = "broker.hivemq.com";
const char* topic = "iot/flood/level";

// Pin Sensor Ultrasonik
const int trigPin = 5;
const int echoPin = 18;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println("\n--- WiFi Setup ---");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Gunakan ID unik agar tidak bentrok dengan user lain di broker publik
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected to Broker");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  
  // Menghitung jarak (cm)
  float distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Membaca nilai dari sensor di Wokwi
  float currentDistance = getDistance();
  
  // Karena Anda ingin data SEARAH dengan slider:
  // Kita langsung gunakan nilai distance sebagai tinggi air
  float waterLevel = currentDistance; 

  // Proteksi jika sensor membaca error (0 atau terlalu jauh)
  if (waterLevel < 0) waterLevel = 0;

  // Konversi float ke string untuk MQTT
  char msg[16];
  dtostrf(waterLevel, 1, 2, msg); 

  // Output ke Serial Monitor
  Serial.print("Nilai Slider (Tinggi Air): ");
  Serial.print(msg);
  Serial.println(" cm");

  // Kirim ke Broker MQTT
  client.publish(topic, msg);

  delay(2000); 
}