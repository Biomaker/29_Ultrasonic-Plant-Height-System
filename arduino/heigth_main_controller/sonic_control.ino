int SONIC_EMIT[SONIC_SENSOR_MAX];
int SONIC_ECHO[SONIC_SENSOR_MAX];
int SONIC_BUFFER[SONIC_BUFFER_SIZE];
int SONIC_BUFFER_USED = 0;
float SONIC_BUFFER_AVG = 0;
int SONIC_ID = 0;
float SONIC_SENSOR_OFFSET;

bool SONIC_BUFFER_AVG_STORED = false;
bool SONIC_BUFFER_OVERFLOW = false;

void sonic_sensor_setup(int id, int emit, int echo){
//  pinMode(port, INPUT);
  SONIC_EMIT[id] = emit;
  SONIC_ECHO[id] = echo;
  pinMode(emit,OUTPUT);
  pinMode(echo,INPUT);
  
}

float read_distance_cm(int trigger, int echo){
  
  float distance;
  digitalWrite(trigger,LOW);
  delayMicroseconds(100);
 
  // Start Measurement
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
 
  // Acquire and convert to cm
  distance=pulseIn(echo,HIGH);
  distance=distance*0.01657;
  //distance=distance*0.017;
  return distance;
}

float sonic_sensor_meassure(){
  int i;
   lcd_set_busy_color();
  sonic_sensor_clear_buffer();
  for(i = 0; i < DEFAULT_MESSURES; i ++){
    sonic_sensor_read(0);
    delay(200);
    if(!gyro_is_still(MAX_TOTAL_MOVMENT)){
      return -1;
    }
  }
  lcd_set_neutral_color();
  //sonic_sensor_print_reads();
  return sonic_sensor_average();
}

void sonic_sensor_clear_buffer(){
  SONIC_BUFFER_USED = 0;
  SONIC_BUFFER_AVG =0;
  SONIC_BUFFER_OVERFLOW = false;
  SONIC_BUFFER_AVG_STORED = false;
}

bool sonic_sensor_read(int id){
  SONIC_BUFFER[SONIC_BUFFER_USED] = (int) (read_distance_cm(SONIC_EMIT[id], SONIC_ECHO[id]) * STORE_PRECISION ) ;
  SONIC_BUFFER_AVG += SONIC_BUFFER[SONIC_BUFFER_USED];

  SONIC_BUFFER_USED++;
  if(SONIC_BUFFER_USED >= SONIC_BUFFER_SIZE){
    //Serial.print("Buffer is full! clearing");
    sonic_sensor_clear_buffer();
    SONIC_BUFFER_OVERFLOW = true;
  }
}

void sonic_sensor_print_reads(){
  int i;

  for(i=0; i<SONIC_BUFFER_USED; i++){
    Serial.print((float)SONIC_BUFFER[i]/STORE_PRECISION);
    Serial.print(",");
  }
  Serial.print(":\n"); 
  delay(1000);
  //Serial.print(SONIC_SENSOR_OFFSET);
  //Serial.print("\n");
  SONIC_ID++;
}

bool sonic_sensor_is_buffer_empty(){
  return SONIC_BUFFER_USED == 0;
}


float sonic_sensor_average(){
  //quicksort(SONIC_BUFFER, 0, SONIC_BUFFER_USED - 1);
  //return SONIC_BUFFER[SONIC_BUFFER_USED/2] / 100.0;
  int drop = SONIC_BUFFER_USED * 0.1;
  //int drop = 0;
  int i;
  float sum = 0;
  float count = 0;
  for(i = drop; i < SONIC_BUFFER_USED - drop; i++){
    sum += (float)SONIC_BUFFER[i] /STORE_PRECISION;
    count++;
  }
  return  sum/count ;
}

void sonic_sensor_set_offset(float offset){
  SONIC_SENSOR_OFFSET = offset;
}

/* replaced by luke through quicksort -> seems to be the fastest to process information on Arduino ??? */
////////////////////////////////////////
void quicksort(int a[], int l, int r){            //a=Array, l=left border, r=right border  
  if(r>l){                              //as long that more then 1 followingelement exists do
    int i=l-1, j=r;                  //Initialising the variables with the borders
    int tmp;
    for(;;){                        //endless loop; stops if i>=j
      while(a[++i]<a[r]);                  //inkrem., until found bigger element
      while(a[--j]>a[r] && j>i);            //dekrem., until found smaler element
      if(i>=j) break;                   //stops run if pointer meet
      tmp=a[i];                        //exchange smaller with bigger element
      a[i]=a[j];                       //exchange smaller with bigger element
      a[j]=tmp;                        //exchange smaller with bigger element
    }
    tmp=a[i];           //exchange dividing element
    a[i]=a[r];          //exchange dividing element
    a[r]=tmp;            //exchange dividing element

    quicksort(a, l, i-1);                  //recursive call of function for left
    quicksort(a, i+1, r);                  //recursive call of function for right
  }
}
