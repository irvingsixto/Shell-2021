#include <Arduino.h>
#include <ESP32_ExtInterrupt.h>

#define A 0
#define B 1
#define C 2

int HA = 25;
int HB = 32;
int HC = 33;
int LA = 26;
int LB = 27;
int LC = 14;

int ENCA = 19;
int ENCB = 5;
int ENCC = 18;
int _ENCA = 19;
int _ENCB =  5;
int _ENCC = 18;

int pot = 22;
int lec = 0;

ExternalInterrupt encA;
ExternalInterrupt encB;
ExternalInterrupt encC;

bool sens_a;
bool sens_b;
bool sens_c;

const int freq = 2000;
const int res = 10; // 0 - 1023
const int CHANAH = 0;
const int CHANBH = 0;
const int CHANCH = 0;
const int CHANAL = 0;
const int CHANBL = 0;
const int CHANCL = 0;

char direction = 'FORWARD';

void setup() {
  encA.begin(_ENCA, CHANGE, 100);
  encB.begin(_ENCB, CHANGE, 100);
  encC.begin(_ENCC, CHANGE, 100);

  ledcSetup(CHANAH, freq, res);
  ledcSetup(CHANBH, freq, res);
  ledcSetup(CHANCH, freq, res);
  ledcSetup(CHANAL, freq, res);
  ledcSetup(CHANBL, freq, res);
  ledcSetup(CHANCL, freq, res);
  
  ledcAttachPin(HA, CHANAH);
  ledcAttachPin(HB, CHANBH);
  ledcAttachPin(HC, CHANCH);
  ledcAttachPin(LA, CHANAL);
  ledcAttachPin(LB, CHANBL);
  ledcAttachPin(LC, CHANCL);

  Serial.begin(115200);
}

void loop() {
  lec = analogRead(pot);
  
  sens_a = digitalRead(_ENCA);
  sens_b = digitalRead(_ENCB);
  sens_c = digitalRead(_ENCC);

  int sensor_a = encA.getState();
  int sensor_b = encB.getState();
  int sensor_c = encC.getState();

  char step = ' ';
  uint8_t sensor_sequence = 0;
  bitWrite(sensor_sequence, 2, sensor_a);
  bitWrite(sensor_sequence, 1, sensor_b);
  bitWrite(sensor_sequence, 0, sensor_c);

  switch (sensor_sequence)
  {
    case 1:
      if (direction == 'FORWARD')
        step = 'CB';
      else
        step = 'BC';
      break;

    case 2:
      if (direction == 'FORWARD')
        step = 'BA';
      else
        step = 'AB';
      break;

    case 3:
      if (direction == 'FORWARD')
        step = 'CA';
      else
        step = 'AC';
      break;

    case 4:
      if (direction == 'FORWARD')
        step = 'AC';
      else
        step = 'CA';
      break;

    case 5:
      if (direction == 'FORWARD')
        step = 'AB';
      else
        step = 'BA';
      break;

    case 6:
      if (direction == 'FORWARD')
        step = 'BC';
      else
        step = 'CB';
      break;

    default:
      // No coil active, could be a sensor's hardware failure. Check individual coil signals.
      break;

      switch (step)
      {
        case 'BC':
          
          break;

        case 'AC':
          
          break;

        case 'AB':
          
          break;

        case 'CB':
          
          break;

        case 'CA':
          
          break;

        case 'BA':
          
          break;

        default:
          break;
      }

  }
}