//
// SphereCollider.cpp
//



// ヘッダーファイルのインクルード -------------------------------------------------
#include "SphereCollider.h"

#include "..\Object\GameObject.h"
#include "..\Collision\CollisionManager.h"



// usingディレクティブ ------------------------------------------------------------
using namespace MyLibrary;
using namespace DirectX::SimpleMath;



// メンバ関数の定義 ---------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
SphereCollider::SphereCollider(GameObject* pGameObject): 
	Collider(pGameObject),
	m_radius(0.f), 
	m_center(Vector3::Zero)
{
	CollisionManager::GetInstance()->AddCollider(this);
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="pSphere"></param>
/// <returns></returns>
bool SphereCollider::OnCollisionToSphere(Collider* pSphere)
{
	return false;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="pBox"></param>
/// <returns></returns>
bool SphereCollider::OnCollisionToBox(Collider* pBox)
{
	return false;
}
