#include "KeyCodes.h"
#include "Keyboard.h"

uint8_t convert_keycode(uint8_t keycode, uint8_t which){
  /* 
   * convert keycode to <which> output
   * keycode -- KeyCode.h key code
   * which -- TO_USB or TO_EZKEY
   */
  uint8_t out = keycode;
  if(which == TO_USB){
    switch(keycode){
    case KC_ARROW_UP:
      out = KEY_UP_ARROW;
      break;
    case KC_ARROW_DOWN:
      out = KEY_DOWN_ARROW;
      break;
    case KC_ARROW_LEFT:
      out = KEY_LEFT_ARROW;
      break;
    case KC_ARROW_RIGHT:
      out = KEY_RIGHT_ARROW;
      break;
    case KC_BACKSPACE:
      out = KEY_BACKSPACE;
      break;
    case KC_SPACE:
      out = ' ';
      break;     
    case KC_TAB:
      out = KEY_TAB;
      break;
    case KC_RETURN:
      out = KEY_RETURN;
      break;
    case KC_ESCAPE:
      out = KEY_ESC;
      break;
    case KC_INSERT:
      out = KEY_INSERT;
      break;
    case KC_DELETE:
      out = KEY_DELETE;
      break;
    case KC_PAGE_UP:
      out = KEY_PAGE_UP;
      break;
    case KC_PAGE_DOWN:
      out = KEY_PAGE_DOWN;
      break;
    case KC_HOME:
      out = KEY_HOME;
      break;
    case KC_END:
      out = KEY_END;
      break;
    case KC_CAPS_LOCK:
      out = KEY_CAPS_LOCK;
      break;
    case KC_F1:
      out = KEY_F1;
      break;
    case KC_F2:
      out = KEY_F2;
      break;
    case KC_F3:
      out = KEY_F3;
      break;
    case KC_F4:
      out = KEY_F4;
      break;
    case KC_F5:
      out = KEY_F5;
      break;
    case KC_F6:
      out = KEY_F6;
      break;
    case KC_F7:
      out = KEY_F7;
      break;
    case KC_F8:
      out = KEY_F8;
      break;
    case KC_F9:
      out = KEY_F9;
      break;
    case KC_F10:
      out = KEY_F10;
      break;
    case KC_F11:
      out = KEY_F11;
      break;
    case KC_F12:
      out = KEY_F12;
      break;
    case KC_1:
      out = (uint8_t)'1';
      break;
    case KC_2:
      out = (uint8_t)'2';
      break;
    case KC_3:
      out = (uint8_t)'3';
      break;
    case KC_4:
      out = (uint8_t)'4';
      break;
    case KC_5:
      out = (uint8_t)'5';
      break;
    case KC_6:
      out = (uint8_t)'6';
      break;
    case KC_7:
      out = (uint8_t)'7';
      break;
    case KC_8:
      out = (uint8_t)'8';
      break;
    case KC_9:
      out = (uint8_t)'9';
      break;
    case KC_0:
      out = (uint8_t)'0';
      break;
    case KC_GRAVE:
      out = (uint8_t)'`';
      break;
    case KC_COMMA:
      out = (uint8_t)',';
      break;
    case KC_PERIOD:
      out = (uint8_t)'.';
      break;
    case KC_SLASH:
      out = (uint8_t)'/';
      break;
    case KC_SEMICOLON:
      out = (uint8_t)':';
      break;
    case KC_APOSTROPHE:
      out = (uint8_t)'\'';
      break;
    case KC_BRACKET_LEFT:
      out = (uint8_t)'[';
      break;
    case KC_BRACKET_RIGHT:
      out = (uint8_t)']';
      break;
    case KC_MINUS:
      out = (uint8_t)'-';
      break;
    case KC_EQUAL:
      out = (uint8_t)'=';
      break;
    case KC_BACKSLASH:
      out = (uint8_t)'\\';
      break;
    default:
      out = keycode - KC_A + (uint8_t)'a';
    }
  }
  else{
  }
  return out;
}
