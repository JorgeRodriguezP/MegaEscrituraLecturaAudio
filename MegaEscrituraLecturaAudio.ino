#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>

#include <Wire.h>
#include <RTClib.h>
//#include <SD.h>

//#define analogBatt1 0
//#define analogBatt2 1
//#define analogBatt3 2
//#define analogBatt4 3
//#define analogBatt5 4
//#define analogBatt6 5


#define SD_ChipSelectPin 53

/*
  CS --> D9
  Mosi --> D11
  SCK ---> D13
  Miso --> D12
  GND --> GND
  LED --> D7
  RX -->Debe ir al D6
  TX -->Debe ir al D5

*/

int led = 10; //puertosD 32,33,34,35 para leds. eliminar el 10****************************
int pulsador1 = digitalRead(3);
int pulsador2 = digitalRead(4);
int pulsador3 = digitalRead(5);
int pulsador4 = digitalRead(6);
int pulsador5 = digitalRead(7);
int pulsador6 = digitalRead(8);
int pulsadorW = digitalRead(9);

int ledGreen1 = 38;
int ledRed1 = 39;
int ledGreen2 = 40;
int ledRed2 = 41;
int ledGreen3 = 42;
int ledRed3 = 43;
int ledGreen4 = 44;
int ledRed4 = 45;
int ledGreen5 = 46;
int ledRed5 = 47;
int ledGreen6 = 48;
int ledRed6 = 49;

bool recordatorio1 = true;
bool recordatorio2 = true;
bool recordatorio3 = true;
bool recordatorio4 = true;
bool recordatorio5 = true;
bool recordatorio6 = true;

float analogValue1 = 0; float voltage1 = 0;
float analogValue2 = 0; float voltage2 = 0;
float analogValue3 = 0; float voltage3 = 0;
float analogValue4 = 0; float voltage4 = 0;
float analogValue5 = 0; float voltage5 = 0;
float analogValue6 = 0; float voltage6 = 0;

int ledDelay = 400;

// Threshold    *******agregar valor para baterias de litio******
float maxV = 1.4;

TMRpcm Audio;
File logFile;
RTC_DS3231 rtc;     // crea objeto del tipo RTC_DS3231

void setup()
{
  Serial.begin(9600);

  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println(F("Error al iniciar!!"));
    return;
  }
  Serial.println(F("SD iniciada correctamente"));

  if (! rtc.begin()) {
    Serial.println("RTC no encontrado!!");
    while (1);
  }
  Serial.println(F("RTC iniciado correctamente"));

  rtc.adjust(DateTime(__DATE__, __TIME__ ));
  Audio.speakerPin = 11; //Salida para el audio
  Audio.quality(1);
  Audio.setVolume(5);

  // Leds output mode ******************definir los otros 10 leds***************
  pinMode(ledGreen1, OUTPUT); pinMode(ledRed1, OUTPUT);
  pinMode(ledGreen2, OUTPUT); pinMode(ledRed2, OUTPUT);
  pinMode(ledGreen3, OUTPUT); pinMode(ledRed3, OUTPUT);
  pinMode(ledGreen4, OUTPUT); pinMode(ledRed4, OUTPUT);
  pinMode(ledGreen5, OUTPUT); pinMode(ledRed5, OUTPUT);
  pinMode(ledGreen6, OUTPUT); pinMode(ledRed6, OUTPUT);
}

