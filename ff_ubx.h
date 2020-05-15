// flipflip's UBX protocol stuff
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

#ifndef __FF_UBX_H__
#define __FF_UBX_H__

/* ********************************************************************************************** */

#define UBX_ACK_CLSID                0x05
#define UBX_ACK_ACK_MSGID            0x01
#define UBX_ACK_NAK_MSGID            0x00

#define UBX_CFG_CLSID                0x06
#define UBX_CFG_PWR_MSGID            0x57
#define UBX_CFG_RST_MSGID            0x04
#define UBX_CFG_CFG_MSGID            0x09
#define UBX_CFG_VALSET_MSGID         0x8a
#define UBX_CFG_VALGET_MSGID         0x8b
#define UBX_CFG_VALDEL_MSGID         0x8c

#define UBX_INF_CLSID                0x04
#define UBX_INF_ERROR_MSGID          0x00
#define UBX_INF_WARNING_MSGID        0x01
#define UBX_INF_NOTICE_MSGID         0x02
#define UBX_INF_TEST_MSGID           0x03
#define UBX_INF_DEBUG_MSGID          0x04

#define UBX_LOG_CLSID                0x21
#define UBX_LOG_CREATE_MSGID         0x07
#define UBX_LOG_ERASE_MSGID          0x03
#define UBX_LOG_FINDTIME_MSGID       0x0e
#define UBX_LOG_INFO_MSGID           0x08
#define UBX_LOG_RETRPOSX_MSGID       0x0f
#define UBX_LOG_RETRPOS_MSGID        0x0b
#define UBX_LOG_RETRSTR_MSGID        0x0d
#define UBX_LOG_RETR_MSGID           0x09
#define UBX_LOG_STR_MSGID            0x04

#define UBX_MGA_CLSID                0x13
#define UBX_MGA_ACK_MSGID            0x60
#define UBX_MGA_DBD_MSGID            0x80
#define UBX_MGA_INI_MSGID            0x40
#define UBX_MGA_GPS_MSGID            0x00
#define UBX_MGA_GAL_MSGID            0x02
#define UBX_MGA_BDS_MSGID            0x03
#define UBX_MGA_QZSS_MSGID           0x05
#define UBX_MGA_GLO_MSGID            0x06

#define UBX_MON_CLSID                0x0a
#define UBX_MON_GNSS_MSGID           0x28
#define UBX_MON_HW_MSGID             0x09
#define UBX_MON_HW2_MSGID            0x0b
#define UBX_MON_HW3_MSGID            0x37
#define UBX_MON_RF_MSGID             0x38
#define UBX_MON_IO_MSGID             0x02
#define UBX_MON_COMMS_MSGID          0x36
#define UBX_MON_MSGPP_MSGID          0x06
#define UBX_MON_PATH_MSGID           0x27
#define UBX_MON_RXR_MSGID            0x21
#define UBX_MON_RXBUF_MSGID          0x07
#define UBX_MON_TXBUF_MSGID          0x08
#define UBX_MON_VER_MSGID            0x04

#define UBX_NAV_CLSID                0x01
#define UBX_NAV_PVT_MSGID            0x07
#define UBX_NAV_SAT_MSGID            0x35
#define UBX_NAV_ORB_MSGID            0x34
#define UBX_NAV_STATUS_MSGID         0x03
#define UBX_NAV_SIG_MSGID            0x43
#define UBX_NAV_CLOCK_MSGID          0x22
#define UBX_NAV_DOP_MSGID            0x04
#define UBX_NAV_POSECEF_MSGID        0x01
#define UBX_NAV_HPPOSECEF_MSGID      0x13
#define UBX_NAV_POSLLH_MSGID         0x02
#define UBX_NAV_HPPOSLLH_MSGID       0x14
#define UBX_NAV_RELPOSNED_MSGID      0x3c
#define UBX_NAV_VELECEF_MSGID        0x11
#define UBX_NAV_VELNED_MSGID         0x12
#define UBX_NAV_SVIN_MSGID           0x3b
#define UBX_NAV_EOE_MSGID            0x61
#define UBX_NAV_GEOFENCE_MSGID       0x39
#define UBX_NAV_ODO_MSGID            0x09
#define UBX_NAV_RESETODO_MSGID       0x10
#define UBX_NAV_TIMEUTC_MSGID        0x21
#define UBX_NAV_TIMELS_MSGID         0x26
#define UBX_NAV_TIMEGPS_MSGID        0x20
#define UBX_NAV_TIMEGLO_MSGID        0x23
#define UBX_NAV_TIMEBDS_MSGID        0x24
#define UBX_NAV_TIMEGAL_MSGID        0x25

