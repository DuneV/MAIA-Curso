#include <stdio.h>
#include <mpu6050.hpp>

extern "C" {
    void app_main(void);
}

void app_main(void) {

    // clk gpio pin 23
    // sda gpio pin 22
    // read speed 50 ms
    Mpu6050* imu = new Mpu6050(10, 11, 50);

    while (1) {
        imu->read_mpu6050();
        imu->calculate_angles_madgwick();
        printf("%.2f, %.2f, %.2f, Temperature: %.2f\n", imu->data[0], imu->data[1], imu->data[2], imu->temperature);
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}