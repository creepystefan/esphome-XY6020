import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch, modbus
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_SWITCH,
    CONF_ADDRESS,
)

AUTO_LOAD = ["modbus"]
CODEOWNERS = ["@creepystefan"]

CONF_TURN_ON_OFF = "turn_on_off"
CONF_KEY_PROTECT = "key_protect"


xy6020_ns = cg.esphome_ns.namespace("xy6020")
XY6020Switch = xy6020_ns.class_(
    "XY6020Switch", cg.PollingComponent, modbus.ModbusDevice
)

SWITCHES = {
    CONF_TURN_ON_OFF: switch.switch_schema(
        device_class=DEVICE_CLASS_SWITCH,
    ), 
    CONF_KEY_PROTECT: switch.switch_schema(
        device_class=DEVICE_CLASS_SWITCH,
    ), 

}

CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(XY6020Switch)})
    .extend(
        {cv.Optional(switch_name): schema for switch_name, schema in SWITCHES.items()}
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(modbus.modbus_device_schema(0x01))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await modbus.register_modbus_device(var, config)
    await switch.register_switch(var, config)
    for name in SWITCHES:
        if name in config:
            hub = await switch.new_switch(config[name])
            cg.add(getattr(var, f"set_{name}_switch")(hub))


#     await switch.register_switch(var, conf)
#            cg.add(getattr(hub, f"set_{key}_switch")(var))
#            cg.add(var.set_parent(hub))
#            cg.add(var.set_holding_register(address))
