#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"
#include <Adafruit_ADT7410.h>

namespace esphome {
namespace adt7410 {

class ADT7410Component : public PollingComponent, public i2c::I2CDevice, public sensor::Sensor {
 public:
  ADT7410Component() : PollingComponent(60000) {}  // Default update interval: 60s

  void setup() override;
  void update() override;
  void dump_config() override;

 protected:
  Adafruit_ADT7410 adt7410_;
};

}  // namespace adt7410
}  // namespace esphome
