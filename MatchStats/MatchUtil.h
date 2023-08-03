#pragma once

// Temporary execute config
constexpr auto MATCH_API_TEMP_FILE = "cstrike/addons/matchstats/temp.cfg";

class CMatchUtil
{
public:
	cvar_t* CvarRegister(const char* Name, const char* Value);
	void ServerCommand(const char* Format, ...);
	const char* GetAuthId(CBasePlayer* Player);
	int MakeDirectory(const char* Path);
	void ServerExecute(std::string Command);
	bool PlayerIsVisible(int PlayerIndex, int TargetIndex);

private:
	std::map<std::string, cvar_t> m_CvarData;
};

extern CMatchUtil gMatchUtil;

