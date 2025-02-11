#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/modbus/modbus.h"
#include <vector>

namespace esphome {
namespace xy6020_switch {

#define XY6020_SWITCH(name) 
 protected: 
  switch::Switch *name##_switch_{nullptr}; 

public: 
  void set_##name##_switch(switch::Switch *(name)) { this->name##_switch_ = name; }

class XY6020_Switch : public PollingComponent, public modbus::ModbusDevice {
 public:
  XY6020_SENSOR(turn_on_off)
    
    void setup() override {
    // This will be called by App.setup()
    pinMode(5, INPUT);
  }
  void write_state(bool state) override {
    // This will be called every time the user requests a state change.

    digitalWrite(5, state);

    // Acknowledge new state by publishing it
    publish_state(state);
  }
};

}  // namespace xy6020_switch
}  // namespace esphome
