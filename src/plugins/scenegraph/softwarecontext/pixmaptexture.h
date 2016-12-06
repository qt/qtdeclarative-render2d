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

#ifndef PIXMAPTEXTURE_H
#define PIXMAPTEXTURE_H

#define QT_NO_OPENGL_ES_3
#undef QT_OPENGL_ES_3

#include <private/qsgtexture_p.h>

QT_BEGIN_NAMESPACE

class PixmapTexture : public QSGTexture
{
    Q_OBJECT
public:
    PixmapTexture(const QImage &image);
    PixmapTexture(const QPixmap &pixmap);

    virtual int textureId() const;
    virtual QSize textureSize() const;
    virtual bool hasAlphaChannel() const;
    virtual bool hasMipmaps() const;
    virtual void bind();

    const QPixmap &pixmap() const { return m_pixmap; }

private:
    QPixmap m_pixmap;
};

QT_END_NAMESPACE

#endif // PIXMAPTEXTURE_H
