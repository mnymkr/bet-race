#include <SoftwareSerial.h>
#include <HCSR04.h>
//#include <Wire.h>
//#include <AFMotor.h>
//SoftwareSerial Bluetooth(0, 1); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)

//**********5 Channel IR Sensor Connection**********//
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4

//*************Variables for Line Following***************//
int s1;  //Left Most Sensor
int s2;  //Left Sensor
int s3;  //Middle Sensor
int s4;  //Right Sensor
int s5;  //Right Most Sensor

//***********Distances for moving to avoid obstacle****************//
int horizontal = 10;
int vertical = 10;

//***********Sonar*************//
#define TRIG_PIN 52  //attach pin D3 Arduino to pin Trig of HC-SR04 (TBD)
#define ECHO_PIN 53  //attach pin D3 Arduino to pin Trig of HC-SR04 (TBD)

#define TRIG_PIN_LEFT 50  //attach pin D3 Arduino to pin Trig of HC-SR04 (TBD)
#define ECHO_PIN_LEFT 51  //attach pin D3 Arduino to pin Trig of HC-SR04 (TBD)

#define TRIG_PIN_RIGHT 48  //attach pin D3 Arduino to pin Trig of HC-SR04 (TBD)
#define ECHO_PIN_RIGHT 49  //attach pin D3 Arduino to pin Trig of HC-SR04 (TBD)

//*************Sonar*****************//
HCSR04 hcsr04(TRIG_PIN, ECHO_PIN);
HCSR04 hcsr04_left(TRIG_PIN_LEFT, ECHO_PIN_LEFT);
HCSR04 hcsr04_right(TRIG_PIN_RIGHT, ECHO_PIN_RIGHT);

//*************Variables for Sonar*****************//
int sonar_center;
int sonar_left;
int sonar_right;
#define NEAR 15
#define FAR 30
int obstacle = 0;

//**********Front wheels***********//
#define IN11 32  // 0
#define IN12 33  // 0
#define IN13 12  // 1
#define IN14 13  // 1
#define ENA1 9   // 0
#define ENB1 11  // 1

//***********Back wheels*************//
#define IN21 5   //3
#define IN22 4   //3
#define IN23 6   //2
#define IN24 7   //2
#define ENA2 8   //3
#define ENB2 10  //2

#define C 18.85  // circumference of wheel
#define P 20     // pulses per revolution

//*******encoder pins and variables**********//
int encoder0 = 2;
int encoder1 = 3;
int pulseCount0 = 0;
int pulseCount1 = 0;

//*********variables for rpm calculation*******//
unsigned long thoigian;
unsigned long hientai;
int rpm;


void pulseUp0() {
  pulseCount0++;  // interrupt encoder 0
}
void pulseUp1() {
  pulseCount1++;  // interrupt encoder 1
}

//DIRECTIONS
void moveForward() {
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, HIGH);
  digitalWrite(IN14, LOW);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN23, LOW);
  digitalWrite(IN24, HIGH);
  digitalWrite(IN21, HIGH);
  digitalWrite(IN22, LOW);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
void moveBackward() {
  digitalWrite(IN11, LOW);
  digitalWrite(IN12, HIGH);
  digitalWrite(IN13, HIGH);
  digitalWrite(IN14, LOW);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN21, HIGH);
  digitalWrite(IN22, LOW);
  digitalWrite(IN23, HIGH);
  digitalWrite(IN24, LOW);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
void moveSidewaysRight() {
  digitalWrite(IN11, LOW);
  digitalWrite(IN12, HIGH);
  digitalWrite(IN13, HIGH);
  digitalWrite(IN14, LOW);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN23, LOW);
  digitalWrite(IN24, HIGH);
  digitalWrite(IN21, LOW);
  digitalWrite(IN22, HIGH);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
void moveSidewaysLeft() {
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, LOW);
  digitalWrite(IN14, HIGH);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN23, HIGH);
  digitalWrite(IN24, LOW);
  digitalWrite(IN21, HIGH);
  digitalWrite(IN22, LOW);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
void rotateLeft() {
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, LOW);
  digitalWrite(IN14, HIGH);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN23, LOW);
  digitalWrite(IN24, HIGH);
  digitalWrite(IN21, LOW);
  digitalWrite(IN22, HIGH);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
void rotateRight() {
  digitalWrite(IN11, LOW);
  digitalWrite(IN12, HIGH);
  digitalWrite(IN13, HIGH);
  digitalWrite(IN14, LOW);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN23, HIGH);
  digitalWrite(IN24, LOW);
  digitalWrite(IN21, HIGH);
  digitalWrite(IN22, LOW);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
