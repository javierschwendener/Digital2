// Se incluyen las librerias a utilizar
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
// Se agregan los archivos necesarios
#include "index.h"
// Se declaran las variables
int parking;
int P1;
int P2;
int P3;
int P4;
int inUse;
// Se establece el puerto del servidor
WebServer server(80);
// Se establece la red de conexion
const char* ssid = "Schinzii";
const char* password = "Schwendener411";
// Se declaran las funciones del servidor web
// mainF sera la funcion por la cual se carga el .html
void mainF(){
  String s = MAIN_page;
  server.send(200,"text/html",s);
}
// Las funciones handle de P1 a P4 se ocupan de pasar 
// el estado del parqueo en cuestion
void handleP1(){
  String SP1;
  if(P1==1){
    SP1 = "Ocupado";
  }
  else{
    SP1 = "Libre";
  }
  server.send(200,"text/html",SP1);
}
void handleP2(){
  String SP2;
  if(P2==1){
    SP2 = "Ocupado";
  }
  else{
    SP2 = "Libre";
  }
  server.send(200,"text/html",SP2);
}
void handleP3(){
  String SP3;
  if(P3==1){
    SP3 = "Ocupado";
  }
  else{
    SP3 = "Libre";
  }
  server.send(200,"text/html",SP3);
}
void handleP4(){
  String SP4;
  if(P4==1){
    SP4 = "Ocupado";
  }
  else{
    SP4 = "Libre";
  }
  server.send(200,"text/html",SP4);
}

void setup() {
  // Se declaran los pines de salida para el 7 segmentos
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(33,OUTPUT);
  // Se inicia la comunicacion serial
  Serial.begin(9600);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  while (! Serial);
  // Se inicializa el modulo WiFi
  WiFi.begin(ssid,password);
  WiFi.mode (WIFI_STA);
  // Se espera a la conexion de la red
  while(WiFi.status()!=WL_CONNECTED);
  // Se muestra la IP en el monitor serial
  Serial.println(WiFi.localIP());
  // Se activan las funciones de WiFi
  server.on("/",mainF);
  server.on("/readP1",handleP1);
  server.on("/readP2",handleP2);
  server.on("/readP3",handleP3);
  server.on("/readP4",handleP4);
  // Se abre el servidor
  server.begin();
}
// Loop principal
void loop() {
  // Se espera a que reciba un dato en el puerto serial 2
  while (Serial2.available()){
    // Se guarda el dato
    parking = Serial2.read();
    // Por programacion en la Tiva, se comprueba el estado de las LEDs
    // y se almacena el estado de cada una en las variables de P1 a P4 respectivamente 
    if(parking >= 8){
      P1 = 1;
      parking = parking - 8;
    }
    else{
      P1 = 0;
    }
    if(parking >= 4){
      P2 = 1;
      parking = parking - 4;
    }
    else{
      P2 = 0;
    }
    if(parking >= 2){
      P3 = 1;
      parking = parking - 2;
    }
    else{
      P3 = 0;
    }
    if(parking >= 1){
      P4 = 1;
      parking = parking - 1;
    }
    else{
      P4 = 0;
    }
    // Se obtiene el numero de parqueos libres
    inUse = 4-(P1+P2+P3+P4);
  }
  // Se crea la tabla para el 7 segmentos
  switch(inUse){
    case 0: // Dibuja 0
      digitalWrite(13,LOW);
      digitalWrite(12,HIGH);
      digitalWrite(14,HIGH);
      digitalWrite(27,HIGH);
      digitalWrite(26,HIGH);
      digitalWrite(25,HIGH);
      digitalWrite(33,HIGH);
      break;
    case 1: // Dibuja 1
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
      digitalWrite(14,LOW);
      digitalWrite(27,LOW);
      digitalWrite(26,LOW);
      digitalWrite(25,HIGH);
      digitalWrite(33,HIGH);
      break;
    case 2: // Dibuja 2
      digitalWrite(13,HIGH);
      digitalWrite(12,LOW);
      digitalWrite(14,HIGH);
      digitalWrite(27,HIGH);
      digitalWrite(26,HIGH);
      digitalWrite(25,HIGH);
      digitalWrite(33,LOW);
      break;
    case 3: // Dibuja 3
      digitalWrite(13,HIGH);
      digitalWrite(12,LOW);
      digitalWrite(14,LOW);
      digitalWrite(27,HIGH);
      digitalWrite(26,HIGH);
      digitalWrite(25,HIGH);
      digitalWrite(33,HIGH);
      break;
    case 4: // Dibuja 4
      digitalWrite(13,HIGH);
      digitalWrite(12,HIGH);
      digitalWrite(14,LOW);
      digitalWrite(27,LOW);
      digitalWrite(26,LOW);
      digitalWrite(25,HIGH);
      digitalWrite(33,HIGH);
      break;
  }
  // Se mantiene el servidor abierto
  server.handleClient();
}
