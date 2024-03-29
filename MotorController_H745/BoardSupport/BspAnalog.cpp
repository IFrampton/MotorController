/*
 * BspAnalog.cpp
 *
 *  Created on: Jan 1, 2024
 *      Author: Isaac Frampton
 */

#include "BspAnalog.h"
#include "BspDma.h"
#include "SineTable.h"

BspAnalog::AnalogConfig *BspAnalog::_configuration = (BspAnalog::AnalogConfig *)&BspAnalog::DummyVariable;
long BspAnalog::_analogDataBuffer[3][19];
bool BspAnalog::_initialized;
unsigned char BspAnalog::_nextChannel[3];
unsigned char BspAnalog::_dmaRxChannel[3];
unsigned char BspAnalog::_dmaTxChannel;

void BspAnalog::InitializeAdc(void)
{
	// Configure clock to ADC123
	RCC->D3CCIPR &= ~(3 << 16);
	RCC->D3CCIPR |= (0 << 16); // 2 = per_ck, 0 = pll2_p_cl, 1 = pll3_r_clk, 3 = disabled

	// Remove Reset from ADC12
	RCC->AHB1RSTR &= ~(1 <<  5);
	// Remove Reset from ADC3
	RCC->AHB4RSTR &= ~(1 << 24);

	RCC->AHB1ENR |= (1 << 5);
	RCC->AHB4ENR |= (1 << 24);

	// Disable ADC for Core 1 (Core 1 is believed to be the M7 core)
	RCC_C1->AHB1ENR &= ~(1 << 5);
	RCC_C1->AHB4ENR &= ~(1 << 24);

	// Enable ADC for Core 2 (Core 2 is believed to be the M4 core)
	RCC_C2->AHB1ENR |= (1 << 1);
	RCC_C2->AHB4ENR |= (1 << 24);

	// Clear Status Flags
	ADC1->ISR = 0x000007FF;

	// Setup relevant interrupts
	ADC1->IER = (0  << 10)	|	// JQOVFIE = 0; Injected context queue overflow interrupt enable
				(0  <<  9)	|	// AWD3IE = 0; Analog watchdog 3 interrupt enable (0 = disabled)
				(0  <<  8)	|	// AWD2IE = 0; Analog watchdog 2 interrupt enable (0 = disabled)
				(0  <<  7)	|	// AWD1IE = 0; Analog watchdog 1 interrupt enable (0 = disabled)
				(0  <<  6)	|	// JEOSIE = 0; End of injected sequence of conversions interrupt enable (0 = disabled)
				(0  <<  5)	|	// JEOCIE = 0; End of injected conversion interrupt enable (0 = disabled)
				(0  <<  4)	|	// OVRIE = 0; Overrun interrupt enable (0 = disabled)
				(0  <<  3)	|	// EOSIE = 0; End of regular sequence interrupt enable (0 = disabled)
				(0  <<  2)	|	// OSCIE = 0; End of regular conversion interrupt enable (0 = disabled)
				(0  <<  1)	|	// EOSMPIE = 0; End of sampling flag interrupt enable for regular conversions (0 = disabled)
				(0  <<  0)	;	// ADRDYIE = 0; ADC ready interrupt enable (0 = disabled)
	ADC1->CR =  (0  << 31)	|	// ADCAL = 0; ADC calibration (0 = Calibration complete)
				(0  << 30)	|	// ADCALDIF = 0; Different mode for calibration (0 = single ended)
				(0  << 29)	|	// DEEPPWD = 0; Deep power down enable (0 = disabled)
				(1  << 28)	|	// ADVREGEN = 1; ADC voltage regulator enable
				(0  << 27)	|	// LINCALRDYW6 = 0; Linearity calibration ready Word 6 (0 = not ready)
				(0  << 26)	|	// LINCALRDYW5 = 0; Linearity calibration ready Word 5 (0 = not ready)
				(0  << 25)	|	// LINCALRDYW4 = 0; Linearity calibration ready Word 4 (0 = not ready)
				(0  << 24)	|	// LINCALRDYW3 = 0; Linearity calibration ready Word 3 (0 = not ready)
				(0  << 23)	|	// LINCALRDYW2 = 0; Linearity calibration ready Word 2 (0 = not ready)
				(0  << 22)	|	// LINCALRDYW1 = 0; Linearity calibration ready Word 1 (0 = not ready)
				(0  << 16)	|	// ADCALLIN = 0; Linearity calibration (0 = not used for calibration)
//				(3  <<  8)	|	// BOOST = 3; Boost Mode Control (3 = optimized between 25 and 50MHz)
				(1  <<  8)	|	// BOOST = 1; Boost Mode Control (1 = optimized between 0.25 and 12MHz, 3 = optimized between 25 and 50MHz)
				(0  <<  5)	|	// JADSTP = 0; ADC stop of injected conversion command (0 = no command ongoing)
				(0  <<  4)	|	// ADSTP = 0; ADC stop of regular conversion command (0 = no command ongoing)
				(0  <<  3)	|	// JADSTART = 0; ADC start of injected conversion (0 = no conversion ongoing)
				(0  <<  2)	|	// ADSTART = 0; ADC start of regular conversion (0 = no conversion ongoing)
				(0  <<  1)	|	// ADDIS = 0; ADC disable command (0 = no command ongoing)
				(0  <<  0)	;	// ADEN = 0; ADC enable command (0 = no command ongoing)

	ADC1->CFGR = (0 << 31)	|	// JQDIS = 0; Injected Queue disabled
				(0  << 28)	|	// AWD1CH = 0; Analog Input Channel 0 is monitored by watchdog (unused)
				(0  << 25)	|	// JAUTO = 0; Automatic injected group conversion disabled
				(0  << 24)	|	// JAWD1EN = 0; Analog watchdog 1 disabled on injected channels (unused)
				(0  << 23)	|	// AWD1EN = 0; Analog watchdog 1 enable on regular channels
				(0  << 22)	|	// AWD1SGL = 0; Analog watchdog enabled on all channels
				(0  << 21)	|	// JQM = 0; JSQR queue mode (queue is never empty and maintains last configuration)
				(0  << 20)	|	// JDISCEN = 0; Discontinuous mode disabled on injected channels
				(0  << 17)	|	// DISCNUM = 0; Discontinuous channel count is 1
				(0  << 16)	|	// DISCEN = 0; Discontinuous mode for regular channels is disabled
				(0  << 14)	|	// AUTDLY = 0; Delayed conversion mode is off
				(1  << 13)	|	// CONT = 1; Single / Continuous conversion mode for regular conversions is enabled
				(0  << 12)	|	// OVRMOD = 0; Overrun Mode
				(0  << 10)	|	// EXTEN = 0; External trigger enable and polarity selection for regular channels (external trigger disabled)
				(0  <<  5)	|	// EXTSEL = 0; External trigger selection for regular group (0 = Event 0)
//				(0  <<  2)	|	// RES = 0; Data resolution (0 = 16 bits, 5 = 14 bits, 6 = 12 bits, 3 = 10 bits, 7 = 8 bits)
				(5  <<  2)	|	// RES = 5; Data resolution (0 = 16 bits, 5 = 14 bits, 6 = 12 bits, 3 = 10 bits, 7 = 8 bits)
				(3  <<  0)	;	// DMNGT = 3; Data Management Confirmation (3 - DMA circular mode)
	ADC1->CFGR2 = (0<< 31)	|	// LSHIFT = 0; Left Shift factor (0 = no left shift)
//				(31 << 16)	|	// OSVR = 31; Oversampling Ratio (31 = 32 samples are down-sampled)
				(7 << 16)	|	// OSVR = 31; Oversampling Ratio (7 = 8 samples are down-sampled)
				(0  << 14)	|	// RSHIFT4 = 0; Right shift data after offset 4 correction (no shift)
				(0  << 13)	|	// RSHIFT3 = 0; Right shift data after offset 3 correction (no shift)
				(0  << 12)	|	// RSHIFT2 = 0; Right shift data after offset 2 correction (no shift)
				(0  << 11)	|	// RSHIFT1 = 0; Right shift data after offset 1 correction (no shift)
				(0  << 10)	|	// ROVSM = 0; Regular oversampling mode (0 = continued mode)(unused)
				(0  <<  9)	|	// TROVS = 0; Triggered regular oversampling (0 = all conversions require only one trigger)
				(1  <<  5)	|	// OVSS = 0; Oversampling right shift (0 = no right shift)
				(0  <<  1)	|	// JOVSE = 0; Injected oversampling enable (0 = disabled)
				(1  <<  0)	;	// ROVSE = 0; Regular oversampling enable (1 = enabled)
	ADC1->SMPR1 = (2<< 27)	|	// SMP9 = 1; Channel 9 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  << 24)	|	// SMP8 = 1; Channel 8 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  << 21)	|	// SMP7 = 1; Channel 7 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  << 18)	|	// SMP6 = 1; Channel 6 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  << 15)	|	// SMP5 = 1; Channel 5 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  << 12)	|	// SMP4 = 1; Channel 4 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  <<  9)	|	// SMP3 = 1; Channel 3 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  <<  6)	|	// SMP2 = 1; Channel 2 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  <<  3)	|	// SMP1 = 1; Channel 1 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  <<  0)	;	// SMP0 = 1; Channel 0 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
	ADC1->SMPR2 = (2<< 27)	|	// SMP19 = 1; Channel 19 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  << 24)	|	// SMP18 = 1; Channel 18 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  << 21)	|	// SMP17 = 1; Channel 17 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  << 18)	|	// SMP16 = 1; Channel 16 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  << 15)	|	// SMP15 = 1; Channel 15 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  << 12)	|	// SMP14 = 1; Channel 14 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  <<  9)	|	// SMP13 = 1; Channel 13 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  <<  6)	|	// SMP12 = 1; Channel 12 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  <<  3)	|	// SMP11 = 1; Channel 11 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
				(2  <<  0)	;	// SMP10 = 1; Channel 10 sampling time selection (0 = 1.5 X adc_clk, 1 = 2.5 X adc_clk, 2 = 8.5 X adc_clk ...)
	ADC1->PCSEL = (0<< 19)	|	// PCSEL19 = 0; Channel 19 is not pre-selected for conversion
				(0  << 18)	|	// PCSEL18 = 0; Channel 18 is not pre-selected for conversion
				(0  << 17)	|	// PCSEL17 = 0; Channel 17 is not pre-selected for conversion
				(0  << 16)	|	// PCSEL16 = 0; Channel 16 is not pre-selected for conversion
				(0  << 15)	|	// PCSEL15 = 0; Channel 15 is not pre-selected for conversion
				(0  << 14)	|	// PCSEL14 = 0; Channel 14 is not pre-selected for conversion
				(0  << 13)	|	// PCSEL13 = 0; Channel 13 is not pre-selected for conversion
				(0  << 12)	|	// PCSEL12 = 0; Channel 12 is not pre-selected for conversion
				(0  << 11)	|	// PCSEL11 = 0; Channel 11 is not pre-selected for conversion
				(0  << 10)	|	// PCSEL10 = 0; Channel 10 is not pre-selected for conversion
				(0  <<  9)	|	// PCSEL9 = 0; Channel 9 is not pre-selected for conversion
				(0  <<  8)	|	// PCSEL8 = 0; Channel 8 is not pre-selected for conversion
				(0  <<  7)	|	// PCSEL7 = 0; Channel 7 is not pre-selected for conversion
				(0  <<  6)	|	// PCSEL6 = 0; Channel 6 is not pre-selected for conversion
				(0  <<  5)	|	// PCSEL5 = 0; Channel 5 is not pre-selected for conversion
				(0  <<  4)	|	// PCSEL4 = 0; Channel 4 is not pre-selected for conversion
				(0  <<  3)	|	// PCSEL3 = 0; Channel 3 is not pre-selected for conversion
				(0  <<  2)	|	// PCSEL2 = 0; Channel 2 is not pre-selected for conversion
				(0  <<  1)	|	// PCSEL1 = 0; Channel 1 is not pre-selected for conversion
				(0  <<  0)	;	// PCSEL0 = 0; Channel 0 is not pre-selected for conversion
	// Thresholds are not used
	ADC1->LTR1 = 0; // Analog watchdog lower threshold register 1
	ADC1->HTR1 = 0x03FFFFFF; // Analog watchdog higher threshold register 1
	ADC1->SQR1 = (0 << 24)	|	// SQ4 = 0; 4th conversion in regular sequence
				(0  << 18)	|	// SQ3 = 0; 3rd conversion in regular sequence
				(0  << 12)	|	// SQ2 = 0; 2nd conversion in regular sequence
				(0  <<  6)	|	// SQ1 = 0; 1st conversion in regular sequence
				(0  <<  0)	;	// L = 0; Regular channel sequence length (0 = 1 conversion)
	ADC1->SQR2 = (0 << 24)	|	// SQ9 = 0; 9th conversion in regular sequence
				(0  << 18)	|	// SQ8 = 0; 8th conversion in regular sequence
				(0  << 12)	|	// SQ7 = 0; 7th conversion in regular sequence
				(0  <<  6)	|	// SQ6 = 0; 6th conversion in regular sequence
				(0  <<  0)	;	// SQ5 = 0; 5th conversion in regular sequence
	ADC1->SQR3 = (0 << 24)	|	// SQ14 = 0; 14th conversion in regular sequence
				(0  << 18)	|	// SQ13 = 0; 13th conversion in regular sequence
				(0  << 12)	|	// SQ12 = 0; 12th conversion in regular sequence
				(0  <<  6)	|	// SQ11 = 0; 11th conversion in regular sequence
				(0  <<  0)	;	// SQ10 = 0; 10th conversion in regular sequence
	ADC1->SQR4 = (0 <<  6)	|	// SQ16 = 0; 16th conversion in regular sequence
				(0  <<  0)	;	// SQ15 = 0; 15th conversion in regular sequence

	volatile unsigned int read = ADC1->DR;

	// None of the injected sequence is used
	ADC1->JSQR = (0 << 27)	|	// JSQ4 = 0; 4th conversion in injected sequence
				(0  << 21)	|	// JSQ3 = 0; 3rd conversion in injected sequence
				(0  << 15)	|	// JSQ2 = 0; 2nd conversion in injected sequence
				(0  <<  9)	|	// JSQ1 = 0; 1st conversion in injected sequence
				(0  <<  7)	|	// JEXTEN = 0; External trigger enable and polarity selection for injected channels (0 = disabled)
				(0  <<  2)	|	// JEXTSEL = 0; External trigger selection for injected group (0 = event 0)
				(0  <<  0)	;	// JL = 0; Injected channel sequence length (0 = 1 conversion)
	ADC1->OFR1 = (0 << 31)	|	// SSATE = 0; Signed saturation enable (0 = offset is subtracted)
				(0  << 26)	|	// OFFSET_CH = 0; Channel selection for the data offset y (channel 0)
				(0  <<  0)	;	// OFFSET = 0; Data offset y for the channel programmed into bits OFFSETy_CH[4:0] (0 = no offset)
	ADC1->OFR2 = (0 << 31)	|	// SSATE = 0; Signed saturation enable (0 = offset is subtracted)
				(0  << 26)	|	// OFFSET_CH = 0; Channel selection for the data offset y (channel 0)
				(0  <<  0)	;	// OFFSET = 0; Data offset y for the channel programmed into bits OFFSETy_CH[4:0] (0 = no offset)
	ADC1->OFR3 = (0 << 31)	|	// SSATE = 0; Signed saturation enable (0 = offset is subtracted)
				(0  << 26)	|	// OFFSET_CH = 0; Channel selection for the data offset y (channel 0)
				(0  <<  0)	;	// OFFSET = 0; Data offset y for the channel programmed into bits OFFSETy_CH[4:0] (0 = no offset)
	ADC1->OFR4 = (0 << 31)	|	// SSATE = 0; Signed saturation enable (0 = offset is subtracted)
				(0  << 26)	|	// OFFSET_CH = 0; Channel selection for the data offset y (channel 0)
				(0  <<  0)	;	// OFFSET = 0; Data offset y for the channel programmed into bits OFFSETy_CH[4:0] (0 = no offset)

	read = ADC1->JDR1;
	read = ADC1->JDR2;
	read = ADC1->JDR3;
	read = ADC1->JDR4;

	// Thresholds are not used
	ADC1->AWD2CR = 0;
	ADC1->LTR2 = 0; // Analog watchdog lower threshold register 2
	ADC1->HTR2 = 0x03FFFFFF; // Analog watchdog higher threshold register 2
	ADC1->AWD3CR = 0;
	ADC1->LTR3 = 0; // Analog watchdog lower threshold register 3
	ADC1->HTR3 = 0x03FFFFFF; // Analog watchdog higher threshold register 3

	// Differential mode is unused in this configuration
	ADC1->DIFSEL = (0<<19)	|	//DIFSEL19 = 0; Differential mode for channel 19 (0 = disabled)
				(0  << 18)	|	//DIFSEL18 = 0; Differential mode for channel 18 (0 = disabled)
				(0  << 17)	|	//DIFSEL17 = 0; Differential mode for channel 17 (0 = disabled)
				(0  << 16)	|	//DIFSEL16 = 0; Differential mode for channel 16 (0 = disabled)
				(0  << 15)	|	//DIFSEL15 = 0; Differential mode for channel 15 (0 = disabled)
				(0  << 14)	|	//DIFSEL14 = 0; Differential mode for channel 14 (0 = disabled)
				(0  << 13)	|	//DIFSEL13 = 0; Differential mode for channel 13 (0 = disabled)
				(0  << 12)	|	//DIFSEL12 = 0; Differential mode for channel 12 (0 = disabled)
				(0  << 11)	|	//DIFSEL11 = 0; Differential mode for channel 11 (0 = disabled)
				(0  << 10)	|	//DIFSEL10 = 0; Differential mode for channel 10 (0 = disabled)
				(0  <<  9)	|	//DIFSEL9 = 0; Differential mode for channel 9 (0 = disabled)
				(0  <<  8)	|	//DIFSEL8 = 0; Differential mode for channel 8 (0 = disabled)
				(0  <<  7)	|	//DIFSEL7 = 0; Differential mode for channel 7 (0 = disabled)
				(0  <<  6)	|	//DIFSEL6 = 0; Differential mode for channel 6 (0 = disabled)
				(0  <<  5)	|	//DIFSEL5 = 0; Differential mode for channel 5 (0 = disabled)
				(0  <<  4)	|	//DIFSEL4 = 0; Differential mode for channel 4 (0 = disabled)
				(0  <<  3)	|	//DIFSEL3 = 0; Differential mode for channel 3 (0 = disabled)
				(0  <<  2)	|	//DIFSEL2 = 0; Differential mode for channel 2 (0 = disabled)
				(0  <<  1)	|	//DIFSEL1 = 0; Differential mode for channel 1 (0 = disabled)
				(0  <<  0)	;	//DIFSEL0 = 0; Differential mode for channel 0 (0 = disabled)

	ADC12_COMMON->CCR = (0  << 24)	|	// VBATEN = 0; VBAT Enable (0 = channel disabled)
				(1  << 23)	|	// TSEN = 0; Temperature Sensor Voltage Enable (1 = channel enabled)
				(0  << 22)	|	// VREFEN = 0; V_refint enable (0 = channel disabled)
				// 50MHz
//				(1  << 18)	|	// PRESC = 2; ADC prescaler (0 = divide by 1, 1 = divide by 2, 2 = divide by 4, ...)
				// 10MHz
				(5  << 18)	|	// PRESC = 5; ADC prescaler (0 = divide by 1, 1 = divide by 2, 2 = divide by 4, 5 = divide by 10 ...)
				(0  << 16)	|	// CKMODE = 1; ADC clock mode (0 = adc_kernel_clk (pll2_p_clk) 1 = adc_sclk / 1)
				(2  << 14)	|	// DAMDF = 2; Dual ADC mode data format (2 = data formatting for 32 down to 1 bit resolution)
				(0  <<  8)	|	// DELAY = 0; Delay between two sampling phases (0 = no delay)
				(0  <<  0)	;	// DUAL = 0; Dual ADC mode selection (0 = All ADCs are independent)

	read = ADC12_COMMON->CDR;
	read = ADC12_COMMON->CDR2;
	// Dummy code to make compiler happy.
	if(read)
	{
		read++;
	}

	// Wait for voltage regulator
	while((ADC1->ISR & (1 << 12)) == 0);

	// <TODO = calibrate>
	ADC1->CR |= (unsigned long)(1 << 31);

	// Wait for calibration to complete
	while((ADC1->CR & (1 << 31)));

	// Enable ADC
	ADC1->CR |= (1 << 0);

	// Wait for ADC ready
	while((ADC1->ISR & (1 << 0)) == 0);

	_dmaRxChannel[0] = BspDma::SetupRxChannel(9, (unsigned long *)&ADC1->DR, (unsigned long *)&_analogDataBuffer[0][0], 2, sizeof(_analogDataBuffer[0][0]) / sizeof(long));
	//_dmaRxChannel[1] = BspDma::SetupRxChannel(10, (unsigned long *)ADC2->DR, (unsigned long *)&_analogDataBuffer[1][0], 2, sizeof(_analogDataBuffer[0][0]) / sizeof(long));
	//_dmaRxChannel[2] = BspDma::SetupRxChannel(115, (unsigned long *)ADC3->DR, (unsigned long *)&_analogDataBuffer[2][0], 2, sizeof(_analogDataBuffer[0][0]) / sizeof(long));

	_initialized = true;
}

