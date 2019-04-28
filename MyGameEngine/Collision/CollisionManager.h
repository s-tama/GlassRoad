//
// CollisionManager.h
// 制作者: 玉村柊希
// 作成日: 2019/03/10(日)
//
#pragma once


// ヘッダーファイルのインクルード --------------------------------------------------
#include <vector>
#include <memory>


// クラスの定義 --------------------------------------------------------------------
namespace MyLibrary
{
	class Collider;
	class Collider2D;

	/// <summary>
	/// 当たり判定管理クラス
	/// </summary>
	class CollisionManager
	{
	public:

		static CollisionManager* GetInstance();

		// 当たり判定を行うコライダを追加する
		void AddCollider(Collider* pCollider);
		void RemoveCollider(Collider* pCollider);

		void Reset();

		// 更新
		void Update();


	private:

		CollisionManager();


	private:

		static std::unique_ptr<CollisionManager> m_pInstance;

		std::vector<Collider*> m_pColliders;
	};
}
