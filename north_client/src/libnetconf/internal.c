/**
 * \file internal.c
 * \author Radek Krejci <rkrejci@cesnet.cz>
 * \brief Implementation of internal libnetconf's functions.
 *
 * Copyright (c) 2012-2014 CESNET, z.s.p.o.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this
 * product may be distributed under the terms of the GNU General Public
 * License (GPL) version 2 or later, in which case the provisions
 * of the GPL apply INSTEAD OF those given above.
 *
 * This software is provided ``as is, and any express or implied
 * warranties, including, but not limited to, the implied warranties of
 * merchantability and fitness for a particular purpose are disclaimed.
 * In no event shall the company or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 *
 */

#define _BSD_SOURCE
#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>

#include <libxslt/xslt.h>
#include <libxml/parser.h>

#include "netconf_internal.h"
#include "nacm.h"

static const char rcsid[] __attribute__((used)) ="$Id: "__FILE__": "RCSID" $";

char* nc_clrwspace (const char* in)
{
	int i, j = 0, len = strlen(in);
	char* retval = strdup(in);
	if (retval == NULL) {
		nc_verb_error("Memory allocation failed (%s:%d).", __FILE__, __LINE__);
		return (NULL);
	}

	if (isspace(retval[0])) {
		/* remove leading whitespace characters */
		for (i = 0, j = 0; i < len ; i++, j++) {
			while (retval[i] != '\0' && isspace(retval[i])) {
				i++;
			}
			retval[j] = retval[i];
		}
	}

	/* remove trailing whitespace characters */
	while (j >= 0 && isspace(retval[j])) {
		retval[j] = '\0';
		j--;
	}

	return (retval);
}

void nc_clip_occurences_with(char *str, char sought, char replacement)
{
	int adjacent = 0;
	int clipped = 0;

	if (str == NULL) {
		return;
	}

	while (*str != '\0') {
		if (*str != sought) {
			if (clipped != 0) {
				/* Hurl together. */
				*(str - clipped) = *str;
			}
			adjacent = 0;
		} else if (adjacent == 0) {
			/*
			 * Found first character from a possible sequence of
			 * characters. The whole sequence is going to be
			 * replaced by only one replacement character.
			 */
			*(str - clipped) = replacement;
			/* Next occurrence will be adjacent. */
			adjacent = 1;
		} else {
			++clipped;
		}

		/* Next character. */
		++str;
	}

	if (clipped != 0) {
		/* New string end. */
		*(str - clipped) = '\0';
	}
}

char** nc_get_grouplist(const char* username)
{
	struct passwd* p;
	struct group* g;
	int i, j, k;
	gid_t *glist;
	char** retval = NULL;

	/* get system groups for the username */
	if (username != NULL && (p = getpwnam(username)) != NULL) {
		i = 0;
		/* this call end with -1, but sets i to contain count of groups */
		getgrouplist(username, p->pw_gid, NULL, &i);
		if (i != 0) {
			glist = malloc(i * sizeof (gid_t));
			retval = malloc((i+1) * sizeof(char*));
			if (glist == NULL || retval == NULL) {
				nc_verb_error("Memory reallocation failed (%s:%d - %s).", __FILE__, __LINE__, strerror(errno));
				free(retval);
				free(glist);
				return NULL;
			}

			if (getgrouplist(username, p->pw_gid, glist, &i) != -1) {
				for (j = 0, k = 0; j < i; j++) {
					g = getgrgid(glist[j]);
					if (g && g->gr_name) {
						retval[k++] = strdup(g->gr_name);
					}
				}
				retval[k] = NULL; /* list termination */
			} else {
				nc_verb_warning("%s: unable to get list of groups (getgrouplist() failed)", __func__);
			}
			free(glist);
		}
	}

	return (retval);
}

time_t nc_datetime2time(const char* datetime)
{
	struct tm time;
	char* dt;
	int i;
	long int shift, shift_m;
	time_t retval;

	if (datetime == NULL) {
		return (-1);
	} else {
		dt = strdup(datetime);
	}

	if (strlen(dt) < 20 || dt[4] != '-' || dt[7] != '-' || dt[13] != ':' || dt[16] != ':') {
		nc_verb_error("Wrong date time format not compliant to RFC 3339.");
		free(dt);
		return (-1);
	}

	memset(&time, 0, sizeof(struct tm));
	time.tm_year = atoi(&dt[0]) - 1900;
	time.tm_mon = atoi(&dt[5]) - 1;
	time.tm_mday = atoi(&dt[8]);
	time.tm_hour = atoi(&dt[11]);
	time.tm_min = atoi(&dt[14]);
	time.tm_sec = atoi(&dt[17]);

	retval = timegm(&time);

	/* apply offset */
	i = 19;
	if (dt[i] == '.') { /* we have fractions to skip */
		for (i++; isdigit(dt[i]); i++);
	}
	if (dt[i] == 'Z' || dt[i] == 'z') {
		/* zero shift */
		shift = 0;
	} else if (dt[i+3] != ':') {
		/* wrong format */
		nc_verb_error("Wrong date time shift format not compliant to RFC 3339.");
		free(dt);
		return (-1);
	} else {
		shift = strtol(&dt[i], NULL, 10);
		shift = shift * 60 * 60; /* convert from hours to seconds */
		shift_m = strtol(&dt[i+4], NULL, 10) * 60; /* includes conversion from minutes to seconds */
		/* correct sign */
		if (shift < 0) {
			shift_m *= -1;
		}
		/* connect hours and minutes of the shift */
		shift = shift + shift_m;
	}
	/* we have to shift to the opposite way to correct the time */
	retval -= shift;

	free(dt);
	return (retval);
}

char* nc_time2datetime(time_t time, const char* tz)
{
	char* date = NULL;
	char* zoneshift = NULL;
	int zonediff, zonediff_h, zonediff_m;
	struct tm tm, *tm_ret;
	char *tz_origin;

	if (tz) {
		tz_origin = getenv("TZ");
		setenv("TZ", tz, 1);
		tm_ret = localtime_r(&time, &tm);
		setenv("TZ", tz_origin, 1);

		if (tm_ret == NULL) {
			return (NULL);
		}
	} else {
		if (gmtime_r(&time, &tm) == NULL) {
			return (NULL);
		}
	}

	if (tm.tm_isdst < 0) {
		zoneshift = NULL;
	} else {
		if (tm.tm_gmtoff == 0) {
			/* time is Zulu (UTC) */
			if (asprintf(&zoneshift, "Z") == -1) {
				nc_verb_error("asprintf() failed (%s:%d).", __FILE__, __LINE__);
				return (NULL);
			}
		} else {
			zonediff = tm.tm_gmtoff;
			zonediff_h = zonediff / 60 / 60;
			zonediff_m = zonediff / 60 % 60;
			if (asprintf(&zoneshift, "%s%02d:%02d",
			                (zonediff < 0) ? "-" : "+",
			                zonediff_h,
			                zonediff_m) == -1) {
				nc_verb_error("asprintf() failed (%s:%d).", __FILE__, __LINE__);
				return (NULL);
			}
		}
	}
	if (asprintf(&date, "%04d-%02d-%02dT%02d:%02d:%02d%s",
			tm.tm_year + 1900,
			tm.tm_mon + 1,
			tm.tm_mday,
			tm.tm_hour,
			tm.tm_min,
			tm.tm_sec,
	                (zoneshift == NULL) ? "" : zoneshift) == -1) {
		free(zoneshift);
		nc_verb_error("asprintf() failed (%s:%d).", __FILE__, __LINE__);
		return (NULL);
	}
	free (zoneshift);

	return (date);
}
