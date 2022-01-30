/*
 *  It is simple project for STM32f051.
 *  It blinks LED connected to PC8 every 1 seconds.
 *  It shows some statup animation on 7segment display.
 *  PC9 LED is always on.
 *  After every button press it counts some number and displays it.
 */


#include "config.h"
#include "dyn_display.h"
#include "irq_handlers.h"

int main(void)
{
	rcc_config();
	gpio_config();
	exti_config();
	/* The Systick Config function argument
	 * must be 0...2^23, otherwise the function will return 1 and loop
	 * SystemCoreClock/1000 = 1ms between two interrupts.
	 */
	while(SysTick_Config(SystemCoreClock/1000));
	startup_animation();
	
	WRITE_REG(GPIOB -> ODR, 0x0);
	SET_BIT(GPIOC -> ODR, 0x200);
	while(1)
	{
		display_number(disp_number);
	}
}
