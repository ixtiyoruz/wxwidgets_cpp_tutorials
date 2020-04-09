#include "Source.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

	void OnAbout(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	private:
};	


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
	frame->Connect(frame->GetId(),
		wxEVT_CLOSE_WINDOW,
		wxCommandEventHandler(MyFrame::OnQuit));
	frame->Connect(wxID_ABOUT,
		wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(MyFrame::OnAbout));
	frame->Show(true);
	return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
	wxMessageBox(" OnQuit THis program is about to quit","do you want to quit ?", wxOK | wxICON_INFORMATION);
	
	Destroy();
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets' Hello world sample",
		"About Hello World", wxOK | wxICON_INFORMATION);
}
