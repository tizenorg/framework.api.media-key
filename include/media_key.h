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
 * @addtogroup CAPI_SYSTEM_MEDIA_KEY_MODULE
 * @{
 */

/**
 * @brief Enumeration of error code for media key
 */

typedef enum
{
	MEDIA_KEY_ERROR_NONE = TIZEN_ERROR_NONE, /**< Successful */
	MEDIA_KEY_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid parameter */
} media_key_error_e;


/**
 * @brief Enumeration of media key
 */
typedef enum
{
	MEDIA_KEY_PLAY, /**< */
	MEDIA_KEY_STOP, /**< */
	MEDIA_KEY_PAUSE, /**< */
	MEDIA_KEY_PREVIOUS, /**< */
	MEDIA_KEY_NEXT, /**< */
	MEDIA_KEY_FASTFORWARD, /**< */
	MEDIA_KEY_REWIND, /**< */
	MEDIA_KEY_PLAYPAUSE, /**< */
	MEDIA_KEY_UNKNOWN,
} media_key_e;


/**
 * @brief Enumeration of media key event status
 */
typedef enum
{
	MEDIA_KEY_STATUS_PRESSED, /**<  */
	MEDIA_KEY_STATUS_RELEASED, /**<  */
	MEDIA_KEY_STATUS_UNKNOWN,
} media_key_event_e;


/**
 * @brief   Called when the status of media key is changed
 * @param[in] key the key which has status change
 * @param[in] status the status of key
 * @param[in] user_data The user data passed from the callback registration function
 * @pre media_key_reserve() will invoke this callback function.
 * @see media_key_reserve()
 * @see media_key_release()
 */
typedef void (*media_key_event_cb)(media_key_e key, media_key_event_e status, void* user_data);


/**
 * @brief   Registers a change event callback for all media keys.
 *
 * @param[in] callback The callback function to invoke
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return  0 on success, otherwise a negative error value.
 * @retval  #MEDIA_KEY_ERROR_NONE Successful
 * @retval  #MEDIA_KEY_ERROR_INVALID_PARAMETER Invalid parameter
 * @post runtime_info_changed_cb() will be invoked.
 *
 * @see media_key_release()
 * @see media_key_event_cb()
*/
int media_key_reserve(media_key_event_cb callback, void* user_data);


/**
 * @brief   Unregisters the callback function.
 *
 * @param[in] key The runtime information type
 * @return  0 on success, otherwise a negative error value.
 * @retval  #MEDIA_KEY_ERROR_NONE Successful
 * @retval  #MEDIA_KEY_ERROR_INVALID_PARAMETER Invalid parameter
 *
 * @see media_key_set_event_cb()
 */
int media_key_release();


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_SYSTEM_MEDIA_KEY_H__ */

