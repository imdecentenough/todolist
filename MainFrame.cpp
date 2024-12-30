#include "MainFrame.h"
#include <wx/wx.h>
#include <iostream>
#include <fstream>
#include "Task.h"

enum {
	ID_newList = 1, ID_loadList = 2, ID_saveList = 3, ID_clear = 4,
	ID_newTask = 5, ID_deleTask = 6, ID_editTask = 7, ID_collectionInfo = 8,
	ID_customise = 9
};

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	listbox->SetBackgroundColour(wxColour(120, 120, 120));
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_newList, "&New List\tCtrl+E", "Create a new list");
	menuFile->AppendSeparator(); // separates buttons
	menuFile->Append(ID_loadList, "&Load List", "Open a pre-existing list."); 
	menuFile->Append(ID_saveList, "&Save List\tCtrl+S", "Save the current list."); 
	menuFile->AppendSeparator(); 
	menuFile->Append(ID_clear, "&Clear", "Clears the list of its tasks.");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT, "&Exit", "Exits the application. ");

	wxMenu* menuTask = new wxMenu;
	menuTask->Append(ID_newTask, "&New Task\tCtrl+T", "Create a new Task");
	menuTask->Append(ID_deleTask, "&Delete Task\tCtrl+Q", "Delete the selected task(s).");
	menuTask->Append(ID_editTask, "&Edit Task\tCtrl+F", "Edit the selected task.");
	menuTask->AppendSeparator();
	menuTask->Append(ID_collectionInfo, "&List Info", "Display data about the task list.");

	wxMenu* menuSettings = new wxMenu;
	menuSettings->Append(ID_customise, "&Change Colour", "");

	wxMenuBar* bar = new wxMenuBar;
	bar->Append(menuFile, "&File");
	bar->Append(menuTask, "&Task");
	bar->Append(menuSettings, "&Settings");
	SetMenuBar(bar);

	Bind(wxEVT_MENU, &MainFrame::onNewList, this, ID_newList);
	Bind(wxEVT_MENU, &MainFrame::onLoad, this, ID_loadList);
	Bind(wxEVT_MENU, &MainFrame::onSave, this, ID_saveList);
	Bind(wxEVT_MENU, &MainFrame::onClear, this, ID_clear);
	Bind(wxEVT_MENU, &MainFrame::onExit, this, wxID_EXIT);

	Bind(wxEVT_MENU, &MainFrame::onNewTask, this, ID_newTask);
	Bind(wxEVT_MENU, &MainFrame::onDeleTask, this, ID_deleTask);
	Bind(wxEVT_MENU, &MainFrame::onEditTask, this, ID_editTask);
	Bind(wxEVT_MENU, &MainFrame::onListInfo, this, ID_collectionInfo);

	Bind(wxEVT_MENU, &MainFrame::onCustomise, this, ID_customise);
}


void MainFrame::onNewList(wxCommandEvent& event) { // when the hello button is uhhh
	int ans = wxMessageBox("Would you like to create a new list? \nAll tasks will be cleared.", "New List", wxYES_NO | wxICON_INFORMATION);
	if (ans == wxYES) {
		if (collection.clear()) {
			listbox->Clear();
			wxString location = wxSaveFileSelector("Save", "bin", "tasklist.bin", this);
			if (!location.empty()) {
				lastKnownSave = location;
				listbox->SetBackgroundColour(wxColour(120, 120, 120));
				colorChoice = 0;
			}
		}
		else {
			wxMessageBox("Error", "List could not be cleared.", wxOK | wxICON_INFORMATION);
		}
	}
}
void MainFrame::onLoad(wxCommandEvent& event) {
	wxString filename = wxFileSelector("Open a Task List file.", "C:/Users", "tasklist.bin", "bin", "");
	if (!filename.empty()) {
		//success
		std::ifstream taskfile;
		std::string uhhh = std::string(filename.mb_str());
		taskfile.open(uhhh);
		if (taskfile.is_open()) {
			
		}
		wxMessageBox("Successful Loading.", "", wxOK | wxICON_INFORMATION);
		lastKnownSave = filename;
	}
}
void MainFrame::onSave(wxCommandEvent& event) {
	if (lastKnownSave != "") {
		if (encrypt) {
			// encrypt the file
		}
		else if (collection.printAll(lastKnownSave, colorChoice)) {
			// save was a success.
		}
		else {
			wxMessageBox("There was an error saving.", "Error", wxOK | wxICON_INFORMATION);
		}
	}
}
void MainFrame::onClear(wxCommandEvent& event) {
	if (collection.clear()) {
		listbox->Clear();
		wxMessageBox("List Cleared", "List is emptied.", wxOK | wxICON_INFORMATION);
	}
	else {
		wxMessageBox("Error", "List could not be cleared.", wxOK | wxICON_INFORMATION);
	}
}
void MainFrame::onExit(wxCommandEvent& event) {
	int ans = wxMessageBox("Are you sure you want to exit?\nAny unsaved tasks will be lost.", "Exit", wxYES_NO | wxICON_INFORMATION);
	if (ans == wxYES) {
		Close(true);
	}
}

