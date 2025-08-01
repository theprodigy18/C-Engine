#include <pch.h>
#include <Platform/Window.h>

#include <crtdbg.h>

int main()
{

	WndInitProps props;
	props.title = "Window";
	props.width = 1280;
	props.height = 720;

    WndHandle handle = NULL;
	Platform_CreateWindow(&handle, &props);

	bool running = true;

	while (running)
    {
		running = Platform_PollEvents();
    }

	Platform_DestroyWindow(&handle);

    _CrtDumpMemoryLeaks(); // panggil ini sebelum return di main()
	return 0;
}