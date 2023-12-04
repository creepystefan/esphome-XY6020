#include "xy6020.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace xy6020 {

static const char *const TAG = "xy6020";

static const uint8_t FUNCTION_READ_REGISTERS = 0x03;
static const uint8_t FUNCTION_WRITE_SINGLE_REGISTER = 0x06;
static const uint8_t FUNCTION_WRITE_MULTIPLE_REGISTERS = 0x10;

static const uint8_t PROTECTION_STATUS_SIZE = 4;
static const char *const PROTECTION_STATUS[PROTECTION_STATUS_SIZE] = {
    "Normal",        // 0x00
    "Over-Voltage",  // 0x01
    "Over-Current",  // 0x02
    "Over-Power",    // 0x03
};

void xy6020::on_modbus_data(const std::vector<uint8_t> &data) {
  if (data.size() == 52) {
    this->on_status_data_(data);
    return;
  }

  if (data.size() == 4) {
    this->on_acknowledge_data_(data);
    return;
  }

  ESP_LOGW(TAG, "Invalid size (%zu) for xy6020 frame!", data.size());
  ESP_LOGW(TAG, "Payload: %s", format_hex_pretty(&data.front(), data.size()).c_str());
}

void xy6020::on_acknowledge_data_(const std::vector<uint8_t> &data) {
  auto xy6020_get_16bit = [&](size_t i) -> uint16_t {
    return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  };

  // Write register acknowledge
  //
  // -> 0x01 0x10 0x00 0x01 0x00 0x01 0x02 0x02 0xF7 0xE7 0x67
  // <- 0x01 0x10 0x00 0x01 0x00 0x01 .... ....

  uint16_t starting_address = xy6020_get_16bit(0);
  uint16_t registers_written = xy6020_get_16bit(2);

  if (registers_written == 0) {
    ESP_LOGW(TAG, "Updating register 0x%02X failed", starting_address);
    return;
  }

  ESP_LOGD(TAG, "Acknowledge received: %zu registers written at address 0x%02X", registers_written, starting_address);
}

