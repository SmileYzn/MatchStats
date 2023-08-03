#pragma once

// Match Stats Settings Path
constexpr auto MS_SETTINGS_PATH = "cstrike/addons/matchstats/matchstats.cfg";;

// Match Stats Path
constexpr auto MS_SAVE_PATH = "cstrike/addons/matchstats/logs";

// Match States
constexpr auto STATE_DEAD = 0;
constexpr auto STATE_WARMUP = 1;
constexpr auto STATE_START = 2;
constexpr auto STATE_FIRST_HALF = 3;
constexpr auto STATE_HALFTIME = 4;
constexpr auto STATE_SECOND_HALF = 5;
constexpr auto STATE_OVERTIME = 6;
constexpr auto STATE_END = 7;

// Match Stats
typedef struct S_MATCH_STATS
{
	// BETA: Match Start Time
	time_t StartTime;

	// BETA: Match End Time
	time_t EndTime;

	// BETA: Server Name
	std::string HostName;

	// BETA: Map Name
	std::string Map;

	// BETA: Server Address
	std::string Address;

	// BETA: Team Score
	std::array<int, SPECTATOR + 1> Score = { };

	// BETA: Winner of match
	int Winner;

	// BETA: Rounds Played
	int TotalRounds;

	// Reset
	void Reset()
	{
		this->StartTime = 0;
		this->EndTime = 0;
		this->HostName = "";
		this->Map = "";
		this->Address = "";
		this->Score.fill(0);
		this->Winner = 0;
		this->TotalRounds = 0;
	}

	// Swap Scores
	void SwapScores()
	{
		// Store Terrorist Score
		auto ScoreTR = this->Score[TERRORIST];

		// Set Terorrorist Score
		this->Score[TERRORIST] = this->Score[CT];

		// Set CT Score
		this->Score[CT] = ScoreTR;
	}
} P_MATCH_STATS, *LP_MATCH_STATS;

// Weapon Stats
typedef struct S_WEAPON_STATS
{
	int Frags;
	int Deaths;
	int Headshots;
	int Shots;
	int Hits;
	int HitsReceived;
	int Damage;
	int DamageReceived;
} P_WEAPON_STATS, * LP_WEAPON_STATS;

// Round Stats
typedef struct S_ROUND_STATS
{
	int Frags;				// BETA: Player Frags
	int Deaths;				// BETA: Player Deaths
	int Headshots;			// BETA: Headshots
	int Shots;				// BETA: Shots
	int Hits;				// BETA: Hits
	int HitsReceived;		// BETA: Hits Received
	int Damage;				// BETA: Damage Taken
	int DamageReceived;		// BETA: Damage Receeived
	bool BombDefused;		// BETA: Bomb Defused
	bool BombExploded;		// BETA: Bomb Exploded
	int Versus;				// BETA: Player is versus X players

	// Damage dealt to other players
	std::map<std::string, int> PlayerDamage;

	// Reset
	void Reset()
	{
		this->Frags = 0;
		this->Deaths = 0;
		this->Headshots = 0;
		this->Shots = 0;
		this->Hits = 0;
		this->HitsReceived = 0;
		this->Damage = 0;
		this->DamageReceived = 0;
		this->BombDefused = 0;
		this->BombExploded = 0;
		this->Versus = 0;
	}
} P_ROUND_STATS, * LP_ROUND_STATS;

