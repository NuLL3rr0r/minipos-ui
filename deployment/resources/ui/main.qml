/**
 * @author  Mohammad S. Babaei <info@babaei.net>
 */


import QtQuick 2.2;
import QtQuick.Controls 1.1;
import "com/rahpooyanco/minipos";

ApplicationWindow {
    id: applicationWindow;
    objectName: "applicationWindow";
    visible: true;
    width: 640;
    height: 480;
    title: qsTr("mini POS Card Reader") + UiEngine.EmptyLangString;

    signal signal_englishMenuItemPressed();
    signal signal_farsiMenuItemPressed();

    function menuPressed(title) {
        UiEngine.notify(qsTr("mini POS Card Reader") + UiEngine.EmptyLangString, title);
        UiEngine.showToast(title);
    }

    function showToast(text, duration) {
        toast.timoutInterval = duration;
        toast.notificationText = "";
        toast.notificationText = text;
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("mini POS") + UiEngine.EmptyLangString;
            MenuItem {
                text: qsTr("Purchase") + UiEngine.EmptyLangString;
                onTriggered:{
                    view.currentIndex = 1;
                    menuPressed(qsTr("Purchase") + UiEngine.EmptyLangString);
                }
            }
            MenuItem {
                text: qsTr("Balance") + UiEngine.EmptyLangString;
                onTriggered: {
                    view.currentIndex = 2;
                    menuPressed(qsTr("Balance") + UiEngine.EmptyLangString);
                }
            }
            MenuItem {
                text: qsTr("Bill Payment") + UiEngine.EmptyLangString;
                onTriggered: {
                    view.currentIndex = 3;
                    menuPressed(qsTr("Bill Payment") + UiEngine.EmptyLangString);
                }
            }
            MenuItem {
                text: qsTr("Special Payment") + UiEngine.EmptyLangString;
                onTriggered: {
                    view.currentIndex = 4;
                    menuPressed(qsTr("Special Payment") + UiEngine.EmptyLangString);
                }
            }
            MenuItem {
                text: qsTr("Charging Mobile") + UiEngine.EmptyLangString;
                onTriggered: {
                    view.currentIndex = 5;
                    menuPressed(qsTr("Charging Mobile") + UiEngine.EmptyLangString);
                }
            }
            Menu {
                title: qsTr("Language") + UiEngine.EmptyLangString;

                MenuItem {
                    id: englishMenuItem;
                    text: "English";
                    onTriggered: {
                        signal_englishMenuItemPressed();
                        UiEngine.showToast("The language is changed to English!");
                    }
                }
                MenuItem {
                    id: farsiMenuItem;
                    text: "فارسی"
                    onTriggered: {
                        signal_farsiMenuItemPressed();
                        UiEngine.showToast("زبان به فارسی تغییر یافت!");
                    }
                }
            }
            MenuItem {
                text: qsTr("Exit") + UiEngine.EmptyLangString;
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
                    text: qsTr("Welcome") + UiEngine.EmptyLangString;
                    font.bold: true;
                    anchors.centerIn: parent;
                }
            }
            Rectangle  {
                width: view.width;
                height: view.height;
                color: "#F0FFF7";
                Text  {
                    text: qsTr("Purchase") + UiEngine.EmptyLangString;
                    font.bold: true;
                    anchors.centerIn: parent;
                }
            }
            Rectangle  {
                width: view.width;
                height: view.height;
                color: "#F4F0FF";
                Text  {
                    text: qsTr("Balance") + UiEngine.EmptyLangString;
                    font.bold: true;
                    anchors.centerIn: parent;
                }
            }
            Rectangle  {
                width: view.width;
                height: view.height;
                color: "#FFFEF0";
                Text  {
                    text: qsTr("Bill Payment") + UiEngine.EmptyLangString;
                    font.bold: true;
                    anchors.centerIn: parent;
                }
            }
            Rectangle  {
                width: view.width;
                height: view.height;
                color: "#F0FFF7";
                Text  {
                    text: qsTr("Special Payment") + UiEngine.EmptyLangString;
                    font.bold: true;
                    anchors.centerIn: parent;
                }
            }
            Rectangle  {
                width: view.width;
                height: view.height;
                color: "#F4F0FF";
                Text  {
                    text: qsTr("Charging Mobile") + UiEngine.EmptyLangString;
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

