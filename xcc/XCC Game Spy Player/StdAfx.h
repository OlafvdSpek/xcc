// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E1DCE637_B449_441A_85D5_450FEE4A4EF3__INCLUDED_)
#define AFX_STDAFX_H__E1DCE637_B449_441A_85D5_450FEE4A4EF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning(disable: 4503)
#pragma warning(disable: 4786)
#pragma warning(disable: 4800)

#include <afxsock.h>		// MFC socket extensions
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <mmsystem.h>
#include "ETSLayout.h"

using namespace ETSLayout;
using namespace std;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E1DCE637_B449_441A_85D5_450FEE4A4EF3__INCLUDED_)
