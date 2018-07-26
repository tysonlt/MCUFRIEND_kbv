#define USE_UTFT (defined(__AVR_ATmega2560__)||defined(__SAM3X8E__))
#if USE_UTFT
#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t BigFont[], SmallFont[];
extern uint8_t SevenSegNumFont[];

//UTFT myGLCD(model,RS,WR,CS,RST,[ALE]);  //assumes that nRD is tied high
//UTFT myGLCD(ILI9481, 38, 39, 40, 41);
UTFT myGLCD(ILI9486, 38, 39, 40, 41);
//UTFT myGLCD(R61581, 38, 39, 40, 41);

#define TFT_WHITE 0xFFFF
#define TFT_BLACK 0x0000
#define TFT_BLUE  0x001F

void setup()
{
    myGLCD.InitLCD(PORTRAIT);
    myGLCD.clrScr();
}

void WriteCmdParamN(uint16_t cmd, int8_t N, uint8_t *block)
{
    cbi(myGLCD.P_CS, myGLCD.B_CS);
    myGLCD.LCD_Write_COM(cmd);
    while (N-- > 0) {
        myGLCD.LCD_Write_DATA(*block++);
    }
    sbi(myGLCD.P_CS, myGLCD.B_CS);
}

char *msgs[] = {
    "0: Flip Vert",
    "1: Flip Horiz",
    "2: Horiz refresh",
    "3: RGB-BGR order",
    "4: Vert refresh",
    "5: Row Col Xchange",
    "6: Column Order",
    "7: Row Order",
};

void pic(int w, int h, uint16_t color, char *msg, int xx, int yy)
{
    myGLCD.clrScr();
    myGLCD.setColor(color);
    myGLCD.drawRect(0, 0, w - 1, h - 1);
    myGLCD.drawRect(xx, yy, w - xx - 1, h - yy - 1);
    myGLCD.setFont(SmallFont);
    myGLCD.print("TOP",  xx + 2, yy / 2);
    myGLCD.print("BOTTOM",  xx + 2, h - yy / 2);
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.print("4", xx, yy);
    myGLCD.setFont(SmallFont);
    myGLCD.print(msg, xx + 2, h / 2);
}

void loop()
{
    uint8_t initval = 0x0A;     //what is in your initlcd.h for 0x36

    int w = myGLCD.getDisplayXSize(), h = myGLCD.getDisplayYSize();
    uint8_t i = 0, madctl;
    WriteCmdParamN(0x20, 0, &madctl);  //INVOFF
    //    WriteCmdParamN(0x21, 0, &madctl);  //INVON
    for (i = 0; i < 8; i++) if (initval & (1 << i)) msgs[i][2] = '!';
    for (i = 0; i < 8; i++) {
        WriteCmdParamN(0x36, 1, &initval);
        pic(w, h, TFT_WHITE, msgs[i], 32, 32);
        delay(2000);
        madctl = (1 << i) ^ initval;
        WriteCmdParamN(0x36, 1, &madctl);
        pic(w, h, TFT_BLUE, msgs[i], 32, 32);
        delay(5000);
    }
}
#endif

