//
// StageManager.cpp
// Actor: Tamamura Shuuki
// Date: 2019/04/13(日)
//

#include "StageManager.h"
#include "StageMesh.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pGameObject"></param>
StageManager::StageManager(MyLibrary::GameObject* pGameObject):
	Behaviour(pGameObject)
{
}

/// <summary>
/// 開始
/// </summary>
void StageManager::Start()
{
	m_pStageChips.resize(12);
	StageMesh* pMesh;
	BoxCollider* pBox;
	for (size_t i = 0; i < m_pStageChips.size(); i++)
	{
		m_pStageChips[i] = new GameObject();
		pMesh = m_pStageChips[i]->AddComponent<StageMesh>();
		pMesh->Create();
		pBox = m_pStageChips[i]->AddComponent<BoxCollider>();
		pBox->SetStatus(Vector3::Zero, Vector3(0.5f, 0.5f, 0.5f));
		m_pStageChips[i]->GetTransform()->SetPosition(-1.0f + static_cast<float>(i % 3), -1, i / 3);
		m_pStageChips[i]->SetTag("Floor");
	}
}

/// <summary>
/// 更新
/// </summary>
void StageManager::Update()
{
	for (const auto& chip : m_pStageChips)
	{
		//chip->GetTransform()->Translate(0, 0, -1 * Time::GetInstance()->GetElapsedTime());
	}
}