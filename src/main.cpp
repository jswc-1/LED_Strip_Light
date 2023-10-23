#include <FastLED.h>

#define LED_PIN     2

// Information about the LED strip itself
#define NUM_LEDS    500
#define CHIPSET     WS2811
#define COLOR_ORDER BRG
CRGB leds[NUM_LEDS];

#define BRIGHTNESS  20
#define MINBRIGHTNESS 2

#define TEMPERATURE_1 Candle

#define TEMPERATURE_2 Halogen

// How many seconds to show each temperature before switching
#define DISPLAYTIME 10
// How many seconds to show black between switches
#define BLACKTIME   0
#define RUNTIME 100000

unsigned long starttime;
unsigned long endtime;

void ChangeColor(int r, int g, int b)
{
  for(int x = 0; x < NUM_LEDS; x++){
    leds[x] = CRGB(r,g,b);
   }


   for(int x = MINBRIGHTNESS; x < BRIGHTNESS; x++){
    FastLED.setBrightness( x );
    FastLED.show();
    delay(500);
   }
  
  for(int x = BRIGHTNESS; x > MINBRIGHTNESS; x--){
    FastLED.setBrightness( x );
    FastLED.show();
    delay(500);
   } 
}





void Chase()
{
  
  FastLED.setBrightness( 15 );
  int NUM_COLORS = 4;
  CHSV myColors[] = {CHSV(0, 255, 255), CHSV(95, 255, 255), CHSV(45, 255, 255), CHSV(255, 0, 255)};
  int j = 0; 
  
  starttime = millis();
  endtime = starttime;
  while ((endtime - starttime) <=RUNTIME) // do this loop for up to 1000mS
  {
    
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = myColors[(i + j) % NUM_COLORS];  // mod restricts the color number
    }
    FastLED.show();
  
    j = (j + 1) %  NUM_COLORS;                // Cycle through the starting LED#


    
    delay(1000);
    
    endtime = millis();
  }
}

void Rainbow()
{
  FastLED.setBrightness( BRIGHTNESS );
  starttime = millis();
  endtime = starttime;
  while ((endtime - starttime) <=RUNTIME) // do this loop for up to 1000mS
  {
     // draw a generic, no-name rainbow
    static uint8_t starthue = 0;
    fill_rainbow( leds, NUM_LEDS, --starthue, 20);
  
   
    FastLED.show();
    FastLED.delay(10);

     endtime = millis();
  }
  
  
}


void Fade()
{
  int FREQUENCY = 20;

  FastLED.setBrightness( BRIGHTNESS );
  starttime = millis();
  endtime = starttime;
  while ((endtime - starttime) <=RUNTIME)
  {
  for( int colorStep=0; colorStep<256; colorStep++ ) {

      int r = colorStep;  // Redness starts at zero and goes up to full
      int b = 0;  // Blue starts at full and goes down to zero
      int g = 255-colorStep;              // No green needed to go from blue to red

      for(int x = 0; x < NUM_LEDS; x++){
          leds[x] = CRGB(r,g,b);
      }
      FastLED.show();
      delay(FREQUENCY); 
  }

   for( int colorStep=0; colorStep<256; colorStep++ ) {

      int b = 0;  // Redness starts at zero and goes up to full
      int r = 255-colorStep;  // Blue starts at full and goes down to zero
      int g = colorStep;              // No green needed to go from blue to red

      for(int x = 0; x < NUM_LEDS; x++){
          leds[x] = CRGB(r,g,b);
      }

      // Display the colors we just set on the actual LEDs
      FastLED.show();

      delay(FREQUENCY); 
  }

  delay(FREQUENCY); 
  delay(FREQUENCY); 
endtime = millis();
}
  }

void setup() {
  delay( 3000 ); // power-up safety delay
  // It's important to set the color correction for your LED strip here,
  // so that colors can be more accurately rendered through the 'temperature' profiles
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( MINBRIGHTNESS );
}


void loop()
{
  //PumpkinColor
ChangeColor(247, 95, 28);
ChangeColor(255, 154, 0);
ChangeColor(136, 30, 228);
ChangeColor(133, 226, 31);





  //ChangeColor(222, 120, 58);
  // Rainbow();
  // ChangeColor( 255, 0, 0);
  // Fade();
  // ChangeColor( 0, 255, 0);
  // Chase();
  ChangeColor( 0, 0, 255);
}