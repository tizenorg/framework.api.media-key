#include <tet_api.h>
#include <media_key.h>

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_media_key_reserve_positive(void);

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

struct tet_testlist tet_testlist[] = {
	{ utc_media_key_reserve_positive, POSITIVE_TC_IDX },
	{ NULL, 0},
};

static void startup(void)
{
}

static void cleanup(void)
{
	media_key_release();
}

void event_cb(media_key_e key, media_key_event_e status, void* user_data)
{
}

/**
 * @brief Positive test case of media_key_reserve()
 */
static void utc_media_key_reserve_positive(void)
{
	int r = 0;

	r = media_key_reserve(event_cb, NULL);

        if(r == MEDIA_KEY_ERROR_NONE)
        {
                dts_pass("utc_media_key_reserve_positive", "passed");
        }
        else
        {
                dts_fail("utc_media_key_reserve_positive", "failed");
        }
}
