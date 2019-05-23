int a;
void setup()
{
    Serial.begin(115200);    
    pinMode(2,OUTPUT);
    pinMode(13,INPUT);
}

void loop()
{
    a=digitalRead(13);
    if(a==HIGH)
    {
        Serial.println("person detected");
        digitalWrite(2,HIGH);
        //delay(100);
    }
    else
    {
        Serial.println("person not detected");
        digitalWrite(2,LOW);
       // delay(100);
    }

}
