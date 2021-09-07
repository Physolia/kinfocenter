/*
    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
    SPDX-FileCopyrightText: 2021 Harald Sitter <sitter@kde.org>
*/

import QtQuick 2.5
import QtQuick.Controls 2.5 as QQC2
import QtQuick.Layouts 1.1

import org.kde.kirigami 2.12 as Kirigami
import org.kde.kquickcontrolsaddons 2.0
import org.kde.kcm 1.4 as KCM

KCM.SimpleKCM {
    id: root

    implicitWidth: Kirigami.Units.gridUnit * 20
    implicitHeight: Kirigami.Units.gridUnit * 20
    // Use a horizontal scrollbar if text wrapping is disabled. In all other cases we'll go with the defaults.
    horizontalScrollBarPolicy: wrapMode === TextEdit.NoWrap ? Qt.ScrollBarAsNeeded : undefined

    // Somewhat hacky view background setting. The view is the contentItem and our actual
    // content will be moved into it. So, to cover the entire view area with the background we need to
    // anchor it to an already existing item. To achieve that the background is a component that gets
    // instantiated as child of the contentItem (the scrollView) upon completion.
    // TODO: replace with whatever sane solution we come up with
    //   (see https://invent.kde.org/frameworks/kdeclarative/-/merge_requests/77 and references)
    Component {
        id: viewBackground
        Rectangle {
            z: parent.z - 1
            anchors.fill: parent
            color: Kirigami.Theme.backgroundColor
            Kirigami.Theme.colorSet: Kirigami.Theme.View
            Kirigami.Theme.inherit: false
        }
    }

    Component.onCompleted: {
        viewBackground.createObject(root.contentItem)
    }

    // The CommandOutputContext object.
    required property QtObject output
    property int wrapMode: TextEdit.NoWrap

    Component {
        id: dataComponent

        QQC2.Label {
            text: output.text
            font.family: "monospace"
            wrapMode: root.wrapMode
            textFormat: TextEdit.PlainText
        }
    }

    Component {
        id: loadingComponent
        QQC2.BusyIndicator {
            id: indicator
            visible: false
            running: true

            // only show the indicator after a brief timeout otherwise we can have a situtation where loading takes a couple
            // milliseconds during which time the indicator flashes up for no good reason
            Timer {
                running: true
                repeat: false
                interval: 500
                onTriggered: indicator.visible = true
            }
        }
    }

    Component {
        id: noDataComponent

        Kirigami.PlaceholderMessage {
            width: root.width - (Kirigami.Units.largeSpacing * 4)
            text: {
                if (output.error !== "") {
                    return output.error
                }
                if (output.filter !== "" && output.text === "") {
                    return i18nc("@info", "No text matching the filter")
                }
                return i18nc("@info the KCM has no data to display", "No data available")
            }
            icon.name: "data-warning"
        }
    }

    // This is a bit flimsy but we want to switch the content of the KCM around, based on the data state.
    // We could switch around visiblity but a Loader seems neater over all.
    Loader {
        id: contentLoader
    }

    footer: ColumnLayout {
        Kirigami.SearchField {
            id: filterField
            visible: root.state !== "loading"

            placeholderText: i18nc("@label placeholder text to filter for something", "Filter…")

            Accessible.name: i18nc("accessible name for filter input", "Filter")
            Accessible.searchEdit: true

            focusSequence: "Ctrl+I"
            Layout.fillWidth: true

            onAccepted: output.filter = text
        }
    }

    states: [
        State {
            name: "loading"
            when: !output.ready
            PropertyChanges { target: contentLoader; sourceComponent: loadingComponent }
        },
        State {
            name: "noData"
            when: output.text === "" || output.error !== ""
            PropertyChanges { target: contentLoader; sourceComponent: noDataComponent }
        },
        State {
            name: "" // default state
            PropertyChanges { target: contentLoader; sourceComponent: dataComponent }
        }
    ]
}
