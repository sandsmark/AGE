/* AGEFrame_cpp/TerrainRestrictions.cpp */

#include "../AGE_Frame.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <cctype>
using std::tolower;

string AGE_Frame::GetTerrainRestrictionName(int Index)
{
	string Name = "";
	Name = "Restriction " + lexical_cast<string>(Index);
	if(Index == 1)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 2)
	{
		Name = "Shoreline " + lexical_cast<string>(Index);
	}
	else if(Index == 3)
	{
		Name = "Waterborne " + lexical_cast<string>(Index);
	}
	else if(Index == 4)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 5)
	{
		Name = "All Restriction " + lexical_cast<string>(Index);
	}
	else if(Index == 6)
	{
		Name = "Waterborne " + lexical_cast<string>(Index);
	}
	else if(Index == 7)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 8)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 9)
	{
		Name = "All Restriction " + lexical_cast<string>(Index);
	}
	else if(Index == 10)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 11)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 12)
	{
		Name = "No Restriction " + lexical_cast<string>(Index);
	}
	else if(Index == 13)
	{
		Name = "Waterborne " + lexical_cast<string>(Index);
	}
	else if(Index == 14)
	{
		Name = "No Restriction " + lexical_cast<string>(Index);
	}
	else if(Index == 15)
	{
		Name = "Waterborne " + lexical_cast<string>(Index);
	}
	else if(Index == 16)
	{
		Name = "Grass 1 & Shoreline " + lexical_cast<string>(Index);
	}
	else if(Index == 17)
	{
		Name = "No Moving Restriction " + lexical_cast<string>(Index);
	}
	else if(Index == 18)
	{
		Name = "No Restriction " + lexical_cast<string>(Index);
	}
	else if(Index == 19)
	{
		Name = "Waterborne " + lexical_cast<string>(Index);
	}
	else if(Index == 20)
	{
		Name = "Overland " + lexical_cast<string>(Index);
	}
	else if(Index == 21)
	{
		Name = "Waterborne " + lexical_cast<string>(Index);
	}
	return Name;
}

void AGE_Frame::ListTerrainRestrictions()
{
	string Name;
	wxString SearchText = wxString(TerRestrict_TerRestrict_Search->GetValue()).Lower();
	string CompareText;
	
	short Selection = TerRestrict_TerRestrict_List->GetSelection();
	short RestrictionID1 = Units_ComboBox_TerrainRestriction->GetSelection();

	if(!TerRestrict_TerRestrict_List->IsEmpty())
	{
		TerRestrict_TerRestrict_List->Clear();
	}
	if(!Units_ComboBox_TerrainRestriction->IsEmpty())
	{
		Units_ComboBox_TerrainRestriction->Clear();
	}
	
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	if(RestrictionID1 == wxNOT_FOUND)
	{
		RestrictionID1 = 0;
	}

	Units_ComboBox_TerrainRestriction->Append("-1 - None");
	
	for(short loop = 0;loop < GenieFile->TerrainRestrictions.size();loop++)
	{
		Name = lexical_cast<string>(loop);
		Name += " - ";
		Name += GetTerrainRestrictionName(loop);
		CompareText = wxString(lexical_cast<string>(loop)+ " - "+GetTerrainRestrictionName(loop)).Lower();
		if(SearchText.IsEmpty() || CompareText.find(SearchText) != string::npos)
		{
			TerRestrict_TerRestrict_List->Append(Name, (void*)&GenieFile->TerrainRestrictions[loop]);
		}
		Units_ComboBox_TerrainRestriction->Append(Name);
	}
	
	TerRestrict_TerRestrict_List->SetFirstItem(Selection - 3);
	TerRestrict_TerRestrict_List->SetSelection(0);
	TerRestrict_TerRestrict_List->SetSelection(Selection);
	Units_ComboBox_TerrainRestriction->SetSelection(RestrictionID1);
	
	wxCommandEvent E;
	OnTerrainRestrictionsTerrainSelect(E);
}

void AGE_Frame::OnTerrainRestrictionsSearch(wxCommandEvent& Event)
{
	short Selection = TerRestrict_TerRestrict_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		ListTerrainRestrictions();
	}
}

