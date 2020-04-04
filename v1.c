//Arduino project. Robots with two wheels, which is self-managed.
//Robot is using ultrasonic to detect where to go and how to overcome barriers.
//Also robot could be managed by bluetooth


//set managing by bluetooth by default
int bluetooth = 1;

//move forward slow
void forwardSlow() {
  analogWrite(5, 155);
  analogWrite(6, 155);
  analogWrite(3, 0);
  analogWrite(11, 0);

  forwardSlowSound();
}

//move forward fast
void forwardFast() {
  analogWrite(5, 255);
  analogWrite(6, 255);
  analogWrite(3, 0);
  analogWrite(11, 0);

  forwardFastSound();
}

void backSlow() {
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(3, 155);
  analogWrite(11, 155);

  backSlowSound();
}

void backFast() {
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(3, 255);
  analogWrite(11, 255);

  backFastSound();
}

void rightForwardFast() {
  analogWrite(5, 255);
  analogWrite(6, 0);
  analogWrite(3, 0);
  analogWrite(11, 0);

  changeDirection();
}

void leftForwardFast() {
  analogWrite(5, 0);
  analogWrite(6, 255);
  analogWrite(3, 0);
  analogWrite(11, 0);

  changeDirection();
}

void rightBackFast() {
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(3, 255);
  analogWrite(11, 0);

  changeDirection();
}

void leftBackFast() {
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(3, 0);
  analogWrite(11, 255);

  changeDirection();
}

void stopDrives() {
  analogWrite(3, 0);
  analogWrite(5, 0);
  analogWrite(11, 0);
  analogWrite(6, 0);
}


void soundStart() {
    tone(9, 1000, 500);
    delay(1000);
    noTone(9);

    tone(9, 1000, 500);
    delay(1000);
    noTone(9);

    tone(9, 1000, 500);
    delay(1000);
    noTone(9);
}

void forwardFastSound() {
    tone(9, 500, 500);
    delay(1000);
    noTone(9);
}

void forwardSlowSound() {
    tone(9, 200, 500);
    delay(2000);
    noTone(9);
}

void backFastSound() {
    tone(9, 1800, 500);
    delay(1000);
    noTone(9);
}

void backSlowSound() {
    tone(9, 1500, 500);
    delay(2000);
    noTone(9);
}

void changeDirection() {
    tone(9, 2000, 500);
    delay(1000);
    noTone(9);
}

double calcDistance() {
  double duration, distance;
  digitalWrite(13, LOW);
  delayMicroseconds(2);
  digitalWrite(13, HIGH);
  delayMicroseconds(10);
  digitalWrite(13, LOW);
  duration = pulseIn(12, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);

  return distance;
}

void initMoveSettins() {
  pinMode(9, OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(6, OUTPUT);
}

void initDistanceSettings() {
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  Serial.begin(9600);
}

int random(int min, int max) {
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void setup() {
  initMoveSettins();
  initDistanceSettings();
  soundStart();
  delay(1000);
}

void loop() {
  int data;

  if (Serial.available() > 0) {

    data = Serial.read();
    Serial.println(data);

    if (data == 56) {
      stopDrives();
      bluetooth = 1;
    }

    if (data == 57) {
      bluetooth = 0;
    }

    if (bluetooth == 1) {
      if (data == 50) {
        forwardFast();
        delay(200);
        stopDrives();
      }

      if (data == 51) {
        rightForwardFast();
        delay(50);
        stopDrives();
      }

      if (data == 52) {
        backFast();
        delay(200);
        stopDrives();
      }

      if (data == 49) {
        leftForwardFast();
        delay(50);
        stopDrives();
      }
    }
  }

  if (bluetooth == 0) {
      double distance;
      distance = calcDistance();

      if (distance < 10) {
        int randNumber = random(1, 6);
        if (randNumber > 3) {
          leftBackFast();
        } else {
          rightBackFast();
        }

        delay(200);
      }

      if (distance > 10) {
        int randNumber = random(1, 6);
          if (randNumber != 1 && randNumber != 6) {
            forwardFast();
            delay(1000);
          } else {
            if (randNumber == 1) {
              rightForwardFast();
            } else {
              leftForwardFast();
            }

            delay(500);
          }
      }
  }
}