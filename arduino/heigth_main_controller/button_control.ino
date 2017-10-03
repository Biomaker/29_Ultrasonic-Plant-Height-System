void button_setup(int port){
  pinMode(port, INPUT);
}

bool button_is_pressed(int port){
  int result =  digitalRead(port);
  return result==HIGH?true:false;
}
