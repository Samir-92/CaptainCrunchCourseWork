#include <Windows.h>
#include "GameApplication.h"

int WINAPI WinMain(HINSTANCE hInstance, 
					HINSTANCE hPrevInstance, 
					LPSTR lpCmdLine,
					int nCmdShow)
{
	CGameApplication *pApp=new CGameApplication();

	if(!pApp -> init())
	{
		if(pApp)
		{
			delete pApp;
			pApp=NULL;
			return 1;
		}
	}
	pApp->run();

	if(pApp)
	{
		delete pApp;
		pApp=NULL;
	}
	return 0;
}
