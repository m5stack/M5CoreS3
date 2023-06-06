/*******************************************************************************
 * Size: 8 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef UBUNTU_MONO_8
#define UBUNTU_MONO_8 1
#endif

#if UBUNTU_MONO_8

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x65, 0x65, 0x54, 0x21, 0x66,

    /* U+0022 "\"" */
    0x99, 0x77, 0x0,

    /* U+0023 "#" */
    0x9, 0x36, 0x6d, 0xc7, 0x18, 0x90, 0x8b, 0xd7,
    0x62, 0x90,

    /* U+0024 "$" */
    0x4, 0x40, 0x1a, 0xa2, 0x65, 0x0, 0x1a, 0x90,
    0x0, 0x48, 0x59, 0xa4, 0x4, 0x40,

    /* U+0025 "%" */
    0x77, 0x17, 0x78, 0x80, 0x5a, 0xa5, 0x8, 0x78,
    0x71, 0x77,

    /* U+0026 "&" */
    0x2a, 0x90, 0x55, 0x90, 0x2e, 0x34, 0xa1, 0xc4,
    0x68, 0x97,

    /* U+0027 "'" */
    0x55, 0x44, 0x0,

    /* U+0028 "(" */
    0x0, 0x80, 0x7, 0x40, 0xa, 0x0, 0x9, 0x0,
    0xa, 0x0, 0xa, 0x0, 0x2, 0xa0, 0x0, 0x20,

    /* U+0029 ")" */
    0x8, 0x0, 0x4, 0x70, 0x0, 0xa0, 0x0, 0x90,
    0x0, 0xa0, 0x0, 0xa0, 0xa, 0x20, 0x2, 0x0,

    /* U+002A "*" */
    0x1, 0x10, 0x26, 0x62, 0x2b, 0xb2, 0x7, 0x70,

    /* U+002B "+" */
    0x4, 0x40, 0x5b, 0xb6, 0x4, 0x40, 0x3, 0x30,

    /* U+002C "," */
    0x4a, 0x48, 0x30,

    /* U+002D "-" */
    0x99,

    /* U+002E "." */
    0x11, 0x77,

    /* U+002F "/" */
    0x0, 0x64, 0x0, 0xa0, 0x0, 0xa0, 0x5, 0x50,
    0xa, 0x0, 0xa, 0x0, 0x46, 0x0,

    /* U+0030 "0" */
    0x1a, 0xa1, 0x72, 0x27, 0x96, 0x69, 0x73, 0x37,
    0x1b, 0xb1,

    /* U+0031 "1" */
    0x7, 0x80, 0x24, 0x90, 0x1, 0x90, 0x1, 0x90,
    0x1a, 0xd4,

    /* U+0032 "2" */
    0x49, 0xb1, 0x0, 0x64, 0x1, 0xa0, 0xa, 0x10,
    0x6b, 0x95,

    /* U+0033 "3" */
    0x39, 0xb1, 0x0, 0x63, 0x6, 0xc1, 0x0, 0x37,
    0x49, 0xa3,

    /* U+0034 "4" */
    0x1, 0xd2, 0x9, 0x92, 0x44, 0x82, 0x89, 0xc7,
    0x0, 0x82,

    /* U+0035 "5" */
    0xd, 0x93, 0x18, 0x0, 0x17, 0xa2, 0x0, 0x37,
    0x49, 0xa2,

    /* U+0036 "6" */
    0x5, 0x82, 0x3b, 0x91, 0x71, 0x28, 0x73, 0x28,
    0x2b, 0xa2,

    /* U+0037 "7" */
    0x49, 0xb9, 0x0, 0x91, 0x2, 0x90, 0x7, 0x30,
    0xa, 0x0,

    /* U+0038 "8" */
    0x2a, 0xa2, 0x64, 0x46, 0x1c, 0xc1, 0x82, 0x28,
    0x4a, 0xa4,

    /* U+0039 "9" */
    0x3a, 0xa2, 0x82, 0x28, 0x29, 0xa8, 0x0, 0x84,
    0x3a, 0x70,

    /* U+003A ":" */
    0x77, 0x11, 0x11, 0x77,

    /* U+003B ";" */
    0x77, 0x11, 0x0, 0x78, 0x84, 0x0,

    /* U+003C "<" */
    0x0, 0x65, 0x5a, 0x40, 0x29, 0x81, 0x0, 0x13,

    /* U+003D "=" */
    0x59, 0x96, 0x0, 0x0, 0x59, 0x96,

    /* U+003E ">" */
    0x56, 0x0, 0x3, 0x96, 0x18, 0x93, 0x32, 0x0,

    /* U+003F "?" */
    0x19, 0xb1, 0x0, 0x82, 0x4, 0x60, 0x2, 0x0,
    0x9, 0x30,

    /* U+0040 "@" */
    0x9, 0x94, 0x65, 0x9a, 0xa7, 0x3a, 0xa7, 0x2a,
    0x83, 0x97, 0x38, 0x0, 0x6, 0x93,

    /* U+0041 "A" */
    0x8, 0x90, 0x9, 0xa0, 0x36, 0x63, 0x89, 0xa8,
    0xa0, 0xa,

    /* U+0042 "B" */
    0x8a, 0xb1, 0x91, 0x54, 0x99, 0xc1, 0x91, 0x28,
    0x89, 0xa3,

    /* U+0043 "C" */
    0xa, 0x95, 0x74, 0x0, 0x91, 0x0, 0x73, 0x0,
    0xa, 0x95,

    /* U+0044 "D" */
    0x8a, 0xa1, 0x91, 0x38, 0x91, 0xa, 0x91, 0x28,
    0x8a, 0x91,

    /* U+0045 "E" */
    0x4c, 0x94, 0x46, 0x0, 0x4c, 0x92, 0x46, 0x0,
    0x4c, 0x96,

    /* U+0046 "F" */
    0x4c, 0x95, 0x46, 0x0, 0x4b, 0x92, 0x46, 0x0,
    0x46, 0x0,

    /* U+0047 "G" */
    0xa, 0x95, 0x74, 0x0, 0x91, 0x4, 0x73, 0xa,
    0x1a, 0x98,

    /* U+0048 "H" */
    0xa0, 0xa, 0xa0, 0xa, 0xa9, 0x9a, 0xa0, 0xa,
    0xa0, 0xa,

    /* U+0049 "I" */
    0x2b, 0xb2, 0x5, 0x50, 0x5, 0x50, 0x5, 0x50,
    0x2b, 0xb2,

    /* U+004A "J" */
    0x9, 0xb5, 0x0, 0x45, 0x0, 0x45, 0x0, 0x55,
    0x49, 0xa1,

    /* U+004B "K" */
    0x72, 0x66, 0x76, 0x90, 0x7d, 0x20, 0x73, 0xb1,
    0x72, 0x2a,

    /* U+004C "L" */
    0x46, 0x0, 0x46, 0x0, 0x46, 0x0, 0x46, 0x0,
    0x4c, 0x96,

    /* U+004D "M" */
    0x66, 0x56, 0x87, 0x77, 0x86, 0x68, 0x90, 0x9,
    0xa0, 0xa,

    /* U+004E "N" */
    0x95, 0x9, 0x99, 0x19, 0x94, 0x69, 0x90, 0x99,
    0x90, 0x59,

    /* U+004F "O" */
    0x2a, 0xa2, 0x91, 0x9, 0xa0, 0xa, 0x90, 0x9,
    0x2a, 0xa2,

    /* U+0050 "P" */
    0x6a, 0xa4, 0x63, 0x19, 0x6a, 0x92, 0x63, 0x0,
    0x63, 0x0,

    /* U+0051 "Q" */
    0x2a, 0xa2, 0x91, 0x19, 0xa0, 0xa, 0xa0, 0xa,
    0x4a, 0xa4, 0x4, 0xa1, 0x0, 0x33,

    /* U+0052 "R" */
    0x8a, 0xa2, 0x91, 0x46, 0x99, 0xb0, 0x91, 0x91,
    0x91, 0x37,

    /* U+0053 "S" */
    0x2b, 0x92, 0x55, 0x0, 0x7, 0x81, 0x0, 0x37,
    0x49, 0xb3,

    /* U+0054 "T" */
    0x6b, 0xb6, 0x5, 0x50, 0x5, 0x50, 0x5, 0x50,
    0x5, 0x50,

    /* U+0055 "U" */
    0x90, 0x9, 0x90, 0x9, 0x90, 0x9, 0x91, 0x19,
    0x3a, 0xa3,

    /* U+0056 "V" */
    0xb0, 0xa, 0x82, 0x28, 0x36, 0x63, 0x9, 0x90,
    0x9, 0x80,

    /* U+0057 "W" */
    0xa0, 0x9, 0x90, 0x9, 0x97, 0x78, 0x87, 0x87,
    0x75, 0x66,

    /* U+0058 "X" */
    0x74, 0x47, 0xa, 0xa0, 0x9, 0x90, 0x19, 0x91,
    0x82, 0x28,

    /* U+0059 "Y" */
    0xa1, 0xa, 0x37, 0x73, 0x9, 0x90, 0x5, 0x50,
    0x5, 0x50,

    /* U+005A "Z" */
    0x49, 0xb8, 0x0, 0xa0, 0x6, 0x40, 0x1a, 0x0,
    0x7b, 0x96,

    /* U+005B "[" */
    0xc8, 0xa, 0x0, 0xa0, 0xa, 0x0, 0xa0, 0xa,
    0x0, 0xc8, 0x0,

    /* U+005C "\\" */
    0x46, 0x0, 0xa, 0x0, 0x9, 0x0, 0x5, 0x50,
    0x0, 0x90, 0x0, 0xa0, 0x0, 0x64,

    /* U+005D "]" */
    0x8, 0xc0, 0xa, 0x0, 0xa0, 0xa, 0x0, 0xa0,
    0xa, 0x8, 0xc0,

    /* U+005E "^" */
    0x8, 0x80, 0x28, 0x82, 0x61, 0x16,

    /* U+005F "_" */
    0x89, 0x98,

    /* U+0060 "`" */
    0x61, 0x4,

    /* U+0061 "a" */
    0x19, 0xa2, 0x19, 0xa7, 0x73, 0x37, 0x3b, 0xa6,

    /* U+0062 "b" */
    0x53, 0x0, 0x73, 0x0, 0x7b, 0xb3, 0x73, 0x19,
    0x73, 0x19, 0x5a, 0xa2,

    /* U+0063 "c" */
    0x1a, 0x94, 0x83, 0x0, 0x83, 0x0, 0x1a, 0x95,

    /* U+0064 "d" */
    0x0, 0x25, 0x0, 0x37, 0x3b, 0xb7, 0x91, 0x37,
    0x91, 0x37, 0x2a, 0xb5,

    /* U+0065 "e" */
    0x29, 0xa4, 0x99, 0x97, 0x92, 0x0, 0x2b, 0xa3,

    /* U+0066 "f" */
    0x5, 0xa7, 0xa, 0x0, 0x4d, 0x94, 0xa, 0x0,
    0xa, 0x0, 0xa, 0x0,

    /* U+0067 "g" */
    0x2a, 0xa5, 0x91, 0x37, 0x91, 0x37, 0x3b, 0xb6,
    0x39, 0xa2,

    /* U+0068 "h" */
    0x53, 0x0, 0x73, 0x0, 0x7b, 0xb2, 0x73, 0x46,
    0x73, 0x37, 0x73, 0x37,

    /* U+0069 "i" */
    0xb, 0x10, 0x0, 0x0, 0x5c, 0x20, 0x8, 0x20,
    0x7, 0x20, 0x3, 0xb5,

    /* U+006A "j" */
    0x0, 0xc0, 0x0, 0x0, 0x9, 0xd1, 0x0, 0x91,
    0x0, 0x91, 0x0, 0x91, 0x3a, 0xa0,

    /* U+006B "k" */
    0x53, 0x0, 0x73, 0x0, 0x73, 0x84, 0x7c, 0x40,
    0x78, 0x90, 0x73, 0x57,

    /* U+006C "l" */
    0x5c, 0x20, 0x8, 0x20, 0x8, 0x20, 0x8, 0x20,
    0x7, 0x20, 0x3, 0xb5,

    /* U+006D "m" */
    0x8a, 0xa7, 0x94, 0x49, 0x92, 0x29, 0x90, 0x9,

    /* U+006E "n" */
    0x5a, 0xb2, 0x73, 0x36, 0x73, 0x37, 0x73, 0x37,

    /* U+006F "o" */
    0x2a, 0xa2, 0x91, 0x19, 0x91, 0x19, 0x2a, 0xa2,

    /* U+0070 "p" */
    0x5b, 0xa2, 0x73, 0x19, 0x73, 0x19, 0x7b, 0xb3,
    0x73, 0x0,

    /* U+0071 "q" */
    0x2a, 0xa5, 0x91, 0x37, 0x91, 0x37, 0x2b, 0xb7,
    0x0, 0x37,

    /* U+0072 "r" */
    0x1b, 0x94, 0x28, 0x0, 0x28, 0x0, 0x28, 0x0,

    /* U+0073 "s" */
    0x2b, 0x92, 0x3a, 0x20, 0x1, 0x94, 0x49, 0xa3,

    /* U+0074 "t" */
    0x1, 0x0, 0xa, 0x0, 0x4d, 0x94, 0xa, 0x0,
    0xa, 0x0, 0x6, 0xa5,

    /* U+0075 "u" */
    0x73, 0x37, 0x73, 0x37, 0x64, 0x37, 0x2b, 0xa6,

    /* U+0076 "v" */
    0x91, 0x19, 0x46, 0x64, 0xa, 0xa0, 0x8, 0x70,

    /* U+0077 "w" */
    0x90, 0x9, 0x96, 0x69, 0x88, 0x88, 0x56, 0x75,

    /* U+0078 "x" */
    0x56, 0x65, 0x9, 0x90, 0xa, 0xa0, 0x73, 0x37,

    /* U+0079 "y" */
    0x74, 0x28, 0x18, 0x64, 0x9, 0xa0, 0x4, 0x80,
    0x6a, 0x10,

    /* U+007A "z" */
    0x29, 0xd4, 0x3, 0x90, 0xb, 0x0, 0x5c, 0x94,

    /* U+007B "{" */
    0x4, 0xa3, 0x7, 0x20, 0x8, 0x10, 0x3b, 0x0,
    0x8, 0x10, 0x7, 0x20, 0x4, 0xa3,

    /* U+007C "|" */
    0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45,

    /* U+007D "}" */
    0x3a, 0x40, 0x2, 0x70, 0x1, 0x80, 0x0, 0xb3,
    0x1, 0x80, 0x2, 0x70, 0x3a, 0x40,

    /* U+007E "~" */
    0x39, 0x15, 0x51, 0x94
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 64, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 64, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 64, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 8, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 32, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 64, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 55, .adv_w = 64, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 71, .adv_w = 64, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 87, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 95, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 64, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 106, .adv_w = 64, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 107, .adv_w = 64, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 123, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 64, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 64, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 233, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 64, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 247, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 265, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 279, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 429, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 453, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 64, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 554, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 568, .adv_w = 64, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 579, .adv_w = 64, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 585, .adv_w = 64, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 587, .adv_w = 64, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 589, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 609, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 617, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 629, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 637, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 649, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 659, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 671, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 683, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 697, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 709, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 729, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 737, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 745, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 755, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 765, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 781, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 793, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 801, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 809, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 817, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 835, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 843, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 857, .adv_w = 64, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 864, .adv_w = 64, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 878, .adv_w = 64, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t ubuntu_mono_8 = {
#else
lv_font_t ubuntu_mono_8 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 8,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UBUNTU_MONO_8*/

