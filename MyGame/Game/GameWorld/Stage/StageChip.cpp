//
// StageChip.cpp
// Actor: Tmamura Shuuki
// Date: 2019/04/13(日)
//

#include "StageChip.h"

#include "StageMesh.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ	
/// </summary>
StageChip::StageChip()
{
	SetTag("Floor");

	StageMesh* pMesh = AddComponent<StageMesh>();
	pMesh->Create();

	BoxCollider* pBox = AddComponent<BoxCollider>();
	pBox->SetStatus(Vector3::Zero, Vector3(0.5f, 0.5f, 0.5f));
}