#define UBX_RXM_CLSID                0x02
#define UBX_RXM_MEASX_MSGID          0x14
#define UBX_RXM_RAWX_MSGID           0x15
#define UBX_RXM_SFRBX_MSGID          0x13
#define UBX_RXM_PMREQ_MSGID          0x41
#define UBX_RXM_RLM_MSGID            0x59
#define UBX_RXM_RTCM_MSGID           0x32

#define UBX_SEC_CLSID                0x27
#define UBX_SEC_UNIQUEID_MSGID       0x03

#define UBX_TIM_CLSID                0x0d
#define UBX_TIM_TM2_MSGID            0x03
#define UBX_TIM_TP_MSGID             0x01
#define UBX_TIM_VRFY_MSGID           0x06

#define UBX_UPD_CLSID                0x09
#define UBX_UPD_SOS_MSGID            0x14

#define UBX_CLASSES(_P_) \
    _P_(UBX_ACK_CLSID, "UBX-ACK") \
    _P_(UBX_CFG_CLSID, "UBX-ACK") \
    _P_(UBX_INF_CLSID, "UBX-INF") \
    _P_(UBX_LOG_CLSID, "UBX-LOG") \
    _P_(UBX_MGA_CLSID, "UBX-MGA") \
    _P_(UBX_MON_CLSID, "UBX-MON") \
    _P_(UBX_NAV_CLSID, "UBX-NAV") \
    _P_(UBX_RXM_CLSID, "UBX-RXM") \
    _P_(UBX_SEC_CLSID, "UBX-SEC") \
    _P_(UBX_TIM_CLSID, "UBX-TIM") \
    _P_(UBX_UPD_CLSID, "UBX-UPD")

