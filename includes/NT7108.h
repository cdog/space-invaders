//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#ifndef NT7108_H
#define NT7108_H


#include <avr/io.h>


//------------------------------------------------------------------------------
// Data and control ports
//------------------------------------------------------------------------------
#define NT7108_DATA_DDR         DDRA
#define NT7108_DATA_PORT        PORTA
#define NT7108_DATA_PIN         PINA

#define NT7108_CTRL_DDR         DDRC
#define NT7108_CTRL_PORT        PORTC


//------------------------------------------------------------------------------
// Control port bits
//------------------------------------------------------------------------------
#define NT7108_CS1              PC2
#define NT7108_CS2              PC3
#define NT7108_RST              PC1
#define NT7108_RW               PC5
#define NT7108_DI               PC4
#define NT7108_E                PC6
#define NT7108_LED              PC7


//------------------------------------------------------------------------------
// Instructions
//------------------------------------------------------------------------------
#define NT7108_DISPLAY_ON       0x3f
#define NT7108_DISPLAY_OFF      0x3e

#define NT7108_Y_ADDRESS(y)     (0x40 | (((unsigned char)(y)) & 0x3f))
#define NT7108_X_ADDRESS(x)     (0xb8 | (((unsigned char)(x)) & 0x07))
#define NT7108_Z_ADDRESS(z)     (0xc0 | (((unsigned char)(z)) & 0x3f))

#define NT7108_ADDRESS(y)       NT7108_Y_ADDRESS(y)
#define NT7108_PAGE(x)          NT7108_X_ADDRESS(x)
#define NT7108_START_LINE(z)    NT7108_Z_ADDRESS(z)


//------------------------------------------------------------------------------
// Status read
//------------------------------------------------------------------------------
#define NT7108_IS_BUSY(s)       ((s) & (1 << PA7))
#define NT7108_IS_ON(s)         ((s) & (1 << PA5))
#define NT7108_IS_OFF(s)        (!IS_ON(s))
#define NT7108_IS_RESET(s)      ((s) & (1 << PA4))


//------------------------------------------------------------------------------
#define NT7108_DELAY() __asm__ __volatile__ ("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop")


//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void          NT7108_Initialize      (void);
void          NT7108_WriteInstruction(unsigned char ChipSelect, unsigned char Data);
void          NT7108_WriteData       (unsigned char ChipSelect, unsigned char Data);
unsigned char NT7108_ReadStatus      (unsigned char ChipSelect);
unsigned char NT7108_ReadData        (unsigned char ChipSelect);


#endif
