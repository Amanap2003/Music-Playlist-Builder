#include "MainFrame.h"
#include <wx/wx.h> 
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include "AddSongs.h"
//#include "Algorithms.h"
#include <vector>
#include <string>
#include "algos.h"
#include "details.h"



// ============================================================================

void MainFrame::SetFontRecursively(wxWindow* window, const wxFont& font)
{
	window->SetFont(font);

	wxWindowList& children = window->GetChildren();
	for (wxWindowList::iterator it = children.begin(); it != children.end(); ++it)
	{
		SetFontRecursively(*it, font);
	}
}

void MainFrame::filldet()
{
	det.clear();
	long items = listCtrl->GetItemCount();

	for (long i = 0; i < items; i++) {
		wxString n = listCtrl->GetItemText(i, 0);
		long duration, rating;

		listCtrl->GetItemText(i, 1).ToLong(&duration);
		listCtrl->GetItemText(i, 2).ToLong(&rating);

		details detail1 = { n, static_cast<int>(duration), static_cast<int>(rating) };

		det.push_back(detail1);

	}

}



// ============================================================================




MainFrame::MainFrame(const wxString title) : wxFrame(nullptr, wxID_ANY, title)
{


	panel = new wxPanel(this);
	search = new wxStaticText(panel, wxID_ANY, "Search : ", wxPoint(30, 20));

			wxFont font = search->GetFont();
			font.SetPointSize(12); 
			search->SetFont(font);
	
	text = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(120, 20), wxSize(180, 35));
			wxFont font10 = text->GetFont();
			font10.SetPointSize(10); 
			text->SetFont(font10);
			text->SetHint("Enter the keywords") ; 

			

			

	s_btn = new wxButton(panel, wxID_ANY, "Find", wxPoint(315, 20), wxSize(60, 35));

	listCtrl = new wxListCtrl(panel, wxID_ANY, wxPoint(20, 90), wxSize(370, 200), wxLC_REPORT);
	listCtrl->InsertColumn(0, "Name", wxLIST_FORMAT_LEFT, 140);
	listCtrl->InsertColumn(1, "Duration (sec)", wxLIST_FORMAT_LEFT, 130);
	listCtrl->InsertColumn(2, "Rating  (10)", wxLIST_FORMAT_LEFT, 100);
				
				
			

	wxStaticText* lt = new wxStaticText(panel, wxID_ANY, "Listen Time (sec): ", wxPoint(20, 400));
		wxFont font2 = lt->GetFont();
		font2.SetPointSize(12);
		lt->SetFont(font2);

	/*listentime = new wxSpinCtrl(panel, wxID_ANY,"" , wxPoint(180, 400), wxSize(120, 35), wxSP_WRAP, 0, 10, 1 );*/
	listentime = new wxTextCtrl(panel, wxID_ANY,"", wxPoint(180, 400), wxSize(120, 35));
	//time = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(180, 330), wxSize(120, 35));
	create = new wxButton(panel, wxID_ANY, "Create Playlist", wxPoint(180, 470), wxSize(120, 45));
	mashup = new wxCheckBox(panel, wxID_ANY, "Mashup", wxPoint(20, 470), wxSize(120, 45));

	finalplaylist = new wxStaticText(panel, wxID_ANY, "Created Playlist", wxPoint(540, 20));
			wxFont font3 = finalplaylist->GetFont();
			font3.SetPointSize(12);
			finalplaylist->SetFont(font3);
	

	finallist = new wxListCtrl(panel, wxID_ANY, wxPoint(440, 90), wxSize(370, 200), wxLC_REPORT);
	finallist->InsertColumn(0, "Name", wxLIST_FORMAT_LEFT, 140);
	finallist->InsertColumn(1, "Duration (sec)", wxLIST_FORMAT_LEFT, 130);
	finallist->InsertColumn(2, "Rating  (10)", wxLIST_FORMAT_LEFT, 100);
	
	addsongs("Proper Patola", 175, 8, listCtrl);
	addsongs("Despecito", 181, 7, listCtrl);
	addsongs("No Competition", 166, 9, listCtrl);
		
	
	addbtn = new wxButton(panel, wxID_ANY, "Add Songs", wxPoint(115, 330), wxSize(120, 45));
	delbtn = new wxButton(panel, wxID_ANY, "Remove", wxPoint(310, 300), wxSize(80, 30));
		

	CreateStatusBar();

	addbtn->Bind(wxEVT_BUTTON, &MainFrame::addDialog, this);
	delbtn->Bind(wxEVT_BUTTON, &MainFrame::deletesongs, this);
	create->Bind(wxEVT_BUTTON, &MainFrame::createPlaylist, this);
	s_btn->Bind(wxEVT_BUTTON, &MainFrame::find, this); 

	filldet();

	if (finallist->GetItemCount() == 0)
		finallist->InsertItem(0, "(Empty)");
		
}

