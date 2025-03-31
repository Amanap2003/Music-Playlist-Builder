#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>


wxIMPLEMENT_APP(App);


bool App::OnInit()
{   
    MainFrame* mainframe = new MainFrame("Playlist Maker");
    mainframe->SetClientSize(830, 550);
    mainframe->Center();
    mainframe->Show();

         

    return true;
}
