#include <Servo.h> 
#include <Wire.h>
#include <LIDARLite.h>




 
int servoPin = 5;
int arr1[40];
int arr2[40];
int arr3[40];
int dist;
int cal_cnt = 0;
int angle = 0;   // servo position in degrees 

LIDARLite lidarLite;
Servo servo;  
 


 
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

get_data(1,40);   // (direction,till angle)
get_data(-1,40);   // (direction,till angle)
//Print_to_serial(arr1,40);
//Print_to_serial(arr2,40);
take_diff(40);

} 


void Print_to_serial(int TheArr[], int n)
{
  Serial.print("{");
for(int i = 0; i < n; i++)
{
  Serial.print(TheArr[i]);
  if(i<(n-1)){
  Serial.print(",");}
}
  Serial.print("} ");
  Serial.println("");
  }


void get_data(int d, int p)
{
  if(d==1){
    
  for(angle = 0; angle < p; angle++)  
  {                
 
  cal_cnt++;
  cal_cnt = cal_cnt % 100;                  
    servo.write(angle); 
     if ( cal_cnt == 0 ) {
    dist = lidarLite.distance();      // With bias correction
  } else {
    dist = lidarLite.distance(false); // Without bias correction
  }
  arr1[angle] = dist;
    
  //Serial.println(dist);            
    delay(10);                    
  } 
}
  if(d==-1){
    
  for(angle = p; angle > 0; angle--)    
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
  //Serial.println(dist);

  arr2[angle-1] = dist;
            
    delay(10);       
  } 
}


}

void take_diff(int p)
{
for(int n =  0; n < p; n++)  
  {    
    arr3[n] = arr2[n]-arr1[n] ;           
  }
  
Print_to_serial(arr3, 40);
  
}






