#include "precompiled.h"

CMatchUtil gMatchUtil;

cvar_t* CMatchUtil::CvarRegister(const char* Name, const char* Value)
{
	cvar_t* Pointer = g_engfuncs.pfnCVarGetPointer(Name);

	if (!Pointer)
	{
		this->m_CvarData[Name].name = Name;

		this->m_CvarData[Name].string = (char*)(Value);

		this->m_CvarData[Name].flags = (FCVAR_SERVER | FCVAR_PROTECTED | FCVAR_SPONLY | FCVAR_UNLOGGED);

		g_engfuncs.pfnCVarRegister(&this->m_CvarData[Name]);

		Pointer = g_engfuncs.pfnCVarGetPointer(this->m_CvarData[Name].name);

		if (Pointer)
		{
			g_engfuncs.pfnCvar_DirectSet(Pointer, Value);
		}
	}

	return Pointer;
}

const char* CMatchUtil::GetAuthId(CBasePlayer* Player)
{
	if (Player)
	{
		if (!FNullEnt(Player->edict()))
		{
			if (!(Player->edict()->v.flags & FL_FAKECLIENT))
			{
				return g_engfuncs.pfnGetPlayerAuthId(Player->edict());
			}

			return STRING(Player->edict()->v.netname);
		}
	}

	return nullptr;
}

int CMatchUtil::MakeDirectory(const char* Path)
{
	struct stat st = { 0 };

	if (stat(Path, &st) == -1)
	{
#if defined(_WIN32)
		return _mkdir(Path);
#else
		return mkdir(Path, 0755);
#endif
	}

	return 0;
}

void CMatchUtil::ServerExecute(std::string CommandData)
{
	if (!CommandData.empty())
	{
		std::ofstream File(MATCH_API_TEMP_FILE, std::ofstream::binary);

		if (File)
		{
			File.write(CommandData.c_str(), CommandData.size());
		}

		File.close();
	}

	char ExecuteCommand[MAX_PATH] = { 0 };

	Q_snprintf(ExecuteCommand, sizeof(ExecuteCommand), "exec %s\n", MATCH_API_TEMP_FILE);

	if (ExecuteCommand[0])
	{
		g_engfuncs.pfnServerCommand(ExecuteCommand);
	}
}

bool CMatchUtil::PlayerIsVisible(int PlayerIndex, int TargetIndex)
{
	auto Player = UTIL_PlayerByIndexSafe(PlayerIndex);

	auto Target = UTIL_PlayerByIndexSafe(TargetIndex);

	if (Player && Target)
	{
		edict_t* pEntity = Player->edict();
		edict_t* pTarget = Target->edict();

		if (pEntity->v.flags & FL_NOTARGET)
		{
			return false;
		}
		
		Vector vLooker = (pEntity->v.origin + pEntity->v.view_ofs);
		Vector vTarget = (pTarget->v.origin + pTarget->v.view_ofs);

		TraceResult tr;

		auto oldSolid = pTarget->v.solid;

		pTarget->v.solid = SOLID_NOT;

		g_engfuncs.pfnTraceLine(vLooker, vTarget, FALSE, pEntity, &tr);

		pTarget->v.solid = oldSolid;

		if (tr.fInOpen && tr.fInWater)
		{
			return false;
		}
		else if ((tr.flFraction == 1.0) || (ENTINDEX(tr.pHit) == Target->entindex()))
		{
			return true;
		}
	}

	return false;
}
