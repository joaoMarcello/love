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

		void PlayGames::getPlayerScore(const char *leaderboardId)
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "PLAYGAMES", "getPlayerScore: %s", leaderboardId);
			
			std::string ID = (std::string) leaderboardId;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "playGamesGetPlayerScore", "(Ljava/lang/String;)V");
			jstring ID_jstring = (jstring) env->NewStringUTF(ID.c_str());

			env->CallVoidMethod(activity, method_id, ID_jstring);

			env->DeleteLocalRef(ID_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}

		bool PlayGames::hasScoreForLeaderboard(const char *leaderboardId)
		{
			std::string ID = (std::string) leaderboardId;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "playGamesHasScoreForLeaderboard", "(Ljava/lang/String;)Z");
			jstring ID_jstring = (jstring) env->NewStringUTF(ID.c_str());

			jboolean result = env->CallBooleanMethod(activity, method_id, ID_jstring);

			env->DeleteLocalRef(ID_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return (bool)result;
		}

		long PlayGames::getScore(const char *leaderboardId)
		{
			std::string ID = (std::string) leaderboardId;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "playGamesGetScore", "(Ljava/lang/String;)J");
			jstring ID_jstring = (jstring) env->NewStringUTF(ID.c_str());

			jlong result = env->CallLongMethod(activity, method_id, ID_jstring);

			env->DeleteLocalRef(ID_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return (long)result;
		}
		
		// ========== Cloud Save Methods ==========
		
		bool PlayGames::isCloudSaveEnabled()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "isCloudSaveEnabled", "()Z");
			jboolean result = env->CallBooleanMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return (bool)result;
		}
		
	void PlayGames::cloudSaveSnapshot(const char *snapshotName, const char *data, size_t dataSize, const char *description, long playedTime, long progressValue)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "PLAYGAMES", "cloudSaveSnapshot: %s (size: %zu, progress: %ld)", snapshotName, dataSize, progressValue);
		
		std::string nameStr = (std::string) snapshotName;
		std::string descStr = description ? (std::string) description : "";

		JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
		jobject activity = (jobject) SDL_AndroidGetActivity();
		jclass clazz (env->GetObjectClass(activity));

		// Cria byte array Java
		jbyteArray dataArray = env->NewByteArray(dataSize);
		env->SetByteArrayRegion(dataArray, 0, dataSize, (jbyte*)data);

		jmethodID method_id = env->GetMethodID(clazz, "cloudSaveSnapshot", "(Ljava/lang/String;[BLjava/lang/String;JJ)V");
		jstring name_jstring = (jstring) env->NewStringUTF(nameStr.c_str());
		jstring desc_jstring = (jstring) env->NewStringUTF(descStr.c_str());

		env->CallVoidMethod(activity, method_id, name_jstring, dataArray, desc_jstring, (jlong)playedTime, (jlong)progressValue);

		env->DeleteLocalRef(desc_jstring);
		env->DeleteLocalRef(name_jstring);
		env->DeleteLocalRef(dataArray);
		env->DeleteLocalRef(activity);
		env->DeleteLocalRef(clazz);
	}
	
	void PlayGames::cloudLoadSnapshot(const char *snapshotName)
	{
		__android_log_print(ANDROID_LOG_VERBOSE, "PLAYGAMES", "cloudLoadSnapshot: %s", snapshotName);
		
		std::string nameStr = (std::string) snapshotName;

		JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
		jobject activity = (jobject) SDL_AndroidGetActivity();
		jclass clazz (env->GetObjectClass(activity));

		jmethodID method_id = env->GetMethodID(clazz, "cloudLoadSnapshot", "(Ljava/lang/String;)V");
		jstring name_jstring = (jstring) env->NewStringUTF(nameStr.c_str());

		env->CallVoidMethod(activity, method_id, name_jstring);

		env->DeleteLocalRef(name_jstring);
		env->DeleteLocalRef(activity);
		env->DeleteLocalRef(clazz);
	}
		
		void PlayGames::cloudDeleteSnapshot(const char *snapshotName)
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "PLAYGAMES", "cloudDeleteSnapshot: %s", snapshotName);
			
			std::string nameStr = (std::string) snapshotName;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "cloudDeleteSnapshot", "(Ljava/lang/String;)V");
			jstring name_jstring = (jstring) env->NewStringUTF(nameStr.c_str());

			env->CallVoidMethod(activity, method_id, name_jstring);

			env->DeleteLocalRef(name_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}
		
		void PlayGames::cloudShowSavedGamesUI(const char *title, bool allowAdd, bool allowDelete, int maxSnapshots)
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "PLAYGAMES", "cloudShowSavedGamesUI");
			
			std::string titleStr = title ? (std::string) title : "Saved Games";

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "cloudShowSavedGamesUI", "(Ljava/lang/String;ZZI)V");
			jstring title_jstring = (jstring) env->NewStringUTF(titleStr.c_str());

			env->CallVoidMethod(activity, method_id, title_jstring, (jboolean)allowAdd, (jboolean)allowDelete, (jint)maxSnapshots);

			env->DeleteLocalRef(title_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}
		
		bool PlayGames::cloudHasLoadedSnapshot(const char *snapshotName)
		{
			std::string nameStr = (std::string) snapshotName;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "cloudHasLoadedSnapshot", "(Ljava/lang/String;)Z");
			jstring name_jstring = (jstring) env->NewStringUTF(nameStr.c_str());

			jboolean result = env->CallBooleanMethod(activity, method_id, name_jstring);

			env->DeleteLocalRef(name_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return (bool)result;
		}
		
		std::string PlayGames::cloudGetLoadedSnapshotData(const char *snapshotName, size_t *outSize)
		{
			std::string nameStr = (std::string) snapshotName;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "cloudGetLoadedSnapshotData", "(Ljava/lang/String;)[B");
			jstring name_jstring = (jstring) env->NewStringUTF(nameStr.c_str());

			jbyteArray dataArray = (jbyteArray) env->CallObjectMethod(activity, method_id, name_jstring);

			std::string result = "";
			if (dataArray != nullptr)
			{
				jsize len = env->GetArrayLength(dataArray);
				jbyte* bytes = env->GetByteArrayElements(dataArray, nullptr);
				
				if (outSize != nullptr)
					*outSize = (size_t)len;
				
				result = std::string((char*)bytes, len);
				
				env->ReleaseByteArrayElements(dataArray, bytes, JNI_ABORT);
				env->DeleteLocalRef(dataArray);
			}
			else if (outSize != nullptr)
			{
				*outSize = 0;
			}

			env->DeleteLocalRef(name_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return result;
		}
		
		bool PlayGames::cloudHasSaveResult(const char *snapshotName)
		{
			std::string nameStr = (std::string) snapshotName;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "cloudHasSaveResult", "(Ljava/lang/String;)Z");
			jstring name_jstring = (jstring) env->NewStringUTF(nameStr.c_str());

			jboolean result = env->CallBooleanMethod(activity, method_id, name_jstring);

			env->DeleteLocalRef(name_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return (bool)result;
		}
		
		bool PlayGames::cloudGetSaveResult(const char *snapshotName)
		{
			std::string nameStr = (std::string) snapshotName;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "cloudGetSaveResult", "(Ljava/lang/String;)Z");
			jstring name_jstring = (jstring) env->NewStringUTF(nameStr.c_str());

			jboolean result = env->CallBooleanMethod(activity, method_id, name_jstring);

			env->DeleteLocalRef(name_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return (bool)result;
		}
		
		bool PlayGames::cloudHasError(const char *snapshotName)
		{
			std::string nameStr = (std::string) snapshotName;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "cloudHasError", "(Ljava/lang/String;)Z");
			jstring name_jstring = (jstring) env->NewStringUTF(nameStr.c_str());

			jboolean result = env->CallBooleanMethod(activity, method_id, name_jstring);

			env->DeleteLocalRef(name_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return (bool)result;
		}
		
		std::string PlayGames::cloudGetError(const char *snapshotName)
		{
			std::string nameStr = (std::string) snapshotName;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "cloudGetError", "(Ljava/lang/String;)Ljava/lang/String;");
			jstring name_jstring = (jstring) env->NewStringUTF(nameStr.c_str());

			jstring jstr = (jstring) env->CallObjectMethod(activity, method_id, name_jstring);

			std::string result = "";
			if (jstr != nullptr)
			{
				const char *nativeString = env->GetStringUTFChars(jstr, 0);
				result = std::string(nativeString);
				env->ReleaseStringUTFChars(jstr, nativeString);
				env->DeleteLocalRef(jstr);
			}

			env->DeleteLocalRef(name_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return result;
		}
		
		bool PlayGames::cloudIsSaveInProgress()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "cloudIsSaveInProgress", "()Z");
			jboolean result = env->CallBooleanMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return (bool)result;
		}
		
		bool PlayGames::cloudIsLoadInProgress()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "cloudIsLoadInProgress", "()Z");
			jboolean result = env->CallBooleanMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
			
			return (bool)result;
		}
		
		void PlayGames::cloudClearResults()
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "PLAYGAMES", "cloudClearResults");
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();
			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "cloudClearResults", "()V");
			env->CallVoidMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}
	}
}