void loop()
{
  DateTime fecha = rtc.now();

  // Reading analog input values ​​from battery meter
  analogValue1 = analogRead(A0);
  analogValue2 = analogRead(A1);
  analogValue3 = analogRead(A2);
  analogValue4 = analogRead(A3);
  analogValue5 = analogRead(A4);
  analogValue6 = analogRead(A5);

  // Get voltage
  voltage1 = 0.0048 * analogValue1;
  voltage2 = 0.0048 * analogValue2;
  voltage3 = 0.0048 * analogValue3;
  voltage4 = 0.0048 * analogValue4;
  voltage5 = 0.0048 * analogValue5;
  voltage6 = 0.0048 * analogValue6;

  // Voltage reading
  if ( voltage1 >= 0.9)
  {
    battery1();
  }

  if (voltage2 >= 0.9)
  {
    battery2();
  }

  if (voltage3 >= 0.9)
  {
    battery3();
  }

  if (voltage4 >= 0.9)
  {
    battery4();
  }

  if (voltage5 >= 0.9)
  {
    battery5();
  }

  if (voltage6 >= 0.9)
  {
    battery6();
  }
  
  int  valor1 = !digitalRead(3);
  if (digitalRead(3) == HIGH)
  {
    dates();
    boton1();
    boton11();
  }

  if (digitalRead(4) == HIGH)
  {
    dates();
    boton2();
    boton22();
  }

  if (digitalRead(5) == HIGH)
  {
    dates();
    boton3();
    boton33();
  }

  if (digitalRead(6) == HIGH)
  {
    dates();
    boton4();
    boton44();
  }

  if (digitalRead(7) == HIGH)
  {
    dates();
    boton5();
    boton55();
  }

  if (digitalRead(8) == HIGH)
  {
    dates();
    boton6();
    boton66();
  }

  if (digitalRead(9) == HIGH)
  {
    dates();
    botonW();
    botonWW();
  }

  //  digitalWrite(led, HIGH);
  //  delay(500);
  //  digitalWrite(led, LOW);
  //  delay(500);

  if (fecha.hour() == 8 && fecha.minute() == 0 && fecha.second() == 0) {
    if (recordatorio1 == true) {
      Serial.println("Pastillas AM"); logFile.print("Pastillas AM");
      recordatorio1 = false;
      Audio.play("8.wav");
      delay(6000);
    }
    recordatorio1 = true;
  }

  if (fecha.hour() == 19 && fecha.minute() == 0 && fecha.second() == 0) {
    if (recordatorio2 == true) {
      Serial.println("Pastillas PM"); logFile.print("Pastillas PM");
      recordatorio2 = false;
      Audio.play("8.wav");
      delay(6000);
    }
    recordatorio2 = true;
  }

  if (fecha.hour() == 9 && fecha.minute() == 0 && fecha.second() == 0) {
    if (recordatorio3 == true) {
      Serial.println("Ejercicio AM"); logFile.print("Ejercicio AM");
      recordatorio3 = false;
      Audio.play("8.wav");
      delay(6000);
    }
    recordatorio3 = true;
  }

  if (fecha.hour() == 14 && fecha.minute() == 0 && fecha.second() == 0) {
    if (recordatorio4 == true) {
      Serial.println("Ejercicio PM"); logFile.print("Ejercicio PM");
      recordatorio4 = false;
      Audio.play("8.wav");
      delay(6000);
    }
    recordatorio4 = true;
  }

  if (fecha.hour() == 11 && fecha.minute() == 0 && fecha.second() == 0) {
    if (recordatorio3 == true) {
      Serial.println("Actividad intelectual AM"); logFile.print("Actividad intelectual AM");
      recordatorio3 = false;
      Audio.play("8.wav");
      delay(6000);
    }
    recordatorio3 = true;
  }

  if (fecha.hour() == 16 && fecha.minute() == 0 && fecha.second() == 0) {
    if (recordatorio4 == true) {
      Serial.println("Actividad intelectual PM"); logFile.print("Actividad intelectual PM");
      recordatorio4 = false;
      Audio.play("8.wav");
      delay(6000);
    }
    recordatorio4 = true;
  }

}

void dates()
{
  logFile = SD.open("datalog.txt", FILE_WRITE); // Opening file and writing value

  DateTime fecha = rtc.now();

  Serial.print("Fecha ");

  logFile.print(fecha.day()); logFile.print("/");
  logFile.print(fecha.month()); logFile.print("/");
  logFile.print(fecha.year()); logFile.print(" ");
  logFile.print(fecha.hour()); logFile.print(":");
  logFile.print(fecha.minute()); logFile.print(":");
  logFile.print(fecha.second());

  Serial.print(fecha.day()); Serial.print("/");
  Serial.print(fecha.month()); Serial.print("/");
  Serial.print(fecha.year()); Serial.print(" ");
  Serial.print(fecha.hour()); Serial.print(":");
  Serial.print(fecha.minute()); Serial.print(":");
  Serial.print(fecha.second());

  logFile.close();
}

void boton1() {
  logFile = SD.open("datalog.txt", FILE_WRITE);// Abrir archivo y escribir valor

  logFile.print(", Boton1 "); logFile.println(pulsador1);
  Serial.print(", Boton1 "); Serial.println(pulsador1) + "\n";

  pulsador1++;
  logFile.close();
}

void boton11() {
  Audio.play("1.wav");
  delay(6000);
}

void boton2() {
  logFile = SD.open("datalog.txt", FILE_WRITE);// Abrir archivo y escribir valor

  logFile.print(", Boton2 "); logFile.println(pulsador2);
  Serial.print(", Boton2 "); Serial.println(pulsador2) + "\n";

  pulsador2++;
  logFile.close();

}

void boton22() {
  Audio.play("2.wav");
  delay(6000);

}


void boton3() {
  logFile = SD.open("datalog.txt", FILE_WRITE);// Abrir archivo y escribir valor

  logFile.print(", Boton3 "); logFile.println(pulsador3);
  Serial.print(", Boton3 "); Serial.println(pulsador3) + "\n";

  pulsador3++;
  logFile.close();

}

