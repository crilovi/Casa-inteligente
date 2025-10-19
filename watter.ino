int IN1 = 7;
int IN2 = 8;
int sensorHumedad = A0;  // Pin analógico donde conectas el sensor

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.begin(9600); // Para ver los valores en el monitor serial
}

void loop() {
  int humedad = analogRead(sensorHumedad);
  Serial.print("Humedad: ");
  Serial.println(humedad);

  if (humedad < 400) { // Suelo seco (ajusta este valor según tu sensor y tierra)
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(5000); // Bombea por 5 segundos
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW); // Bomba apagada
  }

  delay(10000); // Espera antes de volver a medir
}