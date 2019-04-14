//
// Game.cpp
//



// ヘッダーファイルのインクルード --------------------------------------------------
#include "Game.h"

#include "Scenes\SampleScene.h"



// usingディレクティブ -------------------------------------------------------------
using namespace MyLibrary;
using namespace MyGame;
using namespace DirectX;



// メンバ関数の定義 ----------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="hInstance">インスタンス</param>
/// <param name="nCmdShow">表示状態</param>
Game::Game(HINSTANCE hInstance, int nCmdShow): 
	Framework(hInstance, nCmdShow, 640, 480, L"だんご大家族"),
	m_pSceneManager(nullptr)
{
	SetWindowColor(0, 0, 0);
}

/// <summary>
/// 初期化処理
/// </summary>
void Game::Initialize()
{
	// リソースの作成処理
	CreateResources();

	// シーンマネージャーの作成
	m_pSceneManager = new SceneManager();
	m_pSceneManager->StartScene(new SampleScene());
}

#pragma region ゲームループ
/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Game::Update(StepTimer const& timer)
{
	Time::GetInstance()->Update(timer);

	System::InputDevice::GetInstance()->Update();

	// エスケープキーでゲームの終了
	if (System::InputDevice::GetInstance()->GetKeyState().Escape)
	{
		PostQuitMessage(0);
	}

	m_pSceneManager->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Game::Render()
{
	// シーンマネージャーの描画
	m_pSceneManager->Render();
}
#pragma endregion

/// <summary>
/// 終了処理
/// </summary>
void Game::Finalize()
{
	SAFE_DELETE(m_pSceneManager);
}

/// <summary>
/// リソースの作成処理
/// </summary>
void Game::CreateResources()
{
}
