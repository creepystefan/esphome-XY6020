#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/number/number.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/modbus/modbus.h"

namespace esphome {
namespace xy6020 {

enum CurrentResolution {
  xy6020_CURRENT_RESOLUTION_AUTO,
  xy6020_CURRENT_RESOLUTION_LOW,
  xy6020_CURRENT_RESOLUTION_HIGH,
};

class xy6020 : public PollingComponent, public modbus::ModbusDevice {
 public:
  void set_output_binary_sensor(binary_sensor::BinarySensor *output_binary_sensor) {
    output_binary_sensor_ = output_binary_sensor;
  }
  void set_key_lock_binary_sensor(binary_sensor::BinarySensor *key_lock_binary_sensor) {
    key_lock_binary_sensor_ = key_lock_binary_sensor;
  }
  void set_constant_current_mode_binary_sensor(binary_sensor::BinarySensor *constant_current_mode_binary_sensor) {
    constant_current_mode_binary_sensor_ = constant_current_mode_binary_sensor;
  }

  void set_voltage_setting_number(number::Number *voltage_setting_number) {
    voltage_setting_number_ = voltage_setting_number;
  }
  void set_current_setting_number(number::Number *current_setting_number) {
    current_setting_number_ = current_setting_number;
  }

  void set_output_voltage_sensor(sensor::Sensor *output_voltage_sensor) {
    output_voltage_sensor_ = output_voltage_sensor;
  }
  void set_output_current_sensor(sensor::Sensor *output_current_sensor) {
    output_current_sensor_ = output_current_sensor;
  }
  void set_output_power_sensor(sensor::Sensor *output_power_sensor) { output_power_sensor_ = output_power_sensor; }
  void set_input_voltage_sensor(sensor::Sensor *input_voltage_sensor) { input_voltage_sensor_ = input_voltage_sensor; }
  void set_voltage_setting_sensor(sensor::Sensor *voltage_setting_sensor) {
    voltage_setting_sensor_ = voltage_setting_sensor;
  }
  void set_current_setting_sensor(sensor::Sensor *current_setting_sensor) {
    current_setting_sensor_ = current_setting_sensor;
  }
  void set_backlight_brightness_sensor(sensor::Sensor *backlight_brightness_sensor) {
    backlight_brightness_sensor_ = backlight_brightness_sensor;
  }
  void set_firmware_version_sensor(sensor::Sensor *firmware_version_sensor) {
    firmware_version_sensor_ = firmware_version_sensor;
  }
  void set_intern_temp_sensor(sensor::Sensor *intern_temp_sensor) {
    intern_temp_sensor_ = intern_temp_sensor;
  }
  void set_runtimehours_sensor(sensor::Sensor *runtimehours_sensor) {
    runtimehours_sensor_ = runtimehours_sensor;
  }
  void set_runtimeminutes_sensor(sensor::Sensor *runtimeminutes_sensor) {
    runtimeminutes_sensor_ = runtimeminutes_sensor;
  }
  void set_run_power_hour_sensor(sensor::Sensor *run_power_hour_sensor) {
    run_power_hour_sensor_ = run_power_hour_sensor;
  }
  void set_run_current_hour_sensor(sensor::Sensor *run_current_hour_sensor) {
    run_current_hour_sensor_ = run_current_hour_sensor;
  }
  void set_M0_50_sensor(sensor::Sensor *M0_50_sensor) {
    M0_50_sensor_ = M0_50_sensor;
  }
    void set_M0_51_sensor(sensor::Sensor *M0_51_sensor) {
    M0_51_sensor_ = M0_51_sensor;
  }
  void set_M0_52_sensor(sensor::Sensor *M0_52_sensor) {
    M0_52_sensor_ = M0_52_sensor;
  }
  void set_M0_53_sensor(sensor::Sensor *M0_53_sensor) {
    M0_53_sensor_ = M0_53_sensor;
  }
  void set_M0_54_sensor(sensor::Sensor *M0_54_sensor) {
    M0_54_sensor_ = M0_54_sensor;
  }
  void set_M0_55_sensor(sensor::Sensor *M0_55_sensor) {
    M0_55_sensor_ = M0_55_sensor;
  }
  void set_M0_56_sensor(sensor::Sensor *M0_56_sensor) {
    M0_56_sensor_ = M0_56_sensor;
  }
  void set_M0_57_sensor(sensor::Sensor *M0_57_sensor) {
    M0_57_sensor_ = M0_57_sensor;
  }
void set_M0_58_sensor(sensor::Sensor *M0_58_sensor) {
    M0_58_sensor_ = M0_58_sensor;
  }
    void set_M0_59_sensor(sensor::Sensor *M0_59_sensor) {
    M0_59_sensor_ = M0_59_sensor;
  }
void set_M0_60_sensor(sensor::Sensor *M0_60_sensor) {
    M0_60_sensor_ = M0_60_sensor;
  }
    void set_M0_61_sensor(sensor::Sensor *M0_61_sensor) {
    M0_61_sensor_ = M0_61_sensor;
  }
  void set_M0_62_sensor(sensor::Sensor *M0_62_sensor) {
    M0_62_sensor_ = M0_62_sensor;
  }
  void set_M0_63_sensor(sensor::Sensor *M0_63_sensor) {
    M0_63_sensor_ = M0_63_sensor;
  }
  void set_M0_64_sensor(sensor::Sensor *M0_64_sensor) {
    M0_64_sensor_ = M0_64_sensor;
  }
  void set_M0_65_sensor(sensor::Sensor *M0_65_sensor) {
    M0_65_sensor_ = M0_65_sensor;
  }
  void set_M0_66_sensor(sensor::Sensor *M0_66_sensor) {
    M0_66_sensor_ = M0_66_sensor;
  }
  void set_M0_67_sensor(sensor::Sensor *M0_67_sensor) {
    M0_67_sensor_ = M0_67_sensor;
  }
void set_M0_68_sensor(sensor::Sensor *M0_68_sensor) {
    M0_68_sensor_ = M0_68_sensor;
  }
    void set_M0_69_sensor(sensor::Sensor *M0_69_sensor) {
    M0_69_sensor_ = M0_69_sensor;
  }
  

