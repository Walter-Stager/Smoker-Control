// which analog pin to connect
#define THERMISTORPIN A0
// resistance at 25 degrees C
#define THERMISTORNOMINAL 53900
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 22.611
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 9830

//#define THERMISTORPIN2 A1
//#define THERMISTORNOMINAL2 50000
//#define TEMPERATURENOMINAL2 25
//#define BCOEFFICIENT2 3950
//#define SERIESRESISTOR2 10000

//#define THERMISTORPIN3 A2
//#define THERMISTORNOMINAL3 50000
//#define TEMPERATURENOMINAL3 25
//#define BCOEFFICIENT3 3950
//#define SERIESRESISTOR3 10000
 
int samples[NUMSAMPLES];
 
void setup(void) {
  Serial.begin(9600);
  analogReference(EXTERNAL);
}
 
void loop(void) {
  uint8_t i;
  float average;
 
  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(THERMISTORPIN);
   delay(10);
  }
 
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
 
  Serial.print("Average analog reading "); 
  Serial.println(average);

//-----THERMISTOR1--------------------------------------------------------------------------------------------------------------
 
  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
  Serial.print("Thermistor resistance "); 
  Serial.println(average);
 
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C

  Serial.print("Temperature "); 
  Serial.print(steinhart);
  Serial.println(" *C");

//-----THERMISTOR2--------------------------------------------------------------------------------------------------------------

//  // convert the value to resistance
//  average = 1023 / average - 1;
//  average = SERIESRESISTOR2 / average;
//  Serial.print("Thermistor resistance "); 
//  Serial.println(average);
//  
//  float steinhart2;
//  steinhart2 = average / THERMISTORNOMINAL2;     // (R/Ro)
//  steinhart2 = log(steinhart2);                  // ln(R/Ro)
//  steinhart2 /= BCOEFFICIENT2;                   // 1/B * ln(R/Ro)
//  steinhart2 += 1.0 / (TEMPERATURENOMINAL2 + 273.15); // + (1/To)
//  steinhart2 = 1.0 / steinhart2;                 // Invert
//  steinhart2 -= 273.15;                         // convert to C
//
//  Serial.print("Temperature "); 
//  Serial.print(steinhart2);
//  Serial.println(" *C");

//-----THERMISTOR3--------------------------------------------------------------------------------------------------------------

//  // convert the value to resistance
//  average = 1023 / average - 1;
//  average = SERIESRESISTOR3 / average;
//  Serial.print("Thermistor resistance "); 
//  Serial.println(average);
//  
//  float steinhart3;
//  steinhart2 = average / THERMISTORNOMINAL3;     // (R/Ro)
//  steinhart2 = log(steinhart3);                  // ln(R/Ro)
//  steinhart2 /= BCOEFFICIENT3;                   // 1/B * ln(R/Ro)
//  steinhart2 += 1.0 / (TEMPERATURENOMINAL3 + 273.15); // + (1/To)
//  steinhart2 = 1.0 / steinhart3;                 // Invert
//  steinhart2 -= 273.15;                         // convert to C
//
//  Serial.print("Temperature "); 
//  Serial.print(steinhart3);
//  Serial.println(" *C");
 
  delay(1000);
}
