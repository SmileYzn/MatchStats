#pragma once

class CMatchEvent
{
public:
	void AlertMessage(const std::string Message);
	void PlayerConnected(std::string Name, std::string UserId, std::string AuthId, std::string Team, std::string Address);
	void PlayerSteamValidated(std::string Name, std::string UserId, std::string AuthId, std::string Team);
	void PlayerJoinedTeam(std::string Name, std::string UserId, std::string AuthId, std::string Team, std::string NewTeam);
	void PlayerEnteredTheGame(std::string Name, std::string UserId, std::string AuthId, std::string Team);
	void PlayerDisconnected(std::string Name, std::string UserId, std::string AuthId, std::string Team);
	void GameCommencing(std::string CT, std::string T);
	void RoundEnd();
};

extern CMatchEvent gMatchEvent;