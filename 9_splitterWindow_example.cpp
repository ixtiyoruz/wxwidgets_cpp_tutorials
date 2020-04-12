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

class WxSplitterWindow2Frame : public wxFrame
{
public:
	WxSplitterWindow2Frame(const wxString& title);

private:
	void OnMenuSplit(wxCommandEvent& evt);
	void OnUnsplit(wxSplitterEvent& evt);

private:
	wxMenu* m_viewMenu;
	wxSplitterWindow* m_splitterWindow;
	wxPanel* m_panel1;
	wxPanel* m_panel2;

	wxDECLARE_EVENT_TABLE();
};


class WxSplitterWindow2App : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(WxSplitterWindow2App);


#include "Source.h"
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/defs.h>

const wxWindowID SplitterWindowID = wxID_HIGHEST + 1;

const int SplitMenuID = wxID_HIGHEST + 2;




bool WxSplitterWindow2App::OnInit()
{
	WxSplitterWindow2Frame* frame = new WxSplitterWindow2Frame("WxSplitterWindow2");
	frame->Show(true);
	return true;
}

WxSplitterWindow2Frame::WxSplitterWindow2Frame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title), m_viewMenu(0), m_splitterWindow(0),
	m_panel1(0), m_panel2(0)
{
	// Create a menu with a checkable item to
	// toggle between the split and unsplit states
	wxMenuBar* menuBar = new wxMenuBar;
	m_viewMenu = new wxMenu;
	m_viewMenu->AppendCheckItem(SplitMenuID, "Split");
	m_viewMenu->Check(SplitMenuID, true);
	menuBar->Append(m_viewMenu, "&View");
	SetMenuBar(menuBar);

	// Create the wxSplitterWindow window
	m_splitterWindow = new wxSplitterWindow(this, SplitterWindowID);

	// Create the left panel
	m_panel1 = new wxPanel(m_splitterWindow, wxID_ANY);
	wxTextCtrl* textCtrl1 = new wxTextCtrl(m_panel1, wxID_ANY, L"Panel 1 Text",
		wxDefaultPosition, wxSize(150, 150));
	wxBoxSizer* panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	panel1Sizer->Add(textCtrl1, 1, wxEXPAND);
	m_panel1->SetSizer(panel1Sizer);

	// Create the right panel
	m_panel2 = new wxPanel(m_splitterWindow, wxID_ANY);
	wxTextCtrl* textCtrl2 = new wxTextCtrl(m_panel2, wxID_ANY, L"Panel 2 Text",
		wxDefaultPosition, wxSize(150, 150));
	wxBoxSizer* panel2Sizer = new wxBoxSizer(wxHORIZONTAL);
	panel2Sizer->Add(textCtrl2, 1, wxEXPAND);
	m_panel2->SetSizer(panel2Sizer);

	// Split the window vertically and set the left and right panes
	m_splitterWindow->SplitVertically(m_panel1, m_panel2, 150);

	// Set up the sizer for the frame and resize the frame
	// according to its contents
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(m_splitterWindow, 1, wxEXPAND);
	SetSizerAndFit(topSizer);
}

// Split or unsplit the window when the "Split" menu item
// is activated
void WxSplitterWindow2Frame::OnMenuSplit(wxCommandEvent& evt)
{
	if (!m_splitterWindow || !m_panel1 || !m_panel2)
	{
		return;
	}

	if (evt.IsChecked())
	{
		m_splitterWindow->SplitVertically(m_panel1, m_panel2, 150);
	}
	else
	{
		m_splitterWindow->Unsplit();
	}
}

// When the window becomes unsplit this event handler
// ensures the checkable menu item gets unchecked
void WxSplitterWindow2Frame::OnUnsplit(wxSplitterEvent& evt)
{
	if (m_viewMenu)
	{
		m_viewMenu->Check(SplitMenuID, false);
	}

	evt.Skip();
}

// Add the event handler to the event table. As you can see we use
// the window ID to link the event handler to the wxSplitterWindow we created.
wxBEGIN_EVENT_TABLE(WxSplitterWindow2Frame, wxFrame)
EVT_MENU(SplitMenuID, WxSplitterWindow2Frame::OnMenuSplit)
EVT_SPLITTER_UNSPLIT(SplitterWindowID, WxSplitterWindow2Frame::OnUnsplit)
wxEND_EVENT_TABLE()



