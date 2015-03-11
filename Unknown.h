/*
  DESCRIPTION

  This is an abstract class that enables the easy implementation of the IUnknown functions.
  A class needing to implement a COM interface or a set of COM interfaces can multiply inherit
  from this class as well as all the other COM interface classes and not have to worry too 
  much about implementing the aggregation idea behind COM. In fact, the deriving object does
  not have to worry too much about any of the IUnknown functions. It simply has to override 
  the member function -- CUnknown::InternalQueryInterface, which looks just like a regular 
  QI of a non-aggregating COM-object.

  RULES TO USE THIS OBJECT

  1. Multiply derive the COM object from this object and one or more classes which are in turn
     derived from IUnknown. The interface classes define COM-interfaces which may even have
     implementation associated with certain member functions. These implementations are
     inherited.

  2. Use the DECLARE_UNKNOWN macro inside the declaration of the derived class. This gives you
     the complete definition of the IUnknown methods for the derived class. You don't need to
     declare or write any more IUnknown code, directly.

  3. Override CUnknown::InternalQueryInterface in the derived class and write the function as
     you would in the case of the simple, non-aggregatable COM-object (ie, a non-delegating 
     QueryInterface). Except that, you don't worry about handling the QI for IUnknown -- this
     would have been implemented for you by CUnknown.
*/

/*------------------------ CUnknown class declaration --------------------------------------------*/

#ifndef _CUnknown_
#define _CUnknown_

#include <stddef.h>
#include <objbase.h>

class CUnknown
{
  /*
   * Data declared for this class
   */
  protected:
    IUnknown* m_pUnkOuter;  // Holds the controlling IUnknown (for the inheriting object)

    class XPrivateUnknown : public IUnknown
    {
      private:
        ULONG m_cRef;  // Holds the ref count for the inheriting object. Controls the life-time of this
                       // object.

      public:
        STDMETHODIMP QueryInterface (REFIID riid, void** ppv);  // Ends up calling CUnknown::InternalQueryInterface
        STDMETHODIMP_ (ULONG) AddRef();
        STDMETHODIMP_ (ULONG) Release();

        XPrivateUnknown();  // Constructor for this nested object.
      
      private:
        CUnknown* ThisObjPtr();  // Returns 'this' of the CUnknown (outer) object
    } m_xPrivateUnknown; // Becomes the controlling IUnknown in the non-aggregated case.
    
    friend class XPrivateUnknown;

  /*
   * Methods and/or overrides of this class
   */
  public:
    HRESULT ExternalQueryInterface (REFIID riid, void** ppv);
    ULONG ExternalAddRef();
    ULONG ExternalRelease();  // Derived class's IUnknown methods map to these via DECLARE_UNKNOWN.

    IUnknown* PrivateUnknown(); // Access in the derived class to the private IUnknown.
  
    virtual HRESULT InternalQueryInterface (REFIID riid, void** ppv)=0; // overridden by derived class
                                                                        // as if it was the QI for a
                                                                        // non-delegating IUnknown.

  /*
   * Constructors and/or destructors
   */
  public:
    CUnknown (IUnknown* pUnkOuter);  // Always constructed by this constructor
    virtual ~CUnknown();
};

/*-------------------------- Macro to be used inside the deriving class definition -----------------*/

#define DECLARE_UNKNOWN \
  STDMETHOD (QueryInterface) (REFIID riid, void** ppv) \
    {   AFX_MANAGE_STATE (AfxGetStaticModuleState()); \
        return ExternalQueryInterface (riid, ppv); } \
  STDMETHOD_ (ULONG, AddRef) () \
    {   AFX_MANAGE_STATE (AfxGetStaticModuleState()); \
        return ExternalAddRef(); } \
  STDMETHOD_ (ULONG, Release) () \
    {   AFX_MANAGE_STATE (AfxGetStaticModuleState()); \
        return ExternalRelease(); }

#endif
