/*
 * Copyright 2012 Martin Gräßlin <mgraesslin@kde.org>
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
#ifndef KWIN_THEROB_BUTTON_H
#define KWIN_THEROB_BUTTON_H

#include <QQuickImageProvider>

class TheRobButtonProvider : public QQuickImageProvider
{
public:
    explicit TheRobButtonProvider();
    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:
    enum ButtonIcon {
        CloseIcon = 0,
        MaxIcon,
        MaxRestoreIcon,
        MinIcon,
        HelpIcon,
        OnAllDesktopsIcon,
        NotOnAllDesktopsIcon,
        KeepAboveIcon,
        NoKeepAboveIcon,
        KeepBelowIcon,
        NoKeepBelowIcon,
        ShadeIcon,
        UnShadeIcon,
        AppMenuIcon,
        NumButtonIcons
    };
    enum Object {
        HorizontalLine,
        VerticalLine,
        DiagonalLine,
        CrossDiagonalLine
    };
    enum DecorationButton {
        /**
         * Invalid button value. A decoration should not create a button for
         * this type.
         */
        DecorationButtonNone,
        DecorationButtonMenu,
        DecorationButtonApplicationMenu,
        DecorationButtonOnAllDesktops,
        DecorationButtonQuickHelp,
        DecorationButtonMinimize,
        DecorationButtonMaximizeRestore,
        DecorationButtonClose,
        DecorationButtonKeepAbove,
        DecorationButtonKeepBelow,
        DecorationButtonShade,
        DecorationButtonResize,
        /**
         * The decoration should create an empty spacer instead of a button for
         * this type.
         */
        DecorationButtonExplicitSpacer
    };
    QPixmap icon(ButtonIcon icon, int size, bool active, QColor titleBarColor);
};

#endif //  KWIN_THEROB_BUTTON_H
