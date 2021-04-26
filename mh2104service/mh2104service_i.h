

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for mh2104service.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __mh2104service_i_h__
#define __mh2104service_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ImhReboot_FWD_DEFINED__
#define __ImhReboot_FWD_DEFINED__
typedef interface ImhReboot ImhReboot;

#endif 	/* __ImhReboot_FWD_DEFINED__ */


#ifndef __ImhPolicy_FWD_DEFINED__
#define __ImhPolicy_FWD_DEFINED__
typedef interface ImhPolicy ImhPolicy;

#endif 	/* __ImhPolicy_FWD_DEFINED__ */


#ifndef __ImhComputerInfo_FWD_DEFINED__
#define __ImhComputerInfo_FWD_DEFINED__
typedef interface ImhComputerInfo ImhComputerInfo;

#endif 	/* __ImhComputerInfo_FWD_DEFINED__ */


#ifndef __mhReboot_FWD_DEFINED__
#define __mhReboot_FWD_DEFINED__

#ifdef __cplusplus
typedef class mhReboot mhReboot;
#else
typedef struct mhReboot mhReboot;
#endif /* __cplusplus */

#endif 	/* __mhReboot_FWD_DEFINED__ */


#ifndef __mhPolicy_FWD_DEFINED__
#define __mhPolicy_FWD_DEFINED__

#ifdef __cplusplus
typedef class mhPolicy mhPolicy;
#else
typedef struct mhPolicy mhPolicy;
#endif /* __cplusplus */

#endif 	/* __mhPolicy_FWD_DEFINED__ */


#ifndef __mhComputerInfo_FWD_DEFINED__
#define __mhComputerInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class mhComputerInfo mhComputerInfo;
#else
typedef struct mhComputerInfo mhComputerInfo;
#endif /* __cplusplus */

#endif 	/* __mhComputerInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ImhReboot_INTERFACE_DEFINED__
#define __ImhReboot_INTERFACE_DEFINED__