unsigned char BspAnalog::SetupChannel(char converter, char channel, AnalogType *channelData)
{
	// Don't try to access register if not initialized
	if(!_initialized)
	{
		return 255;
	}
	// prevent too many channels on each converter
	if(_nextChannel[(long)converter] >= 16)
	{
		return 254;
	}
	ADC_TypeDef *adc;
	switch(converter)
	{
		case 0:
		default:
		{
			adc = ADC1;
			break;
		}
		case 1:
		{
			adc = ADC2;
			break;
		}
		case 2:
		{
			adc = ADC3;
			break;
		}
	}
	// catch possible exception
	if(channel > 19)
	{
		channel = 19;
	}
	adc->SQR1 &= ~0x3F;
	adc->SQR1 |= _nextChannel[(long)converter];

	// Include in sequence
	unsigned long registerOffset = ((_nextChannel[(long)converter] * 6 + 6) / 30);
	unsigned long positionOffset = ((_nextChannel[(long)converter] * 6 + 6) % 30);
	unsigned long *relevantPosition = (unsigned long *)((unsigned long)&adc->SQR1 + (registerOffset << 2));
	*relevantPosition &= ~(0x1F << positionOffset);
	*relevantPosition |= (channel << positionOffset);
	// Setup preselection to ensure valid conversion of channel
	adc->PCSEL |= (1 << channel);

	channelData->BaseLocation = (unsigned long *)&_analogDataBuffer[(long)converter][_nextChannel[(long)converter]];
	channelData->Offset = &_configuration->Offset[(long)converter][(long)channel];
	channelData->ScaleFactor = &_configuration->ScaleFactor[(long)converter][(long)channel];
	_nextChannel[(long)converter]++;

	BspDma::UpdateLength(_dmaRxChannel[(long)converter], _nextChannel[(long)converter]);

	// Success
	return 0;
}

