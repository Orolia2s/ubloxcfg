/* ************************************************************************************************/ // clang-format off
// flipflip's cfggui
//
// Copyright (c) 2021 Philippe Kehl (flipflip at oinkzwurgl dot org),
// https://oinkzwurgl.org/hacking/ubloxcfg
//
// This program is free software: you can redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
// even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see <https://www.gnu.org/licenses/>.

#include "gui_win_data_inf.hpp"

#include "gui_win_data_inc.hpp"

/* ****************************************************************************************************************** */

GuiWinDataInf::GuiWinDataInf(const std::string &name,
            std::shared_ptr<Receiver> receiver, std::shared_ptr<Logfile> logfile, std::shared_ptr<Database> database)
{
    _winSize  = { 80, 25 };
    _receiver = receiver;
    _logfile  = logfile;
    _database = database;
    _winTitle = name;
    _winName  = name;
    ClearData();
}

// ---------------------------------------------------------------------------------------------------------------------

//void GuiWinDataInf::Loop(const std::unique_ptr<Receiver> &receiver)
//{
//}

// ---------------------------------------------------------------------------------------------------------------------

void GuiWinDataInf::ProcessData(const Data &data)
{
    switch (data.type)
    {
        case Data::Type::DATA_MSG:
        {
            if ( (data.msg->type == Ff::ParserMsg::UBX) && (UBX_CLSID(data.msg->data) == UBX_INF_CLSID) )
            {
                ImU32 colour = GUI_COLOUR(INF_OTHER);
                std::string prefix;
                switch (UBX_MSGID(data.msg->data))
                {
                    case UBX_INF_DEBUG_MSGID:    colour = GUI_COLOUR(INF_DEBUG);   prefix = "Debug:   "; _nDebug++;   break;
                    case UBX_INF_NOTICE_MSGID:   colour = GUI_COLOUR(INF_NOTICE);  prefix = "Notice:  "; _nNotice++;  break;
                    case UBX_INF_WARNING_MSGID:  colour = GUI_COLOUR(INF_WARNING); prefix = "Warning: "; _nWarning++; break;
                    case UBX_INF_ERROR_MSGID:    colour = GUI_COLOUR(INF_ERROR);   prefix = "Error:   "; _nError++;   break;
                    case UBX_INF_TEST_MSGID:     colour = GUI_COLOUR(INF_TEST);    prefix = "Test:    "; _nTest++;    break;
                    default:                                               prefix = "Other:   "; _nOther++;   break;
                }
                _log.AddLine(prefix + data.msg->info, colour);
                _nInf++;
            }
            else if ( (data.msg->type == Ff::ParserMsg::NMEA) && (data.msg->name == "NMEA-GN-TXT") )
            {
                if (data.msg->info.substr(6, 2) == "04")
                {
                    _log.AddLine(std::string("Debug:   ") + data.msg->info.substr(9), GUI_COLOUR(INF_DEBUG));
                    _nDebug++;
                    _nInf++;
                }
                else if (data.msg->info.substr(6, 2) == "02")
                {
                    _log.AddLine(std::string("Notice:  ") + data.msg->info.substr(9), GUI_COLOUR(INF_NOTICE));
                    _nNotice++;
                    _nInf++;
                }
                else if (data.msg->info.substr(6, 2) == "01")
                {
                    _log.AddLine(std::string("Warning: ") + data.msg->info.substr(9), GUI_COLOUR(INF_WARNING));
                    _nWarning++;
                    _nInf++;
                }
                else if (data.msg->info.substr(6, 2) == "00")
                {
                    _log.AddLine(std::string("Error:   ") + data.msg->info.substr(9), GUI_COLOUR(INF_ERROR));
                    _nError++;
                    _nInf++;
                }
                else if (data.msg->info.substr(6, 2) == "03")
                {
                    _log.AddLine(std::string("Test:    ") + data.msg->info.substr(9), GUI_COLOUR(INF_TEST));
                    _nTest++;
                    _nInf++;
                }
                else
                {
                    _log.AddLine(std::string("Other:   ") + data.msg->info, GUI_COLOUR(INF_OTHER));
                    _nOther++;
                    _nInf++;
                }
            }
            break;
        }
        default:
            break;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void GuiWinDataInf::ClearData()
{
    _log.Clear();
    _sizeRx   = 0;
    _nInf     = 0;
    _nDebug   = 0;
    _nNotice  = 0;
    _nWarning = 0;
    _nError   = 0;
    _nTest    = 0;
    _nOther   = 0;
}

// ---------------------------------------------------------------------------------------------------------------------

void GuiWinDataInf::DrawWindow()
{
    if (!_DrawWindowBegin())
    {
        return;
    }

    {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 4));

        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(C_WHITE));
        ImGui::TextUnformatted("Msg: ");
        ImGui::PopStyleColor();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(C_BRIGHTBLUE));
        ImGui::Text("%u", _nInf);
        ImGui::PopStyleColor();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(C_WHITE));
        ImGui::TextUnformatted(", Debug: ");
        ImGui::PopStyleColor();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(INF_DEBUG));
        ImGui::Text("%u", _nDebug);
        ImGui::PopStyleColor();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(C_WHITE));
        ImGui::TextUnformatted(", Notice: ");
        ImGui::PopStyleColor();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(INF_NOTICE));
        ImGui::Text("%u", _nNotice);
        ImGui::PopStyleColor();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(C_WHITE));
        ImGui::TextUnformatted(", Warning: ");
        ImGui::PopStyleColor();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(INF_WARNING));
        ImGui::Text("%u", _nWarning);
        ImGui::PopStyleColor();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(C_WHITE));
        ImGui::TextUnformatted(", Error: ");
        ImGui::PopStyleColor();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(INF_ERROR));
        ImGui::Text("%u", _nError);
        ImGui::PopStyleColor();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(C_WHITE));
        ImGui::TextUnformatted(", Test: ");
        ImGui::PopStyleColor();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(INF_TEST));
        ImGui::Text("%u", _nTest);
        ImGui::PopStyleColor();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(C_WHITE));
        ImGui::TextUnformatted(", Other: ");
        ImGui::PopStyleColor();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, GUI_COLOUR(INF_OTHER));
        ImGui::Text("%u", _nOther);
        ImGui::PopStyleColor();
        //ImGui::SameLine();

        ImGui::PopStyleVar(); // ImGuiStyleVar_ItemSpacing
    }
    ImGui::Separator();

    _log.DrawWidget();

    _DrawWindowEnd();
}

/* ****************************************************************************************************************** */
