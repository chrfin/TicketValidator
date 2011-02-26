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

#pragma once

#include <windows.h>

#include "lap.h"

#ifdef __cplusplus
extern "C"
{
#endif

//Success codes

//The server pc is unlocked and authenticated
#define VOIPLAP_S_PCUNLOCKED                0

//the server pc is locked and authenticated
#define VOIPLAP_S_PCLOCKED                  1

//error codes
#define VOIPLAP_E_BASE     6000

//no server set on the system
#define VOIPLAP_E_NOSERVER                  VOIPLAP_E_BASE + 1

//no credentials on the system
#define VOIPLAP_E_NOCREDENTIALS             VOIPLAP_E_BASE + 2

//can't connect to the host pc
#define VOIPLAP_E_CANTCONNECT               VOIPLAP_E_BASE + 3

//can't authenticate with the server
#define VOIPLAP_E_CANTAUTHENTICATESERVER    VOIPLAP_E_BASE + 4

//send/receive failed
#define VOIPLAP_E_TRANSMISSIONFAILED        VOIPLAP_E_BASE + 5

//timeout during query
#define VOIPLAP_E_TIMEOUT                   VOIPLAP_E_BASE + 6

//invalid data received from the server
#define VOIPLAP_E_INVALIDDATA               VOIPLAP_E_BASE + 7

//Another request is currently running
#define VOIPLAP_E_BUSY                      VOIPLAP_E_BASE + 8

HRESULT SetPCSyncName(const WCHAR *c_wszPCName);
HRESULT GetPCSyncName(WCHAR *wszNameBuffer, INT cchNameBuffer);

DWORD   AttemptConnection();

#ifdef __cplusplus
}
#endif
