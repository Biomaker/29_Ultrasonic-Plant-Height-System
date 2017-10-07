const char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
const int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };


void speaker_play_tone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(SPEAKER_PIN, HIGH);
    delayMicroseconds(tone);
    digitalWrite(SPEAKER_PIN, LOW);
    delayMicroseconds(tone);
  }
}

void speaker_play_note(char note, int duration) {
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      speaker_play_tone(tones[i], duration);
    }
  }
}
void speaker_setup(){
  pinMode(SPEAKER_PIN, OUTPUT);
    
}
