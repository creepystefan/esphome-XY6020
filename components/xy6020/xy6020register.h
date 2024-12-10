#pragma once

namespace esphome {
namespace xy6020 {

static const float TWO_DEC_UNIT = 0.01;
static const float ONE_DEC_UNIT = 0.1;
static const float NO_DEC_UNIT = 1;
static const float MULTIPLY_TEN_UNIT = 10;
static const float MULTIPLY_THOUSAND_UNIT = 1000;
 
/* PHASE STATUS REGISTERS */
//static const uint16_t SELEC_VOLTAGE_VALUE_SETTING = 0x00;
//static const uint16_t SELEC_CURRENT_VALUE_SETTING = 0x01;
static const uint16_t SELEC_VOLTAGE_VALUE_DISPLAY = 0x02;
static const uint16_t SELEC_CURRENT_VALUE_DISPLAY = 0x03;
static const uint16_t SELEC_POWER_OUTPUT_DISPLAY = 0x04;
static const uint16_t SELEC_VOLTAGE_INPUT_DISPLAY = 0x05;
static const uint16_t SELEC_TEMPERATUR_INTERNAL_DISPLAY = 0x0D;
static const uint16_t SELEC_TEMPERATUR_EXTERNAL_DISPLAY = 0x0E;


}  // namespace xy6020
}  // namespace esphome
