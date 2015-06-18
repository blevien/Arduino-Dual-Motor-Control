/*
 Read pulse length from Spektrum 2.4 Ghz Reciever for dual motor control, and spin 2 motors
 L293D Code Adapted from
 https://www.safaribooksonline.com/library/view/beginning-arduino/9781430232407/project_16_using_an_l293d_motor_driver_ic.html
*/

#define steeringInput 8
#define throttleInput 9

unsigned long steerDuration;
unsigned long throttleDuration;

#define motorPin3 11 // L293D Input 1
#define motorPin4 12// L293D Input 2
#define throttleOutput 10 //L293D Speed Pin

#define motorPin1 6 // L293D Input 1
#define motorPin2 7// L293D Input 2
#define steeringOutput 5 //L293D Speed Pin

int speed = 0;
int direction = 0;


void setup()
{

  pinMode(steeringInput, INPUT);
  pinMode(throttleInput, INPUT);

  pinMode(throttleOutput, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  pinMode(steeringOutput, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  Serial.begin(9600);

}

void setMotor(int output, int pin1, int pin2, int Mspeed) {

  if (Mspeed < 20 && Mspeed > -20){
    analogWrite(output, 0); // write speed to Enable 1 pin
  }
  else {
    analogWrite(output, abs(Mspeed)); // write speed to Enable 1 pin
  }
   
  if (Mspeed > 20) { // Rotate motor clockwise
    digitalWrite(pin1, LOW); // set Input 1 of the L293D low
    digitalWrite(pin2, HIGH); // set Input 2 of the L293D high
    Serial.println(String(output) + "||" + String(abs(Mspeed)));
  }
  
  else if (Mspeed < -20) {  // Rotate motor anti-clockwise
    digitalWrite(pin1, HIGH); // set Input 1 of the L293D low
    digitalWrite(pin2, LOW); // set Input 2 of the L293D high
    Serial.println(String(output) + "||" + String(abs(Mspeed)));
  }

  
}



void loop() {

  steerDuration = pulseIn(steeringInput, HIGH);
  throttleDuration = pulseIn(throttleInput, HIGH);

  direction = constrain(map(steerDuration, 1100, 1900, -255, 255), -255, 255);
  speed = constrain(map(throttleDuration, 1100, 1900, -255, 255), -255, 255);

  setMotor(steeringOutput, motorPin1, motorPin2, direction);
  setMotor(throttleOutput, motorPin3, motorPin4, speed);

}

