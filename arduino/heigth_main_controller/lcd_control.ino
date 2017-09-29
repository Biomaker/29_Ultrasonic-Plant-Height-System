#include "rgb_lcd.h"
rgb_lcd lcd;


void lcd_print(int line, const char * text){
  lcd.setCursor(0,line);
  lcd.print(text);
}

void lcd_setup(){
  // set up the LCD's number of columns and rows: 
  lcd.begin(2, 16);
  lcd.clear();
  // Print a message to the LCD.
  lcd.display();
  
}


void lcd_print_processing(){
  lcd.clear();
  lcd_print(0, "Processing...");
}

void lcd_print_waiting(){
  lcd.clear();
  lcd_print(0,"Press the");
  lcd_print(1, "red button");
}

void lcd_print_measuring(){
  lcd.clear();
  lcd_print(0, "Measuring...");
}


bool lcd_print_distance(float distance){
  bool readed = false;
  bool result = false;
  lcd.clear();
  lcd.print("Save? ");
  lcd.print(distance); 
  lcd.setCursor(0,1);
  lcd.print("(Y:up/N:down)");
  /*
  while(!readed){
    lcd_key = lcd_read_button();
    switch(lcd_key){
      case btnUP:{
        result = true;
        readed = true;
        break;
      }
      case btnDOWN:{
        readed = true;
      }
    }
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  if(result){
    lcd.print("Saving          ");
  }else{
   lcd.print("Discarded       ");
  }
  lcd.setCursor(0,1);
  lcd.print(distance);
  //display_pressed_button();
  */
  return result;
}
