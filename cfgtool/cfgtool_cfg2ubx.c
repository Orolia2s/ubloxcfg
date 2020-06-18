// u-blox 9 positioning receivers configuration tool
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

#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>

#include "cfgtool_util.h"
#include "ff_ubx.h"

#include "cfgtool_cfg2rx.h"
#include "cfgtool_cfg2ubx.h"

/* ********************************************************************************************** */

const char *cfg2ubxHelp(void)
{
    return
// -----------------------------------------------------------------------------
"Commands 'cfg2ubx', 'cfg2hex' and 'cfg2c':\n"
"\n"
"    Usage: cfgtool cfg2ubx [-i <infile>] [-o <outfile>] [-y] -l <layer(s)>\n"
"           cfgtool cfg2hex [-i <infile>] [-o <outfile>] [-y] -l <layer(s)> [-x]\n"
"           cfgtool cfg2c [-i <infile>] [-o <outfile>] [-y] -l <layer(s)> [-x]\n"
"\n"
"    The cfg2ubx, cfg2hex and cfg2c modes convert a configuration file into one\n"
"    or more UBX-CFG-VALSET messages, output as binary UBX messages, u-center\n"
"    compatible hex dumps, or c code. Optional extra comments can be enabled\n"
"    using the -x flag.\n"
"    See the 'rx2cfg' command for the specification of the configuration file.\n"
"\n";
}

/* ********************************************************************************************** */

typedef enum FMT_e
{
    FMT_UBX, FMT_HEX, FMT_C
} FMT_t;

static int _cfg2fmt(const char *layerArg, const bool extraInfo, const FMT_t fmt);

int cfg2ubxRun(const char *layerArg, const bool extraInfo)
{
    return _cfg2fmt(layerArg, extraInfo, FMT_UBX);
}

int cfg2hexRun(const char *layerArg, const bool extraInfo)
{
    return _cfg2fmt(layerArg, extraInfo, FMT_HEX);
}

int cfg2cRun(const char *layerArg, const bool extraInfo)
{
    return _cfg2fmt(layerArg, extraInfo, FMT_C);
}

/* ********************************************************************************************** */

static int _cfg2fmt(const char *layerArg, const bool extraInfo, const FMT_t fmt)
{
    const uint8_t layers = ubxCfgValsetLayer(layerArg);
    if (layers == 0x00)
    {
        return EXIT_BADARGS;
    }

    PRINT("Loading configuration");
    int nKv = 0;
    UBLOXCFG_KEYVAL_t *kv = cfgToKeyVal(&nKv);
    if (kv == NULL)
    {
        return EXIT_OTHERFAIL;
    }

    PRINT("Converting %d items into UBX-CFG-VALSET messages", nKv);
    int nMsgs = 0;
    VALSET_MSG_t *msgs = keyValToUbxCfgValset(kv, nKv, layers, &nMsgs);
    if (msgs == NULL)
    {
        free(kv);
        return EXIT_OTHERFAIL;
    }

    char layersStr[100];
    if (fmt != FMT_UBX)
    {
        layersStr[0] = '\0';
        if ((layers & UBX_CFG_VALSET_V1_LAYER_RAM) != 0)
        {
            strcat(&layersStr[strlen(layersStr)], ",RAM");
        }
        if ((layers & UBX_CFG_VALSET_V1_LAYER_BBR) != 0)
        {
            strcat(&layersStr[strlen(layersStr)], ",BBR");
        }
        if ((layers & UBX_CFG_VALSET_V1_LAYER_FLASH) != 0)
        {
            strcat(&layersStr[strlen(layersStr)], ",FLASH");
        }
        switch (fmt)
        {
            case FMT_HEX:
                ioOutputStr("# cfg2hex");
                break;
            case FMT_C:
                ioOutputStr("// cfg2c");
                break;
            default:
                break;
        }
        ioOutputStr(" (%d items in %s)\n", nKv, &layersStr[1]);
    }

    int kvOffs = 0;
    for (int msgIx = 0; msgIx < nMsgs; msgIx++)
    {
        PRINT("Dumping UBX-CFG-VALSET %d/%d (%d items, %s)",
            msgIx + 1, nMsgs, msgs[msgIx].nKv, msgs[msgIx].info);

        if (fmt != FMT_UBX)
        {
            const char *comment1 = fmt == FMT_HEX ? "# - " : "// ";
            const char *comment2 = fmt == FMT_HEX ? "#   " : "// ";
            ioOutputStr("%sUBX-CFG-VALSET %d/%d (%d items, %d bytes, %s, %s)\n",
                comment1, msgIx + 1, nMsgs, msgs[msgIx].nKv, msgs[msgIx].size, msgs[msgIx].info, &layersStr[1]);
            if (extraInfo)
            {
                for (int n = 1; n <= nKv; n++)
                {
                    char str[UBLOXCFG_MAX_KEYVAL_STR_SIZE];
                    if (ubloxcfg_stringifyKeyVal(str, sizeof(str), &kv[kvOffs + n - 1]))
                    {
                        ioOutputStr("%s%2d. %s\n", comment2, n, str);
                    }
                }
            }
        }
        if (fmt == FMT_C)
        {
            ioOutputStr("const uint8_t ubxCfgValset%d[%d] =\n{\n", msgIx, msgs[msgIx].size);
        }
        switch (fmt)
        {
            case FMT_HEX:
                ioAddOutputHex(msgs[msgIx].msg, msgs[msgIx].size, 4);
                break;
            case FMT_C:
                ioAddOutputC(msgs[msgIx].msg, msgs[msgIx].size, 4, "    ");
                break;
            case FMT_UBX:
                ioAddOutputBin(msgs[msgIx].msg, msgs[msgIx].size);
                break;
            default:
                break;                
        }
        if (fmt == FMT_C)
        {
            ioOutputStr("};\n");
        }
    }
    if (fmt == FMT_C)
    {
        ioOutputStr("const struct { const int size; const uint8_t *data; } ubxCfgValsetMsgs[%d] =\n{\n", nMsgs);
        for (int ix = 0; ix < nMsgs; ix++)
        {
            ioOutputStr("    { .size = sizeof(ubxCfgValset%d), .data = ubxCfgValset%d }%s\n", 
                ix, ix, (ix + 1) < nMsgs ? "," : "");
        }
        ioOutputStr("};\n", nMsgs);
    }

    free(kv);
    return ioWriteOutput(false) ? EXIT_SUCCESS : EXIT_OTHERFAIL;
}

/* ********************************************************************************************** */
// eof