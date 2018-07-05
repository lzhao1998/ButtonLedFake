#include "unity.h"
#include "LedController.h"
#include "mock_Button.h"
#include "mock_Led.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int turnLedCallNumbers = 0;
int geTbuttonStateMaxCalls = 0;
int expectedTurnLedMaxCalls = 0;
ButtonState *expectedButtonStates = NULL;
LedState *expectedLedStates = NULL;

void setUp(void){}
void tearDown(void){}

char *createMsg(char *format, ...)
{
  va_list valist;
  int neededSize;
  char *buffer;

  va_start(valist,format);
  neededSize = vsnprintf(NULL, 0, format, valist)+ 1;
  buffer = malloc(neededSize);
  vsnprintf(buffer,neededSize, format, valist);
  va_end(valist);

  return buffer;
}

void freeMsg(char *msg)
{
  if(msg){
    free(msg);
  }
}

char *getLedStateName(LedState state)
{
  switch(state)
  {
    case LED_ON:
      return "LED_ON";
      break;
    case LED_OFF:
      return "LED_OFF";
      break;
    default:
    return "(unknown LED state)";
      break;
  }
}

void fake_turnLed(LedState state, int NumCalls)
{
  //fake code live here
  char *msg;
  turnLedCallNumbers++;
    if(NumCalls < expectedTurnLedMaxCalls)
    {
      LedState expectedState = expectedLedStates[NumCalls];
      if(state != expectedLedStates)
        msg = createMsg("turnLed() was called with %s, but expect %s", \
                  getLedStateName(state), getLedStateName(expectedState));
        TEST_FAIL_MESSAGE(msg);
    }
    else
    {
      msg = createMsg("turnLed(%s) was called more times than expected", \
                getLedStateName(state));
      TEST_FAIL_MESSAGE(msg);
    }
}

void fake_turnLedOn(LedState state, int NumCalls)
{
  turnLedCallNumbers++;
  switch(NumCalls)
  {
    case 1:
      if(state != LED_ON)
      {
        TEST_FAIL_MESSAGE("turnLed() was called with LED_OFF, but expect LED_ON");
      }
      break;
    default:
      TEST_FAIL_MESSAGE("Received extra getButtonState() calls");
  }
}

void fake_turnLedOff(LedState state, int NumCalls)
{
  //fake code live here
  turnLedCallNumbers++;
  switch(NumCalls)
  {
    case 1:
      if(state != LED_OFF)
      {
        TEST_FAIL_MESSAGE("turnLed() was called with LED_OFF, but expect LED_ON");
      }
      break;
    default:
      TEST_FAIL_MESSAGE("Received extra getButtonState() calls");
  }
}

ButtonState fake_getButtonState(int NumCalls)
{
  if(NumCalls < geTbuttonStateMaxCalls)
  {
    return expectedButtonStates[NumCalls];
  }
  else
  {
    TEST_FAIL_MESSAGE("Received extra getButtonState() calls");
  }
}

void setupFake(LedState expLedStates[], int ledMaxCalls, ButtonState buttStates[], int buttonMaxCalls)
{
  turnLedCallNumbers = 0;
  turnLed_StubWithCallback(fake_turnLed);
  expectedLedStates = expLedStates;
  expectedTurnLedMaxCalls = ledMaxCalls;
  getButtonState_StubWithCallback(fake_getButtonState);
  expectedButtonStates = buttStates;
  geTbuttonStateMaxCalls = buttonMaxCalls;
}

ButtonState fake_getButtonStateReleasedPressedReleased(int NumCalls)
{
  switch(NumCalls)
  {
    case 1:
      return BUTTON_RELEASED;
      break;
    case 2:
      return BUTTON_PRESSED;
      break;
    case 3:
      return BUTTON_RELEASED;
      break;
    default:
      TEST_FAIL_MESSAGE("Received extra getButtonState() calls");
  }
}

void verifyTurnLedCalls(int numCalls)
{
  if(turnLedCallNumbers != numCalls)
    TEST_FAIL_MESSAGE("turnLed() was not called at all. But 1 call is expected");
}

/*
void test_turnOnLedIfButtonIsPressed_given_button_is_pressed_expect_led_to_turn_on(void)
{
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  turnLed_Expect(LED_ON);

  turnOnLedIfButtonIsPressed();
}

void test_turnOnLedIfButtonIsPressed_given_button_is_not_pressed_expect_led_to_turn_off(void)
{
  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  turnLed_Expect(LED_OFF);

  turnOnLedIfButtonIsPressed();
}*/

void test_doTapTapTurnOn_given_button_is_taptap_when_led_off_expect_led_to_turn_on(void)
{
  //Faking....
  LedButtonInfo info = {LED_OFF,BUTTON_RELEASED,BUTTON_PRESSED};
  LedState expectedLedStates[] = {LED_ON};
  ButtonState buttonStates[] = {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_RELEASED};

  setupFake(expectedLedStates, 1, buttonStates, 3);

  tapTurnOnTapTurnOffLed(&info);
  tapTurnOnTapTurnOffLed(&info);
  tapTurnOnTapTurnOffLed(&info);

  verifyTurnLedCalls(1);

  TEST_ASSERT_EQUAL(LED_ON, info.currentLedState);
}

void test_doTapTapTurnOff_given_button_is_taptap_when_led_on_expect_led_to_turn_off(void)
{
  LedButtonInfo info = {LED_ON,BUTTON_RELEASED,BUTTON_PRESSED};
  LedState expectedLedStates[] = {LED_OFF};
  ButtonState buttonStates[] = {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_RELEASED};

  setupFake(expectedLedStates, 1, buttonStates, 3);

  tapTurnOnTapTurnOffLed(&info);
  tapTurnOnTapTurnOffLed(&info);
  tapTurnOnTapTurnOffLed(&info);

  verifyTurnLedCalls(1);

  TEST_ASSERT_EQUAL(LED_ON, info.currentLedState);
}

void test_nani_kore(void)
{
  LedButtonInfo info = {LED_ON,BUTTON_RELEASED,BUTTON_PRESSED};
  LedState expectedLedStates[] = {LED_OFF};
  ButtonState buttonStates[] = {BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_RELEASED};

  setupFake(expectedLedStates, 1, buttonStates, 3);

  getButtonState();     //It should return RELEASED
  getButtonState();     //It should return PRESSED
  turnLed(LED_ON);
  getButtonState();     //It should return RELEASED

  verifyTurnLedCalls(1);

  //TEST_ASSERT_EQUAL(LED_ON, info.currentLedState);
}
/*
void test_doTapTapTurnOff_given_button_is_alway_pressed_when_led_on_expect_led_to_turn_on(void)
{
  LedButtonInfo info = {LED_ON,BUTTON_RELEASED,BUTTON_RELEASED};

  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  tapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  tapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  turnLed_Expect(LED_ON);
  tapTurnOnTapTurnOffLed(&info);

  TEST_ASSERT_EQUAL(LED_ON, info.currentLedState);
}

void test_doTapTapTurnOff_given_button_is_alway_released_when_led_off_expect_led_to_turn_off(void)
{
  LedButtonInfo info = {LED_ON,BUTTON_PRESSED,BUTTON_RELEASED};

  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  tapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  tapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  turnLed_Expect(LED_OFF);
  tapTurnOnTapTurnOffLed(&info);

  TEST_ASSERT_EQUAL(LED_OFF, info.currentLedState);
}*/
