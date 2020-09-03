// libreria para lcd
#include <LiquidCrystal.h>

// pines para incializar el lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//asignacion de pines para los leds
int const greenPin = 9;
int const yellowPin = 8;
int const redPin = 7;


//Inicio declaracion funcion readUltrasonicDistance,
//entrega medición realizada por sensor
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Inicializar LOW para limpiar trigger por 2 microsegundos
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Inicializar trigger en HIGH por 8 microsegundos para comenzar
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(8);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // lectura de pin echo con el retorno de la señal
  return pulseIn(echoPin, HIGH);
}

//configuración de leds como salidas, velocidad de comunicación usb, y configuracion incial LCD
void setup() {
  // condigura cantidad de columnas (16) y filas (2) del lcd
  lcd.begin(16, 2);
  // imprime la cadena de caracteres "Distancia" en LCD
  lcd.print("Distancia");
  
  Serial.begin(9600);// comunicación serial 9600 caracteres por segundo
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  
  float distancia = 0.01723 * readUltrasonicDistance(6, 6); //valor distancia en cm con decimales
	
  //condiciones para encendido de led rojo en rango entre 200 y 336 cm
  if((distancia <= 336) && (distancia >= 200)) {
    digitalWrite(redPin, HIGH);
  } 
  else {
    digitalWrite(redPin, LOW); 
  }
  
  //condiciones para encendido led amarillo entre rango de 100 y 200 cm
  if((distancia < 200) && (distancia >= 100)) {
    digitalWrite(yellowPin, HIGH);
  } 
  else {
    digitalWrite(yellowPin,LOW); 
  }
  //condiciones para encendido de led verde para un rango entre 0 y 100 cm
  if(distancia < 100) {
    digitalWrite(greenPin, HIGH);
  } 
  else {
    digitalWrite(greenPin, LOW);
  } 
  
  // posicionamiento del cursor en la columna 1, fila 2 
  // nota: 0 es primera posicion; 1 es segunda posicion...
  lcd.setCursor(0, 1);
  // imprime valor de la distancias en la posicion previamente indicada
  lcd.print(distancia);
  
  // posicionamiento en columna 8, fila 2
  lcd.setCursor(7, 1);
  // imprimir cadena de caracteres "cm" en posicion previamente indicada
  lcd.print("cm");
  delay(1000); //actualizacion cada 1 segundo
}
 
