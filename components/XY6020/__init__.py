import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import modbus
from esphome.const import CONF_ID

CODEOWNERS = ["@syssi"]

DEPENDENCIES = ["modbus"]
AUTO_LOAD = ["binary_sensor", "number", "sensor", "switch", "text_sensor"]
MULTI_CONF = True

CONF_XY6020_ID = "XY6020_id"
CONF_CURRENT_RESOLUTION = "current_resolution"

XY6020_ns = cg.esphome_ns.namespace("XY6020")
XY6020 = XY6020_ns.class_("XY6020", cg.PollingComponent, modbus.ModbusDevice)

CurrentResolution = XY6020_ns.enum("CurrentResolution")
CURRENT_RESOLUTION_OPTIONS = {
    "AUTO": CurrentResolution.XY6020_CURRENT_RESOLUTION_AUTO,
    "LOW": CurrentResolution.XY6020_CURRENT_RESOLUTION_LOW,
    "HIGH": CurrentResolution.XY6020_CURRENT_RESOLUTION_HIGH,
}

XY6020_COMPONENT_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_XY6020_ID): cv.use_id(XY6020),
    }
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(XY6020),
            cv.Optional(CONF_CURRENT_RESOLUTION, default="AUTO"): cv.enum(
                CURRENT_RESOLUTION_OPTIONS, upper=True
            ),
        }
    )
    .extend(cv.polling_component_schema("5s"))
    .extend(modbus.modbus_device_schema(0x01))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await modbus.register_modbus_device(var, config)

    cg.add(var.set_current_resolution(config[CONF_CURRENT_RESOLUTION]))
