#include "tkCol.h"
#include <wx/wx.h>
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
#include "Task.h"

tkCol::tkCol() { colSize = 0; }
tkCol::~tkCol() { colSize = 0; clear(); }
int tkCol::returnSize() {return colSize;}
bool tkCol::insert(Task* a) {
	collection.push_back(a);
	colSize++;
	time_t currentTime;
	time(&currentTime);
	lastUpdated = ctime(&currentTime);
	return true;
}

bool tkCol::newTask(wxString a) {
	Task* c = new Task(a);
	insert(c);
	return true;
}

bool tkCol::clear() {
	colSize = 0;
	collection.clear();
	if (collection.size() != 0) {
		// fuck it didnt clear what
		return false;
	}
	return true;
}

wxString tkCol::latestTaskInfo() {
	if (collection.empty()) {
		std::string ex = "No Tasks in List.";
		wxString e;
		e << ex;
		return e;
	}
	else {
		int a = collection.size();
		a = a - 1;
		Task* lastTask = collection[a];
		return lastTask->returnTitle();
	}
}

wxString tkCol::returnUpdated() { return lastUpdated; }

int tkCol::find(wxString a) {
	if (colSize == 0) {
		// empty list 
		return -1;
	}
	else {
		for (int i = 0; i < colSize; i++) {
			wxString b = collection.at(i)->returnTitle();
			if (b == a) {
				return i;
			}
		}
	}
}

wxString tkCol::titleOfTask(int a) {return collection.at(a)->returnTitle();}

bool tkCol::editTask(int a, wxString b) {
	if (collection.at(a)->edit(b)) {
		return true;
	}
	else {
		return false;
	}
}

bool tkCol::deleteTask(wxString a) {
	if (colSize == 0) {
		// empty list 
		return false;
	}
	else {
		for (int i = 0; i < colSize; i++) {
			wxString b = collection.at(i)->returnTitle();
			if (b == a) {
				Task* atEnd = collection.back();
				Task* choose = collection[i];
				collection[i] = atEnd;
				collection.back() = choose;
				collection.pop_back();
				colSize = colSize - 1;
				return true;
			}
		}
	}
}

bool tkCol::printAll(wxString file, int a) {
	std::string filename = std::string(file.mb_str());
	std::string data;
	std::ofstream FileToSave(filename);
	int size = colSize;
	size = size - 1;
	FileToSave << "[";
	FileToSave << a;
	FileToSave << "]";
	for (int i = 0; i <= size; i++) {
		std::string a = collection.at(i)->printToFile();
		data.append(a);
	}
	FileToSave << data;
	FileToSave.close();
	return true;
}