// Player Stats
typedef struct S_PLAYER_STATS
{
	// Stats
	int Frags;					// BETA: Player Frags
	int Deaths;					// BETA: Player Deaths
	int Assists;				// BETA: Player Kill Assists
	int Headshots;				// BETA: Headshots by player
	int Shots;					// BETA: Shots by player
	int Hits;					// BETA: Hits done by player
	int HitsReceived;			// BETA: Hits received by player
	int Damage;					// BETA: Damage taken by player
	int DamageReceived;			// BETA: Damage received by player
	long Money;					// BETA: Money Balance from player
	int Suicides;				// BETA: Suicide Count

	// BETA: Round Win Share stats
	float RoundWinShare;

	// Sick Stats
	int BlindFrags;				// BETA: Player frags when blinded by flashbang
	int BlindDeaths;			// BETA: Player deaths when blinded by flashbang
	int OneShot;				// BETA: One Shot Frags (Except for AWP)
	int NoScope;				// BETA: No Scope Frags
	int FlyFrags;				// BETA: Flying Frags
	int WallFrags;				// BETA: Wallbgang Frags
	int	GodLikes;				// TODO: Count of times when a player killed the other accompanied by the wall

	// TODO: Count of Knife Duels in match (0 Wins, 1 Loses)
	std::array<int, 2> KnifeDuels;

	// Entries
	int EntryFrags;				// BETA: Entry Frag of round
	int EntryDeaths;			// BETA: Entry Death of round

	// Rounds
	int RoundPlay;				// BETA: Rounds Play
	int RoundWin;				// BETA: Rounds Won
	int RoundLose;				// BETA: Rounds Lose

	// Bomb
	int BombSpawn;				// BETA: Bomb Spawns
	int BombDrop;				// BETA: Bomb Drops
	int BombPlanting;			// BETA: Bomb Plant Attempts
	int BombPlanted;			// BETA: Bomb Plants
	int BombExploded;			// BETA: Bomb Explosions
	int BombDefusing;			// BETA: Bomb Defusing Attempts
	int BombDefusingKit;		// BETA: Bomb Defusing with Kit Attempts
	int BombDefused;			// BETA: Bomb Defuses
	int BombDefusedKit;			// BETA: Bomb Defuses with Kit

	// BETA: Kill streak
	std::array<int, (MAX_CLIENTS / 2)> KillStreak;

	// BETA: Versus: 1 vs X win situations
	std::array<int, (MAX_CLIENTS / 2)> Versus;
	
	// BETA: HitBox (0 Hits, 1 Damage, 1 Hits Received, 3 Damage Received)
	std::array<std::array<int, 4>, 9> HitBox;

	// BETA: Weapon Stats
	std::map<int, P_WEAPON_STATS> Weapon;
	
	// Clear stats
	void Reset()
	{
		// Stats
		this->Frags = 0;
		this->Deaths = 0;
		this->Assists = 0;
		this->Headshots = 0;
		this->Shots = 0;
		this->Hits = 0;
		this->HitsReceived = 0;
		this->Damage = 0;
		this->DamageReceived = 0;
		this->Money = 0;
		this->Suicides = 0;

		// Round Win Share stats
		this->RoundWinShare = 0.0f;

		// Sick Frags
		this->BlindFrags = 0;
		this->BlindDeaths = 0;
		this->OneShot = 0;
		this->NoScope = 0;
		this->FlyFrags = 0;
		this->WallFrags = 0;

		// Entries
		this->EntryFrags = 0;
		this->EntryDeaths = 0;

		// Kill streak
		this->KillStreak.fill(0);

		// Versus: 1 vs X win situations
		this->Versus.fill(0);

		// HitBox (0 Hits, 1 Damage, 1 Hits Received, 3 Damage Received)
		this->HitBox.fill({ 0 });

		// Weapon Stats
		this->Weapon.clear();

		// Rounds
		this->RoundPlay = 0;
		this->RoundWin = 0;
		this->RoundLose = 0;

		// Bomb
		this->BombSpawn = 0;
		this->BombDrop = 0;
		this->BombPlanting = 0;
		this->BombPlanted = 0;
		this->BombExploded = 0;
		this->BombDefusing = 0;
		this->BombDefusingKit = 0;
		this->BombDefused = 0;
		this->BombDefusedKit = 0;
	}
} P_PLAYER_STATS, * LP_PLAYER_STATS;

// Player Chat
typedef struct S_PLAYER_CHAT
{
	time_t Time;
	int State;
	int Team;
	int Alive;
	std::string Message;
} P_PLAYER_CHAT, *LPP_PLAYER_CHAT;

// Player Data
typedef struct S_PLAYER_DATA
{
	// Timers
	time_t JoinGameTime;		// BETA: Joined Game Time
	time_t DisconnectTime;		// BETA: Disconnected Time

	// Player Data
	std::string Name;			// BETA: Player Name
	int Team;					// BETA: Plyer Team

	// Player Stats
	std::map<int, P_PLAYER_STATS> Stats;

	// Player chat log
	std::vector<P_PLAYER_CHAT> ChatLog;

	// Round Stats
	P_ROUND_STATS Round;
} P_PLAYER_DATA, *LP_PLAYER_DATA;

