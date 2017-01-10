// Win32Project11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <pxccapturemanager.h>
#include <pxcsensemanager.h>
#include <util_render.h>
#include<conio.h>

int wmain(int argc,WCHAR* argv[])
{
	PXCSenseManager *sm = PXCSenseManager::CreateInstance();
	sm->EnableStream(PXCCapture::STREAM_TYPE_COLOR, 0, 0, 0, PXCCapture::Device::STREAM_OPTION_UNRECTIFIED);
	sm->EnableStream(PXCCapture::STREAM_TYPE_DEPTH, 320, 240, 0);
	sm->Init();
	UtilRender *renderColor = new UtilRender(L"COLOR STREAM");
	UtilRender *renderDepth = new UtilRender(L"DEPTH STREAM");
	PXCImage *colorIm, *depthIm;
	for (int i = 0; i<100; i++)
	{
		pxcStatus sts = sm ->AcquireFrame(true);
		if(sts<PXC_STATUS_NO_ERROR) break;
		PXCCapture::Sample *sample = sm->QuerySample();
		colorIm = sample->color;
		depthIm = sample->depth;
		if (!renderColor->RenderFrame(colorIm)) break;
		if (!renderDepth->RenderFrame(depthIm)) break;
		sm->ReleaseFrame();
	}
	
	sm->Release();

    return 0;
}

