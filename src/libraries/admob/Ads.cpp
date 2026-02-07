/**
 * Created by bio1712 for love2d
 * Modified and updated by flamendless
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
#include "Ads.h"

#include <cerrno>
#include <SDL.h>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>

#if defined(LOVE_MACOSX)
#include <CoreServices/CoreServices.h>
#elif defined(LOVE_IOS)
#include "common/ios.h"
#elif defined(LOVE_LINUX) || defined(LOVE_ANDROID)
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#elif defined(LOVE_WINDOWS)
#include "common/utf8.h"
#include <shlobj.h>
#include <shellapi.h>
#pragma comment(lib, "shell32.lib")
#endif
#if defined(LOVE_ANDROID)
#include "common/android.h"
#elif defined(LOVE_LINUX)
#include <spawn.h>
#endif


namespace admob
{
	namespace ads
	{
		Ads::Ads() {}

		void Ads::test() const
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "ADMOBLOG", "Admob TEST called");
		}

		void Ads::createBanner(const char *adID,const char *position)
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "ADMOBLOG", "createBanner");
			if (hasBannerBeenCreated)
			{
				__android_log_print(ANDROID_LOG_VERBOSE, "ADMOBLOG", "Banner has already been created!");
				return;
			}

			hasBannerBeenCreated = true;

			std::string ID = (std::string) adID;
			std::string pos = (std::string) position;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "createBanner", "(Ljava/lang/String;Ljava/lang/String;)V");
			jstring ID_jstring = (jstring) env->NewStringUTF(ID.c_str());
			jstring pos_jstring = (jstring) env->NewStringUTF(pos.c_str());

			env->CallVoidMethod(activity, method_id, ID_jstring, pos_jstring);

			env->DeleteLocalRef(ID_jstring);
			env->DeleteLocalRef(pos_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}


		void Ads::hideBanner()
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "ADMOBLOG", "hideBanner");
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "hideBanner", "()V");

			env->CallVoidMethod(activity, method_id);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}

		void Ads::showBanner()
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "ADMOBLOG", "showBanner");
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "showBanner", "()V");

			env->CallVoidMethod(activity, method_id);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}

		void Ads::requestInterstitial(const char *adID)
		{
			std::string ID = (std::string) adID;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "requestInterstitial", "(Ljava/lang/String;)V");
			jstring ID_jstring = (jstring) env->NewStringUTF(ID.c_str());

			env->CallVoidMethod(activity, method_id, ID_jstring);

			env->DeleteLocalRef(ID_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}

		bool Ads::isInterstitialLoaded()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();

			jclass clazz(env->GetObjectClass(activity));
			jmethodID method_id = env->GetMethodID(clazz, "isInterstitialLoaded", "()Z");

			jboolean adLoaded = env->CallBooleanMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);

			return adLoaded;
		}

		void Ads::showInterstitial()
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "ADMOBLOG", "showInterstitial");
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "showInterstitial", "()V");

			env->CallVoidMethod(activity, method_id);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}


		void Ads::requestRewardedAd(const char *adID)
		{
			std::string ID = (std::string) adID;

			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "requestRewardedAd", "(Ljava/lang/String;)V");
			jstring ID_jstring = (jstring) env->NewStringUTF(ID.c_str());

			env->CallVoidMethod(activity, method_id, ID_jstring);

			env->DeleteLocalRef(ID_jstring);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}

		bool Ads::isRewardedAdLoaded()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();

			jclass clazz(env->GetObjectClass(activity));
			jmethodID method_id = env->GetMethodID(clazz, "isRewardedAdLoaded", "()Z");

			jboolean adLoaded = env->CallBooleanMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);

			return adLoaded;
		}

		void Ads::showRewardedAd()
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "ADMOBLOG", "showRewardedAd");
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "showRewardedAd", "()V");

			env->CallVoidMethod(activity, method_id);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}

		void Ads::changeEUConsent()
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "ADMOBLOG", "changeEUConsent");
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();
			jclass clazz (env->GetObjectClass(activity));

			jmethodID method_id = env->GetMethodID(clazz, "changeEUConsent", "()V");

			env->CallVoidMethod(activity, method_id);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);
		}

		std::string Ads::getDeviceLanguage()
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "ADMOBLOG", "getDeviceLanguage");
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();

			jclass clazz(env->GetObjectClass(activity));
			jmethodID method_id = env->GetMethodID(clazz, "getDeviceLanguage",  "()Ljava/lang/String;");

			jstring countryCode = (jstring) env->CallObjectMethod(activity, method_id);

			const char *strPtr = env->GetStringUTFChars(countryCode, 0);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);

			return (std::string) strPtr;
		}

		std::string Ads::getAppVersionName()
		{
			__android_log_print(ANDROID_LOG_VERBOSE, "ADMOBLOG", "getAppVersionName");
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();

			jclass clazz(env->GetObjectClass(activity));
			jmethodID method_id = env->GetMethodID(clazz, "getAppVersionName",  "()Ljava/lang/String;");

			jstring versionName = (jstring) env->CallObjectMethod(activity, method_id);

			const char *strPtr = env->GetStringUTFChars(versionName, 0);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);

			return (std::string) strPtr;
		}

		//For callbacks

		bool Ads::coreInterstitialError()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();

			jclass clazz(env->GetObjectClass(activity));
			jmethodID method_id = env->GetMethodID(clazz, "coreInterstitialError", "()Z");

			jboolean adHasFailedToLoad = env->CallBooleanMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);

			return adHasFailedToLoad;
		}

		bool Ads::coreInterstitialClosed()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();

			jclass clazz(env->GetObjectClass(activity));
			jmethodID method_id = env->GetMethodID(clazz, "coreInterstitialClosed", "()Z");

			jboolean adHasBeenClosed = env->CallBooleanMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);

			return adHasBeenClosed;
		}

		bool Ads::coreRewardedAdError()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();

			jclass clazz(env->GetObjectClass(activity));
			jmethodID method_id = env->GetMethodID(clazz, "coreRewardedAdError", "()Z");

			jboolean adHasFailedToLoad = env->CallBooleanMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);

			return adHasFailedToLoad;
		}

		bool Ads::coreRewardedAdDidStop()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();

			jclass clazz(env->GetObjectClass(activity));
			jmethodID method_id = env->GetMethodID(clazz, "coreRewardedAdDidStop", "()Z");

			jboolean adHasBeenClosed = env->CallBooleanMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);

			return adHasBeenClosed;
		}

		bool Ads::coreRewardedAdDidFinish()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();

			jclass clazz(env->GetObjectClass(activity));
			jmethodID method_id = env->GetMethodID(clazz, "coreRewardedAdDidFinish", "()Z");

			jboolean videoHasFinishedPlaying = env->CallBooleanMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);

			return videoHasFinishedPlaying;
		}

		std::string Ads::coreGetRewardType()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();

			jclass clazz(env->GetObjectClass(activity));
			jmethodID method_id = env->GetMethodID(clazz, "coreGetRewardType",  "()Ljava/lang/String;");

			jstring rewardType = (jstring) env->CallObjectMethod(activity, method_id);

			const char *strPtr = env->GetStringUTFChars(rewardType, 0);
			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);

			return (std::string) strPtr;
		}

		double Ads::coreGetRewardQuantity()
		{
			JNIEnv *env = (JNIEnv*) SDL_AndroidGetJNIEnv();

			jobject activity = (jobject) SDL_AndroidGetActivity();

			jclass clazz(env->GetObjectClass(activity));
			jmethodID method_id = env->GetMethodID(clazz, "coreGetRewardQuantity",  "()D");

			jdouble rewardQty = (jdouble) env->CallDoubleMethod(activity, method_id);

			env->DeleteLocalRef(activity);
			env->DeleteLocalRef(clazz);

			return static_cast<double>(rewardQty);
		}
	}
}
