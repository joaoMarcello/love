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
