// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__51DE2A22_BA6C_4A11_A46E_42779214DD1F__INCLUDED_)
#define AFX_STDAFX_H__51DE2A22_BA6C_4A11_A46E_42779214DD1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning(disable: 4503)
#pragma warning(disable: 4786)
#pragma warning(disable: 4800)

#include <cassert>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "ETSLayout.h"
#include "virtual_binary.h"

using namespace ETSLayout;
using namespace std;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__51DE2A22_BA6C_4A11_A46E_42779214DD1F__INCLUDED_)
