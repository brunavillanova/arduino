#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2  // Pino de dados do sensor de temperatura

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define FAN_PIN 3      // Pino de controle do motor de ventilador
#define LED_PIN 4      // Pino de controle do LED vermelho
#define BUZZER_PIN 5   // Pino de controle da buzina

void setup() {
  Serial.begin(9600);
  sensors.begin();

  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);

  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  // Verificar se a temperatura é maior ou igual a 30 °C
  if (temperatura >= 30) {
    acionarVentilador();
  } else {
    desligarVentilador();
  }

  // Verificar se a temperatura ultrapassa os 50 °C
  if (temperatura > 50) {
    acionarEmergencia();
  } else {
    desligarEmergencia();
  }

  delay(1000);  // Aguardar 1 segundo entre as leituras
}

void acionarVentilador() {
  digitalWrite(FAN_PIN, HIGH);
}

void desligarVentilador() {
  digitalWrite(FAN_PIN, LOW);
}

void acionarEmergencia() {
  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, 1000);  // Ativar a buzina com frequência de 1000 Hz
}

void desligarEmergencia() {
  digitalWrite(LED_PIN, LOW);
  noTone(BUZZER_PIN);  // Desligar a buzina
}
