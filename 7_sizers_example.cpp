#pragma once
#include "wx/setup.h"
#include <wx/slider.h>
#include <wx/image.h>
#include <wx/control.h>
#include <wx/wxprec.h>
#include <wx/wx.h>


class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};


class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
};

wxIMPLEMENT_APP(MyApp);





bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
	frame->Show(true);
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	wxPanel* main_window = new wxPanel(this, wxID_ANY);	
	main_window->SetBackgroundColour(wxColour(255, 0, 0, 255));
	
	wxBoxSizer *main_sizer = new wxBoxSizer(wxHORIZONTAL);
	main_window->SetSizer(main_sizer);
	wxPanel* window1 = new wxPanel(main_window, wxID_ANY, wxDefaultPosition);
	wxPanel* window2 = new wxPanel(main_window, wxID_ANY, wxDefaultPosition);
	window1->SetBackgroundColour(wxColour(255, 255, 0, 255));
	window2->SetBackgroundColour(wxColour(0, 255, 0, 255));
	main_sizer->Add(window1, 1, wxEXPAND, wxALL);
	main_sizer->Add(window2, 1, wxEXPAND, wxALL);
	main_sizer->Fit(main_window);
	main_sizer->SetSizeHints(main_window);
}


