#include "img.h"
#include <avr/pgmspace.h>

/* Leave button (normal state). */
const const unsigned char PROGMEM PROGMEM btn_leave_data[] =
{
    0x1f, 0xff, 0xf8, 0x60, 0x00, 0x0e, 0x40, 0x00, 0x02, 0xc0, 0x00, 0x03,
    0x80, 0x00, 0x01, 0x80, 0x00, 0x01, 0x83, 0x00, 0xc1, 0x83, 0x81, 0xc1,
    0x81, 0xc3, 0x81, 0x80, 0xe7, 0x01, 0x80, 0x7e, 0x01, 0x80, 0x3c, 0x01,
    0x80, 0x3c, 0x01, 0x80, 0x7e, 0x01, 0x80, 0xe7, 0x01, 0x81, 0xc3, 0x81,
    0x83, 0x81, 0xc1, 0x83, 0x00, 0xc1, 0x80, 0x00, 0x01, 0x80, 0x00, 0x01,
    0xc0, 0x00, 0x03, 0x40, 0x00, 0x02, 0x70, 0x00, 0x0e, 0x1f, 0xff, 0xf8
};

GLI_BITMAP btn_leave =
{
    24,
    24,
    btn_leave_data
};


/* Leave button (hover state). */
const unsigned char PROGMEM btn_leave_hover_data[] =
{
    0x1f, 0xff, 0xf8, 0x7f, 0xff, 0xfe, 0x7f, 0xff, 0xfe, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0x3f, 0xfc, 0x7e, 0x3f,
    0xfe, 0x3c, 0x7f, 0xff, 0x18, 0xff, 0xff, 0x81, 0xff, 0xff, 0xc3, 0xff,
    0xff, 0xc3, 0xff, 0xff, 0x81, 0xff, 0xff, 0x18, 0xff, 0xfe, 0x3c, 0x7f,
    0xfc, 0x7e, 0x3f, 0xfc, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x7f, 0xff, 0xfe, 0x7f, 0xff, 0xfe, 0x1f, 0xff, 0xf8
};

GLI_BITMAP btn_leave_hover =
{
    24,
    24,
    btn_leave_hover_data
};


/* Resume button (normal state). */
const unsigned char PROGMEM btn_resume_data[] =
{
    0x1f, 0xff, 0xf8, 0x70, 0x00, 0x06, 0x40, 0x00, 0x02, 0xc0, 0x00, 0x01,
    0x80, 0x00, 0x01, 0x80, 0x00, 0x01, 0x83, 0x00, 0x01, 0x83, 0xc0, 0x01,
    0x83, 0xf0, 0x01, 0x83, 0xfc, 0x01, 0x83, 0xff, 0x01, 0x83, 0xff, 0xc1,
    0x83, 0xff, 0xc1, 0x83, 0xff, 0x01, 0x83, 0xfc, 0x01, 0x83, 0xf0, 0x01,
    0x83, 0xc0, 0x01, 0x83, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x00, 0x01,
    0x80, 0x00, 0x01, 0x40, 0x00, 0x02, 0x70, 0x00, 0x06, 0x1f, 0xff, 0xf8
};

GLI_BITMAP btn_resume =
{
    24,
    24,
    btn_resume_data
};


/* Resume button (hover state). */
const unsigned char PROGMEM btn_resume_hover_data[] =
{
    0x1f, 0xff, 0xf8, 0x7f, 0xff, 0xfe, 0x7f, 0xff, 0xfe, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0x3f, 0xff,
    0xfc, 0x0f, 0xff, 0xfc, 0x03, 0xff, 0xfc, 0x00, 0xff, 0xfc, 0x00, 0x3f,
    0xfc, 0x00, 0x3f, 0xfc, 0x00, 0xff, 0xfc, 0x03, 0xff, 0xfc, 0x0f, 0xff,
    0xfc, 0x3f, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x7f, 0xff, 0xfe, 0x7f, 0xff, 0xfe, 0x1f, 0xff, 0xf8
};

GLI_BITMAP btn_resume_hover =
{
    24,
    24,
    btn_resume_hover_data
};


/* Invader. */
const unsigned char PROGMEM invader_data[] =
{
    0x20, 0x82, 0x20, 0xfe, 0x37, 0x6f, 0xff, 0x7f, 0x68, 0x28, 0xd8
};

GLI_BITMAP invader =
{
    11,
    8,
    invader_data
};


/* Invader (large). */
const unsigned char PROGMEM invader_large_data[] =
{
    0x03, 0x80, 0x00, 0xe0, 0x01, 0xc0, 0x00, 0x70, 0x00, 0xe0, 0x00, 0x38,
    0x00, 0x0e, 0x00, 0xe0, 0x00, 0x07, 0x00, 0x70, 0x00, 0x03, 0x80, 0x38,
    0x00, 0x0f, 0xff, 0xff, 0x80, 0x07, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff,
    0xe0, 0x0f, 0xc7, 0xfc, 0x7e, 0x07, 0xe3, 0xfe, 0x3f, 0x03, 0xf1, 0xff,
    0x1f, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xc7, 0xff, 0xff, 0xc7, 0xe3, 0xff, 0xff, 0xe3, 0xf1, 0xff,
    0xff, 0xf1, 0xf8, 0xe0, 0x00, 0x38, 0xfc, 0x70, 0x00, 0x1c, 0x7e, 0x38,
    0x00, 0x0e, 0x38, 0x03, 0xf1, 0xf8, 0x00, 0x01, 0xf8, 0xfc, 0x00, 0x00,
    0xfc, 0x7e, 0x00
};

GLI_BITMAP invader_large =
{
    33,
    24,
    invader_large_data
};


/* Invader laser. */
const unsigned char PROGMEM invader_laser_data[] =
{
    0x99
};

GLI_BITMAP invader_laser =
{
    2,
    4,
    invader_laser_data
};


/* Player. */
const unsigned char PROGMEM player_data[] =
{
    0x02, 0x00, 0x38, 0x01, 0xc0, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xe0
};

GLI_BITMAP player =
{
    13,
    7,
    player_data
};


/* Player laser. */
const unsigned char PROGMEM player_laser_data[] =
{
    0xe0
};

GLI_BITMAP player_laser =
{
    1,
    3,
    player_laser_data
};
