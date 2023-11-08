#pragma once

#include "../xy6020.h"
#include "esphome/core/component.h"
#include "esphome/components/number/number.h"

namespace esphome {
namespace xy6020 {

class xy6020;

class xy6020Number : public number::Number, public Component {
 public:
  void set_parent(xy6020 *parent) { this->parent_ = parent; };
  void set_holding_register(uint16_t holding_register) { this->holding_register_ = holding_register; };
  void dump_config() override;

 protected:
  void control(float value) override;

  xy6020 *parent_;
  uint16_t holding_register_;
};

}  // namespace xy6020
}  // namespace esphome
