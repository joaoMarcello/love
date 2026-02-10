/**
 * PlayGames - Google Play Games Services v2 for Love2D
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

#ifndef PLAYGAMES_H
#define PLAYGAMES_H

// LOVE
#include "common/config.h"
#include "common/Module.h"
#include "common/StringMap.h"

// stdlib
#include <string>

//SDL
#include <SDL_syswm.h>
#include "window/Window.h"

namespace playgames
{
	namespace games
	{
		class PlayGames : public love::Module
		{
			public:
				PlayGames();
				virtual ~PlayGames() {}
				
				// Implements Module.
				virtual ModuleType getModuleType() const { return M_PLAYGAMES; }
				virtual const char *getName() const = 0;
				
				// Leaderboard methods
				bool isEnabled();
				void signIn();
				void signOut();
				bool isSignedIn();
				void submitScore(const char *leaderboardId, long score);
				void showLeaderboard(const char *leaderboardId);
				void showAllLeaderboards();
				std::string getPlayerName();
				std::string getPlayerId();
				
				// Score retrieval methods
				void getPlayerScore(const char *leaderboardId);
				bool hasScoreForLeaderboard(const char *leaderboardId);
				long getScore(const char *leaderboardId);

		};
	}
}

#endif // PLAYGAMES_H
