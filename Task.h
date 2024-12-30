#pragma once
#include <wx/wx.h>
#include <string>
struct Task
{
public:
	Task(wxString a);
	wxString returnTitle();
	wxString returnDate();
	std::string printToFile();
	bool edit(wxString b);

private:
	wxString title;
	wxString date;
};

