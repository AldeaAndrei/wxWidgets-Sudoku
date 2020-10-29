#include "cApp.h"
#include <wx\wx.h>

wxIMPLEMENT_APP(cApp);

wxBEGIN_EVENT_TABLE(cApp, wxApp)
EVT_KEY_DOWN(OnKeyPressed)
wxEND_EVENT_TABLE()


cApp::cApp()
{
	
}

cApp::~cApp()
{

}

void cApp::OnButtonClicked(wxCommandEvent& event)
{
	if (event.GetId() >= 90 && event.GetId() <= 93)
	{
		if (event.GetId() == 90)
		{
			frame->SetLabels();
		}
		else if (event.GetId() == 91)
		{
			frame->game->SetGame();
			frame->SetLabels();
		}
		else if (event.GetId() == 92)
		{
			if (cApp::check())
			{
				wxLogMessage("The solution is correct !");
			}
			else
			{
				wxLogMessage("The solution is incorrect !");
			}
		}
		else if (event.GetId() == 93)
		{
			frame->SetLabelsSol();
		}
		
	}
	event.Skip();
}

void cApp::OnKeyPressed(wxKeyEvent& event)
{
	wxChar uc = event.GetUnicodeKey();
	if (uc >= '1' && uc <= '9')
	{
		frame->bt[frame->sel - 100]->SetLabel(wxString(uc));
	}

	event.Skip();
}

bool cApp::check()
{
	return cApp::checkCol() && cApp::checkLine() && cApp::checkSquare();
}

bool cApp::checkCol()
{
	
	for (int i = 0; i < 9; i++)
	{
		int nr[10];
		nr[0] = 1;
		for (int j = 0; j < 9; j++)
		{
			nr[j+1] = 0;
		}
		for (int j = 0; j < 9; j++)
		{
			nr[wxAtoi(frame->bt[j * 9 + i]->GetLabel())]++;
		}
		for (int j = 1; j <= 9; j++)
		{
			if (nr[j] != 1)
			{
				return false;
			}
		}
	}
	return true;
}

bool cApp::checkLine()
{

	for (int j = 0; j < 9; j++)
	{
		int nr[10];
		nr[0] = 1;
		for (int i = 0; i < 9; i++)
		{
			nr[i+1] = 0;
		}
		for (int i = 0; i < 9; i++)
		{
			nr[wxAtoi(frame->bt[j * 9 + i]->GetLabel())]++;
		}
		for (int i = 0; i < 9; i++)
		{
			if (nr[i+1] != 1)
			{
				return false;
			}
		}
	}
	return true;
}

bool cApp::checkSquare()
{
	
	int nr[10];
	
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int i = 1; i <= 9; i++)
			{
				nr[i] = 0;
			}

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					nr[wxAtoi(frame->bt[((y * 3) + j) * 9 + (x * 3) + i]->GetLabel())]++;
				}
			}

			for (int i = 1; i <= 9; i++)
			{
				if (nr[i] != 1)
				{
					return false;
				}
			}
		}
	}
	
	
	return true;
}

bool cApp :: OnInit()
{
	int sz = 50;
	frame = new cMain();
	frame->Show();

	btResest = new wxButton(frame, 90, "Reset", wxPoint(frame->game->n * sz + 15, 15),  wxSize(100, 50));
	btNew = new wxButton(frame,    91, "New",   wxPoint(frame->game->n * sz + 15, 65),  wxSize(100, 50));
	btCheck = new wxButton(frame,  92, "Check", wxPoint(frame->game->n * sz + 15, 115), wxSize(100, 50));
	btSol = new wxButton(frame, 93, "Show Solution", wxPoint(frame->game->n * sz + 15, 165), wxSize(100, 50));

	btResest->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cApp::OnButtonClicked, this);
	btNew->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cApp::OnButtonClicked, this);
	btCheck->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cApp::OnButtonClicked, this);
	btSol->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cApp::OnButtonClicked, this);

	frame->game->SetGame();
	frame->SetLabels();

	return true;
}
