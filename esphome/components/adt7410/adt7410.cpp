#include "adt7410.h"
#include "esphome/core/log.h"

namespace esphome {
namespace adt7410 {

static const char *const TAG = "adt7410.sensor";

void ADT7410Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up ADT7410 sensor...");

  // Initialize the sensor
  if (!adt7410_.begin()) {
    ESP_LOGE(TAG, "Failed to find ADT7410 sensor!");
    mark_failed();
    return;
  }

  // Set to 16-bit resolution mode
  adt7410_.setResolution(ADT7410_16BIT);
}

void ADT7410Component::update() {
  ESP_LOGD(TAG, "Reading temperature from ADT7410...");

  float temperature = adt7410_.readTempC();
  if (isnan(temperature)) {
    ESP_LOGW(TAG, "Failed to read temperature!");
    return;
  }

  ESP_LOGD(TAG, "Temperature: %.2f °C", temperature);
  publish_state(temperature);
}

void ADT7410Component::dump_config() {
  ESP_LOGCONFIG(TAG, "ADT7410 Sensor:");
  LOG_I2C_DEVICE(this);
  LOG_UPDATE_INTERVAL(this);
}

}  // namespace adt7410
}  // namespace esphome
