

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for BaiduTranslate.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
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


#ifndef __BaiduTranslate_h_h__
#define __BaiduTranslate_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBaiduTranslate_FWD_DEFINED__
#define __IBaiduTranslate_FWD_DEFINED__
typedef interface IBaiduTranslate IBaiduTranslate;

#endif 	/* __IBaiduTranslate_FWD_DEFINED__ */


#ifndef __BaiduTranslate_FWD_DEFINED__
#define __BaiduTranslate_FWD_DEFINED__

#ifdef __cplusplus
typedef class BaiduTranslate BaiduTranslate;
#else
typedef struct BaiduTranslate BaiduTranslate;
#endif /* __cplusplus */

#endif 	/* __BaiduTranslate_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __BaiduTranslate_LIBRARY_DEFINED__
#define __BaiduTranslate_LIBRARY_DEFINED__

/* library BaiduTranslate */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_BaiduTranslate;

#ifndef __IBaiduTranslate_DISPINTERFACE_DEFINED__
#define __IBaiduTranslate_DISPINTERFACE_DEFINED__

/* dispinterface IBaiduTranslate */
/* [uuid] */ 


EXTERN_C const IID DIID_IBaiduTranslate;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CB83B94D-18B7-4034-9108-8593F6B27B55")
    IBaiduTranslate : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IBaiduTranslateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBaiduTranslate * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBaiduTranslate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBaiduTranslate * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBaiduTranslate * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBaiduTranslate * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBaiduTranslate * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBaiduTranslate * This,
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
        
        END_INTERFACE
    } IBaiduTranslateVtbl;

    interface IBaiduTranslate
    {
        CONST_VTBL struct IBaiduTranslateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBaiduTranslate_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBaiduTranslate_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBaiduTranslate_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBaiduTranslate_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBaiduTranslate_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBaiduTranslate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBaiduTranslate_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IBaiduTranslate_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_BaiduTranslate;

#ifdef __cplusplus

class DECLSPEC_UUID("CB6CECE9-433C-44EF-BF0A-28B333B997CF")
BaiduTranslate;
#endif
#endif /* __BaiduTranslate_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


