#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include "AddSongs.h"
#include <vector>
#include <string>
//#include "Algorithms.h"
#include "algos.h"
#include "details.h"
//struct details {
//	wxString name;
//	int dur; 
//	int rat;
//};


class MainFrame : public wxFrame 
{
public: 
	MainFrame(const wxString title);	
private: 
	wxPanel* panel;
	wxTextCtrl* text ;
	wxListCtrl* listCtrl;
	wxStaticText* search;
	wxTextCtrl* time;
	wxButton* create;
	wxCheckBox* mashup;
	bool allowed;
	wxButton* s_btn;
	std :: vector<details> det;
	
	
	//Algorithms* algos = new Algorithms() ;
	//Algorithms algos;
	algos* algo1 = new algos();


	wxButton* addbtn ;
	wxButton* delbtn;
	//wxSpinCtrl* listentime;;
	wxTextCtrl* listentime;
	wxStaticText* finalplaylist;
	wxListCtrl* finallist;
	
	void createPlaylist(wxCommandEvent& evt);
	void addsongs(wxString name, int dur, int rating, wxListCtrl* listCtrl);
	void addDialog(wxCommandEvent& evt);
	void deletesongs(wxCommandEvent& evt);
	void AddtoFinal(vector<details> ans);
	void AddtoOri(vector<details>& ans);
	void SetFontRecursively(wxWindow* window, const wxFont& font);
	void filldet();
	void find(wxCommandEvent& evt);
	void AddColor(wxListCtrl* list);
	void RemoveColor(wxListCtrl* list);





};

