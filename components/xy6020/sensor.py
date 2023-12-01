import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_EMPTY,
    DEVICE_CLASS_POWER,
    DEVICE_CLASS_VOLTAGE,
    ICON_EMPTY,
    STATE_CLASS_MEASUREMENT,
    UNIT_AMPERE,
    UNIT_EMPTY,
    UNIT_PERCENT,
    UNIT_VOLT,
    UNIT_WATT,
    UNIT_CELSIUS,
   
)

from . import CONF_xy6020_ID, xy6020_COMPONENT_SCHEMA

DEPENDENCIES = ["xy6020"]

CODEOWNERS = ["@syssi"]

CONF_OUTPUT_VOLTAGE = "output_voltage"
CONF_OUTPUT_CURRENT = "output_current"
CONF_OUTPUT_POWER = "output_power"
CONF_INPUT_VOLTAGE = "input_voltage"
CONF_VOLTAGE_SETTING = "voltage_setting"
CONF_CURRENT_SETTING = "current_setting"
CONF_BACKLIGHT_BRIGHTNESS = "backlight_brightness"
CONF_FIRMWARE_VERSION = "firmware_version"
CONF_INTERN_TEMP = "intern_temp"
CONF_RUNTIMEHOURS = "runtimehours"
CONF_RUNTIMEMINUTES = "runtimeminutes"
CONF_run_power_hour = "run_power_hour"
CONF_run_current_hour = "run_current_hour"
CONF_M0_50 = "M0_50"
CONF_M0_51 = "M0_51"
CONF_M0_52 = "M0_52"
CONF_M0_53 = "M0_53"


ICON_BACKLIGHT_BRIGHTNESS = "mdi:brightness-6"

SENSORS = [
    CONF_OUTPUT_VOLTAGE,
    CONF_OUTPUT_CURRENT,
    CONF_OUTPUT_POWER,
    CONF_INPUT_VOLTAGE,
    CONF_VOLTAGE_SETTING,
    CONF_CURRENT_SETTING,
    CONF_BACKLIGHT_BRIGHTNESS,
    CONF_FIRMWARE_VERSION,
    CONF_INTERN_TEMP,
    CONF_RUNTIMEHOURS,
    CONF_RUNTIMEMINUTES,
    CONF_RUN_POWER_HOURS,
    CONF_RUN_CURRENT_HOURS,
    CONF_M0_50,
    CONF_M0_51,
    CONF_M0_52,
    CONF_M0_53,
]

# pylint: disable=too-many-function-args
CONFIG_SCHEMA = xy6020_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_OUTPUT_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_OUTPUT_CURRENT): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            accuracy_decimals=3,
            device_class=DEVICE_CLASS_CURRENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_OUTPUT_POWER): sensor.sensor_schema(
            unit_of_measurement=UNIT_WATT,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_POWER,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_INPUT_VOLTAGE): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_VOLTAGE_SETTING): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_VOLTAGE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_CURRENT_SETTING): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            accuracy_decimals=3,
            device_class=DEVICE_CLASS_CURRENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_BACKLIGHT_BRIGHTNESS): sensor.sensor_schema(
            unit_of_measurement=UNIT_PERCENT,
            icon=ICON_BACKLIGHT_BRIGHTNESS,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_FIRMWARE_VERSION): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
         ),
        cv.Optional(CONF_INTERN_TEMP): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_RUNTIMEHOURS): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_RUNTIMEMINUTES): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_RUN_CURRENT_HOURS): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_RUN_POWER_HOURS): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        
        ),
        cv.Optional(CONF_M0_50): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_M0_51): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
            
        ),
        cv.Optional(CONF_M0_52): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_M0_53): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon=ICON_EMPTY,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_xy6020_ID])
    for key in SENSORS:
        if key in config:
            conf = config[key]
            sens = await sensor.new_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_sensor")(sens))
