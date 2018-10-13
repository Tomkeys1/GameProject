
#pragma once
//EXTERNAL INCLUDES
#include <map>
#include <string>
//INTERNAL INCLUDES
#include "typedefs/types.h"
#include "typedefs/utils.h"
#include "typedefs/cvar.h"

class Console 
{
	//Define Console as a singleton. See utils.h for definition.
	DEFINE_SINGLETON(Console)

public:
	CVar GetCVar(const std::string& name);
	void SetCVar(const CVar& cvar);
	void CleanUp();

private:
	std::map<std::string, const char*> cvars;
};