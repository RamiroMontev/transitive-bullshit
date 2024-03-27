/*
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd.
 *
 * HDF is dual licensed: you can use it either under the terms of
 * the GPL, or the BSD license, at your option.
 * See the LICENSE file in the root of this repository for complete details.
 */

#include "hdf_log.h"
#include "hdmi_common.h"

#define HDF_LOG_TAG hdmi_common_c

/*
 * vic, pixel clk, vfreq, hactive, vactive, hblank, vblank, hfront, hsync, hback, vfront, vsync, vback, aspect,
 * timing, I/P
 */
struct HdmiVideoDefInfo g_ceaVideoDefInfoMap[HDMI_CEA_VIDEO_CODE_MAX] = {
    { 0,                              0,       0,      0,    0,    0,    0,   0,    0,   0,   0,  0,  0,
      HDMI_PICTURE_ASPECT_NO_DATA, HDMI_VIDEO_TIMING_NONE,         HDMI_VIDEO_FORMAT_NULL },
    { HDMI_VIC_640X480P60_4_3,        25175,   59940,  640,  480,  160,  45,  16,   96,  48,  10, 2,  33,
      HDMI_PICTURE_ASPECT_4_3,     HDMI_VIDEO_TIMING_640X480P60,   HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_720X480P60_4_3,        27000,   59940,  720,  480,  138,  45,  16,   62,  60,  9,  6,  30,
      HDMI_PICTURE_ASPECT_4_3,     HDMI_VIDEO_TIMING_720X480P60,   HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_720X480P60_16_9,       27000,   59940,  720,  480,  138,  45,  16,   62,  60,  9,  6,  30,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_720X480P60,   HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1280X720P60_16_9,      74250,   60000,  1280, 720,  370,  30,  110,  40,  220, 5,  5,  20,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1280X720P60,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1920X1080I60_16_9,     74250,   60000,  1920, 1080, 280,  22,  88,   44,  148, 2,  5,  15,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1920X1080I60, HDMI_VIDEO_FORMA_INTERLACE },
    { HDMI_VIC_1440X480I60_4_3,       27000,   59940,  1440, 480,  276,  22,  38,   124, 114, 4,  3,  15,
      HDMI_PICTURE_ASPECT_4_3,     HDMI_VIDEO_TIMING_1440X480I60,  HDMI_VIDEO_FORMA_INTERLACE },
    { HDMI_VIC_1440X480I60_16_9,      27000,   59940,  1440, 480,  276,  22,  38,   124, 114, 4,  3,  15,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1440X480I60,  HDMI_VIDEO_FORMA_INTERLACE },
    { HDMI_VIC_1440X240P60_4_3,       27000,   60054,  1440, 240,  276,  22,  38,   124, 114, 4,  3,  15,
      HDMI_PICTURE_ASPECT_4_3,     HDMI_VIDEO_TIMING_1440X240P60,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1440X240P60_16_9,      27000,   60054,  1440, 240,  276,  22,  38,   124, 114, 4,  3,  15,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1440X240P60,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_2880X480I60_4_3,       54000,   59940,  2880, 480,  552,  22,  76,   248, 228, 4,  3,  15,
      HDMI_PICTURE_ASPECT_4_3,     HDMI_VIDEO_TIMING_2880X480I60,  HDMI_VIDEO_FORMA_INTERLACE },
    { HDMI_VIC_2880X480I60_16_9,      54000,   59940,  2880, 480,  552,  22,  76,   248, 228, 4,  3,  15,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_2880X480I60,  HDMI_VIDEO_FORMA_INTERLACE },
    { HDMI_VIC_2880X240P60_4_3,       54000,   60054,  2880, 240,  552,  22,  76,   248, 228, 4,  3,  15,
      HDMI_PICTURE_ASPECT_4_3,     HDMI_VIDEO_TIMING_2880X240I60,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_2880X240P60_16_9,      54000,   60054,  2880, 240,  552,  23,  76,   248, 228, 4,  3,  15,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_2880X240I60,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1440X480P60_4_3,       54000,   59940,  1440, 480,  276,  45,  32,   124, 120, 9,  6,  30,
      HDMI_PICTURE_ASPECT_4_3,     HDMI_VIDEO_TIMING_1440X480P60,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1440X480P60_16_9,      54000,   59940,  1440, 480,  276,  45,  32,   124, 120, 9,  6,  30,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1440X480P60,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1920X1080P60_16_9,     148500,  60000,  1920, 1080, 280,  45,  88,   44,  148, 4,  5,  36,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1920X1080P60, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_720X576P50_4_3,        27000,   50000,  720,  576,  144,  49,  12,   64,  68,  5,  5,  39,
      HDMI_PICTURE_ASPECT_4_3,     HDMI_VIDEO_TIMING_720X576P50,   HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_720X576P50_16_9,       27000,   50000,  720,  576,  144,  49,  12,   64,  68,  5,  5,  39,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_720X576P50,   HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1280X720P50_16_9,      74250,   50000,  1280, 720,  700,  30,  440,  40,  220, 5,  5,  20,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1280X720P50,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1920X1080I50_16_9,     74250,   50000,  1920, 1080, 720,  24,  528,  44,  148, 2,  5,  15,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1920X1080I50, HDMI_VIDEO_FORMA_INTERLACE },
    { HDMI_VIC_1440X576I50_4_3,       27000,   50000,  1440, 576,  288,  24,  24,   126, 138, 2,  3,  19,
      HDMI_PICTURE_ASPECT_4_3,     HDMI_VIDEO_TIMING_1440X576I50,  HDMI_VIDEO_FORMA_INTERLACE },
    { HDMI_VIC_1440X576I50_16_9,      27000,   50000,  1440, 576,  288,  24,  24,   126, 138, 2,  3,  19,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1440X576I50,  HDMI_VIDEO_FORMA_INTERLACE },
    { HDMI_VIC_1440X576P50_4_3,       54000,   50000,  1440, 576,  288,  49,  24,   128, 136, 5,  5,  39,
      HDMI_PICTURE_ASPECT_4_3,     HDMI_VIDEO_TIMING_1440X576P50,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1440X576P50_16_9,      54000,   50000,  1440, 576,  288,  49,  24,   128, 136, 5,  5,  39,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1440X576P50,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1920X1080P50_16_9,     148500,  50000,  1920, 1080, 720,  45,  528,  44,  148, 4,  5,  36,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1920X1080P50, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1920X1080P24_16_9,     742500,  24000,  1920, 1080, 830,  45,  638,  44,  148, 4,  5,  36,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1920X1080P24, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1920X1080P25_16_9,     742500,  25000,  1920, 1080, 720,  45,  528,  44,  148, 4,  5,  36,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1920X1080P25, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_1920X1080P30_16_9,     742500,  30000,  1920, 1080, 280,  45,  88,   44,  148, 4,  5,  36,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_1920X1080P30, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_3840X2160P24_16_9,     297000,  24000,  3840, 2160, 1660, 90,  1276, 88,  296, 8,  10, 72,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_3840X2160P24, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_3840X2160P25_16_9,     297000,  25000,  3840, 2160, 1440, 90,  1056, 88,  296, 8,  10, 72,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_3840X2160P25, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_3840X2160P30_16_9,     297000,  30000,  3840, 2160, 560,  90,  176,  88,  296, 8,  10, 72,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_3840X2160P30, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_3840X2160P50_16_9,     594000,  50000,  3840, 2160, 1440, 90,  1056, 88,  296, 8,  10, 72,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_3840X2160P50, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_3840X2160P60_16_9,     594000,  60000,  3840, 2160, 560,  90,  176,  88,  296, 8,  10, 72,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_3840X2160P60, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_4096X2160P24_256_135,  297000,  24000,  4096, 2160, 1404, 90,  1020, 88,  296, 8,  10, 72,
      HDMI_PICTURE_ASPECT_256_135, HDMI_VIDEO_TIMING_4096X2160P24, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_4096X2160P25_256_135,  297000,  25000,  4096, 2160, 1184, 90,  968,  88,  128, 8,  10, 72,
      HDMI_PICTURE_ASPECT_256_135, HDMI_VIDEO_TIMING_4096X2160P25, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_4096X2160P30_256_135,  297000,  30000,  4096, 2160, 304,  90,  88,   88,  128, 8,  10, 72,
      HDMI_PICTURE_ASPECT_256_135, HDMI_VIDEO_TIMING_4096X2160P30, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_4096X2160P50_256_135,  594000,  50000,  4096, 2160, 1184, 90,  968,  88,  128, 8,  10, 72,
      HDMI_PICTURE_ASPECT_256_135, HDMI_VIDEO_TIMING_4096X2160P50, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_4096X2160P60_256_135,  594000,  60000,  4096, 2160, 304,  90,  88,   88,  128, 8,  10, 72,
      HDMI_PICTURE_ASPECT_256_135, HDMI_VIDEO_TIMING_4096X2160P60, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_3840X2160P120_16_9,    1188000, 120000, 3840, 2160, 560,  90,  176,  88,  296, 8,  10, 72,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_3840X2160P120, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_7680X4320P24_16_9,     1188000, 24000,  7680, 4320, 3320, 180, 2552, 176, 592, 16, 20, 144,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_7680X4320P24, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_7680X4320P25_16_9,     1188000, 25000,  7680, 4320, 3120, 80,  2352, 176, 592, 16, 20, 44,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_7680X4320P25, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_7680X4320P30_16_9,     1188000, 30000,  7680, 4320, 1320, 80,  552,  176, 592, 16, 20, 44,
      HDMI_PICTURE_ASPECT_16_9,    HDMI_VIDEO_TIMING_7680X4320P30, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_VIC_4096X2160P120_256_135, 1188000, 120000, 4096, 2160, 304,  90,  88,   88,  128, 8,  10, 72,
      HDMI_PICTURE_ASPECT_256_135, HDMI_VIDEO_TIMING_4096X2160P120, HDMI_VIDEO_FORMAT_PROGRESSIVE }
};

