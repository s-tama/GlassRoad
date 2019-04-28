//
// PlayerController.h
// Actor: Tamamura Shuuki
//
#pragma once

#include "MyLibrary.h"


class PlayerMesh;

class PlayerController : public MyLibrary::Behaviour
{
public:

	PlayerController(MyLibrary::GameObject* pGameObject);

	void Start() override;
	void Update() override;

	void OnCollisionStay(MyLibrary::Collider* pOther);


private:

	PlayerMesh* m_pPlayerMesh;
	
	DirectX::SimpleMath::Vector3 m_moveDirection;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_velocity;

	float m_gravity;
	float m_speed;
	float m_jumpForce;

	bool m_isGrounded;
};
