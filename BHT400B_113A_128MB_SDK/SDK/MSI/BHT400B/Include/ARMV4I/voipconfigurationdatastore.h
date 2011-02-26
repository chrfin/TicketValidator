
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Wed Feb 20 14:02:58 2008
 */
/* Compiler settings for .\voipconfigurationdatastore.idl:
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

#ifndef __voipconfigurationdatastore_h__
#define __voipconfigurationdatastore_h__

/* Forward Declarations */ 

#ifndef __IVoIPConfigurationDataStore_FWD_DEFINED__
#define __IVoIPConfigurationDataStore_FWD_DEFINED__
typedef interface IVoIPConfigurationDataStore IVoIPConfigurationDataStore;
#endif 	/* __IVoIPConfigurationDataStore_FWD_DEFINED__ */


#ifndef __VoIPConfigurationDataStore_FWD_DEFINED__
#define __VoIPConfigurationDataStore_FWD_DEFINED__

#ifdef __cplusplus
typedef class VoIPConfigurationDataStore VoIPConfigurationDataStore;
#else
typedef struct VoIPConfigurationDataStore VoIPConfigurationDataStore;
#endif /* __cplusplus */

#endif 	/* __VoIPConfigurationDataStore_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_voipconfigurationdatastore_0000 */
/* [local] */ 

#define	CONFIG_DATA_PHONE_INFO_USERNAME	( 0x1 )

#define	CONFIG_DATA_PHONE_INFO_AREACODES	( 0x2 )

#define	CONFIG_DATA_PHONE_INFO_VOICEMAIL	( 0x4 )

#define	CONFIG_DATA_PHONE_INFO_DIALOUTPREFIX	( 0x8 )

#define	CONFIG_DATA_PHONE_SIP_URI	( 0x10 )

#define	CONFIG_DATA_PHONE_SIP_SERVER	( 0x20 )

#define	CONFIG_DATA_PHONE_SIP_TRANSPORT	( 0x40 )

#define	CONFIG_DATA_PHONE_SIP_AUTHTYPE	( 0x80 )

#define	CONFIG_DATA_PHONE_SIP_ACCOUNT	( 0x100 )

#define	CONFIG_DATA_EXCHANGE_OWASERVER	( 0x200 )

#define	CONFIG_DATA_EXCHANGE_HTTPPROXY	( 0x400 )

#define	CONFIG_DATA_PRESENCE_URI	( 0x800 )

#define	CONFIG_DATA_PRESENCE_SERVER	( 0x1000 )

#define	CONFIG_DATA_UPDATE_SMSSERVER	( 0x2000 )

#define	CONFIG_DATA_ALL	( 0x3fff )



extern RPC_IF_HANDLE __MIDL_itf_voipconfigurationdatastore_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_voipconfigurationdatastore_0000_v0_0_s_ifspec;

#ifndef __IVoIPConfigurationDataStore_INTERFACE_DEFINED__
#define __IVoIPConfigurationDataStore_INTERFACE_DEFINED__