//volatile unsigned short *BspAnalog::_spiData[3] = {(volatile unsigned short *)&DummyVariable, (volatile unsigned short *)&DummyVariable, (volatile unsigned short *)&DummyVariable};
//volatile unsigned char *BspAnalog::_spiDataReady[3] = {(volatile unsigned char *)&DummyVariable, (volatile unsigned char *)&DummyVariable, (volatile unsigned char *)&DummyVariable};
//unsigned short *BspAnalog::_spiReadComplete[3] = {(unsigned short *)&DummyVariable, (unsigned short *)&DummyVariable, (unsigned short *)&DummyVariable};
bool BspAnalog::_externalInitialized = false;
long BspAnalog::DummyVariable = 0xDEADBEEF;

void BspAnalog::InitializeExternal(void)
{
	//BspSpi::Initialize(1, 9375000, &_spiData[0], &_spiDataReady[0], &_spiReadComplete[0]);
	//BspSpi::Initialize(2, 9375000, &_spiData[1], &_spiDataReady[1], &_spiReadComplete[1]);
	//BspSpi::Initialize(3, 9375000, &_spiData[2], &_spiDataReady[2], &_spiReadComplete[2]);
	_externalInitialized = true;
}
unsigned char BspAnalog::SetupExternalChannel(char channel, ExternalAnalogType *channelData)
{
	// Don't try to access register if not initialized
	if(!_externalInitialized)
	{
		return 255;
	}
	// catch possible exception
	if(channel >= 3)
	{
		return 254;
	}

	//channelData->BaseLocation = (unsigned long *)_spiData[(long)channel];
	channelData->Offset = &_configuration->ExternalOffset[(long)channel];
	channelData->ScaleFactor = &_configuration->ExternalScaleFactor[(long)channel];
	BspSpi::Initialize(channel + 1, 9375000, &channelData->BaseLocation, &channelData->DataReady, &channelData->ReadComplete);
	// Success
	return 0;
}


