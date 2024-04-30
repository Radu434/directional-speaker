#define PWM_OUT 11
#define ANALOG_IN A0
int TOP_VAL = 400  // 16 000 000HZ / 400 = 40 000Hz
  uint16_t nextDuty = 0;
void setup() {
  pinMode(PWM_OUT, OUTPUT);   //set pint 11 as output (timer1 pwm output)_
  pinMode(ANALOG_IN, INPUT);  //set A0 as an input pim
  cli();                      //stop interrupts
  TIMSK1 = 0;                 //disable interrupts
  TCNT1 = 0;                  //initialize counter value as 0
  TCCR1A = B00000000;         //zero TCCR1A
  TCCR1B = B00000000;         //zero TCCR1B
  //TCCR1A = B01000011;
  //TCCR1B = B00011001;

  TCCR1A |= (1 << wGM11) | (1 << WGM10) | (1 << COM1A0);  //output compare match on TCNT == OC1A
  TCCR1B |= (1 << wGM12) | (1 << WGM13) | (1 << CS10);    //prescaler set to 1; Fast PWM
  OCR1A = TOP_VAL;                                        //set output capture register val to 400
  TIMSK1 = (1 << OCIE1A);                                 //enable interrupts
  sei();                                                  //start interrupts
}
ISR(TIMER1_COMPA_vecy) {
  nextDuty = (uint16_t)map(analogRead(ANALOG_IN), 0, 4095, TOP_VAL / 2 - 1)  //read pin A0 and map it from 0-4095 to 0-199
    OCR1A = nextDuty + TOP_VAL / 2;                                          //set next duty cycle to vary according to nextDUty, inside a modula
}
void loop() {
}