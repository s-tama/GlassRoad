//
// PlayerBehaviour.h
// Actor: Tamamura Shuuki
//
#pragma once

#include "MyLibrary.h"


class PlayerMesh;

class PlayerBehaviour : public MyLibrary::Behaviour
{
public:

	PlayerBehaviour(MyLibrary::GameObject* pGameObject);

	void Start();
	void Update();


private:

	PlayerMesh* m_pPlayerMesh;
	DirectX::SimpleMath::Vector3 m_velocity;
	MyLibrary::Time* pTime;
};
