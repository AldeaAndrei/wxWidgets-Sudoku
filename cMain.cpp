#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
//EVT_BUTTON(100, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain :: cMain() : wxFrame(nullptr, wxID_ANY, "wxWidgets Sudoku", wxPoint(100, 100))
{
	game = new Game();

	int sz = 50;
	wxSize frameSize = wxSize(game->n * (sz + 5) + 100, game->n * (sz + 5) + 15);
	this->SetSize(frameSize);


	bt = new wxButton *[game->n * game->n];

	

	for (int i = 0; i < game->n; i++)
	{
		for (int j = 0; j < game->n; j++)
		{
			wxPoint point;
			

			if ((i + 0) % 3 == 0 && (j + 0) % 3 == 0) {
				point = wxPoint(i * sz + 15, j * sz + 15);
			}
			else if ((i + 0) % 3 == 0) {
				point = wxPoint(i * sz + 15, j * sz + 5);
			}
			else if ((j + 0) % 3 == 0) {
				point = wxPoint(i * sz + 5, j * sz + 15);
			}
			else {
				point = wxPoint(i * sz + 5, j * sz + 5);
			}


			wxSize size =  wxSize(sz, sz);

			if(game->grid[i][j] != 0)
				bt[j * game->n + i] = new wxButton(this, 100 + (j * game->n + i), wxString::Format(wxT("%i"), game->grid[i][j]),point, size);
			else
				bt[j * game->n + i] = new wxButton(this, 100 + (j * game->n + i), " ", point, size);

			bt[j * game->n + i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
		}
	}
}

cMain :: ~cMain()
{
	delete[]bt;
}

void cMain::SetLabels()
{
	for (int i = 0; i < game->n; i++)
	{
		for (int j = 0; j < game->n; j++)
		{
			if (game->grid[i][j] != 0)
			{
				bt[j * game->n + i]->SetLabel(wxString::Format(wxT("%i"), game->grid[i][j]));
				bt[j * game->n + i]->Enable(false);
			}
			else
			{
				bt[j * game->n + i]->SetLabel(" ");
				bt[j * game->n + i]->Enable(true);
			}
		}
	}
}

void cMain::SetLabelsSol()
{
	for (int i = 0; i < game->n; i++)
	{
		for (int j = 0; j < game->n; j++)
		{
			if (game->solvedGrid[i][j] != 0)
			{
				bt[j * game->n + i]->SetLabel(wxString::Format(wxT("%i"), game->solvedGrid[i][j]));
				bt[j * game->n + i]->Enable(false);
			}
		}
	}
}


void cMain::OnButtonClicked(wxCommandEvent& event)
{
	sel = event.GetId();
	event.Skip();
}
