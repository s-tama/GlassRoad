//
// CollisionManager.cpp
//


// ヘッダーファイルのインクルード -----------------------------------------------------------
#include "CollisionManager.h"

#include "..\Component\Collider.h"
#include "..\Component\Collider2D.h"
#include "..\Component\BoxCollider2D.h"
#include "..\Component\CircleCollider.h"


// usingディレクティブ -------------------------------------------------------------------
using namespace MyLibrary;


// 静的メンバ変数の定義 -----------------------------------------------------------------
std::unique_ptr<CollisionManager> CollisionManager::m_pInstance = nullptr;


// メンバ関数の定義 ----------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pNode"></param>
CollisionManager::CollisionManager()
{
}

/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns></returns>
CollisionManager* MyLibrary::CollisionManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance.reset(new CollisionManager);
	return m_pInstance.get();
}

/// <summary>
/// コライダを追加する
/// </summary>
/// <param name="pCollider"></param>
void CollisionManager::AddCollider(Collider* pCollider)
{
	m_pColliders.push_back(pCollider);
}

/// <summary>
/// 指定のコライダを管理対象から外す
/// </summary>
/// <param name="pCollider"></param>
void CollisionManager::RemoveCollider(Collider* pCollider)
{
}

/// <summary>
/// 全コライダを管理対象から外す
/// </summary>
void CollisionManager::Reset()
{
	m_pColliders.clear();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void CollisionManager::Update()
{
	for (const auto& c0 : m_pColliders)
	{
		for (const auto& c1 : m_pColliders)
		{
			if (c0 != c1)
			{
				c0->OnCollisionToBox(c1);
				c0->OnCollisionToSphere(c1);
			}
		}
	}
}
