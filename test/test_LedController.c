#include "unity.h"
#include "LedController.h"
#include "mock_Button.h"
#include "mock_Led.h"
#include <stdio.h>

void setUp(void){}
void tearDown(void){}

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
}


void test_doTapTapTurnOn_given_button_is_taptap_when_led_off_expect_led_to_turn_on(void)
{
  LedButtonInfo info = {LED_OFF,BUTTON_RELEASED,BUTTON_PRESSED};

  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  tapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  turnLed_Expect(LED_ON);
  tapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  tapTurnOnTapTurnOffLed(&info);

  TEST_ASSERT_EQUAL(LED_ON, info.currentLedState);
}
/*
void test_doTapTapTurnOff_given_button_is_taptap_when_led_on_expect_led_to_turn_off(void)
{
  LedButtonInfo info = {LED_ON,BUTTON_RELEASED,BUTTON_RELEASED};

  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  tapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  tapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_RELEASED);
  turnLed_Expect(LED_OFF);
  tapTurnOnTapTurnOffLed(&info);

  TEST_ASSERT_EQUAL(LED_OFF, info.currentLedState);
}

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
