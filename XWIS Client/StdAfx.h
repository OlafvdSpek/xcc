#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <array>
#include <boost/algorithm/string.hpp>
#include <cassert>
#include <fstream>
#include <string>
#include <strstream>
#include <vector>
#include <winsock2.h>
#include "ETSLayout.h"

using namespace std;
