/*
-------------------------------------------------------------------------
//Assignment 1
// author : Negar Saeidi - 101261396
// main.cpp Main entry of the engine
-------------------------------------------------------------------------*/
#include "Game.hpp"

 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		Game game(hInstance);
		if (!game.Initialize())
			return 0;

		return game.Run();
	}
	catch (DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}










//CBVs will be set at different frequencies—the per pass CBV only needs to be set once per
//rendering pass while the per object CBV needs to be set per render item








