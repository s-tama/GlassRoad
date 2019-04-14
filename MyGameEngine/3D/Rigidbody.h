//
// Rigidbody.h
// Actor: Tamamura Shuuki
//
#pragma once

#include "..\Component\Component.h"


namespace MyLibrary
{
	class Rigidbody : public Component
	{
	public:

		Rigidbody(GameObject* pGameObject);

		void Update() override;

		// プロパティ
		const DirectX::SimpleMath::Vector3& GetVelocity() { return m_velocity; }
		void SetVelocity(DirectX::SimpleMath::Vector3 const& velocity) { m_velocity = velocity; }


	private:

		DirectX::SimpleMath::Vector3 m_velocity;
		DirectX::SimpleMath::Vector3 m_anglerVelocity;
	};
}
