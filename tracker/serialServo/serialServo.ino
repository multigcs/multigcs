
#include <Servo.h> 
 
Servo myservo1;
Servo myservo2;
int pos1 = 0;
int pos2 = 0;
 
void setup() { 
  myservo1.attach(8);
  myservo2.attach(9);
  Serial.begin(38400);
} 
 
void loop() { 
  int i = 0;
  char commandbuffer[100];
  if (Serial.available()){
     delay(10);
     while( Serial.available() && i< 99) {
        commandbuffer[i++] = Serial.read();
     }
     commandbuffer[i++]='\0';
  }
  if(i>0) {
     sscanf(commandbuffer, "%i %i", &pos1, &pos2);
  }
  myservo1.write(pos1 * -1 + 90);
  myservo2.write(pos2 * -1 + 90);
}


