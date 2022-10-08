/*
 * Module : Integration Drivers
 *
 *
 * File Name: main.c
 *
 * Description: Source file which integrate all drivers with each other
 *
 * Author: Ziad-Sherif
 */

/*
 * Include all header files of driver
 */
#include "dc-motor.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "pwm.h"
#include "adc.h"
int main()
{
    DcMotor_Init();
    DcMotor_State state = stop;

    LCD_init();

    ADC_ConfigType ConfigType;
    ConfigType.ref_volt = INTERNAL;
    ConfigType.prescaler = DiVISION_BY_8;
    ADC_ConfigType *Config_Ptr = &ConfigType;
    ADC_init(Config_Ptr);

    uint8 temperature = 0, prevTemp = 0;
    while (1)
    {

        temperature = LM35_getTemperature(Config_Ptr);
        if (temperature != prevTemp)
        {
            if (temperature < 30)

            {
                LCD_clearScreen();
                state = stop;
                DcMotor_Rotate(state, 0);
                LCD_moveCursor(0, 3);
                LCD_displayString("FAN IS OFF");
                LCD_moveCursor(1, 3);
                LCD_displayString("temp = ");
                LCD_intgerToString(temperature);
                LCD_displayString(" C");
            }
            else if (temperature >= 30 && temperature < 60)
            {
                LCD_clearScreen();
                state = CLOCK_WISE;
                DcMotor_Rotate(state, 25);
                LCD_moveCursor(0, 3);
                LCD_displayString("FAN IS ON");
                LCD_moveCursor(1, 3);
                LCD_displayString("temp = ");
                LCD_intgerToString(temperature);
                LCD_displayString(" C");
            }
            else if (temperature >= 60 && temperature < 90)
            {
                LCD_clearScreen();
                state = CLOCK_WISE;
                DcMotor_Rotate(state, 50);
                LCD_moveCursor(0, 3);
                LCD_displayString("FAN IS ON");
                LCD_moveCursor(1, 3);
                LCD_displayString("temp = ");
                LCD_intgerToString(temperature);
                LCD_displayString(" C");
            }
            else if (temperature >= 90 && temperature < 120)
            {
                LCD_clearScreen();
                state = CLOCK_WISE;
                DcMotor_Rotate(state, 75);
                LCD_moveCursor(0, 3);
                LCD_displayString("FAN IS ON");
                LCD_moveCursor(1, 3);
                LCD_displayString("temp = ");
                LCD_intgerToString(temperature);
                LCD_displayString(" C");
            }
            else
            {
                LCD_clearScreen();
                state = CLOCK_WISE;
                DcMotor_Rotate(state, 100);
                LCD_moveCursor(0, 3);
                LCD_displayString("FAN IS ON");
                LCD_moveCursor(1, 3);
                LCD_displayString("temp = ");
                LCD_intgerToString(temperature);
                LCD_displayString(" C");
            }
        }
        prevTemp = temperature;
    }
}
