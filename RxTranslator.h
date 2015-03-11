/*
	DESCRIPTION

	This file contains the declaration of the class that defines the COM-object with which
	Autodesk Inventor (R) first communicates (supports the IRxApplicationAddInServer interface).

*/

#ifndef _RXTranslator_
#define _RXTranslator_

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "unknown.h"
#include "resource.h"


class CRxTranslator : public CUnknown, public IRxTranslatorAddInServer2
{
	// The IUnknown implementation is handled largely by CUnknown. We only have to re-direct the methods
	// by including the following macro. The QueryInterface gets implemented by this class overiding
	// the InternalQueryInterface.

	public:
		DECLARE_UNKNOWN;
		HRESULT InternalQueryInterface (REFIID iid, void **ppv);

	
	// Private data and public accessors

	private:
		CComPtr<IRxApplicationAddInSite>m_pSite;
		CComPtr<Application>m_pApplication;

		// Addin wizard adds definitions of commands here.


	public:
		// Return the Autodesk Inventor (R) Add-In Site of this object's attachment. Do NOT Release().
		IRxApplicationAddInSite* Site()
		 { return m_pSite; }

		// Return the Autodesk Inventor (R) Application. Do NOT Release().
		Application *Application()
		 { return m_pApplication; }

	
	// Constructor(s), initializers and destructor

	public:
		CRxTranslator ();
		~CRxTranslator();

	
	// Interface(s) supported by this object

	public:

		// IRxApplicationAddInSite

		STDMETHOD(Activate)(IRxApplicationAddInSite* pAddInSite, BooleanType bFirstTime);
		STDMETHOD(Deactivate)();
		STDMETHOD(ExecuteCommand)(long CommandID);
		STDMETHOD(get_Automation)(IUnknown** ppUnk);

		// IRxTranslatorAddInServer
		
		STDMETHOD(get_HasOpenOptions)(DataMedium* pSourceData, TranslationContext* pContext, NameValueMap* pDefaultOptions, char* HasOptionsUI);
		STDMETHOD(ShowOpenOptions)(DataMedium* pSourceData, TranslationContext* pContext, NameValueMap* pChosenOptions);
		STDMETHOD(Open)(DataMedium* pSourceData, TranslationContext* pContext, NameValueMap* pOptions, IUnknown** ppTargetObject);
		STDMETHOD(get_HasSaveCopyAsOptions)(IUnknown* pSourceObject, TranslationContext* pContext, NameValueMap* pDefaultOptions, char* pHasOptionsUI);
		STDMETHOD(ShowSaveCopyAsOptions)(IUnknown* pSourceObject, TranslationContext* pContext, NameValueMap* pChosenOptions);
		STDMETHOD(SaveCopyAs)(IUnknown* pSourceObject, TranslationContext* pContext, NameValueMap* pOptions, DataMedium* pTargetData);

		// IRxTranslatorAddInServer2

		STDMETHOD(GetThumbnail)(DataMedium* SourceData, VARIANT* Thumbnail);

private:
	HRESULT WriteModelicaFile(FILE* pFile, AssemblyDocument* pDoc);
};

#endif 
