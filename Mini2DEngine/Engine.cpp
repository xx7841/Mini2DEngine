#include "pch.h"
#include "Engine.h"

#include "Project.h"
#include "TimerSystem.h"
#include "SceneManager.h"
#include "WindowSystem.h"
#include "GraphicsSystem.h"

namespace
{
	const int INITIALIZATION_FAILED = 0x0001;
	const int SHUTDOWN_FAILED = 0x0010;
}

Engine::Engine(Project* _project)
	:m_project(_project)
{
	assert(!m_isCreate);
	m_isCreate = true;
}



int Engine::MainLoop()
{
	if (!Initialize()) {
		return INITIALIZATION_FAILED;
	}

	srand(GetTickCount());

	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Update();
		Draw();
	}

	if (!Terminate()) {
		return SHUTDOWN_FAILED;
	}

	return msg.wParam;
}



bool Engine::Initialize()
{
	m_timer = new TimerSystem();
	if (m_timer == nullptr) {
		return false;
	}

	m_window = new WindowSystem();
	if (m_window == nullptr) {
		return false;
	}

	if (GraphicsSystem::Instance() == nullptr) {
		return false;
	}

	m_sceneManager = new SceneManager();
	if (m_sceneManager == nullptr) {
		return false;
	}

	if (m_timer->Initialize() == false) {
		return false;
	}

	// 반드시 Window를 먼저 초기화시켜야함.
	if (m_window->Initialize() == false) {
		return false;
	}

	if (GraphicsSystem::Instance()->Initialize(m_window) == false) {
		return false;
	}

	m_project->SetSceneManager(m_sceneManager);
	if (m_project->BindScene() == false) {
		return false;
	}

	return true;
}

bool Engine::Terminate()
{
	m_timer->Terminate();
	m_window->Terminate();
	m_sceneManager->Terminate();
	GraphicsSystem::Instance()->Terminate();

	delete m_project;

	delete m_timer;
	delete m_window;
	delete m_sceneManager;
	delete GraphicsSystem::Instance();

	return true;
}

void Engine::Update()
{
	m_timer->Update();
	m_sceneManager->Update();
}

void Engine::Draw()
{
	GraphicsSystem::Instance()->GetRT()->BeginDraw();
	GraphicsSystem::Instance()->GetRT()->Clear();

	m_sceneManager->Draw();

	GraphicsSystem::Instance()->GetRT()->EndDraw();
}

bool Engine::m_isCreate = false;