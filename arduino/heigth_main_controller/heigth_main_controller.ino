#define STORE_PRECISION 100.0f
#define SONIC_SENSOR_MAX 1
#define SONIC_BUFFER_SIZE 30
#define SONIC_EMIT_PIN 12
#define SONIC_ECHO_PIN 13
#define DEFAULT_MESSURES 20

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  sonic_sensor_setup(0, SONIC_EMIT_PIN, SONIC_ECHO_PIN);
  sonic_sensor_set_offset(0);
   Serial.print("Starting");

}

void loop() {
  int i;
  // put your main code here, to run repeatedly:
  sonic_sensor_clear_buffer();
  for(i = 0; i < DEFAULT_MESSURES; i ++){
    sonic_sensor_read(0);
  }
  //sonic_sensor_print_reads();
  Serial.print( sonic_sensor_average());
  Serial.print("\n");
  delay(1000);
  
}
