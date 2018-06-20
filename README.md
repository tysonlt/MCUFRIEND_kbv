#Nucleo L433 on MBED

@shadow12348
ADA_GFX and STM32 files in extras/unused

Life is much easier if you Fork the MCUFRIEND_kbv project from GitHub to your Arduino User libraries folder.
Then you can swap Branch from Master to Nucleo-L433-on-MBED easily.

Alternatively,   you can select the Branch and save as a ZIP.
The Arduino can install a library from ZIP but it is best to delete any previous version directory

I suggest that you install/update the STM32 Core from the Arduino Board Manager.
1. IDE: File->Preferences: click on the "preferences.txt".   
2. This opens File Explorer on the "hidden" directory
3. You will find the STM32 Core tree under packages. e.g. packages\STM32\hardware\stm32\1.2.0
4. Replace boards.txt (or just add the L433 entry)
5. Copy the new variant directory(s) to variants
6. Start the IDE.
7. Build blinky
8. Build graphictest_kbv from examples
9. I created the L433 variant completely blind.   It is UNTESTED
10. Continue discussion under GitHub  Issues.
11. If you need help with creating a MBED project,   say so.
12. I don't want to duplicate the Arduino examples for MBED.
13. It is much easier to stick with the Arduino IDE.   Your shield runs on Uno, Mega, ...

This Branch is short-lived.   I will remove it when you have success.

#MCUFRIEND_kbv 
Library for Uno 2.4, 2.8, 3.5, 3.6, 3.95 inch mcufriend  Shields

1. The Arduino Library Manager should find and install MCUFRIEND_kbv library

2. Install the Adafruit_GFX library if not already in your User libraries.

3. Insert your Mcufriend style display shield into UNO.   Only 28-pin shields are supported.

4. Build any of the Examples from the File->Examples->Mcufriend_kbv menu.  e.g.

graphictest_kbv.ino: shows all the methods.

LCD_ID_readreg.ino:  diagnostic check to identify unsupported controllers.

MCUFRIEND_kbv inherits all the methods from 
the Adafruit_GFX class: https://learn.adafruit.com/adafruit-gfx-graphics-library/overview 
and Print class: https://www.arduino.cc/en/Serial/Print

The only "new" methods are hardware related: 
vertScroll(), readGRAM(), readPixel(), setAddrWindow(), pushColors(), readID(), begin()

readReg(), pushCommand() access the controller registers

The File layout changed with v2.9.3.   If replacing a pre-v2.9.3 library:
Please leave IDE.  Delete the existing MCUFRIEND_kbv folder.  Start the IDE.  Install from Library Manager.

HOW TO INSTALL AND USE: is now in "mcufriend_how_to.txt"

CHANGE HISTORY:         is now in "mcufriend_history.txt"
