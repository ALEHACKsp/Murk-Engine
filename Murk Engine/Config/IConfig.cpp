#include "IConfig.h"
#include "../Engine/IEngine.h"

#include <Windows.h>
#include <shlobj.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

template<typename T = int>
T ReadString(const char* szPath, string str)
{
	ifstream file(szPath);

	string buf;
	while (getline(file, buf))
	{
		if (buf.find(str.c_str()) != string::npos)
		{
			buf.erase(0, str.length());
			file.close();

			stringstream ss;
			ss << buf;
			T ret;
			ss >> ret;
			return ret;
		}
	}

	file.close();
	return {};
}

void IConfig::Initialize()
{
	HWND desktop = GetDesktopWindow();
	RECT rc;
	GetWindowRect(desktop, &rc);

	w = rc.right;
	h = rc.bottom;

	char szDocumentsPath[MAX_PATH];
	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, szDocumentsPath);

	szConfig = szDocumentsPath;
	szConfig += "\\Without Regrets";

	CreateDirectory(szConfig.c_str(), 0);

	szConfig += "\\settings.ini";

	Settings.width = ReadString(szConfig.c_str(), "resolution_w=");
	Settings.height = ReadString(szConfig.c_str(), "resolution_h=");
	Settings.windowed = ReadString<bool>(szConfig.c_str(), "resolution_windowed=");

	if (!Settings.width || !Settings.height)
	{
		ofstream file(szConfig);
		file << "resolution_w=" << 1280 << endl;
		file << "resolution_h=" << 720 << endl;
		file << "resolution_windowed=" << false << endl;
		file.close();
	}
}

void IConfig::ApplySettings()
{
	/*DEVMODE dm;
	dm.dmSize = sizeof(dm);

	if (!Settings.windowed)
	{
		dm.dmPelsWidth = Settings.width;
		dm.dmPelsHeight = Settings.height;
	}
	else
	{
		dm.dmPelsWidth = w;
		dm.dmPelsHeight = h;
	}

	dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);

	SetWindowPos(g_window.hWindow, 0, 0, 0, dm.dmPelsWidth, dm.dmPelsHeight, 0);*/

	ofstream file(szConfig);

	file << "resolution_w=" << Settings.width << endl;
	file << "resolution_h=" << Settings.height << endl;
	file << "resolution_windowed=" << Settings.windowed << endl;

	file.close();
}

void IConfig::ResetResolution()
{
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmPelsWidth = w;
	dm.dmPelsHeight = h;
	dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);
}