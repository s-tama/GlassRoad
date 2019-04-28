//
// Scene.cpp
//



// ヘッダーファイルのインクルード ---------------------------------------------------------------
#include "SceneBase.h"

#include "..\Object\ObjectManager.h"
#include "..\Collision\CollisionManager.h"
#include "..\3D\MeshRenderer.h"
#include "..\2D\SpriteRenderer.h"

#include "..\Utility\Macro.h"



// usingディレクティブ --------------------------------------------------------------------------
using namespace MyLibrary;



// メンバ関数の定義 -----------------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="name">シーン名</param>
SceneBase::SceneBase():
	m_name("")
{
}

/// <summary>
/// デストラクタ
/// </summary>
SceneBase::~SceneBase()
{
}

/// <summary>
/// 初期化
/// </summary>
void SceneBase::Initialize()
{
	m_pObjectManager = new ObjectManager();
	m_pObjectManager->Initialize();
}

/// <summary>
/// 更新
/// </summary>
void SceneBase::Update()
{
	m_pObjectManager->Update();
	CollisionManager::GetInstance()->Update();
}

/// <summary>
/// 描画
/// </summary>
void SceneBase::Render()
{
	// メッシュの描画
	MeshRenderer* pMeshRenderer = MeshRenderer::GetInstance();
	pMeshRenderer->Begin();
	pMeshRenderer->Draw();
	pMeshRenderer->End();

	// スプライトの描画
	SpriteRenderer* pSpriteRenderer = SpriteRenderer::GetInstance();
	pSpriteRenderer->Begin();
	pSpriteRenderer->Draw();
	pSpriteRenderer->End();
}

/// <summary>
/// 終了
/// </summary>
void SceneBase::Finalize()
{
	MeshRenderer::GetInstance()->Reset();
	SpriteRenderer::GetInstance()->Reset();
	CollisionManager::GetInstance()->Reset();

	SAFE_DELETE(m_pObjectManager);
}
