#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
long duration, inches, cm;

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 0
#define DELTAY 2
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; 

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   { 
  Serial.begin(9600); // Starting Serial Terminal
  pinMode(4,INPUT);
  pinMode(13,OUTPUT);  
  pinMode(8,OUTPUT);             
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Hello, ");
  display.display();
  delay(3000);
  display.clearDisplay();
  //display.println("How are you ?");
  //display.display();
  //delay(2000);
  //display.clearDisplay();
  
}

void loop() {
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   while(true){
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 4);
  display.print(inches);
  display.print(" inches");
  display.println("");
  display.print(cm);
  display.print(" cm");
  display.println("");
  if(digitalRead(4)==HIGH){
  display.print("motion detected");
  display.println("");
  }
  display.display();
  if (cm < 7){
    digitalWrite(13,1);
    digitalWrite(8,1);
    Serial.println("LESS THAN 7cm");
   }
   else{
    digitalWrite(13,0);
    digitalWrite(8,0); 
   }
  delay(1000);
  display.clearDisplay();
  } while(true){
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 4);
  display.print(inches);
  display.print(" inches");
  display.println("");
  display.print(cm);
  display.print(" cm");
  display.println("");
  if(digitalRead(4)==HIGH){
  display.print("motion detected");
  display.println("");
  }
  display.display();
  if (cm < 7){
    digitalWrite(13,1);
    digitalWrite(8,1);
    Serial.println("LESS THAN 7cm");
   }
   else{
    digitalWrite(13,0);
    digitalWrite(8,0); 
   }
  delay(1000);
  display.clearDisplay();
  } 
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   if (cm < 7){
    digitalWrite(13,1);
    Serial.println("LESS THAN 7cm");
   }
   else{
    digitalWrite(13,0);
   }
   delay(1000);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
