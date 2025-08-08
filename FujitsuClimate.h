#pragma once
#include "FujiHeatPump.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/climate/climate.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace fujitsu {

enum class ControllerType : uint8_t {
    PRIMARY = 0,
    SECONDARY = 1,
};

class FujitsuClimate : public climate::Climate, public Component {
   public:
    void setup() override;
    void loop() override;
    void control(const climate::ClimateCall &call) override;
    climate::ClimateTraits traits() override;
    void set_uart_parent(uart::UARTComponent *parent) { this->uart_ = parent; }
    void set_controller_type(ControllerType controller_type) { this->controller_type_ = controller_type; }
    void set_controller_is_secondary(bool is_secondary) { 
        this->controller_type_ = is_secondary ? ControllerType::SECONDARY : ControllerType::PRIMARY; 
    }
    void set_log_serial_messages(bool log_serial_messages) { this->log_serial_messages_ = log_serial_messages; }
    
    TaskHandle_t taskHandle;
    FujiHeatPump heatPump;
    FujiFrame sharedState;
    SemaphoreHandle_t lock;
    bool pendingUpdate;

   protected:
    uart::UARTComponent *uart_{nullptr};
    ControllerType controller_type_{ControllerType::SECONDARY};
    bool log_serial_messages_{false};

    void updateState();
    optional<climate::ClimateMode> fujiToEspMode(FujiMode fujiMode);
    optional<FujiMode> espToFujiMode(climate::ClimateMode espMode);
    
    optional<climate::ClimateFanMode> fujiToEspFanMode(FujiFanMode fujiFanMode);
    optional<FujiFanMode> espToFujiFanMode(climate::ClimateFanMode espFanMode);
};

}  // namespace fujitsu
}  // namespace esphome
