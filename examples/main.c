/*
 * Copyright (C) 2018 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @brief       Lora-serialization example
 *
 * @author      Leandro Lanzieri <leandro.lanzieri@haw-hamburg.de>
 * @author      Jose Ignacio Alamos <jose.alamos@haw-hamburg.de>
 */

#include <stdio.h>

#include "lora_serialization.h"

static void print_buffer(lora_serialization_t *serialization)
{
    for (uint8_t i = 0; i < serialization->cursor; i++) {
        printf("%02X", serialization->buffer[i]);
    }
    puts("\n");
}

void example_temerature(lora_serialization_t *serialization)
{
    float t = 35.4;

    printf("> Temperature example\n");
    
    lora_serialization_reset(serialization);
    
    printf("  Adding temperature: %.2f\n", t);
    lora_serialization_write_temperature(serialization, t);
    
    printf("  Encoded information: ");
    print_buffer(serialization);
}

void example_weather_station_log(lora_serialization_t *serialization)
{
    uint32_t unix_time = 1535557041;
    double lat = 53.5570, lng = 10.0229;
    float t = 26.3, h = 37.6;
    uint8_t battery = 75;

    printf("> Weather station example\n");
    lora_serialization_reset(serialization);

    /* time */
    printf("  Adding time: %d\n", unix_time);
    lora_serialization_write_unix_time(serialization, unix_time);

    /* position */
    printf("  Adding position: %.4f, %.4f\n", lat, lng);
    lora_serialization_write_coordinates(serialization, lat, lng);

    /* temperature */
    printf("  Adding temperature: %.2f\n", t);
    lora_serialization_write_temperature(serialization, t);

    /* humidity */
    printf("  Adding humidity: %.2f\n", h);
    lora_serialization_write_humidity(serialization, h);

    /* battery */
    printf("  Adding humidity: %d\n", battery);
    lora_serialization_write_uint8(serialization, battery);

    printf("  Encoded information: ");
    print_buffer(serialization);
}

int main(void)
{
    lora_serialization_t serialization;

    example_temerature(&serialization);
    example_weather_station_log(&serialization);

    return 0;
}
