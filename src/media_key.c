#include <aul.h>
#include <media_key.h>
#include <string.h>
#include <utilX.h>
#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "CAPI_SYSTEM_MEDIA_KEY"

static void (*_media_key_event_cb)(media_key_e key, media_key_event_e status, void* user_data) = NULL;
static void *_media_key_data = NULL;
static int _media_key_initialized = 0;

extern int aul_key_reserve();
extern int aul_key_release();
extern int aul_key_init(int (*aul_handler) (bundle *, void *), void *data);


static int __aul_key_handler(bundle *b, void *data)
{
	int ret = MEDIA_KEY_ERROR_NONE;
	char *key_str;
	char *event_str;
	media_key_e key = MEDIA_KEY_UNKNOWN;
	media_key_event_e event = MEDIA_KEY_STATUS_UNKNOWN;

	key_str = (char *)bundle_get_val(b, AUL_K_MULTI_KEY);
	event_str = (char *)bundle_get_val(b, AUL_K_MULTI_KEY_EVENT);

	if (!strcmp(key_str, KEY_PLAYCD)) {
		key = MEDIA_KEY_PLAY;
	} else if (!strcmp(key_str, KEY_STOPCD)) {
		key = MEDIA_KEY_STOP;
	} else if (!strcmp(key_str, KEY_PAUSECD)) {
		key = MEDIA_KEY_PAUSE;
	} else if (!strcmp(key_str, KEY_NEXTSONG)) {
		key = MEDIA_KEY_NEXT;
	} else if (!strcmp(key_str, KEY_PREVIOUSSONG)) {
		key = MEDIA_KEY_PREVIOUS;
	} else if (!strcmp(key_str, KEY_REWIND)) {
		key = MEDIA_KEY_REWIND;
	} else if (!strcmp(key_str, KEY_FASTFORWARD)) {
		key = MEDIA_KEY_FASTFORWARD;
	}  else if (!strcmp(key_str, KEY_PLAYPAUSE)) {
		key = MEDIA_KEY_PLAYPAUSE;
	}

	if (!strcmp(event_str, AUL_V_KEY_RELEASED)) {
		event = MEDIA_KEY_STATUS_RELEASED;
	} else if (!strcmp(event_str, AUL_V_KEY_PRESSED)) {
		event = MEDIA_KEY_STATUS_PRESSED;
	}

	LOGD("[%s] media_key [%s][%d]", __FUNCTION__, key_str, key);
	LOGD("[%s] media_key_event [%s][%d]", __FUNCTION__, event_str, event);

	if(_media_key_event_cb)
		_media_key_event_cb(key, event, _media_key_data);

	return ret;
}

int media_key_reserve(media_key_event_cb callback, void* user_data)
{
	int ret;

	if(!_media_key_initialized) {
		aul_key_init(__aul_key_handler, NULL);
		_media_key_initialized = 1;
	}

	_media_key_event_cb = callback;
	_media_key_data = user_data;

	ret = aul_key_reserve();
	if(ret < 0) {
		LOGE("[%s] aul_key_set_event error [%d]", __FUNCTION__, ret);
		return MEDIA_KEY_ERROR_INVALID_PARAMETER;
	}

	return MEDIA_KEY_ERROR_NONE;
}

int media_key_release()
{
	int ret;

	ret = aul_key_release();
	if(ret < 0) {
		LOGE("[%s] aul_key_unset_event error [%d]", __FUNCTION__, ret);
		return MEDIA_KEY_ERROR_INVALID_PARAMETER;
	}

	_media_key_event_cb = NULL;
	_media_key_data = NULL;

	return MEDIA_KEY_ERROR_NONE;
}
