import QtQuick 2.2;

Item {
    id: view;

    property VisualItemModel model;
    property alias currentIndex: listView.currentIndex;

    ListView  {
        id: listView;
        anchors  {
            fill: parent;
            bottomMargin: parent.height * 0.1;
        }
        model: view.model;
        preferredHighlightBegin: 0;
        preferredHighlightEnd: 0;
        highlightRangeMode: ListView.StrictlyEnforceRange;
        orientation: ListView.Horizontal;
        snapMode: ListView.SnapOneItem;
        cacheBuffer: 1;
        highlightMoveVelocity: 4000;
        highlightMoveDuration: 500;
    }

    Rectangle  {
        id: navBar;
        width: parent.width;
        height: parent.height * 0.075;
        anchors  {
            top: listView.bottom;
            bottom: parent.bottom;
        }
        color: "gray";

        Row  {
            anchors.centerIn: parent
            spacing: navBar.height * 0.4;

            Repeater  {
                model: view.model.count;

                Rectangle  {
                    width: navBar.height * 0.4;
                    height: navBar.height * 0.4;
                    radius: navBar.height * 0.25;
                    color: listView.currentIndex === index ? "blue" : "white";

                    MouseArea  {
                        width: parent.width;
                        height: parent.height;
                        anchors.centerIn: parent;
                        onClicked: listView.currentIndex = index;
                    }
                }
            }
        }
    }
}
