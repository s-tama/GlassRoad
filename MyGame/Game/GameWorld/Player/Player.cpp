//
// Playeer.cpp
//

#include "Player.h"

#include "PlayerMesh.h"
#include "PlayerController.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player(GameObject* pGameObject):
	Behaviour(pGameObject),
	m_pMesh(nullptr),
	m_pController(nullptr)
{
	
}

/// <summary>
/// 開始
/// </summary>
void Player::Start()
{
	m_pMesh = GetGameObject()->AddComponent<PlayerMesh>();
	m_pController = GetGameObject()->AddComponent<PlayerController>();
}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
}
