import QtQuick 2.2;
import QtQuick.Controls 1.1;
import "com/rahpooyanco/minipos";

ApplicationWindow {
    id: applicationWindow;
    objectName: "applicationWindow";
    visible: true;
    width: 640;
    height: 480;
    title: qsTr("mini POS Card Reader") + uiEngine.EmptyLangString;

    signal signal_englishMenuItemPressed();
    signal signal_farsiMenuItemPressed();

    function menuPressed(title) {
        uiEngine.notify(qsTr("mini POS Card Reader") + uiEngine.EmptyLangString, title);
        uiEngine.showToast(title);
    }

    function showToast(text, duration) {
        toast.timoutInterval = duration;
        toast.notificationText = "";
        toast.notificationText = text;
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("mini POS") + uiEngine.EmptyLangString;
            MenuItem {
                text: qsTr("Purchase") + uiEngine.EmptyLangString;
                onTriggered:{
                    view.currentIndex = 1;
                    menuPressed(qsTr("Purchase") + uiEngine.EmptyLangString);
                }
            }
            MenuItem {
                text: qsTr("Balance") + uiEngine.EmptyLangString;
                onTriggered: {
                    view.currentIndex = 2;
                    menuPressed(qsTr("Balance") + uiEngine.EmptyLangString);
                }
            }
            MenuItem {
                text: qsTr("Bill Payment") + uiEngine.EmptyLangString;
                onTriggered: {
                    view.currentIndex = 3;
                    menuPressed(qsTr("Bill Payment") + uiEngine.EmptyLangString);
                }
            }
            MenuItem {
                text: qsTr("Special Payment") + uiEngine.EmptyLangString;
                onTriggered: {
                    view.currentIndex = 4;
                    menuPressed(qsTr("Special Payment") + uiEngine.EmptyLangString);
                }
            }
            MenuItem {
                text: qsTr("Charging Mobile") + uiEngine.EmptyLangString;
                onTriggered: {
                    view.currentIndex = 5;
                    menuPressed(qsTr("Charging Mobile") + uiEngine.EmptyLangString);
                }
            }
            Menu {
                title: qsTr("Language") + uiEngine.EmptyLangString;

                MenuItem {
                    id: englishMenuItem;
                    text: "English";
                    onTriggered: {
                        signal_englishMenuItemPressed();
                        uiEngine.showToast("The language is changed to English!");
                    }
                }
                MenuItem {
                    id: farsiMenuItem;
                    text: "فارسی"
                    onTriggered: {
                        signal_farsiMenuItemPressed();
                        uiEngine.showToast("زبان به فارسی تغییر یافت!");
                    }
                }
            }
            MenuItem {
                text: qsTr("Exit") + uiEngine.EmptyLangString;
                onTriggered: Qt.quit();
            }
        }
    }

    View {
        id: view;
        anchors.fill: parent;
        anchors.centerIn: parent;
        model: VisualItemModel  {
            Rectangle  {
                width: view.width;
                height: view.height;
                color: "#FFFEF0";
                Text  {
                    text: qsTr("Welcome") + uiEngine.EmptyLangString;
                    font.bold: true;
                    anchors.centerIn: parent;
                }
            }
            Rectangle  {
                width: view.width;
                height: view.height;
                color: "#F0FFF7";
                Text  {
                    text: qsTr("Purchase") + uiEngine.EmptyLangString;
                    font.bold: true;
                    anchors.centerIn: parent;
                }
            }
            Rectangle  {
                width: view.width;
                height: view.height;
                color: "#F4F0FF";
                Text  {
                    text: qsTr("Balance") + uiEngine.EmptyLangString;
                    font.bold: true;
                    anchors.centerIn: parent;
                }
            }
            Rectangle  {
                width: view.width;
                height: view.height;
                color: "#FFFEF0";
                Text  {
                    text: qsTr("Bill Paymente") + uiEngine.EmptyLangString;
                    font.bold: true;
                    anchors.centerIn: parent;
                }
            }
            Rectangle  {
                width: view.width;
                height: view.height;
                color: "#F0FFF7";
                Text  {
                    text: qsTr("Special Payment") + uiEngine.EmptyLangString;
                    font.bold: true;
                    anchors.centerIn: parent;
                }
            }
            Rectangle  {
                width: view.width;
                height: view.height;
                color: "#F4F0FF";
                Text  {
                    text: qsTr("Charging Mobile") + uiEngine.EmptyLangString;
                    font.bold: true;
                    anchors.centerIn: parent;
                }
            }
        }
    }

    Toast {
        id: toast;
        anchors.fill: parent;
        anchors.centerIn: parent;
        fontPath: FontPath;
    }
}