struct HdmiVideoDefInfo g_vesaVideoDefInfoMap[HDMI_VESA_VIDEO_CODE_MAX] = {
    { 0, 0,      0,     0,    0,    0,   0,   0,   0,   0,   0, 0, 0,  HDMI_PICTURE_ASPECT_NO_DATA,
        HDMI_VIDEO_TIMING_NONE,               HDMI_VIDEO_FORMAT_NULL },
    { 0, 40000,  60317, 800,  600,  256, 28,  40,  128, 88,  1, 4, 23, HDMI_PICTURE_ASPECT_16_9,
        HDMI_VIDEO_TIMING_VESA_800X600_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 33750,  60000, 848,  480,  240, 37,  16,  112, 112, 6, 8, 23, HDMI_PICTURE_ASPECT_16_9,
        HDMI_VIDEO_TIMING_VESA_848X480_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 65000,  60004, 1024, 768,  320, 38,  24,  136, 160, 3, 6, 29, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1024X768_60,     HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 74250,  60000, 1280, 720,  370, 30,  110, 40,  220, 5, 5, 20, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1280X720_60,     HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 68250,  59995, 1280, 768,  160, 22,  48,  32,  80,  3, 7, 12, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1280X768_60_RB,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 79500,  59870, 1280, 768,  384, 30,  64,  128, 192, 3, 7, 20, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1280X768_60,     HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 71001,  59910, 1280, 800,  160, 23,  48,  32,  80,  3, 6, 14, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1280X800_60_RB,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 83500,  59810, 1280, 800,  400, 31,  72,  128, 200, 3, 6, 22, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1280X800_60,     HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 108000, 60000, 1280, 960,  520, 40,  96,  112, 312, 1, 3, 36, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1280X960_60,     HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 108000, 60020, 1280, 1024, 408, 42,  48,  112, 248, 1, 3, 38, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1280X1024_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 85500,  60015, 1360, 768,  432, 27,  64,  112, 256, 3, 6, 18, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1360X768_60,     HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 85501,  59790, 1366, 768,  426, 30,  70,  143, 213, 3, 3, 24, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1366X768_60,     HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 121749, 59978, 1400, 1050, 464, 39,  88,  144, 232, 3, 4, 32, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1400X1050_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 88749,  59901, 1440, 900,  160, 26,  48,  32,  80,  3, 6, 17, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1440X900_60_RB,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 106499, 59887, 1440, 900,  464, 34,  80,  152, 232, 3, 6, 25, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1440X900_60,     HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 108000, 60000, 1440, 1050, 144, 49,  12,  64,  68,  3, 6, 25, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1440X1050_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 108000, 60000, 1440, 1050, 144, 49,  12,  64,  68,  3, 6, 25, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1440X1050_60_RB, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 108000, 60000, 1600, 900,  200, 100, 24,  80,  96,  1, 3, 96, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1600X900_60_RB,  HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 162000, 60000, 1600, 1200, 560, 50,  64,  192, 304, 1, 3, 46, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1600X1200_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 118999, 59883, 1680, 1050, 160, 30,  48,  32,  80,  3, 6, 21, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1680X1050_60_RB, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 146249, 59954, 1680, 1050, 560, 39,  104, 176, 280, 3, 6, 30, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1680X1050_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 204751, 60000, 1792, 1344, 656, 50,  128, 200, 328, 1, 3, 46, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1792X1344_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 218249, 59995, 1856, 1392, 672, 47,  96,  224, 352, 1, 3, 43, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1856X1392_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 148500, 60000, 1920, 1080, 280, 45,  88,  44,  148, 4, 5, 36, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1920X1080_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 154000, 59950, 1920, 1200, 160, 35,  48,  32,  80,  3, 6, 26, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1920X1200_60_RB, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 193251, 59885, 1920, 1200, 672, 45,  136, 200, 336, 3, 6, 36, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1920X1200_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 234000, 60000, 1920, 1440, 680, 60,  128, 208, 344, 1, 3, 56, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_1920X1440_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 162000, 60000, 2048, 1152, 202, 48,  26,  80,  96,  1, 3, 44, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_2048X1152_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 82500,  50000, 2560, 1440, 520, 30,  260, 40,  220, 3, 3, 24, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_2560X1440_60_RB, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { 0, 348502, 59987, 2560, 1600, 944, 58,  192, 280, 472, 3, 6, 49, HDMI_PICTURE_ASPECT_16_9,
      HDMI_VIDEO_TIMING_VESA_2560X1600_60,    HDMI_VIDEO_FORMAT_PROGRESSIVE },
};

struct HdmiVideo4kInfo g_video4kInfoMap[HDMI_VIDEO_4K_CODES_MAX] = {
    { HDMI_4K_VIC_3840X2160_30,     HDMI_VIC_3840X2160P30_16_9,     296703, 30, 3840, 2160,
      HDMI_PICTURE_ASPECT_16_9,     HDMI_VIDEO_TIMING_3840X2160P30, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_4K_VIC_3840X2160_25,     HDMI_VIC_3840X2160P25_16_9,     297000, 25, 3840, 2160,
      HDMI_PICTURE_ASPECT_16_9,     HDMI_VIDEO_TIMING_3840X2160P25, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_4K_VIC_3840X2160_24,     HDMI_VIC_3840X2160P24_16_9,     296703, 24, 3840, 2160,
      HDMI_PICTURE_ASPECT_16_9,     HDMI_VIDEO_TIMING_3840X2160P24, HDMI_VIDEO_FORMAT_PROGRESSIVE },
    { HDMI_4K_VIC_4096X2160_24,     HDMI_VIC_4096X2160P24_256_135,  297000, 24, 4096, 2160,
      HDMI_PICTURE_ASPECT_256_135,  HDMI_VIDEO_TIMING_4096X2160P24, HDMI_VIDEO_FORMAT_PROGRESSIVE }
};

enum HdmiVideoBitDepth HdmiCommonDeepClolorConvertToColorDepth(enum HdmiDeepColor deepColor)
{
    enum HdmiVideoBitDepth colorDepth;

