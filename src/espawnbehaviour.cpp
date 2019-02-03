
//EXTERNAL INCLUDES
#include <time.h>
//INTERNAL INCLUDES
#include "components\enemies\espawnbehaviour.h"
#include "typedefs/utils.h"
#include "application.h"
#include "scene/scene.h"
#include "scene/gameobject.h"
#include "components/shooting.h"

void EnemySpawner::Initialize(void)
{
	this->spawn = true;
	this->count = 0;
	srand(time(NULL));

	CreatePatterns();
}

void EnemySpawner::Update(void)
{
	if (this->spawn)
	{
		this->spawn = false;

		std::vector<EnemyPattern*> pattern = this->patterns[this->count];

		for (ui32 i = 0; i < pattern.size(); i++)
		{
			switch (pattern[i]->type)
			{
				case EnemyType::NORMAL:
				{
					Gameobject* temp = Application::GetInstancePtr()->GetScene()->GetObjectItem("normalEnemies", false);

					temp->GetTransform().position.x = -100.0f + (pattern[i]->xPosInDivision * (50.0f * temp->GetTransform().scaling.x));
					temp->GetTransform().position.y = 100.0f - (pattern[i]->yPosInDivision * (60.0f * temp->GetTransform().scaling.y));
					temp->GetEulerRotation().z = 180.0f;
					temp->SetVisi(true);
					temp->SetActive(true);

					ui32 cooldown = rand() % 15 + 10;
					reinterpret_cast<Shooting*>(temp->GetComponent(ComponentType::Shoot))->GetShootingValues().cooldown = cooldown;
					reinterpret_cast<Shooting*>(temp->GetComponent(ComponentType::Shoot))->GetShootingValues().timer = cooldown - 5;

					break;
				}

				case EnemyType::DOUBLE:
				{
					Gameobject* temp = Application::GetInstancePtr()->GetScene()->GetObjectItem("normalEnemies", false);

					temp->GetTransform().position.x = -100.0f + (pattern[i]->xPosInDivision * (50.0f * temp->GetTransform().scaling.x));
					temp->GetTransform().position.y = 100.0f - (pattern[i]->yPosInDivision * (60.0f * temp->GetTransform().scaling.y));
					temp->SetVisi(true);
					temp->SetActive(true);
					break;
				}

				case EnemyType::TANK:
				{
					Gameobject* temp = Application::GetInstancePtr()->GetScene()->GetObjectItem("normalEnemies", false);

					temp->GetTransform().position.x = -100.0f + (pattern[i]->xPosInDivision * (50.0f * temp->GetTransform().scaling.x));
					temp->GetTransform().position.y = 100.0f - (pattern[i]->yPosInDivision * (60.0f * temp->GetTransform().scaling.y));
					temp->SetVisi(true);
					temp->SetActive(true);
					break;
				}
			}
		}

		this->count++;
	}

}

void EnemySpawner::Cleanup(void)
{
	std::map<ui32, std::vector<EnemyPattern*>>::iterator it;

	for (it = this->patterns.begin(); it != this->patterns.end(); it++)
	{
		for (EnemyPattern* pattern : it->second)
		{
			delete pattern;
		}
		it->second.clear();
	}
}

std::vector<EnemyPattern*> EnemySpawner::GetPattern(ui32 id)
{
	return this->patterns[id];
}

void EnemySpawner::CreatePatterns(void)
{
	//NORMAL PATTERN
	EnemyPattern* pattern1_1 = new EnemyPattern;
	EnemyPattern* pattern1_2 = new EnemyPattern;
	EnemyPattern* pattern1_3 =  new EnemyPattern;
	EnemyPattern* pattern1_4 = new EnemyPattern;
	EnemyPattern* pattern1_5 = new EnemyPattern;
	EnemyPattern* pattern1_6 = new EnemyPattern;
	pattern1_1->type = EnemyType::NORMAL;
	pattern1_1->xPosInDivision = 1;
	pattern1_1->yPosInDivision = 1;
			  
	pattern1_2->type = EnemyType::NORMAL;
	pattern1_2->xPosInDivision = 2;
	pattern1_2->yPosInDivision = 1;
			  
	pattern1_3->type = EnemyType::NORMAL;
	pattern1_3->xPosInDivision = 3;
	pattern1_3->yPosInDivision = 1;

	pattern1_4->type = EnemyType::NORMAL;
	pattern1_4->xPosInDivision = 1;
	pattern1_4->yPosInDivision = 2;

	pattern1_5->type = EnemyType::NORMAL;
	pattern1_5->xPosInDivision = 2;
	pattern1_5->yPosInDivision = 2;

	pattern1_6->type = EnemyType::NORMAL;
	pattern1_6->xPosInDivision = 3;
	pattern1_6->yPosInDivision = 2;

	this->patterns[0].push_back(pattern1_1);
	this->patterns[0].push_back(pattern1_2);
	this->patterns[0].push_back(pattern1_3);
	this->patterns[0].push_back(pattern1_4);
	this->patterns[0].push_back(pattern1_5);
	this->patterns[0].push_back(pattern1_6);
}
