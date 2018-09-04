#pragma once

#include "GlobalEnvironment.h"

class GameFactory
{
public:
	static void Initialize()
	{
		Paddle* paddle01 = new Paddle();
		Ball* ball = new Ball();

		EntityManager* m_pEntityManager = gEnv.GetEntityManager();

		m_pEntityManager->Add(paddle01);
		m_pEntityManager->Add(ball);

		BlockSpawner::SpawnBlocks();
	}
};