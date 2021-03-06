﻿//
// BoxCollider.h
//
#pragma once

#include "Collider.h"

namespace MyLibrary
{
	/// <summary>
	/// ボックスコライダクラス
	/// </summary>
	class BoxCollider : public Collider
	{
	public:

		// コンストラクタ
		BoxCollider(GameObject* pGameObject);

		// 中心点の取得
		DirectX::SimpleMath::Vector3 GetCenter() { return m_center; }
		
		// 広さの取得
		DirectX::SimpleMath::Vector3 GetExtents() { return m_extents; }

		// 情報の設定
		void SetStatus(DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 extents)
		{
			m_center = center;
			m_extents = extents;
		}

		// 他のコライダとの当たり判定
		bool OnCollisionToSphere(Collider* pOther) override;
		bool OnCollisionToBox(Collider* pOther) override;


	private:

		// 中心点
		DirectX::SimpleMath::Vector3 m_center;

		// 広さ
		DirectX::SimpleMath::Vector3 m_extents;
	};
}
