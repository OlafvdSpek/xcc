#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <array>
#include <boost/algorithm/string.hpp>
#include <cassert>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <xbt/find_ptr.h>
#include "ETSLayout.h"
#include "mix_file.h"
#include "xcc_dirs.h"

using namespace std;
using boost::iequals;
using boost::to_lower_copy;
using boost::trim_copy;
