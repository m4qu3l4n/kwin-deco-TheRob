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
#include "therobcolors.h"
#include <QSettings>
#include <QPalette>

QHash<QString, ColorData *> TheRobColors::m_data;

// helper function to create the hash
inline QString hashColor(const QColor &color)
{
  return color.name();
}

const ColorData *TheRobColors::colorData(QColor titleBarColor)
{
  QString hash = hashColor(titleBarColor);
  
  if (!m_data.contains(hash))
    return m_data.value(hash);
  
  return m_data.value(hash);
}

QColor TheRobColors::color1(QColor titleBarColor)
{
  QString hash = hashColor(titleBarColor);

  if (!m_data.contains(hash))
    readConfig(titleBarColor);
    
  return m_data.value(hash)->color[1];
}

QColor TheRobColors::color2(QColor titleBarColor)
{
  QString hash = hashColor(titleBarColor);
  
  if (!m_data.contains(hash))
    readConfig(titleBarColor);
  
  return m_data.value(hash)->color[2];
}

QColor TheRobColors::color3(QColor titleBarColor)
{
  QString hash = hashColor(titleBarColor);
  
  if (!m_data.contains(hash))
    readConfig(titleBarColor);
  
  return m_data.value(hash)->color[3];
}

QColor TheRobColors::color4(QColor titleBarColor)
{
  QString hash = hashColor(titleBarColor);
  
  if (!m_data.contains(hash))
    readConfig(titleBarColor);
  
  return m_data.value(hash)->color[4];
}

QColor TheRobColors::black(QColor titleBarColor)
{
  QString hash = hashColor(titleBarColor);
  
  if (!m_data.contains(hash))
    readConfig(titleBarColor);
  
  return m_data.value(hash)->black;
}

QColor TheRobColors::white(QColor titleBarColor)
{
  QString hash = hashColor(titleBarColor);
  
  if (!m_data.contains(hash))
    readConfig(titleBarColor);
  
  return m_data.value(hash)->white;
}

void TheRobColors::readConfig(QColor titleBarColor)
{
  QString hash = hashColor(titleBarColor);
  
  // if already cached, just return
  if (m_data.contains(hash))
    return;

  ColorData *data = new ColorData();
  QPalette pal;
  QColor background = pal.color(QPalette::Window);
  
  //TODO: check whether black and white should not be black and white
  data->black = Qt::black;
  data->white = Qt::white;
  
  QSettings conf("/etc/therobcolors", QSettings::NativeFormat); // TODO: define where this file must go
  
  if (background.name() == "#eff3f7") {
    conf.beginGroup("Default");
    data->gray[0] = (conf.value("gray0", background)).value<QColor>();
    data->gray[1] = (conf.value("gray1", background.darker(107))).value<QColor>();
    data->gray[2] = (conf.value("gray2", background.darker(115))).value<QColor>();
    data->gray[3] = (conf.value("gray3", background.darker(144))).value<QColor>();
    data->gray[4] = (conf.value("gray4", background.darker(144))).value<QColor>();
    data->gray[5] = (conf.value("gray5", background.darker(144))).value<QColor>();
    data->gray[6] = (conf.value("gray6", background.darker(144))).value<QColor>();
    conf.endGroup();
  } else {
    data->gray[0] = background.darker(107);
    data->gray[1] = background.darker(107);
    data->gray[2] = background.darker(115);
    data->gray[3] = background.darker(117);
    data->gray[4] = background.darker(117);
    data->gray[5] = background.darker(117);
    data->gray[6] = background.darker(117);
  }
  
  QString group = "";
  
  if (titleBarColor.name() == "#8ec7ff") group = "Arctic";
  else if (titleBarColor.name() == "#4965ae") group = "Blue";
  else if (titleBarColor.name() == "#cfd7df") group = "Gray";
  else if (titleBarColor.name() == "#5d658e") group = "Night";
  else if (titleBarColor.name() == "#f7b610") group = "Orange";
  else if (titleBarColor.name() == "#7baae7") group = "Smooth";
  else if (titleBarColor.name() == "#148dcd") group = "Steel";
  
  if (!group.isEmpty()) {
    conf.beginGroup(group);
    data->color[0] = (conf.value("color0", titleBarColor.lighter(150))).value<QColor>();
    data->color[1] = (conf.value("color1", titleBarColor.lighter(137))).value<QColor>();
    data->color[2] = (conf.value("color2", titleBarColor)).value<QColor>();
    data->color[3] = (conf.value("color3", titleBarColor.lighter(112))).value<QColor>();
    data->color[4] = (conf.value("color4", titleBarColor.lighter(130))).value<QColor>();
    conf.endGroup();
  } else {
    data->color[0] = titleBarColor.lighter(160);
    data->color[1] = titleBarColor.lighter(130);
    data->color[2] = titleBarColor;
    data->color[3] = titleBarColor;
    data->color[4] = titleBarColor;
    data->color[5] = titleBarColor;
    data->color[6] = titleBarColor;
  }

  m_data.insert(hashColor(titleBarColor), data);
}
