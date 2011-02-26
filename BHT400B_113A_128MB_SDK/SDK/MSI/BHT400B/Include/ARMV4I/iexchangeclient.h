
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Wed Feb 20 14:03:13 2008
 */
/* Compiler settings for .\iexchangeclient.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __iexchangeclient_h__
#define __iexchangeclient_h__

/* Forward Declarations */ 

#ifndef __IExchangeClient_FWD_DEFINED__
#define __IExchangeClient_FWD_DEFINED__
typedef interface IExchangeClient IExchangeClient;
#endif 	/* __IExchangeClient_FWD_DEFINED__ */


#ifndef __IExchangeClientRequest_FWD_DEFINED__
#define __IExchangeClientRequest_FWD_DEFINED__
typedef interface IExchangeClientRequest IExchangeClientRequest;
#endif 	/* __IExchangeClientRequest_FWD_DEFINED__ */


#ifndef __IExchangeClientRequestCallback_FWD_DEFINED__
#define __IExchangeClientRequestCallback_FWD_DEFINED__
typedef interface IExchangeClientRequestCallback IExchangeClientRequestCallback;
#endif 	/* __IExchangeClientRequestCallback_FWD_DEFINED__ */


#ifndef __IExchangeClientDataItemArray_FWD_DEFINED__
#define __IExchangeClientDataItemArray_FWD_DEFINED__
typedef interface IExchangeClientDataItemArray IExchangeClientDataItemArray;
#endif 	/* __IExchangeClientDataItemArray_FWD_DEFINED__ */


#ifndef __IExchangeClientContactInformation_FWD_DEFINED__
#define __IExchangeClientContactInformation_FWD_DEFINED__
typedef interface IExchangeClientContactInformation IExchangeClientContactInformation;
#endif 	/* __IExchangeClientContactInformation_FWD_DEFINED__ */


#ifndef __IExchangeClientGALSearchInformation_FWD_DEFINED__
#define __IExchangeClientGALSearchInformation_FWD_DEFINED__
typedef interface IExchangeClientGALSearchInformation IExchangeClientGALSearchInformation;
#endif 	/* __IExchangeClientGALSearchInformation_FWD_DEFINED__ */


#ifndef __IExchangeClientFreeBusyInformation_FWD_DEFINED__
#define __IExchangeClientFreeBusyInformation_FWD_DEFINED__
typedef interface IExchangeClientFreeBusyInformation IExchangeClientFreeBusyInformation;
#endif 	/* __IExchangeClientFreeBusyInformation_FWD_DEFINED__ */


#ifndef __ExchangeClient_FWD_DEFINED__
#define __ExchangeClient_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExchangeClient ExchangeClient;
#else
typedef struct ExchangeClient ExchangeClient;
#endif /* __cplusplus */

#endif 	/* __ExchangeClient_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_iexchangeclient_0000 */
/* [local] */ 

#define	OWAEC_E_NOTINITIALIZED	( ( HRESULT  )(( unsigned long  )1 << 31 | ( unsigned long  )0xbb << 16 | ( unsigned long  )0x1) )

#define	OWAEC_E_NOSERVER	( ( HRESULT  )(( unsigned long  )1 << 31 | ( unsigned long  )0xbb << 16 | ( unsigned long  )0x2) )

#define	OWAEC_E_NOUSER	( ( HRESULT  )(( unsigned long  )1 << 31 | ( unsigned long  )0xbb << 16 | ( unsigned long  )0x3) )

#define	OWAEC_E_INVALIDSEARCH	( ( HRESULT  )(( unsigned long  )1 << 31 | ( unsigned long  )0xbb << 16 | ( unsigned long  )0x4) )

#define	OWAEC_E_NODATA	( ( HRESULT  )(( unsigned long  )1 << 31 | ( unsigned long  )0xbb << 16 | ( unsigned long  )0x5) )

#define	OWAEC_E_ALREADYINITIALIZED	( ( HRESULT  )(( unsigned long  )1 << 31 | ( unsigned long  )0xbb << 16 | ( unsigned long  )0x6) )


enum ExchangeClientRequestStatus
    {	e_ecrsPending	= 0,
	e_ecrsInProgress	= e_ecrsPending + 1,
	e_ecrsSending	= e_ecrsInProgress + 1,
	e_ecrsBypassingOWAPage	= e_ecrsSending + 1,
	e_ecrsSucceeded	= e_ecrsBypassingOWAPage + 1,
	e_ecrsOutOfMemory	= e_ecrsSucceeded + 1,
	e_ecrsParseFailed	= e_ecrsOutOfMemory + 1,
	e_ecrsHttpFailure	= e_ecrsParseFailed + 1,
	e_ecrsFailedToSend	= e_ecrsHttpFailure + 1,
	e_ecrsFailedToBypassAuthPage	= e_ecrsFailedToSend + 1,
	e_ecrsCancelled	= e_ecrsFailedToBypassAuthPage + 1,
	e_ecrsNoCredentials	= e_ecrsCancelled + 1
    };

