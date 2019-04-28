//
// SampleScene.cpp
//



// ヘッダーファイルのインクルード --------------------------------------------------------
#include "SampleScene.h"

#include "..\GameWorld\Player\Player.h"
#include "..\GameWorld\Camera\FollowingCamera.h"



// usingディレクティブ -------------------------------------------------------------------
using namespace MyLibrary;
using namespace MyGame;
using namespace DirectX;
using namespace DirectX::SimpleMath;



// メンバ関数の定義 ----------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
SampleScene::SampleScene()
{
	// カメラの作成
	GameObject* pCamera = new GameObject();
	pCamera->SetTag("MainCamera");
	pCamera->GetTransform()->SetPosition(0, 3, -5);
	pCamera->AddComponent<Camera>();
	
	// プレイヤーの作成
	GameObject* pPlayer = new GameObject();
	pPlayer->SetTag("Player");
	pPlayer->GetTransform()->SetPosition(0, 5, 0);
	pPlayer->AddComponent<Player>();

	//pCamera->AddComponent<FollowingCamera>()->SetTarget(pPlayer->GetTransform());
}
