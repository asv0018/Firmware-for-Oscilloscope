#include<SoftwareSerial.h>
SoftwareSerial android(2,3); // Rx , Tx //
void ReadNewData(byte*ADC1,byte*ADC2);
// These are the data parameters
#define MAX_LEVEL 240
#define MAX_SAMPLES 640
#define DATA_START (MAX_LEVEL + 1)
#define DATA_END (MAX_LEVEL + 2)

// These are the amplitude macros
#define kSCALE  6.2
#define SCALE_10mV    (long)(kSCALE / 0.01)
#define SCALE_20mV    (long)(kSCALE / 0.02)
#define SCALE_50mV    (long)(kSCALE / 0.05)
#define SCALE_100mV   (long)(kSCALE / 0.1)
#define SCALE_200mV   (long)(kSCALE / 0.2)
#define SCALE_500mV   (long)(kSCALE / 0.5)
#define SCALE_1V    (long)(kSCALE / 1.0)
#define SCALE_2V    (long)(kSCALE / 2.0)
#define SCALE_GND   (long)(0)

// These are the timebase macros
#define FCY        16000000  // 16 MIPS
#define SAMPLES_PER_DIV 32

#define PERIOD_5us    (unsigned int)(FCY * 5E-6 / SAMPLES_PER_DIV ) // 6
#define PERIOD_10us   (unsigned int)(FCY * 10E-6 / SAMPLES_PER_DIV )  // 12
#define PERIOD_20us   (unsigned int)(FCY * 20E-6 / SAMPLES_PER_DIV )
#define PERIOD_50us   (unsigned int)(FCY * 50E-6 / SAMPLES_PER_DIV )
#define PERIOD_100us  (unsigned int)(FCY * 100E-6 / SAMPLES_PER_DIV )
#define PERIOD_200us  (unsigned int)(FCY * 200E-6 / SAMPLES_PER_DIV )
#define PERIOD_500us  (unsigned int)(FCY * 500E-6 / SAMPLES_PER_DIV )
#define PERIOD_1ms    (unsigned int)(FCY * 1E-3 / SAMPLES_PER_DIV )
#define PERIOD_2ms    (unsigned int)(FCY * 2E-3 / SAMPLES_PER_DIV )
#define PERIOD_5ms    (unsigned int)(FCY * 5E-3 / SAMPLES_PER_DIV )
#define PERIOD_10ms   (unsigned int)(FCY * 10E-3 / SAMPLES_PER_DIV )  // 12500
#define PERIOD_20ms   (unsigned int)(FCY * 20E-3 / SAMPLES_PER_DIV )
#define PERIOD_50ms   (unsigned int)(FCY * 50E-3 / SAMPLES_PER_DIV )  // 62500


// This is the array of amplitude based on amplitude index
unsigned int amplitude[] = {
  SCALE_10mV,
  SCALE_20mV,
  SCALE_50mV,
  SCALE_100mV,
  SCALE_200mV,
  SCALE_500mV,
  SCALE_1V,
  SCALE_2V,
  SCALE_GND
  };

// this is the array of timebase based on timebase index
unsigned int timebase[] = {
  PERIOD_5us,
  PERIOD_10us,
  PERIOD_20us,
  PERIOD_50us,
  PERIOD_100us,
  PERIOD_200us,
  PERIOD_500us,
  PERIOD_1ms,
  PERIOD_2ms,
  PERIOD_5ms,
  PERIOD_10ms,
  PERIOD_20ms,
  PERIOD_50ms
  };

// These are the oscilloscope parameters
byte REQ_DATA = 0x00,ADJ_HORIZONTAL = 0x01,ADJ_VERTICAL = 0x02,ADJ_POSITION = 0x03,TIMEBASE_INDEX = 1;

// These are the channels
byte CHANNEL_1 = 0x01,CHANNEL_2 = 0x02;

// These are the two channels with the struct
struct CHANNEL {
  byte timebase_index = TIMEBASE_INDEX;
  byte amplitude_index;
  byte amplitude;
  byte timebase;
  byte position;
  byte data[MAX_SAMPLES/2];
}ch1,ch2;

void setup() {
  Serial.begin(9600);
  android.begin(9600);
  int t[4] = {1,22,3,55};
//  android.write((int*)t,4);
}

void loop() {
  int response[20];
  int size = LenOfDataFromAndroid(response);// get the size of the array but it also reads data from android
  Settings(response,size);// based on the size of the array, necessory updates to the parameters will be made
}
