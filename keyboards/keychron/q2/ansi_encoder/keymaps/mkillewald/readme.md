
This is test code to show eeprom reading/writing.   

- I set up three colors to the eeprom as default values (the eeprom must be reset to apply the defaults):
    - c1 0x44, 0x00, 0xff (purple)
    - c2 0xff, 0x00, 0x4f (pink)
    - c3 0x00, 0xff, 0x00 (green)

- The values stored in the eeprom are then read from the eeprom to display pink on the Esc key, purple on the Q2 top row and green on the Q2 second row. 
- If you now power cycle the board, the row colors should remain as is. 
- When you pres Fn1+Y, it changes color 1 (c1) from purple to yellow and saves it to the eeprom.
- If you power cycle the board now, the top row remains yellow.
- reset the eeprom to get purple back on the top row.
