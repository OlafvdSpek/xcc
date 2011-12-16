#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <boost/foreach.hpp>
#include <cassert>
#include <climits>
#include <memory>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "ETSLayout.h"

using namespace ETSLayout;
using namespace std;
