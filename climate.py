import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, uart
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

CONF_CONTROLLER_TYPE = "controller_type"
CONF_LOG_SERIAL_MESSAGES = "log_serial_messages"

fujitsu_climate_ns = cg.esphome_ns.namespace("fujitsu")
FujitsuClimate = fujitsu_climate_ns.class_("FujitsuClimate", climate.Climate, cg.Component)

CONTROLLER_TYPES = {
    "PRIMARY": "PRIMARY",
    "SECONDARY": "SECONDARY",
}

CONFIG_SCHEMA = climate.climate_schema(FujitsuClimate).extend(
    {
        cv.GenerateID(): cv.declare_id(FujitsuClimate),
        cv.Required("uart_id"): cv.use_id(uart.UARTComponent),
        cv.Optional(CONF_CONTROLLER_TYPE, default="SECONDARY"): cv.enum(CONTROLLER_TYPES, upper=True),
        cv.Optional(CONF_LOG_SERIAL_MESSAGES, default=False): cv.boolean,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await climate.register_climate(var, config)

    uart_component = await cg.get_variable(config["uart_id"])
    cg.add(var.set_uart_parent(uart_component))
    
    # Handle controller type using boolean method
    is_secondary = config[CONF_CONTROLLER_TYPE] == "SECONDARY"
    cg.add(var.set_controller_is_secondary(is_secondary))
    
    cg.add(var.set_log_serial_messages(config[CONF_LOG_SERIAL_MESSAGES]))
