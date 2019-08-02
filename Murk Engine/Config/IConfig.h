#pragma once

#include <string>

class IConfig
{
public:
	struct {
		int width = 1280;
		int height = 720;
		bool windowed = true;
	} Settings;

	int w, h;

	std::string szConfig;

	void Initialize();
	void ApplySettings();
	void ResetResolution();
};

extern IConfig g_config;