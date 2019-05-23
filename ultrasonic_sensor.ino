const int trigPin=4;
const int echoPin=5;
long duration;
int distance;
//int a;
void setup()
{
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    pinMode(14,OUTPUT);
    pinMode(15,OUTPUT);
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);
    Serial.begin(115200);

}

void loop()
{
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigPin,LOW);
    duration=pulseIn(echoPin,HIGH);
    distance=duration*0.034/2;
    Serial.print("Distance:");
    Serial.println(distance);
    if(distance>300)
    {
      digitalWrite(12,HIGH);
      delay(100);
    }
    else
    {
      digitalWrite(12,LOW);
      delay(100);
    }
    if(distance<300&&distance>=200)
    {
      digitalWrite(13,HIGH);
      delay(100);
    }
     else
    {
      digitalWrite(13,LOW);
      delay(100);
    }
    if(distance<200&&distance>=100)
    {
      digitalWrite(14,HIGH);
      delay(100);
    }
     else
    {
      digitalWrite(14,LOW);
      delay(100);
    }
   if(distance<100)
    {
      digitalWrite(15,HIGH);
      delay(100);
    }
     else
    {
      digitalWrite(15,LOW);
      delay(100);
    }
   
}
