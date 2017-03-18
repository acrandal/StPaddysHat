// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      31

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);


int delayval = 500; // delay for half a second

int curr_light = 0;

int curr_show = 0;
int last_rand_addr = 0;

//***************************************************************************************************//
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(25);
  
  randomSeed(analogRead(0));
  allOff();
}


// Turn off a single light
void turnOff( int addr )
{
  pixels.setPixelColor(addr, pixels.Color(0,0,0));
}


// Turn off ALL lights
void allOff()
{
  for( int curr_light = 0; curr_light < NUMPIXELS; curr_light++ )
    turnOff( curr_light );
  pixels.show();
}

void setLight( int addr, int red, int green, int blue, int white=0 )
{
  pixels.setPixelColor(addr, pixels.Color(red, green, blue, white));
}


// show random
void show_random()
{
  for( int i = 0; i < 10; i++ ){
    setLight( random(NUMPIXELS), random(50), random(100), random(50) );
    delay(20);
    pixels.show();
  }
  delay(1000);
  do_wipe(100);
  allOff();
}


void show_smile()
{
  allOff();
 setLight(16, 0, 20, 0);
 setLight(20, 0, 20, 0);
 setLight(24, 0, 20, 0);
 //setLight(28, 0, 20, 0);
 //setLight(29, 0, 20, 0);
 for( int i = 8; i < 13; i++ )
 {
  setLight(i, 0, 20, 0);
 }
 pixels.show();
 delay(2000);
 do_wipe(50);
  
}

// Simple increment series for "wiping" all pixels
void do_wipe( int wipe_delay )
{
  for( int curr_light = 0; curr_light < NUMPIXELS; curr_light++ )
  {
    if(curr_light > 0)
      turnOff( curr_light - 1 );
    setLight(curr_light, 0, 20, 0);
    pixels.show(); 
    delay(wipe_delay); 
  }
  turnOff( NUMPIXELS - 1 );
}


// Simple increment series for testing and light counting
void show_collision()
{
  for( int curr_light = 0; curr_light < NUMPIXELS; curr_light++ )
  {
    if(curr_light > 0)
      turnOff( curr_light - 1 );
      turnOff( NUMPIXELS - curr_light );
    setLight(curr_light, 0, 20, 0);
    setLight(NUMPIXELS - curr_light - 1, 0, 100, 0);
    pixels.show(); 
    delay(250); 
  }
  turnOff( NUMPIXELS - 1 );
}


// A simple blinking cursor
void show_cursor()
{
  allOff();
  for( int flash_count = 0; flash_count < 10; flash_count++ )
  {
    if( flash_count % 2 == 0 )
    {
      allOff();
    }else{
      for( int i = 24; i < 31; i++ )
      {
        setLight(i, 0, 20, 0);
        pixels.show();
      }
    }
    delay(750);
  }
  allOff();  
}

// Fireworks!
void show_fireworks()
{
  allOff();
  // Pre launch
  setLight(0, 80, 30, 0);
  pixels.show();    delay(250); 
  setLight(0, 80, 0, 0);
  pixels.show();    delay(250);
  turnOff(0); 
  pixels.show();    delay(250);

  int locs[14] = {-1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 14, 27, 24};
  
  // Launch series
  for(int i = 3; i < 14; i++)
  {
    setLight( locs[i], 100, 0, 0 );
    setLight( locs[i-1], 125, 60, 0 );
    setLight( locs[i-2], 30, 20, 0 );
    turnOff( locs[i-3] );
    pixels.show();
    delay(150);
  }
  turnOff( 27 );
  turnOff( 14 );
  setLight( 24, 125, 60, 0 );
  pixels.show();
  delay(200);
  
  // Fire explosion
  setLight(24, 100, 0, 0);
  for(int i = 25; i < 31; i++)
  {
    setLight(i, 80, 30, 0);
  }
  pixels.show();
  delay(150);
  setLight(24, 80, 30, 0);
  pixels.show();
  delay(150);

  allOff();  // Just center green
  setLight(24, 0, 80, 0);
  pixels.show(); delay(150);

  allOff();  // Center rim green
  for(int i = 25; i < 31; i++)
  {
    setLight(i, 0, 80, 0);
  }
  pixels.show();
  delay(500);

  // Do outer rim green
  int outerBoom[10] = {8, 9, 11, 12, 14, 16, 17, 19, 20, 22};

  for( int i = 0; i < 10; i++ )
  {
    setLight( outerBoom[i], 0, 80, 0 );
  }
  pixels.show();
  delay(250);

  // Clear inner rim
  for(int i = 25; i < 31; i++)
    turnOff( i );
  pixels.show(); delay(750);

  allOff();
  delay(250);

  for( int i = 0; i < 10; i++ )
    setLight( outerBoom[i], 0, 80, 0 );
  pixels.show();   delay(250);

  allOff();

  //delay(2000);
  // Start orange/green flow out
  // All green flow out

  allOff();
}

void show_flag_bar()
{
  allOff();
  setLight(7, 0, 80, 0);
  setLight(6, 0, 80, 0);
  setLight(5, 0, 80, 0);
  setLight(4, 80, 80, 80);
  setLight(3, 80, 80, 80);
  setLight(2, 80, 30, 0);
  setLight(1, 80, 30, 0);
  setLight(0, 80, 30, 0);
  pixels.show();
  delay(10000); // 9 seconds
}


//***************************************************************************************//
void loop() {
  show_fireworks();
  delay(1000);
  show_fireworks();
  delay(1000);

  show_flag_bar();
  allOff();
  delay(15000);
  
  //show_smile();
  //show_cursor();
  //show_random();
  //show_collision();
  //delay(1000);
}
