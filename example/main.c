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

void example1(lora_serialization_t *serialization)
{
    lora_serialization_reset(serialization);
    //lora_serialization_write_temperature(serialization, 35.4);
    //lora_serialization_write_coordinates(serialization, 53.557001, 10.022856);
    print_buffer(serialization);
}

int main(void)
{
    lora_serialization_t serialization;

    example1(&serialization);

    return 0;
}