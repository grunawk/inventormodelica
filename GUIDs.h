/*
  DESCRIPTION

  This file contains the definitions of various GUIDs that may be used within this
  sample.

*/

#ifndef _GUIDS_
#define _GUIDS_

#include <objbase.h>


// This GUID is the CLSID of the object that Autodesk Inventor (R) first CoCreates. It is the 
// Add-In Server object.

// {B0CE4C31-36B5-4581-B7C2-AC903D3F58DF}
DEFINE_GUID(CLSID_ModelicaTrans, 
0xb0ce4c31, 0x36b5, 0x4581, 0xb7, 0xc2, 0xac, 0x90, 0x3d, 0x3f, 0x58, 0xdf);

#define CLSID_ModelicaTrans_RegGUID _T("B0CE4C31-36B5-4581-B7C2-AC903D3F58DF")
#define CLSID_ModelicaTrans_Name _T("ModelicaTrans")
#define CLSID_ModelicaTrans_Descr _T("Saves Modelica assembly.")

#endif
