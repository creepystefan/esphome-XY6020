import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch, modbus
from esphome.const import (
    CONF_ID,
    CONF_ADDRESS,
)

AUTO_LOAD = ["modbus"]
CODEOWNERS = ["@creepystefan"]

CONF_TURN_ON_OFF = "turn_on_off"
CONF_KEY_PROTECT = "key_protect"


xy6020_ns = cg.esphome_ns.namespace("xy6020")
XY6020 = xy6020_ns.class_(
    "XY6020", cg.PollingComponent, modbus.ModbusDevice
)

SWITCHES = {
    CONF_TURN_ON_OFF: switch.swtich_schema(
 #       unit_of_measurement=UNIT_VOLT,
 #       accuracy_decimals=2,
 #       device_class=DEVICE_CLASS_VOLTAGE,
 #       state_class=STATE_CLASS_MEASUREMENT,
    ), 
    CONF_KEY_PROTECT: sensor.sensor_schema(
 #       unit_of_measurement=UNIT_AMPERE,
 #       accuracy_decimals=2,
 #       device_class=DEVICE_CLASS_CURRENT,
 #       state_class=STATE_CLASS_MEASUREMENT,
    ), 

}

CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(XY6020)})
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
    for name in SWITCHES:
        if name in config:
            swit = await switch.new_switch(config[name])
            cg.add(getattr(var, f"set_{name}_swtich")(swit))
