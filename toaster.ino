#include <TMRpcm.h>
#include <pcmRF.h>
#include <pcmConfig.h>
#include <SD.h>

/*
 
 This example shows how to read and write data to and from an SD card file   
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10
 ** speaker - pin 9
 ** switch - A0 in
 ** 
 ** TOASTER
 * RED - 5V
 * GREEN - A0
 * GREEN WITH RESISTER - Ground Calibration
 */

TMRpcm tmrpcm;
File myFile;

int lastThree[] = {0, 0, 0};
int n = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);


  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(10, OUTPUT);
   
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("ta.wav");
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Audio file found...");
      tmrpcm.speakerPin = 9; 
    myFile.close();
    Serial.println("Audio file closed.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening audio file");
  }
  int lastThree[] = {0, 0, 0};
  n = 0;
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read: 
  n ++;

  lastThree[n%3] = sensorValue;

  int summed = lastThree[0] + lastThree[1] + lastThree[2];
  Serial.println(summed);

  if(summed >= 500) { 
    if(!tmrpcm.isPlaying()) {
      play();
      lastThree[0] = 0;
      lastThree[1] = 0;
      lastThree[2] = 0;
    }
  }
  if(!tmrpcm.isPlaying()) {
    digitalWrite(9, 0);      
  }
}

void play(){
    Serial.println("Beginning playback");
    tmrpcm.play("ta.wav");
    Serial.println("Playback complete");
}
