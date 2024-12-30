#include <wx/wx.h>
#include "Task.h"
#include "tkCol.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	int taskCount = 0;
	int colorChoice = 0;
	tkCol collection;
	bool encrypt = false;
	wxPanel* panel = new wxPanel(this);
	wxListBox* listbox = new wxListBox(panel, wxID_ANY, wxPoint(30, 20), wxSize(400, 150));
	wxString lastKnownSave = "";
	void onNewList(wxCommandEvent& event);
	void onLoad(wxCommandEvent& event);
	void onSave(wxCommandEvent& event);
	void onClear(wxCommandEvent& event);
	void onExit(wxCommandEvent& event);

	void onNewTask(wxCommandEvent& event);
	void onDeleTask(wxCommandEvent& event);
	void onEditTask(wxCommandEvent& event);
	void onListInfo(wxCommandEvent& event);

	void onCustomise(wxCommandEvent& event);
};

