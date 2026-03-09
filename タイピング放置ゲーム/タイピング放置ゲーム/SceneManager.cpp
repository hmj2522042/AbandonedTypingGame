#include "SceneManager.h"
#include "SceneBase.h"

void SceneManager::LoadScene(SceneBase* scene)
{
	// シーン遷移中なら無効
	if(m_nextScene)
	{
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}

	m_nextScene = scene;
	m_phase = Phase::SetUp;
}

void SceneManager::Update()
{
	switch (m_phase)
	{
	case Phase::Run:
		// 最後にpushbackしたシーンのみ更新
		if (!m_sceneList.empty()) m_sceneList.back()->Update();

		/*for (auto scene : m_sceneList)
		{
			scene->Update();
		}*/
		break;

	case Phase::SetUp:
		// 実行中のシーンがあるなら更新
		if (!m_sceneList.empty()) m_sceneList.back()->Update();

		m_nextScene->Initialize();

		for (auto scene : m_sceneList)
		{
			scene->Finalize();
			delete scene;
			scene = nullptr;
		}
		m_sceneList.clear();

		m_phase = Phase::Transition;
		break;

	case Phase::Transition:
		PushScene(m_nextScene);
		m_nextScene = nullptr;

		m_phase = Phase::Run;
		break;
	}
}

void SceneManager::Draw()
{
	for (auto scene : m_sceneList)
	{
		scene->Draw();
	}
}