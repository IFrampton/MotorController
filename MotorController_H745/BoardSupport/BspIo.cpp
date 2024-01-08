/*
 * BspIo.cpp
 *
 *  Created on: Jan 6, 2024
 *      Author: Isaac Frampton
 */

#include "BspIo.h"

#define FOUR_INPUTS
//#define USE_TIM2_TWICE

BspIo::PinInfo	BspIo::_pinInfo[NUMBER_OF_GPIO];

void BspIo::Initialize(void)
{
	// Enable all GPIO ports
	RCC->AHB4ENR |= 0x7FF;
	RCC_C2->AHB4ENR |= 0x7FF;

	// Setup Each Function on the Controller

	// Setup Analog Inputs.
	//InitAnalog(char port, char pin)
	InitAnalog(0, 2);	// ANA_V_BUS
	InitAnalog(0, 3);	// ANA_V_A
	InitAnalog(0, 5);	// ANA_V_B
	InitAnalog(0, 6);	// ANA_V_C
	InitAnalog(0, 7);	// ANA_I_IN
	InitAnalog(2, 4);	// ANA_T_1
	InitAnalog(2, 5);	// ANA_T_2
	InitAnalog(1, 0);	// ANA_RSLV_SIN
	InitAnalog(1, 1);	// ANA_RSLV_COS
	// Setup Analog Outputs
	//InitAltFunction(char port, char pin, char alternate)
	InitAnalog(0, 4);	// RSLV_DAC

	// Setup CAN
	//InitAltFunction(char port, char pin, char alternate)
	InitAltFunction(3, 0, 9);	// CAN_RX
	InitAltFunction(3, 1, 9);	// CAN_TX

	// Setup ETM
	//InitAltFunction(char port, char pin, char alternate)
	InitAltFunction(4, 2, 0);	// TRACE_CLK
	InitAltFunction(4, 3, 0);	// TRACE_D0
	InitAltFunction(4, 4, 0);	// TRACE_D1
	InitAltFunction(4, 5, 0);	// TRACE_D2
	InitAltFunction(4, 6, 0);	// TRACE_D3

	// Setup QuadSPI
	//InitAltFunction(char port, char pin, char alternate)
	InitAltFunction(1, 3, 9);	// FLASH_SCLK
	InitAltFunction(4, 7, 10);	// FLASH_D0
	InitAltFunction(4, 8, 10);	// FLASH_D1
	InitAltFunction(4, 9, 10);	// FLASH_D2
	InitAltFunction(4, 10, 10);	// FLASH_D3
	InitAltFunction(2, 11, 9);	// FLASH_NCS

	// Setup SPI
	//InitAltFunction(char port, char pin, char alternate)
	// SPI1
	InitAltFunction(6, 11, 5);	// I_1_SCLK
	InitAltFunction(6, 9, 5);	// I_1_MISO
	// SPI2
	InitAltFunction(3, 3, 5);	// I_2_SCLK
	InitAltFunction(2, 1, 5);	// I_2_MISO
	// SPI3
	InitAltFunction(2, 10, 6);	// I_3_SCLK
	InitAltFunction(1, 4, 6);	// I_3_MISO
	// SPI4
	InitAltFunction(4, 11, 5);	// RSLV_SPI_CS
	InitAltFunction(4, 12, 5);	// RSLV_SPI_SCK
	InitAltFunction(4, 13, 5);	// RSLV_SPI_MISO
	InitAltFunction(4, 14, 5);	// RSLV_SPI_MOSI

	// Setup I2C
	//InitAltFunction(char port, char pin, char alternate)
	// I2C1
	InitAltFunction(1, 6, 4);	// 16G_ACCEL_SCL
	InitAltFunction(1, 7, 4);	// 16G_ACCEL_SDA
	// I2C4
	InitAltFunction(1, 8, 6);	// 200G_ACCEL_SDA
	InitAltFunction(5, 15, 4);	// 200G_ACCEL_SCL

	// Setup Switch PWM
	//InitAltFunction(char port, char pin, char alternate)
	InitAltFunction(0, 8, 1);	// CTRL_A_H
	InitAltFunction(0, 9, 1);	// CTRL_B_H
	InitAltFunction(0, 10, 1);	// CTRL_C_H
	InitAltFunction(1, 13, 1);	// CTRL_A_L
	InitAltFunction(1, 14, 1);	// CTRL_B_L
	InitAltFunction(1, 15, 1);	// CTRL_C_L

	// Setup Fixed PWM (isolating power supplies)
	//InitAltFunction(char port, char pin, char alternate)
	// TIM2
	InitAltFunction(0, 15, 1);	// CTRL_IN_PWR_1
	InitAltFunction(1, 3, 1);	// CTRL_IN_PWR_2
	// TIM3
	InitAltFunction(2, 6, 2);	// CTRL_CAN_PWR_1
	InitAltFunction(2, 7, 2);	// CTRL_CAN_PWR_2
	// TIM4
	InitAltFunction(3, 12, 2);	// CTRL_MTR_PWR_1
	InitAltFunction(3, 13, 2);	// CTRL_MTR_PWR_2
	// TIM5
#ifdef USE_TIM2_TWICE // TIM2 controls both the Input power suppy and the switch power supply
	InitAltFunction(0, 0, 1);	// CTRL_SW_PWR_1
	InitAltFunction(0, 1, 1);	// CTRL_SW_PWR_2
#else
	InitAltFunction(0, 0, 2);	// CTRL_SW_PWR_1
	InitAltFunction(0, 1, 2);	// CTRL_SW_PWR_2
#endif

	// Setup GPIO
	// Setup Inputs
	//InitInput(char port, char pin, PinInfo *pinInfo)
	InitInput(3, 8, &_pinInfo[AUX_NOT_AVAIL]);	// AUX_NOT_AVAIL
	InitInput(3, 9, &_pinInfo[MAIN_NOT_AVAIL]);	// MAIN_NOT_AVAIL
#ifdef FOUR_INPUTS
	InitInput(3, 10, &_pinInfo[INPUT_1]);		// INPUT_1
#else
	InitOutput(3, 10, &_pinInfo[INPUT_1]);		// INPUT_1
#endif
	InitInput(6, 7, &_pinInfo[INPUT_2]);		// INPUT_2
#ifdef FOUR_INPUTS
	InitInput(3, 4, &_pinInfo[INPUT_3]);		// INPUT_3
#else
	InitOutput(3, 4, &_pinInfo[INPUT_3]);		// INPUT_3
#endif
	InitInput(3, 5, &_pinInfo[INPUT_4]);		// INPUT_4
	// Setup Outputs
	//InitOutput(char port, char pin, PinInfo *pinInfo)
	InitOutput(2, 13, &_pinInfo[LED_RED]);		// LED_RED
	InitOutput(2, 14, &_pinInfo[LED_YELLOW]);	// LED_YELLOW
	InitOutput(2, 15, &_pinInfo[LED_GREEN]);		// LED_GREEN
}

