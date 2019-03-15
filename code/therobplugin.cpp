/*
 * Copyright (C) 2012 Martin Gräßlin <mgraesslin@kde.org>
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
 */
#include "therobplugin.h"
#include "therobbutton.h"
#include "therobcolors.h"
#include <QQmlEngine>
#include <QtQml>

void TheRobPlugin::registerTypes(const char *uri)
{
  Q_ASSERT(QLatin1String(uri) == QLatin1String("org.kde.kwin.decorations.therob"));
  qmlRegisterType<TheRobColors>(uri, 0, 1, "TheRobColors");
}

void TheRobPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("org.kde.kwin.decorations.therob"));
    engine->addImageProvider(QLatin1String("therob"), new TheRobButtonProvider());
    QQmlExtensionPlugin::initializeEngine(engine, uri);
}

#include "moc_therobplugin.cpp"
