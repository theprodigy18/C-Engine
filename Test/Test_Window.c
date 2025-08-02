#include <EngineAPI.h>

#include <crtdbg.h>

int main()
{

	WndInitProps props;
	props.title = "Window";
	props.width = 1280;
	props.height = 720;

    WndHandle handle = NULL;
	API_CreateWindow(&handle, &props);

	bool running = true;

	while (running)
    {
		running = API_PollEvents();
    }

	API_DestroyWindow(&handle);

    _CrtDumpMemoryLeaks(); // panggil ini sebelum return di main()
	return 0;
}