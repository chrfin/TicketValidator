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
/********
*
*  Copyright (c) 1995  Process Software Corporation
*
*
*
*  Module Name  : HttpExt.h
*
*  Abstract :
*
*     This module contains  the structure definitions and prototypes for the
*      HTTP Server Extension interface used to build ISAPI Applications
*
******************/

#ifndef _HTTPEXT_H_
#define _HTTPEXT_H_

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif


/************************************************************
 *   Manifest Constants
 ************************************************************/

#define   HSE_VERSION_MAJOR           4      // major version of this spec
#define   HSE_VERSION_MINOR           0      // minor version of this spec
#define   HSE_LOG_BUFFER_LEN         80
#define   HSE_MAX_EXT_DLL_NAME_LEN  256

#define   HSE_VERSION     MAKELONG( HSE_VERSION_MINOR, HSE_VERSION_MAJOR )

//
// the following are the status codes returned by the Extension DLL
//

#define   HSE_STATUS_SUCCESS                       1
#define   HSE_STATUS_SUCCESS_AND_KEEP_CONN         2
#define   HSE_STATUS_PENDING                       3
#define   HSE_STATUS_ERROR                         4

//
// The following are the values to request services with the
//   ServerSupportFunction().
//  Values from 0 to 1000 are reserved for future versions of the interface

#define   HSE_REQ_BASE                             0
#define   HSE_REQ_SEND_URL_REDIRECT_RESP           ( HSE_REQ_BASE + 1 )
#define   HSE_REQ_SEND_URL                         ( HSE_REQ_BASE + 2 )
#define   HSE_REQ_SEND_RESPONSE_HEADER             ( HSE_REQ_BASE + 3 )
#define   HSE_REQ_DONE_WITH_SESSION                ( HSE_REQ_BASE + 4 )
#define   HSE_REQ_END_RESERVED                     1000

//
//  These are Microsoft specific extensions
//

#define   HSE_REQ_MAP_URL_TO_PATH                  (HSE_REQ_END_RESERVED+1)
#define   HSE_REQ_GET_SSPI_INFO                    (HSE_REQ_END_RESERVED+2)
#define   HSE_APPEND_LOG_PARAMETER                 (HSE_REQ_END_RESERVED+3)
#define   HSE_REQ_IO_COMPLETION                    (HSE_REQ_END_RESERVED+5)
#define   HSE_REQ_TRANSMIT_FILE                    (HSE_REQ_END_RESERVED+6)
#define   HSE_REQ_REFRESH_ISAPI_ACL                (HSE_REQ_END_RESERVED+7)
#define   HSE_REQ_IS_KEEP_CONN                     (HSE_REQ_END_RESERVED+8)
#define   HSE_REQ_ASYNC_READ_CLIENT                (HSE_REQ_END_RESERVED+10)
#define   HSE_REQ_GET_IMPERSONATION_TOKEN          (HSE_REQ_END_RESERVED+11)
#define   HSE_REQ_MAP_URL_TO_PATH_EX               (HSE_REQ_END_RESERVED+12)
#define   HSE_REQ_ABORTIVE_CLOSE                   (HSE_REQ_END_RESERVED+14)
#define   HSE_REQ_GET_CERT_INFO_EX                 (HSE_REQ_END_RESERVED+15)
#define   HSE_REQ_SEND_RESPONSE_HEADER_EX          (HSE_REQ_END_RESERVED+16)

//
//  Bit Flags for TerminateExtension
//
//    HSE_TERM_ADVISORY_UNLOAD - Server wants to unload the extension,
//          extension can return TRUE if OK, FALSE if the server should not
//          unload the extension
//
//    HSE_TERM_MUST_UNLOAD - Server indicating the extension is about to be
//          unloaded, the extension cannot refuse.
//

#define HSE_TERM_ADVISORY_UNLOAD                   0x00000001
#define HSE_TERM_MUST_UNLOAD                       0x00000002

//
// Flags for IO Functions, supported for IO Funcs.
//  TF means ServerSupportFunction( HSE_REQ_TRANSMIT_FILE)
//

# define HSE_IO_SYNC                      0x00000001   // for WriteClient
# define HSE_IO_ASYNC                     0x00000002   // for WriteClient/TF
# define HSE_IO_DISCONNECT_AFTER_SEND     0x00000004   // for TF
# define HSE_IO_SEND_HEADERS              0x00000008   // for TF


/************************************************************
 *   Type Definitions
 ************************************************************/

typedef   LPVOID          HCONN;

//
// structure passed to GetExtensionVersion()
//

