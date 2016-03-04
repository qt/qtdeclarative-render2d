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

#ifndef GLYPHNODE_H
#define GLYPHNODE_H

#define QT_NO_OPENGL_ES_3
#undef QT_OPENGL_ES_3

#include <private/qsgadaptationlayer_p.h>

QT_BEGIN_NAMESPACE

class GlyphNode : public QSGGlyphNode
{
public:
    GlyphNode();

    virtual void setGlyphs(const QPointF &position, const QGlyphRun &glyphs);
    virtual void setColor(const QColor &color);
    virtual void setStyle(QQuickText::TextStyle style);
    virtual void setStyleColor(const QColor &color);
    virtual QPointF baseLine() const;
    virtual void setPreferredAntialiasingMode(AntialiasingMode);
    virtual void update();

    void paint(QPainter *painter);

private:
    QPointF m_position;
    QGlyphRun m_glyphRun;
    QColor m_color;
    QSGGeometry m_geometry;
    QQuickText::TextStyle m_style;
    QColor m_styleColor;
};

QT_END_NAMESPACE

#endif // GLYPHNODE_H
