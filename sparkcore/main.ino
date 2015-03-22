// This #include statement was automatically added by the Spark IDE.
#include "HttpClient.h"

// This #include statement was automatically added by the Spark IDE.
#include "HttpClient.h"

// This #include statement was automatically added by the Spark IDE.
#include "AzureMobileService.h"

#define MYSERVICE ""
#define MYKEY ""

AzureMobileService ams;


// -----------------
// Read temperature
// -----------------

// Create a variable that will store the temperature value
double temperature = 0.0;

void setup()
{

    Serial.begin(9600);
    delay(10000);
    ams.configure(MYSERVICE, MYKEY);

  // Register a Spark variable here
  Spark.variable("temperature", &temperature, DOUBLE);

  // Connect the temperature sensor to A7 and configure it
  // to be an input
  pinMode(A7, INPUT);
}

void loop()
{
  double reading = 0;
  double voltage = 0.0;


  // Keep reading the sensor value so when we make an API
  // call to read its value, we have the latest one
  reading = analogRead(A7);

  // The returned value from the Core is going to be in the range from 0 to 4095
  // Calculate the voltage from the sensor reading
  voltage = (reading * 3.3) / 4095;

  // Calculate the temperature and update our static variable
  temperature = (voltage - 0.5) * 100;
  // Multiply by 9, then divide by 5, then add 32
  temperature = (double)((temperature * 9 ) / 5 ) + 32; 
    
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "{\"temp\":\"%f\"}", temperature);
    
    String table = "temp";
    
    Serial.println("**************************************************************");
    Serial.println("Publishing data from buffer to AMS");
    Serial.println("**************************************************************");
    ams.create(table, buffer);
    delay(5000);
}