    switch (deepColor) {
        case HDMI_DEEP_COLOR_24BITS:
            colorDepth = HDMI_VIDEO_BIT_DEPTH_8;
            break;
        case HDMI_DEEP_COLOR_30BITS:
            colorDepth = HDMI_VIDEO_BIT_DEPTH_10;
            break;
        case HDMI_DEEP_COLOR_36BITS:
            colorDepth = HDMI_VIDEO_BIT_DEPTH_12;
            break;
        case HDMI_DEEP_COLOR_48BITS:
            colorDepth = HDMI_VIDEO_BIT_DEPTH_16;
            break;
        default:
            HDF_LOGD("deep color %d is not support, use default value.", deepColor);
            colorDepth = HDMI_VIDEO_BIT_DEPTH_8;
            break;
    }
    return colorDepth;
}

enum HdmiDeepColor HdmiCommonColorDepthConvertToDeepClolor(enum HdmiVideoBitDepth colorDepth)
{
    enum HdmiDeepColor deepColor;

    switch (colorDepth) {
        case HDMI_VIDEO_BIT_DEPTH_8:
            deepColor = HDMI_DEEP_COLOR_24BITS;
            break;
        case HDMI_VIDEO_BIT_DEPTH_10:
            deepColor = HDMI_DEEP_COLOR_30BITS;
            break;
        case HDMI_VIDEO_BIT_DEPTH_12:
            deepColor = HDMI_DEEP_COLOR_36BITS;
            break;
        case HDMI_VIDEO_BIT_DEPTH_16:
            deepColor = HDMI_DEEP_COLOR_48BITS;
            break;
        case HDMI_VIDEO_BIT_DEPTH_OFF:
            deepColor = HDMI_DEEP_COLOR_OFF;
            break;
        default:
            deepColor = HDMI_DEEP_COLOR_BUTT;
            break;
    }
    return deepColor;
}

enum HdmiVic HdmiCommonGetVic(enum HdmiVideoTiming timing,
    enum HdmiPictureAspectRatio aspect, bool enable3d)
{
    uint32_t i, len;
    enum HdmiVic vic = 0;

