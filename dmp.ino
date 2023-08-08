#include <DPM8600.h>

DPM8600 converter;
float v;

void toread()
{
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
}
void towrite()
{
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
}
void setup()
{
    Serial.begin(115200);
    // Initating power converter
    converter.begin(Serial);
    // Setting both Voltage and Current to 2V and 0.1A respectively
    converter.writeVC(30, 10);
    pinMode(13, OUTPUT); // re
    pinMode(14, OUTPUT); // de
}

void loop()
{

    // Turn on the power
    towrite();
    converter.power(true);
    toread();
    // delay(500);
    //  Read voltage if we want to.
    //  Measurements should be taken at least 0.5s after power on, as converter needs time to adjust
    /*
    'v' or 'V' - returns voltage in Volts.
  'c' or 'C' - returns current in Amps.
  'p' or 'P' - returns power state. 0 - power off, 1 - power on.
  's' or 'S' - returns CC / CV status. 0 - CV, 1 - CC.
  'm' or 'M' - returns max current of the power converter in Amps (e.g. 5, 8, 16 or 24).
  't' or 'T' (or any other character) - returns the internal temperature of the power converter in Celcius.*/
    v = converter.read('m');
    Serial.println(v);
    // Turn off the power
    towrite();
    converter.power(false);
}
