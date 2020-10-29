#pragma once
#include <wx/wx.h>
#include "cMain.h"

class cApp : public wxApp
{

public:
	cApp();
	~cApp();

private:
	cMain* frame = nullptr;

public:
	virtual bool OnInit();
	void OnButtonClicked(wxCommandEvent& event);
	void OnKeyPressed(wxKeyEvent& event);

	wxButton* btResest;
	wxButton* btNew;
	wxButton* btCheck;
	wxButton* btSol;

	bool check();
	bool checkLine();
	bool checkCol();
	bool checkSquare();

wxDECLARE_EVENT_TABLE();

};

