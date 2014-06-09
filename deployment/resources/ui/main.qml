import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Button {
        text: qsTr("Say Hello World!");
        anchors.centerIn: parent;
        onClicked: {
            uiEngine.notify("mini POS", "Hello World!");
            uiEngine.showToast("Hello World!");
        }
    }
}
