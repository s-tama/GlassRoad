//
// Rigidbody.cpp
// Actor: Tamamura Shuuki
//

#include "Rigidbody.h"

#include "..\Component\Transform.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pGameObject"></param>
Rigidbody::Rigidbody(GameObject* pGameObject):
	Component(pGameObject),
	m_velocity(0, -0.098f, 0),
	m_anglerVelocity(Vector3::Zero)
{
}

/// <summary>
/// 更新
/// </summary>
void Rigidbody::Update()
{
	m_pTransform->SetPosition(m_pTransform->GetPosition() + m_velocity);
}
