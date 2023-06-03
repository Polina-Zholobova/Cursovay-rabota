/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#include "RTE_Components.h"
#include CMSIS_device_header
#include "cmsis_os2.h"

#include "TempDevice.h"
#include "UsartUser.h"

void UART_Init(void);

volatile uint8_t t;
unsigned int i;
void delay() {
  for (i = 0; i < 1000000; i++)
    ;
}

/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/

int ClockInit(void) {
  __IO int StartUpCounter;

  RCC->CR |= (1 << RCC_CR_HSEON_Pos);

  for (StartUpCounter = 0;; StartUpCounter++) {
    if (RCC->CR & (1 << RCC_CR_HSERDY_Pos))
      break;

    if (StartUpCounter > 0x1000) {
      RCC->CR &= ~(1 << RCC_CR_HSEON_Pos);
      return 1;
    }
  }

  RCC->CFGR |= (0x07 << RCC_CFGR_PLLMUL_Pos) | (0x01 << RCC_CFGR_PLLSRC_Pos);

  RCC->CR |= (1 << RCC_CR_PLLON_Pos);

  for (StartUpCounter = 0;; StartUpCounter++) {

    if (RCC->CR & (1 << RCC_CR_PLLRDY_Pos))
      break;

    if (StartUpCounter > 0x1000) {
      RCC->CR &= ~(1 << RCC_CR_HSEON_Pos);
      RCC->CR &= ~(1 << RCC_CR_PLLON_Pos);
      return 2;
    }
  }

  FLASH->ACR |= (0x02 << FLASH_ACR_LATENCY_Pos);

  RCC->CFGR |= (0x00 << RCC_CFGR_PPRE2_Pos) | (0x04 << RCC_CFGR_PPRE1_Pos) |
               (0x00 << RCC_CFGR_HPRE_Pos);

  RCC->CFGR |= (0x02 << RCC_CFGR_SW_Pos);

  while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != (0x02 << RCC_CFGR_SWS_Pos))

  {
  }

  RCC->CR &= ~(1 << RCC_CR_HSION_Pos);

  return 0;
}


DigitalFilter temperatureFilter(1.0);
DigitalFilter humidityFilter(1.0);

TempDevice temperatureClass(humidityFilter, temperatureFilter);

void ConvertTemperatureToString(const double t, char *msg, int size) {
  int16_t temperature = (int16_t)(t * 10);

  uint16_t indx = 0;
  constexpr int MaxIdx = 22;

  //assert(size < MaxIdx);
	size = (size < MaxIdx) ? size : MaxIdx;

  msg[indx++] = 'T';
  msg[indx++] = 'e';
  msg[indx++] = 'm';
  msg[indx++] = 'p';
  msg[indx++] = 'e';
  msg[indx++] = 'r';
  msg[indx++] = 'a';
  msg[indx++] = 't';
  msg[indx++] = 'u';
  msg[indx++] = 'r';
  msg[indx++] = 'e';
  msg[indx++] = ':';
  msg[indx++] = ' ';

  if (temperature < 0) {
    msg[indx++] = '-';
  }

  msg[indx++] = temperature / 1000 + '0';
  msg[indx++] = temperature / 100 + '0';
  msg[indx++] = temperature / 10 % 10 + '0';
  msg[indx++] = ',';
  msg[indx++] = temperature % 10 + '0';
  msg[indx++] = '0';
  msg[indx++] = '\n';
}


__NO_RETURN static void TempTask(void *arg)
{
  (void)arg;

  for (;;)
  {
    osDelay(852);
    temperatureClass.updateTemp();
    temperatureClass.updateHum();
  }
}

__NO_RETURN static void UsartTask(void *arg)
{
  //(void)arg;
  constexpr int MaxMessageSize = 22;
  char msg[MaxMessageSize];
  UsartUser _parametr;
  _parametr.Init();
  TempDevice& temp = (TempDevice &)* arg;
  int a = 0;

  for (;;) {
    osDelay(3000);

    double _temperature = 0.0;
		double _hum = 0.0;

    //core_util_critical_section_enter();
		__disable_irq();
    _temperature = temp.getTemp();
    _hum				 = temp.getHum();
		//core_util_critical_section_exit();
		__enable_irq();

    ConvertTemperatureToString(_temperature, msg, MaxMessageSize);
    _parametr.Send(msg);
  }
}



int main(void) {

  int a = ClockInit();
  SystemCoreClockUpdate();

  osKernelInitialize();
  osThreadNew(TempTask, NULL, NULL);
  osThreadNew(UsartTask, &temperatureClass, NULL);
  osKernelStart();

  for (;;) {
  }
}
