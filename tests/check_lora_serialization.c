/*
 * Copyright (C) 2018 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @brief       Lora-serialization tests
 *
 * @author      Leandro Lanzieri <leandro.lanzieri@haw-hamburg.de>
 * @author      Jose Ignacio Alamos <jose.alamos@haw-hamburg.de>
 */

#include <check.h>
#include <string.h>

#include "../lora_serialization.h"
#include "check_lora_serialization.h"

lora_serialization_t serialization;

START_TEST(test_lora_serialization_reset)
{
    serialization.cursor = LORA_SERIALIZATION_FAKE_CURSOR;
    ck_assert_int_eq(serialization.cursor, LORA_SERIALIZATION_FAKE_CURSOR);
    lora_serialization_reset(&serialization);
    ck_assert_int_eq(serialization.cursor, 0);
}
END_TEST

START_TEST(test_lora_serialization_write_time_simple)
{
    /* should transform a simple unixtime to a byte array */
    uint8_t expected[] = LORA_SERIALIZATION_EXPECTED_UNIX_TIME_SIMPLE;
    
    lora_serialization_reset(&serialization);

    lora_serialization_write_unix_time(&serialization,
                                       LORA_SERIALIZATION_UNIX_TIME_SIMPLE);

    ck_assert_int_eq(0, memcmp(expected, serialization.buffer,
                               sizeof(expected)));
}
END_TEST

START_TEST(test_lora_serialization_write_time)
{
    /* should transform a given unixtime to a byte array */
    uint32_t now = LORA_SERIALIZATION_UNIX_TIME;
    uint8_t expected[] = LORA_SERIALIZATION_EXPECTED_UNIX_TIME;

    lora_serialization_reset(&serialization);

    lora_serialization_write_unix_time(&serialization, now);

    ck_assert_str_eq(expected, serialization.buffer);
}
END_TEST

START_TEST(test_lora_serialization_write_coordinates)
{
    /* should transform a coordinate to a byte array */
    lora_serialization_reset(&serialization);
    uint8_t expected[] = LORA_SERIALIZATION_EXPECTED_COORDS;

    lora_serialization_write_coordinates(&serialization,
                                         LORA_SERIALIZATION_LATITUDE,
                                         LORA_SERIALIZATION_LONGITUDE);

    ck_assert_int_eq(0, memcmp(expected, serialization.buffer,
                               sizeof(expected)));
}
END_TEST

START_TEST(test_lora_serialization_write_8bit)
{
    /* should transform an unsigned 8bit int to a byte array */
    uint8_t expected[] = LORA_SERIALIZATION_EXPECTED_UINT8;
    lora_serialization_reset(&serialization);

    lora_serialization_write_uint8(&serialization,
                                   LORA_SERIALIZATION_UINT8);

    ck_assert_int_eq(0, memcmp(expected, serialization.buffer,
                               sizeof(expected)));
}
END_TEST

START_TEST(test_lora_serialization_write_16bit)
{
    /* should transform an unsigned 16bit int to a byte array */
    uint8_t expected[] = LORA_SERIALIZATION_EXPECTED_UINT16;
    lora_serialization_reset(&serialization);

    lora_serialization_write_uint16(&serialization,
                                    LORA_SERIALIZATION_UINT16);

    ck_assert_int_eq(0, memcmp(expected, serialization.buffer,
                               sizeof(expected)));
}
END_TEST

START_TEST(test_lora_serialization_write_temperature)
{
    /* should transform a temperature to a byte array */
    uint8_t expected[] = LORA_SERIALIZATION_EXPECTED_TEMPERATURE;
    lora_serialization_reset(&serialization);

    lora_serialization_write_temperature(&serialization,
                                         LORA_SERIALIZATION_TEMPERATURE);

    ck_assert_int_eq(0, memcmp(expected, serialization.buffer,
                               sizeof(expected)));
}
END_TEST

START_TEST(test_lora_serialization_write_negative_temperature)
{
    /* should transform a negative temperature to a byte array */
    uint8_t expected[] = LORA_SERIALIZATION_EXPECTED_NEGATIVE_TEMPERATURE;
    lora_serialization_reset(&serialization);

    lora_serialization_write_temperature(&serialization,
                                       LORA_SERIALIZATION_NEGATIVE_TEMPERATURE);

    ck_assert_int_eq(0, memcmp(expected, serialization.buffer,
                               sizeof(expected)));
}
END_TEST

START_TEST(test_lora_serialization_write_humidity)
{
    /* should transform a humidity to a byte array */
    uint8_t expected[] = LORA_SERIALIZATION_EXPECTED_HUMIDITY;
    lora_serialization_reset(&serialization);

    lora_serialization_write_humidity(&serialization,
                                      LORA_SERIALIZATION_HUMIDITY);

    ck_assert_int_eq(0, memcmp(expected, serialization.buffer,
                               sizeof(expected)));
}
END_TEST

START_TEST(test_lora_serialization_write_multiple_fields)
{
    /* write multiple fields to one byte array */
    uint8_t expected[] = LORA_SERIALIZATION_EXPECTED_TEST;
    lora_serialization_reset(&serialization);

    lora_serialization_write_unix_time(&serialization,
                                       LORA_SERIALIZATION_UNIX_TIME);
    lora_serialization_write_coordinates(&serialization,
                                         LORA_SERIALIZATION_LATITUDE,
                                         LORA_SERIALIZATION_LONGITUDE);
    lora_serialization_write_uint8(&serialization,
                                   LORA_SERIALIZATION_UINT8);
    lora_serialization_write_uint16(&serialization,
                                    LORA_SERIALIZATION_UINT16);
    lora_serialization_write_temperature(&serialization,
                                         LORA_SERIALIZATION_TEMPERATURE);
    lora_serialization_write_humidity(&serialization,
                                      LORA_SERIALIZATION_HUMIDITY);

    ck_assert_int_eq(0, memcmp(expected, serialization.buffer,
                               sizeof(expected)));

    ck_assert_int_eq(serialization.cursor, sizeof(expected));
}
END_TEST

START_TEST(test_lora_serialization_full_buffer)
{
    /* should fail to write more than LORA_SERIALIZATION_MAX_BUFFER_SIZE bytes */
    lora_serialization_reset(&serialization);
    uint8_t iterations = LORA_SERIALIZATION_MAX_BUFFER_SIZE /
                         LORA_SERIALIZATION_UINT8_SIZE;

    for (uint8_t i = 0; i < iterations; i++) {
        lora_serialization_write_uint8(&serialization,
                                       LORA_SERIALIZATION_UINT8);
    }

    ck_assert_int_eq(
            lora_serialization_write_uint8(
                &serialization, LORA_SERIALIZATION_UINT8),
            -ENOBUFS);
}
END_TEST

Suite* lora_serialization_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Lora Serialization");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_lora_serialization_reset);
    tcase_add_test(tc_core, test_lora_serialization_write_time_simple);
    tcase_add_test(tc_core, test_lora_serialization_write_time);
    tcase_add_test(tc_core, test_lora_serialization_write_coordinates);
    tcase_add_test(tc_core, test_lora_serialization_write_8bit);
    tcase_add_test(tc_core, test_lora_serialization_write_16bit);
    tcase_add_test(tc_core, test_lora_serialization_write_temperature);
    tcase_add_test(tc_core, test_lora_serialization_write_negative_temperature);
    tcase_add_test(tc_core, test_lora_serialization_write_humidity);
    tcase_add_test(tc_core, test_lora_serialization_write_multiple_fields);
    tcase_add_test(tc_core, test_lora_serialization_full_buffer);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = lora_serialization_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed != 0);
}
