#include "GameApplication.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Input.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "ModelLoader.h"

CGameApplication::CGameApplication(void)
{
	m_pWindow=NULL;
	m_pD3D10Device=NULL;
	m_pRenderTargetView=NULL;
	m_pSwapChain=NULL;
	m_pDepthStencelView=NULL;
	m_pDepthStencilTexture=NULL;
	m_pGameObjectManager=new CGameObjectManager();
}

CGameApplication::~CGameApplication(void)
{
	if (m_pD3D10Device)
		m_pD3D10Device->ClearState();

	if (m_pGameObjectManager)
	{
		delete m_pGameObjectManager;
		m_pGameObjectManager=NULL;
	}

	if (m_pRenderTargetView)
		m_pRenderTargetView->Release();
	if (m_pDepthStencelView)
		m_pDepthStencelView->Release();
	if (m_pDepthStencilTexture)
		m_pDepthStencilTexture->Release();
	if (m_pSwapChain)
		m_pSwapChain->Release();
	if (m_pD3D10Device)
		m_pD3D10Device->Release();
	if (m_pWindow)
	{
		delete m_pWindow;
		m_pWindow=NULL;
	}
}

bool CGameApplication::init()
{
	if (!initWindow())
		return false;
	if (!initGraphics())
		return false;
	if (!initInput())
		return false;
	if (!initAudio())
		return false;
	if (!initGame())
		return false;
	return true;
}

