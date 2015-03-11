/*
	DESCRIPTION

	The intention with this sample is more to illustrate the concepts and provide a working example.
	It does not necessarily use all of the latest technology and other boiler-plate, error-handling,
	thread-safe code that you might want to use. So, treat this more as an advanced  starting point.

	This file contains the functions that deal with the DLL as a whole. Some of them are exported
	to the external world and others are used to keep track of the state of the DLL as far is it's
	usage is concerned.


	BRIEF EXPLANATION

	More importantly, this file contains the one function that becomes the single entry point for a
	client (Autodesk Inventor (R)) to use in order to get at the functionality encapsulated inside. The immediate client,
	in most cases, is the intermediary -- COM runtime library, acting on behalf of the Client
	which usually is the caller of the CoCreateInstance function. The function is the DllGetClassObject.
	Via the DllGetClassObject, the clients get hold of the various class factories that in turn create
	the actual objects of interest -- in this DLL.

	Another exported function is the DllCanUnloadNow. This function is called by the system periodically,
	to check if the memory resource being used for the DLL can be freed if none of the parts of the DLL
	are currently in use.

	Other functions are for internal book-keeping, serving to give the correct answer when
	the question is asked whether the DLL can unload. These are not exported. The various COM objects
	supported in here, use these functions to keep up the count of objects that are currently in use
	by clients. A ref-counter on the DLL itself is provided. This is mainly used by the
	IClassFactory::LockServer method, probably called by the COM Runtime.

*/

#include "stdafx.h"

#include "translator.h"
#include "rxtranslator.h"

#include "guids.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/*-------------------------- CTranslatorApp ------------------------------------------*/

BEGIN_MESSAGE_MAP(CTranslatorApp, CWinApp)
	//{{AFX_MSG_MAP(CTranslatorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTranslatorApp construction

CTranslatorApp::CTranslatorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTranslatorApp object

CTranslatorApp theApp;


// Hold this DLL's instance handle for outside access

static HINSTANCE s_hModule = NULL;

BOOL CTranslatorApp::InitInstance()
{
	s_hModule = m_hInstance;
	return CWinApp::InitInstance();
}

/*------------------------ CTranslatorFactory -----------------------------------*/

/*
 * This class factory is used by COM to create an object of class CTranslator
 * via its CreateInstance method. The CTranslator is the object with which Autodesk Inventor (R) establishes
 * initial contact using the IRxApplicationAddInServer interface that it MUST support.
 */

STDMETHODIMP CTranslatorFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	OnErrorReturn(!ppv, E_INVALIDARG);
	*ppv = NULL;

	// The semantics of this method is that the target object cannot be aggregated in.
	OnErrorReturn(pUnkOuter, CLASS_E_NOAGGREGATION);

	// Create the Application AddIns controller object

	CRxTranslator* pTranslator = new CRxTranslator();
	OnErrorReturn(!pTranslator, E_OUTOFMEMORY);

	// Now QI for the requested interface and return as is.

	HRESULT hr = pTranslator->QueryInterface(riid, ppv);
	if (FAILED(hr))
		delete pTranslator;
	return hr;
}

STDMETHODIMP CTranslatorFactory::LockServer(BOOL fLock)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (fLock)
		IncrementDllLocks();
	else
		DecrementDllLocks();

	return S_OK;
}

// IUnknown interface methods

STDMETHODIMP CTranslatorFactory::QueryInterface(REFIID riid, void** ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	OnErrorReturn(!ppv, E_INVALIDARG);
	*ppv = NULL;

	if (IsEqualIID(riid, IID_IUnknown) ||
	    IsEqualIID(riid, IID_IClassFactory))
		*ppv = static_cast<IClassFactory*>(this);

	if (*ppv)
		static_cast<IUnknown*>(*ppv)->AddRef();

	return *ppv ? S_OK : E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) CTranslatorFactory::AddRef()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CTranslatorFactory::Release()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	ULONG cRef = --m_cRef;
	if(!m_cRef)
		delete this;
	return cRef;
}

// Constructor(s) and destructor

CTranslatorFactory::CTranslatorFactory()
{
	m_cRef = 0;
	::IncrementObjectCount();
}

CTranslatorFactory::~CTranslatorFactory()
{
	::DecrementObjectCount();
}

/*------------------------------- DLL Exported functions ----------------------------------------*/

/*
 * This function returns the class-factory object that would in turn create objects of the
 * specified class ('rClsid', registered in the system's registry at install time, identifies
 * the COM-object). The interface that the caller (quite often the COM API --
 * CoCreateInstance) is looking for on this object, is specified in 'riid'. The class factory
 * must support IClassFactory and of course, IUnknown.
 */

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	OnErrorReturn(!ppv, E_INVALIDARG);
	*ppv = NULL;

	// Check for supported class id.
	//
	OnErrorReturn(!IsEqualCLSID(rclsid, CLSID_ModelicaTrans), E_INVALIDARG);

	// Check for supported interfaces (only IClassFactory and IUnknown). If not supported
	// return error.
	OnErrorReturn(!IsEqualIID(riid, IID_IUnknown) &&
		!IsEqualIID(riid, IID_IClassFactory), E_NOINTERFACE);

	*ppv = static_cast<IClassFactory*>(new CTranslatorFactory());
	OnErrorReturn(!*ppv, E_OUTOFMEMORY);

	static_cast<IUnknown*>(*ppv)->AddRef();

	return S_OK;
}

/*
 * This exported function simply returns an S_FALSE or an S_OK, depending on whether
 * the DLL is currently being used (a client is using an object of this DLL) or not.
 * This is known by looking up the reference count on the objects created in here
 * and not yet released.
 */

STDAPI DllCanUnloadNow()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	return ObjectCount() || DllLocks() ? S_FALSE : S_OK;
}

/*----------------------- DLL internal functions that manage the DLL --------------------------------------*/

/*
 * Variable keeping a count of the number of objects in use. C++ initialized to 0!
 * Below are the functions that update or read this number.
 */

static ULONG nObjects;
static ULONG nDllLocks;

void IncrementObjectCount()
{
	++nObjects;
}

void DecrementObjectCount()
{
	--nObjects;
}

ULONG ObjectCount()
{
	return nObjects;
}

void IncrementDllLocks()
{
	++nDllLocks;
}

void DecrementDllLocks()
{
	--nDllLocks;
}

ULONG DllLocks()
{
	return nDllLocks;
}
