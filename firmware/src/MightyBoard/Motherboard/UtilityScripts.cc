/*
 * Copyright 2012 by Alison Leonard <alison@makerbot.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
 
 #include "Interface.hh"
 #include <util/delay.h>
 
 #include "UtilityScripts.hh"
 #include <avr/pgmspace.h>
 
 static uint16_t Lengths[7]  PROGMEM = { 798,  /// FilamentRight
							798, /// FilamentLeft
							75, /// Home Axes
							1458, /// Level Plate
							1911, /// Level Plate(Startup)
							859, /// FilamentSingle(Startup)
							1179};  /// FilamentDual(Startup)

static uint8_t FilamentRight[] PROGMEM = { 149,  0,  0,  0,  10,  73,  39,  109,  32,  104,  101,  97,  116,  105,  110,  103,  32,  117,  112,  32,  109,  121,  32,  32,  32,  0,  149,  1,  0,  0,  10,  101,  120,  116,  114,  117,  100,  101,  114,  32,  115,  111,  32,  119,  101,  32,  99,  97,  110,  32,  32,  0,  149,  1,  0,  0,  10,  112,  117,  108,  108,  32,  111,  117,  116,  32,  116,  104,  101,  32,  32,  32,  32,  32,  32,  32,  32,  0,  149,  3,  0,  0,  10,  102,  105,  108,  97,  109,  101,  110,  116,  46,  0,  137,  8,  153,  0,  0,  0,  0,  67,  104,  97,  110,  103,  101,  32,  70,  105,  108,  97,  109,  101,  110,  116,  0,  150,  0,  255,  136,  0,  3,  2,  225,  0,  134,  0,  135,  0,  100,  0,  255,  255,  149,  0,  0,  0,  0,  79,  75,  33,  32,  73,  39,  109,  32,  103,  111,  105,  110,  103,  32,  116,  111,  32,  114,  117,  110,  0,  149,  1,  0,  0,  0,  109,  121,  32,  101,  120,  116,  114,  117,  100,  101,  114,  32,  109,  111,  116,  111,  114,  32,  105,  110,  0,  149,  1,  0,  0,  0,  114,  101,  118,  101,  114,  115,  101,  32,  115,  111,  32,  116,  104,  101,  32,  32,  32,  32,  32,  32,  0,  149,  7,  0,  0,  0,  102,  105,  108,  97,  109,  101,  110,  116,  32,  105,  115,  32,  114,  101,  108,  101,  97,  115,  101,  100,  0,  137,  136,  149,  0,  0,  0,  90,  71,  114,  97,  115,  112,  32,  116,  104,  101,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  32,  0,  149,  1,  0,  0,  90,  110,  101,  97,  114,  32,  116,  104,  101,  32,  101,  120,  116,  114,  117,  100,  101,  114,  32,  32,  32,  0,  149,  3,  0,  0,  90,  105,  110,  112,  117,  116,  32,  97,  110,  100,  32,  112,  117,  108,  108,  46,  0,  136,  0,  10,  1,  3,  136,  0,  4,  1,  255,  142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  64,  56,  0,  0,  0,  0,  0,  0,  128,  74,  93,  5,  31,  149,  0,  0,  0,  0,  65,  119,  101,  115,  111,  109,  101,  33,  32,  85,  110,  109,  111,  117,  110,  116,  32,  116,  104,  101,  0,  149,  1,  0,  0,  0,  111,  108,  100,  32,  102,  105,  108,  97,  109,  101,  110,  116,  44,  32,  108,  111,  97,  100,  32,  32,  0,  149,  1,  0,  0,  0,  116,  104,  101,  32,  110,  101,  119,  32,  102,  105,  108,  97,  109,  101,  110,  116,  46,  32,  32,  32,  0,  149,  7,  0,  0,  0,  80,  114,  101,  115,  115,  32,  77,  32,  116,  111,  32,  99,  111,  110,  116,  105,  110,  117,  101,  46,  0,  137,  136,  149,  0,  0,  0,  0,  79,  75,  33,  32,  73,  39,  109,  32,  103,  111,  105,  110,  103,  32,  116,  111,  32,  114,  117,  110,  0,  149,  1,  0,  0,  0,  109,  121,  32,  101,  120,  116,  114,  117,  100,  101,  114,  32,  109,  111,  116,  111,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  115,  111,  32,  116,  104,  101,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  119,  105,  108,  108,  0,  149,  7,  0,  0,  0,  112,  117,  108,  108,  32,  116,  104,  114,  111,  117,  103,  104,  46,  0,  149,  0,  0,  0,  120,  80,  117,  115,  104,  32,  116,  104,  101,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  105,  110,  0,  149,  1,  0,  0,  120,  116,  104,  114,  111,  117,  103,  104,  32,  116,  104,  101,  32,  103,  114,  101,  121,  32,  32,  32,  32,  0,  149,  1,  0,  0,  120,  114,  105,  110,  103,  32,  117,  110,  116,  105,  108,  32,  116,  104,  101,  32,  109,  111,  116,  111,  114,  0,  149,  3,  0,  0,  120,  116,  117,  103,  115,  32,  105,  116,  32,  105,  110,  46,  0,  142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  181,  255,  255,  0,  0,  0,  0,  0,  14,  39,  7,  31,  137,  8,  136,  0,  3,  2,  0,  0,  149,  0,  0,  0,  0,  73,  39,  109,  32,  100,  111,  110,  101,  32,  108,  111,  97,  100,  105,  110,  103,  32,  109,  121,  32,  0,  149,  1,  0,  0,  0,  102,  105,  108,  97,  109,  101,  110,  116,  33,  32,  73,  102,  32,  112,  108,  97,  115,  116,  105,  99,  0,  149,  1,  0,  0,  0,  105,  115,  110,  39,  116,  32,  108,  111,  97,  100,  101,  100,  32,  103,  111,  32,  116,  111,  32,  32,  0,  149,  7,  0,  0,  0,  109,  97,  107,  101,  114,  98,  111,  116,  46,  99,  111,  109,  47,  104,  101,  108,  112,  0,  150,  100,  255,  154,  0,  136,  0,  10,  1,  2,  136,  0,  4,  1,  255,  137,  31 };
static uint8_t HomeAxes[] PROGMEM = { 131,  4,  136,  0,  0,  0,  20,  0,  140,  0,  0,  0,  0,  0,  0,  0,  0, 48,  248,  255,  255,  0,  0,  0,  0,  0,  0,  0,  0,  142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  87,  41,  4,  0,  24,  131,  4,  220,  5,  0,  0,  20,  0,  132,  3,  105,  1,  0,  0,  20,  0,  144,  31,  137,  31 };
static uint8_t LevelPlateStartup[] PROGMEM = { 149,  0,  0,  0,  0,  70,  105,  110,  100,  32,  116,  104,  101,  32,  52,  32,  107,  110,  111,  98,  115,  32,  111,  110,  32,  0,  149,  1,  0,  0,  0,  116,  104,  101,  32,  98,  111,  116,  116,  111,  110,  32,  111,  102,  32,  116,  104,  101,  32,  32,  32,  0,  149,  1,  0,  0,  0,  112,  108,  97,  116,  102,  111,  114,  109,  32,  97,  110,  100,  32,  116,  117,  114,  110,  32,  116,  111,  0,  149,  7,  0,  0,  0,  116,  105,  103,  104,  116,  101,  110,  32,  99,  111,  109,  112,  108,  101,  116,  101,  108,  121,  46,  0,  149,  0,  0,  0,  0,  73,  39,  109,  32,  103,  111,  105,  110,  103,  32,  116,  111,  32,  109,  111,  118,  101,  32,  32,  32,  0,  149,  1,  0,  0,  0,  116,  104,  101,  32,  101,  120,  116,  114,  117,  100,  101,  114,  32,  116,  111,  32,  32,  32,  32,  32,  0,  149,  1,  0,  0,  0,  118,  97,  114,  105,  111,  117,  115,  32,  112,  111,  115,  105,  116,  105,  111,  110,  115,  32,  32,  32,  0,  149,  7,  0,  0,  0,  102,  111,  114,  32,  97,  100,  106,  117,  115,  116,  109,  101,  110,  116,  46,  0,  149,  0,  0,  0,  0,  73,  110,  32,  101,  97,  99,  104,  32,  112,  111,  115,  105,  116,  105,  111,  110,  44,  32,  32,  32,  0,  149,  1,  0,  0,  0,  119,  101,  32,  119,  105,  108,  108,  32,  110,  101,  101,  100,  32,  116,  111,  32,  32,  32,  32,  32,  0,  149,  1,  0,  0,  0,  97,  100,  106,  117,  115,  116,  32,  50,  32,  107,  110,  111,  98,  115,  32,  97,  116,  32,  32,  32,  0,  149,  7,  0,  0,  0,  116,  104,  101,  32,  115,  97,  109,  101,  32,  116,  105,  109,  101,  46,  0,  149,  0,  0,  0,  0,  78,  111,  122,  122,  108,  101,  115,  32,  97,  114,  101,  32,  97,  116,  32,  116,  104,  101,  32,  32,  0,  149,  1,  0,  0,  0,  114,  105,  103,  104,  116,  32,  104,  101,  105,  103,  104,  116,  32,  119,  104,  101,  110,  32,  32,  32,  0,  149,  1,  0,  0,  0,  121,  111,  117,  32,  99,  97,  110,  32,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  32,  97,  0,  149,  7,  0,  0,  0,  115,  104,  101,  101,  116,  32,  111,  102,  32,  112,  97,  112,  101,  114,  0,  149,  0,  0,  0,  0,  98,  101,  116,  119,  101,  101,  110,  32,  116,  104,  101,  32,  110,  111,  122,  122,  108,  101,  32,  32,  0,  149,  1,  0,  0,  0,  97,  110,  100,  32,  116,  104,  101,  32,  112,  108,  97,  116,  102,  111,  114,  109,  46,  32,  32,  32,  0,  149,  1,  0,  0,  0,  71,  114,  97,  98,  32,  97,  32,  115,  104,  101,  101,  116,  32,  111,  102,  32,  32,  32,  32,  32,  0,  149,  7,  0,  0,  0,  112,  97,  112,  101,  114,  32,  116,  111,  32,  97,  115,  115,  105,  115,  116,  32,  117,  115,  46,  0,  131,  4,  136,  0,  0,  0,  20,  0,  140,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  0,  0,  0,  0,  0,  0,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  132,  3,  105,  1,  0,  0,  20,  0,  140,  165,  49,  0,  0,  148,  27,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  0,  0,  0,  0,  0,  0,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  29,  71,  28,  0,  24,  142,  0,  0,  0,  0,  202,  228,  255,  255,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  192,  140,  13,  0,  24,  142,  0,  0,  0,  0,  201,  228,  255,  255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  116,  104,  101,  32,  102,  114,  111,  110,  116,  32,  116,  119,  111,  0,  149,  1,  0,  0,  0,  107,  110,  111,  98,  115,  32,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  0,  0,  0,  0,  202,  228,  255,  255,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  142,  239,  34,  0,  0,  202,  228,  255,  255,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  32,  101,  17,  0,  24,  142,  239,  34,  0,  0,  201,  228,  255,  255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  116,  104,  101,  32,  114,  105,  103,  104,  116,  32,  116,  119,  111,  0,  149,  1,  0,  0,  0,  107,  110,  111,  98,  115,  32,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  240,  34,  0,  0,  202,  228,  255,  255,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  142,  246,  219,  255,  255,  202,  228,  255,  255,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  224,  86,  35,  0,  24,  142,  246,  219,  255,  255,  201,  228,  255,  255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  116,  104,  101,  32,  108,  101,  102,  116,  32,  116,  119,  111,  32,  0,  149,  1,  0,  0,  0,  107,  110,  111,  98,  115,  32,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  247,  219,  255,  255,  202,  228,  255,  255,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  142,  0,  0,  0,  0,  122,  26,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  138,  50,  32,  0,  24,  142,  0,  0,  0,  0,  122,  26,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  116,  104,  101,  32,  98,  97,  99,  107,  32,  116,  119,  111,  32,  0,  149,  1,  0,  0,  0,  107,  110,  111,  98,  115,  32,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  0,  0,  0,  0,  122,  26,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  142,  239,  34,  0,  0,  122,  26,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  32,  101,  17,  0,  24,  142,  239,  34,  0,  0,  122,  26,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  116,  104,  101,  32,  114,  105,  103,  104,  116,  32,  116,  119,  111,  0,  149,  1,  0,  0,  0,  107,  110,  111,  98,  115,  32,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  239,  34,  0,  0,  122,  26,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  142,  85,  220,  255,  255,  122,  26,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  40,  35,  0,  24,  142,  84,  220,  255,  255,  122,  26,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  116,  104,  101,  32,  108,  101,  102,  116,  32,  116,  119,  111,  32,  0,  149,  1,  0,  0,  0,  107,  110,  111,  98,  115,  32,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  0,  142,  85,  220,  255,  255,  122,  26,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  142,  0,  0,  0,  0,  0,  0,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  145,  30,  22,  0,  24,  142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  80,  108,  97,  116,  101,  32,  99,  97,  108,  105,  98,  114,  97,  116,  105,  111,  110,  32,  32,  32,  0,  149,  7,  0,  0,  0,  99,  111,  109,  112,  108,  101,  116,  101,  33,  0,  137,  31 };
static uint8_t FilamentSingle[] PROGMEM = { 149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  0,  0,  0,  0,  0,  0,  0,  0,  96,  234,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  205,  11,  49,  0,  24,  136,  0,  3,  2,  225,  0,  149,  0,  0,  0,  0,  76,  101,  116,  39,  115,  32,  114,  101,  109,  111,  118,  101,  32,  116,  104,  101,  32,  32,  32,  32,  0,  149,  1,  0,  0,  0,  98,  108,  97,  99,  107,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  103,  117,  105,  100,  101,  0,  149,  1,  0,  0,  0,  116,  117,  98,  101,  32,  115,  111,  32,  116,  104,  97,  116,  32,  119,  101,  32,  99,  97,  110,  32,  0,  149,  7,  0,  0,  0,  102,  101,  101,  100,  32,  112,  108,  97,  115,  116,  105,  99,  32,  101,  97,  115,  105,  108,  121,  46,  0,  149,  0,  0,  0,  0,  80,  114,  101,  115,  115,  32,  100,  111,  119,  110,  32,  111,  110,  32,  116,  104,  101,  32,  32,  32,  0,  149,  1,  0,  0,  0,  103,  114,  101,  121,  32,  114,  105,  110,  103,  32,  111,  110,  32,  116,  111,  112,  32,  111,  102,  32,  0,  149,  1,  0,  0,  0,  116,  104,  101,  32,  101,  120,  116,  114,  117,  100,  101,  114,  32,  97,  110,  100,  32,  32,  32,  32,  0,  149,  7,  0,  0,  0,  112,  117,  108,  108,  32,  116,  104,  101,  32,  103,  117,  105,  100,  101,  32,  116,  117,  98,  101,  46,  0,  149,  0,  0,  0,  0,  78,  111,  119,  32,  102,  101,  101,  100,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  32,  32,  0,  149,  1,  0,  0,  0,  116,  104,  114,  111,  117,  103,  104,  32,  103,  117,  105,  100,  101,  32,  116,  117,  98,  101,  32,  32,  0,  149,  1,  0,  0,  0,  102,  114,  111,  109,  32,  116,  104,  101,  32,  98,  97,  99,  107,  32,  117,  110,  116,  105,  108,  32,  0,  149,  7,  0,  0,  0,  105,  116,  32,  112,  111,  112,  115,  32,  111,  117,  116,  32,  105,  110,  32,  102,  114,  111,  110,  116,  0,  149,  0,  0,  0,  0,  73,  39,  109,  32,  104,  101,  97,  116,  105,  110,  103,  32,  117,  112,  32,  109,  121,  32,  32,  32,  0,  149,  1,  0,  0,  0,  101,  120,  116,  114,  117,  100,  101,  114,  32,  115,  111,  32,  119,  101,  32,  99,  97,  110,  32,  32,  0,  149,  1,  0,  0,  0,  102,  101,  101,  100,  32,  116,  104,  101,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  32,  32,  0,  149,  7,  0,  0,  0,  116,  104,  114,  111,  117,  103,  104,  46,  0,  149,  0,  0,  0,  10,  84,  104,  105,  115,  32,  109,  105,  103,  104,  116,  32,  116,  97,  107,  101,  32,  97,  32,  32,  32,  0,  149,  1,  0,  0,  10,  102,  101,  119,  32,  109,  105,  110,  117,  116,  101,  115,  46,  32,  32,  32,  32,  32,  32,  32,  32,  0,  149,  1,  0,  0,  10,  65,  110,  100,  32,  119,  97,  116,  99,  104,  32,  111,  117,  116,  44,  32,  116,  104,  101,  32,  32,  0,  149,  3,  0,  0,  10,  110,  111,  122,  122,  108,  101,  32,  119,  105,  108,  108,  32,  103,  101,  116,  32,  72,  79,  84,  33,  0,  137,  8,  153,  0,  0,  0,  0,  67,  104,  97,  110,  103,  101,  32,  70,  105,  108,  97,  109,  101,  110,  116,  0,  150,  0,  255,  134,  0,  135,  0,  100,  0,  255,  255,  137,  136,  149,  0,  0,  0,  0,  79,  75,  32,  73,  39,  109,  32,  114,  101,  97,  100,  121,  33,  32,  80,  117,  115,  104,  32,  32,  0,  149,  1,  0,  0,  0,  102,  105,  108,  97,  109,  101,  110,  116,  32,  105,  110,  32,  116,  104,  114,  111,  117,  103,  104,  32,  0,  149,  1,  0,  0,  0,  116,  104,  101,  32,  103,  114,  101,  121,  32,  114,  105,  110,  103,  32,  117,  110,  116,  105,  108,  32,  0,  149,  3,  0,  0,  0,  116,  104,  101,  32,  109,  111,  116,  111,  114,  32,  116,  117,  103,  115,  32,  105,  116,  32,  105,  110,  0,  136,  0,  10,  1,  3,  136,  0,  4,  1,  255,  142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  128,  193,  255,  255,  0,  0,  0,  0,  0,  225,  245,  5,  31,  149,  0,  0,  0,  0,  73,  39,  109,  32,  100,  111,  110,  101,  32,  108,  111,  97,  100,  105,  110,  103,  32,  109,  121,  32,  0,  149,  1,  0,  0,  0,  102,  105,  108,  97,  109,  101,  110,  116,  33,  32,  73,  102,  32,  112,  108,  97,  115,  116,  105,  99,  0,  149,  1,  0,  0,  0,  105,  115,  110,  39,  116,  32,  108,  111,  97,  100,  101,  100,  32,  103,  111,  32,  116,  111,  32,  32,  0,  149,  7,  0,  0,  0,  109,  97,  107,  101,  114,  98,  111,  116,  46,  99,  111,  109,  47,  104,  101,  108,  112,  0,  137,  8,  136,  0,  3,  2,  0,  0,  150,  100,  255,  154,  0,  136,  0,  10,  1,  2,  136,  0,  4,  1,  255,  137,  31 };
static uint8_t FilamentLeft[] PROGMEM = { 149,  0,  0,  0,  10,  73,  39,  109,  32,  104,  101,  97,  116,  105,  110,  103,  32,  117,  112,  32,  109,  121,  32,  32,  32,  0,  149,  1,  0,  0,  10,  101,  120,  116,  114,  117,  100,  101,  114,  32,  115,  111,  32,  119,  101,  32,  99,  97,  110,  32,  32,  0,  149,  1,  0,  0,  10,  112,  117,  108,  108,  32,  111,  117,  116,  32,  116,  104,  101,  32,  32,  32,  32,  32,  32,  32,  32,  0,  149,  3,  0,  0,  10,  102,  105,  108,  97,  109,  101,  110,  116,  46,  0,  137,  16,  153,  0,  0,  0,  0,  67,  104,  97,  110,  103,  101,  32,  70,  105,  108,  97,  109,  101,  110,  116,  0,  150,  0,  255,  136,  1,  3,  2,  225,  0,  134,  1,  135,  1,  100,  0,  255,  255,  149,  0,  0,  0,  0,  79,  75,  33,  32,  73,  39,  109,  32,  103,  111,  105,  110,  103,  32,  116,  111,  32,  114,  117,  110,  0,  149,  1,  0,  0,  0,  109,  121,  32,  101,  120,  116,  114,  117,  100,  101,  114,  32,  109,  111,  116,  111,  114,  32,  105,  110,  0,  149,  1,  0,  0,  0,  114,  101,  118,  101,  114,  115,  101,  32,  115,  111,  32,  116,  104,  101,  32,  32,  32,  32,  32,  32,  0,  149,  7,  0,  0,  0,  102,  105,  108,  97,  109,  101,  110,  116,  32,  105,  115,  32,  114,  101,  108,  101,  97,  115,  101,  100,  0,  137,  144,  149,  0,  0,  0,  90,  71,  114,  97,  115,  112,  32,  116,  104,  101,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  32,  0,  149,  1,  0,  0,  90,  110,  101,  97,  114,  32,  116,  104,  101,  32,  101,  120,  116,  114,  117,  100,  101,  114,  32,  32,  32,  0,  149,  3,  0,  0,  90,  105,  110,  112,  117,  116,  32,  97,  110,  100,  32,  112,  117,  108,  108,  46,  0,  136,  1,  10,  1,  3,  136,  1,  4,  1,  255,  142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  64,  56,  0,  0,  128,  74,  93,  5,  31,  149,  0,  0,  0,  0,  65,  119,  101,  115,  111,  109,  101,  33,  32,  85,  110,  109,  111,  117,  110,  116,  32,  116,  104,  101,  0,  149,  1,  0,  0,  0,  111,  108,  100,  32,  102,  105,  108,  97,  109,  101,  110,  116,  44,  32,  108,  111,  97,  100,  32,  32,  0,  149,  1,  0,  0,  0,  116,  104,  101,  32,  110,  101,  119,  32,  102,  105,  108,  97,  109,  101,  110,  116,  46,  32,  32,  32,  0,  149,  7,  0,  0,  0,  80,  114,  101,  115,  115,  32,  77,  32,  116,  111,  32,  99,  111,  110,  116,  105,  110,  117,  101,  46,  0,  137,  144,  149,  0,  0,  0,  0,  79,  75,  33,  32,  73,  39,  109,  32,  103,  111,  105,  110,  103,  32,  116,  111,  32,  114,  117,  110,  0,  149,  1,  0,  0,  0,  109,  121,  32,  101,  120,  116,  114,  117,  100,  101,  114,  32,  109,  111,  116,  111,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  115,  111,  32,  116,  104,  101,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  119,  105,  108,  108,  0,  149,  7,  0,  0,  0,  112,  117,  108,  108,  32,  116,  104,  114,  111,  117,  103,  104,  46,  0,  149,  0,  0,  0,  120,  80,  117,  115,  104,  32,  116,  104,  101,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  105,  110,  0,  149,  1,  0,  0,  120,  116,  104,  114,  111,  117,  103,  104,  32,  116,  104,  101,  32,  103,  114,  101,  121,  32,  32,  32,  32,  0,  149,  1,  0,  0,  120,  114,  105,  110,  103,  32,  117,  110,  116,  105,  108,  32,  116,  104,  101,  32,  109,  111,  116,  111,  114,  0,  149,  3,  0,  0,  120,  116,  117,  103,  115,  32,  105,  116,  32,  105,  110,  46,  0,  142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  181,  255,  255,  0,  14,  39,  7,  31,  137,  16,  136,  1,  3,  2,  0,  0,  149,  0,  0,  0,  0,  73,  39,  109,  32,  100,  111,  110,  101,  32,  108,  111,  97,  100,  105,  110,  103,  32,  109,  121,  32,  0,  149,  1,  0,  0,  0,  102,  105,  108,  97,  109,  101,  110,  116,  33,  32,  73,  102,  32,  112,  108,  97,  115,  116,  105,  99,  0,  149,  1,  0,  0,  0,  105,  115,  110,  39,  116,  32,  108,  111,  97,  100,  101,  100,  32,  103,  111,  32,  116,  111,  32,  32,  0,  149,  7,  0,  0,  0,  109,  97,  107,  101,  114,  98,  111,  116,  46,  99,  111,  109,  47,  104,  101,  108,  112,  0,  150,  100,  255,  154,  0,  136,  1,  10,  1,  2,  136,  1,  4,  1,  255,  137,  31 };
static uint8_t FilamentDual[] PROGMEM = { 149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  0,  0,  0,  0,  0,  0,  0,  0,  96,  234,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  205,  11,  49,  0,  24,  136,  0,  3,  2,  225,  0,  136,  1,  3,  2,  225,  0,  149,  0,  0,  0,  0,  76,  101,  116,  39,  115,  32,  114,  101,  109,  111,  118,  101,  32,  116,  104,  101,  32,  32,  32,  32,  0,  149,  1,  0,  0,  0,  98,  108,  97,  99,  107,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  103,  117,  105,  100,  101,  0,  149,  1,  0,  0,  0,  116,  117,  98,  101,  115,  32,  115,  111,  32,  116,  104,  97,  116,  32,  119,  101,  32,  99,  97,  110,  0,  149,  7,  0,  0,  0,  102,  101,  101,  100,  32,  112,  108,  97,  115,  116,  105,  99,  32,  101,  97,  115,  105,  108,  121,  46,  0,  149,  0,  0,  0,  0,  80,  114,  101,  115,  115,  32,  100,  111,  119,  110,  32,  111,  110,  32,  116,  104,  101,  32,  32,  32,  0,  149,  1,  0,  0,  0,  103,  114,  101,  121,  32,  114,  105,  110,  103,  115,  32,  111,  110,  32,  116,  111,  112,  32,  111,  102,  0,  149,  1,  0,  0,  0,  116,  104,  101,  32,  101,  120,  116,  114,  117,  100,  101,  114,  115,  32,  97,  110,  100,  32,  32,  32,  0,  149,  7,  0,  0,  0,  112,  117,  108,  108,  32,  116,  104,  101,  32,  103,  117,  105,  100,  101,  32,  116,  117,  98,  101,  115,  0,  149,  0,  0,  0,  0,  78,  111,  119,  32,  102,  101,  101,  100,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  32,  32,  0,  149,  1,  0,  0,  0,  116,  104,  114,  111,  117,  103,  104,  32,  103,  117,  105,  100,  101,  32,  116,  117,  98,  101,  115,  32,  0,  149,  1,  0,  0,  0,  102,  114,  111,  109,  32,  116,  104,  101,  32,  98,  97,  99,  107,  32,  117,  110,  116,  105,  108,  32,  0,  149,  7,  0,  0,  0,  105,  116,  32,  112,  111,  112,  115,  32,  111,  117,  116,  32,  105,  110,  32,  102,  114,  111,  110,  116,  0,  149,  0,  0,  0,  0,  73,  39,  109,  32,  104,  101,  97,  116,  105,  110,  103,  32,  117,  112,  32,  109,  121,  32,  32,  32,  0,  149,  1,  0,  0,  0,  101,  120,  116,  114,  117,  100,  101,  114,  115,  32,  115,  111,  32,  119,  101,  32,  99,  97,  110,  32,  0,  149,  1,  0,  0,  0,  102,  101,  101,  100,  32,  116,  104,  101,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  32,  32,  0,  149,  7,  0,  0,  0,  116,  104,  114,  111,  117,  103,  104,  46,  0,  149,  0,  0,  0,  10,  84,  104,  105,  115,  32,  109,  105,  103,  104,  116,  32,  116,  97,  107,  101,  32,  97,  32,  32,  32,  0,  149,  1,  0,  0,  10,  102,  101,  119,  32,  109,  105,  110,  117,  116,  101,  115,  46,  32,  32,  32,  32,  32,  32,  32,  32,  0,  149,  1,  0,  0,  10,  65,  110,  100,  32,  119,  97,  116,  99,  104,  32,  111,  117,  116,  44,  32,  116,  104,  101,  32,  32,  0,  149,  3,  0,  0,  10,  110,  111,  122,  122,  108,  101,  115,  32,  119,  105,  108,  108,  32,  103,  101,  116,  32,  72,  79,  84,  0,  137,  8,  153,  0,  0,  0,  0,  67,  104,  97,  110,  103,  101,  32,  70,  105,  108,  97,  109,  101,  110,  116,  0,  150,  0,  255,  134,  0,  135,  0,  100,  0,  255,  255,  149,  0,  0,  0,  0,  79,  75,  32,  73,  39,  109,  32,  114,  101,  97,  100,  121,  33,  32,  32,  32,  32,  32,  32,  32,  0,  149,  1,  0,  0,  0,  87,  101,  39,  108,  108,  32,  102,  101,  101,  100,  32,  116,  104,  101,  32,  114,  105,  103,  104,  116,  0,  149,  7,  0,  0,  0,  102,  105,  108,  97,  109,  101,  110,  116,  32,  102,  105,  114,  115,  116,  46,  0,  137,  136,  149,  0,  0,  0,  0,  80,  117,  115,  104,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  105,  110,  32,  32,  32,  32,  0,  149,  1,  0,  0,  0,  116,  104,  114,  111,  117,  103,  104,  32,  116,  104,  101,  32,  114,  105,  103,  104,  116,  32,  32,  32,  0,  149,  1,  0,  0,  0,  103,  114,  101,  121,  32,  114,  105,  110,  103,  32,  117,  110,  116,  105,  108,  32,  116,  104,  101,  32,  0,  149,  3,  0,  0,  0,  109,  111,  116,  111,  114,  32,  116,  117,  103,  115,  32,  105,  116,  32,  105,  110,  46,  0,  136,  0,  10,  1,  3,  136,  0,  4,  1,  255,  142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  128,  193,  255,  255,  0,  0,  0,  0,  0,  225,  245,  5,  31,  137,  8,  149,  0,  0,  0,  0,  78,  111,  119,  32,  119,  101,  39,  108,  108,  32,  102,  101,  101,  100,  32,  32,  32,  32,  32,  32,  0,  149,  1,  0,  0,  0,  102,  105,  108,  97,  109,  101,  110,  116,  32,  102,  111,  114,  32,  109,  121,  32,  108,  101,  102,  116,  0,  149,  7,  0,  0,  0,  101,  120,  116,  114,  117,  100,  101,  114,  0,  137,  144,  149,  0,  0,  0,  0,  80,  117,  115,  104,  32,  102,  105,  108,  97,  109,  101,  110,  116,  32,  105,  110,  32,  32,  32,  32,  0,  149,  1,  0,  0,  0,  116,  104,  114,  111,  117,  103,  104,  32,  116,  104,  101,  32,  108,  101,  102,  116,  32,  32,  32,  32,  0,  149,  1,  0,  0,  0,  103,  114,  101,  121,  32,  114,  105,  110,  103,  32,  117,  110,  116,  105,  108,  32,  116,  104,  101,  32,  0,  149,  3,  0,  0,  0,  109,  111,  116,  111,  114,  32,  116,  117,  103,  115,  32,  105,  116,  32,  105,  110,  46,  0,  142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  128,  193,  255,  255,  0,  225,  245,  5,  31,  149,  0,  0,  0,  0,  76,  111,  97,  100,  32,  112,  108,  97,  115,  116,  105,  99,  32,  115,  99,  114,  105,  112,  116,  32,  0,  149,  3,  0,  0,  0,  99,  111,  109,  112,  108,  101,  116,  101,  33,  0,  137,  16,  136,  1,  3,  2,  0,  0,  136,  0,  3,  2,  0,  0,  149,  0,  0,  0,  0,  73,  39,  109,  32,  100,  111,  110,  101,  32,  108,  111,  97,  100,  105,  110,  103,  32,  109,  121,  32,  0,  149,  1,  0,  0,  0,  102,  105,  108,  97,  109,  101,  110,  116,  33,  32,  73,  102,  32,  112,  108,  97,  115,  116,  105,  99,  0,  149,  1,  0,  0,  0,  105,  115,  110,  39,  116,  32,  108,  111,  97,  100,  101,  100,  32,  103,  111,  32,  116,  111,  32,  32,  0,  149,  7,  0,  0,  0,  109,  97,  107,  101,  114,  98,  111,  116,  46,  99,  111,  109,  47,  104,  101,  108,  112,  0,  150,  100,  255,  154,  0,  136,  0,  10,  1,  2,  136,  0,  4,  1,  255,  137,  31 };

 namespace utility {
	 
	 volatile bool is_playing;
	 int build_index = 0;
	 int build_length = 0;
	 uint8_t * buildFile;
	  
 /// returns true if script is running
 bool isPlaying(){
	 return is_playing;		
 }
 void reset(){
	 int build_index = 0;
	 int build_length = 0;
	 is_playing = false;
 
 }
 
 /// returns true if more bytes are available in the script
 bool playbackHasNext(){
	return (build_index < build_length);
 }
 
 /// gets next byte in script
 uint8_t playbackNext(){
	 
	 uint8_t byte;
	 
	 if(build_index < build_length)
	 {
		 byte = pgm_read_byte(buildFile + build_index++);
		return byte;
	}

	else 
		return 0;
 }
 
 /// begin buffer playback
 bool startPlayback(uint8_t build){

	switch (build){
		case FILAMENT_RIGHT:
			buildFile = FilamentRight;
			break;
		case FILAMENT_LEFT:
			buildFile = FilamentLeft;
			break;
		case HOME_AXES:
			buildFile = HomeAxes;		
			break;
		//case LEVEL_PLATE:
	//		buildFile = LevelPlate;
	//		break;
		case LEVEL_PLATE_STARTUP:
			buildFile = LevelPlateStartup;
			break;
		case FILAMENT_STARTUP_SINGLE:
			buildFile = FilamentSingle;
			break;
		case FILAMENT_STARTUP_DUAL:
			buildFile = FilamentDual;
			break;
		default:
			return false;
	}
	
	build_length = pgm_read_word(Lengths + build);
	is_playing = true;
	 build_index = 0;
	 return is_playing;
 }
 
 /// updates state to finished playback
 void finishPlayback(){
 
	is_playing = false;
 }

};

