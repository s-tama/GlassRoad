//
// Player.h
//
#pragma once

#include "MyLibrary.h"


class PlayerMesh;
class PlayerController;

class Player : public MyLibrary::Behaviour
{
public:

	Player(MyLibrary::GameObject* pGameObject);

	void Start() override;
	void Update() override;


private:

	PlayerMesh* m_pMesh;
	PlayerController* m_pController;
};
