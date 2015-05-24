/*
 Read pulse length from Spektrum 2.4 Ghz Reciever for dual motor control, and spin 2 motors
*/

#define steeringInput 8
#define throttleInput 9

unsigned long steerDuration;
unsigned long throttleDuration;

#define motorPin1 10 // L293D Input 1
#define motorPin2 11// L293D Input 2
#define throttleOutput 12 //L293D Speed Pin

#define motorPin3 6 // L293D Input 1
#define motorPin4 7// L293D Input 2
#define steeringOutput 5 //L293D Speed Pin

int speed = 0;
int direction = 0;


void setup()
{
  
  Serial.begin(9600);
  pinMode(steeringInput, INPUT);
  pinMode(throttleInput, INPUT);
  
  pinMode(throttleOutput, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  
  pinMode(steeringOutput, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

}

void setMotor(int output, int pin1, int pin2, int Mspeed){

  analogWrite(output, abs(Mspeed)); // write speed to Enable 1 pin
  
  if (Mspeed > 0) { // Rotate motor clockwise
    digitalWrite(pin1, LOW); // set Input 1 of the L293D low
    digitalWrite(pin2, HIGH); // set Input 2 of the L293D high
  }
  else {  // Rotate motor anti-clockwise
    digitalWrite(pin1, HIGH); // set Input 1 of the L293D low
    digitalWrite(pin2, LOW); // set Input 2 of the L293D high
  }
  
}

void loop(){
  
 steerDuration = pulseIn(steeringInput, HIGH);
 throttleDuration = pulseIn(throttleInput, HIGH);
 
 Serial.println(String(speed) + "||" + String(direction));
 
 direction = constrain(map(steerDuration, 1100, 1900, -255, 255), -255, 255);
 speed = constrain(map(throttleDuration, 1100, 1900, -255, 255), -255, 255); 
 
 setMotor(steeringOutput, motorPin3, motorPin4, direction);
 setMotor(throttleOutput, motorPin1, motorPin2, speed);

}

