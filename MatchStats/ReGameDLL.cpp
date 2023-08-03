#include "precompiled.h"

IReGameApi			*g_ReGameApi;
const ReGameFuncs_t	*g_ReGameFuncs;
IReGameHookchains	*g_ReGameHookchains;
CGameRules			*g_pGameRules;

bool ReGameDLL_Init()
{
	const char *szGameDLLModule = GET_GAME_INFO(PLID, GINFO_DLL_FULLPATH);

	if (!szGameDLLModule)
	{
		LOG_CONSOLE(PLID, "[%s] Failed to get GameDLL module", Plugin_info.logtag);
		return false;
	}

	CSysModule *gameModule = Sys_LoadModule(szGameDLLModule);

	if (!gameModule)
	{
		LOG_CONSOLE(PLID, "[%s] Failed to locate GameDLL module", Plugin_info.logtag);
		return false;
	}

	CreateInterfaceFn ifaceFactory = Sys_GetFactory(gameModule);

	if (!ifaceFactory)
	{
		LOG_CONSOLE(PLID, "[%s] Failed to locate interface factory in GameDLL module", Plugin_info.logtag);
		return false;
	}

	int retCode = 0;

	g_ReGameApi = (IReGameApi *)ifaceFactory(VRE_GAMEDLL_API_VERSION, &retCode);

	if (!g_ReGameApi)
	{
		LOG_CONSOLE(PLID, "[%s] Failed to locate retrieve rehlds api interface from GameDLL module, return code is %d", Plugin_info.logtag, retCode);
		return false;
	}

	int majorVersion = g_ReGameApi->GetMajorVersion();
	int minorVersion = g_ReGameApi->GetMinorVersion();

	if (majorVersion != REGAMEDLL_API_VERSION_MAJOR)
	{
		LOG_CONSOLE(PLID, "[%s] ReGameDLL API major version mismatch; expected %d, real %d", Plugin_info.logtag, REGAMEDLL_API_VERSION_MAJOR, majorVersion);

		if (majorVersion < REGAMEDLL_API_VERSION_MAJOR)
		{
			LOG_CONSOLE(PLID, "[%s] Please update the ReGameDLL up to a major version API >= %d", Plugin_info.logtag, REGAMEDLL_API_VERSION_MAJOR);
		}
		else if (majorVersion > REGAMEDLL_API_VERSION_MAJOR)
		{
			LOG_CONSOLE(PLID, "[%s] Please update the %s up to a major version API >= %d", Plugin_info.logtag, Plugin_info.logtag, majorVersion);
		}

		return false;
	}

	if (minorVersion < REGAMEDLL_API_VERSION_MINOR)
	{
		LOG_CONSOLE(PLID, "[%s] ReGameDLL API minor version mismatch; expected at least %d, real %d", Plugin_info.logtag, REGAMEDLL_API_VERSION_MINOR, minorVersion);
		LOG_CONSOLE(PLID, "[%s] Please update the ReGameDLL up to a minor version API >= %d", Plugin_info.logtag, REGAMEDLL_API_VERSION_MINOR);
		return false;
	}

	g_ReGameFuncs = g_ReGameApi->GetFuncs();

	g_ReGameHookchains = g_ReGameApi->GetHookchains();

	if (!g_ReGameApi->BGetICSEntity(CSENTITY_API_INTERFACE_VERSION))
	{
		LOG_CONSOLE(PLID, "[%s] Interface CCSEntity API version '%s' not found", Plugin_info.logtag, CSENTITY_API_INTERFACE_VERSION);
		return false;
	}

	g_ReGameHookchains->InstallGameRules()->registerHook(ReGameDLL_InstallGameRules);

	g_ReGameHookchains->CBasePlayer_GetIntoGame()->registerHook(ReGameDLL_CBasePlayer_GetIntoGame);

	g_ReGameHookchains->CBasePlayer_SwitchTeam()->registerHook(ReGameDLL_CBasePlayer_SwitchTeam);

	g_ReGameHookchains->HandleMenu_ChooseTeam()->registerHook(ReGameDLL_HandleMenu_ChooseTeam);

	g_ReGameHookchains->CBasePlayer_SetAnimation()->registerHook(ReGameDLL_CBasePlayer_SetAnimation);

	g_ReGameHookchains->CBasePlayer_TakeDamage()->registerHook(ReGameDLL_CBasePlayer_TakeDamage);

	g_ReGameHookchains->CSGameRules_PlayerKilled()->registerHook(ReGameDLL_CSGameRules_PlayerKilled);

	g_ReGameHookchains->CBasePlayer_AddAccount()->registerHook(ReGameDLL_CBasePlayer_AddAccount);

	g_ReGameHookchains->CSGameRules_RestartRound()->registerHook(ReGameDLL_CSGameRules_RestartRound);

	g_ReGameHookchains->CSGameRules_OnRoundFreezeEnd()->registerHook(ReGameDLL_CSGameRules_OnRoundFreezeEnd);

	g_ReGameHookchains->RoundEnd()->registerHook(ReGameDLL_RoundEnd);

	g_ReGameHookchains->CBasePlayer_MakeBomber()->registerHook(ReGameDLL_CBasePlayer_MakeBomber);

	g_ReGameHookchains->CBasePlayer_DropPlayerItem()->registerHook(ReGameDLL_CBasePlayer_DropPlayerItem);

	g_ReGameHookchains->PlantBomb()->registerHook(ReGameDLL_PlantBomb);

	g_ReGameHookchains->CGrenade_DefuseBombStart()->registerHook(ReGameDLL_CGrenade_DefuseBombStart);

	g_ReGameHookchains->CGrenade_DefuseBombEnd()->registerHook(ReGameDLL_CGrenade_DefuseBombEnd);

	g_ReGameHookchains->CGrenade_ExplodeBomb()->registerHook(ReGameDLL_CGrenade_ExplodeBomb);

	return true;
}

