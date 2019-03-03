
// EXTERNAL INCLUDES
#include <string>
// INTERNAL INCLUDES
#include "application.h"
#include "systems/filesystem.h"
#include "typedefs/cvar.h"
#include "math/mat4x4.h"

//If Debugmode is active use the main function. If not use the WinMain function.
#if defined(NDEBUG)
	int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
ui32 main(ui32 argc, char** argv)
#endif
{
	srand(time(NULL));
	std::string gamepathstr = static_cast<std::string>(argv[0]);
	for (char& sign : gamepathstr)
	{
		if (sign == '\\') 
		{
			sign = '/';
		}
	}
	gamepathstr = gamepathstr.substr(0, gamepathstr.find_last_of("/") + 1);
	CVar gamepath = {"gamepath", gamepathstr.c_str()};
	Console::GetInstancePtr()->SetCVar(gamepath);

	//Execute the application functions.
	Application::GetInstancePtr()->Initialize("Game", iVec2{ 1200, 800 }, 1);
	Application::GetInstancePtr()->Update();
	Application::GetInstancePtr()->CleanUp();
}
