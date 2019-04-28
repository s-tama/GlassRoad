//
// BoxCollider.cpp
//



// ヘッダーファイルのインクルード -------------------------------------------------
#include "BoxCollider.h"

#include "..\Object\GameObject.h"
#include "..\Collision\CollisionManager.h"



// usingディレクティブ ------------------------------------------------------------
using namespace MyLibrary;
using namespace DirectX::SimpleMath;



// メンバ関数の定義 ---------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
BoxCollider::BoxCollider(GameObject* pGameObject):
	Collider(pGameObject),
	m_center(Vector3::Zero), 
	m_extents(Vector3::Zero)
{
	CollisionManager::GetInstance()->AddCollider(this);
}

/// <summary>
/// 
/// </summary>
/// <param name="pSphere"></param>
/// <returns></returns>
bool BoxCollider::OnCollisionToSphere(Collider* pOther)
{


	return false;
}

/// <summary>
/// ボックスとの当たり判定
/// </summary>
/// <param name="pBox"></param>
/// <returns></returns>
bool MyLibrary::BoxCollider::OnCollisionToBox(Collider* pOther)
{
	BoxCollider* pBox = dynamic_cast<BoxCollider*>(pOther);
	if (pBox == nullptr) return false;

	Vector3 myPos = m_pTransform->GetPosition() + m_center;
	Vector3 otherPos = pBox->GetTransform()->GetPosition() + pBox->GetCenter();

	float dx = abs(myPos.x - otherPos.x);
	float dy = abs(myPos.y - otherPos.y);
	float dz = abs(myPos.z - otherPos.z);

	if (dx > m_extents.x + pBox->GetExtents().x) return false;
	if (dy > m_extents.y + pBox->GetExtents().y) return false;
	if (dz > m_extents.z + pBox->GetExtents().z) return false;

	m_pGameObject->OnCollisionStay(pOther);
	return true;
}
