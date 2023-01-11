#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	rc = new ObRect();
	rc->scale = Vector2(400.0f, 400.0f);
}

void Main::Release()
{
	SafeDelete(rc);
}

void Main::Update()
{
	rc->Update();
}

void Main::LateUpdate()
{
	if (rc->Intersect(INPUT->GetWorldMousePos()))
	{
		Vector2 dis = INPUT->GetWorldMousePos() - rc->GetWorldPos();
		dis.Normalize();

		if (INPUT->KeyPress(VK_LBUTTON))
		{
			Vector2 velocity = INPUT->GetWorldMousePos() - lastPos;
			rc->MoveWorldPos(velocity);
		}

		rc->color = Color(dis.x, dis.y, 0.5f, 1.0f);
	}
	else
	{
		rc->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
	}
}

void Main::Render()
{
	rc->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(1400.0f, 800.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}