#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

static const int RXPin = 50, TXPin = 51;
static const uint32_t GPSBaud = 9600;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // initialize the LCD library with the pins connected to the LCD shield

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
  lcd.begin(16, 2); // set up the LCD's number of columns and rows

 
}

void loop()
{
  // This sketch will display information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    /*Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);*/
    lcd.clear(); // clear the LCD display
    lcd.setCursor(0, 0);
    lcd.print("La:");
    lcd.print(gps.location.lat(), 3); // display the latitude on the left side of the first row, up to 6 decimal places
    lcd.setCursor(8, 0);
    lcd.print("Lo:");
    lcd.print(gps.location.lng(), 3); // display the longitude on the right side of the first row, up to 6 decimal places
    _delay_us(1500);
  }
  /*else
  {
    Serial.print(F("INVALID"));
  }

  

  Serial.println();*/
}
