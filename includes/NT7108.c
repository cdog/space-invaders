//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#include "NT7108.h"


//------------------------------------------------------------------------------
void NT7108_Initialize(void)
{
    NT7108_CTRL_DDR |= (1 << NT7108_CS1);
    NT7108_CTRL_DDR |= (1 << NT7108_CS2);
    NT7108_CTRL_DDR |= (1 << NT7108_RST);
    NT7108_CTRL_DDR |= (1 << NT7108_RW);
    NT7108_CTRL_DDR |= (1 << NT7108_DI);
    NT7108_CTRL_DDR |= (1 << NT7108_E);
    NT7108_CTRL_DDR |= (1 << NT7108_LED);

    NT7108_CTRL_PORT |= (1 << NT7108_CS1);
    NT7108_CTRL_PORT |= (1 << NT7108_CS2);
    NT7108_CTRL_PORT |= (1 << NT7108_RST);
    NT7108_CTRL_PORT |= (1 << NT7108_LED);

    while (NT7108_IS_RESET(NT7108_ReadStatus(NT7108_CS1)));

    while (NT7108_IS_RESET(NT7108_ReadStatus(NT7108_CS2)));
}


//------------------------------------------------------------------------------
void NT7108_WriteInstruction(unsigned char ChipSelect, unsigned char Data)
{
    while (NT7108_IS_BUSY(NT7108_ReadStatus(ChipSelect)));

    NT7108_DATA_DDR = 0xff;

    NT7108_CTRL_PORT &= ~(1 << NT7108_E);

    NT7108_CTRL_PORT &= ~(1 << NT7108_RW);

    NT7108_CTRL_PORT &= ~(1 << ChipSelect);
    NT7108_CTRL_PORT &= ~(1 << NT7108_DI);

    NT7108_DELAY();

    NT7108_CTRL_PORT |= (1 << NT7108_E);

    NT7108_DATA_PORT = Data;

    NT7108_DELAY();

    NT7108_CTRL_PORT &= ~(1 << NT7108_E);

    NT7108_DELAY();

    NT7108_CTRL_PORT |= (1 << ChipSelect);
}


//------------------------------------------------------------------------------
void NT7108_WriteData(unsigned char ChipSelect, unsigned char Data)
{
    while (NT7108_IS_BUSY(NT7108_ReadStatus(ChipSelect)));

    NT7108_DATA_DDR = 0xff;

    NT7108_CTRL_PORT &= ~(1 << NT7108_E);

    NT7108_CTRL_PORT &= ~(1 << NT7108_RW);

    NT7108_CTRL_PORT &= ~(1 << ChipSelect);
    NT7108_CTRL_PORT |= (1 << NT7108_DI);

    NT7108_DELAY();

    NT7108_CTRL_PORT |= (1 << NT7108_E);

    NT7108_DATA_PORT = Data;

    NT7108_DELAY();

    NT7108_CTRL_PORT &= ~(1 << NT7108_E);

    NT7108_DELAY();

    NT7108_CTRL_PORT |= (1 << ChipSelect);
}


//------------------------------------------------------------------------------
unsigned char NT7108_ReadStatus(unsigned char ChipSelect)
{
    NT7108_DATA_DDR = 0;
    NT7108_DATA_PORT = 0;

    NT7108_CTRL_PORT &= ~(1 << NT7108_E);

    NT7108_CTRL_PORT |= (1 << NT7108_RW);

    NT7108_CTRL_PORT &= ~(1 << ChipSelect);
    NT7108_CTRL_PORT &= ~(1 << NT7108_DI);

    NT7108_DELAY();

    NT7108_CTRL_PORT |= (1 << NT7108_E);

    NT7108_DELAY();

    NT7108_CTRL_PORT &= ~(1 << NT7108_E);

    NT7108_DELAY();

    NT7108_CTRL_PORT |= (1 << ChipSelect);

    return NT7108_DATA_PIN;
}


//------------------------------------------------------------------------------
unsigned char NT7108_ReadData(unsigned char ChipSelect)
{
    while (NT7108_IS_BUSY(NT7108_ReadStatus(ChipSelect)));

    NT7108_DATA_DDR = 0;
    NT7108_DATA_PORT = 0;

    NT7108_CTRL_PORT &= ~(1 << NT7108_E);

    NT7108_CTRL_PORT |= (1 << NT7108_RW);

    NT7108_CTRL_PORT &= ~(1 << ChipSelect);
    NT7108_CTRL_PORT |= (1 << NT7108_DI);

    NT7108_DELAY();

    NT7108_CTRL_PORT |= (1 << NT7108_E);

    NT7108_DELAY();

    NT7108_CTRL_PORT &= ~(1 << NT7108_E);

    NT7108_DELAY();

    NT7108_CTRL_PORT |= (1 << ChipSelect);

    return NT7108_DATA_PIN;
}