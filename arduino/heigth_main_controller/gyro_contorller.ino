#include <ITG3200.h>

ITG3200 gyro;

void gyro_setup(){ 
  gyro.init();
  lcd_gyro_calibrate();

}



