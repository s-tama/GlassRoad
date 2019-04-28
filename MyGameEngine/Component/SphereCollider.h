﻿//
// SphereCollider.h
//
#pragma once

#include "Collider.h"

namespace MyLibrary
{
	/// <summary>
	/// 球のコライダクラス
	/// </summary>
	class SphereCollider : public Collider
	{
	public:

		// コンストラクタ
		SphereCollider(GameObject* pGameObject);

		// 中心点の取得
		DirectX::SimpleMath::Vector3 GetCenter() { return m_center; }

		// 半径の取得
		float GetRadius() { return m_radius; }

		// 情報の設定
		void SetStatus(DirectX::SimpleMath::Vector3 center, float radius)
		{
			m_center = center;
			m_radius = radius;
		}

		// 他のコライダとの当たり判定
		bool OnCollisionToSphere(Collider* pSphere) override;
		bool OnCollisionToBox(Collider* pBox) override;


	private:

		// 中心点
		DirectX::SimpleMath::Vector3 m_center;

		// 半径
		float m_radius;
	};
}
