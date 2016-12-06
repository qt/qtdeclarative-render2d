/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of Qt Quick 2d Renderer of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
** $QT_END_LICENSE$
**
****************************************************************************/
#include "context.h"

#include "rectanglenode.h"
#include "imagenode.h"
#include "painternode.h"
#include "pixmaptexture.h"
#include "glyphnode.h"
#include "ninepatchnode.h"
#include "softwarelayer.h"
#include "renderer.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>

#include <QtGui/QWindow>

#include <QtQuick/QSGFlatColorMaterial>
#include <QtQuick/QSGVertexColorMaterial>
#include <QtQuick/QSGOpaqueTextureMaterial>
#include <QtQuick/QSGTextureMaterial>
#include <private/qsgdefaultimagenode_p.h>
#include <private/qsgdefaultrectanglenode_p.h>
#include <private/qsgdistancefieldglyphnode_p_p.h>
#include <private/qsgdefaultglyphnode_p.h>

#ifndef QSG_NO_RENDERER_TIMING
static bool qsg_render_timing = !qgetenv("QSG_RENDER_TIMING").isEmpty();
#endif

// Used for very high-level info about the renderering and gl context
// Includes GL_VERSION, type of render loop, atlas size, etc.
Q_LOGGING_CATEGORY(QSG_RASTER_LOG_INFO,                "qt.scenegraph.info")

// Used to debug the renderloop logic. Primarily useful for platform integrators
// and when investigating the render loop logic.
Q_LOGGING_CATEGORY(QSG_RASTER_LOG_RENDERLOOP,          "qt.scenegraph.renderloop")

// GLSL shader compilation
Q_LOGGING_CATEGORY(QSG_RASTER_LOG_TIME_COMPILATION,    "qt.scenegraph.time.compilation")

// polish, animations, sync, render and swap in the render loop
Q_LOGGING_CATEGORY(QSG_RASTER_LOG_TIME_RENDERLOOP,     "qt.scenegraph.time.renderloop")

// Texture uploads and swizzling
Q_LOGGING_CATEGORY(QSG_RASTER_LOG_TIME_TEXTURE,        "qt.scenegraph.time.texture")

// Glyph preparation (only for distance fields atm)
Q_LOGGING_CATEGORY(QSG_RASTER_LOG_TIME_GLYPH,          "qt.scenegraph.time.glyph")

// Timing inside the renderer base class
Q_LOGGING_CATEGORY(QSG_RASTER_LOG_TIME_RENDERER,       "qt.scenegraph.time.renderer")

QT_BEGIN_NAMESPACE

namespace SoftwareContext
{

RenderContext::RenderContext(QSGContext *ctx)
    : QSGRenderContext(ctx)
    , currentWindow(0)
    , m_initialized(false)
{
}
Context::Context(QObject *parent)
    : QSGContext(parent)
{
    setDistanceFieldEnabled(false);
}

QSGRectangleNode *Context::createRectangleNode()
{
    return new RectangleNode();
}

QSGImageNode *Context::createImageNode()
{
    return new ImageNode();
}

QSGPainterNode *Context::createPainterNode(QQuickPaintedItem *item)
{
    return new PainterNode(item);
}

QSGGlyphNode *Context::createGlyphNode(QSGRenderContext *rc, bool preferNativeGlyphNode)
{
    Q_UNUSED(rc);
    Q_UNUSED(preferNativeGlyphNode);
    return new GlyphNode();
}

QSGNinePatchNode *Context::createNinePatchNode()
{
    return new NinePatchNode();
}

QSGLayer *Context::createLayer(QSGRenderContext *renderContext)
{
    return new SoftwareLayer(renderContext);
}

QSurfaceFormat Context::defaultSurfaceFormat() const
{
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setRenderableType(QSurfaceFormat::DefaultRenderableType);
    format.setMajorVersion(0);
    format.setMinorVersion(0);
    return format;
}

void RenderContext::initialize(QOpenGLContext *context)
{
    Q_UNUSED(context)
    Q_UNREACHABLE();
}

void RenderContext::initializeIfNeeded()
{
    if (m_initialized)
        return;
    m_initialized = true;
    emit initialized();
}

void RenderContext::invalidate()
{
    QSGRenderContext::invalidate();
}

QSGTexture *RenderContext::createTexture(const QImage &image) const
{
    return new PixmapTexture(image);
}

QSGTexture *RenderContext::createTextureNoAtlas(const QImage &image) const
{
    return new PixmapTexture(image);
}

QSGRenderer *RenderContext::createRenderer()
{
    return new Renderer(this);
}


void RenderContext::renderNextFrame(QSGRenderer *renderer, GLuint fbo)
{
    QSGRenderContext::renderNextFrame(renderer, fbo);
}

} // namespace

QT_END_NAMESPACE
