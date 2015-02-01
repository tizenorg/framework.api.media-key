/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __TIZEN_SYSTEM_MEDIA_KEY_H__
#define __TIZEN_SYSTEM_MEDIA_KEY_H__

#include <tizen.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @file media_key.h
 */

/**
 * @addtogroup CAPI_SYSTEM_MEDIA_KEY_MODULE
 * @{
 */

/**
 * @brief Enumeration for error codes of a media key.
 *
 * @since_tizen 2.3
 */

typedef enum
{
	MEDIA_KEY_ERROR_NONE = TIZEN_ERROR_NONE,                           /**< Successful */
	MEDIA_KEY_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid parameter */
	MEDIA_KEY_ERROR_OPERATION_FAILED = TIZEN_ERROR_MEDIA_KEY | 0x01,   /**< Reserve/Release failed */
} media_key_error_e;

/**
 * @brief Enumeration for media keys.
 *
 * @since_tizen 2.3
 */
typedef enum
{
	MEDIA_KEY_PLAY,          /**< Play key */
	MEDIA_KEY_STOP,          /**< Stop key */
	MEDIA_KEY_PAUSE,         /**< Pause key */
	MEDIA_KEY_PREVIOUS,      /**< Previous key */
	MEDIA_KEY_NEXT,          /**< Next key */
	MEDIA_KEY_FASTFORWARD,   /**< Fastforward key */
	MEDIA_KEY_REWIND,        /**< Rewind key */
	MEDIA_KEY_PLAYPAUSE,     /**< Playpause key */
	MEDIA_KEY_MEDIA,         /**< Media key for earjack */
	MEDIA_KEY_UNKNOWN,       /**< Unknown key */
} media_key_e;

/**
 * @brief Enumeration for event statuses of a media key.
 *
 * @since_tizen 2.3
 */
typedef enum
{
	MEDIA_KEY_STATUS_PRESSED,  /**< Pressed status */
	MEDIA_KEY_STATUS_RELEASED, /**< Released status */
	MEDIA_KEY_STATUS_UNKNOWN,  /**< Unknown status */
} media_key_event_e;

/**
 * @brief Called when the status of the media key is changed.
 *
 * @since_tizen 2.3
 *
 * @param[in] key The key whose status is changed
 * @param[in] status The status of the key
 * @param[in] user_data The user data passed from the callback registration function
 * @pre media_key_reserve() will invoke this callback function.
 * @see media_key_reserve()
 * @see media_key_release()
 */
typedef void (*media_key_event_cb)(media_key_e key, media_key_event_e status, void* user_data);

/**
 * @brief Registers a change event callback for all media keys.
 *
 * @since_tizen 2.3
 *
 * @param[in] callback The callback function to invoke
 * @param[in] user_data The user data to be passed to the callback function
 * @return  @c 0 on success,
 *          otherwise a negative error value
 * @retval  #MEDIA_KEY_ERROR_NONE Successful
 * @retval  #MEDIA_KEY_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #MEDIA_KEY_ERROR_OPERATION_FAILED Reserve key failed
 * @see media_key_release()
*/
int media_key_reserve(media_key_event_cb callback, void* user_data);

/**
 * @brief Unregisters the change event callback function.
 *
 * @since_tizen 2.3
 *
 * @return  @c 0 on success,
 *          otherwise a negative error value
 * @retval  #MEDIA_KEY_ERROR_NONE Successful
 * @retval  #MEDIA_KEY_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #MEDIA_KEY_ERROR_OPERATION_FAILED Release key failed
 * @see media_key_reserve()
 */
int media_key_release(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_SYSTEM_MEDIA_KEY_H__ */

