#include "Task.h"
#include <wx/wx.h>
#include <string>
#include <ctime>

Task::Task(wxString a) {
	title = a;
	time_t currentTime;
	time(&currentTime);
	std::string dick = ctime(&currentTime);
	date << dick;
}

wxString Task::returnTitle() {
	return title;
}
wxString Task::returnDate() {
	return date;
}
bool Task::edit(wxString b) {
	title = b;
	return true;
}

std::string Task::printToFile() {
	std::string a;
	a = a + title;
	a = a + " | ";
	a = a + date;
	a = a + " _ ";
	return a;
}

