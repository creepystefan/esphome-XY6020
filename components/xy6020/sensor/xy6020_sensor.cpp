#include "xy6020_sensor.h"
#include "xy6020register_sensor.h"
#include "esphome/core/log.h"

// ORIGInAL from selec_meter

namespace esphome {
namespace xy6020 {

static const char *const TAG = "xy6020";

static const uint8_t MODBUS_CMD_READ_IN_REGISTERS = 0x03;
static const uint8_t MODBUS_REGISTER_COUNT = 20;  // 20 x 16-bit registers

void XY6020Sensor::on_modbus_data(const std::vector<uint8_t> &data) {
  if (data.size() < MODBUS_REGISTER_COUNT * 2) {
    ESP_LOGW(TAG, "Invalid size for XY6020!");
    return;
  }
  auto xy6020_get_16bit = [&](size_t i, uint16_t unit) -> uint16_t {  
 //   uint32_t temp = encode_uint32(data[i + 2], data[i + 3], data[i], data[i + 1]);
      uint16_t temp = encode_uint16(data[i], data[i + 1]);
    uint16_t f;
    memcpy(&f, &temp, sizeof(f));
    return (f * unit);
  };
  uint16_t seted_output_voltage = xy6020_get_16bit(XY6020_SETED_OUTPUT_VOLTAGE, NO_DEC_UNIT);         //0x00
  uint16_t seted_output_current = xy6020_get_16bit(XY6020_SETED_OUTPUT_CURRENT * 2, NO_DEC_UNIT);         //0x01
  uint16_t output_voltage = xy6020_get_16bit(XY6020_OUTPUT_VOLTAGE * 2, NO_DEC_UNIT);         //0x02
  uint16_t output_current = xy6020_get_16bit(XY6020_OUTPUT_CURRENT * 2, NO_DEC_UNIT);         //0x03
  uint16_t output_power = xy6020_get_16bit(XY6020_OUTPUT_POWER * 2, NO_DEC_UNIT);             //0x04
  uint16_t input_voltage = xy6020_get_16bit(XY6020_INPUT_VOLTAGE * 2, NO_DEC_UNIT);           //0x05
  uint16_t temperature_intern = xy6020_get_16bit(XY6020_TEMPERATURE_INTERN * 2, NO_DEC_UNIT); //0x0d
  uint16_t temperature_extern = xy6020_get_16bit(XY6020_TEMPERATURE_EXTERN * 2, NO_DEC_UNIT); //0x0e
  uint16_t model = xy6020_get_16bit(XY6020_MODEL * 2, NO_DEC_UNIT); //0x16
  uint16_t software_version = xy6020_get_16bit(XY6020_SOFTWARE_VERSION * 2, NO_DEC_UNIT); //0x17

  if (this->seted_output_voltage_sensor_ != nullptr)
    this->seted_output_voltage_sensor_->publish_state(seted_output_voltage);               //0x00
  if (this->seted_output_current_sensor_ != nullptr)
    this->seted_output_current_sensor_->publish_state(seted_output_current);               //0x01
  if (this->output_voltage_sensor_ != nullptr)
    this->output_voltage_sensor_->publish_state(output_voltage);               //0x02
  if (this->output_current_sensor_ != nullptr)
    this->output_current_sensor_->publish_state(output_current);               //0x03
  if (this->output_power_sensor_ != nullptr)
    this->output_power_sensor_->publish_state(output_power);                   //0x03
  if (this->input_voltage_sensor_ != nullptr)
    this->input_voltage_sensor_->publish_state(input_voltage);                 //0x05
  if (this->temperature_intern_sensor_ != nullptr)
    this->temperature_intern_sensor_->publish_state(temperature_intern);       //0x0d
  if (this->temperature_extern_sensor_ != nullptr)
    this->temperature_extern_sensor_->publish_state(temperature_extern);       //0x0e
  if (this->model_sensor_ != nullptr)
    this->model_sensor_->publish_state(model);                                 //0x16
  if (this->software_version_sensor_ != nullptr)
    this->software_version_sensor_->publish_state(software_version);           //0x17
}


void XY6020Sensor::update() {this->send(MODBUS_CMD_READ_IN_REGISTERS, 0, MODBUS_REGISTER_COUNT);}

void XY6020Sensor::dump_config() {
  ESP_LOGCONFIG(TAG, "XY6020:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  LOG_SENSOR("  ", "seted Output Voltage", this->seted_output_voltage_sensor_);
  LOG_SENSOR("  ", "seted Output Current", this->seted_output_current_sensor_);
  LOG_SENSOR("  ", "Output Voltage", this->output_voltage_sensor_);
  LOG_SENSOR("  ", "Output Current", this->output_current_sensor_);
  LOG_SENSOR("  ", "Output Power", this->output_current_sensor_);
  LOG_SENSOR("  ", "Input Voltage", this->input_voltage_sensor_);
  LOG_SENSOR("  ", "Temperature Intern", this->temperature_intern_sensor_);
  LOG_SENSOR("  ", "Temperature Extern", this->temperature_extern_sensor_);
  LOG_SENSOR("  ", "Model", this->model_sensor_);
  LOG_SENSOR("  ", "Software Version", this->software_version_sensor_);  
}

}  // namespace xy6020
}  // namespace esphome
