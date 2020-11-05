/* 

Inconvenient Interface
By Mairead Stewart
For DIGF 6037 - Creation & Computation
November 6, 2020

Sine wave code based on code from https://processing.org/reference/libraries/sound/Sound_volume_.html
Receiving Arduino code from Creation & Computation example file: https://github.com/DigitalFuturesOCADU/CC2020
*/

import processing.serial.*;
Serial myPort;  

import processing.sound.*;
Sound mySound;  

float pitch;
float roll;

Circle[] circles = new Circle[1];

void setup() { 
  
  printArray(Serial.list());
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
  
  size(1200, 700);

    for (int i = 0; i < 1; i++) {
    circles[i] = new Circle();
  }
  
  SinOsc sin = new SinOsc(this);
  sin.play(240, 0.2);
  
  sin = new SinOsc(this);
  sin.play(220, 0.2);
  
  mySound = new Sound(this);
}

void draw() {
  fill(0, 40);
  rect(0, 0, width, height); 
  
  if (pitch >= 3) {
      stroke(255,0,0);
  } else {
    stroke(0,0,0);
  }

  for (int i = 0; i < 1; i++) {
    circles[i].move(map(pitch,0,240,500,850), map(roll,0,240,450,200));
    circles[i].display();

  }

float amp = map(pitch, 0, 15, 0, 1);
 mySound.volume(amp);

}
class Circle { 
  float xpos = 600;
  float ypos = 450;

  void move(float newX, float newY) { 
    xpos=newX; 
    ypos=newY;
  }

  void display() {
    noFill(); 
    strokeWeight(0.1);
    pushMatrix();
    float a = (float)360/width*xpos;
    float b = (float)360/height*ypos;
    translate(xpos, ypos);


    for (int X = 0; X < 360; X++) { 
      float x = cos(radians(X)) * a;
      float y = sin(radians(X)) * b;

      pushMatrix();
      translate(x, y);
      rotate(radians(X-frameCount));
      rect(0, 0, 200, 200);
      popMatrix();
      
      pushMatrix(); 
      translate(x, y);
      rotate(radians(X-frameCount));
      rect(0, 0, 200, 200); 
      popMatrix();
      
      pushMatrix();
      translate(x, y);
      rotate(radians(X-frameCount));
      rect(0, 0, 200, 200);
      popMatrix(); 
    }
    popMatrix();
}
} 

void serialEvent(Serial myPort) {

  String myString = myPort.readStringUntil('\n');
  if (myString != null) {

    myString = trim(myString);

    float sensors[] = float(split(myString, ','));
    
    pitch = sensors[0];
    roll = sensors[1];
  } 
  }
