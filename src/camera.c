#include "./camera.h"

void setCameraPos(Camera* pCam, const float X, const float Y)
{
	pCam->x = X;
	pCam->y = Y;
}

void moveCameraLeft(Camera* pCam, const float MOVESTEP)
{
	pCam->x -= MOVESTEP;
}

void moveCameraRight(Camera* pCam, const float MOVESTEP)
{
	pCam->x += MOVESTEP;
}

void moveCameraUp(Camera* pCam, const float MOVESTEP)
{
	pCam->y -= MOVESTEP;
}

void moveCameraDown(Camera* pCam, const float MOVESTEP)
{
	pCam->y += MOVESTEP;
}