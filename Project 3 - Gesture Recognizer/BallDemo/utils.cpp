#include "utils.h"

#include <windows.h>
#include <shlobj.h>
#include "SDL_syswm.h"

#define IDD_PASSWORD 1300

// Open the "Save File" dialog. Return the file path.
std::string SaveFileDialog(SDL_Window* window, const char* filter)
{
	// Get the info of the native window.
	static SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);

	// Open the save file dialog.
	OPENFILENAMEA ofn;
	char szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = wmInfo.info.win.window;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetSaveFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}
	return std::string();
}

// Open the "Open File" dialog. Return the file path.
std::string OpenFileDialog(SDL_Window* window, const char* filter)
{
	// Get the info of the native window.
	static SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);

	// Open the save file dialog.
	OPENFILENAMEA ofn;
	char szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = wmInfo.info.win.window;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}
	return std::string();
}

// Open the "Browse Folder" dialog. Return the folder path.
std::string BrowseFolder(const std::string& saved_path)
{
	TCHAR path[MAX_PATH];

	const char* path_param = saved_path.c_str();

	BROWSEINFO bi = { 0 };
	bi.lpszTitle = ("Browse for folder...");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn = NULL;
	bi.lParam = (LPARAM)path_param;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != 0)
	{
		//get the name of the folder and put it in path
		SHGetPathFromIDList(pidl, path);

		//free memory used
		IMalloc* imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}

		return path;
	}

	return std::string();
}

// Get all the files in a folder.
std::vector<std::string> GetAllFileNames(const std::string& templateFolderPath, const std::string& filter)
{
	std::vector<std::string> names;

	std::string searchPath = templateFolderPath + "/" + filter;

	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(searchPath.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

std::string InputDialog(SDL_Window* window)
{
	// Get the info of the native window.
	static SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);

	HWND hwnd = wmInfo.info.win.window;

	HWND inputDialogBox = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "Line one",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,
		CW_USEDEFAULT, CW_USEDEFAULT, 200, 24,	// x, y, w, h
		hwnd, (HMENU)(101), (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

	// char array to hold the text from the textbox
	char szInput[MAX_PATH];

	// Obtains input from the textbox and puts it into the char array
	GetWindowText(GetDlgItem(hwnd, 101), szInput, MAX_PATH);

	return std::string();
}
