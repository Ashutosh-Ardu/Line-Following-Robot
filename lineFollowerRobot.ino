#define IR_SENSOR_RIGHT 11
#define IR_SENSOR_LEFT 12
#define MOTOR_SPEED 255
//Right motor
int enableRightMotor=10;
int rightMotorPin1=4;
int rightMotorPin2=5;

//Left motor
int enableLeftMotor=9;
int leftMotorPin1=2;
int leftMotorPin2=3;

void setup()
{
  TCCR0B = TCCR0B & B11111000 | B00000010 ;
  
  // put your setup code here, to run once:
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0,0);   
  Serial.begin(9600);
}


void loop()
{
//READING THE SENSOR VALUES
  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);
//PRINTING THEM IN SERIAL MONITOR
  Serial.print("left:");Serial.print(leftIRSensorValue);Serial.print("|right:");Serial.println(rightIRSensorValue);
  //If none of the sensors detects black line, then go straight
  if (rightIRSensorValue == 0 && leftIRSensorValue == 0) {
//    MOVE FORWARD
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  //If right sensor detects black line, then turn right
  else if (rightIRSensorValue == 1 && leftIRSensorValue == 0 ){
//    TURN RIGHT
//    ROTATEMOTOR(RIGHT,LEFT);
      rotateMotor(-MOTOR_SPEED, MOTOR_SPEED); 
  }
  //If left sensor detects black line, then turn left  
  else if (rightIRSensorValue == 0 && leftIRSensorValue == 1 ){
//    TURN LEFT
//    ROTATEMOTOR(RIGHT,LEFT);
      rotateMotor(MOTOR_SPEED, -MOTOR_SPEED); 
  } 
  //If both the sensors detect black line, then stop 
  else {
//    STOP
    rotateMotor(0, 0);
  }
}


void rotateMotor(int rightMotorSpeed, int leftMotorSpeed){
//  ROTOR FACING RIGHT
  if (rightMotorSpeed < 0){//    ANTI-CLOCKWISE
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0){//    CLOCKWISE
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else{//    STOP
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }
// ROTOR FACING LEFT
  if (leftMotorSpeed < 0){//    ANTICLOCKWISE
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);    
  }
  else if (leftMotorSpeed > 0){//    CLOCKWISE
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);      
  }
  else {//    STOP
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));//  LOADING THE SPEED
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}
