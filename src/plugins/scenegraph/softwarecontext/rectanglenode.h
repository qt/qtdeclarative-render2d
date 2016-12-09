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

#ifndef RECTANGLENODE_H
#define RECTANGLENODE_H

#define QT_NO_OPENGL_ES_3
#undef QT_OPENGL_ES_3

#include <private/qsgadaptationlayer_p.h>

#include <QPen>
#include <QBrush>
#include <QPixmap>

QT_BEGIN_NAMESPACE

class RectangleNode : public QSGRectangleNode
{
public:
    RectangleNode();

    virtual void setRect(const QRectF &rect);
    virtual void setColor(const QColor &color);
    virtual void setPenColor(const QColor &color);
    virtual void setPenWidth(qreal width);
    virtual void setGradientStops(const QGradientStops &stops);
    virtual void setRadius(qreal radius);
    virtual void setAntialiasing(bool antialiasing) { Q_UNUSED(antialiasing) }
    virtual void setAligned(bool aligned);

    virtual void update();

    void paint(QPainter *);

    bool isOpaque() const;
    QRectF rect() const;
private:
    void paintRectangle(QPainter *painter, const QRect &rect);
    void generateCornerPixmap();

    QRect m_rect;
    QColor m_color;
    QColor m_penColor;
    double m_penWidth;
    QGradientStops m_stops;
    double m_radius;
    QPen m_pen;
    QBrush m_brush;

    bool m_cornerPixmapIsDirty;
    QPixmap m_cornerPixmap;

    int m_devicePixelRatio;
};

QT_END_NAMESPACE

#endif // RECTANGLENODE_H