#define UBX_MESSAGES(_P_) \
    _P_(UBX_ACK_CLSID, UBX_ACK_ACK_MSGID,         "UBX-ACK-ACK") \
    _P_(UBX_ACK_CLSID, UBX_ACK_NAK_MSGID,         "UBX-ACK-NAK") \
    _P_(UBX_CFG_CLSID, UBX_CFG_PWR_MSGID,         "UBX-CFG-PWR") \
    _P_(UBX_CFG_CLSID, UBX_CFG_RST_MSGID,         "UBX-CFG-RST") \
    _P_(UBX_CFG_CLSID, UBX_CFG_CFG_MSGID,         "UBX-CFG-CFG") \
    _P_(UBX_CFG_CLSID, UBX_CFG_VALSET_MSGID,      "UBX-CFG-VALSET") \
    _P_(UBX_CFG_CLSID, UBX_CFG_VALGET_MSGID,      "UBX-CFG-VALGET") \
    _P_(UBX_CFG_CLSID, UBX_CFG_VALDEL_MSGID,      "UBX-CFG-VALDEL") \
    _P_(UBX_INF_CLSID, UBX_INF_ERROR_MSGID,       "UBX-INF-ERROR") \
    _P_(UBX_INF_CLSID, UBX_INF_WARNING_MSGID,     "UBX-INF-WARNING") \
    _P_(UBX_INF_CLSID, UBX_INF_NOTICE_MSGID,      "UBX-INF-NOTICE") \
    _P_(UBX_INF_CLSID, UBX_INF_TEST_MSGID,        "UBX-INF-TEST") \
    _P_(UBX_INF_CLSID, UBX_INF_DEBUG_MSGID,       "UBX-INF-DEBUG") \
    _P_(UBX_LOG_CLSID, UBX_LOG_CREATE_MSGID,      "UBX-LOG-CREATE") \
    _P_(UBX_LOG_CLSID, UBX_LOG_ERASE_MSGID,       "UBX-LOG-ERASE") \
    _P_(UBX_LOG_CLSID, UBX_LOG_FINDTIME_MSGID,    "UBX-LOG-FINDTIME") \
    _P_(UBX_LOG_CLSID, UBX_LOG_INFO_MSGID,        "UBX-LOG-INFO") \
    _P_(UBX_LOG_CLSID, UBX_LOG_RETRPOSX_MSGID,    "UBX-LOG-RETRPOSX") \
    _P_(UBX_LOG_CLSID, UBX_LOG_RETRPOS_MSGID,     "UBX-LOG-RETRPOS") \
    _P_(UBX_LOG_CLSID, UBX_LOG_RETRSTR_MSGID,     "UBX-LOG-RETRSTR") \
    _P_(UBX_LOG_CLSID, UBX_LOG_RETR_MSGID,        "UBX-LOG-RETR") \
    _P_(UBX_LOG_CLSID, UBX_LOG_STR_MSGID,         "UBX-LOG-STR") \
    _P_(UBX_MGA_CLSID, UBX_MGA_ACK_MSGID,         "UBX-MGA-ACK") \
    _P_(UBX_MGA_CLSID, UBX_MGA_DBD_MSGID,         "UBX-MGA-DBD") \
    _P_(UBX_MGA_CLSID, UBX_MGA_INI_MSGID,         "UBX-MGA-INI") \
    _P_(UBX_MGA_CLSID, UBX_MGA_GPS_MSGID,         "UBX-MGA-GPS") \
    _P_(UBX_MGA_CLSID, UBX_MGA_GAL_MSGID,         "UBX-MGA-GAL") \
    _P_(UBX_MGA_CLSID, UBX_MGA_BDS_MSGID,         "UBX-MGA-BDS") \
    _P_(UBX_MGA_CLSID, UBX_MGA_QZSS_MSGID,        "UBX-MGA-QZSS") \
    _P_(UBX_MGA_CLSID, UBX_MGA_GLO_MSGID,         "UBX-MGA-GLO") \
    _P_(UBX_MON_CLSID, UBX_MON_GNSS_MSGID,        "UBX-MON-GNSS") \
    _P_(UBX_MON_CLSID, UBX_MON_HW_MSGID,          "UBX-MON-HW") \
    _P_(UBX_MON_CLSID, UBX_MON_HW2_MSGID,         "UBX-MON-HW2") \
    _P_(UBX_MON_CLSID, UBX_MON_HW3_MSGID,         "UBX-MON-HW3") \
    _P_(UBX_MON_CLSID, UBX_MON_RF_MSGID,          "UBX-MON-RF") \
    _P_(UBX_MON_CLSID, UBX_MON_IO_MSGID,          "UBX-MON-IO") \
    _P_(UBX_MON_CLSID, UBX_MON_COMMS_MSGID,       "UBX-MON-COMMS") \
    _P_(UBX_MON_CLSID, UBX_MON_MSGPP_MSGID,       "UBX-MON-MSGPP") \
    _P_(UBX_MON_CLSID, UBX_MON_PATH_MSGID,        "UBX-MON-PATH") \
    _P_(UBX_MON_CLSID, UBX_MON_RXR_MSGID,         "UBX-MON-RXR") \
    _P_(UBX_MON_CLSID, UBX_MON_RXBUF_MSGID,       "UBX-MON-RXBUF") \
    _P_(UBX_MON_CLSID, UBX_MON_TXBUF_MSGID,       "UBX-MON-TXBUF") \
    _P_(UBX_MON_CLSID, UBX_MON_VER_MSGID,         "UBX-MON-VER") \
    _P_(UBX_NAV_CLSID, UBX_NAV_PVT_MSGID,         "UBX-NAV-PVT") \
    _P_(UBX_NAV_CLSID, UBX_NAV_SAT_MSGID,         "UBX-NAV-SAT") \
    _P_(UBX_NAV_CLSID, UBX_NAV_ORB_MSGID,         "UBX-NAV-ORB") \
    _P_(UBX_NAV_CLSID, UBX_NAV_STATUS_MSGID,      "UBX-NAV-STATUS") \
    _P_(UBX_NAV_CLSID, UBX_NAV_SIG_MSGID,         "UBX-NAV-SIG") \
    _P_(UBX_NAV_CLSID, UBX_NAV_CLOCK_MSGID,       "UBX-NAV-CLOCK") \
    _P_(UBX_NAV_CLSID, UBX_NAV_DOP_MSGID,         "UBX-NAV-DOP") \
    _P_(UBX_NAV_CLSID, UBX_NAV_POSECEF_MSGID,     "UBX-NAV-POSECEF") \
    _P_(UBX_NAV_CLSID, UBX_NAV_HPPOSECEF_MSGID,   "UBX-NAV-HPPOSECEF") \
    _P_(UBX_NAV_CLSID, UBX_NAV_POSLLH_MSGID,      "UBX-NAV-POSLLH") \
    _P_(UBX_NAV_CLSID, UBX_NAV_HPPOSLLH_MSGID,    "UBX-NAV-HPPOSLLH") \
    _P_(UBX_NAV_CLSID, UBX_NAV_RELPOSNED_MSGID,   "UBX-NAV-RELPOSNED") \
    _P_(UBX_NAV_CLSID, UBX_NAV_VELECEF_MSGID,     "UBX-NAV-VELECEF") \
    _P_(UBX_NAV_CLSID, UBX_NAV_VELNED_MSGID,      "UBX-NAV-VELNED") \
    _P_(UBX_NAV_CLSID, UBX_NAV_SVIN_MSGID,        "UBX-NAV-SVIN") \
    _P_(UBX_NAV_CLSID, UBX_NAV_EOE_MSGID,         "UBX-NAV-EOE") \
    _P_(UBX_NAV_CLSID, UBX_NAV_GEOFENCE_MSGID,    "UBX-NAV-GEOFENCE") \
    _P_(UBX_NAV_CLSID, UBX_NAV_ODO_MSGID,         "UBX-NAV-ODO") \
    _P_(UBX_NAV_CLSID, UBX_NAV_RESETODO_MSGID,    "UBX-NAV-RESETODO") \
    _P_(UBX_NAV_CLSID, UBX_NAV_TIMEUTC_MSGID,     "UBX-NAV-TIMEUTC") \
    _P_(UBX_NAV_CLSID, UBX_NAV_TIMELS_MSGID,      "UBX-NAV-TIMELS") \
    _P_(UBX_NAV_CLSID, UBX_NAV_TIMEGPS_MSGID,     "UBX-NAV-TIMEGPS") \
    _P_(UBX_NAV_CLSID, UBX_NAV_TIMEGLO_MSGID,     "UBX-NAV-TIMEGLO") \
    _P_(UBX_NAV_CLSID, UBX_NAV_TIMEBDS_MSGID,     "UBX-NAV-TIMEBDS") \
    _P_(UBX_NAV_CLSID, UBX_NAV_TIMEGAL_MSGID,     "UBX-NAV-TIMEGAL") \
    _P_(UBX_RXM_CLSID, UBX_RXM_MEASX_MSGID,       "UBX-RXM-MEASX") \
    _P_(UBX_RXM_CLSID, UBX_RXM_RAWX_MSGID,        "UBX-RXM-RAWX") \
    _P_(UBX_RXM_CLSID, UBX_RXM_SFRBX_MSGID,       "UBX-RXM-SFRBX") \
    _P_(UBX_RXM_CLSID, UBX_RXM_PMREQ_MSGID,       "UBX-RXM-PMREQ") \
    _P_(UBX_RXM_CLSID, UBX_RXM_RLM_MSGID,         "UBX-RXM-RLM") \
    _P_(UBX_RXM_CLSID, UBX_RXM_RTCM_MSGID,        "UBX-RXM-RTCM") \
    _P_(UBX_SEC_CLSID, UBX_SEC_UNIQUEID_MSGID,    "UBX-SEC-UNIQUEID") \
    _P_(UBX_TIM_CLSID, UBX_TIM_TM2_MSGID,         "UBX-TIM-TM2") \
    _P_(UBX_TIM_CLSID, UBX_TIM_TP_MSGID,          "UBX-TIM-TP") \
    _P_(UBX_TIM_CLSID, UBX_TIM_VRFY_MSGID,        "UBX-TIM-VRFY") \
    _P_(UBX_UPD_CLSID, UBX_UPD_SOS_MSGID,         "UBX-UPD-SOS")