/* interface IVoIPConfigurationDataStore */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVoIPConfigurationDataStore;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("39D6E331-EE5B-44bb-A7A9-DF462214B2EE")
    IVoIPConfigurationDataStore : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Uninitialize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteValue( 
            UINT fWhichItem,
            const WCHAR __RPC_FAR *c_wszNewValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadValue( 
            UINT fWhichItem,
            WCHAR __RPC_FAR *wszDataBuffer,
            UINT cchDataBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateSettingsFromXML( 
            const WCHAR __RPC_FAR *c_wszXML,
            UINT fSettingsToUpdate,
            UINT __RPC_FAR *pfUpdatedSettings) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateSettingsFromFile( 
            const WCHAR __RPC_FAR *c_wszFileName,
            UINT fSettingsToUpdate,
            UINT __RPC_FAR *pfUpdatedSettings) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateSettingsFromServer( 
            const WCHAR __RPC_FAR *c_wszServerName,
            WCHAR __RPC_FAR *ldap_cred,
            ULONG ldap_method,
            UINT fSettingsToUpdate,
            UINT __RPC_FAR *pfUpdatedSettings) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVoIPConfigurationDataStoreVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVoIPConfigurationDataStore __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVoIPConfigurationDataStore __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVoIPConfigurationDataStore __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IVoIPConfigurationDataStore __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Uninitialize )( 
            IVoIPConfigurationDataStore __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteValue )( 
            IVoIPConfigurationDataStore __RPC_FAR * This,
            UINT fWhichItem,
            const WCHAR __RPC_FAR *c_wszNewValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadValue )( 
            IVoIPConfigurationDataStore __RPC_FAR * This,
            UINT fWhichItem,
            WCHAR __RPC_FAR *wszDataBuffer,
            UINT cchDataBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateSettingsFromXML )( 
            IVoIPConfigurationDataStore __RPC_FAR * This,
            const WCHAR __RPC_FAR *c_wszXML,
            UINT fSettingsToUpdate,
            UINT __RPC_FAR *pfUpdatedSettings);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateSettingsFromFile )( 
            IVoIPConfigurationDataStore __RPC_FAR * This,
            const WCHAR __RPC_FAR *c_wszFileName,
            UINT fSettingsToUpdate,
            UINT __RPC_FAR *pfUpdatedSettings);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateSettingsFromServer )( 
            IVoIPConfigurationDataStore __RPC_FAR * This,
            const WCHAR __RPC_FAR *c_wszServerName,
            WCHAR __RPC_FAR *ldap_cred,
            ULONG ldap_method,
            UINT fSettingsToUpdate,
            UINT __RPC_FAR *pfUpdatedSettings);
        
        END_INTERFACE
    } IVoIPConfigurationDataStoreVtbl;

    interface IVoIPConfigurationDataStore
    {
        CONST_VTBL struct IVoIPConfigurationDataStoreVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVoIPConfigurationDataStore_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVoIPConfigurationDataStore_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVoIPConfigurationDataStore_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVoIPConfigurationDataStore_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IVoIPConfigurationDataStore_Uninitialize(This)	\
    (This)->lpVtbl -> Uninitialize(This)

#define IVoIPConfigurationDataStore_WriteValue(This,fWhichItem,c_wszNewValue)	\
    (This)->lpVtbl -> WriteValue(This,fWhichItem,c_wszNewValue)

#define IVoIPConfigurationDataStore_ReadValue(This,fWhichItem,wszDataBuffer,cchDataBuffer)	\
    (This)->lpVtbl -> ReadValue(This,fWhichItem,wszDataBuffer,cchDataBuffer)

#define IVoIPConfigurationDataStore_UpdateSettingsFromXML(This,c_wszXML,fSettingsToUpdate,pfUpdatedSettings)	\
    (This)->lpVtbl -> UpdateSettingsFromXML(This,c_wszXML,fSettingsToUpdate,pfUpdatedSettings)

#define IVoIPConfigurationDataStore_UpdateSettingsFromFile(This,c_wszFileName,fSettingsToUpdate,pfUpdatedSettings)	\
    (This)->lpVtbl -> UpdateSettingsFromFile(This,c_wszFileName,fSettingsToUpdate,pfUpdatedSettings)

#define IVoIPConfigurationDataStore_UpdateSettingsFromServer(This,c_wszServerName,ldap_cred,ldap_method,fSettingsToUpdate,pfUpdatedSettings)	\
    (This)->lpVtbl -> UpdateSettingsFromServer(This,c_wszServerName,ldap_cred,ldap_method,fSettingsToUpdate,pfUpdatedSettings)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVoIPConfigurationDataStore_Initialize_Proxy( 
    IVoIPConfigurationDataStore __RPC_FAR * This);


void __RPC_STUB IVoIPConfigurationDataStore_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPConfigurationDataStore_Uninitialize_Proxy( 
    IVoIPConfigurationDataStore __RPC_FAR * This);


void __RPC_STUB IVoIPConfigurationDataStore_Uninitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPConfigurationDataStore_WriteValue_Proxy( 
    IVoIPConfigurationDataStore __RPC_FAR * This,
    UINT fWhichItem,
    const WCHAR __RPC_FAR *c_wszNewValue);


void __RPC_STUB IVoIPConfigurationDataStore_WriteValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPConfigurationDataStore_ReadValue_Proxy( 
    IVoIPConfigurationDataStore __RPC_FAR * This,
    UINT fWhichItem,
    WCHAR __RPC_FAR *wszDataBuffer,
    UINT cchDataBuffer);


void __RPC_STUB IVoIPConfigurationDataStore_ReadValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPConfigurationDataStore_UpdateSettingsFromXML_Proxy( 
    IVoIPConfigurationDataStore __RPC_FAR * This,
    const WCHAR __RPC_FAR *c_wszXML,
    UINT fSettingsToUpdate,
    UINT __RPC_FAR *pfUpdatedSettings);


void __RPC_STUB IVoIPConfigurationDataStore_UpdateSettingsFromXML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPConfigurationDataStore_UpdateSettingsFromFile_Proxy( 
    IVoIPConfigurationDataStore __RPC_FAR * This,
    const WCHAR __RPC_FAR *c_wszFileName,
    UINT fSettingsToUpdate,
    UINT __RPC_FAR *pfUpdatedSettings);


void __RPC_STUB IVoIPConfigurationDataStore_UpdateSettingsFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVoIPConfigurationDataStore_UpdateSettingsFromServer_Proxy( 
    IVoIPConfigurationDataStore __RPC_FAR * This,
    const WCHAR __RPC_FAR *c_wszServerName,
    WCHAR __RPC_FAR *ldap_cred,
    ULONG ldap_method,
    UINT fSettingsToUpdate,
    UINT __RPC_FAR *pfUpdatedSettings);


void __RPC_STUB IVoIPConfigurationDataStore_UpdateSettingsFromServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVoIPConfigurationDataStore_INTERFACE_DEFINED__ */



#ifndef __VOIPCONFIGURATIONDATASTORELib_LIBRARY_DEFINED__
#define __VOIPCONFIGURATIONDATASTORELib_LIBRARY_DEFINED__

/* library VOIPCONFIGURATIONDATASTORELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VOIPCONFIGURATIONDATASTORELib;

EXTERN_C const CLSID CLSID_VoIPConfigurationDataStore;

#ifdef __cplusplus

class DECLSPEC_UUID("CF8C9CD9-638E-40ff-8A51-8131EB8F496B")
VoIPConfigurationDataStore;
#endif
#endif /* __VOIPCONFIGURATIONDATASTORELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


