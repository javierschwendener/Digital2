const byte GLed = 39; //Se declara la LED verde
const byte BLed = 40; //Se declara la LED azul
//Se declaran los botones a utilizar
const byte Push2 = 17; //Boton 2
const byte Push1 = 31; //Boton 1
//Se declaran las variables de estado
int S1 = 0;
int S2 = 0;
int C = 0;

void setup() {
  //Se declaran las leds como salidas
  pinMode(GLed, OUTPUT);
  pinMode(BLed, OUTPUT);
  pinMode(PA_7, OUTPUT);
  pinMode(PE_3, OUTPUT);
  pinMode(PE_2, OUTPUT);
  pinMode(PE_1, OUTPUT);
  pinMode(PD_3, OUTPUT);
  pinMode(PD_2, OUTPUT);
  pinMode(PB_1, OUTPUT);
  pinMode(PB_0, OUTPUT);
  pinMode(PA_2, OUTPUT);
  pinMode(PD_7, OUTPUT);
  pinMode(PC_7, OUTPUT);
  pinMode(PC_6, OUTPUT);
  pinMode(PC_5, OUTPUT);
  pinMode(PC_4, OUTPUT);
  pinMode(PB_3, OUTPUT);
  pinMode(PD_6, OUTPUT);
  //Se declara el modo en que se trabaja el pin seleccionado
  pinMode(Push1, INPUT_PULLUP);
  pinMode(Push2, INPUT_PULLUP);
  //Se llaman las funciones de interrupcion
  attachInterrupt(digitalPinToInterrupt(Push1), b1, FALLING);
  attachInterrupt(digitalPinToInterrupt(Push2), b2, FALLING);
}

void loop() {
  //Se modifican las leds segun el valor del contador del jugador 1
  while (C == 1) {
    switch (S1) {
      case 0:
        digitalWrite(PA_7, LOW);
        digitalWrite(PE_3, LOW);
        digitalWrite(PE_2, LOW);
        digitalWrite(PE_1, LOW);
        digitalWrite(PD_3, LOW);
        digitalWrite(PD_2, LOW);
        digitalWrite(PB_1, LOW);
        digitalWrite(PB_0, LOW);
        break;
      case 1:
        digitalWrite(PB_0, LOW);
        digitalWrite(PA_7, HIGH);
        break;
      case 2:
        digitalWrite(PA_7, LOW);
        digitalWrite(PE_3, HIGH);
        break;
      case 3:
        digitalWrite(PE_3, LOW);
        digitalWrite(PE_2, HIGH);
        break;
      case 4:
        digitalWrite(PE_2, LOW);
        digitalWrite(PE_1, HIGH);
        break;
      case 5:
        digitalWrite(PE_1, LOW);
        digitalWrite(PD_3, HIGH);
        break;
      case 6:
        digitalWrite(PD_3, LOW);
        digitalWrite(PD_2, HIGH);
        break;
      case 7:
        digitalWrite(PD_2, LOW);
        digitalWrite(PB_1, HIGH);
        break;
      case 8:
        digitalWrite(PB_1, LOW);
        digitalWrite(PB_0, HIGH);
        break;
      case 9:
        S1 = 0;
        S2 = 0;
        C = 0;
        digitalWrite(BLed, HIGH);
        digitalWrite(PA_7, LOW);
        digitalWrite(PE_3, LOW);
        digitalWrite(PE_2, LOW);
        digitalWrite(PE_1, LOW);
        digitalWrite(PD_3, LOW);
        digitalWrite(PD_2, LOW);
        digitalWrite(PB_1, LOW);
        digitalWrite(PB_0, LOW);
        break;
      default:
        digitalWrite(PA_7, LOW);
        digitalWrite(PE_3, LOW);
        digitalWrite(PE_2, LOW);
        digitalWrite(PE_1, LOW);
        digitalWrite(PD_3, LOW);
        digitalWrite(PD_2, LOW);
        digitalWrite(PB_1, LOW);
        digitalWrite(PB_0, LOW);
        break;
    }
    //Se modifican las leds segun el valor del contador del jugador 2
    switch (S2) {
      case 0:
        digitalWrite(PA_2, LOW);
        digitalWrite(PD_7, LOW);
        digitalWrite(PD_6, LOW);
        digitalWrite(PC_7, LOW);
        digitalWrite(PC_6, LOW);
        digitalWrite(PC_5, LOW);
        digitalWrite(PC_4, LOW);
        digitalWrite(PB_3, LOW);
        break;
      case 1:
        digitalWrite(PB_3, LOW);
        digitalWrite(PA_2, HIGH);
        break;
      case 2:
        digitalWrite(PA_2, LOW);
        digitalWrite(PD_7, HIGH);
        break;
      case 3:
        digitalWrite(PD_7, LOW);
        digitalWrite(PD_6, HIGH);
        break;
      case 4:
        digitalWrite(PD_6, LOW);
        digitalWrite(PC_7, HIGH);
        break;
      case 5:
        digitalWrite(PC_7, LOW);
        digitalWrite(PC_6, HIGH);
        break;
      case 6:
        digitalWrite(PC_6, LOW);
        digitalWrite(PC_5, HIGH);
        break;
      case 7:
        digitalWrite(PC_5, LOW);
        digitalWrite(PC_4, HIGH);
        break;
      case 8:
        digitalWrite(PC_4, LOW);
        digitalWrite(PB_3, HIGH);
        break;
      case 9:
        S1 = 0;
        S2 = 0;
        C = 0;
        digitalWrite(GLed, HIGH);
        digitalWrite(PA_2, LOW);
        digitalWrite(PD_7, LOW);
        digitalWrite(PD_6, LOW);
        digitalWrite(PC_7, LOW);
        digitalWrite(PC_6, LOW);
        digitalWrite(PC_5, LOW);
        digitalWrite(PC_4, LOW);
        digitalWrite(PB_3, LOW);
        break;
      default:
        digitalWrite(PA_2, LOW);
        digitalWrite(PD_7, LOW);
        digitalWrite(PD_6, LOW);
        digitalWrite(PC_7, LOW);
        digitalWrite(PC_6, LOW);
        digitalWrite(PC_5, LOW);
        digitalWrite(PC_4, LOW);
        digitalWrite(PB_3, LOW);
        break;
    }
  }
}

void b1() {
  if (C == 1) {
    S1 = S1 + 1;
  }
  if (C == 0) {
    C = 1;
    digitalWrite(GLed,LOW);
    digitalWrite(BLed,LOW);
    delay(500);
    digitalWrite(BLed, HIGH);
    delay(500);
    digitalWrite(GLed, HIGH);
    delay(500);
    digitalWrite(BLed, LOW);
    delay(500);
    digitalWrite(GLed, LOW);
  }
}

void b2() {
  if (C == 1) {
    S2 = S2 + 1;
  }
  if (C == 0) {
    C = 1;
    digitalWrite(GLed,LOW);
    digitalWrite(BLed,LOW);
    delay(500);
    digitalWrite(BLed, HIGH);
    delay(500);
    digitalWrite(GLed, HIGH);
    delay(500);
    digitalWrite(BLed, LOW);
    delay(500);
    digitalWrite(GLed, LOW);
  }
}
