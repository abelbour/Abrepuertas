#pragma once

static const char MELODY_1[] PROGMEM = "d=8,o=6,b=140:c,c,g,4g,16g,16p,f,g,c,2c,p";
static const char MELODY_2[] PROGMEM = "d=8,o=6,b=140:c,g,c7,4c7,16c7,16p,b,c7,g,2g,p";
static const char MELODY_3[] PROGMEM = "d=4,o=4,b=100:c7,b,2a,16a,16p,a,d7,b,2g,p";
static const char MELODY_4[] PROGMEM = "d=4,o=4,b=100:a,b,c7,g,f,e,g,4d,16d,16p,c,2c,p";
static const char APERTURA[] PROGMEM = "d=16,o=7,b=225:c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,p,c,c";
static const char EMERGENCIA[] PROGMEM = "d=1,o=6,b=225:c,8p,c,8p,c,8p,c,8p";
static const char ACTIVAR[] PROGMEM = "d=8,o=5,b=200:8c,8e,8g,8c6,8e6,8d6,8c6,4g";
static const char DESACTIVAR[] PROGMEM = "d=8,o=5,b=200:8c6,8g,8e,8c,8a4,8g,8e,4c";
static const char BEEP_FLASH[] PROGMEM = "d=8,o=5,b=300:b";

static const char* ALL_MELODIES[] = {MELODY_1, MELODY_2, MELODY_3, MELODY_4};