// Round Events
typedef struct S_ROUND_EVENT
{
	int			Round;			// Round Count
	float		Time;			// Round Time Seconds;
	int			Type;			// ROUND_NONE for player events, ScenarioEventEndRound for round events
	int			ScenarioEvent;	// Scenario Event End Round
	int			Winner;			// Winner team of event
	int			Loser;			// Loser team of event
	std::string Killer;			// Killer
	std::string Victim;			// Victim
	Vector		KillerOrigin;	// Killer Position
	Vector		VictimOrigin;	// Victim Position
	int			IsHeadShot;		// HeadShot
	int			ItemIndex;		// Item Index of event
} P_ROUND_EVENT, * LP_ROUND_EVENT;

class CMatchStats
{
public:
	void ServerActivate();
	void Cvar_DirectSet(struct cvar_s* var, const char* value);
	void PlayerGetIntoGame(CBasePlayer* Player);
	void PlayerDisconnect(CBasePlayer* Player);
	void PlayerSwitchTeam(CBasePlayer* Player);
	void PlayerSetAnimation(CBasePlayer* Player, PLAYER_ANIM playerAnim);
	void PlayerDamage(CBasePlayer* Victim, entvars_t* pevInflictor, entvars_t* pevAttacker, float& flDamage, int bitsDamageType);
	void PlayerKilled(CBasePlayer* Victim, entvars_t* pevKiller, entvars_t* pevInflictor);
	void PlayerAddAccount(CBasePlayer* Player, int amount, RewardType type, bool bTrackChange);
	void RoundRestart();
	void RoundFreezeEnd();
	void RoundEnd(int winStatus, ScenarioEventEndRound eventScenario, float tmDelay);
	void PlayerMakeBomber(CBasePlayer* Player);
	void PlayerDropItem(CBasePlayer* Player, const char* pszItemName);
	void PlantBomb(entvars_t* pevOwner, bool Planted);
	void DefuseBombStart(CBasePlayer* Player);
	void DefuseBombEnd(CBasePlayer* Player, bool Defused);
	void ExplodeBomb(CGrenade* pThis, TraceResult* ptr, int bitsDamageType);
	static bool SayText(int msg_dest, int msg_type, const float* pOrigin, edict_t* pEntity);
	void PlayerSayText(CBasePlayer* Player, const char* TextMsg);
	void OnEvent(GameEventType event, int ScenarioEvent, CBaseEntity* pEntity, CBaseEntity* pEntityOther);
	void ExportData();
	static void CallbackResult(CURL* ch, size_t Size, const char* Memory, int EventIndex);

private:
	// Stats State
	cvar_t* m_stats_state = nullptr;

	// Kill Assistance mininum damage
	cvar_t* m_assistance_dmg = nullptr;

	// Total of Round Win Share points to be divided by winner team of round
	cvar_t* m_rws_total_points = nullptr;

	// Round Win Share: Extra amount added to player from winner team that planted the bomb and bomb explode
	cvar_t* m_rws_c4_explode = nullptr;

	// Round Win Share: Extra amount added to player from winner team that defused the bomb
	cvar_t* m_rws_c4_defused = nullptr;

	// Enable Stats Remote API (0 Disable, 1 Enable)
	cvar_t* m_api_enable = nullptr;

	// Stats Remote API Address (HTTP protocol API)
	cvar_t* m_api_address = nullptr;

	// Stats Remote API Timeout (Timeout in seconds to wait for response from remote server)
	cvar_t* m_api_timeout = nullptr;

	// Stats Remote API Bearer Token (Authentication Token or leave empty to disable)
	cvar_t* m_api_bearer = nullptr;

	// Match State
	int m_State = STATE_DEAD;

	// Match Data
	P_MATCH_STATS m_Match = { };

	// Player Data
	std::map<std::string, P_PLAYER_DATA> m_Player;

	// Match event data
	std::vector<P_ROUND_EVENT> m_RoundEvent;
};

extern CMatchStats gMatchStats;
