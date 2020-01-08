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

#include "playersinkbinpmtinfo.h"

enum
{
	PLAYERSINK_0,
	PLAYERSINK_PGM_NO,
	PLAYERSINK_VER_NO,
	PLAYERSINK_PCR_PID,
	PLAYERSINK_STREAM_INFO
};

#define parent_class playersinkbin_pmt_info_parent_class
G_DEFINE_TYPE (PlayerSinkbinPmtInfo, playersinkbin_pmt_info, G_TYPE_OBJECT);

static void playersinkbin_pmt_info_finalize (GObject *object);
static void playersinkbin_pmt_info_set_property (GObject * object, guint propid,
        const GValue * val, GParamSpec * pspec);
static void playersinkbin_pmt_info_get_property (GObject * object, guint propid,
        GValue * val, GParamSpec * pspec);

static void
playersinkbin_pmt_info_class_init (PlayerSinkbinPmtInfoClass *klass)
{
	GObjectClass *pmtobject_klass;
	pmtobject_klass = (GObjectClass *) klass;

	pmtobject_klass->finalize = playersinkbin_pmt_info_finalize;
	pmtobject_klass->set_property = playersinkbin_pmt_info_set_property;
	pmtobject_klass->get_property = playersinkbin_pmt_info_get_property;

	g_object_class_install_property (pmtobject_klass, PLAYERSINK_PCR_PID,
	                                 g_param_spec_uint ("pcr-pid", "Pid showing the pcr",
	                                         "Pid containing pcr value of program", 1, G_MAXUINT16, 1, G_PARAM_READABLE));
	g_object_class_install_property (pmtobject_klass, PLAYERSINK_VER_NO,
	                                 g_param_spec_uint ("version-number","Property showing version number",
	                                         "program info version number", 0, G_MAXUINT8, 1, G_PARAM_READABLE));
	g_object_class_install_property (pmtobject_klass, PLAYERSINK_PGM_NO,
	                                 g_param_spec_uint ("program-number", "Identifier of program",
	                                         "Identifying number of particular program", 0, G_MAXUINT16, 1, G_PARAM_READABLE));

	g_object_class_install_property (pmtobject_klass, PLAYERSINK_STREAM_INFO,
	                                 g_param_spec_value_array ("stream-info", "stream information",
	                                         "Information of available program streams", 
	                                         g_param_spec_object ("fluendopmt-streaminfo", "stream info",
	                                                 "Object containing fluendo pmt stream info",
	                                                 PLAYERSINKBIN_TYPE_PMT_STREAM_INFO, G_PARAM_READABLE),G_PARAM_READABLE));

}

static void
playersinkbin_pmt_info_init (PlayerSinkbinPmtInfo *pmtinfo)
{
	pmtinfo->streams = g_value_array_new (0);
}

PlayerSinkbinPmtInfo *playersinkbin_pmt_info_new (guint16 pgm_no, guint16 pcr_pid,
                                  guint8 ver_no)
{
	PlayerSinkbinPmtInfo *pmtInfo;
	pmtInfo = g_object_new (PLAYERSINKBIN_TYPE_PMT_INFO, NULL);
	pmtInfo->program_no = pgm_no;
	pmtInfo->pcr_pid = pcr_pid;
	pmtInfo->version_no = ver_no;
	return pmtInfo;
}

static void
playersinkbin_pmt_info_finalize (GObject *object)
{
	PlayerSinkbinPmtInfo *pmtInfo = PLAYERSINKBIN_PMT_INFO (object);

	g_value_array_free (pmtInfo->streams);

	G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void playersinkbin_pmt_info_set_property (GObject * object, guint propid,
        const GValue * val, GParamSpec * pspec)
{
	g_return_if_fail (PLAYERSINKBIN_IS_PMT_INFO (object));
	PlayerSinkbinPmtInfo *pmtInfo = PLAYERSINKBIN_PMT_INFO (object);
	
	switch(propid) {
	/*Cannot set prop*/
	default:
	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, propid, pspec);
	}
}

static void playersinkbin_pmt_info_get_property (GObject * object, guint propid,
        GValue * val, GParamSpec * pspec)
{
	PlayerSinkbinPmtInfo *info;
	info = PLAYERSINKBIN_PMT_INFO (object);

	switch (propid) {
	case PLAYERSINK_PGM_NO:
		g_value_set_uint (val, info->program_no);
		break;
	case PLAYERSINK_VER_NO:
		g_value_set_uint (val, info->version_no);
		break;
	case PLAYERSINK_PCR_PID:
		g_value_set_uint (val, info->pcr_pid);
		break;
	case PLAYERSINK_STREAM_INFO:
		g_value_set_boxed (val, info->streams);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, propid, pspec);
		break;
	}
}

void
playersinkbin_pmt_info_add_stream (PlayerSinkbinPmtInfo *pmt_info, PlayerSinkbinPmtStreamInfo *stream)
{
	GValue value = { 0, };
	g_return_if_fail (PLAYERSINKBIN_IS_PMT_INFO (pmt_info));
	g_return_if_fail (PLAYERSINKBIN_IS_PMT_STREAM_INFO (stream));
	g_value_init (&value, G_TYPE_OBJECT);
	g_value_take_object (&value, stream);
	g_value_array_append (pmt_info->streams, &value);
}

