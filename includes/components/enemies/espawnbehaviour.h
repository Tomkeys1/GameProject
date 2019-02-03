#pragma once

//EXTERNAL INCLUDES
#include <map>
#include <vector>
//INTERNAL INCLUDES
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
private:
	std::map<ui32, std::vector<EnemyPattern*>> patterns;
	bool spawn;
	real count;
};