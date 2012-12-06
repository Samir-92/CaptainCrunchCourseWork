#pragma once
#include "Win32Window.h"
#include "Timer.h"
#include <D3D10.h>
#include <D3DX10.h>

#include "GameObjectManager.h"

#include "MaterialComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "DirectionLightComponent.h"
#include "MeshComponent.h"

#include "ModelLoader.h"
#include "GUIManager.h"

#include <vector>

using namespace std;

enum GameState
{
	MAINMENU,
	GAME,
	PAUSE,
	EXIT
};

class CGameApplication
{
public:
	CGameApplication(void);
	~CGameApplication(void);
	bool init();
	void run();
private:
	bool initInput();
	bool initGame();
	bool initGraphics();
	bool initGUI();
	bool initWindow();
	void render();
	void update();

	void initTheGame();
	void initMenu();

	void updateGame();
	void updateMenu();
	void updatePauseGUI();
private:
	//Graphics
	ID3D10Device * m_pD3D10Device;
	IDXGISwapChain * m_pSwapChain;
	ID3D10RenderTargetView * m_pRenderTargetView;
	ID3D10DepthStencilView * m_pDepthStencelView;
	ID3D10Texture2D *m_pDepthStencilTexture;

	CWin32Window * m_pWindow;

	CTimer m_Timer;
	
	//Get Game Object Manager
	CGameObjectManager *m_pGameObjectManager;

	CModelLoader modelloader;

	Rocket::Core::ElementDocument *m_pMenu;
	Rocket::Core::ElementDocument *m_pGameGUI;
	Rocket::Core::ElementDocument *m_pPauseGUI;

	GameState m_GameState;
	float m_fCurrentTime;
};