void MainFrame::onNewTask(wxCommandEvent& event) {
	wxString taskTitle = wxGetTextFromUser("Enter a title.", "Creating a new task", "");
	if (!taskTitle.empty()) {
		if (!taskTitle.Contains("|")) {
			if (!taskTitle.Contains("_")) {
				//user has entered a title, proceed. 
					if (collection.newTask(taskTitle)) {
						wxArrayString fuckyou;
						fuckyou.Add(taskTitle);
						listbox->InsertItems(fuckyou, 0);
						fuckyou.clear();
						wxMessageBox("Task Creation", "Task successfully added to list.", wxOK | wxICON_INFORMATION);
					}
			}
			else{ wxMessageBox("Cannot contain | or _ ", "Invalid Character", wxOK | wxICON_INFORMATION); }
		}
		else{ wxMessageBox("Cannot contain | or _ ", "Invalid Character", wxOK | wxICON_INFORMATION); }
	}
}
void MainFrame::onDeleTask(wxCommandEvent& event) {
	if (listbox->IsEmpty()) {
		wxMessageBox("The list is empty.", "Error", wxOK | wxICON_INFORMATION);
	}
	else {
		for (int i = 0; i < listbox->GetCount(); i++) {
			if (listbox->IsSelected(i)) {
				wxString title = listbox->GetString(i);
				if (collection.deleteTask(title)) {
					listbox->Delete(i);
				}
			}
	}
	}
	// check
}

void MainFrame::onEditTask(wxCommandEvent& event) {
	//wxMessageBox("Edit a task", "EVENT7 - Edit the selected task.", wxOK | wxICON_INFORMATION);
	if (listbox->IsEmpty()) {
		wxMessageBox("The list is empty.", "Error", wxOK | wxICON_INFORMATION);
	}
	else {
		int SelectedCount = 0;
		int listTaskToCheck = 0;
		for (int i = 0; i < listbox->GetCount(); i++) {
			if (listbox->IsSelected(i)){
				SelectedCount++;
				listTaskToCheck = i;
			}
		}
		if (SelectedCount != 1) {
			wxMessageBox("Please select a task to edit.", "Error", wxOK | wxICON_INFORMATION);
		}
		else {
			wxString titleOfTask = listbox->GetString(listTaskToCheck);
			int base = collection.find(titleOfTask);
			if (base != -1) {
				wxString sampleTitle = collection.titleOfTask(base);

				wxString newTitle = wxGetTextFromUser("Enter a new title:", "Edit Task", sampleTitle);
				if (!newTitle.empty()) {
					if (newTitle.Contains("_") || newTitle.Contains("|")) {
						wxMessageBox("Cannot contain | or _ ", "Invalid Character", wxOK | wxICON_INFORMATION);
					}
					else {
						if (collection.editTask(base, newTitle)) {
							listbox->SetString(listTaskToCheck, newTitle);
							wxMessageBox("Successfully edited task.", "Edit Task", wxOK | wxICON_INFORMATION);
						}
						else {
							wxMessageBox("Error: Failed to edit task.", "Error", wxOK | wxICON_INFORMATION);
							}
						}
				}
			}
		}
	}
}

void MainFrame::onListInfo(wxCommandEvent& event) {
	int a = collection.returnSize();
	wxString collectionSize;
	collectionSize << a;
	wxString lastTaskName = collection.latestTaskInfo();
	wxString lastUpdated = collection.returnUpdated();
	wxMessageBox("List Size: " + collectionSize+"\nLatest Task: " + lastTaskName + "\nLast Updated: " + lastUpdated, "List Information", wxOK | wxICON_INFORMATION);
}

void MainFrame::onCustomise(wxCommandEvent& event) {
	wxArrayString colorChoices;
	colorChoices.Add("Red");	// 1
	colorChoices.Add("Orange"); // 2
	colorChoices.Add("Yellow");	// 3
	colorChoices.Add("Green");	// 4
	colorChoices.Add("Blue");	// 5
	colorChoices.Add("Purple"); // 6
	colorChoices.Add("Grey");	// 0
	wxString choice = wxGetSingleChoice("Choose a colour pallete:", "Customise", colorChoices, 0);
	if (choice == "Red") {listbox->SetBackgroundColour(wxColour(255, 138, 130)); colorChoice = 1;}
	else if (choice == "Orange") { listbox->SetBackgroundColour(wxColour(255, 192, 125)); colorChoice = 2; }
	else if (choice == "Yellow") {listbox->SetBackgroundColour(wxColour(255, 253, 135)); colorChoice = 3;}
	else if (choice == "Green") {listbox->SetBackgroundColour(wxColour(119, 247, 45)); colorChoice = 4;}
	else if (choice == "Blue") {listbox->SetBackgroundColour(wxColour(199, 252, 255)); colorChoice = 5;}
	else if (choice == "Purple") {listbox->SetBackgroundColour(wxColour(232, 186, 255)); colorChoice = 6;}
	else if (choice == "Grey") {listbox->SetBackgroundColour(wxColour(120, 120, 120)); colorChoice = 0;}

}
