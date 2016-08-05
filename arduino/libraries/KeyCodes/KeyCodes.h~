#ifndef __KEYCODES_H
#define __KEYCODES_H

// Bits in usbHidKeyboardInput.modifiers
#include <inttypes.h>

uint8_t convert_keycode(uint8_t keycode, uint8_t which);

typedef uint8_t byte;

const uint8_t TO_USB = 1;
const uint8_t TO_EZKEY = 2;

const byte KC_MODIFIER_NONE          =byte((0));
const byte KC_MODIFIER_CONTROL_LEFT  =byte((1<<0));
const byte KC_MODIFIER_SHIFT_LEFT    =byte((1<<1));
const byte KC_MODIFIER_ALT_LEFT      =byte((1<<2));
const byte KC_MODIFIER_GUI_LEFT      =byte((1<<3));
const byte KC_MODIFIER_CONTROL_RIGHT =byte((1<<4));
const byte KC_MODIFIER_SHIFT_RIGHT   =byte((1<<5));
const byte KC_MODIFIER_ALT_RIGHT     =byte((1<<6));
const byte KC_MODIFIER_GUI_RIGHT     =byte((1<<7));

// Values for usbHidKeyboardInput.keyCodes
// Only the key codes for common keys are defined here. See Hut1_12.pdf for a full list.
const byte KC_NONE               =byte(0x00);
const byte KC_A                  =byte(0x04);
const byte KC_B                  =byte(0x05);
const byte KC_C                  =byte(0x06);
const byte KC_D                  =byte(0x07);
const byte KC_E                  =byte(0x08);
const byte KC_F                  =byte(0x09);
const byte KC_G                  =byte(0x0A);
const byte KC_H                  =byte(0x0B);
const byte KC_I                  =byte(0x0C);
const byte KC_J                  =byte(0x0D);
const byte KC_K                  =byte(0x0E);
const byte KC_L                  =byte(0x0F);
const byte KC_M                  =byte(0x10);
const byte KC_N                  =byte(0x11);
const byte KC_O                  =byte(0x12);
const byte KC_P                  =byte(0x13);
const byte KC_Q                  =byte(0x14);
const byte KC_R                  =byte(0x15);
const byte KC_S                  =byte(0x16);
const byte KC_T                  =byte(0x17);
const byte KC_U                  =byte(0x18);
const byte KC_V                  =byte(0x19);
const byte KC_W                  =byte(0x1A);
const byte KC_X                  =byte(0x1B);
const byte KC_Y                  =byte(0x1C);
const byte KC_Z                  =byte(0x1D);
const byte KC_1                  =byte(0x1E);
const byte KC_2                  =byte(0x1F);
const byte KC_3                  =byte(0x20);
const byte KC_4                  =byte(0x21);
const byte KC_5                  =byte(0x22);
const byte KC_6                  =byte(0x23);
const byte KC_7                  =byte(0x24);
const byte KC_8                  =byte(0x25);
const byte KC_9                  =byte(0x26);
const byte KC_0                  =byte(0x27);
const byte KC_RETURN             =byte(0x28);
const byte KC_ESCAPE             =byte(0x29);
const byte KC_BACKSPACE          =byte(0x2A);
const byte KC_TAB                =byte(0x2B);
const byte KC_SPACE              =byte(0x2C);
const byte KC_MINUS              =byte(0x2D);
const byte KC_EQUAL              =byte(0x2E);
const byte KC_BRACKET_LEFT       =byte(0x2F);
const byte KC_BRACKET_RIGHT      =byte(0x30);
const byte KC_BACKSLASH          =byte(0x31);
const byte KC_EUROPE_1           =byte(0x32);
const byte KC_SEMICOLON          =byte(0x33);
const byte KC_APOSTROPHE         =byte(0x34);
const byte KC_GRAVE              =byte(0x35);
const byte KC_COMMA              =byte(0x36);
const byte KC_PERIOD             =byte(0x37);
const byte KC_SLASH              =byte(0x38);
const byte KC_CAPS_LOCK          =byte(0x39);
const byte KC_F1                 =byte(0x3A);
const byte KC_F2                 =byte(0x3B);
const byte KC_F3                 =byte(0x3C);
const byte KC_F4                 =byte(0x3D);
const byte KC_F5                 =byte(0x3E);
const byte KC_F6                 =byte(0x3F);
const byte KC_F7                 =byte(0x40);
const byte KC_F8                 =byte(0x41);
const byte KC_F9                 =byte(0x42);
const byte KC_F10                =byte(0x43);
const byte KC_F11                =byte(0x44);
const byte KC_F12                =byte(0x45);
const byte KC_PRINT_SCREEN       =byte(0x46);
const byte KC_SCROLL_LOCK        =byte(0x47);
const byte KC_PAUSE              =byte(0x48);
const byte KC_INSERT             =byte(0x49);
const byte KC_HOME               =byte(0x4A);
const byte KC_PAGE_UP            =byte(0x4B);
const byte KC_DELETE             =byte(0x4C);
const byte KC_END                =byte(0x4D);
const byte KC_PAGE_DOWN          =byte(0x4E);
const byte KC_ARROW_RIGHT        =byte(0x4F);
const byte KC_ARROW_LEFT         =byte(0x50);
const byte KC_ARROW_DOWN         =byte(0x51);
const byte KC_ARROW_UP           =byte(0x52);
const byte KC_NUM_LOCK           =byte(0x53);
const byte KC_KCPAD_DIVIDE      =byte(0x54);
const byte KC_KCPAD_MULTIPLY    =byte(0x55);
const byte KC_KCPAD_SUBTRACT    =byte(0x56);
const byte KC_KCPAD_ADD         =byte(0x57);
const byte KC_KCPAD_ENTER       =byte(0x58);
const byte KC_KCPAD_1           =byte(0x59);
const byte KC_KCPAD_2           =byte(0x5A);
const byte KC_KCPAD_3           =byte(0x5B);
const byte KC_KCPAD_4           =byte(0x5C);
const byte KC_KCPAD_5           =byte(0x5D);
const byte KC_KCPAD_6           =byte(0x5E);
const byte KC_KCPAD_7           =byte(0x5F);
const byte KC_KCPAD_8           =byte(0x60);
const byte KC_KCPAD_9           =byte(0x61);
const byte KC_KCPAD_0           =byte(0x62);
const byte KC_KCPAD_DECIMAL     =byte(0x63);
const byte KC_EUROPE_2           =byte(0x64);
const byte KC_APPLICATION        =byte(0x65);
const byte KC_POWER              =byte(0x66);
const byte KC_KCPAD_EQUAL       =byte(0x67);
const byte KC_F13                =byte(0x68);
const byte KC_F14                =byte(0x69);
const byte KC_F15                =byte(0x6A);
const byte KC_CONTROL_LEFT       =byte(0xE0);
const byte KC_SHIFT_LEFT         =byte(0xE1);
const byte KC_ALT_LEFT           =byte(0xE2);
const byte KC_GUI_LEFT           =byte(0xE3);
const byte KC_CONTROL_RIGHT      =byte(0xE4);
const byte KC_SHIFT_RIGHT        =byte(0xE5);
const byte KC_ALT_RIGHT          =byte(0xE6);
const byte KC_GUI_RIGHT          =byte(0xE7);
const byte KC_LEFT_MOUSE_BUTTON  = byte(0b001); // for mouseCommnad
const byte KC_MIDDLE_MOUSE_BUTTON= byte(0b100); // for mouseCommnad
const byte KC_RIGHT_MOUSE_BUTTON = byte(0b010); // for mouseCommnad

// Constants for ConsumerCommand // credit DudleyDoggins from Adafruit Forum
// key                 mask1    mask0    = consumerComand() hex params
// ----------------    -------- --------   ---------------------------
// Home                00000000 00000001 = (0x01,0x00)
// KeyboardLayout      00000000 00000010 = (0x02,0x00)
// Search              00000000 00000100 = (0x04,0x00)
// Snapshot            00000000 00001000 = (0x08,0x00)
// VolumeUp            00000000 00010000 = (0x10,0x00)
// VolumeDown          00000000 00100000 = (0x20,0x00)
// Play/Pause          00000000 01000000 = (0x40,0x00)
// Fast Forward        00000000 10000000 = (0x80,0x00)
// Rewind              00000001 00000000 = (0x00,0x01)
// Scan Next Track     00000010 00000000 = (0x00,0x02)
// Scan Previous Track 00000100 00000000 = (0x00,0x04)
// Random Play         00001000 00000000 = (0x00,0x08)
// Stop                00010000 00000000 = (0x00,0x10)


#endif
