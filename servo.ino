#include <ESP32Servo.h>
#include <WiFi.h>
#include <PubSubClient.h>

Servo Servo;

const char* ssid = "";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";
const char* topic = "";
// -------

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  Servo.attach(13);
  Serial.print("------------------------------");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WIFI Okay!");

  client.setServer(mqtt_server, 1883);

  Serial.println("Conectando ao MQTT Broker...");

  if (client.connect("esp32-luiz-test-5")) {
    client.subscribe(topic);
    client.setCallback(callback);
    Serial.println("Conectado! MQTT");
    initServo();
  } else {
    Serial.print("Falha na conexão, estado = ");
    Serial.println(client.state());
  }
}

void loop() {
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  String mensagem = "";
  for (int i = 0; i < length; i++) {
    mensagem += (char)payload[i];
  }
  int angle = mensagem.toInt();
  startMotor(angle);
}

void startMotor(int angle) {
  if (angle > 90) {
    angle = 90;
  }

  Servo.write(angle);
  delay(2000);
  resetServo();
}

void resetServo(){
  Servo.write(0);
}

void initServo(){
  Servo.write(90);
  delay(2000);
  resetServo();
}
