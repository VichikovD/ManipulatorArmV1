 #include <Servo.h>
Servo servoLeg, bend1, bend2, bend3, graber;
long grabLong = 0;
const int pinX = A7;
const int pinY = A6;
const int pinJButton = 2;
int servoLegPosition, bend1Position, bend2Position, bend3Position, graberPosition;

const int MAX_X_ROTATE_SPEED = 10;  // Меняя эту константу, можно менять максимальную скорость поворота по оси Х
const int MAX_Y_ROTATE_SPEED = 10 / 3;  // Меняя эту константу, можно менять максимальную скорость поворота по оси У
const int DELAY = 10;

void setup () {
  Serial.begin(9600);
  servoLeg.attach(3);
  servoLeg.write(90);
  bend1.attach(4);
  bend1.write(90);
  bend2.attach(5);
  bend2.write(90);
  bend3.attach(6);
  bend3.write(90);
  graber.attach(7);
  graber.write(30);
  pinMode(pinJButton, INPUT_PULLUP);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);

  // bend1.write(60);
  // bend2.write(120);
  // bend3.write(150);
}

void loop() {
  int yValueBitCorrected = map(analogRead(pinY), 0, 1022, 1023, 0);
  int xValueBitCorrected = map(analogRead(pinX), 0, 1022, 1023, 0);

  int xValue = map(xValueBitCorrected, 0, 1022, 0, 180);
  int yValue = map(yValueBitCorrected, 0, 1023, 0, 180);

  int servoLegPosition = servoLeg.read();
  int bend1Position = bend1.read();
  int bend2Position = bend2.read();
  int bend3Position = bend3.read();
  int graberPosition = graber.read();

  Serial.println(xValue);
  // delay(100);
  Serial.println(yValue);
  delay(100);

  manipulateXAxis(servoLegPosition, xValue);

  manipulateYAxis(bend1Position, bend2Position, bend3Position, yValue);

  if(!digitalRead(pinJButton)) {
    grabLong += 1;
    if(grabLong % 2 == 0) {
      graber.write(21);
    } else {
      graber.write(150);
    }
    while(!digitalRead(pinJButton)) {
    }
  }
}

void manipulateYAxis(int bend1Position, int bend2Position, int bend3Position, int yValue) {
  if(yValue > 92 | yValue < 88) {
    int stepY = map(yValue, 0, 180, MAX_Y_ROTATE_SPEED * (-1), MAX_Y_ROTATE_SPEED);
    turnServo(bend1, bend1Position, stepY);
    delay(DELAY);
    turnServo(bend2, bend2Position, stepY);
    delay(DELAY);
    turnServo(bend3, bend3Position, stepY);
    delay(DELAY);
  } 
}

void manipulateXAxis(int servoLegPosition, int xValue) {
  if(xValue > 90 | xValue < 86) {
    int stepX = map(xValue, 0, 180, MAX_X_ROTATE_SPEED * (-1), MAX_X_ROTATE_SPEED);
    turnServo(servoLeg, servoLegPosition, stepX);
  } 
}

void turn3ServoSequentially(Servo servo1, Servo servo2, Servo servo3) {

}

void turnServo(Servo servo, int initialPosition, int step) {
  int resultPosition = initialPosition + step;
  Serial.println(step);
  servo.write(resultPosition);
}