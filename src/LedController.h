#ifndef _LEDCONTROLLER_H
#define _LEDCONTROLLER_H

#include "Led.h"
#include "Button.h"

typedef struct LedButtonInfo LedButtonInfo;
struct LedButtonInfo{
  LedState currentLedState;
  ButtonState currentButtonState;
  ButtonState previousButtonState;
};

void turnOnLedIfButtonIsPressed(void);
void tapTurnOnTapTurnOffLed(LedButtonInfo *info);
void doLedForever();
void doTapTapLedController();
ButtonState getButtonState();

#endif // _LEDCONTROLLER_H
