//
// PlayerController.cpp
// Actor: Tamamura Shuuki
//

#include "PlayerController.h"
#include "PlayerMesh.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pGameObject"></param>
PlayerController::PlayerController(MyLibrary::GameObject* pGameObject):
	Behaviour(pGameObject, 0),
	m_pPlayerMesh(nullptr),
	m_moveDirection(0, 0, 0),
	m_position(0, 0, 0),
	m_velocity(0, 0, 0),
	m_gravity(9.8f),
	m_speed(1),
	m_jumpForce(5),
	m_isGrounded(false)
{
}

/// <summary>
/// 開始
/// </summary>
void PlayerController::Start()
{
	m_pPlayerMesh = this->GetGameObject()->GetComponent<PlayerMesh>();
	m_position = GetTransform()->GetPosition();
}

/// <summary>
/// 更新
/// </summary>
void PlayerController::Update()
{
	// キー入力取得
	auto keyState = System::InputDevice::GetInstance()->GetKeyState();
	auto keyTrigger = System::InputDevice::GetInstance()->GetKeyTracker();

	// 時間取得
	Time* pTime = Time::GetInstance();
	

	// y方向意外の速度をリセットする
	m_velocity.x = 0;
	m_velocity.z = 0;

	// 地上にいる場合のみ操作を行う
	if (m_isGrounded)
	{
		// 入力を検知して前へ進める
		if (keyState.Up)
		{
			m_velocity = GetTransform()->GetForward() * m_speed;
		}
		else if (keyState.Down)
		{
			m_velocity = -GetTransform()->GetForward() * m_speed;
		}

		// 方向転換
		if (keyState.Right)
		{
			GetTransform()->Rotate(0, 1, 0);
		}
		else if (keyState.Left)
		{
			GetTransform()->Rotate(0, -1, 0);
		}

		// ジャンプ
		if (keyTrigger.pressed.Space)
		{
			m_velocity.y = m_jumpForce;
			m_isGrounded = false;
		}
	}

	// 重力分の力を毎フレーム追加
	m_velocity.y -= m_gravity * pTime->GetElapsedTime();

	// 接地していたらy方向の速度をリセットする
	if (m_isGrounded) m_velocity.y = 0;

	// 移動実行
	m_position += m_velocity * pTime->GetElapsedTime();
	GetTransform()->SetPosition(m_position);

	// 接地判定を行う
	if (m_position.y <= 0)
	{
		m_position.y = 0;
		GetTransform()->SetPosition(m_position);
		m_isGrounded = true;
	}
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="pCollider"></param>
void PlayerController::OnCollisionStay(Collider* pOther)
{
}
