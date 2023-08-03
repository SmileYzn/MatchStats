#pragma once

extern IReGameApi			*g_ReGameApi;
extern const ReGameFuncs_t	*g_ReGameFuncs;
extern IReGameHookchains	*g_ReGameHookchains;
extern CGameRules			*g_pGameRules;

extern bool ReGameDLL_Init();
extern bool ReGameDLL_Stop();

CGameRules *ReGameDLL_InstallGameRules(IReGameHook_InstallGameRules* chain);
BOOL ReGameDLL_HandleMenu_ChooseTeam(IReGameHook_HandleMenu_ChooseTeam* chain, CBasePlayer* Player, int Slot);
bool ReGameDLL_CBasePlayer_GetIntoGame(IReGameHook_CBasePlayer_GetIntoGame* chain, CBasePlayer* Player);
void ReGameDLL_CBasePlayer_SwitchTeam(IReGameHook_CBasePlayer_SwitchTeam* chain, CBasePlayer* Player);
void ReGameDLL_CBasePlayer_SetAnimation(IReGameHook_CBasePlayer_SetAnimation* chain, CBasePlayer* pthis, PLAYER_ANIM playerAnim);
int ReGameDLL_CBasePlayer_TakeDamage(IReGameHook_CBasePlayer_TakeDamage* chain, CBasePlayer* pThis, entvars_t* pevInflictor, entvars_t* pevAttacker, float& flDamage, int bitsDamageType);
void ReGameDLL_CSGameRules_PlayerKilled(IReGameHook_CSGameRules_PlayerKilled* chain, CBasePlayer* pVictim, entvars_t* pevKiller, entvars_t* pevInflictor);
void ReGameDLL_CBasePlayer_AddAccount(IReGameHook_CBasePlayer_AddAccount* chain, CBasePlayer* pthis, int amount, RewardType type, bool bTrackChange);
void ReGameDLL_CSGameRules_RestartRound(IReGameHook_CSGameRules_RestartRound* chain);
void ReGameDLL_CSGameRules_OnRoundFreezeEnd(IReGameHook_CSGameRules_OnRoundFreezeEnd* chain);
bool ReGameDLL_RoundEnd(IReGameHook_RoundEnd* chain, int winStatus, ScenarioEventEndRound event, float tmDelay);
bool ReGameDLL_CBasePlayer_MakeBomber(IReGameHook_CBasePlayer_MakeBomber* chain, CBasePlayer* pthis);
CBaseEntity* ReGameDLL_CBasePlayer_DropPlayerItem(IReGameHook_CBasePlayer_DropPlayerItem* chain, CBasePlayer* pthis, const char* pszItemName);
CGrenade* ReGameDLL_PlantBomb(IReGameHook_PlantBomb* chain, entvars_t* pevOwner, Vector& vecStart, Vector& vecVelocity);
void ReGameDLL_CGrenade_DefuseBombStart(IReGameHook_CGrenade_DefuseBombStart* chain, CGrenade* pthis, CBasePlayer* pPlayer);
void ReGameDLL_CGrenade_DefuseBombEnd(IReGameHook_CGrenade_DefuseBombEnd* chain, CGrenade* pthis, CBasePlayer* pPlayer, bool bDefused);
void ReGameDLL_CGrenade_ExplodeBomb(IReGameHook_CGrenade_ExplodeBomb* chain, CGrenade* pthis, TraceResult* ptr, int bitsDamageType);