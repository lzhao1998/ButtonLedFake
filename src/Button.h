#ifndef _BUTTON_H
#define _BUTTON_H

typedef enum
{
  BUTTON_RELEASED,
  BUTTON_PRESSED,
}ButtonState;

// Return non-zero if button is pressed; zero otherwise.
ButtonState getButtonState(void);


#endif // _BUTTON_H