void BspAnalog::InitializeDac(void)
{
	// Configure clock to DAC
	// No configuration required

	// Remove Reset from DAC
	RCC->APB1LRSTR &= ~(1<<29);

	// Enable DAC
	RCC->APB1LENR |= (1 << 29);

	// Disable DAC for Core 1 (Core 1 is believed to be the M7 core)
	RCC_C1->APB1LENR &= ~(1 << 29);

	// Enable DAC for Core 2 (Core 2 is believed to be the M4 core)
	RCC_C2->APB1LENR |= (1 << 29);

	// DAC Registers
	DAC1->CR = 	(0  << 30)	|	// CEN2 = 0; Channel 2 Calibration Enable
				(0  << 29)	|	// DMAUDRIE2 = 0; DAC Channel 2 DMA underrun interrupt enable
				(0  << 28)	|	// DMAEN2 = 0; DAC Channel 2 DMA Enable
				(0  << 24)	|	// MAMP2 = 0; DAC Channel 2 Mask / Amplitude Selector (0 = Mask all bits of LFSR)
				(0  << 22)	|	// WAVE2 = 0; DAC Channel 2 Noise / Triangle Wave Generation Enable (0 = wave generation disabled)
				(0  << 18)	|	// TSEL2 = 0; DAC Channel 2 Trigger Selection (0 = SWTRIG2)
				(0  << 17)	|	// TEN2 = 0; DAC Channel 2 Trigger Enable (0 = disabled)
				(0  << 16)	|	// EN2 = 0; DAC Channel 2 Enable (0 = disabled)
				(0  << 14)	|	// CEN1 = 0; Channel 1 Calibration Enable
				(0  << 13)	|	// DMAUDRIE1 = 0; DAC Channel 1 DMA underrun interrupt enable
				(1  << 12)	|	// DMAEN1 = 1; DAC Channel 1 DMA Enable
				(0  <<  8)	|	// MAMP1 = 0; DAC Channel 1 Mask / Amplitude Selector (0 = Mask all bits of LFSR)
				(0  <<  6)	|	// WAVE1 = 0; DAC Channel 1 Noise / Triangle Wave Generation Enable (0 = wave generation disabled)
				(11 <<  2)	|	// TSEL1 = 0; DAC Channel 1 Trigger Selection (11 = LPTIM1_OUT1)
				(0  <<  1)	|	// TEN1 = 0; DAC Channel 1 Trigger Enable (0 = disabled, enabled below)
				(0  <<  0)	;	// EN1 = 0; DAC Channel 1 Enable (1 = enabled, but 0 for now)
	DAC1->SWTRIGR = (0 << 1)|	// SWTRIG2 = 0 (no trigger for DAC2)
				(0  <<  0)	;	// SWTRIG1 = 0 (no trigger for DAC1)
	DAC1->DHR12R1 = 2047; // Set to center
	DAC1->DHR12R2 = 2047; // This is unused
	DAC1->MCR = 	(3  << 16)	|	// MODE2 = 3; DAC channel 2 Mode (3 = connected to on-chip peripherals, buffer disabled)
				(0  <<  0)	;	// MODE2 = 0; DAC channel 1 Mode (0 = connected to external pin with buffer enabled)
	DAC1->SHSR1 = 0;
	DAC1->SHSR2 = 0;
	DAC1->CR |= (3  <<  0);

	// 67 is dac_ch1_dma
	_dmaTxChannel = BspDma::SetupTxChannel(67, (unsigned long *)SineTable::GetIntSineTableAddress(), (unsigned long *)&DAC1->DHR12R1, 1, SineTable::GetIntTableLength());
}