typedef struct   _HSE_VERSION_INFO {

    DWORD  dwExtensionVersion;
    CHAR   lpszExtensionDesc[HSE_MAX_EXT_DLL_NAME_LEN];

} HSE_VERSION_INFO, *LPHSE_VERSION_INFO;


//
// structure passed to extension procedure on a new request
//
typedef struct _EXTENSION_CONTROL_BLOCK {

    DWORD     cbSize;                 // size of this struct.
    DWORD     dwVersion;              // version info of this spec
    HCONN     ConnID;                 // Context number not to be modified!
    DWORD     dwHttpStatusCode;       // HTTP Status code
    CHAR      lpszLogData[HSE_LOG_BUFFER_LEN];// null terminated log info specific to this Extension DLL

    LPSTR     lpszMethod;             // REQUEST_METHOD
    LPSTR     lpszQueryString;        // QUERY_STRING
    LPSTR     lpszPathInfo;           // PATH_INFO
    LPSTR     lpszPathTranslated;     // PATH_TRANSLATED

    DWORD     cbTotalBytes;           // Total bytes indicated from client
    DWORD     cbAvailable;            // Available number of bytes
    LPBYTE    lpbData;                // pointer to cbAvailable bytes

    LPSTR     lpszContentType;        // Content type of client data

    BOOL (WINAPI * GetServerVariable) ( HCONN       hConn,
                                        LPSTR       lpszVariableName,
                                        LPVOID      lpvBuffer,
                                        LPDWORD     lpdwSize );

    BOOL (WINAPI * WriteClient)  ( HCONN      ConnID,
                                   LPVOID     Buffer,
                                   LPDWORD    lpdwBytes,
                                   DWORD      dwReserved );

    BOOL (WINAPI * ReadClient)  ( HCONN      ConnID,
                                  LPVOID     lpvBuffer,
                                  LPDWORD    lpdwSize );

    BOOL (WINAPI * ServerSupportFunction)( HCONN      hConn,
                                           DWORD      dwHSERequest,
                                           LPVOID     lpvBuffer,
                                           LPDWORD    lpdwSize,
                                           LPDWORD    lpdwDataType );

} EXTENSION_CONTROL_BLOCK, *LPEXTENSION_CONTROL_BLOCK;




//
//  Bit field of flags that can be on a virtual directory
//

#define HSE_URL_FLAGS_READ          0x00000001    // Allow for Read
#define HSE_URL_FLAGS_WRITE         0x00000002    // Allow for Write
#define HSE_URL_FLAGS_EXECUTE       0x00000004    // Allow for Execute
#define HSE_URL_FLAGS_SSL           0x00000008    // Require SSL
#define HSE_URL_FLAGS_DONT_CACHE    0x00000010    // Don't cache (vroot only)
#define HSE_URL_FLAGS_NEGO_CERT     0x00000020    // Allow client SSL certs
#define HSE_URL_FLAGS_REQUIRE_CERT  0x00000040    // Require client SSL certs
#define HSE_URL_FLAGS_MAP_CERT      0x00000080    // Map SSL cert to NT account
#define HSE_URL_FLAGS_SSL128        0x00000100    // Require 128 bit SSL
#define HSE_URL_FLAGS_SCRIPT        0x00000200    // Allow for Script execution

#if defined (UNDER_CE)
#define HSE_URL_FLAGS_SCRIPT_SOURCE 0x00000400    // Allow client to access script source
#define HSE_URL_FLAGS_MASK          0x000007ff
#else
#define HSE_URL_FLAGS_MASK          0x000003ff
#endif



//
//  Structure for extended information on a URL mapping
//

typedef struct _HSE_URL_MAPEX_INFO {

    CHAR   lpszPath[MAX_PATH]; // Physical path root mapped to
    DWORD  dwFlags;            // Flags associated with this URL path
    DWORD  cchMatchingPath;    // Number of matching characters in physical path
    DWORD  cchMatchingURL;     // Number of matching characters in URL

    DWORD  dwReserved1;
    DWORD  dwReserved2;

} HSE_URL_MAPEX_INFO, * LPHSE_URL_MAPEX_INFO;



//
// PFN_HSE_IO_COMPLETION - callback function for the Async I/O Completion.
//

typedef VOID
  (WINAPI * PFN_HSE_IO_COMPLETION)(
                                   IN EXTENSION_CONTROL_BLOCK * pECB,
                                   IN PVOID    pContext,
                                   IN DWORD    cbIO,
                                   IN DWORD    dwError
                                   );