/* ********************************************************************************************** */

//! UBX-CFG-VALSET (version 1, input) message payload header
typedef struct UBX_CFG_VALSET_V1_GROUP0_s
{
    uint8_t  version;                                //!< Message version (#UBX_CFG_VALSET_V1_VERSION)
    uint8_t  layers;                                 //!< Configuration layers
    uint8_t  transaction;                            //!< Transaction mode
    uint8_t  reserved;                               //!< Reserved (set to 0x00)
} UBX_CFG_VALSET_V1_GROUP0_t;

#define UBX_CFG_VALSET_V1_VERSION              0x01  //!< UBX-CFG-VALSET.version value
#define UBX_CFG_VALSET_V1_LAYER_RAM            0x01  //!< UBX-CFG-VALSET.layers flag: layer RAM
#define UBX_CFG_VALSET_V1_LAYER_BBR            0x02  //!< UBX-CFG-VALSET.layers flag: layer BBR
#define UBX_CFG_VALSET_V1_LAYER_FLASH          0x04  //!< UBX-CFG-VALSET.layers flag: layer Flash
#define UBX_CFG_VALSET_V1_TRANSACTION_NONE     0     //!< UBX-CFG-VALSET.transaction value: no transaction
#define UBX_CFG_VALSET_V1_TRANSACTION_BEGIN    1     //!< UBX-CFG-VALSET.transaction value: transaction begin
#define UBX_CFG_VALSET_V1_TRANSACTION_CONTINUE 2     //!< UBX-CFG-VALSET.transaction value: transaction continue
#define UBX_CFG_VALSET_V1_TRANSACTION_END      3     //!< UBX-CFG-VALSET.transaction value: transaction: end
#define UBX_CFG_VALSET_V1_RESERVED             0x00  //!< UBX-CFG-VALSET.reserved value
#define UBX_CFG_VALSET_V1_MAX_KV               64    //!< UBX-CFG-VALSET.cfgData: maximum number of key-value pairs
#define UBX_CFG_VALSET_V1_CFGDATA_MAX (UBX_CFG_VALSET_V1_MAX_KV * (4 + 8)) //!< UBX-CFG-VALSET.cfgData maximum size

