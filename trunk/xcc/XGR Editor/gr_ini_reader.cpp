// gr_ini_reader.cpp: implementation of the Cgr_ini_reader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "gr_ini_reader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

bool opens_sub_section(const string& v)
{
	const char* opens_sub_section[] =
	{
		"AnimatingPart",
		"ApplyRandomForce",
		"ArmorSet",
		"Attack",
		"AttackContinueAreaRadiusCursor",
		"AttackDamageAreaRadiusCursor",
		"AttackScatterAreaRadiusCursor",
		"Behavior",
		"Body",
		"ConditionState",
		"CreateDebris",
		"CreateObject",
		"DefaultConditionState",
		"DeliverPayload",
		"DeliveryDecal",
		"Draw",
		"DynamicGameLOD",
		"EvaEvent",
		"FXListAtBonePos",
		"FireWeapon",
		"FriendlySpecialPowerRadiusCursor",
		"GameData",
		"GuardAreaRadiusCursor",
		"ImagePart",
		"LightPulse",
		"Locomotor",
		"Mission",
		"Object",
		"OffensiveSpecialPowerRadiusCursor",
		"ParticleSystem", // fxlist
		"Prerequisites",
		"SideInfo",
		"SideSounds",
		"SkillSet1",
		"SkillSet2",
		"SkillSet3",
		"SkillSet4",
		"SkillSet5",
		"SkirmishBuildList",
		"Sound",
		"StaticGameLOD",
		"Structure",
		"TerrainScorch",
		"Tracer",
		"TransitionState",
		"UnitSpecificSounds",
		"ViewShake",
		"WeaponSet",
		NULL
	};

	const char** r = opens_sub_section;
	while (*r && *r != v)
		r++;
	return *r && *r == v;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cgr_ini_reader::Cgr_ini_reader()
{
}

Cgr_ini_reader::Cgr_ini_reader(const Cvirtual_binary& d)
{
	import(d);
}

ostream& operator<<(ostream& os, const Cgr_ini_reader& v)
{
	return v.export(os);
}

ostream& operator<<(ostream& os, const Cgr_ini_reader::Csection& v)
{
	return v.export(os, 0);
}

