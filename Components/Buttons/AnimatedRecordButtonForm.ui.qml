import QtQuick 2.14
import QtQuick.Controls 2.14

import "../FontAwesome"

ToolButton {
    id: recordButton
    display: AbstractButton.IconOnly
    icon.source: "qrc:/speech-icon.png"
    icon.height: recordButton.height * 0.8
    icon.width: recordButton.width * 0.8
    icon.color: "transparent"
}
