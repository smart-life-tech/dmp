#include <DPM8600.h>
int Enable_pin = 8;
DPM8600 converter(1);
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
    Serial1.begin(9600);
    Serial.begin(9600);
    delay(1000);
    digitalWrite(Enable_pin, HIGH);
    // Initating power converter
    int begins = converter.begin(Serial1, 10);
    if (!begins)
    {
        /* code */
        Serial.println("the controller was not initailized!!");
    }
    else
    {
        Serial.println("the controller  is well  initailized!! :)");
    }

    // Setting both Voltage and Current to 2V and 0.1A respectively
    converter.writeVC(25, 10);
    pinMode(13, OUTPUT); // re
    pinMode(14, OUTPUT); // de
}

void loop()
{

    // Turn on the power
    towrite();
    converter.power(true);
    toread();
    delay(1000);
    //  Read voltage if we want to.
    //  Measurements should be taken at least 0.5s after power on, as converter needs time to adjust
    /*
    'v' or 'V' - returns voltage in Volts.
  'c' or 'C' - returns current in Amps.
  'p' or 'P' - returns power state. 0 - power off, 1 - power on.
  's' or 'S' - returns CC / CV status. 0 - CV, 1 - CC.
  'm' or 'M' - returns max current of the power converter in Amps (e.g. 5, 8, 16 or 24).
  't' or 'T' (or any other character) - returns the internal temperature of the power converter in Celcius.*/
    v = converter.read('v');
    Serial.print("volatge :");
    Serial.println(v);
    // Turn off the power
    towrite();
    converter.power(false);
}
