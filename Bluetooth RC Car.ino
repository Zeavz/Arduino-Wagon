#include <SoftwareSerial.h>  
#include <Servo.h> 
#define RxD 6
#define TxD 7
 
#define DEBUG_ENABLED  1
 
SoftwareSerial blueToothSerial(RxD,TxD);

const int motor1rPin = 10;   
const int motor2rPin = 7;    
const int enablerPin = 9;    
int servoPin = 3;
const int motor1lPin = 5;   
const int motor2lPin = 2;    
const int enablelPin = 11; 
const int frontled = 12 ; 
const int backled = 8 ;
int sspeed = 204;
int mangle = 90;
int angle = 15;
Servo servo; 
const int ledpin = 13;
 
void setup() {
  Serial.begin(9600);
    pinMode(motor1rPin, OUTPUT);
    pinMode(motor2rPin, OUTPUT);
    pinMode(enablerPin, OUTPUT);
    pinMode(motor1lPin, OUTPUT);
    pinMode(motor2lPin, OUTPUT);
    pinMode(enablelPin, OUTPUT);
    pinMode(ledpin, OUTPUT);
    pinMode(servoPin, OUTPUT);
    pinMode(frontled, OUTPUT);
    pinMode(backled, OUTPUT);  
    servo.attach(servoPin); 



 setupBlueToothConnection();
} 

void loop() 
{ 
  char recvChar;
    if(blueToothSerial.available()){
     digitalWrite(enablerPin, HIGH);
    digitalWrite(enablelPin, HIGH);
      recvChar = blueToothSerial.read();
      //fast
     if(recvChar == 'b'){
      digitalWrite(motor1rPin, LOW);   
      digitalWrite(motor2rPin, HIGH);  
      analogWrite(enablerPin, sspeed);  
      digitalWrite(motor1lPin, LOW);   
      digitalWrite(motor2lPin, HIGH);  
      analogWrite(enablelPin, sspeed);  
     }
     //reverse
     else if(recvChar == 's'){
      digitalWrite(motor1rPin, HIGH);  
      digitalWrite(motor2rPin, LOW);   
      analogWrite(enablerPin, sspeed);  
      digitalWrite(motor1lPin, HIGH);  
      digitalWrite(motor2lPin, LOW);   
      analogWrite(enablelPin, sspeed); 
     } 
      //left
     else if(recvChar == 'r'){
      digitalWrite(motor1rPin, HIGH);  
      digitalWrite(motor2rPin, LOW);   
      analogWrite(enablerPin, sspeed);  
      digitalWrite(motor1lPin, HIGH);  
      digitalWrite(motor2lPin, LOW);   
      analogWrite(enablelPin, 0);  
     }
                //upleft
     else if(recvChar == 'a'){
      digitalWrite(motor1rPin, LOW);  
      digitalWrite(motor2rPin, HIGH);   
      analogWrite(enablerPin, sspeed);  
      digitalWrite(motor1lPin, LOW);  
      digitalWrite(motor2lPin, HIGH);   
      analogWrite(enablelPin, sspeed/2);  
     }
                //downleft
     else if(recvChar == 'q'){
      digitalWrite(motor1rPin, HIGH);  
      digitalWrite(motor2rPin, LOW);   
      analogWrite(enablerPin, sspeed);  
      digitalWrite(motor1lPin, HIGH);  
      digitalWrite(motor2lPin, LOW);   
      analogWrite(enablelPin, sspeed/2);  
     }
      //right
     else if(recvChar == 'l'){
      digitalWrite(motor1rPin, HIGH);  
      digitalWrite(motor2rPin, LOW);   
      analogWrite(enablerPin, 0);  
      digitalWrite(motor1lPin, HIGH);  
      digitalWrite(motor2lPin, LOW);   
      analogWrite(enablelPin, sspeed);  
     }
      //upright
     else if(recvChar == 'e'){
      digitalWrite(motor1rPin, LOW);  
      digitalWrite(motor2rPin, HIGH);   
      analogWrite(enablerPin, sspeed/2);  
      digitalWrite(motor1lPin, LOW);  
      digitalWrite(motor2lPin, HIGH);   
      analogWrite(enablelPin, sspeed);  
     }
      //downright
     else if(recvChar == 'w'){
      digitalWrite(motor1rPin, HIGH);  
      digitalWrite(motor2rPin, LOW);   
      analogWrite(enablerPin, sspeed/2);  
      digitalWrite(motor1lPin, HIGH);  
      digitalWrite(motor2lPin, LOW);   
      analogWrite(enablelPin, sspeed);  
     }
     else if(recvChar == '+'){
       if(sspeed<205){
         sspeed = sspeed+51;
       }
     }
     else if(recvChar == '-'){
       if(sspeed>50){
         sspeed = sspeed-51;
       }
     }
     else if(recvChar == 'n'){
       if(mangle>14){
         mangle = mangle - angle;
      servo.write(mangle); 
       }
     }
     else if(recvChar == 'm'){
       if(mangle<165){
         mangle = mangle + angle;
      servo.write(mangle); 
       }
     }
     else if(recvChar == 'o'){
       digitalWrite(ledpin,HIGH);
       delay(100);
       digitalWrite(ledpin,LOW);
     }
//     else if(recvChar == 'p')

  //  }     
     
     else{
    digitalWrite(motor1rPin, LOW) ;
    digitalWrite(motor2rPin, LOW) ;
    digitalWrite(motor1lPin, LOW) ;
     digitalWrite(motor2lPin, LOW) ;
     }
    }
  }
  void setupBlueToothConnection()
{
  blueToothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  blueToothSerial.print("\r\n+STNA=SeeedBTSlave\r\n"); //set the bluetooth name as "SeeedBTSlave"
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  blueToothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
  Serial.println("The slave bluetooth is inquirable!");
  delay(2000); // This delay is required.
  blueToothSerial.flush();
}
  
