/*
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
#ifndef THEROB_COLORS_H
#define THEROB_COLORS_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QHash>
  
typedef struct {
  QColor gray[7];
  QColor color[5];
  QColor black;
  QColor white;
} ColorData;
  
class TheRobColors : public QObject
{
  Q_OBJECT

private:
  static QHash<QString, ColorData *> m_data;
  static QString m_currentHash;
  void readConfig(QColor titleBarColor);
  
public:
  Q_INVOKABLE QColor color1(QColor titleBarColor);
  Q_INVOKABLE QColor color2(QColor titleBarColor);
  Q_INVOKABLE QColor color3(QColor titleBarColor);
  Q_INVOKABLE QColor color4(QColor titleBarColor);
  Q_INVOKABLE QColor black(QColor titleBarColor);
  Q_INVOKABLE QColor white(QColor titleBarColor);
  static const ColorData *colorData(QColor titleBarColor);
};

#endif //  THEROB_COLORS_H
