#include "Arduino.h"

/*
! For Bright/Fade, make sure LED's are plugged into PWM pins
*/

class LED
{
  public:
    LED(int ledPin);
    void On();
    void Off();

  private:
    int ledPin;
};

LED::LED(int pin) : ledPin(pin) {}

void LED::On() { digitalWrite(ledPin, HIGH); }

void LED::Off() { digitalWrite(ledPin, LOW); }

void roll_die();

// define LED pins
#define LED_1 2
#define LED_2 3
#define LED_3 4
#define LED_4 7
#define LED_5 8
#define LED_6 10
#define LED_7 12

// define Button
#define BUTTON_PIN 13
// Handle button with debounce
#define DEBOUNCE_TIME 50 // Debounce time, increase if output flickers
int last_steady_state = LOW;        // the previous steady state from the input pin
int last_flickerable_state = LOW;   // the previous flickerable state from the input pin
int current_state;                  // the current reading from the input pin
unsigned long last_debounce_time = 0; // the last time the output pin was toggled


// Create LED Objects
LED L1(LED_1);
LED L2(LED_2);
LED L3(LED_3);
LED L4(LED_4);
LED L5(LED_5);
LED L6(LED_6);
LED L7(LED_7);  // middle green LED

void setup()
{
  // initialize serial communication at 9600 bps
  Serial.begin(9600);
  // initialize LED digital pins as an output.
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  // initialize the pushbutton pin as a pull-up input
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{
   // read the state of the switch/button:
  current_state = digitalRead(BUTTON_PIN);

  // If the switch/button changed, due to noise or pressing:
  if (current_state != last_flickerable_state)
  {
    // reset the debouncing timer
    last_debounce_time = millis();
    // save the the last flickerable state
    last_flickerable_state = current_state;
  }

  if ((millis() - last_debounce_time) > DEBOUNCE_TIME)
  {
    // if the button state has changed:
    if (last_steady_state == HIGH && current_state == LOW)
    {
      Serial.println("The button is pressed");
    }
    else if (last_steady_state == LOW && current_state == HIGH)
      Serial.println("The button is released");
    // save the the last steady state
    last_steady_state = current_state;
  }
  L1.On();
  delay(500);
  L1.Off();
  L2.On();
  delay(500);
  L2.Off();
  L3.On();
  delay(500);
  L3.Off();
  L4.On();
  delay(500);
  L4.Off();
  L5.On();
  delay(500);
  L5.Off();
  L6.On();
  delay(500);
  L6.Off();
  L7.On();
  delay(500);
  L7.Off();
}

void roll_die()
{
  int i = random(1, 6);
}