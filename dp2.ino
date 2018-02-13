#include <Servo.h> 
 
int servoPin = 5;



#include <Wire.h>
#include <LIDARLite.h>
int cal_cnt = 0;


LIDARLite lidarLite;

Servo servo;  
 
int angle = 0;   // servo position in degrees 
 
void setup() 
{ 
  Serial.begin(9600);
  servo.attach(servoPin); 
//  tix = 0;c
lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
lidarLite.configure(0); // Change this number to try out alternate configurations
} 
 
 
void loop() 
{ 



  int dist;

  // At the beginning of every 100 readings,
  // take a measurement with receiver bias correction
 





  //delay(10);
  //tix = millis;
  // scan from 0 to 180 degrees
  for(angle = 0; angle < 40; angle++)  
  {                
      // Increment reading counter
  cal_cnt++;
  cal_cnt = cal_cnt % 100;                  
    servo.write(angle); 
     if ( cal_cnt == 0 ) {
    dist = lidarLite.distance();      // With bias correction
  } else {
    dist = lidarLite.distance(false); // Without bias correction
  }
    
  Serial.println(dist);
                
    delay(10);                   
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 40; angle > 0; angle--)    
  {        
      // Increment reading counter
  cal_cnt++;
  cal_cnt = cal_cnt % 100;                        
    servo.write(angle); 
     if ( cal_cnt == 0 ) {
    dist = lidarLite.distance();      // With bias correction
  } else {
    dist = lidarLite.distance(false); // Without bias correction
  }
  Serial.println(dist);
            
    delay(10);       
  } 
} 
