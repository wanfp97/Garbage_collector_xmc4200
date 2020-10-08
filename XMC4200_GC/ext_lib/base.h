#ifndef BASE_H
#define BASE_H

#include "tle94112el.h"

void TLE94112EL_SetHBRegdata(const TLE94112EL_t *const handler, uint8_t TLE94112EL_HB_ACT_X_CTRL, uint8_t regdata);
void TLE94112EL_SetRegdata(const TLE94112EL_t *const handler, uint8_t TLE_REG, uint8_t regdata);

#endif
