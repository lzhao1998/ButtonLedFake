#include "LedController.h"
#include "Button.h"
#include "Led.h"


void turnOnLedIfButtonIsPressed(void)
{
  if(getButtonState() == 1)
  {
    turnLed(LED_ON);
  }
  else
  {
    turnLed(LED_OFF);
  }
}

void doLedForever()
{
  while(1)
  {
    turnOnLedIfButtonIsPressed();
  }
}

void tapTurnOnTapTurnOffLed(LedButtonInfo *info)
{
/*    LedState    ButtonState   PreviousButton   LedOutput
      0             0               0              0
      0             0               1           (wont happen)0
      0             1               0              1
      0             1               1              1
      1             0               0              0
      1             0               1              1
      1             1               0           (wont happen)1
      1             1               1              1

  info->currentButtonState = getButtonState();
  int i,j,k,ans;
  i = info->currentLedState;
  j = info->currentButtonState;
  k = info->previousButtonState;
  ans = j + (i * k);
  info->currentLedState = ans;
  turnLed(info->currentLedState);
  info->previousButtonState = info->currentButtonState;
*/
  info->currentButtonState = getButtonState();
  switch(info->currentLedState)
  {
    case 0:
      if(info->currentButtonState == 0 && info->previousButtonState == 0)
      {
        info->currentLedState = 0;
        info->previousButtonState = 0;
      }
      else if(info->currentButtonState == 0 && info->previousButtonState == 1)
      {
        info->currentLedState = 0;
        info->previousButtonState = 0;
      }
      else
      {
        info->currentLedState = 1;
        info->previousButtonState = 1;
      }
      break;
    case 1:
      if(info->currentButtonState == 0 && info->previousButtonState == 0)
      {
        info->currentLedState = 0;
        info->previousButtonState = 0;
      }
      else if(info->currentButtonState == 0 && info->previousButtonState == 1)
      {
        info->currentLedState = 1;
        info->previousButtonState = 0;
      }
      else
      {
        info->currentLedState = 1;
        info->previousButtonState = 1;
      }
      break;
    default:
      info->currentLedState = info->currentLedState;
      info->previousButtonState = info->previousButtonState;
      turnLed(info->currentLedState);
      break;
  }
  turnLed(info->currentLedState);
}

void doTapTapLedController()
{
  LedState currentLedState;
  while(1)
  {
  //  tapTurnOnTapTurnOffLed(&currentLedState);
  }
}