bool CGameApplication::initGame()
{
    // Set primitive topology, how are we going to interpet the vertices in the vertex buffer - BMD
    //http://msdn.microsoft.com/en-us/library/bb173590%28v=VS.85%29.aspx - BMD
    m_pD3D10Device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );	


	CGameObject *pTestGameObject=new CGameObject();
	//Set the name
	pTestGameObject->setName("Sky");
	CMeshComponent *pMesh=modelloader.loadModelFromFile(m_pD3D10Device,"sphere.fbx");
	//CMeshComponent *pMesh=modelloader.createCube(m_pD3D10Device,10.0f,10.0f,10.0f);
	pMesh->SetRenderingDevice(m_pD3D10Device);
	CMaterialComponent *pMaterial=new CMaterialComponent();
	pMaterial=new CMaterialComponent();
	pMaterial->SetRenderingDevice(m_pD3D10Device);
	pMaterial->setEffectFilename("Environment.fx");
	pMaterial->loadEnvironmentTexture("Mars.dds");
	pTestGameObject->addComponent(pMaterial);
	pTestGameObject->addComponent(pMesh);
	//add the game object
	m_pGameObjectManager->addGameObject(pTestGameObject);

	//Create Game Object
	pTestGameObject=new CGameObject();
	//Set the name
	pTestGameObject->setName("Test");
	//Position
	pTestGameObject->getTransform()->setPosition(0.0f,0.0f,0.0f);
	//create material
	pMaterial=new CMaterialComponent();
	pMaterial->SetRenderingDevice(m_pD3D10Device);
	pMaterial->setEffectFilename("Parallax.fx");
	pMaterial->setAmbientMaterialColour(D3DXCOLOR(0.2f,0.2f,0.2f,1.0f));
	pMaterial->loadDiffuseTexture("armoredrecon_diff.png");
	pMaterial->loadSpecularTexture("armoredrecon_spec.png");
	pMaterial->loadBumpTexture("armoredrecon_N.png");
	pMaterial->loadParallaxTexture("armoredrecon_Height.png");
	pTestGameObject->addComponent(pMaterial);
	pTestGameObject->getTransform()->setcarSpeed(10);
		//Audio - Create our Audio Component
	CAudioSourceComponent *pAudio=new CAudioSourceComponent();
	//Audio - If its a wav file, you should not stream
	pAudio->setFilename("Zombiesound.wav");
	//Audio - stream set to false
	pAudio->setStream(false);
	//Audio - Add it to the Game Object
	pTestGameObject->addComponent(pAudio);

	//Create Mesh
	pMesh=modelloader.loadModelFromFile(m_pD3D10Device,"armoredrecon.fbx");
	//CMeshComponent *pMesh=modelloader.createCube(m_pD3D10Device,10.0f,10.0f,10.0f);
	pMesh->SetRenderingDevice(m_pD3D10Device);
	pTestGameObject->addComponent(pMesh);
	//add the game object
	m_pGameObjectManager->addGameObject(pTestGameObject);

	pTestGameObject=new CGameObject();
	//Set the name
	pTestGameObject->setName("floor");
	//Position
	pTestGameObject->getTransform()->setPosition(0.0f,0.0f,200.0f);
	pTestGameObject->getTransform()->setRotation(180.0f,0.0f,0.0f);
	//create material
	pMaterial=new CMaterialComponent();
	pMaterial->SetRenderingDevice(m_pD3D10Device);
	pMaterial->setEffectFilename("DirectionalLight.fx");
	pMaterial->setAmbientMaterialColour(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f));
	pMaterial->loadDiffuseTexture("Floor.png");
	//pMaterial->loadSpecularTexture("Floor.png");
	pTestGameObject->addComponent(pMaterial);

	//Create Mesh
	pMesh=modelloader.loadModelFromFile(m_pD3D10Device,"floor.fbx");
	//CMeshComponent *pMesh=modelloader.createCube(m_pD3D10Device,10.0f,10.0f,10.0f);
	pMesh->SetRenderingDevice(m_pD3D10Device);
	pTestGameObject->addComponent(pMesh);
	//add the game object
	m_pGameObjectManager->addGameObject(pTestGameObject);

	pTestGameObject=new CGameObject();
	//Set the name
	pTestGameObject->setName("Barrel");
	//Position
	pTestGameObject->getTransform()->setPosition(0.0f,0.0f,3.0f);
	pTestGameObject->getTransform()->setScale(0.01f,0.01f,0.01f);
	//create material
	pMaterial=new CMaterialComponent();
	pMaterial->SetRenderingDevice(m_pD3D10Device);
	pMaterial->setEffectFilename("Bumpmapping.fx");
	pMaterial->setAmbientMaterialColour(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f));
	pMaterial->loadDiffuseTexture("barrel_color_02.png");
	pMaterial->loadSpecularTexture("barrel_spec_02.png");
	pMaterial->loadBumpTexture("barrel_nmap_02.png");
    pTestGameObject->addComponent(pMaterial);

	//Create Mesh
	pMesh=modelloader.loadModelFromFile(m_pD3D10Device,"barrel.fbx");
	//CMeshComponent *pMesh=modelloader.createCube(m_pD3D10Device,10.0f,10.0f,10.0f);
	pMesh->SetRenderingDevice(m_pD3D10Device);
	pTestGameObject->addComponent(pMesh);
	//add the game object
	m_pGameObjectManager->addGameObject(pTestGameObject);

	pTestGameObject=new CGameObject();
	//Set the name
	pTestGameObject->setName("Barrel2");
	//Position
	pTestGameObject->getTransform()->setPosition(1.0f,0.0f,3.0f);
	pTestGameObject->getTransform()->setScale(0.01f,0.01f,0.01f);
	//create material
	pMaterial=new CMaterialComponent();
	pMaterial->SetRenderingDevice(m_pD3D10Device);
	pMaterial->setEffectFilename("Bumpmapping.fx");
	pMaterial->setAmbientMaterialColour(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f));
	pMaterial->loadDiffuseTexture("barrel_color_01.png");
	pMaterial->loadSpecularTexture("barrel_spec_01.png");
	pMaterial->loadBumpTexture("barrel_nmap_01.png");
    pTestGameObject->addComponent(pMaterial);

	//Create Mesh
	pMesh=modelloader.loadModelFromFile(m_pD3D10Device,"barrel.fbx");
	//CMeshComponent *pMesh=modelloader.createCube(m_pD3D10Device,10.0f,10.0f,10.0f);
	pMesh->SetRenderingDevice(m_pD3D10Device);
	pTestGameObject->addComponent(pMesh);
	//add the game object
	m_pGameObjectManager->addGameObject(pTestGameObject);
	
	pTestGameObject=new CGameObject();
	//Set the name
	pTestGameObject->setName("Zombie");
	//Position
	pTestGameObject->getTransform()->setPosition(0.0f,0.0f,-1.0f);
	pTestGameObject->getTransform()->setScale(0.01f,0.01f,0.01f);
	pTestGameObject->getTransform()->setIsMoving(true);
	pTestGameObject->getTransform()->setMovementDirection(true);
	//create material for zombie
	pMaterial=new CMaterialComponent();
	pMaterial->SetRenderingDevice(m_pD3D10Device);
	pMaterial->setEffectFilename("DirectionalLight.fx");
	pMaterial->setAmbientMaterialColour(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f));
	//pMaterial->loadDiffuseTexture("ZOMBIE.png");
	//pMaterial->loadSpecularTexture("barrel_spec_01.png");
	//pMaterial->loadBumpTexture("barrel_nmap_01.png");
    pTestGameObject->addComponent(pMaterial);

	//Create Mesh
	pMesh=modelloader.loadModelFromFile(m_pD3D10Device,"humanoid.fbx");
	//CMeshComponent *pMesh=modelloader.createCube(m_pD3D10Device,10.0f,10.0f,10.0f);
	pMesh->SetRenderingDevice(m_pD3D10Device);
	pTestGameObject->addComponent(pMesh);
	//add the game object
	m_pGameObjectManager->addGameObject(pTestGameObject);

	pTestGameObject=new CGameObject();
	//Set the name
	pTestGameObject->setName("Zombie2");
	//Position
	pTestGameObject->getTransform()->setPosition(1.0f,0.0f,1.0f);
	pTestGameObject->getTransform()->setScale(0.01f,0.01f,0.01f);
	pTestGameObject->getTransform()->setIsMoving(true);
	pTestGameObject->getTransform()->setMovementDirection(true);
	//create material for zombie
	pMaterial=new CMaterialComponent();
	pMaterial->SetRenderingDevice(m_pD3D10Device);
	pMaterial->setEffectFilename("DirectionalLight.fx");
	pMaterial->setAmbientMaterialColour(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f));
	//pMaterial->loadDiffuseTexture("ZOMBIE.png");
	//pMaterial->loadSpecularTexture("barrel_spec_01.png");
	//pMaterial->loadBumpTexture("barrel_nmap_01.png");
    pTestGameObject->addComponent(pMaterial);

	//Create Mesh
	pMesh=modelloader.loadModelFromFile(m_pD3D10Device,"humanoid.fbx");
	//CMeshComponent *pMesh=modelloader.createCube(m_pD3D10Device,10.0f,10.0f,10.0f);
	pMesh->SetRenderingDevice(m_pD3D10Device);
	pTestGameObject->addComponent(pMesh);
	//add the game object
	m_pGameObjectManager->addGameObject(pTestGameObject);


	CGameObject *pCameraGameObject=new CGameObject();
	//pCameraGameObject->getTransform()->setPosition(0.0f,2.0f,-5.0f);
	pCameraGameObject->setName("Camera");

	D3D10_VIEWPORT vp;
	UINT numViewports=1;
	m_pD3D10Device->RSGetViewports(&numViewports,&vp);

	CCameraComponent *pCamera=new CCameraComponent();
	pCamera->setPosition(0.0f,20.0f,-5.0f);
	pCamera->setUp(0.0f,1.0f,0.0f);
	pCamera->setLookAt(0.0f,10.0f,0.0f);
	pCamera->setFOV(D3DX_PI*0.25f);
	pCamera->setAspectRatio((float)(vp.Width/vp.Height));
	pCamera->setFarClip(1000.0f);
	pCamera->setNearClip(0.1f);
	//Debug to default
	pCamera->setDebug(false);
	pCameraGameObject->addComponent(pCamera);

	pCamera->setTarget(m_pGameObjectManager->findGameObject("Test"));

	m_pGameObjectManager->addGameObject(pCameraGameObject);

	//Audio - Create another audio component for music
	CAudioSourceComponent *pMusic=new CAudioSourceComponent();
	//Audio -If it is an mp3 or ogg then set stream to true
	pMusic->setFilename("zombie.mp3");
	//Audio - stream to true
	pMusic->setStream(true);
	//Audio - Add to camera, don't call play until init has been called
	pCameraGameObject->addComponent(pMusic);

	//Audio - Attach a listener to the camera
	CAudioListenerComponent *pListener=new CAudioListenerComponent();
	pCameraGameObject->addComponent(pListener);

	CGameObject *pLightGameObject=new CGameObject();
	pLightGameObject->setName("DirectionalLight");

	CDirectionalLightComponent *pLightComponent=new CDirectionalLightComponent();
	pLightComponent->setDirection(D3DXVECTOR3(0.0f,0.0f,-1.0f));
	pLightGameObject->addComponent(pLightComponent);

	m_pGameObjectManager->addGameObject(pLightGameObject);

	m_pGameObjectManager->setMainLight(pLightComponent);

	//init, this must be called after we have created all game objects
	m_pGameObjectManager->init();
	
	pMusic->play();

	m_Timer.start();
	return true;
}