    len = sizeof(g_ceaVideoDefInfoMap) / sizeof(g_ceaVideoDefInfoMap[0]);
    for (i = 0; i < len; i++) {
        if (timing == g_ceaVideoDefInfoMap[i].timing && aspect == g_ceaVideoDefInfoMap[i].aspect) {
            vic = g_ceaVideoDefInfoMap[i].vic;
            break;
        }
    }

    if (enable3d == true) {
        /* see hdmi spec 10.2. */
        if (vic == HDMI_VIC_3840X2160P24_16_9 || vic == HDMI_VIC_3840X2160P25_16_9 ||
            vic == HDMI_VIC_3840X2160P30_16_9 || vic == HDMI_VIC_4096X2160P24_256_135) {
            HDF_LOGI("4k x 2k 2D vic:%d.", vic);
            vic = HDMI_VIC_NONE;
        }
    }
    return vic;
}

static struct HdmiVideoDefInfo *HdmiCommonGetCommFormatInfo(enum HdmiVic vic)
{
    uint32_t i, len;

    len = sizeof(g_ceaVideoDefInfoMap) / sizeof(g_ceaVideoDefInfoMap[0]);
    for (i = 0; i < len; i++) {
        if (vic == g_ceaVideoDefInfoMap[i].vic) {
            return &g_ceaVideoDefInfoMap[i];
        }
    }
    return NULL;
}

static struct HdmiVideoDefInfo *HdmiCommonGetVesaFormatInfo(enum HdmiVideoTiming timing)
{
    uint32_t i, len;