#define UBX_CFG_VALSET_V1_MAX_SIZE             (sizeof(UBX_CFG_VALSET_V1_GROUP0_t) + UBX_CFG_VALSET_V1_CFGDATA_MAX + UBX_FRAME_SIZE)

//! UBX-CFG-VALGET (version 0, poll) message payload header
typedef struct UBX_CFG_VALGET_V0_GROUP0_s
{
    uint8_t  version;                                //!< Message version (#UBX_CFG_VALGET_V0_VERSION)
    uint8_t  layer;                                  //!< Configuration layer
    uint16_t position;                               //!< Number of values to skip in result set
} UBX_CFG_VALGET_V0_GROUP0_t;

#define UBX_CFG_VALGET_V0_VERSION              0x00  //!< UBX-CFG-VALGET.version value
#define UBX_CFG_VALGET_V0_LAYER_RAM            0     //!< UBX-CFG-VALGET.layers value: layer RAM
#define UBX_CFG_VALGET_V0_LAYER_BBR            1     //!< UBX-CFG-VALGET.layers value: layer BBR
#define UBX_CFG_VALGET_V0_LAYER_FLASH          2     //!< UBX-CFG-VALGET.layers value: layer Flash
#define UBX_CFG_VALGET_V0_LAYER_DEFAULT        7     //!< UBX-CFG-VALGET.layers value: layer Default
#define UBX_CFG_VALGET_V0_MAX_K                64    //!< UBX-CFG-VALGET.cfgData maximum number of keys
#define UBX_CFG_VALGET_V0_KEYS_MAX (UBX_CFG_VALGET_V0_MAX_K * 4) //!< UBX-CFG-VALGET.keys maximum size