void CGameApplication::run()
{
	while(m_pWindow->running())
	{
		if (! m_pWindow->checkForWindowMessages())
		{
			update();
			render();
		}
	}
}

void CGameApplication::render()
{
    // Just clear the backbuffer, colours start at 0.0 to 1.0
	// Red, Green , Blue, Alpha - BMD
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; 
	//Clear the Render Target
	//http://msdn.microsoft.com/en-us/library/bb173539%28v=vs.85%29.aspx - BMD
    m_pD3D10Device->ClearRenderTargetView( m_pRenderTargetView, ClearColor );
	m_pD3D10Device->ClearDepthStencilView(m_pDepthStencelView,D3D10_CLEAR_DEPTH,1.0f,0);
	//We need to iterate through all the Game Objects in the managers
	for(vector<CGameObject*>::iterator iter=m_pGameObjectManager->getBegining();iter!=m_pGameObjectManager->getEnd();iter++)
	{
		//grab the transform
		CTransformComponent *pTransform=(*iter)->getTransform();
		//and the geometry
		CMeshComponent *pMesh=static_cast<CMeshComponent*>((*iter)->getComponent("MeshComponent"));
		//and the material
		CMaterialComponent *pMaterial=static_cast<CMaterialComponent*>((*iter)->getComponent("MaterialComponent"));

		//do we have a matrial
		if (pMaterial)
		{
			CCameraComponent *camera=m_pGameObjectManager->getMainCamera();

			//set the matrices
			pMaterial->setProjectionMatrix((float*)camera->getProjection());
			pMaterial->setViewMatrix((float*)camera->getView());
			pMaterial->setWorldMatrix((float*)pTransform->getWorld());
			//set light colour
			pMaterial->setAmbientLightColour(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f));

			//get the main light and the camera
			CDirectionalLightComponent * light=m_pGameObjectManager->getMainLight();
			pMaterial->setDiffuseLightColour(light->getDiffuseColour());
			pMaterial->setSpecularLightColour(light->getSpecularColour());
			pMaterial->setLightDirection(light->getLightDirection());
			
			pMaterial->setCameraPosition(camera->getParent()->getTransform()->getPosition());

			pMaterial->setTextures();
			pMaterial->setMaterial();
			//bind the vertex layout
			pMaterial->bindVertexLayout();
			//loop for the passes in the material
			for (UINT i=0;i<pMaterial->getNumberOfPasses();i++)
			{
				//Apply the current pass
				pMaterial->applyPass(i);
				//we have a geometry
				if (pMesh)
				{
					//Loop through all the subsets in the mesh
					for (int i=0;i<pMesh->getTotalNumberOfSubsets();i++)
					{
						//grab one of the subset
						CGeometry *pSubset=pMesh->getSubset(i);
						//bind the buffers contained in the subset
						pSubset->bindBuffers();
						//draw
						m_pD3D10Device->DrawIndexed(pSubset->getNumberOfIndices(),0,0);
					}
				}
			}
		}

	}
	//Swaps the buffers in the chain, the back buffer to the front(screen)
	//http://msdn.microsoft.com/en-us/library/bb174576%28v=vs.85%29.aspx - BMD
    m_pSwapChain->Present( 0, 0 );
}

