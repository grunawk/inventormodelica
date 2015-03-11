// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__246084EF_F374_11D3_853D_0060B0F0B5B7__INCLUDED_)
#define AFX_STDAFX_H__246084EF_F374_11D3_853D_0060B0F0B5B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>          // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>         // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

/*--------------------- Custom header files insertion -------------------------------*/

// System level includes
#include <atlbase.h>
#include <vector>

// Local include files
#include "commonpreproc.h"
#include "clipboardformats.h"

/*--------------------- MFC AppWizard gobbledegook -------------------------------*/

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

// Eliminate botherware warnings
#pragma warning(disable : 4049) // compiler limit : terminating line number emission
#pragma warning(disable : 4192) // automatically excluding 'name' while importing type library 'library'
#pragma warning(disable : 4278) // 'name':identifier in type library 'library' is already a macro

// Inventor interfaces include
#include "InventorUtils.h"
#include "types.h"

#endif // !defined(AFX_STDAFX_H__246084EF_F374_11D3_853D_0060B0F0B5B7__INCLUDED_)