#define UBX_CFG_VALGET_V0_GROUP_WILDCARD(groupId)  ((groupId) | 0x0000ffff) //!< UBX-CFG-VALGET.keys group wildcard
#define UBX_CFG_VALGET_V0_ALL_WILDCARD                          0x0fffffff  //!< UBX-CFG-VALGET.keys all wildcard

#define UBX_CFG_VALGET_V0_MAX_SIZE             (sizeof(UBX_CFG_VALGET_V0_GROUP0_t) + UBX_CFG_VALGET_V0_KEYS_MAX + UBX_FRAME_SIZE)

//! UBX-CFG-VALGET (version 1, output) message payload header
typedef struct UBX_CFG_VALGET_V1_GROUP0_s
{
    uint8_t  version;                                //!< Message version (#UBX_CFG_VALGET_V1_VERSION)
    uint8_t  layer;                                  //!< Configuration layer
    uint16_t position;                               //!< Number of values to skip in result set
} UBX_CFG_VALGET_V1_GROUP0_t;

#define UBX_CFG_VALGET_V1_VERSION              0x01  //!< UBX-CFG-VALGET.version value
#define UBX_CFG_VALGET_V1_LAYER_RAM            0x00  //!< UBX-CFG-VALGET.layers value: layer RAM
#define UBX_CFG_VALGET_V1_LAYER_BBR            0x01  //!< UBX-CFG-VALGET.layers value: layer BBR
#define UBX_CFG_VALGET_V1_LAYER_FLASH          0x02  //!< UBX-CFG-VALGET.layers value: layer Flash
#define UBX_CFG_VALGET_V1_LAYER_DEFAULT        0x07  //!< UBX-CFG-VALGET.layers value: layer Default
#define UBX_CFG_VALGET_V1_MAX_KV               64    //!< UBX-CFG-VALGET.cfgData maximum number of key-value pairs
#define UBX_CFG_VALGET_V1_CFGDATA_MAX (UBX_CFG_VALGET_V1_MAX_KV * (4 + 8)) //!< UBX-CFG-VALGET.cfgData maximum size

#define UBX_CFG_VALGET_V1_MAX_SIZE             (sizeof(UBX_CFG_VALGET_V1_GROUP0_t) + UBX_CFG_VALGET_V1_CFGDATA_MAX + UBX_FRAME_SIZE)

//! UBX-CFG-VALDEL (version 1, input) message payload header
typedef struct UBX_CFG_VALDEL_V1_GROUP0_s
{
    uint8_t  version;                                //!< Message version (#UBX_CFG_VALGET_V1_VERSION)
    uint8_t  layers;                                 //!< Configuration layers
    uint8_t  transaction;                            //!< Transaction mode
    uint8_t  reserved;                               //!< Reserved (set to 0x00)
} UBX_CFG_VALDEL_V1_GROUP0_t;

