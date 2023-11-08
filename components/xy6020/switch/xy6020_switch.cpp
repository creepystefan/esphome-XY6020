#include "xy6020_switch.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace xy6020 {

static const char *const TAG = "xy6020.switch";

void Xy6020Switch::dump_config() { LOG_SWITCH("", "xy6020 Switch", this); }
void Xy6020Switch::write_state(bool state) { this->parent_->write_register(this->holding_register_, (uint16_t) state); }

}  // namespace xy6020
}  // namespace esphome
