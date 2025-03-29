#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//  BME280 Stuff //
Adafruit_BME280 bme; // using I2C
#define SEALEVELPRESSURE_HPA (1015.3)

// SD1306 OLED Stuff //
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int displayTime = 1500;

void printValues();
void displayValues();

void setup() {
    ///////////////////////////////////////
    // Start with initializing BME280 stuff
    Serial.begin(9600);
    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));

    unsigned status;
    
    // default settings
    status = bme.begin();  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
    
    Serial.println("-- Default Test --");
    //sensorTime = 5000;  // sensor polling time (in ms)
    //displayTime = 5000; // display timer

    Serial.println();
  //////////////////////////////////////
  // Now initialize SD1306 OLED stuff

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 2 seconds
  display.clearDisplay();
  //////////////////////////////////////
}

void loop() { 
    printValues();
    displayValues();
    delay(displayTime);
}

// Function to print BME280 values to Serial
void printValues() {
    Serial.print("Sensor ID = 0x");
    Serial.println(bme.sensorID());

    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}

// Function to print BME280 values to SSD1306 Display
void displayValues() {
  display.clearDisplay();

  display.setTextSize(2); // draws 2x-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.print("T "); display.print(bme.readTemperature()); display.println("C");
  display.print("H "); display.print(bme.readHumidity()); display.println("%");
  display.print("P "); display.print(bme.readPressure()); display.println("hPa");
  display.display();
}
