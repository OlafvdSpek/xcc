#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include <array>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <xbt/find_ptr.h>
#include <mmsystem.h>
#include "ETSLayout.h"

using namespace ETSLayout;
using namespace std;
