import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, modbus, modbus_controller
from esphome.const import (
    #CONF_INPUT_VOLTAGE,
    #CONF_OUTPUT_VOLTAGE,
    #CONF_TEMPERATURE_INTERN,
    CONF_ID,
    DEVICE_CLASS_VOLTAGE,
    ICON_CURRENT_AC,
    STATE_CLASS_MEASUREMENT,
    STATE_CLASS_TOTAL_INCREASING,
    UNIT_AMPERE,
    UNIT_HERTZ,
    UNIT_VOLT,
    UNIT_VOLT_AMPS,
    UNIT_VOLT_AMPS_REACTIVE,
    UNIT_WATT,
    CONF_ADDRESS,
)
AUTO_LOAD = ["modbus_controller"]
AUTO_LOAD = ["modbus"]
CODEOWNERS = ["@creepystefan"]

CONF_INPUT_VOLTAGE = "input_voltage"
CONF_OUTPUT_VOLTAGE = "output_voltage"
CONF_TEMPERATURE_INTERN = "temperature_intern"

UNIT_KILOWATT_HOURS = "kWh"
UNIT_KILOVOLT_AMPS_HOURS = "kVAh"
UNIT_KILOVOLT_AMPS_REACTIVE_HOURS = "kVARh"

test_ns = cg.esphome_ns.namespace("test")
TEST = test_ns.class_(
    "TEST", cg.PollingComponent, modbus.ModbusDevice
)


SENSORS = {
    CONF_INPUT_VOLTAGE: sensor.sensor_schema(
        platform=modbus_controller
        modbus_controller_id=modbus_device
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,
    ), 
  
}

CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(TEST)}),
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
