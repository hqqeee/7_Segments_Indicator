/*
 *
 *  It is simple template project.
 *  RCC configured in config.c file.
 *
 */


#include "config.h"
#include "dyn_display.h"

int main(void)
{
	rcc_config();
	gpio_config();

	startup_animation();
	//WRITE_REG(GPIOB -> ODR, 0x1FFF);
	
	WRITE_REG(GPIOB -> ODR, 0x0);
	SET_BIT(GPIOC -> ODR, 0x9F00);
	while(1)
	{
		startup_animation();
	}
}
