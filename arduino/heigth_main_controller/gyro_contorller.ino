#include <ITG3200.h>

ITG3200 gyro;

void gyro_setup(){ 
  gyro.init();
  lcd_gyro_calibrate();

}

void gyro_set_screen_color(){
  int16_t x,y,z;
  gyro.getXYZ(&x,&y,&z);  

  Serial.print("values of X , Y , Z: ");
    Serial.print(x);
   Serial.print(" , ");
   Serial.print(y);
   Serial.print(" , ");
   Serial.println(z);
    
  lcd_set_color(abs(x)/10, abs(y)/10, abs(z)/10);
}



