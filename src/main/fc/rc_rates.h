/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>

#include "pg/pg.h"

#define CONTROL_RATE_CONFIG_RC_EXPO_MAX         100
#define CONTROL_RATE_CONFIG_RC_RATES_MAX        255
#define CONTROL_RATE_CONFIG_SUPER_RATE_MAX      255

#define CONTROL_RATE_CONFIG_RATE_LIMIT_MIN      200
#define CONTROL_RATE_CONFIG_RATE_LIMIT_MAX      2000

#define SETPOINT_RATE_LIMIT 2000

typedef enum {
    RATES_TYPE_NONE = 0,
    RATES_TYPE_BETAFLIGHT,
    RATES_TYPE_RACEFLIGHT,
    RATES_TYPE_KISS,
    RATES_TYPE_ACTUAL,
    RATES_TYPE_QUICK,
    RATES_TYPE_COUNT
} ratesType_e;

typedef struct ratesSettingsLimits_s {
    uint8_t rc_rate_limit;
    uint8_t srate_limit;
    uint8_t expo_limit;
} ratesSettingsLimits_t;

#define MAX_RATE_PROFILE_NAME_LENGTH 8

typedef struct controlRateConfig_s {
    char profileName[MAX_RATE_PROFILE_NAME_LENGTH + 1];

    uint8_t rates_type;

    uint8_t rcRates[4];
    uint8_t rcExpo[4];
    uint8_t rates[4];

    uint8_t levelExpo[2];                   // roll/pitch level mode expo
    uint8_t quickRatesRcExpo;               // Sets expo on rc command for quick rates

    uint16_t rate_limit[4];
    uint16_t accel_limit[4];

    uint8_t rates_smoothness;
    uint8_t cyclic_ring;

} controlRateConfig_t;

PG_DECLARE_ARRAY(controlRateConfig_t, CONTROL_RATE_PROFILE_COUNT, controlRateProfiles);


extern controlRateConfig_t * currentControlRateProfile;
extern const ratesSettingsLimits_t ratesSettingLimits[RATES_TYPE_COUNT];

float applyRatesCurve(const int axis, float rcCommandf);

void initControlRates(void);
void loadControlRateProfile(void);
void changeControlRateProfile(uint8_t controlRateProfileIndex);
void copyControlRateProfile(uint8_t dstControlRateProfileIndex, uint8_t srcControlRateProfileIndex);
