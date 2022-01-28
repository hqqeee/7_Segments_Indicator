/*
 *	This file provides .. functions:
 *	 - rcc_config(): Setups System Clock.
 *	 		If SYSCLK48 defined System Clock configured as follow:
 *	 			> System Clock Source: PLL(HSI/2)
 *	 			> SYSCLK(Hz):		   48 000 000
 *	 			> HCLK(Hz):			   48 000 000
 *	 			> AHB Prescaler:	   1
 *	 			> APB Prescaler:	   1
 *	 			> HSI Frequancy(Hz):   8 000 000
 *	 			> PLL Multiplier:	   12
 *	 			> HSI PREDIV(CONST):   2
 *	 			> Flash Latency(WS):   1
 *			If SYSCLK48 isnt defined:	 		
 *	 			> System Clock Source: HSI
 *	 			> SYSCLK(Hz):		   8 000 000
 *	 			> HCLK(Hz):			   8 000 000
 *	 			> AHB Prescaler:       1
 *	 			> APB Prescaler:       1
 *	 			> PLL:				   OFF
 *				> Flash Latenct:	   0
 *
 *	 - rcc_reset(): Resets configurations bits, disable PLL, HSE and RCC interrupts.
 *
 */

#include "main.h"

static void rcc_reset(void);

void rcc_config(void)
{
	rcc_reset();
	#ifdef SYSCLK48
	/*
	 * PLL configuration.
	 * PLL Source: HSI/2 
	 * PLL Multiplier: 12
	 */
	SET_BIT(RCC->CFGR, (RCC_CFGR_PLLSRC_HSI_DIV2 | RCC_CFGR_PLLMUL12));				
	/* 
	 * Enable PLL
	 * Set PLLON bit
	 */
	SET_BIT(RCC->CR, RCC_CR_PLLON);
	/*
	 * Wait until PLL is stable
	 * Loop until PLLRDY flag is 1.	
	 */
	while(!READ_BIT(RCC->CR, RCC_CR_PLLRDY));
	/*
	 * Set PLL as system clock source.
	 * SW[1:0] = 10.
	 */
	SET_BIT(RCC->CFGR,RCC_CFGR_SW_PLL);
	/*
	 * Wait until PLL is set as system clock.
	 */
	while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
	/*
	 * Set Flash Latency 1
	 */
	SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY);
	#endif /* SYSCLK48*/
}

static void rcc_reset(void)
{	
	/* 
	 * HSI Enable 
	 * Set HSION bit 
	 */
	SET_BIT(RCC->CR,RCC_CR_HSION);
	/* 
	 * Wait until HSI is stable
	 * Loop until HSIRDY flag is 1. 
	 */
	while(!READ_BIT(RCC->CR, RCC_CR_HSIRDY));
	/* 
	 * Disable HSE, PLL and CSS
	 */
	CLEAR_BIT(RCC->CR, (RCC_CR_PLLON | RCC_CR_HSEON | RCC_CR_CSSON |RCC_CR_HSEBYP));
	/*
	 * Wait util PLL and HSE is reset.
	 */
	while(READ_BIT(RCC->CR, (RCC_CR_PLLRDY | RCC_CR_HSERDY)));
	/*
	 * RCC configuration reset.
	 * System clock(SW[1:0] = 00): HSI
	 */
	CLEAR_REG(RCC->CFGR);
	CLEAR_REG(RCC->CFGR2);
	CLEAR_REG(RCC->CFGR3);
	/*
	 * Wait until HSI is set as system clock. 
	 * til SWS[1:0] = 00
	 */
	while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS));
	/*
	 * Clock interrupt register reset(Disable RCC interruts).
	 */
	CLEAR_REG(RCC->CIR);
}

void gpio_config(void)
{
	/* 
	 * Clock on CPIOA, GPIOB, GPIOC
	 */
	SET_BIT(RCC->AHBENR, (RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN));	
	/* 
	 * GPIOA 0(build-in discovery board button)  in input mode.
	 * GPIOB 0-12(connection of 7 segment indicator) pins in GP output mode.
	 * GPIOC 8-9(build-in discovery board LEDs) in GP output mode.
	 */
	CLEAR_BIT(GPIOA->MODER, GPIO_MODER_MODER0);
	SET_BIT(GPIOB->MODER, 0x00AAAAAA);
	SET_BIT(GPIOC->MODER, 0x000A0000);
}
