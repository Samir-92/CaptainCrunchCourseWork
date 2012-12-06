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

// 360 controller
#include "CXBOXController.h"

//Audio - Includes
#include "AudioListenerComponent.h"
#include "AudioSourceComponent.h"
#include "AudioSystem.h"

//Physics
#include "Physics.h"
#include "BodyComponent.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include <vector>

using namespace std;

class CGameApplication:public hkpContactListener 
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
	bool initPhysics();
	bool initAudio();
	bool initWindow();
	void render();
	void update();
	
	void contactPointCallback (const hkpContactPointEvent &event); 

private:
	//Graphics
	ID3D10Device * m_pD3D10Device;
	IDXGISwapChain * m_pSwapChain;
	ID3D10RenderTargetView * m_pRenderTargetView;
	ID3D10DepthStencilView * m_pDepthStencelView;
	ID3D10Texture2D *m_pDepthStencilTexture;
	CWin32Window * m_pWindow;
	CTimer m_Timer;

	//360 controller
	CXBOXController* Player1;
	
	//Get Game Object Manager
	CGameObjectManager *m_pGameObjectManager;

	CModelLoader modelloader;
};