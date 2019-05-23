const int ledPin=16;
const int freq=5000;
const int ledChannel=0;
const int resolution=8;
void setup() {
  
  ledcSetup(ledChannel,freq,resolution);
  ledcAttachPin(ledPin,ledChannel);

}

void loop() {
 //increase led brightness
  for(int dutyCycle=0;dutyCycle<=255;dutyCycle++)
  {
    ledWrite(ledChannel,dutyCycle);
    delay(15);
  }
  //decrease led brightness
  for(int dutyCycle=255;dutyCycle>=0;dutyCycle--)
  {
    ledWrite(ledChannel,dutycycle);
    delay(15);
  }

}