GPIO_TypeDef *BspIo::GetGpioPort(char port)
{
	GPIO_TypeDef *gp = GPIOA;
	switch(port)
	{
		case 0:
		default:
		{
			gp = GPIOA;
			break;
		}
		case 1:
		{
			gp = GPIOB;
			break;
		}
		case 2:
		{
			gp = GPIOC;
			break;
		}
		case 3:
		{
			gp = GPIOD;
			break;
		}
		case 4:
		{
			gp = GPIOE;
			break;
		}
		case 5:
		{
			gp = GPIOF;
			break;
		}
		case 6:
		{
			gp = GPIOG;
			break;
		}
		case 7:
		{
			gp = GPIOH;
			break;
		}
		case 8:
		{
			gp = GPIOI;
			break;
		}
		case 9:
		{
			gp = GPIOJ;
			break;
		}
		case 10:
		{
			gp = GPIOK;
			break;
		}
	}
	return gp;
}

void BspIo::InitInput(char port, unsigned char pin, PinInfo *pinInfo)
{
	GPIO_TypeDef *gp = GetGpioPort(port);
	pin &= 0xF;

	// Set mode to input
	gp->MODER &= ~(3 << (pin << 1));
	gp->MODER |= (0 << (pin << 1));
	// Set speed to very high speed
	gp->OSPEEDR |= (3 << pin);
	// disable pulldown and pullup
	gp->PUPDR &= ~(3 << pin);
	gp->PUPDR |= (0 << pin);
	// Clear alternate function
	unsigned char reg = pin >> 3;
	gp->AFR[reg] &= ~(0xF << ((pin & 0x7) << 2));
	pinInfo->SetReg = (unsigned short *)&gp->BSRR;
	pinInfo->ClrReg = (unsigned short *)((unsigned long)&gp->BSRR + 2);
	pinInfo->StsReg = (unsigned short *)&gp->IDR;
	pinInfo->Mask = (1 << pin);
}

void BspIo::InitOutput(char port, unsigned char pin, PinInfo *pinInfo)
{
	GPIO_TypeDef *gp = GetGpioPort(port);
	pin &= 0xF;

	// Set mode to output
	gp->MODER &= ~(3 << (pin << 1));
	gp->MODER |= (1 << (pin << 1));
	// Set speed to very high speed
	gp->OSPEEDR |= (3 << pin);
	// disable pulldown and pullup
	gp->PUPDR &= ~(3 << pin);
	gp->PUPDR |= (0 << pin);
	// Clear alternate function
	unsigned char reg = pin >> 3;
	gp->AFR[reg] &= ~(0xF << ((pin & 0x7) << 2));
	pinInfo->SetReg = (unsigned short *)&gp->BSRR;
	pinInfo->ClrReg = (unsigned short *)((unsigned long)&gp->BSRR + 2);
	pinInfo->StsReg = (unsigned short *)&gp->IDR;
	pinInfo->Mask = (1 << pin);
}

void BspIo::InitAltFunction(char port, unsigned char pin, char alternate)
{
	GPIO_TypeDef *gp = GetGpioPort(port);
	pin &= 0xF;
	// Set mode to alternate
	gp->MODER &= ~(3 << (pin << 1));
	gp->MODER |= (2 << (pin << 1));
	// Set speed to very high speed
	gp->OSPEEDR |= (3 << pin);
	// disable pulldown and pullup
	gp->PUPDR &= ~(3 << pin);
	gp->PUPDR |= (0 << pin);
	// Set alternate function
	unsigned char reg = pin >> 3;
	alternate &= 0xF;
	gp->AFR[reg] &= ~(0xF << ((pin & 0x7) << 2));
	gp->AFR[reg] |= (alternate << ((pin & 0x7) << 2));
}

void BspIo::InitAnalog(char port, unsigned char pin)
{
	GPIO_TypeDef *gp = GetGpioPort(port);
	pin &= 0xF;

	// Set mode to analog
	gp->MODER |= (3 << (pin << 1));
	// Set speed to very high speed
	gp->OSPEEDR |= (3 << pin);
	// disable pulldown and pullup
	gp->PUPDR &= ~(3 << pin);
	gp->PUPDR |= (0 << pin);
	// Clear alternate function
	unsigned char reg = pin >> 3;
	gp->AFR[reg] &= ~(0xF << ((pin & 0x7) << 2));
}

