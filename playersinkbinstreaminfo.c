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
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>

#include "playersinkbinstreaminfo.h"

enum
{
	PROP_0,
	PROP_PID
};

#define parent_class playersinkbin_pmt_stream_info_parent_class 
G_DEFINE_TYPE (PlayerSinkbinPmtStreamInfo, playersinkbin_pmt_stream_info, G_TYPE_OBJECT);

static void playersinkbin_pmt_stream_info_set_property (GObject * object, guint prop_id,
        const GValue * value, GParamSpec * spec);
static void playersinkbin_pmt_stream_info_get_property (GObject * object, guint prop_id,
        GValue * value, GParamSpec * spec);

static void
playersinkbin_pmt_stream_info_class_init (PlayerSinkbinPmtStreamInfoClass *klass)
{
	GObjectClass *gobject_klass = (GObjectClass *) klass;

	gobject_klass->set_property = playersinkbin_pmt_stream_info_set_property;
	gobject_klass->get_property = playersinkbin_pmt_stream_info_get_property;

	g_object_class_install_property (gobject_klass, PROP_PID,
	                                 g_param_spec_uint ("pid", "PID carrying this stream",
	                                         "PID which carries this stream", 1, G_MAXUINT16, 1,
	                                         G_PARAM_READABLE));
}

static void
playersinkbin_pmt_stream_info_init (PlayerSinkbinPmtStreamInfo *pmt_stream_info)
{
}

PlayerSinkbinPmtStreamInfo *playersinkbin_pmt_stream_info_new (guint16 pid)
{
	PlayerSinkbinPmtStreamInfo *info;

	info = g_object_new (PLAYERSINKBIN_TYPE_PMT_STREAM_INFO, NULL);

	info->pid = pid;

	return info;
}

static void
playersinkbin_pmt_stream_info_set_property (GObject * object, guint prop_id,
                                    const GValue * value, GParamSpec * spec)
{
	g_return_if_fail (PLAYERSINKBIN_IS_PMT_STREAM_INFO (object));

	/* No settable properties */
	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, spec);
}

static void
playersinkbin_pmt_stream_info_get_property (GObject * object, guint prop_id,
                                    GValue * value, GParamSpec * spec)
{
	PlayerSinkbinPmtStreamInfo *si;

	g_return_if_fail (PLAYERSINKBIN_IS_PMT_STREAM_INFO (object));

	si = PLAYERSINKBIN_PMT_STREAM_INFO (object);

	switch (prop_id) {
	case PROP_PID:
		g_value_set_uint (value, si->pid);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, spec);
		break;
	}
}
