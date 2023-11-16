// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 

// Create a servo object 
Servo Servo1; 
const int BUTTON = 6; // the button is connected to pin 5 of the Adruino board
const int PumpPin = 1; // the relay Nb 1 is connected to pin 1 of the Adruino board / Relay 1
const int ConveyorPin = 2; // the relay Nb 2 is connected to pin 2 of the Adruino board / Relay 2
const int ShredderPin = 3; // the relay Nb 3 is connected to pin 3 of the Adruino board / Relay 3

const int BatterServoPin = 4; // directly connected to 5V (with circuit breaker switch also powering off the arduino)
const int StoragePin = 5; // the relay Nb 5 is connected to pin 5 of the Adruino board / Relay 5


int Button_State;
  // EXTRA CODE
  // // increasing from min_angle
  // for (int i=min_angle ; i<max_angle ; i++){
  //   Servo1.write(i); 
  //   delay(sleep_time); 
  //   current_angle = i;
  // };

  // // decreasing from max_angle
  // for (int i=max_angle ; i>min_angle ; i--){
  // Servo1.write(i); 
  // delay(sleep_time); 
  // current_angle = i;
  // }   
  // Button_State = digitalRead(BUTTON); 

void setup() { 

   // We need to attach the servo to the used pin number 
   Servo1.attach(BatterServoPin); 
   pinMode(BUTTON, INPUT);
   pinMode(PumpPin, OUTPUT);
   pinMode(ConveyorPin, OUTPUT);
   pinMode(ShredderPin, OUTPUT);
   pinMode(StoragePin, OUTPUT);



}

void loop(){ 
   // SERVO CODE
   int min_angle = 70;
   int max_angle = 180-min_angle;
   int sleep_time = 100;

   int angle_point1 = min_angle+10;
   int angle_point2 = max_angle-10;
   
   const int time_moving_into_oven = 1000;
   const int cooking_time = 5000;
   const int time_moving_out_of_oven = 5000;

  //initialize at zero
  digitalWrite(ConveyorPin, HIGH); // Stop Conveyor Motor
  digitalWrite(PumpPin, HIGH); // Stop Pump Motor
  digitalWrite(ShredderPin, HIGH); // Stop Pump Motor
  digitalWrite(StoragePin, HIGH); // Stop Pump Motor
  Servo1.write(min_angle); 


  // Safety: 5s pause on start
  delay(5000);  


  //  BATTER TIMING CODE

  // First batter output

  digitalWrite(PumpPin, LOW); // Start Pump Motor
  for (int i=min_angle ; i<angle_point1 ; i++){
    Servo1.write(i); 
    delay(sleep_time); 
  };
  digitalWrite(PumpPin, HIGH); // Stop Pump Motor

  // Pump Off. Move to start of second batter output
  for (int i=angle_point1 ; i<angle_point2 ; i++){
    Servo1.write(i); 
    delay(10); 
  };

  // Second batter output

  digitalWrite(PumpPin, LOW); // Start Pump Motor
  for (int i=angle_point2 ; i<max_angle ; i++){
    Servo1.write(i); 
    delay(sleep_time); 
  };
  digitalWrite(PumpPin, HIGH); // Stop Pump Motor


  // Pump Off. Move conveyor motor
  
  digitalWrite(ConveyorPin, LOW); // Start Conveyor Motor
  delay(time_moving_into_oven);  
  digitalWrite(ConveyorPin, HIGH); // Stop Conveyor Motor


  // Conveyor off and cooking.
  delay(cooking_time);  
  

  // Finished cooking. Move conveyor motor to shredder
  digitalWrite(ConveyorPin, LOW); // Start Conveyor Motor
  delay(time_moving_out_of_oven);  
  digitalWrite(ConveyorPin, HIGH); // Stop Conveyor Motor



  // At shredder. Close shredder
  digitalWrite(ShredderPin, LOW); // Start Shredder Motor
  delay(1000);  
  digitalWrite(ShredderPin, HIGH); // Stop Shredder Motor
  delay(500);  
  digitalWrite(ShredderPin, LOW); // Stop Shredder Motor
  delay(500);  
  digitalWrite(ShredderPin, HIGH); // Stop Shredder Motor


  // in storage. Run Storage Motor
  digitalWrite(StoragePin, LOW); // Start Shredder Motor
  delay(1000);  
  digitalWrite(StoragePin, HIGH); // Stop Shredder Motor
  

  // At end. Bring batter servo motor to starting position
  for (int i=max_angle ; i>min_angle ; i--){
    Servo1.write(i); 
    delay(sleep_time); 
  }   



}