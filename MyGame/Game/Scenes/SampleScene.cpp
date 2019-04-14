//
// SampleScene.cpp
//



// ヘッダーファイルのインクルード --------------------------------------------------------
#include "SampleScene.h"

#include "..\GameWorld\MainCamera.h"
#include "..\GameWorld\Player.h"



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
	MainCamera* pMainCamera = new MainCamera();
	Player* pPlayer = new Player();
}
