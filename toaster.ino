// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int lastThree[] = {0, 0, 0};
int n = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
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

  if(summed >= 1000){
    play();
    lastThree[0] = 0;
    lastThree[1] = 0;
    lastThree[2] = 0;
  }
}

void play() {
  
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, 400, noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

