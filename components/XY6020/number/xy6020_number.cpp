#include "xy6020_number.h"
#include "esphome/core/log.h"

namespace esphome {
namespace xy6020 {

static const char *const TAG = "xy6020.number";

void xy6020Number::dump_config() { LOG_NUMBER("", "xy6020 Number", this); }
void xy6020Number::control(float value) {
  float resolution = 100.0f;

  if (this->holding_register_ == 0x0001) {
    resolution = 1.0f / this->parent_->current_resolution_factor();
  }

  this->parent_->write_register(this->holding_register_, (uint16_t) (value * resolution));
}

}  // namespace xy6020
}  // namespace esphome