/* interface ImhReboot */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ImhReboot;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f4a92b01-c0a5-45ec-93c4-674b4a0b4121")
    ImhReboot : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DoReboot( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ImhRebootVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ImhReboot * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ImhReboot * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ImhReboot * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ImhReboot * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ImhReboot * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ImhReboot * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ImhReboot * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DoReboot )( 
            ImhReboot * This);
        
        END_INTERFACE
    } ImhRebootVtbl;

    interface ImhReboot
    {
        CONST_VTBL struct ImhRebootVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ImhReboot_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ImhReboot_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ImhReboot_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ImhReboot_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ImhReboot_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ImhReboot_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ImhReboot_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ImhReboot_DoReboot(This)	\
    ( (This)->lpVtbl -> DoReboot(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ImhReboot_INTERFACE_DEFINED__ */


#ifndef __ImhPolicy_INTERFACE_DEFINED__
#define __ImhPolicy_INTERFACE_DEFINED__

/* interface ImhPolicy */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ImhPolicy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a8e3b238-b997-475e-8cff-ca0f0c9da59c")
    ImhPolicy : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ClearCameraPolicy( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetCameraPolicy( 
            /* [in] */ LONG lAllowCamera) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ClearPasswordPolicy( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetPasswordPolicy( 
            /* [in] */ LONG lAllowSimpleDevicePassword,
            /* [in] */ LONG lAlphanumericDevicePasswordRequired,
            /* [in] */ LONG lDevicePasswordEnabled,
            /* [in] */ LONG lMinDevicePasswordComplexCharacters,
            /* [in] */ LONG lMinDevicePasswordLength) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ImhPolicyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ImhPolicy * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ImhPolicy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ImhPolicy * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ImhPolicy * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ImhPolicy * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ImhPolicy * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ImhPolicy * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ClearCameraPolicy )( 
            ImhPolicy * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetCameraPolicy )( 
            ImhPolicy * This,
            /* [in] */ LONG lAllowCamera);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ClearPasswordPolicy )( 
            ImhPolicy * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetPasswordPolicy )( 
            ImhPolicy * This,
            /* [in] */ LONG lAllowSimpleDevicePassword,
            /* [in] */ LONG lAlphanumericDevicePasswordRequired,
            /* [in] */ LONG lDevicePasswordEnabled,
            /* [in] */ LONG lMinDevicePasswordComplexCharacters,
            /* [in] */ LONG lMinDevicePasswordLength);
        
        END_INTERFACE
    } ImhPolicyVtbl;

    interface ImhPolicy
    {
        CONST_VTBL struct ImhPolicyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ImhPolicy_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ImhPolicy_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ImhPolicy_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ImhPolicy_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ImhPolicy_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ImhPolicy_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ImhPolicy_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ImhPolicy_ClearCameraPolicy(This)	\
    ( (This)->lpVtbl -> ClearCameraPolicy(This) ) 

#define ImhPolicy_SetCameraPolicy(This,lAllowCamera)	\
    ( (This)->lpVtbl -> SetCameraPolicy(This,lAllowCamera) ) 

#define ImhPolicy_ClearPasswordPolicy(This)	\
    ( (This)->lpVtbl -> ClearPasswordPolicy(This) ) 

#define ImhPolicy_SetPasswordPolicy(This,lAllowSimpleDevicePassword,lAlphanumericDevicePasswordRequired,lDevicePasswordEnabled,lMinDevicePasswordComplexCharacters,lMinDevicePasswordLength)	\
    ( (This)->lpVtbl -> SetPasswordPolicy(This,lAllowSimpleDevicePassword,lAlphanumericDevicePasswordRequired,lDevicePasswordEnabled,lMinDevicePasswordComplexCharacters,lMinDevicePasswordLength) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ImhPolicy_INTERFACE_DEFINED__ */


#ifndef __ImhComputerInfo_INTERFACE_DEFINED__
#define __ImhComputerInfo_INTERFACE_DEFINED__

/* interface ImhComputerInfo */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ImhComputerInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("81f513b3-a1ef-4570-a3c5-601482f09021")
    ImhComputerInfo : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetInfo( 
            /* [out] */ BSTR *str) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ImhComputerInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ImhComputerInfo * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ImhComputerInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ImhComputerInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ImhComputerInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ImhComputerInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ImhComputerInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ImhComputerInfo * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetInfo )( 
            ImhComputerInfo * This,
            /* [out] */ BSTR *str);
        
        END_INTERFACE
    } ImhComputerInfoVtbl;

    interface ImhComputerInfo
    {
        CONST_VTBL struct ImhComputerInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ImhComputerInfo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ImhComputerInfo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ImhComputerInfo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ImhComputerInfo_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ImhComputerInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ImhComputerInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ImhComputerInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ImhComputerInfo_GetInfo(This,str)	\
    ( (This)->lpVtbl -> GetInfo(This,str) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ImhComputerInfo_INTERFACE_DEFINED__ */



#ifndef __mh2104serviceLib_LIBRARY_DEFINED__
#define __mh2104serviceLib_LIBRARY_DEFINED__

/* library mh2104serviceLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_mh2104serviceLib;

EXTERN_C const CLSID CLSID_mhReboot;

#ifdef __cplusplus

class DECLSPEC_UUID("1280c50b-536f-4a45-9527-f2807358eca5")
mhReboot;
#endif

EXTERN_C const CLSID CLSID_mhPolicy;

#ifdef __cplusplus

class DECLSPEC_UUID("33ab6359-e350-4d37-a32a-2cc107b02421")
mhPolicy;
#endif

EXTERN_C const CLSID CLSID_mhComputerInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("77136b31-f3e9-4153-874b-206aa20245a2")
mhComputerInfo;
#endif
#endif /* __mh2104serviceLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


