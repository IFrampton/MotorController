/*
 * BspCan.cpp
 *
 *  Created on: Jan 1, 2024
 *      Author: Isaac Frampton
 */

#include "stm32h7xx.h"
#include "BspClock.h"

void BspClock::Initialize(long extFreq, long cpuFreq)
{
	// Give ourselves as much power as we can get.
	PWR->CR1 = 	((unsigned long)15 << 28) |	// Required to match reset value
				(1  << 17) |	// ALS: Set the analog voltage detector level to 2.1V
				(0  << 16) |	// AVDEN: Peripheral voltage monitor on VDDA enable
				(3  << 14) |	// SVOS: System stop mode voltage scaling selection (3 = SVOS3 scale 3)
				(1  <<  9) |	// FLPS: Flash low-power mode in DStop mode (enter low power mode)
				(1  <<  8) |	// DBP: Disable backup domain write protection (backup domain accessible)
				(1  <<  5) |	// PLS: Programmable voltage detector level selection set to 2.1V
				(0  <<  4) |	// PVDE: Programmable Voltage detector enable
				(0  <<  0) ;	// LPDS: Low power deep sleep with SVOS3 Voltage Regulator in main mode when SVOS3 is selected for stop mode

	PWR->CR2 = 	(0  <<  4) |	// MONEN = 0; Vbat and temperature monitoring disable
				(1  <<  0) ;	// BREN = 1; Backup regulator is enabled

	PWR->CR3 = 	(0  << 25) |	// USBREGEN = 0; The USB regulator is disabled
				(0  << 24) |	// USB33DEN = 0; The USB Vdd33ESB voltage level detector is disabled
				(0  <<  9) |	// VBRS = 0; Charge Vbat through a 5k resistor
				(0  <<  8) |	// VBE = 0; Vbat charging disabled
				(0  <<  4) |	// SDLEVEL = 0; SMPS step-down converter voltage output level selection is 1.25V
				(0  <<  3) |	// SDEXTHP = 1; SMPS step-down converter forced ON and in high power MR mode
				(1  <<  2) |	// SDEN = 1; SMPS step-down converter enabled
				(0  <<  1) |	// LDOEN = 0; Low dropout regulator disabled
				(0  <<  0) ;	// BYPASS = 1; Power management unit bypass (bypassed, voltage monitoring still active)

	/*
	// Datasheet Page 375
	Initialize the PLLs registers according to the required frequency.
	– Set PLLxFRACEN of RCC PLL configuration register (RCC_PLLCFGR) to ‘0’ for
	integer mode.
	– For fractional mode, set FRACN to the required initial value (FracInitValue) and
	then set PLLxFRACEN to ‘1’.
	2. Once the PLLxON bit is set to ‘1’, the user application has to wait until PLLxRDY bit is
	set to ‘1’. If the PLLx is in fractional mode, the PLLxFRACEN bit must not be set back
	to ‘0’ as long as PLLxRDY = ‘0’.
	3. Once the PLLxRDY bit is set to ‘1’, the PLLx is ready to be used.
	4. If the application intends to tune the PLLx frequency on-the-fly (possible only in
	fractional mode), then:
	a) PLLxFRACEN must be set to ‘0’,
	When PLLxFRACEN = ‘0’, the Sigma-Delta modulator is still operating with the
	value latched into SH_REG.
	Application must wait for 3 refx_ck clock periods (PLLxFRACEN bit propagation
	delay)
	b) A new value must be uploaded into PLLxFRACR (FracValue(n)).
	c) PLLxFRACEN must be set to ‘1’, in order to latch the content of PLLxFRACR into
	its shadow register.
	The new value is considered after 3 clock periods of refx_ck (PLLxFRACEN bit
	propagation delay)
	*/

	// Before Configuring the PLL, the system must use the internal or external oscillator (not use the PLL)
	RCC->CFGR &= ~(7 << 0);

	RCC->CFGR = (2  << 29) |	// MCO2SEL = 1; Microcontroller clock output 2 (0 = sys_ck, 1 = PLL2, 2 = HSE, 3 = PLL1, 4 = CSI, 5 = LSI, 6 = reserved, 7 = reserved)
				(8  << 25) |	// MCO2PRE = 8; MCO2 prescaler (8 gives 1MHz output)
				(2  << 22) |	// MCO1SEL = 1; Microcontroller clock output 1 (0 = sys_ck, 1 = PLL2, 2 = HSE, 3 = PLL1, 4 = CSI, 5 = LSI, 6 = reserved, 7 = reserved)
				(8  << 18) |	// MCO1PRE = 8; MCO1 prescaler (8 gives 1MHz output)
				(0  << 15) |	// TIMPRE = 0; Timers clocks prescaler selection (0 gives 480MHz)
				(0  << 14) |	// HRTIMSEL = 0; High resolution timer clock prescaler selection (0 gives 480MHz)
				(50 <<  8) |	// RTCPRE = 50; HSE division factor for RTC clock (50 gives 160kHz)
				(0  <<  7) |	// STOPKERWUCK = 0; Kernel clock selection after a wake up from system stop (select HSI)
				(0  <<  6) |	// STOPWUCK = 0; System clock selection after a wake up from system stop (select HSI)
				(0  <<  0) ;	// SW = 0; System clock switch (select HSI)

	// Enable the external oscillator input
	RCC->CR |= (1 << 16);

	// Disable all PLLs
	RCC->CR &= ~(1 << 24); // PLL1
	RCC->CR &= ~(1 << 26); // PLL2
	RCC->CR &= ~(1 << 28); // PLL3

	// Set PLL Ratios
	RCC->PLLCKSELR = (0  << 20) |	// DIVM3 = 0; Disable PLL3 (not in use) to save power
					 (0  << 12) |	// DIVM2 = 0; Disable PLL2 (not in use) to save power
					 (1  <<  4) |	// DIVM1 = 1; Set PLL1 to external oscillator (8MHz)
					 (2  <<  0) ;	// PLLSRC = 2; (0 = HSI, 1 = CSI, 2 = HSE, 3 = none)

	RCC->PLLCFGR = 	(0  << 24) |	// DIVR3EN = 0; PLL3 DIVR divider output enable (output is disabled)
					(0  << 23) |	// DIVQ3EN = 0; PLL3 DIVQ divider output enable (output is disabled)
					(0  << 22) |	// DIVP3EN = 0; PLL3 DIVP divider output enable (output is disabled)
					(0  << 21) |	// DIVR2EN = 0; PLL2 DIVR divider output enable (output is disabled)
					(0  << 20) |	// DIVQ2EN = 0; PLL2 DIVQ divider output enable (output is disabled)
					(0  << 19) |	// DIVP2EN = 0; PLL2 DIVP divider output enable (output is disabled)
					(0  << 18) |	// DIVR1EN = 0; PLL1 DIVR divider output enable (output is disabled)
					(0  << 17) |	// DIVQ1EN = 0; PLL1 DIVQ divider output enable (output is disabled)
					(1  << 16) |	// DIVP1EN = 0; PLL1 DIVP divider output enable (output is disabled)
					(2  << 10) |	// PLL3RGE = 2; PLL3 input frequency range (0 = 1-2MHz, 1 = 2-4MHz, 2 = 4-8Mhz, 3 = 8-16MHz)
					(0  <<  9) |	// PLL3VCOSEL = 1; PLL3 VCO Selection (0 = wide range (192-960MHz), 1 = medium range (150-420MHz)
					(0  <<  8) |	// PLL3FRACEN = 0; PLL3 fractional latch enable (latch is disabled)
					(2  <<  6) |	// PLL2RGE = 2; PLL3 input frequency range (0 = 1-2MHz, 1 = 2-4MHz, 2 = 4-8Mhz, 3 = 8-16MHz)
					(0  <<  5) |	// PLL2VCOSEL = 1; PLL3 VCO Selection (0 = wide range (192-960MHz), 1 = medium range (150-420MHz)
					(0  <<  4) |	// PLL2FRACEN = 0; PLL3 fractional latch enable (latch is disabled)
					(2  <<  2) |	// PLL1RGE = 2; PLL3 input frequency range (0 = 1-2MHz, 1 = 2-4MHz, 2 = 4-8Mhz, 3 = 8-16MHz)
					(0  <<  1) |	// PLL1VCOSEL = 1; PLL3 VCO Selection (0 = wide range (192-960MHz), 1 = medium range (150-420MHz)
					(0  <<  0) ;	// PLL1FRACEN = 0; PLL3 fractional latch enable (latch is disabled)

	RCC->PLL1DIVR = (3  << 24) |	// DIVR1 = 3; (PLL1 DIVR division factor = 4) // Gives 240MHz
					(3  << 16) |	// DIVQ1 = 3; (PLL1 DIVQ division factor = 4) // Gives 240MHz
					(1  <<  9) |	// DIVP1 = 1; (PLL1 DIVP division factor = 2) // Gives 480MHz
					(59 <<  0) ;	// DIVN1 = 59; (PLL1 DIVN division factor = 59, generates HSE X 60 frequency = 480MHz)

	RCC->D1CCIPR = 	(2  << 28) |	// CKPERSEL = 2; per_ck source selection (0 = HSI, 1 = CSI, 2 = HSE, 3 = none)
					(0  << 16) |	// SDMMCSEL = 0; SDMMC kernel clock source selection (use PLL1_q_CLK)
					(0  <<  8) |	// DSISEL = 0; DSI kernel clock source selection (use DSI clock from phy)
					(0  <<  4) |	// QSPISEL = 0; QSPI kernel clock selection (use rcc_hclk3)
					(0  <<  0) ;	// FMCSEL = 0; FMC kernel clock source selection (use rcc_hclk3)

	RCC->D1CFGR = 	(0  <<  8) |	// D1CPRE = 0; D1 domain core prescaler (sys_ck is not divided)
					(1  <<  4) |	// D1PPRE = 1; D1 domain APB3 prescaler (rcc_pclk3 is sys_ck divided by 2)
					(1  <<  0) ;	// HPRE = 1; D1 domain AHB prescaler (rcc_hclk3 is sys_ck divided by 2)

	RCC->D2CFGR = 	(1  <<  8) |	// D2PPRE2 = 1; D2 domain APB2 prescaler (rcc_pclk2 is sys_ck divided by 2)
					(1  <<  4) ;	// D1PPRE1 = 1; D2 domain APB1 prescaler (rcc_pclk1 is sys_ck divided by 2)

	RCC->D3CFGR = 	(1  <<  4) ;	// D4PPRE = 1; D3 domain APB4 prescaler (rcc_pclk4 is sys_ck divided by 2)

	// Enable relevant PLLs
	RCC->CR |= (1 << 24); // PLL1
	//RCC->CR |= (1 << 26); // PLL2
	//RCC->CR |= (1 << 28); // PLL3

	while(!(RCC->CR & (1<<25)))
	{
	}

	// Use the PLL
	RCC->CFGR |= (3 << 0);
}
