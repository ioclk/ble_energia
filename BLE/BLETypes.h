
#ifndef BLE_TYPES_H
#define BLE_TYPES_H

#include <sap.h>
#include <hal_defs.h>

#include <Energia.h>

/* Energia BLE status codes */
#define BLE_SUCCESS             SNP_SUCCESS // 0x00
#define BLE_FAILURE             SNP_FAILURE // 0x83
#define BLE_INVALID_PARAMETERS  SNP_INVALID_PARAMS // 0x84
#define BLE_ALREADY_ADVERTISING SNP_ALREADY_ADVERTISING // 0x8A
#define BLE_NOT_ADVERTISING     SNP_NOT_ADVERTISING // 0x8B
#define BLE_NOT_CONNECTED       SNP_NOT_CONNECTED // 0x92
#define BLE_INVALID_HANDLE      0x50
#define BLE_UNDEFINED_VALUE     0x51
#define BLE_NOT_IMPLEMENTED     0x52
#define BLE_SERIAL_DISABLED     0x53
#define BLE_TIMEOUT             0x54
#define BLE_CHECK_ERROR         0x55

/* Type of connection between the user application's
   processor and the bluetooth chip */
#define BLE_PORT_LOCAL          SAP_PORT_LOCAL // unsupported
#define BLE_PORT_UART           SAP_PORT_REMOTE_UART
#define BLE_PORT_SPI            SAP_PORT_REMOTE_SPI // unsupported

/*
 * For setAdvertData.
 * Data to advertise when not connected, connected, and when scanned.
 * The first two are passively seen by a client, while scanning is an
 * active action to request more data.
 */
#define BLE_ADV_DATA_NOTCONN    SAP_ADV_DATA_NOTCONN
#define BLE_ADV_DATA_CONN       SAP_ADV_DATA_CONN // TO-DO
#define BLE_ADV_DATA_SCANRSP    SAP_ADV_DATA_SCANRSP
 /* The number of kinds of advertising data */
#define MAX_ADVERT_IDX          3

/*
 * For startAdvert.
 * Connectable undirected adverisement.
 * Scannable undirected advertisement.
 * Non-connectable undirected advertisement.
 */
#define BLE_ADV_MODE_CONN               SNP_ADV_TYPE_CONN
#define BLE_ADV_MODE_SCANABLE           SNP_ADV_TYPE_SCANABLE
#define BLE_ADV_MODE_NONCONN            SNP_ADV_TYPE_NONCONN

/* startAdvert connectedBehavior */
#define BLE_ADV_STOP_ON_CONN            SNP_ADV_STOP_ON_CONN
#define BLE_ADV_RESTART_ON_CONN_EST     SNP_ADV_RESTART_ON_CONN_EST
#define BLE_ADV_RESTART_ON_CONN_TERM    SNP_ADV_RESTART_ON_CONN_TERM

/* Characteristic value properties */
#define BLE_READABLE            SNP_GATT_PROP_READ
#define BLE_WRITABLE_NORSP      SNP_GATT_PROP_WRITE_NORSP
#define BLE_WRITABLE            SNP_GATT_PROP_WRITE
#define BLE_NOTIFIABLE          SNP_GATT_PROP_NOTIFICATION
#define BLE_INDICATABLE         SNP_GATT_PROP_INDICATION

// Minimum connection interval (units of 1.25ms, 6=7.5ms) if automatic
// parameter update request is enabled
#define BLE_DEF_DESIRED_MIN_CONN_INT     6

// Maximum connection interval (units of 1.25ms, 80=100ms) if automatic
// parameter update request is enabled
#define BLE_DEF_DESIRED_MAX_CONN_INT     80

 // Company Identifier: Texas Instruments Inc. (13)
#define TI_COMPANY_ID                         0x000D
#define TI_ST_DEVICE_ID                       0x03
#define TI_ST_KEY_DATA_ID                     0x00

/*
 * Characteristic value formatting, Bluetooth spec Vol 3: Part G: 3.3.3.5.2
 */
#define BLE_UINT                 0x06

typedef struct
{
  unsigned char     UUID[16]; // array of UUID bytes, little-endian
  unsigned char     properties; // bitwise OR of macros: e.g. BLE_READABLE | BLE_WRITABLE
  // Null terminated; internally set permissions to read only so we don't have to worry about the length changing
  const char        *charDesc;
  unsigned char     valueFormat;
  unsigned char     valueExponent; // only used with integer formats, e.g. value = storedValue*10^valueExponent
  unsigned int      handle;
  void              *_value;
  uint16_t          _valueLen;
  uint8_t           _CCCD;
  uint16_t          _CCCDHandle;
  bool              _resizable;
} BLE_Char;

typedef struct
{
  unsigned char     UUID[16]; // array of UUID bytes
  unsigned int      numChars;
  BLE_Char          **chars;
  uint16_t          handle;
} BLE_Service;

typedef struct
{
  unsigned char     advertMode;
  unsigned int      timeout; // How long to advertise for (in ms), 0 for indefinitely
  unsigned int      interval; // Advertising Interval (n * 0.625 ms), 0 for 100ms default
  /* 0x00   Advertising is disabled during connection and will not start after.
   * 0x01   Advertising will continue with non-connectable advertising when connection is established
        There are separate GAP parameters for setting connected advertising interval.
   * 0x02   Advertising will restart with connectable advertising when a connection is terminated.
   */
  unsigned char      connectedBehavior;
} BLE_Advert_Settings;

/*******************************************************************************
 * See the SNP API guide for documentation on these typedefs.
 ******************************************************************************/
typedef snpGetRevisionRsp_t BLE_Get_Revision_Rsp;
typedef snpGetStatusCmdRsp_t BLE_Get_Status_Rsp;
typedef snpTestCmdRsp_t BLE_Test_Command_Rsp;
typedef snpUpdateConnParamReq_t BLE_Conn_Params_Update_Req;
typedef snpConnEstEvt_t BLE_Conn_Params;

#endif
