#include <Ecore_X.h>
#include <Evas.h>
#include <Ecore.h>
#include <Ecore_Input.h>
#include <unistd.h>
#include <media_key.h>
#include <string.h>
#include <utilX.h>
#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "CAPI_SYSTEM_MEDIA_KEY"

static char *media_keys[] = {
	KEY_PLAYCD,
	KEY_STOPCD,
	KEY_PAUSECD,
	KEY_NEXTSONG,
	KEY_PREVIOUSSONG,
	KEY_REWIND,
	KEY_FASTFORWARD,
	KEY_PLAYPAUSE,
	KEY_MEDIA,
	NULL
};

static void (*_media_key_event_cb)(media_key_e key, media_key_event_e status, void* user_data) = NULL;
static void *_media_key_data = NULL;
static int _media_key_initialized = 0;

static Ecore_Event_Handler *media_key_up;
static Ecore_Event_Handler *media_key_down;

static Ecore_X_Window win;

static int _media_key_init(void)
{
	if (_media_key_initialized)
		return 0;

	win = ecore_x_window_input_new(ecore_x_window_root_first_get(), 0, 0, 1, 1);
	if (!win) {
		LOGE("failed to create input window");
		return -1;
	}

	ecore_x_icccm_title_set(win, "media key receiver");
	ecore_x_netwm_name_set(win, "media key receiver");
	ecore_x_netwm_pid_set(win, getpid());

	ecore_x_window_show(win);

	_media_key_initialized = 1;

	return 0;
}

static void _media_key_handler(const char *key_str, media_key_e event)
{
	media_key_e key;

	key = MEDIA_KEY_UNKNOWN;

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
	} else if (!strcmp(key_str, KEY_PLAYPAUSE)) {
		key = MEDIA_KEY_PLAYPAUSE;
	} else if (!strcmp(key_str, KEY_MEDIA)) {
		key = MEDIA_KEY_MEDIA;
	}

	if (_media_key_event_cb && key != MEDIA_KEY_UNKNOWN)
		_media_key_event_cb(key, event, _media_key_data);
}

static Eina_Bool _media_key_press_cb(void *data, int type, void *event)
{
	Evas_Event_Key_Down *ev;

	ev = event;
	if (!ev) {
		LOGE("Invalid event object");
		return ECORE_CALLBACK_RENEW;
	}

	_media_key_handler(ev->keyname, MEDIA_KEY_STATUS_PRESSED);

	return ECORE_CALLBACK_RENEW;
}

static Eina_Bool _media_key_release_cb(void *data, int type, void *event)
{
	Evas_Event_Key_Up *ev;

	ev = event;
	if (!ev) {
		LOGE("Invalid event object");
		return ECORE_CALLBACK_RENEW;
	}

	_media_key_handler(ev->keyname, MEDIA_KEY_STATUS_RELEASED);

	return ECORE_CALLBACK_RENEW;
}

static int _grab_media_key(void)
{
	int i;
	int ret;

	for (i = 0; media_keys[i]; i++) {
		ret = utilx_grab_key(ecore_x_display_get(), win, media_keys[i], OR_EXCLUSIVE_GRAB);
		if (ret) {
			LOGE("failed to grab key: %s", media_keys[i]);
			for (i = i - 1; i >= 0; i--)
				utilx_ungrab_key(ecore_x_display_get(), win, media_keys[i]);

			return ret;
		}
	}

	return 0;
}

static int _ungrab_media_key(void)
{
	int i;
	int ret;

	for (i = 0; media_keys[i]; i++) {
		ret = utilx_ungrab_key(ecore_x_display_get(), win, media_keys[i]);
		if (ret)
			LOGE("failed to ungrab key: %s", media_keys[i]);
	}

	return 0;
}

int media_key_reserve(media_key_event_cb callback, void* user_data)
{
	int ret;

	if (callback == NULL) {
		LOGE("[%s] media_key_event_cb callback is NULL", __FUNCTION__);
		return MEDIA_KEY_ERROR_INVALID_PARAMETER;
	}

	if (!_media_key_initialized) {
		if (_media_key_init())
			return MEDIA_KEY_ERROR_OPERATION_FAILED;
	}

	ret = _grab_media_key();
	if (ret) {
		LOGE("reserve media key error [%d]", ret);
		return MEDIA_KEY_ERROR_OPERATION_FAILED;
	}

	media_key_down = ecore_event_handler_add(ECORE_EVENT_KEY_DOWN, _media_key_press_cb, NULL);
	if (!media_key_down)
		LOGE("failed to register key down event handler");


	media_key_up = ecore_event_handler_add(ECORE_EVENT_KEY_UP, _media_key_release_cb, NULL);
	if (!media_key_down)
		LOGE("failed to register key up event handler");

	_media_key_event_cb = callback;
	_media_key_data = user_data;

	return MEDIA_KEY_ERROR_NONE;
}

int media_key_release(void)
{
	int ret;

	ret = _ungrab_media_key();
	if (ret) {
		LOGE("release media key error [%d]", ret);
		return MEDIA_KEY_ERROR_OPERATION_FAILED;
	}

	if (media_key_down) {
		ecore_event_handler_del(media_key_down);
		media_key_down = NULL;
	}

	if (media_key_up) {
		ecore_event_handler_del(media_key_up);
		media_key_up = NULL;
	}

	_media_key_event_cb = NULL;
	_media_key_data = NULL;

	return MEDIA_KEY_ERROR_NONE;
}
