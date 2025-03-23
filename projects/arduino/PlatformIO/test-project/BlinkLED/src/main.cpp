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
    void Bright(int brightness);

  private:
    int ledPin;
    int brightness = 255;
};

LED::LED(int pin) : ledPin(pin) {}

void LED::On() { analogWrite(ledPin, 255); }

void LED::Off() { analogWrite(ledPin, 0); }

void LED::Bright(int brightness) {
  // Brightness = 0 - 255
  analogWrite(ledPin, brightness);
}

void pattern1();
void pattern2();

// define LED pins
#define LED_1 9
#define LED_2 10
#define LED_3 11

// define Button
#define BUTTON_PIN 7
// Handle button with debounce
#define DEBOUNCE_TIME 50 // Debounce time, increase if output flickers
int last_steady_state = LOW;        // the previous steady state from the input pin
int last_flickerable_state = LOW;   // the previous flickerable state from the input pin
int current_state;                  // the current reading from the input pin
unsigned long last_debounce_time = 0; // the last time the output pin was toggled


// Create LED Objects
LED red(LED_1);
LED yellow(LED_2);
LED green(LED_3);

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
  pattern1();
  pattern2();
}

void pattern1()
{
// Turn them on
  red.On();
  delay(1000);
  yellow.On();
  delay(1000);
  green.On();
  delay(1000);
  // Turn them off
  red.Off();
  delay(1000);
  yellow.Off();
  delay(1000);
  green.Off();
  delay(1000);
}

void pattern2()
{
  int i = 0;
  while (i < 1)
  {
    for (int j = 0; j < 255; j += 3)
    {
      red.Bright(j);
      yellow.Bright(j);
      green.Bright(j);
      delay(25);
    }
    ++i;
  }
  red.Off();
  yellow.Off();
  green.Off();
  delay(250);
}