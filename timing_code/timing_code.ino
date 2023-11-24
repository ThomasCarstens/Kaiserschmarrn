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


int next_deposit_time = -1;
int baking_time_seconds = 60; // testing
    
int deposit_short_move_ms = 300;
int deposit_cnt = 3;
int long_belt_ms = 800;   


int l1 = 45;
int l2 = 65;

int r1 = 90;
int r2 = 110;



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
  Serial.begin(115200);

   // We need to attach the servo to the used pin number 
   Servo1.attach(BatterServoPin); 
   pinMode(BUTTON, INPUT);
   pinMode(PumpPin, OUTPUT);
   pinMode(ConveyorPin, OUTPUT);
   pinMode(ShredderPin, OUTPUT);
   pinMode(StoragePin, OUTPUT);

   next_deposit_time = millis();


}


void move(int a, int b, int sleep=600)
{
  int step = 3;
  int cnt = abs(a-b)/step;
  
  if (a>b){ step *= -1;}

  for (int i=0; i<cnt; ++i)
  {
    int pos = a+i*step;
    // Serial.println(pos);
    Servo1.write(pos);
    delay(sleep);
  }

}

void pump_on(){digitalWrite(PumpPin, LOW);}
void pump_off(){digitalWrite(PumpPin, HIGH);}


void move_conveyor_ms(int duration)
{
  digitalWrite(ConveyorPin, LOW);
  delay(duration);
  digitalWrite(ConveyorPin, HIGH);
}

void deposit(int a1, int a2, int b1, int b2, int delay_ms)
{
  Servo1.write(a1);
  delay(50);

  pump_on();
  move(a1, a2);
  pump_off();

  delay(500);

  move(a2, b1, 400);

  pump_on();
  move(b1, b2);
  pump_off();

  move_conveyor_ms(delay_ms);
}


void loop(){ 

    // //initialize at zero
    digitalWrite(ConveyorPin, HIGH); // Stop Conveyor Motor
    digitalWrite(PumpPin, HIGH); // Stop Pump Motor
    digitalWrite(ShredderPin, HIGH); // Stop Pump Motor
    digitalWrite(StoragePin, HIGH); // Stop Pump Motor
    Servo1.write(90); 

    // Serial1.write(90);
    // return;

    int wait_time = (next_deposit_time-millis());
    Serial.print("Wait time:  ");
    Serial.println(wait_time/1000);

    bool start_baking = false;
    if (wait_time < 0)
    {
      Serial.println("starting process");
      next_deposit_time = millis() + baking_time_seconds*1000; 
    }else{
      delay(1000);
      return;
    }


    
    for (int i=0; i<deposit_cnt; ++i)
    {
      Serial.print("deposit cnt");
      Serial.println(i);
      deposit(l1, l2, r1, r2, deposit_short_move_ms);
      deposit(r2,r1, l2, l1, deposit_short_move_ms);
    }


    Serial.println("deposited, moving into oven");
    move_conveyor_ms(long_belt_ms);




   // SERVO CODE
  //  int min_angle = 70;
  //  int max_angle = 180-min_angle;
  //  int sleep_time = 100;

  //  int angle_point1 = min_angle+10;
  //  int angle_point2 = max_angle-10;
   
  //  const int time_moving_into_oven = 1000;
  //  const int cooking_time = 5000;
  //  const int time_moving_out_of_oven = 5000;

  // //initialize at zero
  // digitalWrite(ConveyorPin, HIGH); // Stop Conveyor Motor
  // digitalWrite(PumpPin, HIGH); // Stop Pump Motor
  // digitalWrite(ShredderPin, HIGH); // Stop Pump Motor
  // digitalWrite(StoragePin, HIGH); // Stop Pump Motor
  // Servo1.write(min_angle); 


  // // Safety: 5s pause on start
  // delay(5000);  


  // //  BATTER TIMING CODE

  // // First batter output

  // digitalWrite(PumpPin, LOW); // Start Pump Motor
  // for (int i=min_angle ; i<angle_point1 ; i++){
  //   Servo1.write(i); 
  //   delay(sleep_time); 
  // };
  // digitalWrite(PumpPin, HIGH); // Stop Pump Motor

  // // Pump Off. Move to start of second batter output
  // for (int i=angle_point1 ; i<angle_point2 ; i++){
  //   Servo1.write(i); 
  //   delay(10); 
  // };

  // // Second batter output

  // digitalWrite(PumpPin, LOW); // Start Pump Motor
  // for (int i=angle_point2 ; i<max_angle ; i++){
  //   Servo1.write(i); 
  //   delay(sleep_time); 
  // };
  // digitalWrite(PumpPin, HIGH); // Stop Pump Motor


  // // Pump Off. Move conveyor motor
  
  // digitalWrite(ConveyorPin, LOW); // Start Conveyor Motor
  // delay(time_moving_into_oven);  
  // digitalWrite(ConveyorPin, HIGH); // Stop Conveyor Motor


  // // Conveyor off and cooking.
  // delay(cooking_time);  
  

  // // Finished cooking. Move conveyor motor to shredder
  // digitalWrite(ConveyorPin, LOW); // Start Conveyor Motor
  // delay(time_moving_out_of_oven);  
  // digitalWrite(ConveyorPin, HIGH); // Stop Conveyor Motor



  // // At shredder. Close shredder
  // digitalWrite(ShredderPin, LOW); // Start Shredder Motor
  // delay(1000);  
  // digitalWrite(ShredderPin, HIGH); // Stop Shredder Motor
  // delay(500);  
  // digitalWrite(ShredderPin, LOW); // Stop Shredder Motor
  // delay(500);  
  // digitalWrite(ShredderPin, HIGH); // Stop Shredder Motor


  // // in storage. Run Storage Motor
  // digitalWrite(StoragePin, LOW); // Start Shredder Motor
  // delay(1000);  
  // digitalWrite(StoragePin, HIGH); // Stop Shredder Motor
  

  // At end. Bring batter servo motor to starting position
  // for (int i=max_angle ; i>min_angle ; i--){
  //   Servo1.write(i); 
  //   delay(sleep_time); 
  // }   



}