enum ExchangeClientRequestType
    {	e_ecrtInvalid	= 0,
	e_ecrtContacts	= e_ecrtInvalid + 1,
	e_ecrtGALSearch	= e_ecrtContacts + 1,
	e_ecrtFreeBusy	= e_ecrtGALSearch + 1
    };
struct GALSearchCriteria
    {
    WCHAR __RPC_FAR *wszAlias;
    WCHAR __RPC_FAR *wszFirstName;
    WCHAR __RPC_FAR *wszLastName;
    };
struct FreeBusyCriteria
    {
    WCHAR __RPC_FAR *wszAlias;
    SYSTEMTIME __RPC_FAR *pstStart;
    };
struct ContactsSearchCriteria
    {
    WCHAR __RPC_FAR *wszFirstName;
    WCHAR __RPC_FAR *wszLastName;
    };





extern RPC_IF_HANDLE __MIDL_itf_iexchangeclient_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_iexchangeclient_0000_v0_0_s_ifspec;

#ifndef __IExchangeClient_INTERFACE_DEFINED__
#define __IExchangeClient_INTERFACE_DEFINED__

/* interface IExchangeClient */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IExchangeClient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C8747796-A963-438f-A5B7-0EE3383B4997")
    IExchangeClient : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IExchangeClientRequestCallback __RPC_FAR *piCallback) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetServer( 
            /* [in] */ const WCHAR __RPC_FAR *c_wszServername) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetServer( 
            /* [out] */ WCHAR __RPC_FAR *wszBuffer,
            /* [in] */ UINT cchBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCredentials( 
            /* [in] */ const WCHAR __RPC_FAR *c_wszUsername,
            /* [in] */ const WCHAR __RPC_FAR *c_wszPassword) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestContacts( 
            /* [in] */ struct ContactsSearchCriteria __RPC_FAR *pCriteria,
            /* [retval][out] */ IExchangeClientRequest __RPC_FAR *__RPC_FAR *ppiRequest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestGALSearch( 
            /* [in] */ struct GALSearchCriteria __RPC_FAR *pCriteria,
            /* [retval][out] */ IExchangeClientRequest __RPC_FAR *__RPC_FAR *ppiRequest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestFreeBusyData( 
            /* [in] */ struct FreeBusyCriteria __RPC_FAR *pCriteria,
            /* [retval][out] */ IExchangeClientRequest __RPC_FAR *__RPC_FAR *ppiRequest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CancelPendingRequests( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Uninitialize( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExchangeClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExchangeClient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExchangeClient __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExchangeClient __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IExchangeClient __RPC_FAR * This,
            /* [in] */ IExchangeClientRequestCallback __RPC_FAR *piCallback);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetServer )( 
            IExchangeClient __RPC_FAR * This,
            /* [in] */ const WCHAR __RPC_FAR *c_wszServername);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetServer )( 
            IExchangeClient __RPC_FAR * This,
            /* [out] */ WCHAR __RPC_FAR *wszBuffer,
            /* [in] */ UINT cchBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCredentials )( 
            IExchangeClient __RPC_FAR * This,
            /* [in] */ const WCHAR __RPC_FAR *c_wszUsername,
            /* [in] */ const WCHAR __RPC_FAR *c_wszPassword);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestContacts )( 
            IExchangeClient __RPC_FAR * This,
            /* [in] */ struct ContactsSearchCriteria __RPC_FAR *pCriteria,
            /* [retval][out] */ IExchangeClientRequest __RPC_FAR *__RPC_FAR *ppiRequest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestGALSearch )( 
            IExchangeClient __RPC_FAR * This,
            /* [in] */ struct GALSearchCriteria __RPC_FAR *pCriteria,
            /* [retval][out] */ IExchangeClientRequest __RPC_FAR *__RPC_FAR *ppiRequest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestFreeBusyData )( 
            IExchangeClient __RPC_FAR * This,
            /* [in] */ struct FreeBusyCriteria __RPC_FAR *pCriteria,
            /* [retval][out] */ IExchangeClientRequest __RPC_FAR *__RPC_FAR *ppiRequest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelPendingRequests )( 
            IExchangeClient __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Uninitialize )( 
            IExchangeClient __RPC_FAR * This);
        
        END_INTERFACE
    } IExchangeClientVtbl;

    interface IExchangeClient
    {
        CONST_VTBL struct IExchangeClientVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExchangeClient_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExchangeClient_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExchangeClient_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExchangeClient_Initialize(This,piCallback)	\
    (This)->lpVtbl -> Initialize(This,piCallback)

#define IExchangeClient_SetServer(This,c_wszServername)	\
    (This)->lpVtbl -> SetServer(This,c_wszServername)

#define IExchangeClient_GetServer(This,wszBuffer,cchBuffer)	\
    (This)->lpVtbl -> GetServer(This,wszBuffer,cchBuffer)

#define IExchangeClient_SetCredentials(This,c_wszUsername,c_wszPassword)	\
    (This)->lpVtbl -> SetCredentials(This,c_wszUsername,c_wszPassword)

#define IExchangeClient_RequestContacts(This,pCriteria,ppiRequest)	\
    (This)->lpVtbl -> RequestContacts(This,pCriteria,ppiRequest)

#define IExchangeClient_RequestGALSearch(This,pCriteria,ppiRequest)	\
    (This)->lpVtbl -> RequestGALSearch(This,pCriteria,ppiRequest)

#define IExchangeClient_RequestFreeBusyData(This,pCriteria,ppiRequest)	\
    (This)->lpVtbl -> RequestFreeBusyData(This,pCriteria,ppiRequest)

#define IExchangeClient_CancelPendingRequests(This)	\
    (This)->lpVtbl -> CancelPendingRequests(This)

#define IExchangeClient_Uninitialize(This)	\
    (This)->lpVtbl -> Uninitialize(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IExchangeClient_Initialize_Proxy( 
    IExchangeClient __RPC_FAR * This,
    /* [in] */ IExchangeClientRequestCallback __RPC_FAR *piCallback);


void __RPC_STUB IExchangeClient_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClient_SetServer_Proxy( 
    IExchangeClient __RPC_FAR * This,
    /* [in] */ const WCHAR __RPC_FAR *c_wszServername);


void __RPC_STUB IExchangeClient_SetServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClient_GetServer_Proxy( 
    IExchangeClient __RPC_FAR * This,
    /* [out] */ WCHAR __RPC_FAR *wszBuffer,
    /* [in] */ UINT cchBuffer);


void __RPC_STUB IExchangeClient_GetServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClient_SetCredentials_Proxy( 
    IExchangeClient __RPC_FAR * This,
    /* [in] */ const WCHAR __RPC_FAR *c_wszUsername,
    /* [in] */ const WCHAR __RPC_FAR *c_wszPassword);


void __RPC_STUB IExchangeClient_SetCredentials_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClient_RequestContacts_Proxy( 
    IExchangeClient __RPC_FAR * This,
    /* [in] */ struct ContactsSearchCriteria __RPC_FAR *pCriteria,
    /* [retval][out] */ IExchangeClientRequest __RPC_FAR *__RPC_FAR *ppiRequest);


void __RPC_STUB IExchangeClient_RequestContacts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClient_RequestGALSearch_Proxy( 
    IExchangeClient __RPC_FAR * This,
    /* [in] */ struct GALSearchCriteria __RPC_FAR *pCriteria,
    /* [retval][out] */ IExchangeClientRequest __RPC_FAR *__RPC_FAR *ppiRequest);


void __RPC_STUB IExchangeClient_RequestGALSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClient_RequestFreeBusyData_Proxy( 
    IExchangeClient __RPC_FAR * This,
    /* [in] */ struct FreeBusyCriteria __RPC_FAR *pCriteria,
    /* [retval][out] */ IExchangeClientRequest __RPC_FAR *__RPC_FAR *ppiRequest);


void __RPC_STUB IExchangeClient_RequestFreeBusyData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClient_CancelPendingRequests_Proxy( 
    IExchangeClient __RPC_FAR * This);


void __RPC_STUB IExchangeClient_CancelPendingRequests_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClient_Uninitialize_Proxy( 
    IExchangeClient __RPC_FAR * This);


void __RPC_STUB IExchangeClient_Uninitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExchangeClient_INTERFACE_DEFINED__ */


#ifndef __IExchangeClientRequest_INTERFACE_DEFINED__
#define __IExchangeClientRequest_INTERFACE_DEFINED__

/* interface IExchangeClientRequest */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IExchangeClientRequest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F701C86E-A8D0-4e1b-9E5D-5E6F5522D56B")
    IExchangeClientRequest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetStatus( 
            /* [retval][out] */ enum ExchangeClientRequestStatus __RPC_FAR *pStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDataItemArray( 
            /* [retval][out] */ IExchangeClientDataItemArray __RPC_FAR *__RPC_FAR *ppiArray) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHttpStatus( 
            /* [retval][out] */ LONG __RPC_FAR *plHttpStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetType( 
            /* [retval][out] */ enum ExchangeClientRequestType __RPC_FAR *pecrt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Cancel( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExchangeClientRequestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExchangeClientRequest __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExchangeClientRequest __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExchangeClientRequest __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStatus )( 
            IExchangeClientRequest __RPC_FAR * This,
            /* [retval][out] */ enum ExchangeClientRequestStatus __RPC_FAR *pStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDataItemArray )( 
            IExchangeClientRequest __RPC_FAR * This,
            /* [retval][out] */ IExchangeClientDataItemArray __RPC_FAR *__RPC_FAR *ppiArray);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHttpStatus )( 
            IExchangeClientRequest __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *plHttpStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            IExchangeClientRequest __RPC_FAR * This,
            /* [retval][out] */ enum ExchangeClientRequestType __RPC_FAR *pecrt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            IExchangeClientRequest __RPC_FAR * This);
        
        END_INTERFACE
    } IExchangeClientRequestVtbl;

    interface IExchangeClientRequest
    {
        CONST_VTBL struct IExchangeClientRequestVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExchangeClientRequest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExchangeClientRequest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExchangeClientRequest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExchangeClientRequest_GetStatus(This,pStatus)	\
    (This)->lpVtbl -> GetStatus(This,pStatus)

#define IExchangeClientRequest_GetDataItemArray(This,ppiArray)	\
    (This)->lpVtbl -> GetDataItemArray(This,ppiArray)

#define IExchangeClientRequest_GetHttpStatus(This,plHttpStatus)	\
    (This)->lpVtbl -> GetHttpStatus(This,plHttpStatus)

#define IExchangeClientRequest_GetType(This,pecrt)	\
    (This)->lpVtbl -> GetType(This,pecrt)

#define IExchangeClientRequest_Cancel(This)	\
    (This)->lpVtbl -> Cancel(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IExchangeClientRequest_GetStatus_Proxy( 
    IExchangeClientRequest __RPC_FAR * This,
    /* [retval][out] */ enum ExchangeClientRequestStatus __RPC_FAR *pStatus);


void __RPC_STUB IExchangeClientRequest_GetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientRequest_GetDataItemArray_Proxy( 
    IExchangeClientRequest __RPC_FAR * This,
    /* [retval][out] */ IExchangeClientDataItemArray __RPC_FAR *__RPC_FAR *ppiArray);


void __RPC_STUB IExchangeClientRequest_GetDataItemArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientRequest_GetHttpStatus_Proxy( 
    IExchangeClientRequest __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *plHttpStatus);


void __RPC_STUB IExchangeClientRequest_GetHttpStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientRequest_GetType_Proxy( 
    IExchangeClientRequest __RPC_FAR * This,
    /* [retval][out] */ enum ExchangeClientRequestType __RPC_FAR *pecrt);


void __RPC_STUB IExchangeClientRequest_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientRequest_Cancel_Proxy( 
    IExchangeClientRequest __RPC_FAR * This);


void __RPC_STUB IExchangeClientRequest_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExchangeClientRequest_INTERFACE_DEFINED__ */


#ifndef __IExchangeClientRequestCallback_INTERFACE_DEFINED__
#define __IExchangeClientRequestCallback_INTERFACE_DEFINED__

/* interface IExchangeClientRequestCallback */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IExchangeClientRequestCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D0682E7F-4976-42ec-88DC-EB34C6A28204")
    IExchangeClientRequestCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnShutdown( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnRequestProgress( 
            /* [in] */ IExchangeClientRequest __RPC_FAR *pRequest,
            /* [in] */ enum ExchangeClientRequestStatus status) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExchangeClientRequestCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExchangeClientRequestCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExchangeClientRequestCallback __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExchangeClientRequestCallback __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnShutdown )( 
            IExchangeClientRequestCallback __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnRequestProgress )( 
            IExchangeClientRequestCallback __RPC_FAR * This,
            /* [in] */ IExchangeClientRequest __RPC_FAR *pRequest,
            /* [in] */ enum ExchangeClientRequestStatus status);
        
        END_INTERFACE
    } IExchangeClientRequestCallbackVtbl;

    interface IExchangeClientRequestCallback
    {
        CONST_VTBL struct IExchangeClientRequestCallbackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExchangeClientRequestCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExchangeClientRequestCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExchangeClientRequestCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExchangeClientRequestCallback_OnShutdown(This)	\
    (This)->lpVtbl -> OnShutdown(This)

#define IExchangeClientRequestCallback_OnRequestProgress(This,pRequest,status)	\
    (This)->lpVtbl -> OnRequestProgress(This,pRequest,status)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IExchangeClientRequestCallback_OnShutdown_Proxy( 
    IExchangeClientRequestCallback __RPC_FAR * This);


void __RPC_STUB IExchangeClientRequestCallback_OnShutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientRequestCallback_OnRequestProgress_Proxy( 
    IExchangeClientRequestCallback __RPC_FAR * This,
    /* [in] */ IExchangeClientRequest __RPC_FAR *pRequest,
    /* [in] */ enum ExchangeClientRequestStatus status);


void __RPC_STUB IExchangeClientRequestCallback_OnRequestProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExchangeClientRequestCallback_INTERFACE_DEFINED__ */


#ifndef __IExchangeClientDataItemArray_INTERFACE_DEFINED__
#define __IExchangeClientDataItemArray_INTERFACE_DEFINED__

/* interface IExchangeClientDataItemArray */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IExchangeClientDataItemArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32509779-AE83-42b2-B4D2-9E1BC2E7C70A")
    IExchangeClientDataItemArray : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetItemCount( 
            /* [retval][out] */ UINT __RPC_FAR *pcItems) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItemAt( 
            /* [in] */ UINT idxItem,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppiItem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExchangeClientDataItemArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExchangeClientDataItemArray __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExchangeClientDataItemArray __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExchangeClientDataItemArray __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetItemCount )( 
            IExchangeClientDataItemArray __RPC_FAR * This,
            /* [retval][out] */ UINT __RPC_FAR *pcItems);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetItemAt )( 
            IExchangeClientDataItemArray __RPC_FAR * This,
            /* [in] */ UINT idxItem,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppiItem);
        
        END_INTERFACE
    } IExchangeClientDataItemArrayVtbl;

    interface IExchangeClientDataItemArray
    {
        CONST_VTBL struct IExchangeClientDataItemArrayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExchangeClientDataItemArray_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExchangeClientDataItemArray_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExchangeClientDataItemArray_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExchangeClientDataItemArray_GetItemCount(This,pcItems)	\
    (This)->lpVtbl -> GetItemCount(This,pcItems)

#define IExchangeClientDataItemArray_GetItemAt(This,idxItem,ppiItem)	\
    (This)->lpVtbl -> GetItemAt(This,idxItem,ppiItem)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IExchangeClientDataItemArray_GetItemCount_Proxy( 
    IExchangeClientDataItemArray __RPC_FAR * This,
    /* [retval][out] */ UINT __RPC_FAR *pcItems);


void __RPC_STUB IExchangeClientDataItemArray_GetItemCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientDataItemArray_GetItemAt_Proxy( 
    IExchangeClientDataItemArray __RPC_FAR * This,
    /* [in] */ UINT idxItem,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppiItem);


void __RPC_STUB IExchangeClientDataItemArray_GetItemAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExchangeClientDataItemArray_INTERFACE_DEFINED__ */


#ifndef __IExchangeClientContactInformation_INTERFACE_DEFINED__
#define __IExchangeClientContactInformation_INTERFACE_DEFINED__

/* interface IExchangeClientContactInformation */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IExchangeClientContactInformation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4B9E0608-AA6A-4127-97E4-7892F5CFBE20")
    IExchangeClientContactInformation : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDisplayName( 
            /* [out] */ WCHAR __RPC_FAR *wszNameBuffer,
            /* [in] */ UINT cchNameBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHomePhoneNumber( 
            /* [out] */ WCHAR __RPC_FAR *wszNumberBuffer,
            /* [in] */ UINT cchNumberBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWorkPhoneNumber( 
            /* [out] */ WCHAR __RPC_FAR *wszBuffer,
            /* [in] */ UINT cchBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMobilePhoneNumber( 
            /* [out] */ WCHAR __RPC_FAR *wszBuffer,
            /* [in] */ UINT cchBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEmailAddress( 
            /* [out] */ WCHAR __RPC_FAR *wszBuffer,
            /* [in] */ UINT cchBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHomeAddress( 
            /* [out] */ WCHAR __RPC_FAR *wszBuffer,
            /* [in] */ UINT cchBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWorkAddress( 
            /* [out] */ WCHAR __RPC_FAR *wszBuffer,
            /* [in] */ UINT cchBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExchangeClientContactInformationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExchangeClientContactInformation __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExchangeClientContactInformation __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExchangeClientContactInformation __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDisplayName )( 
            IExchangeClientContactInformation __RPC_FAR * This,
            /* [out] */ WCHAR __RPC_FAR *wszNameBuffer,
            /* [in] */ UINT cchNameBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHomePhoneNumber )( 
            IExchangeClientContactInformation __RPC_FAR * This,
            /* [out] */ WCHAR __RPC_FAR *wszNumberBuffer,
            /* [in] */ UINT cchNumberBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWorkPhoneNumber )( 
            IExchangeClientContactInformation __RPC_FAR * This,
            /* [out] */ WCHAR __RPC_FAR *wszBuffer,
            /* [in] */ UINT cchBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMobilePhoneNumber )( 
            IExchangeClientContactInformation __RPC_FAR * This,
            /* [out] */ WCHAR __RPC_FAR *wszBuffer,
            /* [in] */ UINT cchBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEmailAddress )( 
            IExchangeClientContactInformation __RPC_FAR * This,
            /* [out] */ WCHAR __RPC_FAR *wszBuffer,
            /* [in] */ UINT cchBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHomeAddress )( 
            IExchangeClientContactInformation __RPC_FAR * This,
            /* [out] */ WCHAR __RPC_FAR *wszBuffer,
            /* [in] */ UINT cchBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWorkAddress )( 
            IExchangeClientContactInformation __RPC_FAR * This,
            /* [out] */ WCHAR __RPC_FAR *wszBuffer,
            /* [in] */ UINT cchBuffer);
        
        END_INTERFACE
    } IExchangeClientContactInformationVtbl;

    interface IExchangeClientContactInformation
    {
        CONST_VTBL struct IExchangeClientContactInformationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExchangeClientContactInformation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExchangeClientContactInformation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExchangeClientContactInformation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExchangeClientContactInformation_GetDisplayName(This,wszNameBuffer,cchNameBuffer)	\
    (This)->lpVtbl -> GetDisplayName(This,wszNameBuffer,cchNameBuffer)

#define IExchangeClientContactInformation_GetHomePhoneNumber(This,wszNumberBuffer,cchNumberBuffer)	\
    (This)->lpVtbl -> GetHomePhoneNumber(This,wszNumberBuffer,cchNumberBuffer)

#define IExchangeClientContactInformation_GetWorkPhoneNumber(This,wszBuffer,cchBuffer)	\
    (This)->lpVtbl -> GetWorkPhoneNumber(This,wszBuffer,cchBuffer)

#define IExchangeClientContactInformation_GetMobilePhoneNumber(This,wszBuffer,cchBuffer)	\
    (This)->lpVtbl -> GetMobilePhoneNumber(This,wszBuffer,cchBuffer)

#define IExchangeClientContactInformation_GetEmailAddress(This,wszBuffer,cchBuffer)	\
    (This)->lpVtbl -> GetEmailAddress(This,wszBuffer,cchBuffer)

#define IExchangeClientContactInformation_GetHomeAddress(This,wszBuffer,cchBuffer)	\
    (This)->lpVtbl -> GetHomeAddress(This,wszBuffer,cchBuffer)

#define IExchangeClientContactInformation_GetWorkAddress(This,wszBuffer,cchBuffer)	\
    (This)->lpVtbl -> GetWorkAddress(This,wszBuffer,cchBuffer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IExchangeClientContactInformation_GetDisplayName_Proxy( 
    IExchangeClientContactInformation __RPC_FAR * This,
    /* [out] */ WCHAR __RPC_FAR *wszNameBuffer,
    /* [in] */ UINT cchNameBuffer);


void __RPC_STUB IExchangeClientContactInformation_GetDisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientContactInformation_GetHomePhoneNumber_Proxy( 
    IExchangeClientContactInformation __RPC_FAR * This,
    /* [out] */ WCHAR __RPC_FAR *wszNumberBuffer,
    /* [in] */ UINT cchNumberBuffer);


void __RPC_STUB IExchangeClientContactInformation_GetHomePhoneNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientContactInformation_GetWorkPhoneNumber_Proxy( 
    IExchangeClientContactInformation __RPC_FAR * This,
    /* [out] */ WCHAR __RPC_FAR *wszBuffer,
    /* [in] */ UINT cchBuffer);


void __RPC_STUB IExchangeClientContactInformation_GetWorkPhoneNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientContactInformation_GetMobilePhoneNumber_Proxy( 
    IExchangeClientContactInformation __RPC_FAR * This,
    /* [out] */ WCHAR __RPC_FAR *wszBuffer,
    /* [in] */ UINT cchBuffer);


void __RPC_STUB IExchangeClientContactInformation_GetMobilePhoneNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientContactInformation_GetEmailAddress_Proxy( 
    IExchangeClientContactInformation __RPC_FAR * This,
    /* [out] */ WCHAR __RPC_FAR *wszBuffer,
    /* [in] */ UINT cchBuffer);


void __RPC_STUB IExchangeClientContactInformation_GetEmailAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientContactInformation_GetHomeAddress_Proxy( 
    IExchangeClientContactInformation __RPC_FAR * This,
    /* [out] */ WCHAR __RPC_FAR *wszBuffer,
    /* [in] */ UINT cchBuffer);


void __RPC_STUB IExchangeClientContactInformation_GetHomeAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientContactInformation_GetWorkAddress_Proxy( 
    IExchangeClientContactInformation __RPC_FAR * This,
    /* [out] */ WCHAR __RPC_FAR *wszBuffer,
    /* [in] */ UINT cchBuffer);


void __RPC_STUB IExchangeClientContactInformation_GetWorkAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExchangeClientContactInformation_INTERFACE_DEFINED__ */


#ifndef __IExchangeClientGALSearchInformation_INTERFACE_DEFINED__
#define __IExchangeClientGALSearchInformation_INTERFACE_DEFINED__

/* interface IExchangeClientGALSearchInformation */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IExchangeClientGALSearchInformation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CD5E6AE0-17EE-4c4a-9273-A7D60B59170D")
    IExchangeClientGALSearchInformation : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDisplayName( 
            WCHAR __RPC_FAR *wszNameBuffer,
            UINT cchNameBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPhoneNumber( 
            WCHAR __RPC_FAR *wszNumberBuffer,
            UINT cchNumberBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAlias( 
            WCHAR __RPC_FAR *wszBuffer,
            UINT cchBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOffice( 
            WCHAR __RPC_FAR *wszBuffer,
            UINT cchBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSMTPAddress( 
            WCHAR __RPC_FAR *wszBuffer,
            UINT cchBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExchangeClientGALSearchInformationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExchangeClientGALSearchInformation __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExchangeClientGALSearchInformation __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExchangeClientGALSearchInformation __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDisplayName )( 
            IExchangeClientGALSearchInformation __RPC_FAR * This,
            WCHAR __RPC_FAR *wszNameBuffer,
            UINT cchNameBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPhoneNumber )( 
            IExchangeClientGALSearchInformation __RPC_FAR * This,
            WCHAR __RPC_FAR *wszNumberBuffer,
            UINT cchNumberBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlias )( 
            IExchangeClientGALSearchInformation __RPC_FAR * This,
            WCHAR __RPC_FAR *wszBuffer,
            UINT cchBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOffice )( 
            IExchangeClientGALSearchInformation __RPC_FAR * This,
            WCHAR __RPC_FAR *wszBuffer,
            UINT cchBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSMTPAddress )( 
            IExchangeClientGALSearchInformation __RPC_FAR * This,
            WCHAR __RPC_FAR *wszBuffer,
            UINT cchBuffer);
        
        END_INTERFACE
    } IExchangeClientGALSearchInformationVtbl;

    interface IExchangeClientGALSearchInformation
    {
        CONST_VTBL struct IExchangeClientGALSearchInformationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExchangeClientGALSearchInformation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExchangeClientGALSearchInformation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExchangeClientGALSearchInformation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExchangeClientGALSearchInformation_GetDisplayName(This,wszNameBuffer,cchNameBuffer)	\
    (This)->lpVtbl -> GetDisplayName(This,wszNameBuffer,cchNameBuffer)

#define IExchangeClientGALSearchInformation_GetPhoneNumber(This,wszNumberBuffer,cchNumberBuffer)	\
    (This)->lpVtbl -> GetPhoneNumber(This,wszNumberBuffer,cchNumberBuffer)

#define IExchangeClientGALSearchInformation_GetAlias(This,wszBuffer,cchBuffer)	\
    (This)->lpVtbl -> GetAlias(This,wszBuffer,cchBuffer)

#define IExchangeClientGALSearchInformation_GetOffice(This,wszBuffer,cchBuffer)	\
    (This)->lpVtbl -> GetOffice(This,wszBuffer,cchBuffer)

#define IExchangeClientGALSearchInformation_GetSMTPAddress(This,wszBuffer,cchBuffer)	\
    (This)->lpVtbl -> GetSMTPAddress(This,wszBuffer,cchBuffer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IExchangeClientGALSearchInformation_GetDisplayName_Proxy( 
    IExchangeClientGALSearchInformation __RPC_FAR * This,
    WCHAR __RPC_FAR *wszNameBuffer,
    UINT cchNameBuffer);


void __RPC_STUB IExchangeClientGALSearchInformation_GetDisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientGALSearchInformation_GetPhoneNumber_Proxy( 
    IExchangeClientGALSearchInformation __RPC_FAR * This,
    WCHAR __RPC_FAR *wszNumberBuffer,
    UINT cchNumberBuffer);


void __RPC_STUB IExchangeClientGALSearchInformation_GetPhoneNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientGALSearchInformation_GetAlias_Proxy( 
    IExchangeClientGALSearchInformation __RPC_FAR * This,
    WCHAR __RPC_FAR *wszBuffer,
    UINT cchBuffer);


void __RPC_STUB IExchangeClientGALSearchInformation_GetAlias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientGALSearchInformation_GetOffice_Proxy( 
    IExchangeClientGALSearchInformation __RPC_FAR * This,
    WCHAR __RPC_FAR *wszBuffer,
    UINT cchBuffer);


void __RPC_STUB IExchangeClientGALSearchInformation_GetOffice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientGALSearchInformation_GetSMTPAddress_Proxy( 
    IExchangeClientGALSearchInformation __RPC_FAR * This,
    WCHAR __RPC_FAR *wszBuffer,
    UINT cchBuffer);


void __RPC_STUB IExchangeClientGALSearchInformation_GetSMTPAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExchangeClientGALSearchInformation_INTERFACE_DEFINED__ */


#ifndef __IExchangeClientFreeBusyInformation_INTERFACE_DEFINED__
#define __IExchangeClientFreeBusyInformation_INTERFACE_DEFINED__

/* interface IExchangeClientFreeBusyInformation */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IExchangeClientFreeBusyInformation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4E53FD7-C940-4f87-8634-5EB97DBA0C2E")
    IExchangeClientFreeBusyInformation : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetEmailAddress( 
            WCHAR __RPC_FAR *wszAddressBuffer,
            UINT cchAddressBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDisplayName( 
            WCHAR __RPC_FAR *wszNameBuffer,
            UINT cchNameBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFreeBusyData( 
            WCHAR __RPC_FAR *wszDataBuffer,
            UINT cchDataBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExchangeClientFreeBusyInformationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExchangeClientFreeBusyInformation __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExchangeClientFreeBusyInformation __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExchangeClientFreeBusyInformation __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEmailAddress )( 
            IExchangeClientFreeBusyInformation __RPC_FAR * This,
            WCHAR __RPC_FAR *wszAddressBuffer,
            UINT cchAddressBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDisplayName )( 
            IExchangeClientFreeBusyInformation __RPC_FAR * This,
            WCHAR __RPC_FAR *wszNameBuffer,
            UINT cchNameBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFreeBusyData )( 
            IExchangeClientFreeBusyInformation __RPC_FAR * This,
            WCHAR __RPC_FAR *wszDataBuffer,
            UINT cchDataBuffer);
        
        END_INTERFACE
    } IExchangeClientFreeBusyInformationVtbl;

    interface IExchangeClientFreeBusyInformation
    {
        CONST_VTBL struct IExchangeClientFreeBusyInformationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExchangeClientFreeBusyInformation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExchangeClientFreeBusyInformation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExchangeClientFreeBusyInformation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExchangeClientFreeBusyInformation_GetEmailAddress(This,wszAddressBuffer,cchAddressBuffer)	\
    (This)->lpVtbl -> GetEmailAddress(This,wszAddressBuffer,cchAddressBuffer)

#define IExchangeClientFreeBusyInformation_GetDisplayName(This,wszNameBuffer,cchNameBuffer)	\
    (This)->lpVtbl -> GetDisplayName(This,wszNameBuffer,cchNameBuffer)

#define IExchangeClientFreeBusyInformation_GetFreeBusyData(This,wszDataBuffer,cchDataBuffer)	\
    (This)->lpVtbl -> GetFreeBusyData(This,wszDataBuffer,cchDataBuffer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IExchangeClientFreeBusyInformation_GetEmailAddress_Proxy( 
    IExchangeClientFreeBusyInformation __RPC_FAR * This,
    WCHAR __RPC_FAR *wszAddressBuffer,
    UINT cchAddressBuffer);


void __RPC_STUB IExchangeClientFreeBusyInformation_GetEmailAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientFreeBusyInformation_GetDisplayName_Proxy( 
    IExchangeClientFreeBusyInformation __RPC_FAR * This,
    WCHAR __RPC_FAR *wszNameBuffer,
    UINT cchNameBuffer);


void __RPC_STUB IExchangeClientFreeBusyInformation_GetDisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExchangeClientFreeBusyInformation_GetFreeBusyData_Proxy( 
    IExchangeClientFreeBusyInformation __RPC_FAR * This,
    WCHAR __RPC_FAR *wszDataBuffer,
    UINT cchDataBuffer);


void __RPC_STUB IExchangeClientFreeBusyInformation_GetFreeBusyData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExchangeClientFreeBusyInformation_INTERFACE_DEFINED__ */



#ifndef __EXCHANGECLIENTLib_LIBRARY_DEFINED__
#define __EXCHANGECLIENTLib_LIBRARY_DEFINED__

/* library EXCHANGECLIENTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EXCHANGECLIENTLib;

EXTERN_C const CLSID CLSID_ExchangeClient;

#ifdef __cplusplus

class DECLSPEC_UUID("D963ECEB-B81A-4d5f-89A4-5C7C024AFEDF")
ExchangeClient;
#endif
#endif /* __EXCHANGECLIENTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


