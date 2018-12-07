/*
 * Copyright (c) 2016-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef WAYLAND_THREAD_H
#define WAYLAND_THREAD_H

#include <wayland-client.h>

/*
 * wlExternalApiLock()
 *
 * Tries to acquire the external API lock. If the lock is already acquired by
 * another thread, it will block until the lock is released.
 *
 * Calling this function twice without calling wlExternalApiUnlock() in between
 * will fail.
 *
 * First call to wlExternalApiLock() will initialize the external API lock
 * resources.
 *
 * Returns 0 upon success; otherwise returns -1.
 */
int wlExternalApiLock(void);

/*
 * wlExternalApiUnlock()
 *
 * Releases the external API lock.
 *
 * Calling this function without a previous call to wlExternalApiLock() will
 * fail.
 *
 * Returns 0 upon success; otherwise returns -1.
 */
int wlExternalApiUnlock(void);

/*
 * wlExternalApiDestroyLock()
 *
 * Releases and frees the the external API lock resources. This call should only
 * be called as part of the global teardown.
 */
void wlExternalApiDestroyLock(void);

/*
 * WlThread structure
 *
 * Keeps all thread-specific data required by the Wayland external platform
 * implementation to manage resources relevant to multi-threaded environments.
 */
typedef struct WlThreadRec {
    struct wl_event_queue *queue;
} WlThread;


/*
 * wlEglGetThread()
 *
 * Returns the current thread's WlThread storage. If it doesn't exist yet, it
 * creates it. Callers don't need to worry about destroying the returned storage
 * data since proper global destructors are set up.
 *
 * Returns a pointer to the thread's WlThread storage upon success; otherwise,
 * returns NULL.
 */
WlThread* wlGetThread(void);

#endif