void AGE_Frame::OnTerrainRestrictionsTerrainSelect(wxCommandEvent& Event)
{
	short Selection = TerRestrict_TerRestrict_List->GetSelection();
	short Selection2 = TerRestrict_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND && Selection2 != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = TerRestrict_TerRestrict_List->GetCount() - 1;
			TerRestrict_TerRestrict_List->SetSelection(Selection);
		}
		gdat::TerrainRestriction * TerrainRestrictionPointer = (gdat::TerrainRestriction*)TerRestrict_TerRestrict_List->GetClientData(Selection);
		gdat::Terrain * TerrainPointer = (gdat::Terrain*)TerRestrict_Terrains_List->GetClientData(Selection2);
		TerRestrictID = TerrainRestrictionPointer - (&GenieFile->TerrainRestrictions[0]);
		TerRestrictTerID = TerrainPointer - (&GenieFile->Terrains[0]);
		
		TerRestrict_Accessible->ChangeValue(lexical_cast<string>(TerrainRestrictionPointer->TerrainAccessible[TerRestrictTerID]));
		TerRestrict_Accessible->Container = &TerrainRestrictionPointer->TerrainAccessible[TerRestrictTerID];
		TerRestrict_CheckBox_Accessible->SetValue((bool)TerrainRestrictionPointer->TerrainAccessible[TerRestrictTerID]);
		if(GameVersion >= 2)	//	Above AoE and RoR
		{
			TerRestrict_Holder_Unknown1->Show(true);
			TerRestrict_Holder_Graphics->Show(true);
			TerRestrict_Holder_Amount->Show(true);
		
			TerRestrict_Unknown1->ChangeValue(lexical_cast<string>(TerrainRestrictionPointer->TerrainPassGraphics[TerRestrictTerID].Buildable));
			TerRestrict_Unknown1->Container = &TerrainRestrictionPointer->TerrainPassGraphics[TerRestrictTerID].Buildable;
			switch(TerrainRestrictionPointer->TerrainPassGraphics[TerRestrictTerID].Buildable)
			{
				case -1:
				{
					TerRestrict_CheckBox_Unknown1->SetValue(false);
				}
				break;
				case 0:
				{
					TerRestrict_CheckBox_Unknown1->SetValue(true);
				}
				break;
				default:
				{
					TerRestrict_CheckBox_Unknown1->SetValue(false);
				}
				break;
			}
			TerRestrict_Graphics[0]->ChangeValue(lexical_cast<string>(TerrainRestrictionPointer->TerrainPassGraphics[TerRestrictTerID].GraphicIDs.first));
			TerRestrict_Graphics[0]->Container = &TerrainRestrictionPointer->TerrainPassGraphics[TerRestrictTerID].GraphicIDs.first;
			TerRestrict_Graphics[1]->ChangeValue(lexical_cast<string>(TerrainRestrictionPointer->TerrainPassGraphics[TerRestrictTerID].GraphicIDs.second));
			TerRestrict_Graphics[1]->Container = &TerrainRestrictionPointer->TerrainPassGraphics[TerRestrictTerID].GraphicIDs.second;
			TerRestrict_ComboBox_Graphics[0]->SetSelection(TerrainRestrictionPointer->TerrainPassGraphics[TerRestrictTerID].GraphicIDs.first + 1);
			TerRestrict_ComboBox_Graphics[1]->SetSelection(TerrainRestrictionPointer->TerrainPassGraphics[TerRestrictTerID].GraphicIDs.second + 1);
			TerRestrict_Amount->ChangeValue(lexical_cast<string>(TerrainRestrictionPointer->TerrainPassGraphics[TerRestrictTerID].ReplicationAmount));
			TerRestrict_Amount->Container = &TerrainRestrictionPointer->TerrainPassGraphics[TerRestrictTerID].ReplicationAmount;
		}
		else
		{
			TerRestrict_Holder_Unknown1->Show(false);
			TerRestrict_Holder_Graphics->Show(false);
			TerRestrict_Holder_Amount->Show(false);
		}
		Added = false;
	}
}

