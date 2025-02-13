import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import {
    CONF_UPDATE_INTERVAL,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
}

DEPENDENCIES = ["i2c"]
CODEOWNERS = ["@David-Jackson"]

# Create namespace for the component
adt7410_ns = cg.esphome_ns.namespace("adt7410")
ADT7410Component = adt7410_ns.class_(
    "ADT7410Component", cg.PollingComponent, i2c.I2CDevice, sensor.Sensor
)

# Default I2C address for ADT7410
DEFAULT_I2C_ADDRESS = 0x48

# Configuration schema for YAML
CONFIG_SCHEMA = (
    sensor.sensor_schema(
        ADT7410Component,
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=2,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(i2c.i2c_device_schema(DEFAULT_I2C_ADDRESS))
    .extend(cv.polling_component_schema("60s"))  # Default update interval: 60s
)

# Code generation for ESPHome
async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
