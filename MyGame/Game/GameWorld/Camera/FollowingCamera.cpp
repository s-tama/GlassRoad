//
// FollowingCamera.cpp
// Actor: Tamamura Shuuki
//

#include "FollowingCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pGameObject"></param>
FollowingCamera::FollowingCamera(GameObject* pGameObject):
	Behaviour(pGameObject),
	m_distance(0, 0, 0),
	m_pTarget(nullptr),
	m_followSpeed(1)
{
}

/// <summary>
/// 開始
/// </summary>
void FollowingCamera::Start()
{
	if (!m_pTarget) return;

	// 追従距離を計算する
	m_distance = m_pTarget->GetPosition() - GetTransform()->GetPosition();
}

/// <summary>
/// 更新
/// </summary>
void FollowingCamera::LateUpdate()
{
	if (!m_pTarget) return;

	// 時間取得
	Time* pTime = Time::GetInstance();

	// 線形補間関数によるスムージング
	Vector3 pos = GetTransform()->GetPosition();
	pos = XMVectorLerp(pos, m_pTarget->GetTransform()->GetPosition() - m_distance, m_followSpeed * pTime->GetElapsedTime());
}
