#pragma once

#include "../xy6020.h"
#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace xy6020 {

class xy6020;

class xy6020Switch : public switch_::Switch, public Component {
 public:
  void set_parent(xy6020 *parent) { this->parent_ = parent; };
  void set_holding_register(uint16_t holding_register) { this->holding_register_ = holding_register; };
  void dump_config() override;
  void loop() override {}
  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  void write_state(bool state) override;
  xy6020 *parent_;
  uint16_t holding_register_;
};

}  // namespace xy6020
}  // namespace esphome
