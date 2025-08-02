#include <EngineAPI.h>

#include <crtdbg.h>
#include <math.h>

int main()
{

	WndInitProps props;
	props.title = "Window";
	props.width = 1280;
	props.height = 720;

    WndHandle handle = NULL;
	if (!API_CreateWindow(&handle, &props))
	{
		ASSERT(false);
		return -1;
	}

	GfxInitProps gfxProps;
	gfxProps.wndHandle = handle;
	GfxHandle gfx = NULL;

	if (!API_CreateGraphics(&gfx, &gfxProps))
	{
		ASSERT(false);
		return -1;
	}

	bool running = true;

	API_ShowWindow(handle);

	while (running)
    {
		running = API_PollEvents();
		API_SetCurrentGraphics(gfx);
        API_ClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        API_SwapBuffers(handle);
    }

	API_DestroyGraphics(&gfx);
	API_DestroyWindow(&handle);

    _CrtDumpMemoryLeaks(); // panggil ini sebelum return di main()
	return 0;
}