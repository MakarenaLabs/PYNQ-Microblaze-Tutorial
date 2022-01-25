/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xgpio.h"
#include "xil_printf.h"

#include "circular_buffer.h"

/************************** Constant Definitions *****************************/

#define LED 0x01   /* Assumes bit 0 of GPIO is connected to an LED  */

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define GPIO_EXAMPLE_DEVICE_ID  XPAR_GPIO_1_DEVICE_ID

/*
 * The following constant is used to wait after an LED is turned on to make
 * sure that it is visible to the human eye.  This constant might need to be
 * tuned for faster or slower processor speeds.
 */
#define LED_DELAY     10000000/2

/*
 * The following constant is used to determine which channel of the GPIO is
 * used for the LED if there are 2 channels supported.
 */
#define LED_CHANNEL 1

#define WRITE_LED	0x9
#define READ_LED 	0x23
#define TEST_CYCLE 	0x69


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/

#ifdef PRE_2_00A_APPLICATION

/*
 * The following macros are provided to allow an application to compile that
 * uses an older version of the driver (pre 2.00a) which did not have a channel
 * parameter. Note that the channel parameter is fixed as channel 1.
 */
#define XGpio_SetDataDirection(InstancePtr, DirectionMask) \
        XGpio_SetDataDirection(InstancePtr, LED_CHANNEL, DirectionMask)

#define XGpio_DiscreteRead(InstancePtr) \
        XGpio_DiscreteRead(InstancePtr, LED_CHANNEL)

#define XGpio_DiscreteWrite(InstancePtr, Mask) \
        XGpio_DiscreteWrite(InstancePtr, LED_CHANNEL, Mask)

#define XGpio_DiscreteSet(InstancePtr, Mask) \
        XGpio_DiscreteSet(InstancePtr, LED_CHANNEL, Mask)

#endif

/************************** Function Prototypes ******************************/


/************************** Variable Definitions *****************************/

/*
 * The following are declared globally so they are zeroed and so they are
 * easily accessible from a debugger
 */

XGpio Gpio; /* The Instance of the GPIO Driver */

/*****************************************************************************/
/**
*
* The purpose of this function is to illustrate how to use the GPIO
* driver to turn on and off an LED.
*
*
* @return	XST_FAILURE to indicate that the GPIO Initialization had
*		failed.
*
* @note		This function will not return if the test is running.
*
******************************************************************************/
int main(void)
{
	int Status;
	volatile int Delay;
	int led_status = 0;
	int cmd;
	u16 data;
	/* Initialize the GPIO driver */
	Status = XGpio_Initialize(&Gpio, GPIO_EXAMPLE_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("Gpio Initialization Failed\r\n");
		return XST_FAILURE;
	}

	/* Set the direction for all signals as inputs except the LED output */
	XGpio_SetDataDirection(&Gpio, LED_CHANNEL, ~LED);

	/* Loop forever blinking the LED */

	while (1) {
        while((MAILBOX_CMD_ADDR & 0x01)==0);
        cmd = MAILBOX_CMD_ADDR;

        switch(cmd){
              case WRITE_LED:
                  data = (u16) MAILBOX_DATA(0);
                  if(data == 1){
              		/* Set the LED to High */
              		XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, LED);
                  } else {
              		XGpio_DiscreteClear(&Gpio, LED_CHANNEL, LED);
                  }
                  led_status = data;
                  MAILBOX_CMD_ADDR = 0x0;
                  break;
              case READ_LED:
            	  MAILBOX_DATA(0) = (u16) led_status;
                  MAILBOX_CMD_ADDR = 0x0;
                  break;
              case TEST_CYCLE:
                  MAILBOX_CMD_ADDR = 0x0;
            	  for(int j = 0; j < 1000000; ++j){
                		XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, LED);
                  		XGpio_DiscreteClear(&Gpio, LED_CHANNEL, LED);
            	  }
            	  break;

              default:
                  MAILBOX_CMD_ADDR = 0x0;
                  break;
        }
//		/* Set the LED to High */
//		XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, LED);
//
//		/* Wait a small amount of time so the LED is visible */
//		for (Delay = 0; Delay < LED_DELAY; Delay++);
//
//		/* Clear the LED bit */
//		XGpio_DiscreteClear(&Gpio, LED_CHANNEL, LED);
//
//		/* Wait a small amount of time so the LED is visible */
//		for (Delay = 0; Delay < LED_DELAY; Delay++);
//
//		MAILBOX_DATA(0) = 69;
	}

}
