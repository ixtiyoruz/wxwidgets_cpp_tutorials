//-------------------------------CustomSplitterWindow.h----------------------------------------------------------------
#pragma once
#include "wx/setup.h"
#include <wx/slider.h>
#include <wx/image.h>
#include <wx/control.h>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "wx/bmpbuttn.h"
#include <wx/frame.h>
#include <wx/splitter.h>
#include <wx/menu.h>
#include <wx/panel.h>
class MySplitterWindow :public wxSplitterWindow {
	
	public:
		// Constructors
		MySplitterWindow(){ Init(); }
		MySplitterWindow(wxWindow *parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxSP_3D,
			const wxString& name = wxT("splitter")) {

			Init();
			Create(parent, id, pos, size, style, name);
		}
	/*	bool Create(wxWindow *parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxSP_3D,
			const wxString& name = wxT("splitter"));
*/

// Paints the border and sash
		void OnPaint(wxPaintEvent& event);
		void DrawSash(wxDC& dc);

private:
};


//---------------------CustomSplitterWindow.cpp---------------------------------------------------------------
#include "CustomSplitterWindow.h"
#include <wx/dcbuffer.h>
#include "wx/renderer.h"
void  MySplitterWindow::OnPaint(wxPaintEvent& event) {

	wxBufferedPaintDC dc(this);
	DrawSash(dc);
	event.Skip();
};

void   MySplitterWindow::DrawSash(wxDC& dc) {
	// just do not draw it
}

//-------------------- Source.h-------------------------------------------------------------------------------

#pragma once
#include "wx/setup.h"
#include <wx/slider.h>
#include <wx/image.h>
#include <wx/control.h>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "wx/bmpbuttn.h"
#include <wx/frame.h>
#include <wx/splitter.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include "CustomSplitterWindow.h"
class WxSplitterWindow2Frame : public wxFrame
{
public:
	WxSplitterWindow2Frame(const wxString& title);
	

private:
	void OnMenuSplit(wxCommandEvent& evt);
	void OnUnsplit(wxSplitterEvent& evt);
	void m_splitterOnSplitterSashPosChanged(wxSplitterEvent& event);
	void m_splitterOnPaint(wxPaintEvent& event);
	void onResize(wxSizeEvent& event);
	void render(wxDC& myDC);
	void m_splitterOnErase(wxEraseEvent& event);
private:
	wxMenu* m_viewMenu;
	MySplitterWindow* m_splitterWindow;
	wxPanel* m_panel1;
	wxPanel* m_panel2;
	wxMutex p_GUImutex;

	wxDECLARE_EVENT_TABLE();
};


BEGIN_EVENT_TABLE(WxSplitterWindow2Frame, wxFrame)
//Size event
//EVT_SIZE(WxSplitterWindow2Frame::onResize)
//EVT_ERASE_BACKGROUND(MyWindow::OnErase)
END_EVENT_TABLE()


class WxSplitterWindow2App : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(WxSplitterWindow2App);
//----------------------------------Source.cpp---------------------------------------------------------------------------------

#include "Source.h"
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/defs.h>
#include <wx/dcbuffer.h>

#define wxWS_EX_BUFFERED_DRAW           0x00000040
#define wxWS_EX_PROCESS_UI_UPDATES      0x00000020

const wxWindowID SplitterWindowID = wxID_HIGHEST + 1;

const int SplitMenuID = wxID_HIGHEST + 2;

bool WxSplitterWindow2App::OnInit()
{
	// make sure to call this first
	wxInitAllImageHandlers();
	WxSplitterWindow2Frame* frame = new WxSplitterWindow2Frame("WxSplitterWindow2");
	frame->Show(true);
	return true;
}