void AGE_Frame::OnTerrainRestrictionsAdd(wxCommandEvent& Event)
{
	gdat::TerrainRestriction Temp;
//	Temp.TerrainAccessible.resize(GenieFile->Terrains.size());
//	Temp.TerrainPassGraphics.resize(GenieFile->Terrains.size());
	GenieFile->TerrainRestrictions.push_back(Temp);
	Added = true;
	ListTerrainRestrictions();
}

void AGE_Frame::OnTerrainRestrictionsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TerRestrict_TerRestrict_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		GenieFile->TerrainRestrictions.erase(GenieFile->TerrainRestrictions.begin() + TerRestrictID);
		if(Selection == TerRestrict_TerRestrict_List->GetCount() - 1)
		TerRestrict_TerRestrict_List->SetSelection(Selection - 1);
		ListTerrainRestrictions();
	}
}

void AGE_Frame::OnTerrainRestrictionsCopy(wxCommandEvent& Event)
{
	short Selection = TerRestrict_TerRestrict_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		TerrainRestrictionCopy = *(gdat::TerrainRestriction*)TerRestrict_TerRestrict_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnTerrainRestrictionsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TerRestrict_TerRestrict_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(gdat::TerrainRestriction*)TerRestrict_TerRestrict_List->GetClientData(Selection) = TerrainRestrictionCopy;
		ListTerrainRestrictions();
	}
}

void AGE_Frame::OnTerrainRestrictionsTerrainCopy(wxCommandEvent& Event)
{
	short Selection = TerRestrict_TerRestrict_List->GetSelection();
	short Selection2 = TerRestrict_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND && Selection2 != wxNOT_FOUND)
	{
		TerrainRestrictionSubCopyAccess = GenieFile->TerrainRestrictions[TerRestrictID].TerrainAccessible[TerRestrictTerID];
		if(GameVersion > 1)	// not AoE nor RoR
		{
			TerrainRestrictionSubCopy = GenieFile->TerrainRestrictions[TerRestrictID].TerrainPassGraphics[TerRestrictTerID];
		}
	}
}

void AGE_Frame::OnTerrainRestrictionsTerrainPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = TerRestrict_TerRestrict_List->GetSelection();
	short Selection2 = TerRestrict_Terrains_List->GetSelection();
	if(Selection != wxNOT_FOUND && Selection2 != wxNOT_FOUND)
	{
		GenieFile->TerrainRestrictions[TerRestrictID].TerrainAccessible[TerRestrictTerID] = TerrainRestrictionSubCopyAccess;
		if(GameVersion > 1)	// not AoE nor RoR
		{
			GenieFile->TerrainRestrictions[TerRestrictID].TerrainPassGraphics[TerRestrictTerID] = TerrainRestrictionSubCopy;
		}
		wxCommandEvent E;
		OnTerrainRestrictionsTerrainSelect(E);
	}
}

