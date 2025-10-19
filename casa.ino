#include <LiquidCrystal.h>

// Configuración de la pantalla LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Pines para LEDs
const int ledPins[] = {22, 23, 24, 25, 26};
const int numLeds = 5;

// Pin para el sensor IR
const int irSensorPin = 29;

// Pines para indicador de humedad
const int humidityLedPin = 27; // LED para indicar humedad
const int drynessLedPin = 28;  // LED para indicar sequedad

// Pin para el sensor de humedad
const int humiditySensorPin = A1;
const int humidityThreshold = 600; // Umbral de humedad

// Pin para la fotorresistencia
const int photoResistorPin = A0;
const int threshold = 500;

// Pin para el buzzer y botones
const int buzzerPin = 13;
const int buttonPin = 6;
const int motorStartButton = 30;
const int motorDirectionButton = 31;

// Pines para el motor
const int motorPin1 = 32;
const int motorPin2 = 33;

// Variables de control
bool motorState = false; // Estado del motor
bool lastStartButtonState = HIGH; // Estado previo del botón de encendido
bool motorDirection = false; // Dirección del motor (normal/inversa)
bool lastDirectionButtonState = HIGH; // Estado previo del botón de dirección

void setup() {
  lcd.begin(16, 2);

  // Configurar pines de LEDs
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  // Configurar LEDs de humedad y sequedad
  pinMode(humidityLedPin, OUTPUT);
  pinMode(drynessLedPin, OUTPUT);
  digitalWrite(humidityLedPin, LOW);
  digitalWrite(drynessLedPin, LOW);

  // Configurar buzzer, botones y sensor IR
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(motorStartButton, INPUT_PULLUP);
  pinMode(motorDirectionButton, INPUT_PULLUP);
  pinMode(irSensorPin, INPUT);

  // Configurar pines del motor
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);

  // Mensaje inicial en la LCD
  lcd.setCursor(0, 0);
  lcd.print("Hola, Arduino!");
  lcd.setCursor(0, 1);
  lcd.print("Mega + IR Sensor!");
  delay(3000);
  lcd.clear();
}

void loop() {
  int lightLevel = analogRead(photoResistorPin);
  int humidityLevel = analogRead(humiditySensorPin);
  bool motionDetected = digitalRead(irSensorPin);

  // Mostrar nivel de luz
  lcd.setCursor(0, 0);
  lcd.print("Luz: ");
  lcd.print(lightLevel);

  // Control de LEDs según el sensor IR
  if (motionDetected) {
    lcd.setCursor(0, 1);
    lcd.print("MECOS");
    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Movimiento: NO");
  if (humidityLevel > humidityThreshold) {
    digitalWrite(humidityLedPin, HIGH);  // Enciende LED de humedad
    digitalWrite(drynessLedPin, LOW);   // Apaga LED de sequedad
  } else {
    digitalWrite(humidityLedPin, LOW);  // Apaga LED de humedad
    digitalWrite(drynessLedPin, HIGH); // Enciende LED de sequedad
  }

  // Activar buzzer si se presiona el botón
  if (digitalRead(buttonPin) == LOW) {
    tone(buzzerPin, 1000);
    delay(1000);
    noTone(buzzerPin);
  }

  // Control de encendido/apagado del motor
  bool currentStartButtonState = digitalRead(motorStartButton);
  if (currentStartButtonState == LOW && lastStartButtonState == HIGH) {
    motorState = !motorState; // Alternar estado del motor
  }
  lastStartButtonState = currentStartButtonState;

  // Cambiar dirección del motor
  bool currentDirectionButtonState = digitalRead(motorDirectionButton);
  if (currentDirectionButtonState == LOW && lastDirectionButtonState == HIGH) {
    motorDirection = !motorDirection; // Alternar dirección
  }
  lastDirectionButtonState = currentDirectionButtonState;

  // Configuración del motor según el estado
  if (motorState) {
    if (motorDirection) {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH); // Dirección inversa
    } else {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW); // Dirección normal
    }
  } else {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW); // Motor apagado
  }
  delay(500);
}