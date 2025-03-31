#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>


class AddSongs : public wxDialog
{	
private: 
	wxTextCtrl* n; 
	wxTextCtrl* dur;
	wxSpinCtrl* rat;

public:

	AddSongs(wxWindow* parent);
		
	wxString getname();
	int getdur();
	int getrat();

};

