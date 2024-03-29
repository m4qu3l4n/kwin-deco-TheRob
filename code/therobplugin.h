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
#ifndef THEROB_PLUGIN_H
#define THEROB_PLUGIN_H

#include <QQmlExtensionPlugin>

class TheRobPlugin : public QQmlExtensionPlugin
{
    Q_PLUGIN_METADATA(IID "org.kde.kwin.decorations.therob")
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri) override;
    virtual void initializeEngine(QQmlEngine *engine, const char *uri) override;
};

#endif // THEROB_PLUGIN_H