void xy6020::on_status_data_(const std::vector<uint8_t> &data) {
  auto xy6020_get_16bit = [&](size_t i) -> uint16_t {
    return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  };

  ESP_LOGI(TAG, "Status frame received");

  // Set device model & current resolution based on reported model
  uint16_t model_number = xy6020_get_16bit(44);
  switch (model_number) {
    case 5015:
    case 5020:
      this->set_current_resolution_if_auto(xy6020_CURRENT_RESOLUTION_LOW);
      this->publish_state_(this->device_model_text_sensor_, "xy6020" + to_string(model_number));
      break;
    case 5205:
      this->set_current_resolution_if_auto(xy6020_CURRENT_RESOLUTION_HIGH);
      this->publish_state_(this->device_model_text_sensor_, "DPH" + to_string(model_number - 200));
      break;
    case 3005:
    case 5005:
    case 8005:
    default:
      this->set_current_resolution_if_auto(xy6020_CURRENT_RESOLUTION_HIGH);
      this->publish_state_(this->device_model_text_sensor_, "xy6020" + to_string(model_number));
      break;
  }
        //# DPS
  // Status request (read register 0...13)
  // -> 0x01 0x03 0x00 0x00 0x00 0x0D 0x84 0x0F
  //
  // Status response
  // <- 0x01 0x03 0x1A 0x0E 0x10 0x03 0xE8 0x0E 0x0E 0x00 0xED 0x21 0x4F 0x10 0x87 0x00
  //    0x00 0x00 0x00 0x00 0x00 0x00 0x01 0x00 0x00 0x13 0x9C 0x00 0x11 0x87 0xBD
  //
  // Data: 0x0E 0x10 0x03 0xE8 0x0E 0x0E 0x00 0xED 0x21 0x4F 0x10 0x87 0x00
  //       0x00 0x00 0x00 0x00 0x00 0x00 0x01 0x00 0x00 0x13 0x9C 0x00 0x11
  //
  // *Data*

       // xy6020
    // Status request (read register 0...29)
    // -> 01:03:00:00:00:1D:85:C3
    // Status response
    //       01:03:3A:09:CA:00:63:09:CA:00:0B:00:1B:12:DA:00:01:00:00:00:04:00:00:00:00:00:00:00:06:01:43:22:B8:00:00:00:00:00:00:00:01:00:00:00:03:00:00:61:00:00:73:00:01:00:06:00:00:00:00:00:00:6E:F6
    //Data: 
    //   Power On / OFF    Block 36 
    //  on  09:CA:00:63:09:CA:00:0B:00:1B:12:DA:00:01:00:00:00:04:00:00:00:00:00:00:00:06:01:43:22:B8:00:00:00:00:00:00: (00:01) :00:00:00:03:00:00:61:00:00:73:00:01:00:06:00:00:00:00:00:00:6E:F6
    //  off 09:CA:00:63:01:F2:00:00:00:00:12:CF:00:00:00:00:00:00:00:00:00:00:00:00:00:00:01:53:22:B8:00:00:00:00:00:00: (00:00) :00:00:00:03:00:00:61:00:00:73:00:01:00:06:00:00:00:00:00:00:81:F7
    //  off 09:CA:00:63:01:F2:00:00:00:00:12:D0:00:00:00:00:00:00:00:00:00:00:00:00:00:00:01:35:22:B8:00:00:00:00:00:00: (00:00) :00:00:00:03:00:00:61:00:00:73:00:01:00:06:00:00:00:00:00:00:4B:E2
    //  on  09:CA:00:63:09:CA:00:0B:00:1B:12:DA:00:01:00:00:00:0B:00:00:00:00:00:00:00:0E:01:39:22:B8:00:00:00:00:00:00: (00:01) :00:00:00:03:00:00:61:00:00:73:00:01:00:06:00:00:00:00:00:00:8A:D4

    //  KEY Lock   lock / unluck   Block 30  
    //  unlock 09:CA:00:63:09:CA:00:0B:00:1B:12:D9:00:04:00:00:00:5B:00:00:00:00:00:01:00:3B:01:54:22:B8: (00:00) :00:00:00:00:00:01:00:00:00:03:00:00:61:00:00:73:00:01:00:06:00:00:00:00:00:00:C8:59
    //  lock   09:CA:00:63:09:CA:00:0C:00:1E:12:DC:00:0A:00:00:00:ED:00:00:00:00:00:05:00:08:01:56:22:B8: (00:01) :00:00:00:00:00:01:00:00:00:03:00:00:61:00:00:73:00:01:00:06:00:00:00:00:00:00:14:6E
    //  unlock 09:CA:00:63:09:CA:00:0C:00:1E:12:DA:00:0D:00:00:01:42:00:00:00:00:00:06:00:39:01:57:22:B8: (00:00) :00:00:00:00:00:01:00:00:00:03:00:00:61:00:00:73:00:01:00:06:00:00:00:00:00:00:E4:47
    //  lock   09:CA:00:63:09:CA:00:0B:00:1B:12:DC:00:10:00:00:01:8E:00:00:00:00:00:08:00:24:01:57:22:B8: (00:01) :00:00:00:00:00:01:00:00:00:03:00:00:61:00:00:73:00:01:00:06:00:00:00:00:00:00:95:10

    // running time hours    (hours Block 20)   (minutes Block 22)
    // hours   09:CA:00:63:09:CA:00:0C:00:1E:12:DA:0C:52:00:00:33:C7:00:01: (00:1A) :  00:07  :  00:11  :01:5C:22:B8:00:01:00:00:00:00:00:01:00:00:00:03:00:00:61:00:00:73:00:01:00:06:43:4A
    // minutes 09:CA:00:63:09:CA:00:0C:00:1E:12:DA:0C:52:00:00:33:C7:00:01:  00:1A  : (00:07) :  00:11  :01:5C:22:B8:00:01:00:00:00:00:00:01:00:00:00:03:00:00:61:00:00:73:00:01:00:06:43:4A
    // seconds 09:CA:00:63:09:CA:00:0C:00:1E:12:DA:0C:52:00:00:33:C7:00:01:  00:1A  :  00:07  : (00:11) :01:5C:22:B8:00:01:00:00:00:00:00:01:00:00:00:03:00:00:61:00:00:73:00:01:00:06:43:4A
   
    // verbrauchte Gesamtleistung in W Block 16
    // verbrauchte Leistung  09:CA:00:63:09:CA:00:0C:00:1E:12:DA:0C:52:00:00: (33:C7) :00:01:00:1A:00:07 :00:11:01:5C:22:B8:00:01:00:00:00:00:00:01:00:00:00:03:00:00:61:00:00:73:00:01:00:06:43:4A

    // verbrauchte Gesamtleistung in Ah Block 12
    // verbrauchte Leistung  09:CA:00:63:09:CA:00:0C:00:1E:12:DA: (0C:52) :00:00:33:C7:00:01:00:1A:00:07 :00:11:01:5C:22:B8:00:01:00:00:00:00:00:01:00:00:00:03:00:00:61:00:00:73:00:01:00:06:43:4A
    
    
    
  // Byte   Address Content: Description                      Decoded content               Coeff./Unit
  //   0    0x0E 0x10        Voltage setting                  3600 * 0.01 = 36.00V          0.01 V
  float voltage_setting = xy6020_get_16bit(0) * 0.01f;
  this->publish_state_(this->voltage_setting_sensor_, voltage_setting);
  this->publish_state_(this->voltage_setting_number_, voltage_setting);
  //   2    0x03 0xE8        Current setting                  1000 * 0.01 = 10.00A          0.01 A
  // float current_setting = xy6020_get_16bit(2) * this->current_resolution_factor();
  float current_setting = xy6020_get_16bit(2) * this->current_resolution_factor();
  this->publish_state_(this->current_setting_sensor_, current_setting);
  this->publish_state_(this->current_setting_number_, current_setting);
  //   4    0x0E 0x0E        Output voltage display value     3598 * 0.01 = 35.98V          0.01 V
  this->publish_state_(this->output_voltage_sensor_, (float) xy6020_get_16bit(4) * 0.01f);
  //   6    0x00 0xED        Output current display value     0237 * 0.01 = 2.37A           0.01 A
 // this->publish_state_(this->output_current_sensor_, (float) xy6020_get_16bit(6) * this->current_resolution_factor());
    this->publish_state_(this->output_current_sensor_, (float) xy6020_get_16bit(6) * 0.01f);
  //   8    0x21 0x4F        Output power display value       8527 * 0.01 = 85.27W          0.01 W
  this->publish_state_(this->output_power_sensor_, (float) xy6020_get_16bit(8) * 0.1f);
  //  10    0x10 0x87        Input voltage display value      4231 * 0.01 = 42.31V          0.01 V
  this->publish_state_(this->input_voltage_sensor_, (float) xy6020_get_16bit(10) * 0.01f); 
// DPS  12    0x00 0x00        Key lock                         0x00: off, 0x01: on
// XY6020  30    0x00 0x00        Key lock                         0x00: off, 0x01: on
    bool key_lock = xy6020_get_16bit(30) == 0x0001;
  this->publish_state_(this->key_lock_binary_sensor_, key_lock);
  this->publish_state_(this->key_lock_switch_, key_lock);
  //  14    0x00 0x00        Protection status                0x00: normal, 0x01: over-voltage,
  //  26                     internal Temperatur 
  this->publish_state_(this->intern_temp_sensor_, (float) xy6020_get_16bit(26) * 0.1f);  
 //   20     running Time  hours
  this->publish_state_(this->runtimehours_sensor_, (float) xy6020_get_16bit(20) * 1.f);    
 //   22     running Time  Minutes        
  this->publish_state_(this->runtimeminutes_sensor_, (float) xy6020_get_16bit(22) * 1.f);
 //   24     running Time  Seconds        
  this->publish_state_(this->runtimeseconds_sensor_, (float) xy6020_get_16bit(24) * 1.f);
 //   16     verbrauchte Leistung       
  this->publish_state_(this->run_power_hour_sensor_, (float) xy6020_get_16bit(16) * 1.f);
 //   12     verbrauchte Leistung       
  this->publish_state_(this->run_current_hour_sensor_, (float) xy6020_get_16bit(12) * 1.f);


    
//   LOAD Set Register M0-M9   0x35
    
//       Store M0
    
    //                    0x50     M0 Voltage Set
  this->publish_state_(this->M0_50_sensor_, (float) xy6020_get_16bit(18) * 1.f);    
    //                0x51     M0 Current Set
  this->publish_state_(this->M0_51_sensor_, (float) xy6020_get_16bit(24) * 1.f);
    //                0x52    OVP Over Voltage Protect
  this->publish_state_(this->M0_52_sensor_, (float) xy6020_get_16bit(28) * 0.1f);
    //                0x53    OCP Over Current Protect
  this->publish_state_(this->M0_53_sensor_, (float) xy6020_get_16bit(32) * 0.1f);
    //                0x54    OPP
  this->publish_state_(this->M0_54_sensor_, (float) xy6020_get_16bit(34) * 0.01f);
    //                0x55    b_led2_set_max
  this->publish_state_(this->M0_55_sensor_, (float) xy6020_get_16bit(36) * 0.01f);
    //                0x56    m_pre_set_max, self.limits.m_pre_set_min
  this->publish_state_(this->M0_56_sensor_, (float) xy6020_get_16bit(38) * 0.01f);
    //                0x57    s_ini_set_max, self.limits.s_ini_set_min
  this->publish_state_(this->M0_57_sensor_, (float) xy6020_get_16bit(40) * 0.01f);
    //                0x58
  this->publish_state_(this->M0_58_sensor_, (float) xy6020_get_16bit(42) * 0.01f);
//                    0x59
  this->publish_state_(this->M0_59_sensor_, (float) xy6020_get_16bit(44) * 0.01f);


   
    //           Store M1
    //                    0x60     M1 Voltage Set
  this->publish_state_(this->M0_60_sensor_, (float) xy6020_get_16bit(0x60) * 0.01f);    
    //                0x61     M1 Current Set
  this->publish_state_(this->M0_61_sensor_, (float) xy6020_get_16bit(0x61) * 0.01f);
    //                0x62    OVP Over Voltage Protect
  this->publish_state_(this->M0_62_sensor_, (float) xy6020_get_16bit(0x62) * 0.01f);
    //                0x63    OCP Over Current Protect
  this->publish_state_(this->M0_63_sensor_, (float) xy6020_get_16bit(0x63) * 0.01f);
    //                0x64    OPP
  this->publish_state_(this->M0_64_sensor_, (float) xy6020_get_16bit(0x64) * 0.01f);
    //                0x65    ??  b_led2_set_max
  this->publish_state_(this->M0_65_sensor_, (float) xy6020_get_16bit(0x65) * 0.01f);
    //                0x66    ??  m_pre_set_max, self.limits.m_pre_set_min
  this->publish_state_(this->M0_66_sensor_, (float) xy6020_get_16bit(0x66) * 0.01f);
    //                0x67    ??
  this->publish_state_(this->M0_67_sensor_, (float) xy6020_get_16bit(0x67) * 0.01f);
    //                0x68    ??
  this->publish_state_(this->M0_68_sensor_, (float) xy6020_get_16bit(0x68) * 0.01f);
//                    0x69    ??
  this->publish_state_(this->M0_69_sensor_, (float) xy6020_get_16bit(0x69) * 0.01f);

    //                    0x50     M2 Voltage Set
 // this->publish_state_(this->51_sensor_, (float) xy6020_get_16bit(0x51) * 0.01f);    
    //                0x51     M1 Current Set
 // this->publish_state_(this->51_sensor_, (float) xy6020_get_16bit(0x51) * 0.01f);
    //                0x52    OVP Over Voltage Protect
 // this->publish_state_(this->52_sensor_, (float) xy6020_get_16bit(0x52) * 0.01f);
    //                0x53    OCP Over Current Protect
 // this->publish_state_(this->53_sensor_, (float) xy6020_get_16bit(0x53) * 0.01f);
    //                0x54    OPP
 // this->publish_state_(this->54_sensor_, (float) xy6020_get_16bit(0x54) * 0.01f);
    //                0x55    b_led2_set_max
 // this->publish_state_(this->55_sensor_, (float) xy6020_get_16bit(0x55) * 0.01f);
    //                0x56    m_pre_set_max, self.limits.m_pre_set_min
 // this->publish_state_(this->56_sensor_, (float) xy6020_get_16bit(0x56) * 0.01f);
    //                0x57    s_ini_set_max, self.limits.s_ini_set_min
 // this->publish_state_(this->57_sensor_, (float) xy6020_get_16bit(0x57) * 0.01f);
    //                0x58
 // this->publish_state_(this->58_sensor_, (float) xy6020_get_16bit(0x58) * 0.01f);
//                    0x59
//  this->publish_state_(this->59_sensor_, (float) xy6020_get_16bit(0x59) * 0.01f);

    
    
  //                                                          0x02: over-current, 0x03: over-power
  uint16_t raw_protection_status = data[14];
  if (raw_protection_status < PROTECTION_STATUS_SIZE) {
    this->publish_state_(this->protection_status_text_sensor_, PROTECTION_STATUS[raw_protection_status]);
  } else {
    this->publish_state_(this->protection_status_text_sensor_, "Unknown");
  }
  //  16    0x00 0x00        Constant current (CC mode)       0x00: CV mode, 0x01: CC mode
  this->publish_state_(this->constant_current_mode_binary_sensor_, xy6020_get_16bit(16) == 0x0001);
  //  18    0x00 0x01        Switch output state              0x00: off, 0x01: on
  bool output = xy6020_get_16bit(36) == 0x0001;
  this->publish_state_(this->output_binary_sensor_, output);
  this->publish_state_(this->output_switch_, output);
  //  20    0x00 0x00        Backlight brightness level       0...5
  this->publish_state_(this->backlight_brightness_sensor_, xy6020_get_16bit(20) * 20.0f);
  //  Model xy6020
  //                        Product model                      6020 = xy6020
  //  46     0073           Firmware version                   115 = 11.5
    this->publish_state_(this->firmware_version_sensor_, xy6020_get_16bit(46) * 0.1f);
}    

