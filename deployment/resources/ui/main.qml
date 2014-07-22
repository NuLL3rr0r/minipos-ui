import QtQuick 2.2;
import QtQuick.Controls 1.1;
import "com/rahpooyanco/minipos";

ApplicationWindow {
    id: applicationWindow;
    objectName: "applicationWindow";
    visible: true;
    width: 640;
    height: 480;
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

    Toast {
        id: toast;
        anchors.fill: parent;
        anchors.centerIn: parent;
        fontPath: FontPath;
    }

    function showToast(text, duration) {
        console.log(text);
        toast.timoutInterval = duration;
        toast.notificationText = "";
        toast.notificationText = text;
    }
}