    len = sizeof(g_vesaVideoDefInfoMap) / sizeof(g_vesaVideoDefInfoMap[0]);
    for (i = 0; i < len; i++) {
        if (timing == g_vesaVideoDefInfoMap[i].timing) {
            return &g_vesaVideoDefInfoMap[i];
        }
    }
    return NULL;
}

struct HdmiVideoDefInfo *HdmiCommonGetVideoDefInfo(enum HdmiVideoTiming timing,
    enum HdmiPictureAspectRatio aspect, bool enable3d)
{
    enum HdmiVic vic;
    struct HdmiVideoDefInfo *info = NULL;

    if (timing < HDMI_VIDEO_TIMING_VESA_DEFINE) {
        vic = HdmiCommonGetVic(timing, aspect, enable3d);
        info = HdmiCommonGetCommFormatInfo(vic);
    } else if (timing < HDMI_VIDEO_TIMING_USER_DEFINE) {
        info = HdmiCommonGetVesaFormatInfo(timing);
    }
    return info;
}

enum HdmiVideoTiming HdmiCommonGetVideoTiming(enum HdmiVic vic, enum HdmiPictureAspectRatio aspect)
{
    uint32_t i, len;
    enum HdmiVideoTiming timing = HDMI_VIDEO_TIMING_NONE;

    len = sizeof(g_ceaVideoDefInfoMap) / sizeof(g_ceaVideoDefInfoMap[0]);
    for (i = 0; i < len; i++) {
        if (vic == g_ceaVideoDefInfoMap[i].vic && aspect == g_ceaVideoDefInfoMap[i].aspect) {
            timing = g_ceaVideoDefInfoMap[i].timing;
            break;
        }
    }
    return timing;
}

struct HdmiVideo4kInfo *HdmiCommonGetVideo4kInfo(uint32_t _4kVic)
{
    uint32_t i, len;

    len = sizeof(g_video4kInfoMap) / sizeof(g_video4kInfoMap[0]);
    for (i = 0; i < len; i++) {
        if (_4kVic == g_video4kInfoMap[i]._4kVic) {
            return &g_video4kInfoMap[i];
        }
    }
    HDF_LOGD("4k not support vic = %u", _4kVic);
    return NULL;
}

enum HdmiVideoTiming HdmiCommonGetVideo4kTiming(uint32_t _4kVic)
{
    uint32_t i, len;
    enum HdmiVideoTiming timing = HDMI_VIDEO_TIMING_NONE;

    len = sizeof(g_video4kInfoMap) / sizeof(g_video4kInfoMap[0]);
    for (i = 0; i < len; i++) {
        if (_4kVic == g_video4kInfoMap[i]._4kVic) {
            timing = g_video4kInfoMap[i].timing;
            break;
        }
    }
    return timing;
}
