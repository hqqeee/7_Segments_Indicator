/*
 * Source file with IRQ Handlers.
 * It contains:
 * 		EXTI0_1_IRQHandler that will be processed if button(PA1) is pressed.
 * 		SysTickr_Handler blink LED every 1s and count milliseconds.
 * 		Default system handlers: NMI, HardFault, SVC, PendSV.
 */

#include "main.h"

volatile uint32_t disp_number = 0;
static uint32_t milliseconds = 0;

void EXTI0_1_IRQHandler(void)
{
	static uint32_t ms_old = 0;
	uint32_t ms = milliseconds;
	/* If between two interrupts past more than 200 milliseconds
 	 * it means that button was pressed.(button disbounce) */
	if(ms - ms_old > 200)
	{
		disp_number += 1;
	}
	ms_old = ms;
	/* Clear Pending register flag */
	WRITE_REG(EXTI->PR, 0x1);

}

void SysTick_Handler(void)
{
	milliseconds++;
	if(milliseconds%1000 == 0)
	{
			WRITE_REG(GPIOC -> ODR, (GPIOC->ODR ^ 0x100));
	}
}

/* System Handlers */

void NMI_Hander(void)
{
}

void HardFault_Handler(void)
{
	while(1);
}

void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}

