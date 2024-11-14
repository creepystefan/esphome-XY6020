import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, modbus
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
)

AUTO_LOAD = ["modbus"]
CODEOWNERS = ["@creepystefan"]

CONF_TOTAL_ACTIVE_ENERGY = "total_active_energy"
CONF_TOTAL_REACTIVE_ENERGY = "total_reactive_energy"
CONF_APPARENT_ENERGY = "apparent_energy"
CONF_MAXIMUM_DEMAND_ACTIVE_POWER = "maximum_demand_active_power"
CONF_MAXIMUM_DEMAND_REACTIVE_POWER = "maximum_demand_reactive_power"
CONF_MAXIMUM_DEMAND_APPARENT_POWER = "maximum_demand_apparent_power"
CONF_VOLTAGE_INPUT = "voltage_input"

UNIT_KILOWATT_HOURS = "kWh"
UNIT_KILOVOLT_AMPS_HOURS = "kVAh"
UNIT_KILOVOLT_AMPS_REACTIVE_HOURS = "kVARh"

selec_meter_ns = cg.esphome_ns.namespace("selec_meter")
SelecMeter = selec_meter_ns.class_(
    "SelecMeter", cg.PollingComponent, modbus.ModbusDevice
)


SENSORS = {
    CONF_VOLTAGE_INPUT: sensor.sensor_schema(
        adress=0x02,
        register_type="holding",
        value_type="U_WORD",
        unit_of_measurement="V",
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_ENERGY,
        state_class=STATE_CLASS_TOTAL_INCREASING,
        
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