bool ReGameDLL_Stop()
{
	g_ReGameHookchains->InstallGameRules()->unregisterHook(ReGameDLL_InstallGameRules);

	g_ReGameHookchains->CBasePlayer_GetIntoGame()->unregisterHook(ReGameDLL_CBasePlayer_GetIntoGame);

	g_ReGameHookchains->CBasePlayer_SwitchTeam()->unregisterHook(ReGameDLL_CBasePlayer_SwitchTeam);

	g_ReGameHookchains->HandleMenu_ChooseTeam()->unregisterHook(ReGameDLL_HandleMenu_ChooseTeam);

	g_ReGameHookchains->CBasePlayer_SetAnimation()->unregisterHook(ReGameDLL_CBasePlayer_SetAnimation);

	g_ReGameHookchains->CBasePlayer_TakeDamage()->unregisterHook(ReGameDLL_CBasePlayer_TakeDamage);

	g_ReGameHookchains->CSGameRules_PlayerKilled()->unregisterHook(ReGameDLL_CSGameRules_PlayerKilled);

	g_ReGameHookchains->CBasePlayer_AddAccount()->unregisterHook(ReGameDLL_CBasePlayer_AddAccount);

	g_ReGameHookchains->CSGameRules_RestartRound()->unregisterHook(ReGameDLL_CSGameRules_RestartRound);

	g_ReGameHookchains->CSGameRules_OnRoundFreezeEnd()->unregisterHook(ReGameDLL_CSGameRules_OnRoundFreezeEnd);

	g_ReGameHookchains->RoundEnd()->unregisterHook(ReGameDLL_RoundEnd);

	g_ReGameHookchains->CBasePlayer_MakeBomber()->unregisterHook(ReGameDLL_CBasePlayer_MakeBomber);

	g_ReGameHookchains->CBasePlayer_DropPlayerItem()->unregisterHook(ReGameDLL_CBasePlayer_DropPlayerItem);

	g_ReGameHookchains->PlantBomb()->unregisterHook(ReGameDLL_PlantBomb);

	g_ReGameHookchains->CGrenade_DefuseBombStart()->unregisterHook(ReGameDLL_CGrenade_DefuseBombStart);

	g_ReGameHookchains->CGrenade_DefuseBombEnd()->unregisterHook(ReGameDLL_CGrenade_DefuseBombEnd);

	g_ReGameHookchains->CGrenade_ExplodeBomb()->unregisterHook(ReGameDLL_CGrenade_ExplodeBomb);

	return true;
}

CGameRules *ReGameDLL_InstallGameRules(IReGameHook_InstallGameRules *chain)
{
	auto gamerules = chain->callNext();

	if (!g_ReGameApi->BGetIGameRules(GAMERULES_API_INTERFACE_VERSION))
	{
		LOG_CONSOLE(PLID, "[%s] Interface GameRules API version '%s' not found", Plugin_info.logtag, GAMERULES_API_INTERFACE_VERSION);
	}
	else
	{
		g_pGameRules = gamerules;
	}
	
	return gamerules;
}

BOOL ReGameDLL_HandleMenu_ChooseTeam(IReGameHook_HandleMenu_ChooseTeam* chain, CBasePlayer* Player, int Slot)
{
	auto ret = chain->callNext(Player, Slot);

	gMatchStats.PlayerSwitchTeam(Player);

	return ret;
}

bool ReGameDLL_CBasePlayer_GetIntoGame(IReGameHook_CBasePlayer_GetIntoGame* chain, CBasePlayer* Player)
{
	bool ret = chain->callNext(Player);

	gMatchStats.PlayerGetIntoGame(Player);

	return ret;
}

