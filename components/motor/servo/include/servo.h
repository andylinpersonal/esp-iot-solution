// Copyright 2020 Espressif Systems (Shanghai) Co. Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _IOT_SERVO_H_
#define _IOT_SERVO_H_

#include "esp_err.h"
#include "driver/ledc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configuration of servo motor channel
 * 
 */
typedef struct {
    int8_t servo_pin[LEDC_CHANNEL_MAX];     /**< Pin number of pwm output */
    ledc_channel_t ch[LEDC_CHANNEL_MAX];    /**< The ledc channel which used */
} servo_channel_t;

/**
 * @brief Configuration of servo motor
 * 
 */
typedef struct {
    uint16_t max_angle;        /**< Servo max angle */
    uint16_t min_width_us;     /**< Pulse width corresponding to minimum angle, which is usually 500us */
    uint16_t max_width_us;     /**< Pulse width corresponding to maximum angle, which is usually 2500us */
    ledc_mode_t speed_mode;    /**< speed mode of ledc */
    uint32_t freq;             /**< PWM frequency */
    ledc_timer_t timer_number; /**< Timer number of ledc */
    servo_channel_t channels;  /**< Channels to use */
    uint8_t channel_number;    /**< Total channel number */
} servo_config_t;

/**
 * @brief Initialize ledc to control the servo
 * 
 * @param config Pointer of servo configure struct
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 *     - ESP_FAIL Configure ledc failed
 */
esp_err_t servo_init(const servo_config_t *config);

/**
 * @brief Deinitialize ledc for servo
 * 
 * @return
 *     - ESP_OK Success
 */
esp_err_t servo_deinit(void);

/**
 * @brief Set the servo motor to a certain angle
 * 
 * @param channel LEDC channel (0-7), select from ledc_channel_t
 * @param angle The angle to go
 * 
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
esp_err_t servo_write_angle(uint8_t channel, float angle);

/**
 * @brief Read current angle of one channel 
 * 
 * @param channel LEDC channel (0-7), select from ledc_channel_t
 * @param angle Current angle of the channel
 * 
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 */
esp_err_t servo_read_angle(uint8_t channel, float *angle);

#ifdef __cplusplus
}
#endif

#endif /* _IOT_SERVO_H_ */
