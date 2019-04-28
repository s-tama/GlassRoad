//
// Collider.h
//
#pragma once

#include "Component.h"

namespace MyLibrary
{
	class BoxCollider;
	class SphereCollider;

	/// <summary>
	/// コライダークラス
	/// </summary>
	class Collider : public Component
	{
	public:

		Collider(GameObject* pGameObject);
		virtual ~Collider();

		// 他のコライダとの当たり判定
		virtual bool OnCollisionToSphere(Collider* pSphere) = 0;
		virtual bool OnCollisionToBox(Collider* pBox) = 0;
	};
}
