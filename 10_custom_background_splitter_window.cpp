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


//-------------------------------------------------------------------------------------------
#include "CustomSplitterWindow.h"
#include <wx/dcbuffer.h>
#include "wx/renderer.h"
void  MySplitterWindow::OnPaint(wxPaintEvent& event) {

	wxBufferedPaintDC dc(this);
	DrawSash(dc);
	event.Skip();
};

void   MySplitterWindow::DrawSash(wxDC& dc) {

}