void AGE_Frame::CreateTerrainRestrictionControls()
{

	Tab_TerrainRestrictions = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(-1, 350));
	TerRestrict_Main = new wxBoxSizer(wxHORIZONTAL);
	TerRestrict_ListArea = new wxBoxSizer(wxVERTICAL);
	TerRestrict_TerRestrict_Buttons = new wxGridSizer(2, 0, 0);
	TerRestrict_TerRestrict = new wxStaticBoxSizer(wxVERTICAL, Tab_TerrainRestrictions, "Terrain Restriction Slot");
	TerRestrict_TerRestrict_Search = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
	TerRestrict_TerRestrict_List = new wxListBox(Tab_TerrainRestrictions, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	TerRestrict_Add = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Add", wxDefaultPosition, wxSize(-1, 20));
	TerRestrict_Delete = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Delete", wxDefaultPosition, wxSize(-1, 20));
	TerRestrict_Copy = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	TerRestrict_Paste = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));

	TerRestrict_Terrains = new wxBoxSizer(wxVERTICAL);
	TerRestrict_DataArea = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Terrains_Search = new wxTextCtrl(Tab_TerrainRestrictions, wxID_ANY);
	TerRestrict_Terrains_List = new wxListBox(Tab_TerrainRestrictions, wxID_ANY, wxDefaultPosition, wxSize(-1, 70));
	TerRestrict_Terrains_Buttons = new wxGridSizer(2, 0, 0);
	TerRestrict_Terrains_Copy = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Copy", wxDefaultPosition, wxSize(-1, 20));
	TerRestrict_Terrains_Paste = new wxButton(Tab_TerrainRestrictions, wxID_ANY, "Paste", wxDefaultPosition, wxSize(-1, 20));
	TerRestrict_Holder_Accessible = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Holder_Accessible2 = new wxBoxSizer(wxHORIZONTAL);
	TerRestrict_Text_Accessible = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Accessible", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerRestrict_Accessible = new TextCtrl_Float(Tab_TerrainRestrictions, "0", NULL);
	TerRestrict_CheckBox_Accessible = new CheckBox_Float(Tab_TerrainRestrictions, "Terrain Is Accessible", TerRestrict_Accessible);
	TerRestrict_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Holder_Unknown1Sub = new wxBoxSizer(wxHORIZONTAL);
	TerRestrict_Text_Unknown1 = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Can Be Built On", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerRestrict_Unknown1 = new TextCtrl_Long(Tab_TerrainRestrictions, "0", NULL);
	TerRestrict_CheckBox_Unknown1 = new CheckBox_Long_ZeroIsYes(Tab_TerrainRestrictions, "No", TerRestrict_Unknown1);
	TerRestrict_Holder_Graphics = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Text_Graphics = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Graphics", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerRestrict_Graphics[0] = new TextCtrl_Long(Tab_TerrainRestrictions, "0", NULL);
	TerRestrict_Graphics[1] = new TextCtrl_Long(Tab_TerrainRestrictions, "0", NULL);
	TerRestrict_ComboBox_Graphics[0] = new ComboBox_Long(Tab_TerrainRestrictions, TerRestrict_Graphics[0]);
	TerRestrict_ComboBox_Graphics[1] = new ComboBox_Long(Tab_TerrainRestrictions, TerRestrict_Graphics[1]);
	TerRestrict_Holder_Amount = new wxBoxSizer(wxVERTICAL);
	TerRestrict_Text_Amount = new wxStaticText(Tab_TerrainRestrictions, wxID_ANY, " Replication Amount", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	TerRestrict_Amount = new TextCtrl_Long(Tab_TerrainRestrictions, "0", NULL);

	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Add, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Delete, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Copy, 1, wxEXPAND);
	TerRestrict_TerRestrict_Buttons->Add(TerRestrict_Paste, 1, wxEXPAND);

	TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_Search, 0, wxEXPAND);
	TerRestrict_TerRestrict->Add(-1, 2);
	TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_List, 1, wxEXPAND);
	TerRestrict_TerRestrict->Add(-1, 2);
	TerRestrict_TerRestrict->Add(TerRestrict_TerRestrict_Buttons, 0, wxEXPAND);

	TerRestrict_ListArea->Add(-1, 10);
	TerRestrict_ListArea->Add(TerRestrict_TerRestrict, 1, wxEXPAND);
	TerRestrict_ListArea->Add(-1, 10);

	TerRestrict_Terrains_Buttons->Add(TerRestrict_Terrains_Copy, 1, wxEXPAND);
	TerRestrict_Terrains_Buttons->Add(TerRestrict_Terrains_Paste, 1, wxEXPAND);
	
	TerRestrict_Terrains->Add(-1, 10);
	TerRestrict_Terrains->Add(TerRestrict_Terrains_Search, 0, wxEXPAND);
	TerRestrict_Terrains->Add(-1, 2);
	TerRestrict_Terrains->Add(TerRestrict_Terrains_List, 1, wxEXPAND);
	TerRestrict_Terrains->Add(-1, 2);
	TerRestrict_Terrains->Add(TerRestrict_Terrains_Buttons, 0, wxEXPAND);
	TerRestrict_Terrains->Add(-1, 10);

	TerRestrict_Holder_Accessible2->Add(TerRestrict_Accessible, 1, wxEXPAND);
	TerRestrict_Holder_Accessible2->Add(2, -1);
	TerRestrict_Holder_Accessible2->Add(TerRestrict_CheckBox_Accessible, 2, wxEXPAND);
	TerRestrict_Holder_Accessible->Add(TerRestrict_Text_Accessible, 0, wxEXPAND);
	TerRestrict_Holder_Accessible->Add(-1, 2);
	TerRestrict_Holder_Accessible->Add(TerRestrict_Holder_Accessible2, 1, wxEXPAND);

	TerRestrict_Holder_Unknown1Sub->Add(TerRestrict_Unknown1, 1, wxEXPAND);
	TerRestrict_Holder_Unknown1Sub->Add(2, -1);
	TerRestrict_Holder_Unknown1Sub->Add(TerRestrict_CheckBox_Unknown1, 1, wxEXPAND);
	TerRestrict_Holder_Unknown1->Add(TerRestrict_Text_Unknown1, 0, wxEXPAND);
	TerRestrict_Holder_Unknown1->Add(-1, 2);
	TerRestrict_Holder_Unknown1->Add(TerRestrict_Holder_Unknown1Sub, 1, wxEXPAND);
	TerRestrict_Holder_Graphics->Add(TerRestrict_Text_Graphics, 0, wxEXPAND);
	TerRestrict_Holder_Graphics->Add(-1, 2);
	TerRestrict_Holder_Graphics->Add(TerRestrict_Graphics[0], 1, wxEXPAND);
	TerRestrict_Holder_Graphics->Add(TerRestrict_ComboBox_Graphics[0], 1, wxEXPAND);
	TerRestrict_Holder_Graphics->Add(TerRestrict_Graphics[1], 1, wxEXPAND);
	TerRestrict_Holder_Graphics->Add(TerRestrict_ComboBox_Graphics[1], 1, wxEXPAND);
	TerRestrict_Holder_Amount->Add(TerRestrict_Text_Amount, 0, wxEXPAND);
	TerRestrict_Holder_Amount->Add(-1, 2);
	TerRestrict_Holder_Amount->Add(TerRestrict_Amount, 1, wxEXPAND);

	TerRestrict_DataArea->Add(-1, 10);
	TerRestrict_DataArea->Add(TerRestrict_Holder_Accessible, 0, wxEXPAND);
	TerRestrict_DataArea->Add(-1, 5);
	TerRestrict_DataArea->Add(TerRestrict_Holder_Unknown1, 0, wxEXPAND);
	TerRestrict_DataArea->Add(-1, 5);
	TerRestrict_DataArea->Add(TerRestrict_Holder_Graphics, 0, wxEXPAND);
	TerRestrict_DataArea->Add(-1, 5);
	TerRestrict_DataArea->Add(TerRestrict_Holder_Amount, 0, wxEXPAND);
	TerRestrict_DataArea->Add(-1, 10);

	TerRestrict_Main->Add(10, -1);
	TerRestrict_Main->Add(TerRestrict_ListArea, 1, wxEXPAND);
	TerRestrict_Main->Add(10, -1);
	TerRestrict_Main->Add(TerRestrict_Terrains, 1, wxEXPAND);
	TerRestrict_Main->Add(10, -1);
	TerRestrict_Main->Add(TerRestrict_DataArea, 1, wxEXPAND);
	TerRestrict_Main->AddStretchSpacer(1);

	Tab_TerrainRestrictions->SetSizer(TerRestrict_Main);
	
	Connect(TerRestrict_TerRestrict_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsSearch));
	Connect(TerRestrict_TerRestrict_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainSelect));
	Connect(TerRestrict_Terrains_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnTerrainsSearch));
	Connect(TerRestrict_Terrains_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainSelect));
	Connect(TerRestrict_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsAdd));
	Connect(TerRestrict_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsDelete));
	Connect(TerRestrict_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsCopy));
	Connect(TerRestrict_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsPaste));
	Connect(TerRestrict_Terrains_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainCopy));
	Connect(TerRestrict_Terrains_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnTerrainRestrictionsTerrainPaste));
}