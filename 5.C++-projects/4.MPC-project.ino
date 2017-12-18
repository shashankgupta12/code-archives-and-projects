#include<string.h>
char state[10];
int k=0,moving=0,fwd,back,duration, distance,s=-1;
void setup()
{
  pinMode(3,OUTPUT);  //right motor
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);  //left motor
  pinMode(11,OUTPUT);
  pinMode(12,INPUT);  //ultrasonic sensor
  pinMode(8,OUTPUT);
  Serial.begin(9600);
}
void loop()
{ 
  digitalWrite(8,LOW);
  delayMicroseconds(2);
  digitalWrite(8,HIGH);
  delayMicroseconds(20);
  digitalWrite(8,LOW);
  duration=pulseIn(12,HIGH);
  distance=duration/58;  
  if(distance<=20&&distance>=0&&s==0)
  {
    //stop=1;
    digitalWrite(3,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    delay(2000);
    analogWrite(3,100);
    analogWrite(10,0);
    analogWrite(9,0);
    analogWrite(11,0);
    delay(3000);
    digitalWrite(3,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);          
  }
  else
  {
    if((Serial.available()>0)&&(k<4))
    {
      state[k]=Serial.read();
      k=k+1;
    }
    if(k==4)
    {
      if(strcmp(state,"STRT")==0) //for moving ahead command is 'STRT'
      {
        s=0;
        moving=1;
        fwd=1;
        back=0;
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        for(int i=0;i<=255;i++)
        {
          analogWrite(3,i);
          analogWrite(9,i);
        }
        digitalWrite(3,HIGH);
        digitalWrite(9,HIGH);
        Serial.println("Moving forward");
        k=0;
        loop();
      }
      else if(strcmp(state,"STOP")==0)    //for stopping the vehicle
      {
        s=1;
        if(moving==1)    //checking the condition whether the vehicle is moving or not
        {
          moving=0;
          if(fwd==1)    //moving forward
          {
            for(int i=244;i>=0;i=i--)
            {
              analogWrite(3,i);
              analogWrite(9,i);
            }
            digitalWrite(10,LOW);
            digitalWrite(11,LOW);
          }
          else if(back==1)    //moving backwards
          {
            for(int i=244;i>=0;i=i--)
            {
              analogWrite(10,i);
              analogWrite(11,i);
            }
            digitalWrite(3,LOW);
            digitalWrite(9,LOW);
          }
          Serial.println("Stopping vehicle");
        }
        k=0;
        loop();
      }
      else if(strcmp(state,"BACK")==0)    //for reverse
      {
        s=0;
        moving=1;
        fwd=0;
        back=1;
        digitalWrite(3,LOW);
        digitalWrite(10,HIGH);
        digitalWrite(9,LOW);
        digitalWrite(11,HIGH);
        k=0;
        loop();
      }
      else if((strcmp(state,"LEFT")==0))        //for left turn 
      {
        s=0;
        analogWrite(3,100);
        analogWrite(10,0);
        analogWrite(9,0);
        analogWrite(11,0);
        k=0;
        loop();
      }
      else if(strcmp(state,"RIHT")==0)    //for right turn 
      {
        s=0;
        analogWrite(3,0);
        analogWrite(10,0);
        analogWrite(9,100);
        analogWrite(11,0);
        k=0;
        loop();
      }
    }
  } 
}  
