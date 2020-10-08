#include "base.h"

void TLE94112EL_SetHBRegdata(const TLE94112EL_t *const handler, uint8_t TLE94112EL_HB_ACT_X_CTRL, uint8_t regdata)
{
  uint8_t tx_data[2];
  uint8_t rx_data[2];
  uint8_t addr;

	switch(TLE94112EL_HB_ACT_X_CTRL){

		case 1:
			addr = TLE94112EL_HB_ACT_1_CTRL;
			break;

		case 2:
			addr = TLE94112EL_HB_ACT_2_CTRL;
			break;

		case 3:
			addr = TLE94112EL_HB_ACT_3_CTRL;
			break;

	}

	  //write
	  tx_data[0] = addr | 0x80;
	  tx_data[1] = regdata;
	  handler->spi_transfer(tx_data, rx_data);
}

void TLE94112EL_SetRegdata(const TLE94112EL_t *const handler, uint8_t TLE_REG, uint8_t regdata)
{
	  uint8_t tx_data[2];
	  uint8_t rx_data[2];
	  uint8_t addr = TLE_REG;

	  //write
	  tx_data[0] = addr | 0x80;
	  tx_data[1] = regdata;
	  handler->spi_transfer(tx_data, rx_data);
}


