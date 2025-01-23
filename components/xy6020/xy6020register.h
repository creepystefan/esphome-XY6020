#pragma once

namespace esphome {
namespace xy6020 {

static const float TWO_DEC_UNIT = 0.01;
static const float ONE_DEC_UNIT = 0.1;
static const float NO_DEC_UNIT = 1;
static const float MULTIPLY_TEN_UNIT = 10;
static const float MULTIPLY_THOUSAND_UNIT = 1000;
 
/* STATUS REGISTERS */
static const uint16_t XY6020_SETED_OUTPUT_VOLTAGE = 0x00;    //V_SET
static const uint16_t XY6020_SETED_OUTPUT_CURRENT = 0x01;    //C_SET
static const uint16_t XY6020_OUTPUT_VOLTAGE = 0x02;        //VOUT
static const uint16_t XY6020_OUTPUT_CURRENT = 0x03;        //IOUT
static const uint16_t XY6020_OUTPUT_POWER = 0x04;          //POWER
static const uint16_t XY6020_INPUT_VOLTAGE = 0x05;         //UIN
//static const uint16_t XY6020_KEY_LOCK = 0x0f;              //KEY LOCK
//  bit 0 = unlock
//  bit 1 = locked
//static const uint16_t XY6020_PROTECT_STATE = 0x10;         //Protect_state
static const uint16_t XY6020_TEMPERATURE_INTERN = 0x0D;    //t_in
static const uint16_t XY6020_TEMPERATURE_EXTERN = 0x0E;    //t_ex
//static const uint16_t XY6020_OVERPOWER_PROTECT_VALUE = 0x55;    //0x55
//static const uint16_t XY6020_OVERTEMP_PROTECT_VALUE = 0x5c;    //0x55
static const uint16_t XY6020_MODEL = 0x16;                      //MODEL
static const uint16_t XY6020_SOFTWARE_VERSION = 0x17;         //FirmwareVersion
    


}  // namespace xy6020
}  // namespace esphome
