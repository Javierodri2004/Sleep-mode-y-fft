// Definir los pines donde están conectados los segmentos
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; // a, b, c, d, e, f, g
long randNumber;
// Tabla de consulta (LUT) para los números 0-9 en el display de 7 segmentos
const uint8_t lookup_table[10] = {
  0b1000000,  // 0
  0b1111001,  // 1
  0b0100100,  // 2
  0b0110000,  // 3
  0b0011001,  // 4
  0b0010010,  // 5
  0b0000010,  // 6
  0b1111000,  // 7
  0b0000000,  // 8
  0b0010000   // 9
};

const uint8_t lookup_table1[7] = {
  0b1111110,  // a
  0b1111101,  // b
  0b1111011,  // c
  0b1110111,  // d
  0b1101111,  // e
  0b1011111,  // f
  0b1111111
};

int estadoButton = 0;
const int button = 9;

// Función para mostrar un número en el display de 7 segmentos
void displayNumber(int number, int select) {
  if (number < 0 || number > 9) {
    return; // Solo mostrar números del 0 al 9
  }
  uint8_t segments;
  if (select == 1) {
    segments = lookup_table1[number]; // Obtener los segmentos del número de la LUT
  } else {
    segments = lookup_table[number]; // Obtener los segmentos del número de la LUT
  }
  // Activar o desactivar los segmentos
  for (int i = 0; i < 7; i++) {
    int bitValue = (segments >> i) & 0x01; // Obtener el valor del bit correspondiente al segmento
    digitalWrite(segmentPins[i], bitValue); // Encender o apagar el segmento
  }
}

void setup() {
  pinMode(button, INPUT);
  // Configurar los pines de los segmentos como salidas
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  displayNumber(6,1);
  randomSeed(analogRead(A0));
}

void loop() {
  if(digitalRead(button) == HIGH) {
    if (estadoButton==0){
      estadoButton=1;
      // Mostrar los números del 0 al 9 en el display de 7 segmentos
      for (int i = 0; i <  3; i++) {
        for (int j= 0; j < 6; j++) {
          displayNumber(j,1);
          delay(50); 
        }
      }
      randNumber = random(1,7);
      displayNumber(randNumber,0);
    }
  } else {
    estadoButton=0;
  }
}