void xy6020::update() {
  // Status request: 0x01 0x03 0x00 0x00 0x00 0x0D 0x84 0x0F
  this->send(FUNCTION_READ_REGISTERS, 0x0000, 0x001A);
}

void xy6020::write_register(uint16_t address, uint16_t value) {
  // Output on:    0x01 0x10 0x00 0x09 0x00 0x01 0x02 0x00 0x01 0x67 0x09
  // Output off:   0x01 0x10 0x00 0x09 0x00 0x01 0x02 0x00 0x00 0xa6 0xc9
  // Key lock on:  0x01 0x10 0x00 0x06 0x00 0x01 0x02 0x00 0x01 0x67 0xf6
  // Key lock off: 0x01 0x10 0x00 0x06 0x00 0x01 0x02 0x00 0x00 0xa6 0x36

  // Set voltage to 10V: 0x01 0x10 0x00 0x00 0x00 0x01 0x02 0x03 0xe8 0xa6 0xee
  // Set voltage to 20V: 0x01 0x10 0x00 0x00 0x00 0x01 0x02 0x07 0xd0 0xa5 0xfc
  uint8_t payload[2];
  payload[0] = value >> 8;
  payload[1] = value & 0xff;

  // 0x01 0x10 0x00 0x01 0x00 0x01 0x02 0x00 0x3F 0xE7 0x91
  // |    |    |         |         |    |         |
  // |    |    |         |         |    |         checksum
  // |    |    |         |         |    payload
  // |    |    |         |         data_len_bytes
  // |    |    |         num_of_entities
  // |    |    address
  // |    function
  // addr
  this->send(FUNCTION_WRITE_MULTIPLE_REGISTERS, address, 0x0001, sizeof(payload), payload);
}