//
// HSE_TF_INFO defines the type for HTTP SERVER EXTENSION support for
//  ISAPI applications to send files using TransmitFile.
// A pointer to this object should be used with ServerSupportFunction()
//  for HSE_REQ_TRANSMIT_FILE.
//

typedef struct _HSE_TF_INFO  {

    //
    // callback and context information
    // the callback function will be called when IO is completed.
    // the context specified will be used during such callback.
    //
    // These values (if non-NULL) will override the one set by calling
    //  ServerSupportFunction() with HSE_REQ_IO_COMPLETION
    //
    PFN_HSE_IO_COMPLETION   pfnHseIO;
    PVOID  pContext;

    // file should have been opened with FILE_FLAG_SEQUENTIAL_SCAN
    HANDLE hFile;

    //
    // HTTP header and status code
    // These fields are used only if HSE_IO_SEND_HEADERS is present in dwFlags
    //

    LPCSTR pszStatusCode; // HTTP Status Code  eg: "200 OK"

    DWORD  BytesToWrite;  // special value of "0" means write entire file.
    DWORD  Offset;        // offset value within the file to start from

    PVOID  pHead;         // Head buffer to be sent before file data
    DWORD  HeadLength;    // header length
    PVOID  pTail;         // Tail buffer to be sent after file data
    DWORD  TailLength;    // tail length

    DWORD  dwFlags;       // includes HSE_IO_DISCONNECT_AFTER_SEND, ...

} HSE_TF_INFO, * LPHSE_TF_INFO;


//
//	HSE_SEND_HEADER_EX_INFO allows an ISAPI application to send headers
//	and specify keep-alive behavior in the same call.
//

typedef struct _HSE_SEND_HEADER_EX_INFO  {

    //
    // HTTP status code and header
    //

    LPCSTR  pszStatus;  // HTTP status code  eg: "200 OK"
    LPCSTR  pszHeader;  // HTTP header

    DWORD   cchStatus;  // number of characters in status code
    DWORD   cchHeader;  // number of characters in header

    BOOL    fKeepConn;  // keep client connection alive?

} HSE_SEND_HEADER_EX_INFO, * LPHSE_SEND_HEADER_EX_INFO;


#if(_WIN32_WINNT >= 0x400)
#include <wincrypt.h>
//
//	CERT_CONTEXT_EX is passed as an an argument to 
//  ServerSupportFunction( HSE_REQ_GET_CERT_INFO_EX )
//

typedef struct _CERT_CONTEXT_EX {
    CERT_CONTEXT    CertContext;
    DWORD           cbAllocated;
    DWORD           dwCertificateFlags;
} CERT_CONTEXT_EX;
#endif



/************************************************************
 *   Function Prototypes 
 *   o  for functions exported from the ISAPI Application DLL
 ************************************************************/

BOOL  WINAPI   GetExtensionVersion( HSE_VERSION_INFO  *pVer );
DWORD WINAPI   HttpExtensionProc(  EXTENSION_CONTROL_BLOCK *pECB );
BOOL  WINAPI   TerminateExtension( DWORD dwFlags );

// the following type declarations is for use in the server side

typedef BOOL
    (WINAPI * PFN_GETEXTENSIONVERSION)( HSE_VERSION_INFO  *pVer );

typedef DWORD 
    (WINAPI * PFN_HTTPEXTENSIONPROC )( EXTENSION_CONTROL_BLOCK * pECB );

typedef BOOL  (WINAPI * PFN_TERMINATEEXTENSION )( DWORD dwFlags );

#ifdef UNDER_CE
// The functionality to stop and restart the server.  Either link to
// httpd.lib or do a LoadLibrary on httpd.dll to access this function.
// Note that this only refreshes the web server, use httpdsvc or the
// control panel applet to turn it on or off.
void HttpdStopAndRestart();

// Flags associated with IOCTL_SERVICE_SUPPORTED_OPTIONS.  A calling application
// supplies a DWORD buffer to write to, and web server sets which of the following
// options are included.  These flags indicate what modules the web server has been
// linked with, not necessarily which options are currently enabled.  For instance
// the web server would set HTTPD_OPTION_SSL if it could theoretically support
// SSL operations, even if SSL weren't configured at the moment.

#define HTTPD_OPTION_ISAPI_EXTENSIONS              0x0000001
#define HTTPD_OPTION_ISAPI_FILTERS                 0x0000002
#define HTTPD_OPTION_AUTHENTICATION                0x0000004
#define HTTPD_OPTION_SSL                           0x0000008
#define HTTPD_OPTION_WEBDAV                        0x0000010

#endif


#ifdef __cplusplus
}
#endif


#endif  // end definition _HTTPEXT_H_


