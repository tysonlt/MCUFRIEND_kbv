#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

//select height.  e.g. ID_320 for a 240x320 screen
#define ID_nnn     ID_320

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.print("MCUFRIEND_kbv version:");
    Serial.println(MCUFRIEND_KBV_H_);
}

uint16_t ID_220[] = {
    0x9225, 0x9226,
};

uint16_t ID_320[] = {
    0x8347, 0x4747, 0x7575, 0x9595,
    0x5252, 0x6767, 0x9302, 0x9320,
    0x9325, 0x9328, 0x9329, 0x9331,
    0x9335, 0x9338, 0x9340, 0x9341,
    0x4532, 0x4535, 0x1505, 0xB505,
    0xC505, 0x1520, 0x1526, 0x1580,
    0x6809, 0x0139, 0x0154, 0x5408,
    0x1289, 0x7783, 0x7789, 0x8230,
    0x1602, 0xAC11, 0x2053, 0x8031,
};
uint16_t ID_400[] = {
    0x5252, 0x0065, 0x9326, 0x9327,
    0xB509, 0x5420, 0x7793,
};
uint16_t ID_480[] = {
    0x1581, 0x6814, 0x7796, 0x1511,
    0x9090, 0x0099, 0x8357, 0x9481,
    0x9486, 0x9487, 0x9488, 0x5310,
    0x1581, 0x6814, 0x7796, 0x1511,
};

void loop()
{
    uint16_t ID, *table, sz;
    table = ID_nnn;
    sz = sizeof(ID_nnn) / sizeof(ID_nnn[0]);
    for (int i = 0; i < sz; i++) {
        ID = table[i];
        delay(500);
        tft.reset();
        delay(500);
        tft.begin(ID);
        int ret = tft.width();
        Serial.print("ID = 0x");
        Serial.print(ID, HEX);
        Serial.print(" returns ");
        Serial.println(ret);
        if (ret == 0) continue;
        tft.fillScreen(0x001F);
        tft.setTextSize(5);
        tft.setCursor(0, tft.height() / 2);
        tft.print(ID, HEX);
        delay(1000);
    }
    tft.reset();
    Serial.println("Done");
    while (1) ;
}
