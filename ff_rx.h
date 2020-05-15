// flipflip's u-blox positioning receiver control library
//
// Copyright (c) 2020 Philippe Kehl (flipflip at oinkzwurgl dot org),
// https://oinkzwurgl.org/hacking/ubloxcfg
//
// This program is free software: you can redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
// even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see <https://www.gnu.org/licenses/>.

#include <stdint.h>
#include <stdbool.h>

#include "ff_parser.h"

#ifndef __FF_RX_H__
#define __FF_RX_H__

/* ********************************************************************************************** */

typedef struct RX_s RX_t;

typedef struct RX_ARGS_s
{
    bool     autobaud;    // default: true
    bool     detect;      // default: true
    bool     verbose;     // default: true
    char    *name;        // default: automatic
} RX_ARGS_t;

#define RX_ARGS_DEFAULT() { .autobaud = true, .detect = true, .verbose = true, .name = NULL }

RX_t *rxOpen(const char *port, const RX_ARGS_t *args);
void rxClose(RX_t *rx);

PARSER_MSG_t *rxGetNextMessage(RX_t *rx);
PARSER_MSG_t *rxGetNextMessageTimeout(RX_t *rx, const uint32_t timeout);

bool rxSend(RX_t *rx, const uint8_t *data, const int size);

bool rxAutobaud(RX_t *rx);
int rxGetBaudrate(RX_t *rx);
bool rxSetBaudrate(RX_t *rx, const int baudrate);

/* ********************************************************************************************** */

bool rxGetVerStr(RX_t *rx, char *str, const int size);

typedef struct RX_POLL_UBX_s
{
    uint8_t        clsId;
    uint8_t        msgId;
    const uint8_t *payload;
    int            payloadSize;
    uint32_t       timeout;
    int            retries;
    int            respSizeMin;
} RX_POLL_UBX_t;

PARSER_MSG_t *rxPollUbx(RX_t *rx, const RX_POLL_UBX_t *param);

bool rxSendUbxCfg(RX_t *rx, const uint8_t *msg, const int size, const uint32_t timeout);

typedef enum RX_RESET_e
{
    RX_RESET_HOT,           // Hotstart (like u-center)
    RX_RESET_WARM,          // Warmstart (like u-center)
    RX_RESET_COLD,          // Coldstart (like u-center)
    RX_RESET_DEFAULT,       // Revert config to default, keep nav data
    RX_RESET_FACTORY,       // Revert config to default and coldstart
    RX_RESET_GNSS_STOP,     // Stop GNSS
    RX_RESET_GNSS_START,    // Start GNSS
    RX_RESET_GNSS_RESTART   // Restart GNSS
} RX_RESET_t;

bool rxReset(RX_t *rx, const RX_RESET_t reset);


/* ********************************************************************************************** */
#endif // __FF_RX_H__
