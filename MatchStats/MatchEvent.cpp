#include "precompiled.h"

CMatchEvent gMatchEvent;

void CMatchEvent::AlertMessage(const std::string Message)
{
	// Argument List
	std::smatch Match;

	// "SmileY<1><STEAM_0:1:20326844><>" connected, address "127.0.0.1:27005"
	if (std::regex_search(Message.begin(), Message.end(), Match, std::regex("\"(.*)<([0-9])><(.*)><(.*)>\" connected, address \"(.*)\"")))
	{
		if (Match.size() >= 5)
		{
			this->PlayerConnected(Match[1].str(), Match[2].str(), Match[3].str(), Match[4].str(), Match[5].str());
			return;
		}
	}

	// "SmileY<1><STEAM_0:1:20326844><>" STEAM USERID validated
	if (std::regex_search(Message.begin(), Message.end(), Match, std::regex("\"(.*)<([0-9])><(.*)><(.*)>\" STEAM USERID validated")))
	{
		if (Match.size() >= 4)
		{
			this->PlayerSteamValidated(Match[1].str(), Match[2].str(), Match[3].str(), Match[4].str());
			return;
		}
	}

	// "SmileY<1><STEAM_0:1:20326844><>" joined team "TERRORIST"
	if (std::regex_search(Message.begin(), Message.end(), Match, std::regex("\"(.*)<([0-9])><(.*)><(.*)>\" joined team \"(.*)\"")))
	{
		if (Match.size() >= 5)
		{
			this->PlayerJoinedTeam(Match[1].str(), Match[2].str(), Match[3].str(), Match[4].str(), Match[5].str());
			return;
		}
	}

	// "SmileY<1><STEAM_0:1:20326844><>" entered the game
	if (std::regex_search(Message.begin(), Message.end(), Match, std::regex("\"(.*)<([0-9])><(.*)><(.*)>\" entered the game")))
	{
		if (Match.size() >= 4)
		{
			this->PlayerEnteredTheGame(Match[1].str(), Match[2].str(), Match[3].str(), Match[4].str());
			return;
		}
	}

	// "SmileY<1><STEAM_0:1:20326844><>" disconnected
	if (std::regex_search(Message.begin(), Message.end(), Match, std::regex("\"(.*)<([0-9])><(.*)><(.*)>\" disconnected")))
	{
		if (Match.size() >= 4)
		{
			this->PlayerDisconnected(Match[1].str(), Match[2].str(), Match[3].str(), Match[4].str());
			return;
		}
	}

	// World triggered "Game_Commencing" (CT "0") (T "0")
	if (std::regex_search(Message.begin(), Message.end(), Match, std::regex("World triggered \"Game_Commencing\" \\(CT \"([0-9])\"\\) \\(T \"([0-9])\"\\)")))
	{
		if (Match.size() >= 2)
		{
			this->GameCommencing(Match[1].str(), Match[2].str());
			return;
		}
	}

	// World triggered "Round_End"
	if (std::regex_search(Message.begin(), Message.end(), Match, std::regex("World triggered \"Round_End\"")))
	{
		if (Match.size())
		{
			this->RoundEnd();
			return;
		}
	}
}

void CMatchEvent::PlayerConnected(std::string Name, std::string UserId, std::string AuthId, std::string Team, std::string Address)
{
	LOG_CONSOLE(PLID, "[%s] %s %s %s %s %s", __func__, Name.c_str(), UserId.c_str(), AuthId.c_str(), Team.c_str(), Address.c_str());
}

void CMatchEvent::PlayerSteamValidated(std::string Name, std::string UserId, std::string AuthId, std::string Team)
{
	LOG_CONSOLE(PLID, "[%s] %s %s %s %s", __func__, Name.c_str(), UserId.c_str(), AuthId.c_str(), Team.c_str());
}

void CMatchEvent::PlayerJoinedTeam(std::string Name, std::string UserId, std::string AuthId, std::string Team, std::string NewTeam)
{
	LOG_CONSOLE(PLID, "[%s] %s %s %s %s %s", __func__, Name.c_str(), UserId.c_str(), AuthId.c_str(), Team.c_str(), NewTeam.c_str());
}

void CMatchEvent::PlayerEnteredTheGame(std::string Name, std::string UserId, std::string AuthId, std::string Team)
{
	LOG_CONSOLE(PLID, "[%s] %s %s %s %s", __func__, Name.c_str(), UserId.c_str(), AuthId.c_str(), Team.c_str());
}

void CMatchEvent::PlayerDisconnected(std::string Name, std::string UserId, std::string AuthId, std::string Team)
{
	LOG_CONSOLE(PLID, "[%s] %s %s %s %s", __func__, Name.c_str(), UserId.c_str(), AuthId.c_str(), Team.c_str());
}

void CMatchEvent::GameCommencing(std::string CT, std::string T)
{
	LOG_CONSOLE(PLID, "[%s] %s %s", __func__, CT.c_str(), T.c_str());
}

void CMatchEvent::RoundEnd()
{
	LOG_CONSOLE(PLID, "[%s]", __func__);
}