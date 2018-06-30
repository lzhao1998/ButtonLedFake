#ifndef _LED_H
#define _LED_H

typedef enum
{
  LED_OFF,
  LED_ON,
}LedState;

void turnLed(LedState state);

#endif // _LED_H
