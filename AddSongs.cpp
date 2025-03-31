#include "AddSongs.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>


AddSongs::AddSongs(wxWindow* parent) : wxDialog(parent, wxID_ANY, "Add Song", wxDefaultPosition, wxSize(400, 340))
{	
	wxStaticText* name = new wxStaticText(this, wxID_ANY, "Song Name", wxPoint(20, 40));
	wxStaticText* duration = new wxStaticText(this, wxID_ANY, "Duration (sec)", wxPoint(20, 80));
	wxStaticText* r = new wxStaticText(this, wxID_ANY, "Rating", wxPoint(20, 120));

	
	n = new wxTextCtrl(this, wxID_ANY,"", wxPoint(180, 40), wxSize(160, 30));
	dur = new wxTextCtrl(this, wxID_ANY, "", wxPoint(180, 80), wxSize(160, 30));
	rat = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(180, 120), wxSize(100, 30), wxSP_WRAP, 0, 10, 1);



	wxButton* okbtn = new wxButton(this, wxID_OK, "Add", wxPoint(50, 200), wxSize(100, 38));
	wxButton* C_Btn = new wxButton(this, wxID_CANCEL , "Cancel", wxPoint(220, 200), wxSize(100, 38));



		
		


	Centre();

}

wxString AddSongs::getname()
{
	return wxString(n->GetValue());
}

int AddSongs::getdur()
{
	long duration;
	dur->GetValue().ToLong(&duration);
	return static_cast<int>(duration);
}

int AddSongs::getrat()
{
	return (rat->GetValue() ) ;
}
