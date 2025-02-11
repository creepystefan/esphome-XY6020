#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/modbus/modbus.h"

#include <vector>

namespace esphome {
namespace xy6020 {

#define XY6020_SENSOR(name) \
 protected: \
  sensor::Sensor *name##_sensor_{nullptr}; \
\
 public: \
  void set_##name##_sensor(sensor::Sensor *(name)) { this->name##_sensor_ = name; }
  
class XY6020 : public PollingComponent, public modbus::ModbusDevice {
 public:
  XY6020_SENSOR(seted_output_voltage)
  XY6020_SENSOR(seted_output_current)
  XY6020_SENSOR(output_voltage)
  XY6020_SENSOR(output_current)
  XY6020_SENSOR(output_power)
  XY6020_SENSOR(input_voltage)
  XY6020_SENSOR(temperature_intern)
  XY6020_SENSOR(temperature_extern)
  XY6020_SENSOR(model)
  XY6020_SENSOR(software_version)
  
  void update() override;
 

  void on_modbus_data(const std::vector<uint8_t> &data) override;

  void dump_config() override;
};

}  // namespace xy6020
}  // namespace esphome
