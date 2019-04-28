//
// FollowingCamera.h
// Actor: Tamamura Shuuki
//
#pragma once

#include "MyLibrary.h"


/// <summary>
/// ターゲットを追従するカメラコンポーネント
/// </summary>
class FollowingCamera : public MyLibrary::Behaviour
{
public:

	FollowingCamera(MyLibrary::GameObject* pGameObject);

	void Start() override;
	void LateUpdate() override;

	// プロパティ
	void SetTarget(MyLibrary::Transform* pTarget) { m_pTarget = pTarget; }
	void SetFollowSpeed(float speed) { m_followSpeed = speed; }


private:

	DirectX::SimpleMath::Vector3 m_distance;	// 追従距離

	MyLibrary::Transform* m_pTarget;	// 追従対象の変換情報
	float m_followSpeed;				// 追従速度
};
