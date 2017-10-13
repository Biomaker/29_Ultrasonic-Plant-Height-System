#include "rgb_lcd.h"
rgb_lcd lcd;
#define MAX_DELAY 100


#define btnDELETE 1
#define btnSELECT 4
#define btnNONE   5
#define MIN_HEIGHT 0
#define MAX_HEIGHT 100

bool sound=false;

void lcd_print(int line, const char * text){
  lcd.setCursor(0, line);
  lcd.print(text);
}

void lcd_setup(){
  // set up the LCD's number of columns and rows: 
  lcd.begin(2, 16);
  lcd.clear();
  // Print a message to the LCD.
  lcd.display();
  
}

void lcd_print_horizontal_count(int count){
  lcd.clear();
  lcd_print(0, "Still...");
  lcd_print_int_as_float(count);
}


void lcd_print_processing(){
  lcd.clear();
  lcd_print(0, "Processing...");
}

void lcd_print_waiting(){
  lcd.clear();
  lcd_print(0, "Waiting for");
  lcd_print(1, "horizontal bar ");
}

void lcd_print_measuring(){
  lcd.clear();
  lcd_set_busy_color();
  lcd_print(0, "Measuring...");
}

void lcd_set_ok_color(){
  lcd_set_color(66,84,21); 
}

void lcd_set_nok_color(){
  lcd_set_color(216,48,32); 
}

void lcd_set_busy_color(){
  lcd_set_color(236,195,77); 
}

void lcd_set_neutral_color(){
  lcd_set_color(255,255,255);
}


int lcd_read_button(){
  if(button_is_pressed(BUTTON_DELETE   ) ) {
    lcd_set_nok_color();
    if(sound){
      speaker_play_note('e', 200);
      speaker_play_note('c', 200);
    }
    lcd_set_neutral_color();
    return btnDELETE;
  }
  if(button_is_pressed(BUTTON_SELECT) ) {
    lcd_set_ok_color();
    if(sound){
      speaker_play_note('c', 200);
      speaker_play_note('e', 200);
    }
    lcd_set_neutral_color();
    return btnSELECT;
  }
  return btnNONE;  // when all others fail, return this...
}


float lcd_get_sensor_height(int default_height){
  bool accepted = false;
  bool pressed = false;
  int value_cm = default_height;
  int lcd_delay = MAX_DELAY;
  lcd.clear();
  int lcd_key;
  
  lcd_print(0,"Sensor height");
  lcd_print(1, "          cm" );
  lcd_print_int_as_float(value_cm);
  int steps = 0; 
  int previous = 0;
  sound = false;
  while(!accepted){
    previous = value_cm;
    lcd_key = lcd_read_button();
    //lcd_pressed_button();
    switch (lcd_key){
      case btnDELETE:{
        value_cm -= steps > 10? 10:1;
        if(value_cm < MIN_HEIGHT){
          value_cm = MAX_HEIGHT;
        }
        steps++;
        break;
      }
      case btnSELECT:{
        accepted=true;
        break;
      }
      case btnNONE:{
        lcd_delay = MAX_DELAY;
        steps = 0;
        break;
      }
    } 
    if(value_cm != previous){
       lcd_print_int_as_float(value_cm);
    } 
    delay(lcd_delay);
  }
  sound = true;
  return (float)value_cm/10.0;
}



float lcd_get_baseline_height(){
  bool accepted = false;
  bool pressed = false;
  float value_cm;
  int lcd_delay = MAX_DELAY;
  int lcd_key;
  char result[8]; // Buffer big enough for 7-character float
  lcd_print_measuring();
  value_cm = sonic_sensor_meassure();
  //sonic_sensor_print_reads();
  lcd.clear();
  lcd_print(0, "Baseline height");
  lcd_print(1, "          cm" );
  dtostrf(value_cm, 6, 2, result); // Leave room for too large numbers!
  lcd_print(1, result);

  while(!accepted){
    
    lcd_key = lcd_read_button();
    switch (lcd_key){
       case btnDELETE:{
        lcd_print_measuring();
        value_cm = sonic_sensor_meassure();
        //sonic_sensor_print_reads();
        dtostrf(value_cm, 6, 2, result); 
        lcd.clear();
        lcd_print(0, "Baseline height");
        lcd_print(1, result);
        delay(lcd_delay);
        break;
      }
      case btnSELECT:{
        accepted=true;
        break;
      }
      case btnNONE:{
         lcd_delay = MAX_DELAY;
        break;
      }
    } 
  }
  return value_cm;
}

void lcd_print_int_as_float(int value){
   float val = (float)value / 10.0;
   lcd.setCursor(0,1);
   lcd.print("       ");
   lcd.setCursor(0,1);
   if(val < 100.0){
     lcd.print(" ");
   }
   lcd.print(val);
}


bool lcd_print_distance(float distance){
  bool readed = false;
  bool result = false;
  int lcd_key;
  lcd.clear();
  lcd.print("Save? ");
  lcd.print(distance); 
  lcd.setCursor(0,1);
  lcd.print("(Y:up/N:down)");
  
  while(!readed){
    lcd_key = lcd_read_button();
    switch(lcd_key){
      case btnSELECT:{
        result = true;
        readed = true;
        break;
      }
      case btnDELETE:{
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

  return result;
}

void lcd_set_color(int r, int g,int b){
  lcd.setRGB(r, g, b);  
}

void lcd_gyro_calibrate(){
  bool accepted = false;
  bool pressed = false;
  int lcd_delay = MAX_DELAY;
  int lcd_key;
  
  lcd.clear();
  lcd_print(0, "keep the bar");
  lcd_print(1, "still & press up" );
  
  while(!accepted){
    
    lcd_key = lcd_read_button();
    switch (lcd_key){
       case btnDELETE:{
        break;
      }
      case btnSELECT:{
        accepted=true ;
        lcd.clear();
        lcd_set_busy_color();
        lcd_print(0, "Calibrating");
        lcd_print(1, "gyroscope" );
        gyro.zeroCalibrate(200,10);//sample 200 times to calibrate and it will take 200*10ms 
        break;
      }
      case btnNONE:{
         lcd_delay = MAX_DELAY;
        break;
      }
    } 
  }
  return;
}