void moveRightForward() {
  digitalWrite(IN11, LOW);
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, HIGH);
  digitalWrite(IN14, LOW);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN23, LOW);
  digitalWrite(IN24, HIGH);
  digitalWrite(IN21, LOW);
  digitalWrite(IN22, LOW);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
void moveRightBackward() {
  digitalWrite(IN11, LOW);
  digitalWrite(IN12, HIGH);
  digitalWrite(IN13, LOW);
  digitalWrite(IN14, LOW);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN23, LOW);
  digitalWrite(IN24, LOW);
  digitalWrite(IN21, LOW);
  digitalWrite(IN22, HIGH);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
void moveLeftForward() {
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, LOW);
  digitalWrite(IN14, LOW);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN23, LOW);
  digitalWrite(IN24, LOW);
  digitalWrite(IN21, HIGH);
  digitalWrite(IN22, LOW);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
void moveLeftBackward() {
  digitalWrite(IN11, LOW);
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, LOW);
  digitalWrite(IN14, HIGH);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN23, HIGH);
  digitalWrite(IN24, LOW);
  digitalWrite(IN21, LOW);
  digitalWrite(IN22, LOW);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
void turnLeft() {
  // wheel 1 rotates backwards
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, LOW);
  digitalWrite(IN14, LOW);

  digitalWrite(IN21, HIGH);
  digitalWrite(IN22, LOW);
  digitalWrite(IN23, LOW);
  digitalWrite(IN24, HIGH);
}
void turnRight() {
  digitalWrite(IN11, LOW);
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, HIGH);
  digitalWrite(IN14, LOW);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN23, LOW);
  digitalWrite(IN24, HIGH);
  digitalWrite(IN21, HIGH);
  digitalWrite(IN22, LOW);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
void turnLeftFrontCenterICC() {
  digitalWrite(IN11, LOW);
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, LOW);
  digitalWrite(IN14, LOW);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN23, LOW);
  digitalWrite(IN24, HIGH);
  digitalWrite(IN21, LOW);
  digitalWrite(IN22, HIGH);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