void CGameApplication::update()
{
	m_Timer.update();

	//Recognize the camera
	CCameraComponent * pCamera=m_pGameObjectManager->getMainCamera();

	if (CInput::getInstance().getKeyboard()->isKeyDown((int)'W'))
	{
		if(!pCamera->isDebug()){
	
			CAudioSourceComponent *pAudio=(CAudioSourceComponent*)m_pGameObjectManager->findGameObject("Test")->getComponent("AudioSourceComponent");
	
			CTransformComponent * pTransform=m_pGameObjectManager->findGameObject("Test")->getTransform();
			pTransform->MoveForward(m_Timer.getElapsedTime()*pTransform->getcarspeed());
			pAudio->play();

		}else{
			//Move the debug camera -- doesn't work yet.
			D3DXVECTOR3 cameraNewPosition = D3DXVECTOR3(m_Timer.getElapsedTime()*-30, 0, 0);
			pCamera->setPosition(pCamera->getPosition().x + cameraNewPosition.x, cameraNewPosition.y, cameraNewPosition.z);
		}
	}
	else if (CInput::getInstance().getKeyboard()->isKeyDown((int)'S'))
	{
		//play sound
		CTransformComponent * pTransform=m_pGameObjectManager->findGameObject("Test")->getTransform();
		pTransform->MoveForward(m_Timer.getElapsedTime()*-(pTransform->getcarspeed()));
		
	}
	if (CInput::getInstance().getKeyboard()->isKeyDown((int)'A'))
	{
		//play sound
		CTransformComponent * pTransform=m_pGameObjectManager->findGameObject("Test")->getTransform();
		pTransform->rotate(0.0f,m_Timer.getElapsedTime()*-1,0.0f);
	}
	else if (CInput::getInstance().getKeyboard()->isKeyDown((int)'D'))
	{
		//play sound
		CTransformComponent * pTransform=m_pGameObjectManager->findGameObject("Test")->getTransform();
		pTransform->rotate(0.0f,m_Timer.getElapsedTime(),0.0f);
	}

	//Do we want to go to debug mode with the camera -- doesn't work yet.
	if (CInput::getInstance().getKeyboard()->isKeyDown((int)'P'))
	{
		if(pCamera->isDebug()){
			pCamera->setDebug(false);
		}else{
			pCamera->setDebug(true);
		}
	}

	m_pGameObjectManager->update(m_Timer.getElapsedTime());
	
	CTransformComponent * pZombie=m_pGameObjectManager->findGameObject("Zombie")->getTransform();
	CTransformComponent * pZombie2=m_pGameObjectManager->findGameObject("Zombie2")->getTransform();
	//while(!pZombie->getIsMoving()){
	if(pZombie->getIsMoving() || pZombie2->getIsMoving()){
		//Move the zombie bitch!
		pZombie->enemyMovement(m_Timer.getElapsedTime());
		pZombie2->enemyMovementLR(m_Timer.getElapsedTime());
		//pZombie->setIsMoving(true);
		//pZombie->setRotation(0.1f,0.0f,0.1f);
		//pZombie->enemyMovement(m_Timer.getElapsedTime());
	}
}

