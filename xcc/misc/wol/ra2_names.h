#if !defined(AFX_RA2_NAMES_H__00ADDA5E_BC0C_406B_B88F_7ED2C6750266__INCLUDED_)
#define AFX_RA2_NAMES_H__00ADDA5E_BC0C_406B_B88F_7ED2C6750266__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

using namespace std;

string get_country_name(int i);
string get_map_name(const string& v);
string get_ra2_building_name(int v);
string get_ra2_infantry_name(int v);
string get_ra2_plane_name(int v);
string get_ra2_vehicle_name(int v);

#endif // !defined(AFX_RA2_NAMES_H__00ADDA5E_BC0C_406B_B88F_7ED2C6750266__INCLUDED_)
