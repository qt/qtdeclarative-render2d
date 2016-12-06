/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of Qt Quick 2d Renderer module of the Qt Toolkit.
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

#ifndef CONTEXT_H
#define CONTEXT_H

#define QT_NO_OPENGL_ES_3
#undef QT_OPENGL_ES_3

#include <private/qsgcontext_p.h>
#include <private/qsgrenderer_p.h>
#include <private/qsgadaptationlayer_p.h>
#include <QtCore/QElapsedTimer>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QBackingStore>

Q_DECLARE_LOGGING_CATEGORY(QSG_RASTER_LOG_TIME_RENDERLOOP)
Q_DECLARE_LOGGING_CATEGORY(QSG_RASTER_LOG_TIME_COMPILATION)
Q_DECLARE_LOGGING_CATEGORY(QSG_RASTER_LOG_TIME_TEXTURE)
Q_DECLARE_LOGGING_CATEGORY(QSG_RASTER_LOG_TIME_GLYPH)
Q_DECLARE_LOGGING_CATEGORY(QSG_RASTER_LOG_TIME_RENDERER)
Q_DECLARE_LOGGING_CATEGORY(QSG_RASTER_LOG_INFO)
Q_DECLARE_LOGGING_CATEGORY(QSG_RASTER_LOG_RENDERLOOP)

namespace SoftwareContext
{

class Renderer : public QSGRenderer
{
public:
    Renderer(QSGRenderContext *context);

    virtual void renderScene(GLuint fboId = 0);

    virtual void render();

    void nodeChanged(QSGNode *node, QSGNode::DirtyState state);

    QBackingStore *backingStore() const { return m_backingStore.data(); }

private:
    QScopedPointer<QBackingStore> m_backingStore;
    QRect m_dirtyRect;
};

class PixmapRenderer : public QSGRenderer
{
public:
    PixmapRenderer(QSGRenderContext *context);

    virtual void renderScene(GLuint fboId = 0);

    virtual void render();

    void render(QPixmap *target);

    QRect m_projectionRect;
};

class RenderContext : public QSGRenderContext
{
public:
    RenderContext(QSGContext *ctx);
    void initialize(QOpenGLContext *context);
    void initializeIfNeeded();
    void invalidate();
    void renderNextFrame(QSGRenderer *renderer, GLuint fbo);
    QSGTexture *createTexture(const QImage &image) const;
    QSGTexture *createTextureNoAtlas(const QImage &image) const;
    QSGRenderer *createRenderer();

    QWindow *currentWindow;
    bool m_initialized;
};

class Context : public QSGContext
{
    Q_OBJECT
public:
    explicit Context(QObject *parent = 0);

    QSGRenderContext *createRenderContext() { return new RenderContext(this); }

    virtual QSGRectangleNode *createRectangleNode();
    virtual QSGImageNode *createImageNode();
    virtual QSGPainterNode *createPainterNode(QQuickPaintedItem *item);
    virtual QSGGlyphNode *createGlyphNode(QSGRenderContext *rc, bool preferNativeGlyphNode);
    virtual QSGNinePatchNode *createNinePatchNode();
    virtual QSGLayer *createLayer(QSGRenderContext *renderContext);
    virtual QSurfaceFormat defaultSurfaceFormat() const;
};

} // namespace

#endif // CONTEXT_H