void stopMoving() {
  digitalWrite(IN11, LOW);
  digitalWrite(IN12, LOW);
  digitalWrite(IN13, LOW);
  digitalWrite(IN14, LOW);
  // analogWrite(ENA1, wheelSpeed);
  // analogWrite(ENB1, wheelSpeed);
  digitalWrite(IN21, LOW);
  digitalWrite(IN22, LOW);
  digitalWrite(IN23, LOW);
  digitalWrite(IN24, LOW);
  // analogWrite(ENA2, wheelSpeed);
  // analogWrite(ENB2, wheelSpeed);
}
//**needs refinement
void changeSpeed(int wheelSpeed) {
  analogWrite(ENA1, wheelSpeed - 10); // compensate for misdirection
  analogWrite(ENB1, wheelSpeed);
  analogWrite(ENA2, wheelSpeed);
  analogWrite(ENB2, wheelSpeed);
}
void calculateRPM(int time) {

  thoigian = millis();

  if (thoigian - hientai >= 1000) {
    hientai = thoigian;
    rpm = (((pulseCount0 + pulseCount1) / 2) / 20) * 60;
    /*
         * Đĩa encoder có 20 xung, chúng ta đo được 120 xung/s
         * vậy lấy 120/20 = 6 vòng/s
         * ta được: 6*60 = số vòng quay / phút (RPM)
         */
    Serial.print("\t\t\t\t");
    Serial.print("Số xung/s: ");
    Serial.println((pulseCount0 + pulseCount1) / 2);
    pulseCount0 = 0;
    pulseCount1 = 0;
    Serial.print("\t\t\t\t");
    Serial.print("RPM: ");
    Serial.println(rpm);
  }
}
void followLine(int s1, int s2, int s3, int s4, int s5) {
  //if only middle sensor detects white line

  // state = 0
  // only 3 sensors in the middle
  if ((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0)) {
    //going forward with full speed
    changeSpeed(255);
    moveForward();
  }

  // state = 1
  if ((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 0)) {
    //going forward with full speed
    turnRight();
  }

  // state = 2
  if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1)) {
    //going slightly left
    turnRight();
  }

  //state = 3
  if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 1)) {
    //going slightly left
    rotateRight();
  }

  // state = -1
  if ((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0)) {
    //going left with full speed
    turnLeft();
  }

  // // state = -2
  if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0)) {
    //going left with full speed
    turnLeft();
  }

  // state = -3
  if ((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0)) {
    //going left with full speed
    rotateLeft();
  }
  // nothing
  if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0)) {
    //stop
    stopMoving();
  }

  // full white
  if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1)) {
    changeSpeed(128);
    moveForDistance(215, "leftForward");
    delay(100);
    moveForDistance(35, "turnLeftFrontCenterICC");
    delay(100);
    moveForDistance(150, "forward");
  }
}
void ultrasonic() {
  //Reading Sensor Values
  s1 = digitalRead(ir1);  //Left Most Sensor
  s2 = digitalRead(ir2);  //Left Sensor
  s3 = digitalRead(ir3);  //Middle Sensor
  s4 = digitalRead(ir4);  //Right Sensor
  s5 = digitalRead(ir5);  //Right Most Sensor

  int sonar_center = hcsr04.dist();
  Serial.println(sonar_center);

  int sonar_left = hcsr04_left.dist();

  int sonar_right = hcsr04_right.dist();

  if (sonar_center < 20) {           // O detected
    if (sonar_left < sonar_right) {  // O on left
      if (sonar_left < 15) {

        while (sonar_left < 15) {
          moveSidewaysRight();
          sonar_left = hcsr04_left.dist();
        }

      } else {

        // if (sonar_left > 18) {
        //   moveSidewaysLeft();
        //   sonar_left = hcsr04_left.dist();
        // }

        if (sonar_left < 18) {
          moveForDistance(50, "forward");
        } else {

          if (!(s1 == s2 == s3 == s4 == s5 == 1))
            while (!(s1 == s2 == s3 == s4 == s5 == 1)) {
              followLine(s1, s2, s3, s4, s5);
            }

          else {
            moveSidewaysLeft();
            if (!(s1 == s2 == s3 == s4 == s5 == 1))
              while (!(s1 == s2 == s3 == s4 == s5 == 1)) {
                followLine(s1, s2, s3, s4, s5);
              }
          }
        }
      }
    }
    //else {
    //   if (sonar_right < 15)
    //     while (sonar_right < 15) {
    //       moveSidewaysLeft();
    //       sonar_right = hcsr04_right.dist();
    //     }
    //   else {
    //     if (sonar_right < 15)
    //       while (sonar_right < 15) {
    //         moveForDistance(50, "forward");
    //       }
    //     else {
    //       if (!(s1 = s2 = s3 = s4 = s5 = 1))
    //         while (!(s1 = s2 = s3 = s4 = s5 = 1)) {
    //           followLine(s1, s2, s3, s4, s5);
    //         }
    //       else {
    //         moveSidewaysRight();
    //       }
    //     }
    //   }
    // }
  } else {
    followLine(s1, s2, s3, s4, s5);
  }
}
void moveForDistance(int distance, String direct) {
  pulseCount0 = 0;
  pulseCount1 = 0;
  int pulses = distance / C * P;

  if (direct == "moveForward") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        moveForward();
        delay(50);
        Serial.println();
    }
    stopMoving();
  } else if (direct == "moveBackward") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        moveBackward();
        delay(50);
        Serial.println();
    }
    stopMoving();
  } else if (direct == "moveSidewaysRight") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        moveSidewaysRight();
        delay(50);
        Serial.println();
    }
    stopMoving();
  } else if (direct == "moveSidewaysLeft") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        moveSidewaysLeft();
        delay(50);
        Serial.println();
      }
    stopMoving();
  } else if (direct == "rotateLeft") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        rotateLeft();
        delay(50);
        Serial.println();
      }
    stopMoving();
  } else if (direct == "rotateRight") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        rotateRight();
        delay(50);
        Serial.println();
      }
    stopMoving();
  } else if (direct == "moveRightForward") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        moveRightForward();
        delay(50);
        Serial.println();
      }
    stopMoving();
  } else if (direct == "moveRightBackward") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        moveRightBackward();
        delay(50);
        Serial.println();
      }
    stopMoving();
  } else if (direct == "moveLeftForward") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        moveLeftForward();
        delay(50);
        Serial.println();
      }
    stopMoving();
  } else if (direct == "moveLeftBackward") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        moveLeftBackward();
        delay(50);
        Serial.println();
      }
    stopMoving();
  } else if (direct == "turnLeft") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        turnLeft();
        delay(50);
        Serial.println();
      }
    stopMoving();
  } else if (direct == "turnRight") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        turnRight();
        delay(50);
        Serial.println();
      }
    stopMoving();
  } else if (direct == "turnLeftFrontCenterICC") {
    while (((pulseCount0 + pulseCount1) / 2) < pulses) {  // if average pulse of 2 encoder is < 20
        turnLeftFrontCenterICC();
        delay(50);
        Serial.println();
      }
    stopMoving();
  } else {
    Serial.println("No/Wrong direction provided!");
    stopMoving();
  }
}

