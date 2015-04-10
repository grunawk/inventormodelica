/*
	DESCRIPTION

	This file contains the declaration of the class that defines the COM-object with which
	Autodesk Inventor (R) first communicates (supports the IRxApplicationAddInServer interface).

	Strategy for inventor to modelica

	
	rigid group -> MoBody
	MoBody = definition with cm relative to world + occurrence with ground

	rigid group -> MoRigidGroupOccurrence
	MoRigidGroupOccurrence is instantiation of MoRigidGroup
	MoRigidGroupOccurrence can be grounded and has a transform
	MoRigidGroup contains modelica body that is the sum of all rigid bodies in group
	MoRigidGroup has icon from component with largest mass in group
	MoRigidGroup cm is relative to world
	MoRigidGroup *could* have multiple fixed bodies for each body in group -- but not needed
	MoRigidGroups with same definition *could* be mapped to a single MoRigidGroup for reuse
	MoRigidGroup and MoRigidGroupOccurrence *could* be the same object if MoRigidGroups are not reused
	joint -> MoJoint which combines the joint definition and occurrence since assembly is flat
	MoJoint contains two fixed rotations to two MoRigidGroup frames and a modelica joint
	if MoRigidGroupOccurrence is grounded, frame attached to fixedrotation to world
*/


#ifndef _RXTranslator_
#define _RXTranslator_

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "unknown.h"
#include "resource.h"
#include "TranslationOptionsDlg.h"

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
	HRESULT CreateModelicaAssembly(FILE* pFile, AssemblyDocument* pDoc, MoAssemblyPtr& assem);

private:
	TranslationOptionsDlg m_optionsDlg;
};

#endif 
