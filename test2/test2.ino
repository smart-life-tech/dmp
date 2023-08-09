/*
Control a DPM-8600 series power supply
Compatible with the simple serial protocol
USB Serial cable wiring:
    Red ---- (do not connect)
    Wht ------ A
    Grn ------ B
    Blk ---- GND
    */
#define QUIET -1
#define ERROR 0
#define WARN 1
#define INFO 2
#define DEBUG 3

class Dpm8600
{
private:
    int verbosity = QUIET;
    String cmd_setv = "w10=";
    String cmd_seta = "w11=";
    String cmd_setva = "w20=";
    String cmd_on = "w12=1";
    String cmd_off = "w12=0";
    String cmd_status = "r12=0";
    String cmd_temp = "r33=0";
    String cmd_getvcap = "r10=0";
    String cmd_getacap = "r11=0";
    String cmd_getvval = "r30=0";
    String cmd_getaval = "r31=0";
    String cmd_getva = "r20=0";
    String cmd_getcap = "r32=0";

public:
    Dpm8600(int verbosity = QUIET) : verbosity(verbosity) {}

    void begin()
    {
        Serial1.begin(9600);
    }

    void doCommand(const String &cmd)
    {
        String fullCmd = ":01" + cmd + ",";
        debug(fullCmd, DEBUG);
        Serial1.print(fullCmd + "\r\n");
        delay(500); // Wait for command response
    }

    String getResponse(const String &cmd)
    {
        String fullCmd = ":01" + cmd + ",";
        debug(fullCmd, DEBUG);
        Serial1.print(fullCmd + "\r\n");
        String response = "";
        while (true)
        {
            if (Serial1.available())
            {
                char c = Serial1.read();
                if (c == '\n')
                {
                    break;
                }
                response += c;
            }
        }
        return response;
    }

    void v(float volts)
    {
        String cmd = cmd_setv + String(volts, 0);
        doCommand(cmd);
    }

    void a(float amps)
    {
        String cmd = cmd_seta + String(amps, 0);
        doCommand(cmd);
    }

    void va(float volts, float amps)
    {
        String cmd = cmd_setva + String(volts, 0) + "," + String(amps, 0);
        doCommand(cmd);
    }

    void on()
    {
        doCommand(cmd_on);
    }

    void off()
    {
        doCommand(cmd_off);
    }

    void temp()
    {
        String out = getResponse(cmd_temp);
        debug(out);
    }

    void pwrstatus()
    {
        String out = getResponse(cmd_status);
        debug(out);
    }

    void getvcap()
    {
        String out = getResponse(cmd_getvcap);
        debug(out);
    }

    void getacap()
    {
        String out = getResponse(cmd_getacap);
        debug(out);
    }

    void getvval()
    {
        String out = getResponse(cmd_getvval);
        debug(out);
    }

    void getaval()
    {
        String out = getResponse(cmd_getaval);
        debug(out);
    }

    void getva()
    {
        String out = getResponse(cmd_getva);
        debug(out);
    }

    void getcap()
    {
        String out = (getResponse(cmd_getcap) == "1") ? "cc" : "cv";
        debug(out);
    }

    void debug(const String &msg, int lvl = INFO)
    {
        if (verbosity >= lvl)
        {
            Serial.println(msg);
        }
    }
};

Dpm8600 dpm(DEBUG);

void setup()
{
    Serial.begin(9600);
    dpm.begin();
    dpm.on();
    dpm.v(30.0);
    dpm.a(2.0);
}

void loop()
{
    dpm.temp();
    dpm.pwrstatus();
    dpm.getvcap();
    dpm.getacap();
    dpm.getvval();
    dpm.getaval();
    dpm.getva();
    dpm.getcap();
    delay(5000);
}
