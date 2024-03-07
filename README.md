# sensor de temperatura

Inclusão de Bibliotecas:

c

#include <OneWire.h>
#include <DallasTemperature.h>

O código começa incluindo duas bibliotecas: OneWire e DallasTemperature. Essas bibliotecas são comumente usadas para trabalhar com sensores de temperatura, especificamente aqueles que seguem o protocolo OneWire, como o sensor DS18B20.

Definição de Pinos:

c

#define ONE_WIRE_BUS 2
#define FAN_PIN 3
#define LED_PIN 4
#define BUZZER_PIN 5

O código define alguns pinos usados no Arduino. O pino 2 é usado para a comunicação com o sensor de temperatura, o pino 3 para controlar o motor do ventilador, o pino 4 para controlar um LED vermelho e o pino 5 para controlar uma buzina.

Inicialização do Sensor e Configuração de Pinos:

c

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

O código no bloco setup inicializa a comunicação serial, configura o sensor de temperatura e define os pinos especificados anteriormente como saídas.

Loop Principal:

c

void loop() {
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);
  Serial.print("Temperatura: ");
  Serial.println(temperatura);

No loop principal (loop), o código solicita a leitura da temperatura ao sensor e a armazena na variável temperatura. Em seguida, imprime essa temperatura no Monitor Serial.

Controle do Ventilador e Emergência:

c

  if (temperatura >= 30) {
    acionarVentilador();
  } else {
    desligarVentilador();
  }

  if (temperatura > 50) {
    acionarEmergencia();
  } else {
    desligarEmergencia();
  }

O código verifica se a temperatura está acima de 30 °C e, se sim, aciona o ventilador. Se estiver abaixo de 30 °C, o ventilador é desligado. Além disso, verifica se a temperatura ultrapassou os 50 °C; se sim, aciona um estado de emergência, caso contrário, desliga esse estado.

Funções de Controle:

c

void acionarVentilador() {
  digitalWrite(FAN_PIN, HIGH);
}

void desligarVentilador() {
  digitalWrite(FAN_PIN, LOW);
}

void acionarEmergencia() {
  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, 1000);  // Ativa a buzina com frequência de 1000 Hz
}

void desligarEmergencia() {
  digitalWrite(LED_PIN, LOW);
  noTone(BUZZER_PIN);  // Desativa a buzina
}

O código contém quatro funções que controlam o ventilador e a situação de emergência. acionarVentilador liga o ventilador, desligarVentilador o desliga, acionarEmergencia ativa um LED vermelho e uma buzina em caso de emergência, e desligarEmergencia desliga esses dispositivos.

Atraso entre Leituras:

c

  delay(1000);  // Aguarda 1 segundo entre as leituras
}

Um atraso de 1 segundo é adicionado entre as leituras de temperatura para evitar leituras muito frequentes.