void avoidRight() {
  if (sonar_left < NEAR) {  // too close to Obstacle
    moveForDistance(horizontal, "moveSidewaysRight");

    if (sonar_center > FAR) { // free to move forward
      obstacle = 0;
    }
    // check for line

  } else if (sonar_left > FAR) {  // too FAR from Obstacle
    moveForDistance(horizontal, "moveSidewaysLeft");

    if (sonar_center > FAR) {
      obstacle = 0;
    }
    // check for line

  } else {  // Obstacle within range
    if (sonar_center > FAR) {
      moveForDistance(vertical, "moveForward");
    }
  }
}

void avoidLeft() {
  if (sonar_right < NEAR) {  // too close to Obstacle
    moveForDistance(horizontal, "moveSidewaysLeft");

    if (sonar_center > FAR) { // free to move forward
      obstacle = 0;
    }
    // check for line

  } else if (sonar_right > FAR) {  // too FAR from Obstacle
    moveForDistance(horizontal, "moveSidewaysRight");

    if (sonar_center > FAR) { // free to move forward
      obstacle = 0;
    }
    // check for line

  } else {  // Obstacle within range
    if (sonar_center > FAR) {
      moveForDistance(vertical, "moveForward");
    }
  }
}

void setup() {
  Serial.begin(9600);

  // Set up bluetooth
  //Bluetooth.begin(9600);
  //Bluetooth.begin(9600);
  //Bluetooth.setTimeout(1);

  // ultrasonic
  // pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  // pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  // Set up Encoder
  pinMode(encoder0, INPUT);
  pinMode(encoder1, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder0), pulseUp0, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder1), pulseUp1, RISING);

  // Wheel 0 and 1 pins
  pinMode(IN11, OUTPUT);
  pinMode(IN12, OUTPUT);
  pinMode(IN13, OUTPUT);
  pinMode(IN14, OUTPUT);
  pinMode(ENA1, OUTPUT);
  pinMode(ENB1, OUTPUT);

  // Wheel 2 and 3 pins
  pinMode(IN21, OUTPUT);
  pinMode(IN22, OUTPUT);
  pinMode(IN23, OUTPUT);
  pinMode(IN24, OUTPUT);
  pinMode(ENA2, OUTPUT);
  pinMode(ENB2, OUTPUT);

  // Line follower sensors
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);

  changeSpeed(130);
}

void loop() {

  // calculateRPM(1000); // print pulse count and speed every 1 second
  delay(50);
  //Reading Sensor Values
  sonar_center = hcsr04.dist();
  sonar_left = hcsr04_left.dist();
  sonar_right = hcsr04_right.dist();

  Serial.println(sonar_left);
  Serial.println(sonar_center);
  Serial.println(sonar_right);
  Serial.println();

  if (sonar_center < 25) {
    // detected Obstacle
    obstacle = 1;

    while (obstacle == 1) {  // while still in Avoiding Mode

      delay(50);
      sonar_center = hcsr04.dist();
      sonar_left = hcsr04_left.dist();
      sonar_right = hcsr04_right.dist();

      // Serial.println(sonar_center);
      // Serial.println(sonar_left);
      // Serial.println(sonar_right);
      // Serial.println();

      if (sonar_left < sonar_right) {  // obstacle on left => move right
        Serial.println("Moving right");
        avoidRight();

      } else {                    // obstacle on right => move left + check right
        Serial.println("Moving left");
        avoidLeft();
      }
    }

  } else { // no obstacle
    // check for line

    moveForward();
  }

  // // check for line
    // s1 = digitalRead(ir1);  //Left Most Sensor
    // s2 = digitalRead(ir2);  //Left Sensor
    // s3 = digitalRead(ir3);  //Middle Sensor
    // s4 = digitalRead(ir4);  //Right Sensor
    // s5 = digitalRead(ir5);  //Right Most Sensor

    // if (s1 || s2 || s3 || s4 || s5) {  // if line found then exit Avoiding Mode, change code logic if needed
    //   obstacle = 0;
    //   break;
    // }  // else, keep avoiding Obstacle
}