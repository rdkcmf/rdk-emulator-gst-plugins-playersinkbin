/*
 * Copyright 2014 RDK Management
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation, version 2
 * of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
#ifndef __PLAYERSINKBIN_PMT_INFO_H__
#define __PLAYERSINKBIN_PMT_INFO_H__

#include <glib.h>
#include "playersinkbinstreaminfo.h"

G_BEGIN_DECLS

typedef struct PlayerSinkbinPmtInfoClass {
	GObjectClass parent_class;
} PlayerSinkbinPmtInfoClass;

typedef struct PlayerSinkbinPmtInfo {
	GObject parent;

	guint16 program_no;
	guint16 pcr_pid;

	guint8 version_no;

	GValueArray *descriptors;
	GValueArray *streams;
} PlayerSinkbinPmtInfo;

PlayerSinkbinPmtInfo *playersinkbin_pmt_info_new (guint16 program_no, guint16 pcr_pid, guint8 version);
void playersinkbin_pmt_info_add_stream (PlayerSinkbinPmtInfo *pmt_info, PlayerSinkbinPmtStreamInfo *stream);
void playersinkbin_pmt_info_add_descriptor (PlayerSinkbinPmtInfo *pmt_info,
                                    const gchar *descriptor, guint length);

GType playersinkbin_pmt_info_get_type (void);

#define PLAYERSINKBIN_TYPE_PMT_INFO (playersinkbin_pmt_info_get_type ())
#define PLAYERSINKBIN_IS_PMT_INFO(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), PLAYERSINKBIN_TYPE_PMT_INFO))
#define PLAYERSINKBIN_PMT_INFO(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),PLAYERSINKBIN_TYPE_PMT_INFO, PlayerSinkbinPmtInfo))

G_END_DECLS

#endif
