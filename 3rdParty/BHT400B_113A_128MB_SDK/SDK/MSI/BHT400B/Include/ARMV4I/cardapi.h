//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
/************************************************************************/
/**                         Microsoft Windows                          **/
/************************************************************************/

//
// Module: CARDAPI.H - WINCE PCMCIA Card Services function typedefs
//

//
// Card Services Function Typedefs (exported by pcmcia.dll)
//
typedef CARD_CLIENT_HANDLE (*REGISTERCLIENT)(CLIENT_CALLBACK, PCARD_REGISTER_PARMS);
typedef STATUS (*GETFIRSTTUPLE)(PCARD_TUPLE_PARMS);
typedef STATUS (*GETNEXTTUPLE)(PCARD_TUPLE_PARMS);
typedef STATUS (*GETTUPLEDATA)(PCARD_DATA_PARMS);
typedef STATUS (*GETPARSEDTUPLE)(CARD_SOCKET_HANDLE, UINT8, PVOID, PUINT32);
typedef STATUS (*GETSTATUS)(PCARD_STATUS);
typedef DWORD (*SYSTEMPOWER)(DWORD);
typedef STATUS (*DEREGISTERCLIENT)(CARD_CLIENT_HANDLE);
typedef STATUS (*REQUESTEXCLUSIVE)(CARD_CLIENT_HANDLE, CARD_SOCKET_HANDLE);
typedef STATUS (*RELEASEEXCLUSIVE)(CARD_CLIENT_HANDLE, CARD_SOCKET_HANDLE);
typedef STATUS (*REQUESTSOCKETMASK)(CARD_CLIENT_HANDLE, CARD_SOCKET_HANDLE, UINT16);
typedef STATUS (*RELEASESOCKETMASK)(CARD_CLIENT_HANDLE, CARD_SOCKET_HANDLE);
typedef STATUS (*GETEVENTMASK)(CARD_CLIENT_HANDLE, PCARD_EVENT_MASK_PARMS);
typedef STATUS (*SETEVENTMASK)(CARD_CLIENT_HANDLE, PCARD_EVENT_MASK_PARMS);
typedef STATUS (*RESETFUNCTION)(CARD_CLIENT_HANDLE, CARD_SOCKET_HANDLE);
typedef CARD_WINDOW_HANDLE (*REQUESTWINDOW)(CARD_CLIENT_HANDLE, PCARD_WINDOW_PARMS);
typedef STATUS (*RELEASEWINDOW)(CARD_WINDOW_HANDLE);   
typedef STATUS (*MODIFYWINDOW)(CARD_WINDOW_HANDLE, UINT16, UINT8);
typedef PVOID (*MAPWINDOW)(CARD_WINDOW_HANDLE, UINT32, UINT32, PUINT32);
typedef STATUS (*REQUESTIRQ)(CARD_CLIENT_HANDLE, CARD_SOCKET_HANDLE,
                      CARD_ISR, UINT32);
typedef STATUS (*RELEASEIRQ)(CARD_CLIENT_HANDLE, CARD_SOCKET_HANDLE);
typedef STATUS (*REQUESTCONFIG)(CARD_CLIENT_HANDLE, PCARD_CONFIG_INFO);
typedef STATUS (*MODIFYCONFIG)(CARD_CLIENT_HANDLE, CARD_SOCKET_HANDLE, PUINT16);
typedef STATUS (*RELEASECONFIG)(CARD_CLIENT_HANDLE, CARD_SOCKET_HANDLE);
typedef STATUS (*ACCESSCONFIGREG)(CARD_CLIENT_HANDLE, CARD_SOCKET_HANDLE,
                      UINT8, UINT8, UINT8 *);
typedef STATUS (*POWERON)(CARD_CLIENT_HANDLE, CARD_SOCKET_HANDLE);
typedef STATUS (*POWEROFF)(CARD_CLIENT_HANDLE, CARD_SOCKET_HANDLE);
