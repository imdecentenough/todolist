#include "app.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(app);

bool app::OnInit() {
	MainFrame* mainFrame = new MainFrame("To-Do List");
	mainFrame->SetClientSize(470, 250);
	mainFrame->SetMaxClientSize(wxSize(470, 250));
	mainFrame->SetMinClientSize(wxSize(470, 250));
	mainFrame->SetBackgroundColour(wxColour(160,  160, 160 ));
	mainFrame->Center();
	mainFrame->Show();
	return true;
}
