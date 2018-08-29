/*
 * Copyright (C) 2018 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @addtogroup  unittests
 * @{
 *
 * @file
 * @brief       Unittests for the ``lora-serialization`` module
 *
 * @author      Leandro Lanzieri <leandro.lanzieri@haw-hamburg.de>
 * @author      Jose Ignacio Alamos <jose.alamos@haw-hamburg.de>
 */

#define LORA_SERIALIZATION_FAKE_CURSOR              (20U)
#define LORA_SERIALIZATION_UNIX_TIME_SIMPLE         (1)
#define LORA_SERIALIZATION_UNIX_TIME                (1467632413)
#define LORA_SERIALIZATION_LATITUDE                 (-33.905052)
#define LORA_SERIALIZATION_LONGITUDE                (151.26641)
#define LORA_SERIALIZATION_UINT8                    (10)
#define LORA_SERIALIZATION_UINT16                   (23453)
#define LORA_SERIALIZATION_TEMPERATURE              (80.12)
#define LORA_SERIALIZATION_NEGATIVE_TEMPERATURE     (-123.45)
#define LORA_SERIALIZATION_HUMIDITY                 (99.99)

#define LORA_SERIALIZATION_EXPECTED_UNIX_TIME_SIMPLE        { 1, 0, 0, 0 }
#define LORA_SERIALIZATION_EXPECTED_UNIX_TIME               { 0x1d, 0x4b, 0x7a, 0x57 }
#define LORA_SERIALIZATION_EXPECTED_COORDS                  { 0x64, 0xa6, 0xfa, 0xfd, \
                                                              0x6a, 0x24, 0x04, 0x09 }
#define LORA_SERIALIZATION_EXPECTED_UINT8                   { 0x0A }
#define LORA_SERIALIZATION_EXPECTED_UINT16                  { 0x9d, 0x5b }
#define LORA_SERIALIZATION_EXPECTED_TEMPERATURE             { 0x1f, 0x4c }
#define LORA_SERIALIZATION_EXPECTED_NEGATIVE_TEMPERATURE    { 0xcf, 0xc7 }
#define LORA_SERIALIZATION_EXPECTED_HUMIDITY                { 0x0f, 0x27 }

#define LORA_SERIALIZATION_EXPECTED_TEST {                \
        0x1d, 0x4b, 0x7a, 0x57,                           \
        0x64, 0xa6, 0xfa, 0xfd, 0x6a, 0x24, 0x04, 0x09,   \
        0x0A,                                             \
        0x9d, 0x5b,                                       \
        0x1f, 0x4c,                                       \
        0x0f, 0x27                                        \
};
