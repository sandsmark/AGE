#include "Main.h"
#include "Common.h"
#include "AGE_Copies.hpp"
#include "AGE_Frame.h"

#if __WXGTK3__
#include <glib.h>
#endif

IMPLEMENT_APP(AGE)

AGE_Frame *AGE_Frame::openEditors[4]{0};
Copies AGE_Frame::copies;

bool AGE::OnInit()
{
#if defined(__WXGTK3__) || defined(__WXGTK4__)
    wxMessageBox(wxT(
                "You are using the GTK 3 (or later) version of wxWidgets, which is _very_ slow and has severe issues.\n"
                "\n"
                "Please don't file bugs missing graphics, glitching buttons, laggy or non-responsive UI or other UI issues.\n"
                "\n"
                "For optimal performance use wxqt or wxgtk2.\n"
                "Due to the nature of wxWidgets you will need to re-build AGE after replacing your current wxWidgets installation."
            ),
            wxT("Using GTK 3"),
            wxICON_ERROR
        );

    // shut gtk the fuck up, why the fuck is gtk still used anywhere
    g_log_set_default_handler([](const gchar*, GLogLevelFlags, const gchar*,gpointer){}, nullptr);
    g_log_set_writer_func([](GLogLevelFlags, const GLogField*, gsize, gpointer) {
            return G_LOG_WRITER_HANDLED;
        }, nullptr, nullptr);
#endif


    SetVendorName("Tapsa");
    SetAppName("AdvancedGenieEditor3");
    SetAppDisplayName("Advanced Genie Editor");
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxTGAHandler);

    wxToolTip::SetDelay(200);
    wxToolTip::SetAutoPop(32700);
    wxToolTip::SetReshow(1);

    wxString cmd1 = (wxApp::argc > 1) ? wxApp::argv[1] : "";
    AGE_Frame *window = new AGE_Frame("Advanced Genie Editor " + AGE_AboutDialog::AGE_VER, 0, cmd1);
    SetTopWindow(window);
    wxCommandEvent OpenFiles(wxEVT_COMMAND_MENU_SELECTED, window->eOpen);
    window->OnOpen(OpenFiles);

    return true;
}

// Fancy scaling :)
void AGE_Frame::FixSize(AGE_Frame *window)
{
    int ScrollerWidth = window->Units_ScrollSpace->GetMinSize().GetWidth();
    if(ScrollerWidth > 630)
    {
        int NewWidth = 270.0f * (ScrollerWidth / 630.0f) + ScrollerWidth;
        window->MinWindowWidth = NewWidth;
        window->SetSize(NewWidth, 870);
    }
    else
    {
        window->MinWindowWidth = 900;
        window->SetSize(900, 870);
    }
    window->Show(true);
    window->FixSizes();
}
