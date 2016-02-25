#ifndef __EZKEY_H
#define __EZKEY_H

// Bits in usbHidKeyboardInput.modifiers
#include <inttypes.h>

typedef uint8_t byte;

const byte MODIFIER_NONE          =byte((0));
const byte MODIFIER_CONTROL_LEFT  =byte((1<<0));
const byte MODIFIER_SHIFT_LEFT    =byte((1<<1));
const byte MODIFIER_ALT_LEFT      =byte((1<<2));
const byte MODIFIER_GUI_LEFT      =byte((1<<3));
const byte MODIFIER_CONTROL_RIGHT =byte((1<<4));
const byte MODIFIER_SHIFT_RIGHT   =byte((1<<5));
const byte MODIFIER_ALT_RIGHT     =byte((1<<6));
const byte MODIFIER_GUI_RIGHT     =byte((1<<7));

// Values for usbHidKeyboardInput.keyCodes
// Only the key codes for common keys are defined here. See Hut1_12.pdf for a full list.
const byte EZKEY_NONE               =byte(0x00);
const byte EZKEY_A                  =byte(0x04);
const byte EZKEY_B                  =byte(0x05);
const byte EZKEY_C                  =byte(0x06);
const byte EZKEY_D                  =byte(0x07);
const byte EZKEY_E                  =byte(0x08);
const byte EZKEY_F                  =byte(0x09);
const byte EZKEY_G                  =byte(0x0A);
const byte EZKEY_H                  =byte(0x0B);
const byte EZKEY_I                  =byte(0x0C);
const byte EZKEY_J                  =byte(0x0D);
const byte EZKEY_K                  =byte(0x0E);
const byte EZKEY_L                  =byte(0x0F);
const byte EZKEY_M                  =byte(0x10);
const byte EZKEY_N                  =byte(0x11);
const byte EZKEY_O                  =byte(0x12);
const byte EZKEY_P                  =byte(0x13);
const byte EZKEY_Q                  =byte(0x14);
const byte EZKEY_R                  =byte(0x15);
const byte EZKEY_S                  =byte(0x16);
const byte EZKEY_T                  =byte(0x17);
const byte EZKEY_U                  =byte(0x18);
const byte EZKEY_V                  =byte(0x19);
const byte EZKEY_W                  =byte(0x1A);
const byte EZKEY_X                  =byte(0x1B);
const byte EZKEY_Y                  =byte(0x1C);
const byte EZKEY_Z                  =byte(0x1D);
const byte EZKEY_1                  =byte(0x1E);
const byte EZKEY_2                  =byte(0x1F);
const byte EZKEY_3                  =byte(0x20);
const byte EZKEY_4                  =byte(0x21);
const byte EZKEY_5                  =byte(0x22);
const byte EZKEY_6                  =byte(0x23);
const byte EZKEY_7                  =byte(0x24);
const byte EZKEY_8                  =byte(0x25);
const byte EZKEY_9                  =byte(0x26);
const byte EZKEY_0                  =byte(0x27);
const byte EZKEY_RETURN             =byte(0x28);
const byte EZKEY_ESCAPE             =byte(0x29);
const byte EZKEY_BACKSPACE          =byte(0x2A);
const byte EZKEY_TAB                =byte(0x2B);
const byte EZKEY_SPACE              =byte(0x2C);
const byte EZKEY_MINUS              =byte(0x2D);
const byte EZKEY_EQUAL              =byte(0x2E);
const byte EZKEY_BRACKET_LEFT       =byte(0x2F);
const byte EZKEY_BRACKET_RIGHT      =byte(0x30);
const byte EZKEY_BACKSLASH          =byte(0x31);
const byte EZKEY_EUROPE_1           =byte(0x32);
const byte EZKEY_SEMICOLON          =byte(0x33);
const byte EZKEY_APOSTROPHE         =byte(0x34);
const byte EZKEY_GRAVE              =byte(0x35);
const byte EZKEY_COMMA              =byte(0x36);
const byte EZKEY_PERIOD             =byte(0x37);
const byte EZKEY_SLASH              =byte(0x38);
const byte EZKEY_CAPS_LOCK          =byte(0x39);
const byte EZKEY_F1                 =byte(0x3A);
const byte EZKEY_F2                 =byte(0x3B);
const byte EZKEY_F3                 =byte(0x3C);
const byte EZKEY_F4                 =byte(0x3D);
const byte EZKEY_F5                 =byte(0x3E);
const byte EZKEY_F6                 =byte(0x3F);
const byte EZKEY_F7                 =byte(0x40);
const byte EZKEY_F8                 =byte(0x41);
const byte EZKEY_F9                 =byte(0x42);
const byte EZKEY_F10                =byte(0x43);
const byte EZKEY_F11                =byte(0x44);
const byte EZKEY_F12                =byte(0x45);
const byte EZKEY_PRINT_SCREEN       =byte(0x46);
const byte EZKEY_SCROLL_LOCK        =byte(0x47);
const byte EZKEY_PAUSE              =byte(0x48);
const byte EZKEY_INSERT             =byte(0x49);
const byte EZKEY_HOME               =byte(0x4A);
const byte EZKEY_PAGE_UP            =byte(0x4B);
const byte EZKEY_DELETE             =byte(0x4C);
const byte EZKEY_END                =byte(0x4D);
const byte EZKEY_PAGE_DOWN          =byte(0x4E);
const byte EZKEY_ARROW_RIGHT        =byte(0x4F);
const byte EZKEY_ARROW_LEFT         =byte(0x50);
const byte EZKEY_ARROW_DOWN         =byte(0x51);
const byte EZKEY_ARROW_UP           =byte(0x52);
const byte EZKEY_NUM_LOCK           =byte(0x53);
const byte EZKEY_KEYPAD_DIVIDE      =byte(0x54);
const byte EZKEY_KEYPAD_MULTIPLY    =byte(0x55);
const byte EZKEY_KEYPAD_SUBTRACT    =byte(0x56);
const byte EZKEY_KEYPAD_ADD         =byte(0x57);
const byte EZKEY_KEYPAD_ENTER       =byte(0x58);
const byte EZKEY_KEYPAD_1           =byte(0x59);
const byte EZKEY_KEYPAD_2           =byte(0x5A);
const byte EZKEY_KEYPAD_3           =byte(0x5B);
const byte EZKEY_KEYPAD_4           =byte(0x5C);
const byte EZKEY_KEYPAD_5           =byte(0x5D);
const byte EZKEY_KEYPAD_6           =byte(0x5E);
const byte EZKEY_KEYPAD_7           =byte(0x5F);
const byte EZKEY_KEYPAD_8           =byte(0x60);
const byte EZKEY_KEYPAD_9           =byte(0x61);
const byte EZKEY_KEYPAD_0           =byte(0x62);
const byte EZKEY_KEYPAD_DECIMAL     =byte(0x63);
const byte EZKEY_EUROPE_2           =byte(0x64);
const byte EZKEY_APPLICATION        =byte(0x65);
const byte EZKEY_POWER              =byte(0x66);
const byte EZKEY_KEYPAD_EQUAL       =byte(0x67);
const byte EZKEY_F13                =byte(0x68);
const byte EZKEY_F14                =byte(0x69);
const byte EZKEY_F15                =byte(0x6A);
const byte EZKEY_CONTROL_LEFT       =byte(0xE0);
const byte EZKEY_SHIFT_LEFT         =byte(0xE1);
const byte EZKEY_ALT_LEFT           =byte(0xE2);
const byte EZKEY_GUI_LEFT           =byte(0xE3);
const byte EZKEY_CONTROL_RIGHT      =byte(0xE4);
const byte EZKEY_SHIFT_RIGHT        =byte(0xE5);
const byte EZKEY_ALT_RIGHT          =byte(0xE6);
const byte EZKEY_GUI_RIGHT          =byte(0xE7);
const byte EZKEY_LEFT_MOUSE_BUTTON  = byte(0b001); // for mouseCommnad
const byte EZKEY_MIDDLE_MOUSE_BUTTON= byte(0b100); // for mouseCommnad
const byte EZKEY_RIGHT_MOUSE_BUTTON = byte(0b010); // for mouseCommnad

#endif
