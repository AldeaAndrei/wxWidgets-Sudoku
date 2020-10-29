#pragma once
#include <wx/wx.h>
#include "Game.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	int sel = 0;
	wxButton** bt;
	Game* game;


	
	void SetLabels();
	void SetLabelsSol();

	void OnButtonClicked(wxCommandEvent &event);
	

	wxDECLARE_EVENT_TABLE();

};

