#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning(disable: 4503 4554 4786 4800 4804)

#include <array>
#include <cassert>
#include <climits>
#include <list>
#include <memory>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <xbt/find_ptr.h>
#include "ETSLayout.h"

using namespace ETSLayout;
using namespace std;
