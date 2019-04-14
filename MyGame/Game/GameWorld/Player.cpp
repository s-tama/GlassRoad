//
// Playeer.cpp
//

#include "Player.h"

#include "PlayerMesh.h"
#include "..\Behaviours\PlayerBehaviour.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	PlayerMesh* pMesh = AddComponent<PlayerMesh>();
	pMesh->Create();

	AddComponent<PlayerBehaviour>();
}