#define UBX_CFG_VALDEL_V1_VERSION              0x01  //!< UBX-CFG-VALDEL.version value
#define UBX_CFG_VALDEL_V1_LAYER_BBR            0x02  //!< UBX-CFG-VALDEL.layers flag: layer BBR
#define UBX_CFG_VALDEL_V1_LAYER_FLASH          0x04  //!< UBX-CFG-VALDEL.layers flag: layer Flash
#define UBX_CFG_VALDEL_V1_TRANSACTION_NONE     0     //!< UBX-CFG-VALDEL.transaction value: no transaction
#define UBX_CFG_VALDEL_V1_TRANSACTION_BEGIN    1     //!< UBX-CFG-VALDEL.transaction value: transaction begin
#define UBX_CFG_VALDEL_V1_TRANSACTION_CONTINUE 2     //!< UBX-CFG-VALDEL.transaction value: transaction continue
#define UBX_CFG_VALDEL_V1_TRANSACTION_END      3     //!< UBX-CFG-VALDEL.transaction value: transaction: end
#define UBX_CFG_VALDEL_V1_RESERVED             0x00  //!< UBX-CFG-VALDEL.reserved value
#define UBX_CFG_VALDEL_V1_MAX_K                64    //!< UBX-CFG-VALSET.cfgData maximum number of key IDs
#define UBX_CFG_VALDEL_V1_KEYS_MAX (UBX_CFG_VALDEL_V1_MAX_K * 4) //!< UBX-CFG-VALDEL.keys maximum size

#define UBX_CFG_VALDEL_V1_MAX_SIZE             (sizeof(UBX_CFG_VALDEL_V1_GROUP0_t) + UBX_CFG_VALDEL_V1_KEYS_MAX + UBX_FRAME_SIZE)

//! UBX-CFG-RST (version 0, command) message payload
typedef struct UBX_CFG_RST_V0_GROUP0_s
{
    uint16_t navBbrMask;                              //!< BBR sections to clear
    uint8_t  resetMode;                               //!< Reset type
    uint8_t  reserved;                                //!< Reserved
} UBX_CFG_RST_V0_GROUP0_t;

#define UBX_CFG_RST_V0_NAVBBR_NONE             0x0001 //!< Nothing
#define UBX_CFG_RST_V0_NAVBBR_EPH              0x0001 //!< Ephemeris
#define UBX_CFG_RST_V0_NAVBBR_ALM              0x0002 //!< Almanac
#define UBX_CFG_RST_V0_NAVBBR_HEALTH           0x0004 //!< Health
#define UBX_CFG_RST_V0_NAVBBR_KLOB             0x0008 //!< Klobuchar parameters
#define UBX_CFG_RST_V0_NAVBBR_POS              0x0010 //!< Position
#define UBX_CFG_RST_V0_NAVBBR_CLKD             0x0020 //!< Clock drift
#define UBX_CFG_RST_V0_NAVBBR_OSC              0x0040 //!< Oscillator parameters
#define UBX_CFG_RST_V0_NAVBBR_UTC              0x0080 //!< UTC and leap second parameters
#define UBX_CFG_RST_V0_NAVBBR_RTC              0x0100 //!< RTC
#define UBX_CFG_RST_V0_NAVBBR_AOP              0x8000 //!< AssistNow Autonomous
#define UBX_CFG_RST_V0_NAVBBR_HOTSTART         0x0000 //!< Hostsart (keep all data)
#define UBX_CFG_RST_V0_NAVBBR_WARMSTART        0x0001 //!< Warmstart (clear ephemerides)
#define UBX_CFG_RST_V0_NAVBBR_COLDSTART        0xffff //!< Coldstart (erase all data)
#define UBX_CFG_RST_V0_RESETMODE_HW_FORCED       0x00 //!< Forced, immediate hardware reset
#define UBX_CFG_RST_V0_RESETMODE_SW              0x01 //!< Controlled software reset
#define UBX_CFG_RST_V0_RESETMODE_GNSS            0x02 //!< Restart GNSS
#define UBX_CFG_RST_V0_RESETMODE_HW_CONTROLLED   0x04 //!< Controlled hardware reset
#define UBX_CFG_RST_V0_RESETMODE_GNSS_STOP       0x08 //!< Stop GNSS
#define UBX_CFG_RST_V0_RESETMODE_GNSS_START      0x09 //!< Start GNSS
#define UBX_CFG_RST_V0_RESERVED                  0x00 //!< Reserved

#define UBX_CFG_RST_V0_SIZE             (sizeof(UBX_CFG_RST_V0_GROUP0_t) + UBX_FRAME_SIZE)

//! UBX-CFG-CFG (version 0, command) message head
typedef struct UBX_CFG_CFG_V0_GROUP0_s
{
    uint32_t clearMask;
    uint32_t saveMask;
    uint32_t loadMask;
} UBX_CFG_CFG_V0_GROUP0_t;

