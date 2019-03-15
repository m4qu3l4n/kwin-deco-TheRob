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
import QtQuick 2.0
import org.kde.kwin.decoration 0.1
import org.kde.kwin.decorations.therob 1.0

DecorationButton {
    id: button

    property real size

    width: size
    height: size

    Item {
        property int imageOuterMargin: 4
        property int imageSize: button.size - imageOuterMargin
        //The max/restore icons won't get antialiased when the image size is uneven.
        property int imageSizeUneven: imageSize - ((imageSize % 2) ? 0 : 1)
        property int imageWidth: imageSizeUneven
        property int imageHeight: imageSizeUneven
        //TODO: check why change of titleBarColor does not update the image
        property string source: "image://therob/" + button.buttonType + "/" + decoration.client.active + "/" + ((buttonType == DecorationOptions.DecorationButtonMaximizeRestore) ? decoration.client.maximized : button.toggled) + "/" + button.hovered + "/" + options.titleBarColor
        anchors.fill: parent
        Image {
            id: image
            x: button.x + button.width / 2 - width / 2
            y: button.y + button.height / 2 - height / 2 + (button.pressed ? 1 : 0)
            source: parent.source
            width: parent.imageWidth
            height: parent.imageHeight
            sourceSize.width: width
            sourceSize.height: height
        }
    }
    Component.onCompleted: {
        if (buttonType == DecorationOptions.DecorationButtonQuickHelp) {
            visible = Qt.binding(function() { return decoration.client.providesContextHelp});
        }
        if (buttonType == DecorationOptions.DecorationButtonApplicationMenu) {
            visible = false;
        }
    }
}
