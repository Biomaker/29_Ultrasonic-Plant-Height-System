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

bool gyro_is_still(int16_t max_movment){
  int16_t x,y,z, sum;
  gyro.getXYZ(&x,&y,&z);  

  x = abs(x);
  y = abs(y);
  z = abs(z);
  sum = x + y + z;
  
  return sum < max_movment;
}