//! UBX-CFG-CFG (version 0, command) message optional group
typedef struct UBX_CFG_CFG_V0_GROUP1_s
{
    uint8_t deviceMask;
} UBX_CFG_CFG_V0_GROUP1_t;

#define UBX_CFG_CFG_V0_CLEAR_NONE          0x00000000 //!< Clear no config
#define UBX_CFG_CFG_V0_CLEAR_ALL           0xffffffff //!< Clear all config
#define UBX_CFG_CFG_V0_SAVE_NONE           0x00000000 //!< Save no config
#define UBX_CFG_CFG_V0_SAVE_ALL            0xffffffff //!< Save all config
#define UBX_CFG_CFG_V0_LOAD_NONE           0x00000000 //!< Load no config
#define UBX_CFG_CFG_V0_LOAD_ALL            0xffffffff //!< Load all config
#define UBX_CFG_CFG_V0_DEVICE_BBR                0x01 //!< Layer BBR
#define UBX_CFG_CFG_V0_DEVICE_FLASH              0x02 //!< Layer Flash

#define UBX_CFG_CFG_V0_MAX_SIZE         (sizeof(UBX_CFG_CFG_V0_GROUP0_t) + sizeof(UBX_CFG_CFG_V0_GROUP1_t) + UBX_FRAME_SIZE)


/* ********************************************************************************************** */

//! UBX-MON-VER (version 0, output) message payload header
typedef struct UBX_MON_VER_V0_GROUP0_s
{
    char swVersion[30];
    char hwVersion[10];
} UBX_MON_VER_V0_GROUP0_t;

//! UBX-MON-VER (version 0, output) optional repeated field
typedef struct UBX_MON_VER_V0_GROUP1_s
{
    char extension[30];
} UBX_MON_VER_V0_GROUP1_t;

/* ********************************************************************************************** */

// UBX-ACK-ACK (version 0, output) payload
typedef struct UBX_ACK_ACK_V0_GROUP0_s
{
    uint8_t clsId;                                   //!< Class ID of ack'ed message
    uint8_t msgId;                                   //!< Message ID of ack'ed message
}  UBX_ACK_ACK_V0_GROUP0_t;

// UBX-ACK-NCK (version 0, output) payload
typedef struct UBX_ACK_NAK_V0_GROUP0_s
{
    uint8_t clsId;                                   //!< Class ID of not-ack'ed message
    uint8_t msgId;                                   //!< Message ID of not-ack'ed message
}  UBX_ACK_NAK_V0_GROUP0_t;

/* ********************************************************************************************** */

#define UBX_FRAME_SIZE                         8     //!< Size (in bytes) of UBX frame
#define UBX_SYNC_1                             0xb5
#define UBX_SYNC_2                             0x62
#define UBX_HEAD_SIZE                          6
#define UBX_CLSID(msg)                         ((msg)[2])
#define UBX_MSGID(msg)                         ((msg)[3])

//! Make a UBX message
/*!
    \param[in]   clsId        Message class
    \param[in]   msgId        Message ID
    \param[in]   payload      The message payload (can be NULL)
    \param[in]   payloadSize  Size of the message payload (ignored if \c payload is NULL)
    \param[out]  msg          Message buffer (must be at least \c payloadSize + #UBX_FRAME_SIZE)

    \note \c payload and \c msg may be the same buffer (or may overlap).

    \returns the message size (= \c payloadSize + #UBX_FRAME_SIZE)
*/
int ubxMakeMessage(const uint8_t clsId, const uint8_t msgId, const uint8_t *payload, const uint16_t payloadSize, uint8_t *msg);

//! Get message name
/*!
    \returns the message name
*/
bool ubxMessageName(char *name, const int size, const uint8_t *msg, const int msgSize);

bool ubxMessageInfo(char *info, const int size, const uint8_t *msg, const int msgSize);

/* ********************************************************************************************** */
#endif // __FF_UBX_H__