void MainFrame::createPlaylist(wxCommandEvent& evt) {
	//wxLogStatus("BUTTON CLICKED !");
	finallist->DeleteAllItems();
	
	
	det.clear();
	long items = listCtrl->GetItemCount();

	for (long i = 0; i < items; i++) {
		wxString n = listCtrl->GetItemText(i, 0);
		long duration, rating;

		listCtrl->GetItemText(i, 1).ToLong(&duration);
		listCtrl->GetItemText(i, 2).ToLong(&rating);

		details detail1 = { n, static_cast<int>(duration), static_cast<int>(rating) };

		det.push_back(detail1);		

	}
		
	if (!det.empty()) {
		// here we call the binary or fractional knapsack on pssing det vector , and also the listen time 
		// and return the ans in the form of new struct and then call the addsongs but now this time we are adding our songs to the finallist listCtrl; 
		
		bool mash = mashup->IsChecked();
		if (mash) {
			long time;
			listentime->GetValue().ToLong(&time);
			std::vector<details> ans = algo1->frac_knapsack(det, time);
			AddtoFinal(ans);
			long ratingsum = 0;
			for (int i = 0; i < ans.size(); i++)
				ratingsum += ans[i].rat;
			wxLogStatus("Fractional Knapsack with Total Weight : %d\n and the total value (Rating Sum) is : %d", time, ratingsum);
		}
		else {
			long time;
			listentime->GetValue().ToLong(&time);
			std::vector<details> ans = algo1->binknapsack(det, time) ;
			AddtoFinal(ans);
			long ratingsum = 0;
			for (int i = 0; i < ans.size(); i++)
				ratingsum += ans[i].rat;
			wxLogStatus("Binary Knapsack with Total Weight (time duration)  : %d\n and the total value (Rating Sum) is : %d", time, ratingsum);
		}

		

	}
	else {
		wxString msg = "(Empty)";
		finallist->InsertItem(0, msg);
	}
		

}


void MainFrame::addsongs(wxString name, int dur, int rat, wxListCtrl* list) {
	
	int total = list->GetItemCount();
	
	long row_index = list->InsertItem(total, name);
	wxString duration = wxString::Format("%d", dur);
	wxString rating = wxString::Format("%d", rat);
	list->SetItem(row_index, 1, duration);
	list->SetItem(row_index, 2, rating);	

}

void MainFrame::addDialog(wxCommandEvent& evt)
{
	AddSongs* dialog = new AddSongs(this);
	if (dialog->ShowModal() == wxID_OK) {
		wxString name = dialog->getname();
		int duration = dialog->getdur();
		int rating = dialog->getrat();
		addsongs(name, duration, rating, listCtrl);
	}

	dialog->Destroy();
}

void MainFrame::deletesongs(wxCommandEvent& evt)
{	
	long selectedItem = -1;
	selectedItem = listCtrl->GetNextItem(selectedItem, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

	while (selectedItem != wxNOT_FOUND) {
		listCtrl->DeleteItem(selectedItem);

		if (selectedItem >= 0 && static_cast<size_t>(selectedItem) < det.size()) {
			det.erase(det.begin() + selectedItem);
		}

		selectedItem = listCtrl->GetNextItem(selectedItem, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	}
	if (det.empty()) {
		wxString msg = "(Empty)";
		listCtrl->InsertItem(0, msg);
	}
}

void MainFrame::AddtoFinal(vector<details> ans)
{
	for (int i = 0; i < ans.size(); i++) {
		addsongs(ans[i].name, ans[i].dur, ans[i].rat, finallist);
	}
}

void MainFrame::AddtoOri(vector<details>& ans)
{
	for (int i = 0; i < ans.size(); i++) {
		addsongs(ans[i].name, ans[i].dur, ans[i].rat, listCtrl);
	}

}

void MainFrame::find(wxCommandEvent& evt)
{
	wxString patt = text->GetValue();

	if (patt.size() == 0) {
		wxLogStatus("Empty Search");
		listCtrl->DeleteAllItems();
		AddtoOri(det);
		RemoveColor(listCtrl);
	}
	else {
		std::vector<details>  matched = algo1->kmp(det, patt);
		listCtrl->DeleteAllItems();
		//wxString match = wxString::Format("%d", matched.size());
		wxLogStatus("KMP algorithm running !");
		AddtoOri(matched);
		AddColor(listCtrl);
	}
}

void MainFrame::AddColor(wxListCtrl* list)
{
	long items = list->GetItemCount();

	for (long i = 0; i < items; i++) {
		listCtrl->SetItemTextColour(i, *wxBLUE); 
	}

}

void MainFrame::RemoveColor(wxListCtrl* list)
{
	long items = list->GetItemCount();

	for (long i = 0; i < items; i++) {
		listCtrl->SetItemTextColour(i, *wxBLACK);
	}

}


