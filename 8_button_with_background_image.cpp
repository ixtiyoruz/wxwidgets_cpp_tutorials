#pragma once
#include "wx/setup.h"
#include <wx/slider.h>
#include <wx/image.h>
#include <wx/control.h>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "wx/bmpbuttn.h"

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

#include "Source.h"
bool MyApp::OnInit()
{
	// make sure to call this first
	wxInitAllImageHandlers();
	MyFrame *frame = new MyFrame("Hello World", wxPoint(50, 50), wxSize(1024, 768));
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
	main_sizer->Add(window2, 1, wxEXPAND, wxBORDER_NONE);
	main_sizer->Fit(main_window);
	main_sizer->SetSizeHints(main_window);

	// add button to second window 
	// button must be center aligned
	//wxButton drawer_btn = wxButton(window2, wxID_ANY, wxEmptyString, );	
	wxBoxSizer *sizer_window2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_window2_1 = new wxBoxSizer(wxVERTICAL);
	window2->SetSizer(sizer_window2);
	sizer_window2->Add(sizer_window2_1, 0, wxEXPAND, wxBORDER_NONE);
	
	wxBitmap 
		bitmap(wxT("C:/Users/Challenger/Documents/Visual Studio 2015/Projects/Win32Project2/x64/Release/buttons/foldbuttonright.png"), wxBITMAP_TYPE_PNG);
	//Size of window2 
	wxSize sizew2 = window2->GetSize();
	//size of bitmap to preserve resolution
	wxSize sizeimg = bitmap.GetSize();
	// we have to set width of the image so height should be based on aspect ratio
	float aspect_ratio = bitmap.GetSize().GetWidth() / bitmap.GetSize().GetHeight();
	// and we want our button contribute 1 of 50 of windows size
	int width_btn = 10;
	int height_btn = width_btn / aspect_ratio;
	//wxLogMessage((std::to_string(width_btn) +" " +std::to_string(height_btn)).c_str());

	wxButton* drawer_btn = new wxButton(window2, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxSize(width_btn, 10), wxTRANSPARENT_WINDOW );
	bitmap = wxBitmap(bitmap.ConvertToImage().Scale(width_btn, height_btn, wxIMAGE_QUALITY_HIGH));

	drawer_btn->SetBitmap(bitmap);
	//drawer_btn->SetBitmapHover(bmpSelected);
	//drawer_btn->SetBitmapPressed(bmpSelected);
	drawer_btn->SetBackgroundColour(window2->GetBackgroundColour());
	sizer_window2->Add(drawer_btn, 1, wxALIGN_CENTER_VERTICAL| wxALIGN_LEFT, wxBORDER_NONE);

	wxPanel* window3 = new wxPanel(window2, wxID_ANY, wxDefaultPosition);
	sizer_window2->Add(window3, 50, wxEXPAND, wxBORDER_NONE);
}

