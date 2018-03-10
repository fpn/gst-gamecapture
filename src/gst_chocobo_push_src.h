/* GStreamer
* Copyright (C) 2018 Jake Loo <jake@bebo.com>
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Library General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.
*
* You should have received a copy of the GNU Library General Public
* License along with this library; if not, write to the
* Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA 02111-1307, USA.
*/
#ifndef GST_CHOCOBO_VIDEO_SRC_H_
#define GST_CHOCOBO_VIDEO_SRC_H_

#include <gst/gst.h>
#include <gst/base/gstpushsrc.h>

#include <gst/gl/gl.h>

#include <gst/video/gstvideometa.h>
#include <gst/video/video.h>

#include "shared_resource.h"

G_BEGIN_DECLS

#define GST_TYPE_CHOCOBO                     (gst_chocobopushsrc_get_type())
#define GST_CHOCOBO(obj)                     (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_CHOCOBO,GstChocoboPushSrc))
#define GST_CHOCOBO_CLASS(klass)             (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_CHOCOBO,GstChocoboPushSrcClass))
#define GST_CHOCOBO_GET_CLASS(obj)           (GST_CHOCOBO_CLASS(G_OBJECT_GET_CLASS(obj)))
#define GST_IS_CHOCOBO(obj)                  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_CHOCOBO))
#define GST_IS_CHOCOBO_CLASS(klass)          (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_CHOCOBO))

typedef struct _GstChocoboPushSrc GstChocoboPushSrc;
typedef struct _GstChocoboPushSrcClass GstChocoboPushSrcClass;

struct _GstChocoboPushSrc
{
    GstPushSrc         src;

    SharedResource     *shared_resource;
    GstCaps            *supported_caps;

    GstVideoInfo out_info;
    GstGLFramebuffer *fbo;
    GstGLMemory *out_tex;
    GstGLShader *shader;
    GstBufferPool *pool;
    GstBuffer *current_buffer;
    GstGLDisplay *display;
    GstGLContext *context, *other_context;
    gint64 timestamp_offset;              /* base offset */
    GstClockTime running_time;            /* total running time */
    gint64 n_frames;                      /* total frames sent */
    gboolean negotiated;

    /* properties */
    /*HANDLE*/ void* shtex_handle;

};

struct _GstChocoboPushSrcClass
{
    GstPushSrcClass parent_class;
};

GType    gst_chocobopushsrc_get_type(void);

G_END_DECLS


#endif /* GST_CHOCOBO_VIDEO_SRC_H_ */
