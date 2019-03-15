/*
 * Copyright 2012 Martin Gräßlin <mgraesslin@kde.org>
 * Copyright 2003-2005 Sandro Giessl <sandro@giessl.com>
 * Copyright 2008 Gustavo Pichorim Boiko <boiko@mandriva.com>
 * Copyright 2008-2009 Rodrigo Gonçalves de Oliveira <rodrigo@mandriva.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#include "therobbutton.h"
#include "therobcolors.h"
#include <QPainter>




TheRobButtonProvider::TheRobButtonProvider()
    : QQuickImageProvider(Pixmap)
{
}

QPixmap TheRobButtonProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int origSize = requestedSize.isValid() ? qMin(requestedSize.width(), requestedSize.height()) : 10;
    if (size) {
        *size = QSize(origSize, origSize);
    }
    QStringList idParts = id.split(QStringLiteral("/"));
    if (idParts.isEmpty()) {
        // incorrect id
        return QQuickImageProvider::requestPixmap(id, size, requestedSize);
    }
    bool active = false;
    bool toggled = false;
    bool hovered = false;
    QColor titleBarColor;
    if (idParts.length() > 1 && idParts.at(1) == QStringLiteral("true")) {
        active = true;
    }
    if (idParts.length() > 2 && idParts.at(2) == QStringLiteral("true")) {
        toggled = true;
    }
    if (idParts.length() > 3 && idParts.at(3) == QStringLiteral("true")) {
        hovered = true;
    }
    if (idParts.length() > 4) {
      titleBarColor.setNamedColor(idParts.at(4));
    }
    ButtonIcon button;
    switch (static_cast<DecorationButton>(idParts[0].toInt())) {
    case DecorationButtonClose:
        button = CloseIcon;
        break;
    case DecorationButtonMaximizeRestore:
        if (toggled) {
            button = MaxRestoreIcon;
        } else {
            button = MaxIcon;
        }
        break;
    case DecorationButtonMinimize:
        button = MinIcon;
        break;
    case DecorationButtonQuickHelp:
        button = HelpIcon;
        break;
    default:
        // not recognized icon
        return QQuickImageProvider::requestPixmap(id, size, requestedSize);
    }

    QPixmap pix = icon(button, origSize, active, titleBarColor);
    if (hovered) {
        QPainter p;
        QPixmap temp(pix.size());
        
        temp.fill(Qt::transparent);
        p.begin(&temp);
        
        QRect r(pix.rect());
        p.drawPixmap(r, pix);
        
        p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        
        QColor color;
        color.setAlpha(0.7 * 255);
        p.fillRect(pix.rect(), color);
        
        p.end();
        pix = temp;
    }
    return pix;
}




QPixmap TheRobButtonProvider::icon(ButtonIcon icon, int size, bool active, QColor titleBarColor)
{
    Q_UNUSED(active);
    if (size%2 == 0)
        --size;

    QPixmap image(size, size);
    image.fill(Qt::transparent);
    QPainter p(&image );
    p.setRenderHint(QPainter::Antialiasing, true);
    QRect r = image.rect();
    int margin = 2;
    r.adjust(margin,margin,-margin,-margin);
    float top = r.top(), bottom = r.bottom(), left = r.left(), right = r.right(), centerY = r.center().y();
    float width = r.width(), height = r.height();
    
    const ColorData *data = TheRobColors::colorData(titleBarColor);
    QLinearGradient g(r.left(), r.top(), r.left(),  r.top());
    g.setColorAt(0., data->gray[3]);
    g.setColorAt(0.3, data->gray[3]);
    g.setColorAt(0.7, data->gray[3]);
    g.setColorAt(1., data->gray[3]);
    QBrush b(g);
    QPen pen(b, 2);
    pen.setCapStyle(Qt::RoundCap);
    p.setPen(pen);
    float s = height;

    switch(icon) {
        
        case CloseIcon:
        {
            p.setBrush(Qt::NoBrush);
            p.drawEllipse((s-(s*0.2))/2,(s-(s*0.2))/2,s*0.2,s*0.2); 
            p.setRenderHint( QPainter::Antialiasing );

            p.setPen(QPen(b, 1));
            p.drawEllipse((s-(s*0.8))/2,(s-(s*0.8))/2,s*0.8,s*0.8);


            break;
        }

        case MaxIcon:
        {
            p.setRenderHint( QPainter::Antialiasing );
            p.setBrush(Qt::NoBrush);
            p.drawEllipse((s-(s*0.2))/2,(s-(s*0.2))/2,s*0.2,s*0.2);               
            p.setPen(QPen(b, 1));

            int startAngle = 0 * 16;
            int spanAngle = 180 * 16;
            p.drawArc((s-(s*0.8))/2,(s-(s*0.8))/2,s*0.8,s*0.8, startAngle, spanAngle);
            
            //p.drawEllipse(&center,s*0.2,s*0.2);

            
            break;
        }

        case MaxRestoreIcon:
        {

            p.setBrush(Qt::NoBrush);
            p.drawEllipse((s-(s*0.2))/2,(s-(s*0.2))/2,s*0.2,s*0.2);          
            p.setPen(QPen(b, 1));
            int startAngle = 0 * 16;
            int spanAngle = 180 * 16;
            p.drawArc((s-(s*0.8))/2,(s-(s*0.8))/2,s*0.8,s*0.8, startAngle, spanAngle);
            pen.setWidth(4);
            p.setPen(pen);
            p.drawEllipse((s-(s*0.2))/2,(s-(s*0.2))/2,s*0.2,s*0.2);        
            
            break;
        }

        case MinIcon:
        {
            p.setBrush(Qt::NoBrush);
            p.drawEllipse((s-(s*0.2))/2,(s-(s*0.2))/2,s*0.2,s*0.2);               
            p.setPen(QPen(b, 1));

            int startAngle = 180 * 16;
            int spanAngle = 180 * 16;
            p.drawArc((s-(s*0.8))/2,(s-(s*0.8))/2,s*0.8,s*0.8, startAngle, spanAngle);            
            break;
        }

        case HelpIcon:
        {
          QFont f = p.font();
          f.setPixelSize(r.height());
          //f.setStyleStrategy(QFont::NoAntialias);
          f.setBold(true);
          p.setFont(f);
          p.drawText(r, Qt::AlignCenter, "?");
          
          break;
        }

        default:
          break;
    }

    p.end();
    
    return image;
}
