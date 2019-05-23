#include<time.h>                              
#include<WiFi.h>                              

#define       MILLISECONDS_STEP_HOLD  1                                   
#define       MOTOR_PHASE_A           32                                  
#define       MOTOR_PHASE_B           14                                  
#define       MOTOR_PHASE_C           33                                  
#define       MOTOR_PHASE_D           15                                  
#define       STEPS_PER_REVOLUTION    4096                                

int             nDelay = 100;                     
long            nSeconds =  0;                        
long            nSecondsIndicated =   0;                        
struct timeval  tvTimeValue;                                              
void setup() 
{
  // Serial.
  
  Serial.begin(115200);
  while(!Serial){};

  // Set motor drive pins as outputs.
    
    pinMode(MOTOR_PHASE_A, OUTPUT);
    pinMode(MOTOR_PHASE_B, OUTPUT);
    pinMode(MOTOR_PHASE_C, OUTPUT);
    pinMode(MOTOR_PHASE_D, OUTPUT);
   // Set esp32 rtc to 00:00:00.
 
  memset(& tvTimeValue, 0, sizeof(tvTimeValue));
  settimeofday(& tvTimeValue, NULL);
}

void loop() 
{
  // Update nSeconds from the ESP32 rtc.
  
  gettimeofday(& tvTimeValue, NULL);
  
  struct tm * tmPointer = localtime(& tvTimeValue.tv_sec);
  nSeconds = tmPointer->tm_sec;
  
  // Update the stepper position.
  
  Update();
  
 delay(nDelay);
}

void  MotorOff()
{
  digitalWrite(MOTOR_PHASE_A, LOW);
  digitalWrite(MOTOR_PHASE_B, LOW);
  digitalWrite(MOTOR_PHASE_C, LOW);
  digitalWrite(MOTOR_PHASE_D, LOW);
}

void  Step(int nDirection)
{
  // Local variables.
  
  static  int nPhase = 0;

  // Update phase.
  
  nPhase = ((nDirection < 0) ? (nPhase - 1) : (nPhase + 1)) & 7;

  // Step this phase.
  
  switch(nPhase)
  {
    case 0:
    {
      digitalWrite(MOTOR_PHASE_D, HIGH);
      digitalWrite(MOTOR_PHASE_C, LOW);
      digitalWrite(MOTOR_PHASE_B, LOW);
      digitalWrite(MOTOR_PHASE_A, LOW);
    }
    break;

    case 1:
    {
      digitalWrite(MOTOR_PHASE_D, HIGH);
      digitalWrite(MOTOR_PHASE_C, HIGH);
      digitalWrite(MOTOR_PHASE_B, LOW);
      digitalWrite(MOTOR_PHASE_A, LOW);
    }
    break;

    case 2:
    {
      digitalWrite(MOTOR_PHASE_D, LOW);
      digitalWrite(MOTOR_PHASE_C, HIGH);
      digitalWrite(MOTOR_PHASE_B, LOW);
      digitalWrite(MOTOR_PHASE_A, LOW);
    }
    break;

    case 3:
    {
      digitalWrite(MOTOR_PHASE_D, LOW);
      digitalWrite(MOTOR_PHASE_C, HIGH);
      digitalWrite(MOTOR_PHASE_B, HIGH);
      digitalWrite(MOTOR_PHASE_A, LOW);
    }
    break;

    case 4:
    {
      digitalWrite(MOTOR_PHASE_D, LOW);
      digitalWrite(MOTOR_PHASE_C, LOW);
      digitalWrite(MOTOR_PHASE_B, HIGH);
      digitalWrite(MOTOR_PHASE_A, LOW);
    }
    break;

    case 5:
    {
      digitalWrite(MOTOR_PHASE_D, LOW);
      digitalWrite(MOTOR_PHASE_C, LOW);
      digitalWrite(MOTOR_PHASE_B, HIGH);
      digitalWrite(MOTOR_PHASE_A, HIGH);
    }
    break;

    case 6:
    {
      digitalWrite(MOTOR_PHASE_D, LOW);
      digitalWrite(MOTOR_PHASE_C, LOW);
      digitalWrite(MOTOR_PHASE_B, LOW);
      digitalWrite(MOTOR_PHASE_A, HIGH);
    }
    break;

    case 7:
    {
      digitalWrite(MOTOR_PHASE_D, HIGH);
      digitalWrite(MOTOR_PHASE_C, LOW);
      digitalWrite(MOTOR_PHASE_B, LOW);
      digitalWrite(MOTOR_PHASE_A, HIGH);
    }
    break;
  }

   delay(MILLISECONDS_STEP_HOLD);
}
int   Update()
{
  
  long              nClockwiseSeconds = 0;
  long              nCounterClockwiseSeconds = 0;
  long              nStepCount = 0;
  long              nStepDirection = 0;
  long              nStepPosition = 0;
  long              nStepPositionN1 = 0;
  
  // Calculate clockwise and counterclockwise seconds required to drive indicated seconds to actual seconds.
  
  if(nSeconds > nSecondsIndicated)
  {
    nClockwiseSeconds = nSeconds - nSecondsIndicated;
    nCounterClockwiseSeconds = (nSecondsIndicated + 60) - nSeconds;
  }
  else if(nSeconds < nSecondsIndicated)
  {
    nClockwiseSeconds = (nSeconds + 60) - nSecondsIndicated;
    nCounterClockwiseSeconds = nSecondsIndicated - nSeconds;
  }
  
  // Check if update is needed.
  
  if((nClockwiseSeconds) || (nCounterClockwiseSeconds))
  {
    // Update is needed, determine shortest direction.
    
    if(nClockwiseSeconds < nCounterClockwiseSeconds)
    {
      // Clockwise movement is shorter.
      
      nStepDirection = 1; 
    }
    else
    {
      // Counterclockwise movement is shorter.
      
      nStepDirection = -1;
    }

    // Drive indicated seconds to seconds.

    while(nSeconds != nSecondsIndicated)
    {
      // Calculate n-1 step position.
      
      nStepPositionN1 = ((nSecondsIndicated % 60) * STEPS_PER_REVOLUTION) / 60;
      
      // Update seconds.
      
      nSecondsIndicated = (nSecondsIndicated + nStepDirection) % 60;
      nSecondsIndicated = (nSecondsIndicated < 0) ? 60 + nSecondsIndicated : nSecondsIndicated;
      
      // Calculate current step position.

      nStepPosition = ((nSecondsIndicated % 60) * STEPS_PER_REVOLUTION) / 60;

      // Calculate step count.
      
      nStepCount = ((nStepDirection > 0) ? nStepPosition - nStepPositionN1 : nStepPositionN1 - nStepPosition);
      nStepCount = (nStepCount < 0) ? STEPS_PER_REVOLUTION + nStepCount : nStepCount;
                     
      // Step the required steps.
      
      while(nStepCount)
      {
        Step(nStepDirection);
        nStepCount = nStepCount - 1;
      }
    }
  }
  else
  {
    // No update performed.
    
    return 0;
  }

   MotorOff();
 
  
  return -1;
}
