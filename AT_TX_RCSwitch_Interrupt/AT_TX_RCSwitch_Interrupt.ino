/*
 * Use 8mhz internal oscillator
 */

#include <RCSwitch.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

const int switchPin = PB2;
const int statusLED = PB1;
const int txPin = PB0;


RCSwitch mySwitch = RCSwitch();

void setup() {
  mySwitch.enableTransmit(txPin);
  mySwitch.setProtocol(1);
  mySwitch.setRepeatTransmit(15);

  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH);
  pinMode(statusLED, OUTPUT);
}

void loop() {
  sleep();
  
  mySwitch.switchOn(1, 1);
  delay(100);
  mySwitch.switchOn(1, 2);
  
  digitalWrite(statusLED, HIGH);
  delay(10);
  digitalWrite(statusLED, LOW);
 
}

void sleep() {

    GIMSK |= _BV(PCIE);                     // Enable Pin Change Interrupts
    PCMSK |= _BV(PCINT2);                   // Use PB2 as interrupt pin
    ADCSRA &= ~_BV(ADEN);                   // ADC off
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement

    sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
    sei();                                  // Enable interrupts
    sleep_cpu();                            // sleep

    cli();                                  // Disable interrupts
    PCMSK &= ~_BV(PCINT2);                  // Turn off PB2 as interrupt pin
    sleep_disable();                        // Clear SE bit
    ADCSRA |= _BV(ADEN);                    // ADC on

    sei();                                  // Enable interrupts
}

ISR(PCINT0_vect) {
    // This is called when the interrupt occurs, but I don't need to do anything in it
}
