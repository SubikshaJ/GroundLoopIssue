  int CH1 = 12;
  int CH2 = 13;
  int VIN = A0;
  volatile byte state = LOW;
  int max_state = 0;
  int input = 0;
  int cur_max = 0;
  // volatile byte state1 = LOW;
  // volatile byte state2 = LOW;
  //volatile byte state2 = LOW;

void setup() {
  //define input & output
  // DDRB = B11111111; //port B set as output
  // DDRD = B00000000; //port D7 to D0 set as input  
  pinMode(CH1, OUTPUT);
  pinMode(CH2, OUTPUT);
  pinMode(VIN, INPUT);
  Serial.begin(9600);
  digitalWrite(CH2,LOW);
  digitalWrite(CH1,HIGH);
  // pinMode(1,OUTPUT);
  // pinMode(2,OUTPUT);
  // PCICR |= B00000100; //activate PCINT interrupt on portD
  // PCMSK0 |= B00110000; //set pins 12 & 13 as interrupt pin
  //default orange channel
  // detect low note, change to red channel
}

// void updatePin (){
//   digitalWrite(CH1, LOW);
//   digitalWrite(CH2,HIGH);
// }

int findMax(){
  max_state = 0;
  for (int i = 0; i < 1000; i++){
    input = analogRead(VIN);
    if (input > max_state){
      max_state = input;
    }
  }
  return max_state;
  
}

void loop() {
  //can change to write the output of each port for faster speed, lmk if u want me to do that
  max_state = findMax();
  if ((state == HIGH) && (max_state < 700)){
    if (max_state > (cur_max+20)){
      state = LOW;
    }
  }
  // if (max_state > 10){
  //   cur_max = max_state;
  //   max_state = findMax();
  else if (max_state >= 700){
    digitalWrite(CH1, LOW);
    digitalWrite(CH2, HIGH);
    state = HIGH;
  }
  else if ((state == LOW) || (max_state < 700)){
    digitalWrite(CH2,LOW);
    digitalWrite(CH1,HIGH);
    state = LOW;
  }
  cur_max = max_state;
  // if (max_state >= 800){
  //   updatePin();
  // }
  // else if (max_state < 500){
  //   digitalWrite(CH2,LOW);
  //   digitalWrite(CH1,HIGH);
  //   // delay(100)
  // }
  // while(max_state > 10){
  //   cur_max = max_state;
  //   max_state = findMax();
  //   if (max_state > cur_max){
  //     break;
  //   }
  Serial.println(state);

}

// ISR(PCINT0_vect) {
//   if (PIND & B00010000){
//     state2 = LOW;
//     state1 = HIGH;
//   }
//   else if (PIND & B00100000){
//     state1 = LOW;
//     state2 = HIGH;
//   }
// }
