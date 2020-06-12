#include<SoftwareSerial.h>
SoftwareSerial android(2,3);

// These are the data parameters
#define MAX_LEVEL 240
#define MAX_SAMPLES 640
#define DATA_START (MAX_LEVEL + 1)
#define DATA_END (MAX_LEVEL + 2)

// This  is the array of amplitude based on amplitude index
byte const amplitude[] = {};

//this is the array of timebase based on timebase index
byte const timebase[] = {};

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
}

void loop() {
  int response[20];
  int size = LenOfDataFromAndroid(response);// get the size of the array but it also reads data from android
  Settings(response,size);// based on the size of the array, necessory updates to the parameters will be made
  
}
