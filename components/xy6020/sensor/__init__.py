import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, modbus
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_VOLTAGE,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_POWER,
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

AUTO_LOAD = ["modbus"]
CODEOWNERS = ["@creepystefan"]

CONF_SETED_OUTPUT_VOLTAGE = "seted_output_voltage"
CONF_SETED_OUTPUT_CURRENT = "seted_output_current"
CONF_OUTPUT_VOLTAGE = "output_voltage"
CONF_OUTPUT_CURRENT = "output_current"
CONF_OUTPUT_POWER = "output_power"
CONF_INPUT_VOLTAGE = "input_voltage"
CONF_TEMPERATURE_INTERN = "temperature_intern"
CONF_TEMPERATURE_EXTERN = "temperature_extern"
CONF_MODEL = "model"
CONF_SOFTWARE_VERSION = "software_version"

UNIT_KILOWATT_HOURS = "kWh"
UNIT_KILOVOLT_AMPS_HOURS = "kVAh"
UNIT_KILOVOLT_AMPS_REACTIVE_HOURS = "kVARh"
UNIT_MODEL = "Model"
UNIT_SOFTWARE_VERSION = "Version"

xy6020_ns = cg.esphome_ns.namespace("xy6020")
XY6020Sensor = xy6020_ns.class_(
    "XY6020Sensor", cg.PollingComponent, modbus.ModbusDevice
)

SENSORS = {
    CONF_SETED_OUTPUT_VOLTAGE: sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,
    ), 
    CONF_SETED_OUTPUT_CURRENT: sensor.sensor_schema(
        unit_of_measurement=UNIT_AMPERE,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_CURRENT,
        state_class=STATE_CLASS_MEASUREMENT,
    ), 
    CONF_OUTPUT_VOLTAGE: sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,
    ), 
    CONF_OUTPUT_CURRENT: sensor.sensor_schema(
        unit_of_measurement=UNIT_AMPERE,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_CURRENT,
        state_class=STATE_CLASS_MEASUREMENT,
    ), 
     CONF_OUTPUT_POWER: sensor.sensor_schema(
        unit_of_measurement=UNIT_WATT,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_POWER,
        state_class=STATE_CLASS_MEASUREMENT,
    ), 
    CONF_INPUT_VOLTAGE: sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,
    ), 
    CONF_TEMPERATURE_INTERN: sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,

    ), 
    CONF_TEMPERATURE_EXTERN: sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,
    ),
    CONF_MODEL: sensor.sensor_schema(
        unit_of_measurement=UNIT_MODEL,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_VOLTAGE,
#        state_class=STATE_CLASS_MEASUREMENT,
    ),
    CONF_SOFTWARE_VERSION: sensor.sensor_schema(
        unit_of_measurement=UNIT_SOFTWARE_VERSION,
        accuracy_decimals=0,
        device_class=DEVICE_CLASS_VOLTAGE,
#        state_class=STATE_CLASS_MEASUREMENT,
    ),
    
}

CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(XY6020Sensor)})
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
