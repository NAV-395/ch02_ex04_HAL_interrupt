
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#define GPIO_INTERRUPT_PRIORITY (7u)
/* Interrupt callback function */
//bool a=1;
static void button_isr(void *handler_arg, cyhal_gpio_event_t event)
{
	//a=!a;
	cyhal_gpio_toggle(CYBSP_USER_LED);
}
/* GPIO callback initialization structure */
cyhal_gpio_callback_data_t cb_data =
{
.callback = button_isr,
.callback_arg = NULL
};

int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    __enable_irq();

    cyhal_gpio_init (CYBSP_USER_LED , CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG , 1);
    cyhal_gpio_init(CYBSP_USER_BTN, CYHAL_GPIO_DIR_INPUT,CYHAL_GPIO_DRIVE_PULLUP, CYBSP_BTN_OFF);
    cyhal_gpio_register_callback(CYBSP_USER_BTN, &cb_data);
    cyhal_gpio_enable_event(CYBSP_USER_BTN, CYHAL_GPIO_IRQ_FALL,GPIO_INTERRUPT_PRIORITY, true);
    for (;;)
    {

    }
}