  void set_output_switch(switch_::Switch *output_switch) { output_switch_ = output_switch; }
  void set_key_lock_switch(switch_::Switch *key_lock_switch) { key_lock_switch_ = key_lock_switch; }

  void set_protection_status_text_sensor(text_sensor::TextSensor *protection_status_text_sensor) {
    protection_status_text_sensor_ = protection_status_text_sensor;
  }
  void set_device_model_text_sensor(text_sensor::TextSensor *device_model_text_sensor) {
    device_model_text_sensor_ = device_model_text_sensor;
  }
  void set_current_resolution(CurrentResolution current_resolution) { current_resolution_ = current_resolution; }
  void set_current_resolution_if_auto(CurrentResolution current_resolution) {
    if (this->current_resolution_ == xy6020_CURRENT_RESOLUTION_AUTO) {
      this->set_current_resolution(current_resolution);
    }
  }
  float current_resolution_factor() {
    return (this->current_resolution_ == xy6020_CURRENT_RESOLUTION_HIGH) ? 0.001f : 0.01f;
  }

  void dump_config() override;

  void on_modbus_data(const std::vector<uint8_t> &data) override;

  void update() override;

  void write_register(uint16_t address, uint16_t value);

 protected:
  CurrentResolution current_resolution_{xy6020_CURRENT_RESOLUTION_AUTO};

  binary_sensor::BinarySensor *output_binary_sensor_;
  binary_sensor::BinarySensor *key_lock_binary_sensor_;
  binary_sensor::BinarySensor *constant_current_mode_binary_sensor_;

  number::Number *voltage_setting_number_;
  number::Number *current_setting_number_;

  sensor::Sensor *output_voltage_sensor_;
  sensor::Sensor *output_current_sensor_;
  sensor::Sensor *output_power_sensor_;
  sensor::Sensor *input_voltage_sensor_;
  sensor::Sensor *voltage_setting_sensor_;
  sensor::Sensor *current_setting_sensor_;
  sensor::Sensor *backlight_brightness_sensor_;
  sensor::Sensor *firmware_version_sensor_;
  sensor::Sensor *intern_temp_sensor_;
  sensor::Sensor *runtimehours_sensor_;
  sensor::Sensor *runtimeminutes_sensor_;
  sensor::Sensor *run_power_hour_sensor_;
  sensor::Sensor *run_current_hour_sensor_;
  sensor::Sensor *M0_50_sensor_;
  sensor::Sensor *M0_51_sensor_;
  sensor::Sensor *M0_52_sensor_;
  sensor::Sensor *M0_53_sensor_;
  sensor::Sensor *M0_54_sensor_;
  sensor::Sensor *M0_55_sensor_;
  sensor::Sensor *M0_56_sensor_;
  sensor::Sensor *M0_57_sensor_;
  sensor::Sensor *M0_58_sensor_;
  sensor::Sensor *M0_59_sensor_;
  sensor::Sensor *M0_60_sensor_;
  sensor::Sensor *M0_61_sensor_;
  sensor::Sensor *M0_62_sensor_;
  sensor::Sensor *M0_63_sensor_;
  sensor::Sensor *M0_64_sensor_;
  sensor::Sensor *M0_65_sensor_;
  sensor::Sensor *M0_66_sensor_;
  sensor::Sensor *M0_67_sensor_;
  sensor::Sensor *M0_68_sensor_;
  sensor::Sensor *M0_69_sensor_;
 

  switch_::Switch *output_switch_;
  switch_::Switch *key_lock_switch_;

  text_sensor::TextSensor *protection_status_text_sensor_;
  text_sensor::TextSensor *device_model_text_sensor_;

  void on_status_data_(const std::vector<uint8_t> &data);
  void on_acknowledge_data_(const std::vector<uint8_t> &data);
  void publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state);
  void publish_state_(number::Number *number, float value);
  void publish_state_(sensor::Sensor *sensor, float value);
  void publish_state_(switch_::Switch *obj, const bool &state);
  void publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state);
};

}  // namespace xy6020
}  // namespace esphome
