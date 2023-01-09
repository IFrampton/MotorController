/*
** ###################################################################
**     Processors:          LPC824M201JDH20
**                          LPC824M201JHI33
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    LPC82x User manual Rev.1.2  5 October 2016
**     Version:             rev. 1.1, 2018-02-25
**     Build:               b201015
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2020 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2018-02-09)
**         Initial version.
**     - rev. 1.1 (2018-02-25)
**         Update some registers according to UM rev 1.2
**
** ###################################################################
*/

/*!
 * @file LPC822
 * @version 1.1
 * @date 2018-02-25
 * @brief Device specific configuration file for LPC824 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
/* CMSIS-style register definitions */
#include "LPC822.h"
/* CPU specific feature definitions */
#include "LPC822_features.h"


/* get system pll input freq */
static uint32_t CLOCK_GetSystemPLLInClkRate(void)
{
    uint32_t freq = 0U;

    switch ((SYSCON->SYSPLLCLKSEL & SYSCON_SYSPLLCLKSEL_SEL_MASK))
    {
        /* source from external clock in */
        case 0x00U:
            freq = CLK_IRC_12MHZ;
            break;
        /* source from the IRC clock */
        case 0x01U:
            freq = CLK_OSC_IN;
            break;
        /* source from external clock clock */
        case 0x03U:
            freq = EXT_CLK_IN;
            break;
        default:
        /* default source from the IRC clock */
            freq = CLK_IRC_12MHZ;
            break;
    }

    return freq;
}

/* get system pll output freq*/
static uint32_t Clock_GetPLLFreq(uint32_t PLLReg, uint32_t inputRate)
{
    uint32_t m_val = ((PLLReg & 0x1FU) + 1U);

    return (inputRate * m_val); // Note: This does not consider all divide ratios.
}



/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {

#if defined(__MCUXPRESSO)
    extern void(*const g_pfnVectors[]) (void);
    SCB->VTOR = (uint32_t) &g_pfnVectors;
#else
    extern void *__Vectors;
    SCB->VTOR = (uint32_t) &__Vectors;
#endif
    //SystemCoreClock = DEFAULT_SYSTEM_CLOCK;
    SetupPLL();
    SystemCoreClockUpdate();
  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {
  uint32_t wdt_osc = 0U;
  uint32_t irc_clk = 12000000U;

  switch ((SYSCON->WDTOSCCTRL >> SYSCON_WDTOSCCTRL_FREQSEL_SHIFT) & 0x0FU) {
    case 0U:  wdt_osc =       0U; break;
    case 1U:  wdt_osc =  600000U; break;
    case 2U:  wdt_osc = 1050000U; break;
    case 3U:  wdt_osc = 1400000U; break;
    case 4U:  wdt_osc = 1750000U; break;
    case 5U:  wdt_osc = 2100000U; break;
    case 6U:  wdt_osc = 2400000U; break;
    case 7U:  wdt_osc = 2700000U; break;
    case 8U:  wdt_osc = 3000000U; break;
    case 9U:  wdt_osc = 3250000U; break;
    case 10U: wdt_osc = 3500000U; break;
    case 11U: wdt_osc = 3750000U; break;
    case 12U: wdt_osc = 4000000U; break;
    case 13U: wdt_osc = 4200000U; break;
    case 14U: wdt_osc = 4400000U; break;
    case 15U: wdt_osc = 4600000U; break;
    default:  wdt_osc =       0U; break;
  }
  wdt_osc /= (((SYSCON->WDTOSCCTRL & SYSCON_WDTOSCCTRL_DIVSEL_MASK) + 1U) << 1U);

  switch (SYSCON->MAINCLKSEL & SYSCON_MAINCLKSEL_SEL_MASK)
  {
    case 0U:                                              /* IRC  */
      SystemCoreClock = irc_clk;
      break;
    case 1U:                                             /* System PLL input */
      switch (SYSCON->SYSPLLCLKSEL & SYSCON_SYSPLLCLKSEL_SEL_MASK) {
        case 0U:                                         /* IRC */
          SystemCoreClock = irc_clk;
          break;
        case 1U:                                         /* System oscillator */
          SystemCoreClock = CLK_OSC_IN;
          break;
        case 3U:                                         /* CLKIN */
          SystemCoreClock = EXT_CLK_IN;
          break;
        default:
          SystemCoreClock = irc_clk;                    /* default is IRC */
          break;
      }
      break;
    case 2U:                                              /* watchdog oscillator */
      SystemCoreClock = wdt_osc;
      break;
    case 3U:                                              /* System PLL  */
      SystemCoreClock = Clock_GetPLLFreq((SYSCON->SYSPLLCTRL & SYSCON_SYSPLLCTRL_MSEL_MASK), CLOCK_GetSystemPLLInClkRate());
      break;
    default:
      SystemCoreClock = 0U;
      break;
  }

  SystemCoreClock /= SYSCON->SYSAHBCLKDIV;
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}

void SetupPLL(void)
{
	// Power up the PLL
	SYSCON->PDRUNCFG &= ~(1 << 7);
	SYSCON->SYSPLLCLKSEL = 0; // SEL = 0x0 (Use Internal 12MHz clock)
	SYSCON->SYSPLLCLKUEN = 0; // ENA = 0x0 (Prepare for update)
	SYSCON->SYSPLLCLKUEN = 1; // ENA = 0x0 (Update Clock Source)
	// Set up PLL to use 30MHz clock
	// Internal divider is set to 4 because this puts the CCO output at 240MHz (it's range is 156 to 320)
#ifdef USE_30MHz_SYSTEM_CLOCK
	SYSCON->SYSPLLCTRL = (1 << 5)	|	// PSEL = 1 (divide by 4, gives 240MHz intermediate clock)
						 (4 << 0)	;	// MSEL = 4 (multiply by 5)
#else //  Use 72MHz (Max speed)
	//SYSCON->SYSPLLCTRL = (1 << 5)	|	// PSEL = 1 (divide by 4, gives 288MHz intermediate clock)
	//					 (5 << 0)	;	// MSEL = 5 (multiply by 6)
	// Now using 48MHz
	SYSCON->SYSPLLCTRL = (0 << 5)	|	// PSEL = 0 (divide by 2, gives 192MHz intermediate clock)
						 (7 << 0)	;	// MSEL = 7 (multiply by 8)
#endif
	while(!SYSCON->SYSPLLSTAT)
	{
		__asm("nop");
	}
	// Set up main clock to use the PLL Output
	SYSCON->MAINCLKSEL = 3;
	SYSCON->MAINCLKUEN = 0; // ENA = 0x0 (Prepare for update)
#ifdef USE_30MHz_SYSTEM_CLOCK
	// Note: To hit target of 30MHz, this chip should really be divided by 2.
	// From testing, it seems that the core runs just fine at 60MHz.
	SYSCON->SYSAHBCLKDIV = 2; // Divider is 2, gives 30MHz clock
#else //  Use 72MHz (Max speed)
	// Note: To hit target of 30MHz, this chip should really be divided by 2.
	// From testing, it seems that the core runs just fine at 60MHz.
	//SYSCON->SYSAHBCLKDIV = 1; // Divider is 1, gives 72MHz clock
	// Now Using 48MHz
	SYSCON->SYSAHBCLKDIV = 2; // Divider is 1, gives 72MHz clock
#endif
	SYSCON->MAINCLKUEN = 1; // ENA = 0x0 (Update Clock Source)
}
