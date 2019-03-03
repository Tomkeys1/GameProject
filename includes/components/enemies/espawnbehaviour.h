#pragma once

//EXTERNAL INCLUDES
#include <map>
#include <vector>
//INTERNAL INCLUDES
#include "scene/gameobject.h"
#include "typedefs/types.h"
#include "typedefs/utils.h"
#include "components/enemies/enemypatterns.h"

class EnemySpawner
{
public:
	void Initialize(void);
	void Update(void);
	void Cleanup(void);
	void CreatePatterns(void);


	std::vector<EnemyPattern*> GetPattern(ui32 id);
	ui32& GetDeadEnemies(void);


private:
	std::map<ui32, std::vector<EnemyPattern*>> patterns;
	ui32 activeEnemies;
	ui32 deadEnemeies;
	bool spawn;
	real count;
	real timer;
	ui8 seed;
};