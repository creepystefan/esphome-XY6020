#include "xy6020.h"
#include "xy6020register.h"
#include "esphome/core/log.h"

// ORIGInAL from selec_meter

namespace esphome {
namespace xy6020 {

static const char *const TAG = "xy6020";

static const uint8_t MODBUS_CMD_READ_IN_REGISTERS = 0x04;
static const uint8_t MODBUS_REGISTER_COUNT = 20;  // 20 x 16-bit registers
//static const uint8_t MODBUS_REGISTER_COUNT50 = 50;  // 20 x 16-bit registers


void XY6020::on_modbus_data(const std::vector<uint8_t> &data) {
  if (data.size() < MODBUS_REGISTER_COUNT * 2) {
    ESP_LOGW(TAG, "Invalid size for XY6020!");
    return;
  }
  auto xy6020_get_float = [&](size_t i, float unit) -> float {  
    uint32_t temp = encode_uint32(data[i + 2], data[i + 3], data[i], data[i + 1]);
    float f;
    memcpy(&f, &temp, sizeof(f));
    return (f * unit);
  };

  float output_voltage = xy6020_get_float(XY6020_OUTPUT_VOLTAGE * 2, NO_DEC_UNIT);         //0x02
  float output_current = xy6020_get_float(XY6020_OUTPUT_CURRENT * 2, NO_DEC_UNIT);         //0x03
  float output_power = xy6020_get_float(XY6020_OUTPUT_POWER * 2, NO_DEC_UNIT);             //0x04
  float input_voltage = xy6020_get_float(XY6020_INPUT_VOLTAGE * 2, NO_DEC_UNIT);           //0x05
  float temperature_intern = xy6020_get_float(XY6020_TEMPERATURE_INTERN * 2, NO_DEC_UNIT); //0x0d
  float temperature_extern = xy6020_get_float(XY6020_TEMPERATURE_EXTERN * 2, NO_DEC_UNIT); //0x0e
  
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
}


void XY6020::update() {this->send(MODBUS_CMD_READ_IN_REGISTERS, 0, MODBUS_REGISTER_COUNT);}
void XY6020::update50() {this->send(MODBUS_CMD_READ_IN_REGISTERS, 50, MODBUS_REGISTER_COUNT);}
void XY6020::dump_config() {
  //ESP_LOGCONFIG(TAG, "SELEC Meter:");
  ESP_LOGCONFIG(TAG, "XY6020:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  LOG_SENSOR("  ", "Output Voltage", this->output_voltage_sensor_);
  LOG_SENSOR("  ", "Output Current", this->output_current_sensor_);
  LOG_SENSOR("  ", "Output Power", this->output_current_sensor_);
  LOG_SENSOR("  ", "Input Voltage", this->input_voltage_sensor_);
  LOG_SENSOR("  ", "Temperature Intern", this->temperature_intern_sensor_);
  LOG_SENSOR("  ", "Temperature Extern", this->temperature_extern_sensor_);
}

}  // namespace xy6020
}  // namespace esphome
