/*
  DESCRIPTION

  This file contains the implementation of all of the methods, constructors, etc. of the 
  CUnknown class. 
*/

#include "stdafx.h"
#include "unknown.h"

/*-------------------- Constructors and destructors ----------- ------------------------------------*/

CUnknown::CUnknown (IUnknown* pUnkOuter)
{
	// Set m_pUnkOuter to the controlling object's IUnknown.
	// either the aggregator or the private unknown of this object)

	if (pUnkOuter)
	m_pUnkOuter = pUnkOuter;
	else
	m_pUnkOuter = &m_xPrivateUnknown;
}

CUnknown::XPrivateUnknown::XPrivateUnknown()
{
	m_cRef = 0;
}

CUnknown::~CUnknown()
{
}

/*-------------------- Overrides and new member function of CUnknown::XPrivateUnknown (inner object) -----*/

/*
 * The following IUnknown implementations are the inheriting object's personal IUnknown. When
 * it has been aggregated, the only object invoking these methods will be the controlling object
 * (aggregator), having obtained the pointer to this IUnknown via the CUnknown::PrivateUnknown
 * method. In the non-aggregating case, this implementation becomes the true IUnknown of the object.
 */

STDMETHODIMP CUnknown::XPrivateUnknown::QueryInterface (REFIID riid, void ** ppv)
{
	// This overide can only service the request for the REFIID IUnknown. All other
	// QI requests have to be satisfied by invoking the InternalQueryInterface override implemented 
	// by the inheriting object.

	if (IsEqualIID(riid, IID_IUnknown))
	{
	++m_cRef;
	*ppv = (IUnknown *) this;

	return NOERROR;
	}
	else
	{
	return ThisObjPtr()->InternalQueryInterface (riid, ppv);
	}
}

ULONG CUnknown::XPrivateUnknown::AddRef()
{
	ULONG cRef = ++m_cRef;
	return cRef;
}

ULONG CUnknown::XPrivateUnknown::Release()
{
	ULONG cRef = --m_cRef;

	if (!m_cRef)
	delete ThisObjPtr();

	return cRef;
}

inline CUnknown* CUnknown::XPrivateUnknown::ThisObjPtr()
{
	// The following arithmetic returns the pointer to the whole object while inside the inner
	// object

	return (CUnknown *) ((unsigned char *) this - offsetof (CUnknown, m_xPrivateUnknown));
}


/*--------------------------- Member functions of the CUnknown class ---------------------------*/

/*
 * Works like the delegating Unknown in the case of aggregation. If no aggregation, 
 * m_pUnkOuter is pointing to this object's non-delegating Unknown.
 */

HRESULT CUnknown::ExternalQueryInterface (REFIID riid, void **ppv)
{
	return m_pUnkOuter->QueryInterface (riid, ppv);
}

ULONG CUnknown::ExternalAddRef (void)
{
	return m_pUnkOuter->AddRef();
}

ULONG CUnknown::ExternalRelease (void)
{
	return m_pUnkOuter->Release();
}

/*
 * Returns the non-delegating Unknown of this class
 */

IUnknown * CUnknown::PrivateUnknown (void) 
{
	return (IUnknown *) &m_xPrivateUnknown;
}
