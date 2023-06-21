#pragma once
#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
	float x;
	float y;
} Camera;

void setCameraPos(Camera* pCam, const float X, const float Y);
void moveCameraLeft(Camera* pCam, const float MOVESTEP);
void moveCameraRight(Camera* pCam, const float MOVESTEP);
void moveCameraUp(Camera* pCam, const float MOVESTEP);
void moveCameraDown(Camera* pCam, const float MOVESTEP);

#endif
