import QtQuick 2.2;
import QtQuick.Controls 1.1;
import "com/rahpooyanco/minipos";

ApplicationWindow {
    id: applicationWindow;
    objectName: "applicationWindow";
    visible: true;
    width: 640;
    height: 480;
    title: qsTr("مینی پوز");

    function menuPressed(title) {
        uiEngine.notify("مینی پوز", title);
        uiEngine.showToast(title);
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("منوی اصلی");
            MenuItem {
                text: qsTr("خرید");
                onTriggered: menuPressed("خرید");
            }
            MenuItem {
                text: qsTr("موجودی");
                onTriggered: menuPressed("موجودی");
            }
            MenuItem {
                text: qsTr("قبض");
                onTriggered: menuPressed("قبض");
            }
            MenuItem {
                text: qsTr("پرداخت خاص");
                onTriggered: menuPressed("پرداخت خاص");
            }
            MenuItem {
                text: qsTr("شارژ");
                onTriggered: menuPressed("شارژ");
            }
            MenuItem {
                text: qsTr("خروج");
                onTriggered: Qt.quit();
            }
        }
    }

    Toast {
        id: toast;
        anchors.fill: parent;
        anchors.centerIn: parent;
        fontPath: FontPath;
    }

    function showToast(text, duration) {
        toast.timoutInterval = duration;
        toast.notificationText = "";
        toast.notificationText = text;
    }
}
