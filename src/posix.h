/*
 * Copyright (C) 2009-2012 the libgit2 contributors
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_posix_h__
#define INCLUDE_posix_h__

#include "common.h"
#include <fcntl.h>
#include <time.h>

#define S_IFGITLINK 0160000
#define S_ISGITLINK(m) (((m) & S_IFMT) == S_IFGITLINK)

#if !defined(O_BINARY)
#define O_BINARY 0
#endif

typedef int git_file;

/**
 * Standard POSIX Methods
 *
 * All the methods starting with the `p_` prefix are
 * direct ports of the standard POSIX methods. 
 *
 * Some of the methods are slightly wrapped to provide
 * saner defaults. Some of these methods are emulated
 * in Windows platforns.
 *
 * Use your manpages to check the docs on these.
 * Straightforward 
 */

extern int p_read(git_file fd, void *buf, size_t cnt);
extern int p_write(git_file fd, const void *buf, size_t cnt);

#define p_fstat(f,b) fstat(f, b)
#define p_lseek(f,n,w) lseek(f, n, w)
#define p_close(fd) close(fd)
#define p_umask(m) umask(m)

extern int p_open(const char *path, int flags, ...);
extern int p_creat(const char *path, mode_t mode);
extern int p_getcwd(char *buffer_out, size_t size);
extern int p_rename(const char *from, const char *to);

#ifndef GIT_WIN32

#define p_stat(p,b) stat(p, b)
#define p_chdir(p) chdir(p)
#define p_rmdir(p) rmdir(p)
#define p_chmod(p,m) chmod(p, m)
#define p_access(p,m) access(p,m)
#define p_recv(s,b,l,f) recv(s,b,l,f)
#define p_send(s,b,l,f) send(s,b,l,f)
typedef int GIT_SOCKET;
#define INVALID_SOCKET -1

#define p_localtime_r localtime_r
#define p_gmtime_r gmtime_r
#define p_gettimeofday gettimeofday

#else

typedef SOCKET GIT_SOCKET;
struct timezone;
extern struct tm * p_localtime_r (const time_t *timer, struct tm *result);
extern struct tm * p_gmtime_r (const time_t *timer, struct tm *result);
extern int p_gettimeofday(struct timeval *tv, struct timezone *tz);


#endif

/**
 * Platform-dependent methods
 */
#ifdef GIT_WIN32
#	include "win32/posix.h"
#else
#	include "unix/posix.h"
#endif

#define p_readdir_r(d,e,r) readdir_r(d,e,r)

#endif