WxSplitterWindow2Frame::WxSplitterWindow2Frame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title,wxDefaultPosition, wxSize(800, 500))
{
	this->SetBackgroundColour(wxColour(0, 0, 0, 255));
	this->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	// Create the wxSplitterWindow window
	m_splitterWindow = new MySplitterWindow(this, SplitterWindowID, wxDefaultPosition, wxDefaultSize, wxSP_NOBORDER| wxSP_LIVE_UPDATE);
	m_splitterWindow->SetSashGravity(0.5);	
	// Create the left panel
	m_panel1 = new wxPanel(m_splitterWindow, wxID_ANY, wxDefaultPosition, wxSize(200,200), wxNO_BORDER);
	m_panel1->SetBackgroundColour(wxColour(255, 0, 0, 255));

	// Create the right panel
	m_panel2 = new wxPanel(m_splitterWindow, wxID_ANY,wxDefaultPosition, wxSize(200, 200), wxNO_BORDER);
	m_panel2->SetBackgroundColour(wxColour(255, 0, 255, 255));


	// Split the window vertically and set the left and right panes
	m_splitterWindow->SplitVertically(m_panel1, m_panel2);
	m_splitterWindow->SetBackgroundStyle(wxBG_STYLE_PAINT);
	m_splitterWindow->Bind(wxEVT_PAINT, &WxSplitterWindow2Frame::m_splitterOnPaint, this);
	m_splitterWindow->Bind(wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED, &WxSplitterWindow2Frame::m_splitterOnSplitterSashPosChanged, this);
	m_splitterWindow->Bind(wxEVT_ERASE_BACKGROUND, &WxSplitterWindow2Frame::m_splitterOnErase, this);
	// Set up the sizer for the frame and resize the frame
	// according to its contents
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer *sizer_window2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizer_window2_1 = new wxBoxSizer(wxVERTICAL);
	m_panel2->SetSizer(sizer_window2);
	sizer_window2->Add(sizer_window2_1, 0, wxEXPAND, wxBORDER_NONE);

	wxBitmap
		bitmap(wxT("C:/Users/Challenger/Documents/Visual Studio 2015/Projects/Win32Project2/x64/Release/buttons/foldbuttonright.png"), wxBITMAP_TYPE_PNG);
	//Size of window2 
	wxSize sizew2 = m_panel2->GetSize();
	//size of bitmap to preserve resolution
	wxSize sizeimg = bitmap.GetSize();
	// we have to set width of the image so height should be based on aspect ratio
	float aspect_ratio = bitmap.GetSize().GetWidth() / bitmap.GetSize().GetHeight();
	// and we want our button contribute 1 of 50 of windows size
	int width_btn = 10;
	int height_btn = width_btn / aspect_ratio;
	//wxLogMessage((std::to_string(width_btn) +" " +std::to_string(height_btn)).c_str());

	wxButton* drawer_btn = new wxButton(m_panel2, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxSize(width_btn, 10), wxTRANSPARENT_WINDOW|wxNO_BORDER);
	bitmap = wxBitmap(bitmap.ConvertToImage().Scale(width_btn, height_btn, wxIMAGE_QUALITY_HIGH));
	
	drawer_btn->SetBitmap(bitmap);
	//drawer_btn->SetBitmapHover(bmpSelected);
	//drawer_btn->SetBitmapPressed(bmpSelected);
	drawer_btn->SetBackgroundColour(m_panel2->GetBackgroundColour());
	sizer_window2->Add(drawer_btn, 1, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT, wxBORDER_NONE);

	wxPanel* window3 = new wxPanel(m_panel2, wxID_ANY, wxDefaultPosition);
	sizer_window2->Add(window3, 50, wxEXPAND, wxBORDER_NONE);




	topSizer->Add(m_splitterWindow, 1, wxEXPAND, wxNO_BORDER);
	SetSizerAndFit(topSizer);
}


void WxSplitterWindow2Frame::m_splitterOnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxBufferedPaintDC myDC(m_splitterWindow);
	// Shifts the device origin so we don’t have to worry
	// about the current scroll position ourselves
	PrepareDC(myDC);


	myDC.SetBrush(wxColour(0, 0, 0, 255));
	myDC.SetPen(*wxTRANSPARENT_PEN);

	render(myDC);
}

void WxSplitterWindow2Frame::render(wxDC& myDC) {

	
	wxRect rectToDraw;// (x, y, w, h);
	if (m_splitterWindow->GetSplitMode() == wxSPLIT_VERTICAL)
	{
		rectToDraw = wxRect
		(
			m_splitterWindow->GetSashPosition(),
			0,
			m_splitterWindow->GetSashSize(),
			m_splitterWindow->GetSize().GetHeight()
		);
	}
	else
	{
		rectToDraw = wxRect
		(
			0,
			m_splitterWindow->GetSashPosition(),
			m_splitterWindow->GetSize().GetWidth(),
			m_splitterWindow->GetSashSize()
		);
	}
	myDC.DrawRectangle(rectToDraw);
}

void WxSplitterWindow2Frame::m_splitterOnSplitterSashPosChanged(wxSplitterEvent& event)
{
	
	m_splitterWindow->Refresh();
	//add anything else you want to do when the sash is moved here:
}

void WxSplitterWindow2Frame::onResize(wxSizeEvent& event)
{
}
void WxSplitterWindow2Frame::m_splitterOnErase(wxEraseEvent& event) {
}

