#pragma once

namespace esphome {
namespace xy6020 {

static const float TWO_DEC_UNIT = 0.01;
static const float ONE_DEC_UNIT = 0.1;
static const float NO_DEC_UNIT = 1;
static const float MULTIPLY_TEN_UNIT = 10;
static const float MULTIPLY_THOUSAND_UNIT = 1000;
 
/* STATUS REGISTERS */

static const uint16_t XY6020_OUTPUT_VOLTAGE = 0x02;
static const uint16_t XY6020_CURRENT = 0x03;
static const uint16_t XY6020_POWER_OUTPUT_DISPLAY = 0x04;
static const uint16_t XY6020_INPUT_VOLTAGE = 0x05;
static const uint16_t XY6020_TEMPERATUR_INTERNAL = 0x0D;



}  // namespace xy6020
}  // namespace esphome
