
#pragma once
#include "stm32f303xc.h"

#define DHT_TIMEOUT 				10000	
#define DHT_POLLING_CONTROL			1	
#define DHT_POLLING_INTERVAL_DHT11	2000	
#define DHT_POLLING_INTERVAL_DHT22	1000	
#define DHT_IRQ_CONTROL				

#define GPIO_MODE_Pos                           0u
#define OUTPUT_TYPE_Pos                         4u
#define MODE_OUTPUT                             (0x1uL << GPIO_MODE_Pos)
#define OUTPUT_OD                               (0x1uL << OUTPUT_TYPE_Pos)
#define  GPIO_MODE_OUTPUT_OD                    (MODE_OUTPUT | OUTPUT_OD)

#define MODE_INPUT                              (0x0uL << GPIO_MODE_Pos)
#define  GPIO_MODE_INPUT                        MODE_INPUT                                                  

#define  GPIO_SPEED_FREQ_HIGH     (0x00000003U)  


struct DHT_data
{
	float hum;
	float temp;
};

typedef enum {
	DHT11,
	DHT22
} DHT_type;

class DHT_sensor
{
public:
	DHT_sensor();
	DHT_data DHT_getData();

	float lastTemp;			 
	float lastHum;
private:
	void initGpio();
	void goToOutput();
	void goToInput();
	void lineDown();
	void lineUp();
	bool getLine();

};

















typedef struct
{
  uint32_t Pin;        /*!< Specifies the GPIO pins to be configured.
                           This parameter can be any value of @ref GPIO_pins */

  uint32_t Mode;       /*!< Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref GPIO_mode */

  uint32_t Pull;       /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                           This parameter can be a value of @ref GPIO_pull */

  uint32_t Speed;      /*!< Specifies the speed for the selected pins.
                           This parameter can be a value of @ref GPIO_speed */

  uint32_t Alternate;  /*!< Peripheral to be connected to the selected pins 
                            This parameter can be a value of @ref GPIOEx_Alternate_function_selection */
}GPIO_InitTypeDef;