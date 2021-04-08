/* Author: Sakib Chowdhury */

/* ACS712 Model         Optimized Current Range              Output Sensitivity
-------------------------------------------------------------------------------

ACS712 ELC-05           +/- 5A                              185 mV/A

ACS712 ELC-20           +/- 20A                             100 mV/A

ACS712 ELC-30           +/- 30A                             66 mV/A */

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


}

void loop()
{
  
  
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
  

  Serial.print(Voltage);
  Serial.print(' ');
  Serial.print(Amps);
  Serial.print(' ');
  Serial.print(Power);
  Serial.print(' ');
  float pf = (Power/(Voltage*Amps));
  Serial.println (pf); 
  //display.clearDisplay();
  


   str = "Real power : " + String (Power) + "Watt" + "  " + "Current :" + String (Amps) + "A" + "  " + "Supply Voltage:" + String (Voltage) + "Volts" + "  " + "Power Factor :" + String (pf) ;
   Serial.print (str);
   delay (2000);
   
}
