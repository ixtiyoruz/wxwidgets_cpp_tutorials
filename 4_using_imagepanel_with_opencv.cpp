#include <wx/wx.h>
#include <wx/sizer.h>
#include <opencv2/calib3d.hpp>
#include <opencv2/opencv.hpp>

class wxImagePanel : public wxPanel
{
	wxImage image;
	wxBitmap resized;
	int w, h;

public:
	wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format);

	void paintEvent(wxPaintEvent & evt);
	void paintNow();
	void OnSize(wxSizeEvent& event);
	void render(wxDC& dc);

	DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)

// catch paint events
EVT_PAINT(wxImagePanel::paintEvent)
//Size event
EVT_SIZE(wxImagePanel::OnSize)
END_EVENT_TABLE()
wxImage wx_from_mat(cv::Mat &img)
{
	cv::Mat im2;

	if (img.channels() == 1)
		cvtColor(img, im2, cv::COLOR_GRAY2RGB);
	else if (img.channels() == 4) 
		cvtColor(img, im2, cv::COLOR_BGRA2RGB);
	else 
		cvtColor(img, im2, cv::COLOR_BGR2RGB);

	long imsize = im2.rows*im2.cols*im2.channels();
	
	wxImage wx(im2.cols, im2.rows, (unsigned char*)malloc(imsize), false);
	memcpy(wx.GetData(), im2.data, imsize);
	//unsigned char* s = im2.data;
	//unsigned char* d = wx.GetData();
	//for (long i = 0; i < imsize; i++)
	//	d[i] = s[i];
	/*img.convertTo(img, CV_8UC3);
	wxImage wx(img.cols, img.rows, (unsigned char*)img.data, true);*/
	return wx;
}


wxImagePanel::wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format) :
	wxPanel(parent)
{
	std::string filech = std::string(file.mb_str());
	
	cv::Mat asCvMat = cv::imread(filech, cv::IMREAD_UNCHANGED);
	
	
	/*if (asCvMat.channels() == 3)
		cv::cvtColor(asCvMat, asCvMat, CV_BGR2RGB);*/

	// load the file... ideally add a check to see if loading was successful
	//image.LoadFile(file, format);
	image = wx_from_mat(asCvMat);
	w = -1;
	h = -1;
	
}

/*
* Called by the system of by wxWidgets when the panel needs
* to be redrawn. You can also trigger this call by
* calling Refresh()/Update().
*/

void wxImagePanel::paintEvent(wxPaintEvent & evt)
{
	// depending on your system you may need to look at double-buffered dcs
	wxPaintDC dc(this);
	render(dc);
}

/*
* Alternatively, you can use a clientDC to paint on the panel
* at any time. Using this generally does not free you from
* catching paint events, since it is possible that e.g. the window
* manager throws away your drawing when the window comes to the
* background, and expects you will redraw it when the window comes
* back (by sending a paint event).
*/
void wxImagePanel::paintNow()
{
	// depending on your system you may need to look at double-buffered dcs
	wxClientDC dc(this);
	render(dc);
}

/*
* Here we do the actual rendering. I put it in a separate
* method so that it can work no matter what type of DC
* (e.g. wxPaintDC or wxClientDC) is used.
*/
void wxImagePanel::render(wxDC&  dc)
{
	int neww, newh;
	dc.GetSize(&neww, &newh);

	if (neww != w || newh != h)
	{
		resized = wxBitmap(image.Scale(neww, newh /*, wxIMAGE_QUALITY_HIGH*/));
		w = neww;
		h = newh;
		dc.DrawBitmap(resized, 0, 0, false);
	}
	else {
		dc.DrawBitmap(resized, 0, 0, false);
	}
}

/*
* Here we call refresh to tell the panel to draw itself again.
* So when the user resizes the image panel the image should be resized too.
*/
void wxImagePanel::OnSize(wxSizeEvent& event) {
	Refresh();
	//skip the event.
	//event.Skip();
}

// ----------------------------------------
// how-to-use example

class MyApp : public wxApp
{

	wxFrame *frame;
	wxImagePanel * drawPane;
public:
	bool OnInit()
	{
		// make sure to call this first
		wxInitAllImageHandlers();

		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		frame = new wxFrame(NULL, wxID_ANY, wxT("Hello wxDC"), wxPoint(50, 50), wxSize(800, 600));

		// then simply create like this
		drawPane = new wxImagePanel(frame, wxT("C:/Users/Challenger/Documents/Visual Studio 2015/Projects/Win32Project2/x64/Release/img.png"), wxBITMAP_TYPE_PNG);
		sizer->Add(drawPane, 1, wxEXPAND);

		frame->SetSizer(sizer);

		frame->Show();
		return true;
	}
};

IMPLEMENT_APP(MyApp)
