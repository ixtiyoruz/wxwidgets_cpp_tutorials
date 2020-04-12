#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include "wx/thread.h"
#endif
class cvWorker : public wxThread {
public:
	/* Essentials for thread */
	cvWorker();
	~cvWorker();
	virtual void *Entry();
	virtual void OnExit();
};
