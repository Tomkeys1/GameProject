
#pragma once
//EXTERNAL INCLUDES
#include <map>
//INTERNAL INCLUDES
#include "typedefs/utils.h"
#include "typedefs/keys.h"

class Input 
{
	DEFINE_SINGLETON(Input)
	
public:
	void RegisterKey(KeyCode key, ui16 mode);
	void EradicateKey(KeyCode key, ui16 mode);
	void EradicateUpKeys();

	bool GetKeyDown(KeyCode key);
	bool GetKeyUp(KeyCode key);
	bool GetKeyHold(KeyCode key);
	bool GetUpState(void);

private:
	std::map<KeyCode, KeyCode> downKeys;
	std::map<KeyCode, KeyCode> holdKeys;
	std::map<KeyCode, KeyCode> upKeys;

	bool upState;
};