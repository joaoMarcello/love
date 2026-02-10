/**
 * PlayGames - Google Play Games Services v2 for Love2D
 * Lua wrapper
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

// LOVE
#include "common/Module.h"
#include "common/runtime.h"
#include "wrap_PlayGames.h"
#include "sdl/PlayGames.h"
#include <android/log.h>

//lua
extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

namespace playgames
{
	namespace games
	{
		#define instance() (love::Module::getInstance<PlayGames>(love::Module::M_PLAYGAMES))

		int w_isEnabled(lua_State *L)
		{
			bool ret = instance()->isEnabled();
			love::luax_pushboolean(L, ret);
			return 1;
		}

		int w_signIn(lua_State *L)
		{
			instance()->signIn();
			return 0;
		}

		int w_signOut(lua_State *L)
		{
			instance()->signOut();
			return 0;
		}

		int w_isSignedIn(lua_State *L)
		{
			bool ret = instance()->isSignedIn();
			love::luax_pushboolean(L, ret);
			return 1;
		}

		int w_submitScore(lua_State *L)
		{
			const char *leaderboardId = luaL_checkstring(L, 1);
			lua_Number score_number = luaL_checknumber(L, 2);
			long score = (long)score_number;
			instance()->submitScore(leaderboardId, score);
			return 0;
		}

		int w_showLeaderboard(lua_State *L)
		{
			const char *leaderboardId = luaL_checkstring(L, 1);
			instance()->showLeaderboard(leaderboardId);
			return 0;
		}

		int w_showAllLeaderboards(lua_State *L)
		{
			instance()->showAllLeaderboards();
			return 0;
		}

		int w_getPlayerName(lua_State *L)
		{
			std::string ret = instance()->getPlayerName();
			love::luax_pushstring(L, ret);
			return 1;
		}

		int w_getPlayerId(lua_State *L)
		{
			std::string ret = instance()->getPlayerId();
			love::luax_pushstring(L, ret);
			return 1;
		}

		int w_getPlayerScore(lua_State *L)
		{
			const char *leaderboardId = luaL_checkstring(L, 1);
			instance()->getPlayerScore(leaderboardId);
			return 0;
		}

		int w_hasScoreForLeaderboard(lua_State *L)
		{
			const char *leaderboardId = luaL_checkstring(L, 1);
			bool ret = instance()->hasScoreForLeaderboard(leaderboardId);
			love::luax_pushboolean(L, ret);
			return 1;
		}

		int w_getScore(lua_State *L)
		{
			const char *leaderboardId = luaL_checkstring(L, 1);
			long ret = instance()->getScore(leaderboardId);
			lua_pushnumber(L, (lua_Number)ret);
			return 1;
		}
		
		// ========== Cloud Save Wrappers ==========
		
		int w_isCloudSaveEnabled(lua_State *L)
		{
			bool ret = instance()->isCloudSaveEnabled();
			love::luax_pushboolean(L, ret);
			return 1;
		}
		
		int w_cloudSaveSnapshot(lua_State *L)
		{
			const char *snapshotName = luaL_checkstring(L, 1);
			size_t dataSize;
			const char *data = luaL_checklstring(L, 2, &dataSize);
			const char *description = luaL_optstring(L, 3, "");
			lua_Number playedTime_number = luaL_optnumber(L, 4, 0);
			long playedTime = (long)playedTime_number;
			lua_Number progressValue_number = luaL_optnumber(L, 5, -1);
			long progressValue = (long)progressValue_number;
			
			instance()->cloudSaveSnapshot(snapshotName, data, dataSize, description, playedTime, progressValue);
			return 0;
		}
		
		int w_cloudLoadSnapshot(lua_State *L)
		{
			const char *snapshotName = luaL_checkstring(L, 1);
			instance()->cloudLoadSnapshot(snapshotName);
			return 0;
		}
		
		int w_cloudDeleteSnapshot(lua_State *L)
		{
			const char *snapshotName = luaL_checkstring(L, 1);
			instance()->cloudDeleteSnapshot(snapshotName);
			return 0;
		}
		
		int w_cloudShowSavedGamesUI(lua_State *L)
		{
			const char *title = luaL_optstring(L, 1, "Saved Games");
			bool allowAdd = love::luax_optboolean(L, 2, true);
			bool allowDelete = love::luax_optboolean(L, 3, true);
			int maxSnapshots = (int)luaL_optinteger(L, 4, 3);
			
			instance()->cloudShowSavedGamesUI(title, allowAdd, allowDelete, maxSnapshots);
			return 0;
		}
		
		int w_cloudHasLoadedSnapshot(lua_State *L)
		{
			const char *snapshotName = luaL_checkstring(L, 1);
			bool ret = instance()->cloudHasLoadedSnapshot(snapshotName);
			love::luax_pushboolean(L, ret);
			return 1;
		}
		
		int w_cloudGetLoadedSnapshotData(lua_State *L)
		{
			const char *snapshotName = luaL_checkstring(L, 1);
			size_t outSize = 0;
			std::string ret = instance()->cloudGetLoadedSnapshotData(snapshotName, &outSize);
			
			if (outSize > 0)
				lua_pushlstring(L, ret.c_str(), outSize);
			else
				lua_pushnil(L);
			
			return 1;
		}
		
		int w_cloudHasSaveResult(lua_State *L)
		{
			const char *snapshotName = luaL_checkstring(L, 1);
			bool ret = instance()->cloudHasSaveResult(snapshotName);
			love::luax_pushboolean(L, ret);
			return 1;
		}
		
		int w_cloudGetSaveResult(lua_State *L)
		{
			const char *snapshotName = luaL_checkstring(L, 1);
			bool ret = instance()->cloudGetSaveResult(snapshotName);
			love::luax_pushboolean(L, ret);
			return 1;
		}
		
		int w_cloudHasError(lua_State *L)
		{
			const char *snapshotName = luaL_checkstring(L, 1);
			bool ret = instance()->cloudHasError(snapshotName);
			love::luax_pushboolean(L, ret);
			return 1;
		}
		
		int w_cloudGetError(lua_State *L)
		{
			const char *snapshotName = luaL_checkstring(L, 1);
			std::string ret = instance()->cloudGetError(snapshotName);
			love::luax_pushstring(L, ret);
			return 1;
		}
		
		int w_cloudIsSaveInProgress(lua_State *L)
		{
			bool ret = instance()->cloudIsSaveInProgress();
			love::luax_pushboolean(L, ret);
			return 1;
		}
		
		int w_cloudIsLoadInProgress(lua_State *L)
		{
			bool ret = instance()->cloudIsLoadInProgress();
			love::luax_pushboolean(L, ret);
			return 1;
		}
		
		int w_cloudClearResults(lua_State *L)
		{
			instance()->cloudClearResults();
			return 0;
		}

		// List of functions to wrap.
		static const luaL_Reg functions[] =
		{
			{ "isEnabled", w_isEnabled },
			{ "signIn", w_signIn },
			{ "signOut", w_signOut },
			{ "isSignedIn", w_isSignedIn },
			{ "submitScore", w_submitScore },
			{ "showLeaderboard", w_showLeaderboard },
			{ "showAllLeaderboards", w_showAllLeaderboards },
			{ "getPlayerName", w_getPlayerName },
			{ "getPlayerId", w_getPlayerId },
			{ "getPlayerScore", w_getPlayerScore },
			{ "hasScoreForLeaderboard", w_hasScoreForLeaderboard },
			{ "getScore", w_getScore },
			
			// Cloud Save
			{ "isCloudSaveEnabled", w_isCloudSaveEnabled },
			{ "cloudSaveSnapshot", w_cloudSaveSnapshot },
			{ "cloudLoadSnapshot", w_cloudLoadSnapshot },
			{ "cloudDeleteSnapshot", w_cloudDeleteSnapshot },
			{ "cloudShowSavedGamesUI", w_cloudShowSavedGamesUI },
			{ "cloudHasLoadedSnapshot", w_cloudHasLoadedSnapshot },
			{ "cloudGetLoadedSnapshotData", w_cloudGetLoadedSnapshotData },
			{ "cloudHasSaveResult", w_cloudHasSaveResult },
			{ "cloudGetSaveResult", w_cloudGetSaveResult },
			{ "cloudHasError", w_cloudHasError },
			{ "cloudGetError", w_cloudGetError },
			{ "cloudIsSaveInProgress", w_cloudIsSaveInProgress },
			{ "cloudIsLoadInProgress", w_cloudIsLoadInProgress },
			{ "cloudClearResults", w_cloudClearResults },

			{ 0, 0 }
		};

		extern "C" int luaopen_playgames(lua_State *L)
		{
			PlayGames *instance = instance();
			if (instance == nullptr)
				love::luax_catchexcept(L, [&](){ instance = new playgames::games::sdl::PlayGames(); });
			else
				instance->retain();

			love::WrappedModule w;
			w.module = instance;
			w.name = "playgames";
			w.type = &love::Module::type;
			w.functions = functions;
			w.types = nullptr;

			return love::luax_register_module(L, w);
		}
	}
}
