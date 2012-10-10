#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <array>
#include <cassert>
#include <climits>
#include <cstdint>
#include <memory>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <xbt/find_ptr.h>
#include "ETSLayout.h"

using namespace ETSLayout;
using namespace std;
