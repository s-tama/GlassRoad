//
// CircleCollider.h
// 作成者: 玉村柊希
// 作成日: 2019/03/10(日)
//


// ヘッダーファイルのインクルード -------------------------------------------------------------------
#include "CircleCollider.h"

#include "../Object/GameObject.h"
#include "..\Collision\CollisionManager.h"


// usingディレクティブ ---------------------------------------------------------------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pGameObject"></param>
CircleCollider::CircleCollider(GameObject* pGameObject) :
	Collider2D(pGameObject)
{
}

/// <summary>
/// デストラクタ
/// </summary>
CircleCollider::~CircleCollider()
{
}

/// <summary>
/// セット
/// </summary>
void CircleCollider::Set(float radius)
{
	m_radius = radius;
}

/// <summary>
/// ボックスとの当たり判定
/// </summary>
/// <param name="pOther"></param>
void  CircleCollider::OnCollisionToBox(BoxCollider2D* pOther)
{
}

/// <summary>
/// 円との衝突判定
/// </summary>
/// <param name="pCircleCollider"></param>
void CircleCollider::OnCollisionToCircle(CircleCollider* pOther)
{
}
