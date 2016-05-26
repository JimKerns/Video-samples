/* Functions to write to LCD on the LTU ERE controller board (8 bit serial interface)
Usage: 


LCD_init(); // Set up parameters for LCD

LCDGoToPosition(x,y); // position cursor at row x, column y

sprintf(StringOfCharacters,"blah blah blah %4d",val); // create string from text and numeric values to be displayed

LCDSendString(*StringOfCharacters); // display StringOfCharacters on LCD starting at cursor position


JMK 2/8/2013
*/

#ifndef LCD_H_
#define LCD_H_

extern void LCD_init(void);
extern void LCDGoToPosition(uint8_t x, uint8_t y);
extern void LCDSendString(char *StringOfCharacters);

#endif /* LCD_H_ */