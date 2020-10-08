/*
 * main.c
 *
 *  Created on: 2020 Sep 02 12:52:04
 *  Author: FORGE-15R
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "ext_lib/base.h"

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

volatile uint16_t direction_status;
volatile uint16_t clamp_status;
volatile uint32_t pin_status;
const uint16_t green_led = 0b11111111;
const uint16_t red_led = 0b00000000;
const TickType_t xDelay = 20/portTICK_PERIOD_MS;



static void tle94112el_enable(void);
static void tle94112el_disable(void);
static int32_t tle94112el_spi_transfer(uint8_t *tx_data, uint8_t *rx_data);

static const TLE94112EL_t TLE94112EL_0 =

  {

    .enable = tle94112el_enable,

    .disable = tle94112el_disable,

    .spi_transfer = tle94112el_spi_transfer

  };

TaskHandle_t FORWARD_Handle = NULL;
TaskHandle_t BACKWARD_Handle = NULL;
TaskHandle_t LEFT_Handle = NULL;
TaskHandle_t RIGHT_Handle = NULL;
TaskHandle_t UP_Handle = NULL;
TaskHandle_t DOWN_Handle = NULL;
TaskHandle_t OPEN_Handle = NULL;
TaskHandle_t CLOSE_Handle = NULL;
TaskHandle_t HOLD_Handle = NULL;
TaskHandle_t ROTATE_Handle = NULL;
TaskHandle_t DIRECTION_Handle = NULL;
TaskHandle_t CLAMP_Handle = NULL;

SemaphoreHandle_t FORWARD_interruptSemaphore;
SemaphoreHandle_t BACKWARD_interruptSemaphore;
SemaphoreHandle_t LEFT_interruptSemaphore;
SemaphoreHandle_t RIGHT_interruptSemaphore;
SemaphoreHandle_t UP_interruptSemaphore;
SemaphoreHandle_t DOWN_interruptSemaphore;
SemaphoreHandle_t OPEN_interruptSemaphore;
SemaphoreHandle_t CLOSE_interruptSemaphore;
SemaphoreHandle_t HOLD_interruptSemaphore;
SemaphoreHandle_t ROTATE_interruptSemaphore;
SemaphoreHandle_t DIRECTION_interruptSemaphore;
SemaphoreHandle_t CLAMP_interruptSemaphore;


void FORWARD_Task(void *p){

	while(1){

		if (xSemaphoreTake(FORWARD_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&DIRECTION_INTERRUPT);
			if(pin_status==1){
				//FORWARD
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x99);
				  vTaskDelay( xDelay );

					TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x02, 0x99);
					  vTaskDelay( xDelay );

					  TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x99);
				  vTaskDelay( xDelay );

					 DIGITAL_IO_SetOutputHigh(&MOTOR_HIGH);
					  vTaskDelay( xDelay );

					 DIGITAL_IO_SetOutputLow(&MOTOR_LOW);
					  vTaskDelay( xDelay );

			}

			else{
				//stop
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x00);

				  vTaskDelay( xDelay );

					TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x02, 0x00);
					  vTaskDelay( xDelay );

				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x00);
				  vTaskDelay( xDelay );

					 DIGITAL_IO_SetOutputLow(&MOTOR_HIGH);
					  vTaskDelay( xDelay );

					 DIGITAL_IO_SetOutputLow(&MOTOR_LOW);
					  vTaskDelay( xDelay );
			}
		}
	}
}

void BACKWARD_Task(void *p){

	while(1){

		if (xSemaphoreTake(BACKWARD_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&DIRECTION_INTERRUPT);
			if(pin_status==1){
				//BACKWARD
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x66);

				  vTaskDelay( xDelay );
					TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x02, 0x66);
					  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x66);
				  vTaskDelay( xDelay );

					 DIGITAL_IO_SetOutputLow(&MOTOR_HIGH);
					  vTaskDelay( xDelay );

					 DIGITAL_IO_SetOutputHigh(&MOTOR_LOW);
					  vTaskDelay( xDelay );
			}

			else{
				//stop
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x00);

				  vTaskDelay( xDelay );
					TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x02, 0x00);
					  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x00);
				  vTaskDelay( xDelay );

					 DIGITAL_IO_SetOutputLow(&MOTOR_HIGH);
					  vTaskDelay( xDelay );

					 DIGITAL_IO_SetOutputLow(&MOTOR_LOW);
					  vTaskDelay( xDelay );

			}
		}
	}
}

void LEFT_Task(void *p){

	while(1){

		if (xSemaphoreTake(LEFT_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&DIRECTION_INTERRUPT);
			if(pin_status==1){
				//LEFT
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x66);

				  vTaskDelay( xDelay );
					TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x02, 0x99);
					  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x99);
				  vTaskDelay( xDelay );
					 DIGITAL_IO_SetOutputLow(&MOTOR_HIGH);
					  vTaskDelay( xDelay );

					 DIGITAL_IO_SetOutputHigh(&MOTOR_LOW);
					  vTaskDelay( xDelay );
			}

			else{
				//stop
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x00);

				  vTaskDelay( xDelay );
					TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x02, 0x00);
					  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x00);
				  vTaskDelay( xDelay );
					 DIGITAL_IO_SetOutputLow(&MOTOR_HIGH);
					  vTaskDelay( xDelay );

					 DIGITAL_IO_SetOutputLow(&MOTOR_LOW);
					  vTaskDelay( xDelay );
			}
		}
	}
}

void RIGHT_Task(void *p){

	while(1){

		if (xSemaphoreTake(RIGHT_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&DIRECTION_INTERRUPT);
			if(pin_status==1){
				//RIGHT
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x99);

				  vTaskDelay( xDelay );
					TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x02, 0x66);
					  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x66);
				  vTaskDelay( xDelay );
					 DIGITAL_IO_SetOutputHigh(&MOTOR_HIGH);
					  vTaskDelay( xDelay );

					 DIGITAL_IO_SetOutputLow(&MOTOR_LOW);
					  vTaskDelay( xDelay );
			}

			else{
				//stop
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x01, 0x00);

				  vTaskDelay( xDelay );
					TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x02, 0x00);
					  vTaskDelay( xDelay );
				TLE94112EL_SetHBRegdata(&TLE94112EL_0, 0x03, 0x00);
				  vTaskDelay( xDelay );
					 DIGITAL_IO_SetOutputLow(&MOTOR_HIGH);
					  vTaskDelay( xDelay );

					 DIGITAL_IO_SetOutputLow(&MOTOR_LOW);
					  vTaskDelay( xDelay );
			}
		}
	}
}

void UP_Task(void *p){

	while(1){

		if (xSemaphoreTake(UP_interruptSemaphore, portMAX_DELAY) == pdPASS){

	 	  	// sets the duty to 3%.
	    	// LIFT UP
			PWM_SetDutyCycle(&PWM_LIFT,800);
			vTaskDelay( xDelay );
			PWM_SetDutyCycle(&PWM_LIFT,700);
			vTaskDelay( xDelay );
			PWM_SetDutyCycle(&PWM_LIFT,600);
			vTaskDelay( xDelay );
			PWM_SetDutyCycle(&PWM_LIFT,500);
			vTaskDelay( xDelay );
			PWM_SetDutyCycle(&PWM_LIFT,400);
			vTaskDelay( xDelay );
			PWM_SetDutyCycle(&PWM_LIFT,300);

		}
	}
}

void DOWN_Task(void *p){

	while(1){

		if (xSemaphoreTake(DOWN_interruptSemaphore, portMAX_DELAY) == pdPASS){

	 	  	// sets the duty to 9 %.
	    	// LIFT DOWN
			PWM_SetDutyCycle(&PWM_LIFT,400);
			vTaskDelay( xDelay );
			PWM_SetDutyCycle(&PWM_LIFT,500);
			vTaskDelay( xDelay );
			PWM_SetDutyCycle(&PWM_LIFT,600);
			vTaskDelay( xDelay );
	    	PWM_SetDutyCycle(&PWM_LIFT,700);
	    	vTaskDelay( xDelay );
	    	PWM_SetDutyCycle(&PWM_LIFT,800);
	    	vTaskDelay( xDelay );
	    	PWM_SetDutyCycle(&PWM_LIFT,900);

		}
	}
}

void OPEN_Task(void *p){

	while(1){

		if (xSemaphoreTake(OPEN_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&CLAMP_INTERRUPT);
		     if(pin_status == 1)
		     {
		 	  	// sets the duty to 2%.
		    	// clamp open
		    	 PWM_SetDutyCycle(&PWM_CLAMP,200);
		     }

		     else
		     {
		    	 // sets the channel duty to 0%.
		    	 // clamp maintain
		    	 PWM_SetDutyCycle(&PWM_CLAMP,0);
		     }

		 	pin_status = 0;

		}
	}
}

void CLOSE_Task(void *p){

	while(1){

		if (xSemaphoreTake(CLOSE_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&CLAMP_INTERRUPT);
		     if(pin_status == 1)
		     {
		 	  	// sets the duty to 9%.
		    	// clamp CLOSE
		    	 PWM_SetDutyCycle(&PWM_CLAMP,900);
		     }

//		     else
//		     {
//		    	 // sets the channel duty to 9%.
//		    	 // clamp maintain
//		    	 PWM_SetDutyCycle(&PWM_CLAMP,900);
//		     }

		 	pin_status = 0;

		}
	}
}

void HOLD_Task(void *p){

	while(1){

		if (xSemaphoreTake(HOLD_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&HOLD_INTERRUPT);
		     if(pin_status == 1)
		     {
		    	 // sets the channel duty to 8%.
		    	 // clamp maintain
		    	 PWM_SetDutyCycle(&PWM_CLAMP,800);
		     }

		 	pin_status = 0;

		}
	}
}

void ROTATE_Task(void *p){

	while(1){

		if (xSemaphoreTake(ROTATE_interruptSemaphore, portMAX_DELAY) == pdPASS){

			pin_status = PIN_INTERRUPT_GetPinValue(&ROTATE_INTERRUPT);
		     if(pin_status == 1)
		     {
				 BUS_IO_Write(&LED_BUS_IO, green_led);	//LED INDICATOR
				// sets the duty to 3%.
				// Metal
				PWM_SetDutyCycle(&PWM_ROTATE,800);
				vTaskDelay( xDelay );
				PWM_SetDutyCycle(&PWM_ROTATE,700);
				vTaskDelay( xDelay );
				PWM_SetDutyCycle(&PWM_ROTATE,600);
				vTaskDelay( xDelay );
				PWM_SetDutyCycle(&PWM_ROTATE,500);
				vTaskDelay( xDelay );
				PWM_SetDutyCycle(&PWM_ROTATE,400);
				vTaskDelay( xDelay );
				PWM_SetDutyCycle(&PWM_ROTATE,300);
				vTaskDelay( xDelay );
				PWM_SetDutyCycle(&PWM_ROTATE,200);

		     }

		     else
		     {
		    	 BUS_IO_Write(&LED_BUS_IO, red_led);	//LED INDICATOR
				// sets the duty to 10 %.
				// NON-metal
				PWM_SetDutyCycle(&PWM_ROTATE,400);
				vTaskDelay( xDelay );
				PWM_SetDutyCycle(&PWM_ROTATE,500);
				vTaskDelay( xDelay );
				PWM_SetDutyCycle(&PWM_ROTATE,600);
				vTaskDelay( xDelay );
				PWM_SetDutyCycle(&PWM_ROTATE,700);
				vTaskDelay( xDelay );
				PWM_SetDutyCycle(&PWM_ROTATE,800);
				vTaskDelay( xDelay );
				PWM_SetDutyCycle(&PWM_ROTATE,900);

		     }
		}
	}
}

void DIRECTION_Task(void *p){

	while(1){

		if (xSemaphoreTake(DIRECTION_interruptSemaphore, portMAX_DELAY) == pdPASS){

			direction_status = BUS_IO_Read(&DIRECTION_BUS_IO);

			switch(direction_status){

			case 0:
				xSemaphoreGiveFromISR(FORWARD_interruptSemaphore, NULL);
				break;

			case 1:
				xSemaphoreGiveFromISR(BACKWARD_interruptSemaphore, NULL);
				break;

			case 2:
				xSemaphoreGiveFromISR(LEFT_interruptSemaphore, NULL);
				break;

			case 3:
				xSemaphoreGiveFromISR(RIGHT_interruptSemaphore, NULL);
				break;

			}
		}
	}
}

void CLAMP_Task(void *p){

	while(1){

		if (xSemaphoreTake(CLAMP_interruptSemaphore, portMAX_DELAY) == pdPASS){

			clamp_status = BUS_IO_Read(&CLAMP_BUS_IO);

			switch(clamp_status){

			case 0:
				xSemaphoreGiveFromISR(UP_interruptSemaphore, NULL);
				break;

			case 1:
				xSemaphoreGiveFromISR(DOWN_interruptSemaphore, NULL);
				break;

			case 2:
				xSemaphoreGiveFromISR(OPEN_interruptSemaphore, NULL);
				break;

			case 3:
				xSemaphoreGiveFromISR(CLOSE_interruptSemaphore, NULL);
				break;

			}
		}
	}
}

int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if(status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }

	// LIFT DOWN
	 PWM_SetDutyCycle(&PWM_LIFT,900);
	 PWM_SetDutyCycle(&PWM_ROTATE,200);

	 BUS_IO_Write(&LED_BUS_IO, red_led);	//LED INDICATOR
	 DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);


	// ENABLE DC Motor Shield
	TLE94112EL_Enable(&TLE94112EL_0);

	// Initialize the FreeRTOS
	xTaskCreate(FORWARD_Task, "FORWARD", 200, NULL, tskIDLE_PRIORITY, &FORWARD_Handle);
	xTaskCreate(BACKWARD_Task, "BACKWARD", 200, NULL, tskIDLE_PRIORITY, &BACKWARD_Handle);
	xTaskCreate(LEFT_Task, "LEFT", 200, NULL, tskIDLE_PRIORITY, &LEFT_Handle);
	xTaskCreate(RIGHT_Task, "RIGHT", 200, NULL, tskIDLE_PRIORITY, &RIGHT_Handle);

	xTaskCreate(UP_Task, "UP", 200, NULL, tskIDLE_PRIORITY, &UP_Handle);
	xTaskCreate(DOWN_Task, "DOWN", 200, NULL, tskIDLE_PRIORITY, &DOWN_Handle);
	xTaskCreate(OPEN_Task, "OPEN", 200, NULL, tskIDLE_PRIORITY, &OPEN_Handle);
	xTaskCreate(CLOSE_Task, "CLOSE", 200, NULL, tskIDLE_PRIORITY, &CLOSE_Handle);
	xTaskCreate(HOLD_Task, "HOLD", 200, NULL, tskIDLE_PRIORITY, &HOLD_Handle);

	xTaskCreate(ROTATE_Task, "ROTATE", 200, NULL, tskIDLE_PRIORITY, &ROTATE_Handle);
	xTaskCreate(DIRECTION_Task, "DIRECTION", 200, NULL, tskIDLE_PRIORITY, &DIRECTION_Handle);
	xTaskCreate(CLAMP_Task, "CLAMP", 200, NULL, tskIDLE_PRIORITY, &CLAMP_Handle);


	FORWARD_interruptSemaphore = xSemaphoreCreateBinary();
	BACKWARD_interruptSemaphore = xSemaphoreCreateBinary();
	LEFT_interruptSemaphore = xSemaphoreCreateBinary();
	RIGHT_interruptSemaphore = xSemaphoreCreateBinary();

	UP_interruptSemaphore = xSemaphoreCreateBinary();
	DOWN_interruptSemaphore = xSemaphoreCreateBinary();
	OPEN_interruptSemaphore = xSemaphoreCreateBinary();
	CLOSE_interruptSemaphore = xSemaphoreCreateBinary();
	HOLD_interruptSemaphore = xSemaphoreCreateBinary();

	ROTATE_interruptSemaphore = xSemaphoreCreateBinary();
	DIRECTION_interruptSemaphore = xSemaphoreCreateBinary();
	CLAMP_interruptSemaphore = xSemaphoreCreateBinary();

	vTaskStartScheduler();
	// Initialize the FreeRTOS




  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {

  }
}

void ROTATE_IRQHandler(void){

	xSemaphoreGiveFromISR(ROTATE_interruptSemaphore, NULL);
}

void DIRECTION_IRQHandler(void){

	xSemaphoreGiveFromISR(DIRECTION_interruptSemaphore, NULL);
}

void CLAMP_IRQHandler(void){

	xSemaphoreGiveFromISR(CLAMP_interruptSemaphore, NULL);
}

void HOLD_IRQHandler(void){

	xSemaphoreGiveFromISR(HOLD_interruptSemaphore, NULL);
}

static void tle94112el_enable(void)

{

  DIGITAL_IO_SetOutputHigh(&TLE94112_ENABLE);

}

static void tle94112el_disable(void)

{

  DIGITAL_IO_SetOutputLow(&TLE94112_ENABLE);

}

static int32_t tle94112el_spi_transfer(uint8_t *tx_data, uint8_t *rx_data)

{

  XMC_SPI_CH_SetBitOrderLsbFirst(SPI_MASTER_0.channel);



  DIGITAL_IO_SetOutputLow(&TLE94112_CS);



  SPI_MASTER_Transfer(&SPI_MASTER_0, tx_data, rx_data, 2);

  while(SPI_MASTER_0.runtime->rx_busy);



  DIGITAL_IO_SetOutputHigh(&TLE94112_CS);

  return 0;

}