void ReGameDLL_CBasePlayer_SwitchTeam(IReGameHook_CBasePlayer_SwitchTeam* chain, CBasePlayer* Player)
{
	chain->callNext(Player);

	gMatchStats.PlayerSwitchTeam(Player);
}

void ReGameDLL_CBasePlayer_SetAnimation(IReGameHook_CBasePlayer_SetAnimation* chain, CBasePlayer* pthis, PLAYER_ANIM playerAnim)
{
	chain->callNext(pthis, playerAnim);

	gMatchStats.PlayerSetAnimation(pthis, playerAnim);
}

int ReGameDLL_CBasePlayer_TakeDamage(IReGameHook_CBasePlayer_TakeDamage* chain, CBasePlayer* pThis, entvars_t* pevInflictor, entvars_t* pevAttacker, float& flDamage, int bitsDamageType)
{
	int ret = chain->callNext(pThis, pevInflictor, pevAttacker, flDamage, bitsDamageType);

	gMatchStats.PlayerDamage(pThis, pevInflictor, pevAttacker, flDamage, bitsDamageType);

	return ret;
}

void ReGameDLL_CSGameRules_PlayerKilled(IReGameHook_CSGameRules_PlayerKilled* chain, CBasePlayer* pVictim, entvars_t* pevKiller, entvars_t* pevInflictor)
{
	chain->callNext(pVictim, pevKiller, pevInflictor);

	gMatchStats.PlayerKilled(pVictim, pevKiller, pevInflictor);
}

void ReGameDLL_CBasePlayer_AddAccount(IReGameHook_CBasePlayer_AddAccount* chain, CBasePlayer* pthis, int amount, RewardType type, bool bTrackChange)
{
	chain->callNext(pthis, amount, type, bTrackChange);

	gMatchStats.PlayerAddAccount(pthis, amount, type, bTrackChange);
}

void ReGameDLL_CSGameRules_RestartRound(IReGameHook_CSGameRules_RestartRound* chain)
{
	chain->callNext();

	gMatchStats.RoundRestart();
}

void ReGameDLL_CSGameRules_OnRoundFreezeEnd(IReGameHook_CSGameRules_OnRoundFreezeEnd* chain)
{
	chain->callNext();

	gMatchStats.RoundFreezeEnd();
}

bool ReGameDLL_RoundEnd(IReGameHook_RoundEnd* chain, int winStatus, ScenarioEventEndRound event, float tmDelay)
{
	gMatchStats.RoundEnd(winStatus, event, tmDelay);

	return chain->callNext(winStatus, event, tmDelay);
}

bool ReGameDLL_CBasePlayer_MakeBomber(IReGameHook_CBasePlayer_MakeBomber* chain, CBasePlayer* pthis)
{
	auto ret = chain->callNext(pthis);

	gMatchStats.PlayerMakeBomber(pthis);

	return ret;
}

CBaseEntity* ReGameDLL_CBasePlayer_DropPlayerItem(IReGameHook_CBasePlayer_DropPlayerItem* chain, CBasePlayer* pthis, const char* pszItemName)
{
	auto ret = chain->callNext(pthis, pszItemName);

	gMatchStats.PlayerDropItem(pthis, pszItemName);

	return ret;
}

CGrenade* ReGameDLL_PlantBomb(IReGameHook_PlantBomb* chain, entvars_t* pevOwner, Vector& vecStart, Vector& vecVelocity)
{
	gMatchStats.PlantBomb(pevOwner, false);

	auto ret = chain->callNext(pevOwner, vecStart, vecVelocity);

	gMatchStats.PlantBomb(pevOwner, true);

	return ret;
}

void ReGameDLL_CGrenade_DefuseBombStart(IReGameHook_CGrenade_DefuseBombStart* chain, CGrenade* pthis, CBasePlayer* pPlayer)
{
	chain->callNext(pthis, pPlayer);

	gMatchStats.DefuseBombStart(pPlayer);
}

void ReGameDLL_CGrenade_DefuseBombEnd(IReGameHook_CGrenade_DefuseBombEnd* chain, CGrenade* pthis, CBasePlayer* pPlayer, bool bDefused)
{
	gMatchStats.DefuseBombEnd(pPlayer, bDefused);

	chain->callNext(pthis, pPlayer, bDefused);
}

void ReGameDLL_CGrenade_ExplodeBomb(IReGameHook_CGrenade_ExplodeBomb* chain, CGrenade* pthis, TraceResult* ptr, int bitsDamageType)
{
	gMatchStats.ExplodeBomb(pthis, ptr, bitsDamageType);

	chain->callNext(pthis, ptr, bitsDamageType);
}