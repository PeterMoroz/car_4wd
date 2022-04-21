#include <Servo.h>

Servo servo;

#define SERVO_PIN 11

//Motor one
#define IN1 2
#define IN2 3

//Motor two
#define IN3 4
#define IN4 5


//Ultrasonic Sensor
#define TRIGGER_PIN 6
#define ECHO_PIN 7


void setup() {
  // servo
  servo.attach(SERVO_PIN);
  // motor one
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  // motor two
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // ultrasonic sensor
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIGGER_PIN, LOW);  
  
  Serial.begin(9600);

  delay(2000);
  // to center the ultrasensor's poisition
  servo.write(105);
}

void loop() {
  unsigned long distance = getDistanceCentimeters();

  char text[32];
  sprintf(text, "distance (cm) = %ld", distance);
  Serial.println(text);
  
  if (distance <= 20) {
    stop();

    if (distance <= 10) {
      moveBackward();
      delay(1000);
      stop();
    }
    
    delay(200);
    unsigned long leftDistance = lookLeft();
    unsigned long rightDistance = lookRight();

    sprintf(text, "left distance (cm) = %ld", leftDistance);
    Serial.println(text);
    sprintf(text, "right distance (cm) = %ld", rightDistance);
    Serial.println(text);

    if (leftDistance <= 10 && rightDistance <= 10) {
      moveBackward();
      delay(1000);
      stop();
    } else {
      if (leftDistance > rightDistance) {
        Serial.println("turn left");
        turnLeft();
        delay(900);
        stop();
      } else if (rightDistance > leftDistance) {
        Serial.println("turn right");
        turnRight();
        delay(800);
        stop();
      } else {
        moveBackward();
        delay(1000);
        stop();
      }      
    }
  } else {
    moveForward();
  }

/////////////////////////////////////////////////////
//  Serial.println("move forward");
//  moveForward();
//  delay(1000);
//  Serial.println("stop");
//  stop();
//  delay(1000);
//
//  Serial.println("turn left");
//  turnLeft();
//  delay(900);
//  Serial.println("stop");  
//  stop();
//  delay(1000);
//
//  Serial.println("move backward");
//  moveBackward();
//  delay(1000);
//  Serial.println("stop");
//  stop();
//  delay(1000);
//
//  Serial.println("turn right");
//  turnRight();
//  delay(800);
//  Serial.println("stop");
//  stop();
//  delay(1000);  


///////////////////////////////////////
//  char text[32];
//  unsigned long distance = getDistanceCentimeters();
//  sprintf(text, "distance (cm) = %ld", distance);
//  Serial.println(text);
//
//  if (distance <= 20) {
//    delay(200);
//    unsigned long leftDistance = lookLeft();
//    delay(200);
//    unsigned long rightDistance = lookRight();
//
//    sprintf(text, "distance left (cm) = %ld", leftDistance);
//    Serial.println(text);
//    sprintf(text, "distance right (cm) = %ld", rightDistance);
//    Serial.println(text);
//  }
//  delay(2000);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);  
}

void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

unsigned long lookLeft() {
  servo.write(105);
  delay(500);
  servo.write(185); //  servo.write(175);
  delay(1000);
  unsigned long distance = getDistanceCentimeters();
  servo.write(105);
  return distance;  
}

unsigned long lookRight() {
  servo.write(105);
  delay(500);
  servo.write(25); //  servo.write(5);
  delay(1000);
  unsigned long distance = getDistanceCentimeters();
  servo.write(105);
  return distance;
}

unsigned long getDistanceCentimeters() {
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  unsigned long duration_us = pulseInLong(ECHO_PIN, HIGH); // unsigned long duration_us = pulseIn(ECHO_PIN, HIGH);
  unsigned long distance_cm = (17 * duration_us) / 1000; // 0.017 * duration_us;
  return distance_cm;

//  unsigned long avg = 0;
//  for (int i = 0; i < 10; i++) {
//    digitalWrite(TRIGGER_PIN, HIGH);
//    delayMicroseconds(10);
//    digitalWrite(TRIGGER_PIN, LOW);
//    avg += pulseInLong(ECHO_PIN, HIGH);
//  }
//  unsigned long duration_us = avg / 10;
//  unsigned long distance_cm = (17 * duration_us) / 1000; // 0.017 * duration_us;
//  return distance_cm;
}
