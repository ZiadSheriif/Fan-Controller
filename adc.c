 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 *Author: Ziad-Sherif
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = 0;
	if (Config_Ptr->ref_volt==INTERNAL)//REFS0 =1 ,REFS1 =1 for internal VREF=2.56
	ADMUX |= (1<<REFS1)|(1<<REFS0);

	else if (Config_Ptr->ref_volt==AREF)//REFS0 =0 ,REFS1 =0 for EXternal AREF
		ADMUX =0;
	else if (Config_Ptr->ref_volt==AVCC)//REFS0 =1  for EXternal AREF
		ADMUX |= (1<<REFS0);


	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock=F_CPU/8=1Mhz/8=125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA |= (1<<ADEN);

	/*
	 * configuring pre-scaler
	 */
	if(Config_Ptr->prescaler==DiVISION_BY_1)
		ADCSRA|=DiVISION_BY_1;
	else if (Config_Ptr->prescaler==DiVISION_BY_2)
		ADCSRA|=DiVISION_BY_1;
	else if (Config_Ptr->prescaler==DiVISION_BY_4)
			ADCSRA|=DiVISION_BY_4;
	else if (Config_Ptr->prescaler==DiVISION_BY_8)
			ADCSRA|=DiVISION_BY_8;
	else if (Config_Ptr->prescaler==DiVISION_BY_16)
			ADCSRA|=DiVISION_BY_16;
	else if (Config_Ptr->prescaler==DiVISION_BY_32)
			ADCSRA|=DiVISION_BY_32;
	else if (Config_Ptr->prescaler==DiVISION_BY_64)
			ADCSRA|=DiVISION_BY_64;
	else if (Config_Ptr->prescaler==DiVISION_BY_128)
			ADCSRA|=DiVISION_BY_128;
}

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
