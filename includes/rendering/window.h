
#pragma once
// EXTERNAL INCLUDES
#include <vector>
// INTERNAL INCLUDES
#include "typedefs/types.h"
#include "typedefs/utils.h"
#include "typedefs/display.h"

//Class Window
class Window 
{
	//Define Window as a singleton. See utils.h for definition.
	DEFINE_SINGLETON(Window)

	//Define Window as a friend of Renderer.
	friend class Renderer;

//Declare public functions.
public:
	void Instantiate(char* title, ui32 width, ui32 height, ui32 displayID);
	void DispatchMessages(void);
	void AddDisplay(const Display& display);
	Display* GetDisplay(ui32 id) const;

//Declare protected variables.
protected:
	HWND handle;

//Declare private variables.
private:
	std::vector<Display> displays;
};
