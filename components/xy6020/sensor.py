import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, modbus, modbus_controller
from esphome.const import (
    CONF_ACTIVE_POWER,
    CONF_APPARENT_POWER,
    CONF_CURRENT,
    CONF_EXPORT_ACTIVE_ENERGY,
    CONF_EXPORT_REACTIVE_ENERGY,
    CONF_FREQUENCY,
    CONF_ID,
    CONF_IMPORT_ACTIVE_ENERGY,
    CONF_IMPORT_REACTIVE_ENERGY,
    CONF_POWER_FACTOR,
    CONF_REACTIVE_POWER,
    CONF_VOLTAGE,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_ENERGY,
    DEVICE_CLASS_POWER,
    DEVICE_CLASS_POWER_FACTOR,
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

AUTO_LOAD = ["modbus"]
CODEOWNERS = ["@creepystefan"]

CONF_INPUT_VOLTAGE = "input_voltage"
CONF_OUTPUT_VOLTAGE = "output_voltage"
CONF_TEMPERATURE_INTERN = "temperature_intern"

UNIT_KILOWATT_HOURS = "kWh"
UNIT_KILOVOLT_AMPS_HOURS = "kVAh"
UNIT_KILOVOLT_AMPS_REACTIVE_HOURS = "kVARh"

xy6020_ns = cg.esphome_ns.namespace("xy6020")
XY_6020 = xy6020_ns.class_(
    "XY_6020", cg.PollingComponent, modbus.ModbusDevice
)


SENSORS = {
    CONF_INPUT_VOLTAGE: sensor.sensor_schema(
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,
    ), 
    CONF_OUTPUT_VOLTAGE: sensor.sensor_schema(
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
}

CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(SelecMeter)})
    .extend(
        {cv.Optional(sensor_name): schema for sensor_name, schema in SENSORS.items()}
    )
    .extend(cv.polling_component_schema("10s"))
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