void boton33() {
  Audio.play("3.wav");
  delay(6000);

}

void boton4() {
  logFile = SD.open("datalog.txt", FILE_WRITE);// Abrir archivo y escribir valor

  logFile.print(", Boton4 "); logFile.println(pulsador4);
  Serial.print(", Boton4 "); Serial.println(pulsador4) + "\n";

  pulsador4++;
  logFile.close();

}

void boton44() {
  Audio.play("4.wav");
  delay(6000);

}


void boton5() {
  logFile = SD.open("datalog.txt", FILE_WRITE);// Abrir archivo y escribir valor

  logFile.print(", Boton5 "); logFile.println(pulsador5);
  Serial.print(", Boton5 "); Serial.println(pulsador5) + "\n";

  pulsador5++;
  logFile.close();

}

void boton55() {
  Audio.play("5.wav");
  delay(6000);

}


void boton6() {
  logFile = SD.open("datalog.txt", FILE_WRITE);// Abrir archivo y escribir valor

  logFile.print(", Boton6 "); logFile.println(pulsador6);
  Serial.print(", Boton6 "); Serial.println(pulsador6) + "\n";

  pulsador6++;
  logFile.close();

}

void boton66() {
  Audio.play("6.wav");
  delay(6000);

}

void botonW() {
  logFile = SD.open("datalog.txt", FILE_WRITE);// Abrir archivo y escribir valor

  logFile.print(", GANADOR! "); logFile.println(pulsadorW);
  Serial.print(", GANADOR! "); Serial.println(pulsadorW) + "\n";
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);

  pulsadorW++;
  logFile.close();

}

void botonWW() {
  Audio.play("7.wav");
  delay(6000);

}

void battery1()
{
  if (voltage1 >= maxV) {

    digitalWrite(ledGreen1, HIGH);
    delay(ledDelay);
    digitalWrite(ledGreen1, LOW);
    Serial.print("Voltaje1: ");
    Serial.println(voltage1);
  }
  
  else {
    digitalWrite(ledRed1, HIGH);
    delay(ledDelay);
    digitalWrite(ledRed1, LOW);
    Serial.print("Voltaje1: ");
    Serial.println(voltage1);
  }
}


void battery2()
{
  if (voltage2 >= maxV) {
    digitalWrite(ledGreen2, HIGH);
    delay(ledDelay);
    digitalWrite(ledGreen2, LOW);
    Serial.print("Voltaje2: ");
    Serial.println(voltage2);
  }
  else {
    digitalWrite(ledRed2, HIGH);
    delay(ledDelay);
    digitalWrite(ledRed2, LOW);
    Serial.print("Voltaje2: ");
    Serial.println(voltage2);
  }
}

void battery3()
{
  if (voltage3 >= maxV) {
    digitalWrite(ledGreen3, HIGH);
    delay(ledDelay);
    digitalWrite(ledGreen3, LOW);
    Serial.print("Voltaje3: ");
    Serial.println(voltage3);
  }
  else {
    digitalWrite(ledRed3, HIGH);
    delay(ledDelay);
    digitalWrite(ledRed3, LOW);
    Serial.print("Voltaje3: ");
    Serial.println(voltage3);
  }
}

void battery4()
{
  if (voltage4 >= maxV) {
    digitalWrite(ledGreen4, HIGH);
    delay(ledDelay);
    digitalWrite(ledGreen4, LOW);
    Serial.print("Voltaje4: ");
    Serial.println(voltage4);
  }
  else {
    digitalWrite(ledRed4, HIGH);
    delay(ledDelay);
    digitalWrite(ledRed4, LOW);
    Serial.print("Voltaje4: ");
    Serial.println(voltage4);
  }
}

void battery5()
{
  if (voltage5 >= maxV) {
    digitalWrite(ledGreen5, HIGH);
    delay(ledDelay);
    digitalWrite(ledGreen5, LOW);
    Serial.print("Voltaje5: ");
    Serial.println(voltage5);
  }
  else {
    digitalWrite(ledRed5, HIGH);
    delay(ledDelay);
    digitalWrite(ledRed5, LOW);
    Serial.print("Voltaje5: ");
    Serial.println(voltage5);
  }
}

void battery6()
{
  if (voltage6 >= maxV) {
    digitalWrite(ledGreen6, HIGH);
    delay(ledDelay);
    digitalWrite(ledGreen6, LOW);
    Serial.print("Voltaje6: ");
    Serial.println(voltage6);
  }
  else {
    digitalWrite(ledRed6, HIGH);
    delay(ledDelay);
    digitalWrite(ledRed6, LOW);
    Serial.print("Voltaje6: ");
    Serial.println(voltage6);
  }
}
