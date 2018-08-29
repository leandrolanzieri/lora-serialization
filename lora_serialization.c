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

#include "byteorder.h"
#include "assert.h"
#include "lora_serialization.h"

void lora_serialization_reset(lora_serialization_t *serialization)
{
    memset(serialization->buffer, 0, LORA_SERIALIZATION_MAX_BUFFER_SIZE);
    serialization->cursor = 0;
}

int lora_serialization_write_unix_time(lora_serialization_t *serialization,
                                       uint32_t unixtime)
{
    le_uint32_t *value = (le_uint32_t *)
                         (serialization->buffer + serialization->cursor);

    if ((serialization->cursor + LORA_SERIALIZATION_UNIX_TIME_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    *value = byteorder_btoll(byteorder_htonl(unixtime));
    serialization->cursor += LORA_SERIALIZATION_UNIX_TIME_SIZE;

    return 0;
}

int lora_serialization_write_coordinates(lora_serialization_t *serialization,
                                         double latitude, double longitude)
{
    int32_t lat = latitude * 1e6;
    int32_t lng = longitude * 1e6;
    le_uint32_t *lat_value = (le_uint32_t *)
                             (serialization->buffer + serialization->cursor);
    le_uint32_t *lng_value = (le_uint32_t *)
                             (serialization->buffer + serialization->cursor
                              + LORA_SERIALIZATION_LATITUDE_SIZE);

    if ((serialization->cursor + LORA_SERIALIZATION_GPS_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    *lat_value = byteorder_btoll(byteorder_htonl(lat));
    *lng_value = byteorder_btoll(byteorder_htonl(lng));

    serialization->cursor += LORA_SERIALIZATION_GPS_SIZE;

    return 0;
}

int lora_serialization_write_uint16(lora_serialization_t *serialization,
                                    uint16_t i)
{
    le_uint16_t *value = (le_uint16_t *)
                         (serialization->buffer + serialization->cursor);

    if ((serialization->cursor + LORA_SERIALIZATION_UINT16_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    *value = byteorder_btols(byteorder_htons(i));
    serialization->cursor += LORA_SERIALIZATION_UINT16_SIZE;

    return 0;
}

int lora_serialization_write_uint8(lora_serialization_t *serialization,
                                   uint8_t i)
{
    if ((serialization->cursor + LORA_SERIALIZATION_UINT8_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    (serialization->buffer)[serialization->cursor] = i;
    serialization->cursor += LORA_SERIALIZATION_UINT8_SIZE;

    return 0;
}

int lora_serialization_write_humidity(lora_serialization_t *serialization,
                                      float humidity)
{
    int16_t h = (int16_t)(humidity * 100);
    le_uint16_t *value = (le_uint16_t *)
                         (serialization->buffer + serialization->cursor);

    if ((serialization->cursor + LORA_SERIALIZATION_HUMIDITY_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    *value = byteorder_btols(byteorder_htons(h));
    serialization->cursor += LORA_SERIALIZATION_HUMIDITY_SIZE;

    return 0;
}

/* The temperature has to be  written in Big Endian */
int lora_serialization_write_temperature(lora_serialization_t *serialization,
                                         float temperature)
{
    int16_t t = (int16_t) (temperature * 100);
    network_uint16_t *value = (network_uint16_t *)
                              (serialization->buffer + serialization->cursor);

    if ((serialization->cursor + LORA_SERIALIZATION_TEMPERATURE_SIZE) >=
        LORA_SERIALIZATION_MAX_BUFFER_SIZE) {
        return -ENOBUFS;
    }

    if (temperature < 0) {
        t = ~-t;
        t++;
    }

    *value = byteorder_htons((uint16_t) t);
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
