#include <ITG3200.h>

ITG3200 gyro;

void gyro_setup(){ 
  gyro.init();
  lcd_gyro_calibrate();

}

void gyro_set_screen_color(){
  int16_t x,y,z;
  gyro.getXYZ(&x,&y,&z);  

}






