//
// PlayerBehaviour.cpp
//

#include "PlayerBehaviour.h"

#include "..\GameWorld\PlayerMesh.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pGameObject"></param>
PlayerBehaviour::PlayerBehaviour(MyLibrary::GameObject* pGameObject):
	Behaviour(pGameObject, 0),
	m_pPlayerMesh(nullptr),
	m_velocity(0, 0, 0)
{
}

/// <summary>
/// 開始
/// </summary>
void PlayerBehaviour::Start()
{
	m_pPlayerMesh = this->GetGameObject()->GetComponent<PlayerMesh>();
	GetGameObject()->GetTransform()->SetPosition(0, 1, 0);
	pTime = Time::GetInstance();
}

/// <summary>
/// 更新
/// </summary>
void PlayerBehaviour::Update()
{
	// キーボードトリガー
	auto keyTrg = System::InputDevice::GetInstance()->GetKeyTracker();
	// 重力
	float gravity = -9.8f / 10000.0f;

	m_velocity.y += gravity;
	m_pTransform->SetPosition(m_pTransform->GetPosition() + m_velocity);

	if (keyTrg.pressed.Space)
	{
		m_pPlayerMesh->CallOnDestruction();
	}
}
