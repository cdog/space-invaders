//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#ifndef GLI_H
#define GLI_H


typedef struct GLI_BITMAP
{
    unsigned char Width;
    unsigned char Height;
    const unsigned char *pData;
} GLI_BITMAP, *PGLI_BITMAP;


typedef struct GLI_FONT
{
    unsigned char CharWidth;
    unsigned char CharHeight;
    unsigned char cbCharSize;
    unsigned char CharCodeStart;
    const unsigned char *pData;
} GLI_FONT, *PGLI_FONT;


//------------------------------------------------------------------------------
#define GLI_COLOR_BLACK 0x00
#define GLI_COLOR_WHITE 0xff


//------------------------------------------------------------------------------
void GLI_Initialize(void);

void GLI_Present(void);

void GLI_Clear(unsigned char Color);

void GLI_SetPixel(unsigned char x, unsigned char y, unsigned char Color);

void GLI_DrawBitmap(unsigned char x, unsigned char y, PGLI_BITMAP pBitmap);

void GLI_DrawString(unsigned char x, unsigned char y, PGLI_FONT pFont, const char *pszString);


#endif
