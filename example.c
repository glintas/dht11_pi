#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAXTIMINGS	85
#define DHTPIN	        7

#define VERB 0

int dht11_dat[5] = { 0, 0, 0, 0, 0 };


uint8_t pollBus(uint8_t *state);
uint8_t pollBusUntil(uint8_t state);
void initDHT11(void);
 
void read_dht11_dat()
{
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	float	f; 
        uint8_t tempR;
	
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

	initDHT11();
	delay(1000);
}

void initDHT11(void)
{
  
  uint8_t laststate = HIGH;
  uint8_t counter = 0;
  
  pinMode( DHTPIN, OUTPUT );
  digitalWrite( DHTPIN, LOW );
  delay(20);
  digitalWrite( DHTPIN, HIGH );
  delayMicroseconds(40); 
  pinMode( DHTPIN, INPUT );
        
  /* laststate = digitalRead( DHTPIN ); // this should be still 1; */
  /* printf("beginning - read is %d, should be 1\n", laststate); */
  /* // poll until signal is low - xxx need to brake */
  /* counter = pollBusUntil(0); */
  /* printf("-- counter is %d, should be ~ 0\n", counter); */
  
  // count until sigal goes high
  counter = pollBusUntil(1);
  //printf("laststate is %d, should be 1\n", laststate); //this should be 1
  printf("counter is %d\n", counter);
  if ( counter >= 70 && counter <= 100  )
    {
      printf("AK low\n");
    }
  else
    {
      printf("AK low - init failed.\n");
    }

  counter = pollBusUntil(0);
  //printf("laststate is %d, should be 1\n", laststate); //this should be 1
  printf("counter is %d\n", counter);
  if ( counter >= 70 && counter <= 100  )
    {
      printf("AK high\n");
    }
  else
    {
      printf("AK high - init failed.\n");
    }
 
}

uint8_t pollBusUntil(uint8_t state)
{
  uint8_t counter = 0;
  uint8_t tempR;
  
  tempR = digitalRead( DHTPIN );
  while ( tempR != state )
    {
      counter++;
      delayMicroseconds( 1 );
      if (VERB && (counter % 10 == 0)) {
	printf("poll bus - counter is %d\n", counter);
        }
      tempR = digitalRead( DHTPIN );
      if ( counter == 255 ) {
	  return -1;
        }
     }
  return counter;
}


uint8_t pollBus(uint8_t *state)
{
  uint8_t counter = 0;
  uint8_t tempR;
  
  tempR = digitalRead( DHTPIN );
  while ( tempR == *state )
    {
      counter++;
      delayMicroseconds( 1 );
      if (VERB && (counter % 10 == 0)) {
	printf("poll bus - counter is %d\n", counter);
        }
      tempR = digitalRead( DHTPIN );
      if ( counter == 255 ) {
	  return -1;
        }
     }
  *state = tempR; // update the last state
  return counter;
}
 
int main( void )
{
	printf( "Raspberry Pi wiringPi DHT11 Temperature test program\n" );
 
	if ( wiringPiSetup() == -1 )
		exit( 1 );
 
	while ( 1 )
	{
		read_dht11_dat();
		delay( 5000 ); 
	}
 
	return(0);
}
