
//asignacion de pines para los leds

int const greenPin = 5;
int const yellowPin = 4;
int const redPin = 3;


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

//configuración de leds como salidas y velocidad de comunicación usb
void setup()
{
  Serial.begin(9600);// comunicación serial 9600 caracteres por segundo
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}


void loop()
{
  float distancia = 0.01723 * readUltrasonicDistance(2, 2); //valor distancia en cm con decimales
	
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
  Serial.print("distancia: "); //Imprimir en monitor en serie cadena de caracteres
  Serial.println(distancia+1.8); //Imprimir en monitor en serie valor distancia corregido
  delay(10); // Tiempo de espera mínimo para tener óptimo funcionamiento
}
