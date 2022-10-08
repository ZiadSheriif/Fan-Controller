/******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: source file for the LM35 Temperature Sensor driver
 *
 *
 * Auhtor: Ziad-Sherif
 *******************************************************************************/

#include "lm35_sensor.h"

#include "adc.h"

#include <util/delay.h>
/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(ADC_ConfigType *ptr_ConfigType)
{
    uint8 temp_value = 0;

    uint16 adc_value = 0;

    /* Read ADC channel where the temperature sensor is connected */
    adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);

    /* Calculate the temperature from the ADC value*/
    if (ptr_ConfigType->ref_volt == INTERNAL)
        temp_value = (uint8)(((float)adc_value * SENSOR_MAX_TEMPERATURE * 2.56) / (ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLT_VALUE));
    else if (ptr_ConfigType->ref_volt == AREF)
        temp_value = (uint8)(((uint32)adc_value * SENSOR_MAX_TEMPERATURE * 5) / (ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLT_VALUE));
    else if (ptr_ConfigType->ref_volt == AVCC)
        temp_value = (uint8)(((uint32)adc_value * SENSOR_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE) / (ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLT_VALUE));

    return temp_value;
}
