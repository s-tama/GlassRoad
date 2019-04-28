//
// StageManager.h
// Actor: Tamamura Shuuki
// Date: 2019/04/13(日)
//
#pragma once

#include "MyLibrary.h"


/// <summary>
/// シーンマネージャーコンポーネント
/// </summary>
class StageManager : public MyLibrary::Behaviour
{
public:

	StageManager(MyLibrary::GameObject* pGameObject);

	void Start();
	void Update();

	// プロパティ
	void AddStageChip(std::vector<MyLibrary::GameObject*> const& pStageChips) { m_pStageChips = pStageChips; }


private:

	std::vector<MyLibrary::GameObject*> m_pStageChips;
};
