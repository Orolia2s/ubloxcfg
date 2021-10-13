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

#ifndef __GUI_WIN_FILEDIALOG_H__
#define __GUI_WIN_FILEDIALOG_H__

#include <string>
#include <memory>

#include "gui_win.hpp"

/* ***** File dialog ************************************************************************************************ */

class GuiWinFileDialog : public GuiWin
{
    public:
        enum Mode_e { FILE_OPEN, FILE_SAVE };

        GuiWinFileDialog(const std::string &name);

        // Setup dialog
        void InitDialog(const Mode_e mode, std::shared_ptr<std::string> result);

        // Set current directory
        void SetDirectory(const std::string &directory);

        // Set (propose) filename for mode = FILE_SAVE
        void SetFilename(const std::string &fileName);

        // Set confirm dialog, default is true for mode = FILE_SAVE, false for mode = FILE_OPEN
        void ConfirmSelect(const bool confirm);

        // Set confirm dialog, for mode = FILE_SAVE if file exists, default true
        void ConfirmOverwrite(const bool confirm);

        // True if dialog is inited and we should continue calling DrawDialog()
        bool IsInit();

        // Draw dialog, return true when done, in which case result is the path (on success) or empty (on cancel)
        bool DrawDialog();

    protected:

        struct DirEntry
        {
            DirEntry(const std::filesystem::directory_entry &entry);
            std::string           fullPath;   // "/full/path/to/file_or_dir"
            std::string           fileType;   // type icon
            std::string           fileName;   // "file_or_dir"
            std::string           fileDate;   // date string
            std::string           fileSize;   // size string
            std::string           linkTarget; // "/path/to/link/target/file_or_dir", or "" if not a symlink

            bool                  isFile;
            bool                  isDir;

            std::uintmax_t        sortSize;
            int                   sortType;
            std::time_t           sortDate;
        };

        Mode_e                _dialogMode;

        enum State_e { UNINIT, SELECT, CONFIRM, DONE };

        enum State_e          _dialogState;

        std::string           _currentDir;
        std::vector<std::string> _currentDirParts;
        std::vector<DirEntry> _currentDirFiles;
        bool                  _updatePathScroll;

        bool                  _showHidden;
        bool                  _dirsFirst;
        std::string           _currentDirInput;
        bool                  _editCurrentDir;

        bool                  _confirmSelect;
        bool                  _confirmOverwrite;

        std::string           _selectedFileName;
        bool                  _selectedFileValid;
        std::string           _selectedPath;


        std::shared_ptr<std::string> _resultPath;

        enum Order_e { ASC, DESC };
        enum Col_e { TYPE, NAME, SIZE, DATE };
        struct SortInfo
        {
            SortInfo(const Col_e _col, const Order_e _order) : col{_col}, order{_order} {}
            Col_e   col;
            Order_e order;
        };
        std::vector<SortInfo> _sortInfo;

        void _Done();
        bool _DrawWindow();
        void _Check();

        void _ChangeDir(const std::string &path = "");
        void _RefreshDir();

};

/* ****************************************************************************************************************** */
#endif // __GUI_WIN_FILEDIALOG_H__