void xy6020::publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state) {
  if (binary_sensor == nullptr)
    return;

  binary_sensor->publish_state(state);
}

void xy6020::publish_state_(number::Number *number, float value) {
  if (number == nullptr)
    return;

  number->publish_state(value);
}

void xy6020::publish_state_(sensor::Sensor *sensor, float value) {
  if (sensor == nullptr)
    return;

  sensor->publish_state(value);
}

void xy6020::publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state) {
  if (text_sensor == nullptr)
    return;

  text_sensor->publish_state(state);
}

void xy6020::publish_state_(switch_::Switch *obj, const bool &state) {
  if (obj == nullptr)
    return;

  obj->publish_state(state);
}

void xy6020::dump_config() {  // NOLINT(google-readability-function-size,readability-function-size)
  ESP_LOGCONFIG(TAG, "xy6020:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  LOG_BINARY_SENSOR("", "Output", this->output_binary_sensor_);
  LOG_BINARY_SENSOR("", "Key Lock", this->key_lock_binary_sensor_);
  LOG_BINARY_SENSOR("", "Constant Current Mode", this->constant_current_mode_binary_sensor_);
  LOG_SENSOR("", "Output Voltage", this->output_voltage_sensor_);
  LOG_SENSOR("", "Output Current", this->output_current_sensor_);
  LOG_SENSOR("", "Output Power", this->output_power_sensor_);
  LOG_SENSOR("", "Input Voltage", this->input_voltage_sensor_);
  LOG_SENSOR("", "Voltage Setting", this->voltage_setting_sensor_);
  LOG_SENSOR("", "Current Setting", this->current_setting_sensor_);
  LOG_SENSOR("", "Backlight Brightness", this->backlight_brightness_sensor_);
  LOG_SENSOR("", "Firmware Version", this->firmware_version_sensor_);
  LOG_SENSOR("", "Internal Temperatur", this->intern_temp_sensor_);
  LOG_TEXT_SENSOR("", "Protection Status", this->protection_status_text_sensor_);
  LOG_TEXT_SENSOR("", "Device Model", this->device_model_text_sensor_);

}

}  // namespace xy6020
}  // namespace esphome
