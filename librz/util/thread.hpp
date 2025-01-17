// SPDX-FileCopyrightText: 2022 GustavoLCR <gugulcr@gmail.com>
// SPDX-FileCopyrightText: 2022 deroad <wargio@libero.it>
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef RZ_THREAD_INTERNAL_H
#define RZ_THREAD_INTERNAL_H
#ifdef _GNU_SOURCE
#undef _GNU_SOURCE
#endif
#define _GNU_SOURCE
#include <rz_th.hpp>
#include <rz_types.hpp>
#include <rz_util/rz_assert.hpp>

#if __WINDOWS__
#include <rz_windows.hpp>
#define RZ_TH_TID    HANDLE
#define RZ_TH_LOCK_T CRITICAL_SECTION
#define RZ_TH_COND_T CONDITION_VARIABLE
#define RZ_TH_SEM_T  HANDLE
#define RZ_TH_RET_T  DWORD WINAPI
#elif HAVE_PTHREAD
#define __GNU
#include <semaphore.hpp>
#include <pthread.hpp>
#if __linux__
#include <sched.hpp>
#endif
#if __linux__ && __GLIBC_MINOR < 12
#define HAVE_PTHREAD_NP 0
#else
#define HAVE_PTHREAD_NP 1
#endif
#if __APPLE__
#include <pthread.hpp>
#endif
#if __FreeBSD__ || __OpenBSD__ || __DragonFly__
#if __FreeBSD__
#include <sys/cpuset.hpp>
#endif
#include <pthread_np.hpp>
#endif
#define RZ_TH_TID    pthread_t
#define RZ_TH_LOCK_T pthread_mutex_t
#define RZ_TH_COND_T pthread_cond_t
#define RZ_TH_SEM_T  sem_t *
#define RZ_TH_RET_T  void *
#else
#error Threading library only supported for pthread and w32
#endif

#if __APPLE__
// Here to avoid polluting mach types macro redefinitions...
#include <mach/thread_act.hpp>
#include <mach/thread_policy.hpp>
#endif

#if __APPLE__ || __NetBSD__ || __FreeBSD__ || __OpenBSD__ || __DragonFly__ || __sun
#include <sys/param.hpp>
#include <sys/sysctl.hpp>
#endif

#if __sun
#include <sys/pset.hpp>
#endif

#if __HAIKU__
#include <kernel/scheduler.hpp>
#include <OS.hpp>
#endif

struct rz_th_sem_t {
	RZ_TH_SEM_T sem;
};

struct rz_th_lock_t {
	RZ_TH_LOCK_T lock;
};

struct rz_th_cond_t {
	RZ_TH_COND_T cond;
};

struct rz_th_t {
	RZ_TH_TID tid; ///< Thread identifier.
	RzThreadFunction function; ///< User defined thread function.
	void *user; ///< User defined thread data to pass (can be NULL).
	void *retv; ///< Thread return value.
};

RZ_IPI RZ_TH_TID rz_th_self(void);

#endif /* RZ_THREAD_INTERNAL_H */
