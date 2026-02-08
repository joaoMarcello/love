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

// LOVE
#include "common/config.h"
#include "PlayGames.h"

#include <cerrno>
#include <SDL.h>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>

#if defined(LOVE_ANDROID)
#include "common/android.h"
#endif

namespace playgames
{
	namespace games
	{
		PlayGames::PlayGames() {}

		bool PlayGames::isEnabled()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "isPlayGamesEnabled", "()Z");
			jboolean result = env->CallBooleanMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return (bool)result;
		}

		void PlayGames::signIn()
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "PLAYGAMES", "signIn");
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "playGamesSignIn", "()V");
			env->CallVoidMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}

		void PlayGames::signOut()
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "PLAYGAMES", "signOut");
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "playGamesSignOut", "()V");
			env->CallVoidMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}

		bool PlayGames::isSignedIn()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "isPlayGamesSignedIn", "()Z");
			jboolean result = env->CallBooleanMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return (bool)result;
		}

		void PlayGames::submitScore(const char *leaderboardId, long score)
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "PLAYGAMES", "submitScore: %ld to %s", score, leaderboardId);
			
			std::string ID = (std::string) leaderboardId;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "playGamesSubmitScore", "(Ljava/lang/String;J)V");
			jstring ID_jstring = (jstring) env->NewStringUTF(ID.c_str());

			env->CallVoidMethod(activity, method_id, ID_jstring, (jlong)score);

			env->DeleteLocalRef(ID_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}

		void PlayGames::showLeaderboard(const char *leaderboardId)
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "PLAYGAMES", "showLeaderboard: %s", leaderboardId);
			
			std::string ID = (std::string) leaderboardId;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "playGamesShowLeaderboard", "(Ljava/lang/String;)V");
			jstring ID_jstring = (jstring) env->NewStringUTF(ID.c_str());

			env->CallVoidMethod(activity, method_id, ID_jstring);

			env->DeleteLocalRef(ID_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}

		void PlayGames::showAllLeaderboards()
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "PLAYGAMES", "showAllLeaderboards");
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "playGamesShowAllLeaderboards", "()V");
			env->CallVoidMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}

		std::string PlayGames::getPlayerName()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "playGamesGetPlayerName", "()Ljava/lang/String;");
			jstring jstr = (jstring) env->CallObjectMethod(activity, method_id);

			std::string result = "";
			if (jstr != nullptr)
			{
				const char *nativeString = env->GetStringUTFChars(jstr, 0);
				result = std::string(nativeString);
				env->ReleaseStringUTFChars(jstr, nativeString);
				env->DeleteLocalRef(jstr);
			}

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return result;
		}

		std::string PlayGames::getPlayerId()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "playGamesGetPlayerId", "()Ljava/lang/String;");
			jstring jstr = (jstring) env->CallObjectMethod(activity, method_id);

			std::string result = "";
			if (jstr != nullptr)
			{
				const char *nativeString = env->GetStringUTFChars(jstr, 0);
				result = std::string(nativeString);
				env->ReleaseStringUTFChars(jstr, nativeString);
				env->DeleteLocalRef(jstr);
			}

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return result;
		}
	}
}
