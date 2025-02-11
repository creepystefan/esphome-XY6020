import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch, modbus
from esphome.const import (
    CONF_ID,
#    DEVICE_CLASS_VOLTAGE,
#    DEVICE_CLASS_CURRENT,
#    DEVICE_CLASS_POWER,
#    ICON_CURRENT_AC,
#    STATE_CLASS_MEASUREMENT,
#    STATE_CLASS_TOTAL_INCREASING,
#    UNIT_AMPERE,
#    UNIT_HERTZ,
#    UNIT_VOLT,
#    UNIT_VOLT_AMPS,
#    UNIT_VOLT_AMPS_REACTIVE,
#    UNIT_WATT,
    CONF_ADDRESS,
)

AUTO_LOAD = ["modbus"]
CODEOWNERS = ["@creepystefan"]

CONF_TURN_ON_OFF = "turn_on_off"
CONF_KEY_PROTECT = "key_protect"


#UNIT_KILOWATT_HOURS = "kWh"
#UNIT_KILOVOLT_AMPS_HOURS = "kVAh"
#UNIT_KILOVOLT_AMPS_REACTIVE_HOURS = "kVARh"
#UNIT_MODEL = "Model"
#UNIT_SOFTWARE_VERSION = "Version"

xy6020_ns = cg.esphome_ns.namespace("xy6020")
XY6020 = xy6020_ns.class_(
    "XY6020", cg.PollingComponent, modbus.ModbusDevice
)

SENSORS = {
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
        {cv.Optional(sensor_name): schema for sensor_name, schema in SENSORS.items()}
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(modbus.modbus_device_schema(0x01))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await modbus.register_modbus_device(var, config)
    for name in SENSORS:
        if name in config:
            sens = await sensor.new_sensor(config[name])
            cg.add(getattr(var, f"set_{name}_sensor")(sens))
