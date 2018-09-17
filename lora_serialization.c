/*
 * Copyright (C) 2018 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @brief       Lora-serialization format implementation
 *
 * @author      Leandro Lanzieri <leandro.lanzieri@haw-hamburg.de>
 * @author      Jose Ignacio Alamos <jose.alamos@haw-hamburg.de>
 */

#include "assert.h"
#include "lora_serialization.h"

static void _int_to_bytes(uint8_t *buffer, int value,
                                            uint8_t byteSize);

void lora_serialization_reset(lora_serialization_t *serialization)
{
    memset(serialization->buffer, 0, LORA_SERIALIZATION_MAX_BUFFER_SIZE);
    serialization->cursor = 0;
}

int lora_serialization_write_unix_time(lora_serialization_t *serialization,
                                       uint32_t unixtime)
{
    uint8_t *slot = (uint8_t*)(serialization->buffer + serialization->cursor);

    if ((serialization->cursor + LORA_SERIALIZATION_UNIX_TIME_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    _int_to_bytes(slot, unixtime, LORA_SERIALIZATION_UNIX_TIME_SIZE);
    serialization->cursor += LORA_SERIALIZATION_UNIX_TIME_SIZE;

    return 0;
}

int lora_serialization_write_coordinates(lora_serialization_t *serialization,
                                         double latitude, double longitude)
{
    int32_t lat = latitude * 1e6;
    int32_t lng = longitude * 1e6;
    uint8_t *lat_slot = (uint8_t *)
                             (serialization->buffer + serialization->cursor);
    uint8_t *lng_slot = (uint8_t *)
                             (serialization->buffer + serialization->cursor
                              + LORA_SERIALIZATION_LATITUDE_SIZE);

    if ((serialization->cursor + LORA_SERIALIZATION_GPS_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    _int_to_bytes(lat_slot, lat, LORA_SERIALIZATION_LATITUDE_SIZE);
    _int_to_bytes(lng_slot, lng, LORA_SERIALIZATION_LONGITUDE_SIZE);
    serialization->cursor += LORA_SERIALIZATION_GPS_SIZE;

    return 0;
}

int lora_serialization_write_uint16(lora_serialization_t *serialization,
                                    uint16_t value)
{
    uint8_t *slot = (uint8_t *)
                         (serialization->buffer + serialization->cursor);

    if ((serialization->cursor + LORA_SERIALIZATION_UINT16_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    _int_to_bytes(slot, value, LORA_SERIALIZATION_UINT16_SIZE);
    serialization->cursor += LORA_SERIALIZATION_UINT16_SIZE;

    return 0;
}

int lora_serialization_write_uint8(lora_serialization_t *serialization,
                                   uint8_t value)
{
    if ((serialization->cursor + LORA_SERIALIZATION_UINT8_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    (serialization->buffer)[serialization->cursor] = value;
    serialization->cursor += LORA_SERIALIZATION_UINT8_SIZE;

    return 0;
}

int lora_serialization_write_humidity(lora_serialization_t *serialization,
                                      float humidity)
{
    int16_t h = (int16_t)(humidity * 100);
    uint8_t *slot = (uint8_t *)
                         (serialization->buffer + serialization->cursor);

    if ((serialization->cursor + LORA_SERIALIZATION_HUMIDITY_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    _int_to_bytes(slot, h, LORA_SERIALIZATION_HUMIDITY_SIZE);
    serialization->cursor += LORA_SERIALIZATION_HUMIDITY_SIZE;

    return 0;
}

/* The temperature has to be written in Big Endian */
int lora_serialization_write_temperature(lora_serialization_t *serialization,
                                         float temperature)
{
    int16_t t = (int16_t) (temperature * 100);
    uint8_t *slot = (uint8_t *)
                              (serialization->buffer + serialization->cursor);

    if ((serialization->cursor + LORA_SERIALIZATION_TEMPERATURE_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    if (temperature < 0) {
        t = ~-t;
        t++;
    }

    t = (t << 8) | ((t >> 8) & 0xFF);

    _int_to_bytes(slot, t, LORA_SERIALIZATION_TEMPERATURE_SIZE);
    serialization->cursor += LORA_SERIALIZATION_TEMPERATURE_SIZE;

    return 0;
}

int lora_serialization_write_bitmap(lora_serialization_t *serialization,
                                    lora_serialization_bitmap_t bitmap)
{
    uint8_t *bitmapPtr = (uint8_t*)&bitmap;

    if ((serialization->cursor + LORA_SERIALIZATION_BITMAP_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    serialization->buffer[serialization->cursor] = *bitmapPtr;

    return 0;
}

static void _int_to_bytes(uint8_t *buffer, int value,
                                       uint8_t byteSize)
{
    for (uint8_t i = 0; i < byteSize; i++) {
        buffer[i] = (uint8_t)(value >> (i * 8));
    }
}