bool CGameApplication::initInput()
{
	CInput::getInstance().init();
	return true;
}
bool CGameApplication::initAudio()
{
	CAudioSystem::getInstance().init();
	return true;
}

//initGraphics - initialise the graphics subsystem - BMD
bool CGameApplication::initGraphics()
{
	//Retrieve the size of the window, this is need to match the
	//back buffer to screen size - BMD
	RECT windowRect;
	//http://msdn.microsoft.com/en-us/library/ms633503%28v=vs.85%29.aspx -BMD
	GetClientRect(m_pWindow->getHandleToWindow(),&windowRect);

	//Calculate the width and height of the window - BMD
	UINT width=windowRect.right-windowRect.left;
	UINT height=windowRect.bottom-windowRect.top;

	//Device creation flags, used to control our the D3D10 device is created
	UINT createDeviceFlags=0;
	//If we are in a debug build then set the device creation flag to debug device
#ifdef _DEBUG
	createDeviceFlags|=D3D10_CREATE_DEVICE_DEBUG;
#endif

	//Swap Chain description - used in the creation of the swap chain
	//http://msdn.microsoft.com/en-us/library/bb173075%28v=vs.85%29.aspx - BMD

	//Initialise the swap chain description by setting all its values to zero - BMD
	DXGI_SWAP_CHAIN_DESC sd;
	//http://msdn.microsoft.com/en-us/library/aa366920%28v=vs.85%29.aspx - BMD
    ZeroMemory( &sd, sizeof( sd ) );
	//What kind of surface is contained in the swap chain, in this case something we draw too
	//http://msdn.microsoft.com/en-us/library/bb173078%28v=vs.85%29.aspx - BMD
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//Number of buffers, if we are not full screen this will be one as the desktop
	//acts as a front buffer. If we are in full screen this will be one - BMD
	if (m_pWindow->isFullScreen())
		sd.BufferCount = 2;
	else 
		sd.BufferCount=1;
	//The handle of the window which this swap chain is linked to, this must not be NULL - BMD
	sd.OutputWindow = m_pWindow->getHandleToWindow();
	//Are we in windowed mode, arggh opposite of full screen
	sd.Windowed = (BOOL)(!m_pWindow->isFullScreen());
	//Multisampling(antialsing) parameters for the swap chain - this has performance considerations - see remarks in docs
	//http://msdn.microsoft.com/en-us/library/bb173072%28v=vs.85%29.aspx - BMD
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
	//The description of the swap chain buffer
	//http://msdn.microsoft.com/en-us/library/bb173064%28v=vs.85%29.aspx - BMD
	//width & height of the buffer - this matches the size of the window - BMD
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
	//The data format of the buffer in the swap chain, 8bits used for Red, green, blue & alpha - unsigned int(UNIFORM) - BMD
	//http://msdn.microsoft.com/en-us/library/bb173059%28v=vs.85%29.aspx
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//Refresh rate of the buffer in the swap chain - BMD
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
	
	//NB. You should get use to seeing patterns like this when programming with D3D10 
	//where we use a description object which is then used in the creation of a D3D10 resource 
	//like swap chains. Also in a real application we would check to see if some of the above
	//options are support by the graphics hardware. -BMD

	//Create D3D10 Device and swap chain 
	//http://msdn.microsoft.com/en-us/library/bb205087%28v=vs.85%29.aspx - BMD
	if (FAILED(D3D10CreateDeviceAndSwapChain(NULL, //Pointer to IDXGIAdpater, this is a display adapater on the machine this can be NULL - BMD
		D3D10_DRIVER_TYPE_HARDWARE,//Type of Driver we have, it can be a hardware device, refrence(slow) or Software(not supported yet) - BMD
		NULL, //Handle to a module that implements a software rasterizer - BMD
		createDeviceFlags,//The device creation flags we used earlier on - BMD
		D3D10_SDK_VERSION,//The version of the SDK we are using this should D3D10 - BMD
		&sd,//The memory address of the swap chain description - BMD
		&m_pSwapChain, //The memory address of the swap chain pointer, if all goes well this will be intialised after this function call - BMD
		&m_pD3D10Device)))//the memory address of the D3D10 Device, if all goes well this will be initialised after this function call - BMD
		return false;

	//NB. There are two ways of creating the device, the above way which initialises the device and swap chain at the sametime
	// or we can create a swap chain and a device seperatly and then associate a swap chain with a device. - BMD

	//Create a render target, this is a Texture which will hold our backbuffer, this will
	//enable us to link the rendertarget with buffer held in the swap chain - BMD
	ID3D10Texture2D *pBackBuffer;
	//Get a buffer from the swap chain 
	//http://msdn.microsoft.com/en-us/library/bb174570%28v=vs.85%29.aspx - BMD
	if (FAILED(m_pSwapChain->GetBuffer(0, //buffer index, 0 will get the back buffer
		__uuidof(ID3D10Texture2D),//The unique identifier of the type of pointer we want in
								  //this case a I3D10 Texture2D
		(void**)&pBackBuffer)))//A pointer to a memory address, this is cast to a void ** because this function
							   //can return back different types dependent on the 2nd param
		return false;

	D3D10_TEXTURE2D_DESC descDepth;
	descDepth.Width=width;
	descDepth.Height=height;
	descDepth.MipLevels=1;
	descDepth.ArraySize=1;
	descDepth.Format=DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count=1;
	descDepth.SampleDesc.Quality=0;
	descDepth.Usage=D3D10_USAGE_DEFAULT;
	descDepth.BindFlags=D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags=0;
	descDepth.MiscFlags=0;

	if (FAILED(m_pD3D10Device->CreateTexture2D(&descDepth,NULL,&m_pDepthStencilTexture)))
		return false;

	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format=descDepth.Format;
	descDSV.ViewDimension=D3D10_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice=0;

	if (FAILED(m_pD3D10Device->CreateDepthStencilView(m_pDepthStencilTexture,&descDSV,&m_pDepthStencelView)))
		return false;


	//Create the Render Target View, a view is the way we access D3D10 resources
	//http://msdn.microsoft.com/en-us/library/bb173556%28v=vs.85%29.aspx - BMD
	if (FAILED(m_pD3D10Device->CreateRenderTargetView( pBackBuffer, //The resource we are creating the view for - BMD
		NULL, //The description of the view, in this case NULL - BMD
		&m_pRenderTargetView ))) // the memory address of a pointer to D3D10 Render Target - BMD
	{
		
		pBackBuffer->Release();
		return  false;
	}
	//The above Get Buffer call will allocate some memory, we now need to release it. - BMD
    pBackBuffer->Release();

	//Binds one or more render targets and depth buffer to the Output merger stage - BMD
	//http://msdn.microsoft.com/en-us/library/bb173597%28v=vs.85%29.aspx - BMD
	m_pD3D10Device->OMSetRenderTargets(1, //Number  of views - BMD
		&m_pRenderTargetView, //pointer to an array of D3D10 Render Target Views - BMD
		m_pDepthStencelView); //point to Depth Stencil buffer - BMD

    // Setup the viewport 
	//http://msdn.microsoft.com/en-us/library/bb172500%28v=vs.85%29.aspx - BMD
    D3D10_VIEWPORT vp;
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
	//Sets the Viewport 
	//http://msdn.microsoft.com/en-us/library/bb173613%28v=vs.85%29.aspx - BMD
    m_pD3D10Device->RSSetViewports( 1 //Number of viewports to bind
		, &vp );//an array of viewports

	return true;
}

bool CGameApplication::initWindow()
{
	m_pWindow=new CWin32Window();
	if (!m_pWindow->init(TEXT("Games Programming"),800,640,false))
		return false;
	return true;
}