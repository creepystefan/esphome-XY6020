#include "selec_meter.h"
#include "selec_meter_registers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace xy_6020 {

//static const char *const TAG = "selec_meter";
static const char *const TAG = "xy_6020";

static const uint8_t MODBUS_CMD_READ_IN_REGISTERS = 0x04;
static const uint8_t MODBUS_REGISTER_COUNT = 20;  // 20 x 16-bit registers

//void SelecMeter::on_modbus_data(const std::vector<uint8_t> &data) {
void XY6020::on_modbus_data(const std::vector<uint8_t> &data) {
  if (data.size() < MODBUS_REGISTER_COUNT * 2) {
    ESP_LOGW(TAG, "Invalid size for XY6020!");
    return;
  }

  //auto selec_meter_get_float = [&](size_t i, float unit) -> float {
  auto xy_6020_get_float = [&](size_t i, float unit) -> float {  
    uint32_t temp = encode_uint32(data[i + 2], data[i + 3], data[i], data[i + 1]);

    float f;
    memcpy(&f, &temp, sizeof(f));
    return (f * unit);
  };
  //
  float input_voltage_energy = xy_6020_get_float(SELEC_TOTAL_ACTIVE_ENERGY * 2, NO_DEC_UNIT);
  float output_voltage_energy = xy_6020_get_float(SELEC_TOTAL_ACTIVE_ENERGY * 2, NO_DEC_UNIT);
  float temperature_intern = xy_6020_get_float(SELEC_TOTAL_ACTIVE_ENERGY * 2, NO_DEC_UNIT);
  

  if (this->input_voltage_sensor_ != nullptr)
    this->input_voltage_sensor_->publish_state(input_voltage);
  if (this->output_voltage_sensor_ != nullptr)
    this->output_voltage_sensor_->publish_state(output_voltage);
  if (this->temperature_intern_sensor_ != nullptr)
    this->temperature_intern_sensor_->publish_state(temperature_intern);
 
}

//void SelecMeter::update() { this->send(MODBUS_CMD_READ_IN_REGISTERS, 0, MODBUS_REGISTER_COUNT); }
//void SelecMeter::dump_config() {
void XY6020::update() { this->send(MODBUS_CMD_READ_IN_REGISTERS, 0, MODBUS_REGISTER_COUNT); }
void XY6020::dump_config() {
  //ESP_LOGCONFIG(TAG, "SELEC Meter:");
  ESP_LOGCONFIG(TAG, "XY6020:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  LOG_SENSOR("  ", "Input Voltage", this->input_voltage_sensor_);
  LOG_SENSOR("  ", "Output Voltage", this->output_voltage_sensor_);
  LOG_SENSOR("  ", "Temperature Intern", this->temperature_intern_sensor_);
}

}  // namespace selec_meter
}  // namespace esphome
