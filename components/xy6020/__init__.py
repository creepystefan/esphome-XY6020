import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import modbus
from esphome.const import CONF_ID

CODEOWNERS = ["@syssi"]

DEPENDENCIES = ["modbus"]
AUTO_LOAD = ["binary_sensor", "number", "sensor", "switch", "text_sensor"]
MULTI_CONF = True

CONF_xy6020_ID = "xy6020_id"
CONF_CURRENT_RESOLUTION = "current_resolution"

xy6020_ns = cg.esphome_ns.namespace("xy6020")
xy6020 = xy6020_ns.class_("xy6020", cg.PollingComponent, modbus.ModbusDevice)

CurrentResolution = xy6020_ns.enum("CurrentResolution")
CURRENT_RESOLUTION_OPTIONS = {
    "AUTO": CurrentResolution.xy6020_CURRENT_RESOLUTION_AUTO,
    "LOW": CurrentResolution.xy6020_CURRENT_RESOLUTION_LOW,
    "HIGH": CurrentResolution.xy6020_CURRENT_RESOLUTION_HIGH,
}

xy6020_COMPONENT_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_xy6020_ID): cv.use_id(xy6020),
    }
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(xy6020),
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
