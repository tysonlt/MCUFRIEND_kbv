#if USE_UTFT == 0
#include <MCUFRIEND_kbv.h>
#include <FreeDefaultFonts.h>

MCUFRIEND_kbv tft;

uint16_t ID;
uint8_t initval;

void setup()
{
    ID = tft.readID();
    Serial.begin(9600);
    Serial.println(ID, HEX);
    if (ID == 0) ID = 0x1581;
    yield();
    tft.begin(ID);
    tft.setRotation(0);              //PORTRAIT (default)
    tft.setTextColor(TFT_WHITE);     //default
    tft.fillScreen(TFT_BLACK);
    initval = tft.readReg(0x0B);     //what is in your initlcd.h for 0x36
}

char msgs[][20] = {
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
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(color);
    tft.drawRect(0, 0, w, h, color);
    tft.drawRect(xx, yy, w - xx * 2, h - yy * 2, color);
    tft.setFont(&FreeSmallFont);
    tft.setCursor(xx + 2, yy / 2);
    tft.print("TOP");
    tft.setCursor(xx + 2, h - yy / 2);
    tft.print("BOTTOM");
    tft.setFont(&FreeSevenSegNumFont);
    tft.setCursor(xx, yy + 50);
    tft.print("4");
//    tft.setFont(NULL);     //use 7x5 system font
    tft.setFont(&FreeSmallFont);
    tft.setCursor(xx + 2, h / 2);
    tft.print(msg);
}

void loop()
{
    int w = tft.width(), h = tft.height();
    uint8_t i = 0, madctl;
    if (ID == 0x9486) tft.pushCommand(0x21, &madctl, 0);  //INVON
    for (i = 0; i < 8; i++) if (initval & (1 << i)) msgs[i][2] = '!';
    for (i = 0; i < 8; i++) {
        tft.pushCommand(0x36, &initval, 1);
        pic(w, h, TFT_WHITE, msgs[i], 32, 32);
        delay(2000);
        madctl = (1 << i) ^ initval;
        tft.pushCommand(0x36, &madctl, 1);
        pic(w, h, TFT_BLUE, msgs[i], 32, 32);
        delay(5000);
    }
}
#endif

