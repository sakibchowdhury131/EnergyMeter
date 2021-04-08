// #include "EmonLib.h"             // Include Emon Library
// EnergyMonitor emon1;             // Create an instance

int mVperAmp = 185; // use 100 for 20A Mdule and 66 for 30A Module
int RawValue = 0;
int ACSoffset = 1630;

float Vcorr = 0.9;
float ccorr = 1.0;


#define samplerate 89

String str;

int voltages[samplerate], currents[samplerate];
float tempV, tempI;
int voltage_offset = 512, current_offset = 512;
double Voltage = 0, Amps = 0, Power=0, PF;

void setup()
{
  Serial.begin(115200);


  //emon1.voltage(0, 234.26, 0);  // Voltage: input pin, calibration, phase_shift
  //emon1.current(1, 141.1);       // Current: input pin, calibration.

}

void loop()
{
  //emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  //emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)

  //emon1.calcVI(20, 2000);        // Calculate all. No.of half wavelengths (crossings), time-out
  //emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)

  //float realPower       = emon1.realPower;        //extract Real Power into variable
  //float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  //float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
  //float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  //float Irms            = emon1.Irms*100;             //extract Irms into Variable

  /*if (abs(realPower) < 15)
    {
    realPower = 0;
    }
  */
  //if (abs(supplyVoltage) < 50)
  //{
    //supplyVoltage = 0;

  //}
  /*
    if (abs(Irms) < 2 )
    {
      Irms = 0;
    }
  */

  //Serial.print(realPower/1000);
  //Serial.print(" ");
  // Serial.print(supplyVoltage);

  // Serial.print(" ");
  //Serial.println(powerFActor);
 
  
  for (int i = 0; i < samplerate; i++)
  {
    voltages[i] = analogRead(A2);
    currents[i] = analogRead(A1);
    
  }
  
  Voltage = 0;
  Amps = 0;
  
    for (int i = 0; i < samplerate; i++)
  {
    Voltage += voltages[i];
    Amps+= currents[i];
  }
  
  Voltage/=samplerate;
  Amps/=samplerate;
  
      for (int i = 0; i < samplerate; i++)
  {
    voltages[i]-=Voltage;
    currents[i]-=Amps;
  }
  
  Voltage = 0;
  Amps = 0;
  Power = 0;
  
  for (int i = 0; i < samplerate; i++)
  {
    //Serial.println(voltages[i]);
    tempV = 5*(11.0*220.0/6)*(voltages[i])/1023.0*Vcorr;
    tempI = (5000.0*(currents[i])) / (1023.0*mVperAmp)*ccorr ; // Gets you mV
    Serial.print(tempV); Serial.print("    "); Serial.println(tempI);
    Power += tempV*tempI;
    
    Voltage = Voltage + pow(tempV,2);
    Amps = Amps + pow(tempI, 2);
  }
  
  Voltage = sqrt(Voltage/samplerate);
  Amps = sqrt (Amps / samplerate);
  Power/=samplerate;
  

  //Serial.print("Raw Value = " ); // shows pre-scaled value
  //Serial.print(RawValue);
  //Serial.print("\t mV = "); // shows the voltage measured
  //Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
  //Serial.print("\t Amps = "); // shows the voltage measured
  //Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point
  //delay(100);


  //Serial.print("Raw3 " ); // shows pre-scaled value
  //Serial.print(Raw3);
  //Serial.print("\t mV = "); // shows the voltage measured
  //Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
  //Serial.print("\t Amps = "); // shows the voltage measured
  //Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point
  //delay(100);

  //str = "Real power : " + String (supplyVoltage * Amps * powerFActor) + "Watt" + "  " + "Current :" + String (Amps) + "A" + "  " + "Supply Voltage:" + String (supplyVoltage) + "Volts" + "  " + "Power Factor :" + String (powerFActor) ;
  /*
    long int realPower1=(long int)realPower;
    long int powerFActor1=(long int)powerFActor;
    long int supplyVoltage1=(long int)supplyVoltage*1000;
    long int Irms1=(long int)Irms*1000;

    String stringOne=String(realPower1);
    String stringTwo=String(powerFActor1);
    String stringThree=String(supplyVoltage1);
    String stringFour=String(Irms1);

    String msg = "s"+stringOne + "a" + stringTwo + "k" + stringThree + "i" + stringFour + "b";
  */
  Serial.print(Voltage);
  Serial.print(' ');
  Serial.print(Amps);
  Serial.print(' ');
  Serial.print(Power);
  Serial.print(' ');
  float pf = (Power/(Voltage*Amps));
  Serial.println (pf); 
  //display.clearDisplay();
  
/*
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  //display.print(F("Power Real:"));
  //display.print(supplyVoltage * Amps * powerFActor);
  //display.println(F("W"));
  display.print(F("Voltage:"));
  display.print(Voltage);
  display.println(F("V"));
  display.print(F("Current:"));
  display.print(Amps);
  display.println(F("A"));
  //display.print(F("Power Factor:"));
  //display.println(powerFActor);

  display.display();
 
  */

   str = "Real power : " + String (Power) + "Watt" + "  " + "Current :" + String (Amps) + "A" + "  " + "Supply Voltage:" + String (Voltage) + "Volts" + "  " + "Power Factor :" + String (pf) ;
   Serial.print (str);
   delay (2000);
   
}
