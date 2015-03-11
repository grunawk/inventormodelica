/*
  DESCRIPTION
  
  This is the first-level header file for the DLL. It declares the primary CWinApp
  object (that serves to initialize and close out the DLL). More impotantly, it contains
  the description of the COM Class Factory which is used by COM to start up this DLL
  and dole out objects from within it.

*/

#if !defined(AFX_TRANSLATOR_H__246084EC_F374_11D3_853D_0060B0F0B5B7__INCLUDED_)
#define AFX_TRANSLATOR_H__246084EC_F374_11D3_853D_0060B0F0B5B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/*--------------------- CTranslatorApp class declaration -------------------------------*/

class CTranslatorApp : public CWinApp
{
public:
	CTranslatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTranslatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTranslatorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/*--------------------- CTranslatorFactory class declaration -------------------------------*/

/*
 * The COM Class Factory class that is used by COM at CoCreation time to create the
 * CTranslator object through its CreateInstance method. The CTranslator object
 * is the object that is the first point of communication with Autodesk Inventor (R).
 */

class CTranslatorFactory : public IClassFactory
{
  // IUnknown interface methods and supporting member data.
  protected:
    ULONG m_cRef;

  public:
    STDMETHOD (QueryInterface) (REFIID riid, LPVOID FAR *ppvObj);
    STDMETHOD_ (ULONG, AddRef) ();
    STDMETHOD_ (ULONG, Release) ();

  // Contructor(s) and destructors.    
  public:
    CTranslatorFactory ();
    ~CTranslatorFactory ();

  // IClassFactory interface methods
  public:
    STDMETHOD (CreateInstance) (LPUNKNOWN pUnkOuter, REFIID riid, LPVOID *ppvObj);
    STDMETHOD (LockServer) (BOOL);
};


/*--------------------- Global function declarations -------------------------------*/

/*
 * Prototypes of exported functions. These are functions known to COM and are used
 * in the outside management of the DLL
 */

STDAPI DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv);
STDAPI DllCanUnloadNow ();

/*
 * Prototypes of global functions that control the DLL's lifetime. These functions are
 * called whenever objects are created/destroyed by Clients and additional locks are
 * placed on the DLL. Through the reference count maintenance done by these functions,
 * the DLL knows at any time if it can be unloaded.
 */

void IncrementObjectCount();
void DecrementObjectCount();
ULONG ObjectCount();

void IncrementDllLocks ();
void DecrementDllLocks ();
ULONG DllLocks();

/*--------------------- MFC AppWizard gobbledegook -------------------------------*/

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSLATOR_H__246084EC_F374_11D3_853D_0060B0F0B5B7__INCLUDED_)
