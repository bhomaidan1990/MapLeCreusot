#ifndef RENDERITEM_H
#define RENDERITEM_H

#include <QGraphicsPolygonItem>
#include <QGraphicsPathItem>
#include <QGraphicsLayoutItem>
#include <QPen>
#include <QPainter>
#include <vector>
#include <string>
#include "modelDataHandler.h"
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

//================================ use color reference from P0267_RefImpl
static QColor getPolygonColor(polygonType type)
{
    switch (type) {
    case building:
        return QColor(255, 190, 190);
    case water:
        return QColor(0, 201, 215);
    case grass:
        return QColor(197, 236, 148);
    case forest:
        return QColor(46, 139, 87);
    case industrial:
        return QColor(223, 197, 220);
    case leisure:
        return QColor(189, 252, 193);
    case railway:
        return QColor(193, 193, 193);
    case commercial:
        return QColor(233, 195, 196);
    case residential:
        return QColor(209, 209, 209);
    default:
        return QColor(100, 100, 100);

    }
}

static QColor getPathColor(roadType type)
{
    switch(type) {
        case Motorway:      return QColor{226, 122, 143};
        case Trunk:         return QColor{245, 161, 136};
        case Primary:       return QColor{249, 207, 144};
        case Secondary:     return QColor{244, 251, 173};
        case Tertiary:      return QColor{244, 251, 173};
        case Residential:   return QColor{254, 254, 254};
        case Service:       return QColor{254, 254, 254};
        case Footway:       return QColor{241, 106, 96};
        case Unclassified:  return QColor{254, 254, 254};
        default:            return QColor(190, 190, 190);
    }
}

static float getPathWidth(roadType type)
{
    switch( type ) {
        case Motorway:      return 6.f;
        case Trunk:         return 6.f;
        case Primary:       return 5.f;
        case Secondary:     return 5.f;
        case Tertiary:      return 4.f;
        case Residential:   return 2.5f;
        case Unclassified:  return 2.5f;
        case Service:       return 1.f;
        case Footway:       return 0.f;
        default:            return 1.f;
    }
}

//io2d::brush m_BackgroundFillBrush{ io2d::rgba_color{238, 235, 227} };

//    io2d::brush m_BuildingFillBrush{ io2d::rgba_color{208, 197, 190} };
//    io2d::brush m_BuildingOutlineBrush{ io2d::rgba_color{181, 167, 154} };
//    io2d::stroke_props m_BuildingOutlineStrokeProps{1.f};

//    io2d::brush m_LeisureFillBrush{ io2d::rgba_color{189, 252, 193} };
//    io2d::brush m_LeisureOutlineBrush{ io2d::rgba_color{160, 248, 162} };
//    io2d::stroke_props m_LeisureOutlineStrokeProps{1.f};

//    io2d::brush m_WaterFillBrush{ io2d::rgba_color{155, 201, 215} };

//    io2d::brush m_RailwayStrokeBrush{ io2d::rgba_color{93,93,93} };
//    io2d::brush m_RailwayDashBrush{ io2d::rgba_color::white };
//    io2d::dashes m_RailwayDashes{0.f, {3.f, 3.f}};
//    float m_RailwayOuterWidth = 3.f;
//    float m_RailwayInnerWidth = 2.f;

//    struct RoadRep {
//        io2d::brush brush{io2d::rgba_color::black};
//        io2d::dashes dashes{};
//        float metric_width = 1.f;
//    };
//=================================================================================================


// test for drawing multipolygon in relations
class Multipolygon : public QGraphicsPolygonItem
{

    polygonType m_PolygonType;    //this will determin the z-value
    QColor m_brushColor;
    idType m_wayId;

public:
    Multipolygon(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override
    {
        painter->setBrush(m_brushColor);
        painter->drawPolygon(this->polygon());
    }
    void setPolyType(polygonType type)
    {

        m_PolygonType = type;
        m_brushColor = getPolygonColor(m_PolygonType);

//        setZValue(m_PolygonType);
    }
    void setId(idType id)
    {
        m_wayId = id;
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
//        this->setSelected(true);
        if(event->button() == Qt::RightButton)
            std::cout << "selected item id: " << m_wayId << std::endl;
        else
            QGraphicsItem::mousePressEvent(event);

    }

};

class Road : public QGraphicsPolygonItem
{
    roadType m_rtype;
    QColor m_RoadStyle;
    idType m_wayId;
    QPen m_pen;

public:
    Road(){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
    QWidget *widget) override
    {
        painter->setPen(m_pen);
        painter->drawPolyline(this->polygon());
    }
    void setId(idType id)
    {
        m_wayId = id;
    }

    void setPenStyle(roadType rType)
    {
        m_pen.setBrush(getPathColor(rType));
        m_pen.setWidth(getPathWidth(rType)+3.0);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
//        this->setSelected(true);
        if(event->button() == Qt::RightButton)
            std::cout << "selected item id: " << m_wayId << std::endl;
        else
            QGraphicsItem::mousePressEvent(event);

    }
};


#endif // RENDERITEM_H