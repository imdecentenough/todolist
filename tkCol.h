#pragma once
#include <wx/wx.h>
#include <vector>
#include "Task.h"
class tkCol
{
public:
	tkCol();
	~tkCol();
	int returnSize();
	bool insert(Task* a);
	bool newTask(wxString a);
	bool clear();
	wxString latestTaskInfo();
	wxString returnUpdated();
	int find(wxString a);
	wxString titleOfTask(int a);
	bool editTask(int a, wxString b);
	bool deleteTask(wxString a);
	bool printAll(wxString filename, int a);

private:
	std::vector<Task*> collection;
	int colSize;
	wxString lastUpdated;
};

