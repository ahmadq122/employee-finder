import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Qt.labs.settings 1.0
import Maes.ReadJsonFromFile 1.0

ApplicationWindow {
    id: window
    visible: true
    //    visibility: "FullScreen"
    width: 1024
    height: 600
    title: qsTr("Employee Finder")

    RowLayout{
        anchors.fill: parent
        spacing: 0
        Item{
            id: itemLeft
            Layout.fillWidth: true
            Layout.fillHeight: true
            Column{
                spacing: 10
                Column{
                    Text{
                        text: "Filter Data Options"
                        padding: 5
                    }
                    Rectangle{
                        height: 1
                        width: itemLeft.width
                        color: "black"
                    }
                }
                Column{
                    spacing: 5
                    Row{
                        Text{
                            text: "Filter Options 1"
                            padding: 5
                        }
                        ComboBox{
                            id: fil1Box
                            model: props.modelFilter1
                            textRole: "text"
                            valueRole: "id"
                            onActivated: {
                                //                                console.debug(currentText, displayText, currentValue)
                            }
                        }
                    }
                    Row{
                        Text{
                            text: "Filter Options 2"
                            padding: 5
                        }
                        ComboBox{
                            id: fil2Box
                            visible: fil1Box.currentValue !== "name"
                            //model: props.modelFilter1
                            textRole: "text"
                            valueRole: "text"
                            onActivated: {
                                //                                console.debug(currentText, displayText)
                            }
                            Component.onCompleted: {
                                model = Qt.binding(function(){
                                    if(fil1Box.currentValue === "position_level"){
                                        return props.modelFilter2PosLevel
                                    }else if(fil1Box.currentValue === "job_title"){
                                        return props.modelFilter2JobTitle
                                    }else if(fil1Box.currentValue === "employment_status"){
                                        return props.modelFilter2EmpStatus
                                    }else if(fil1Box.currentValue === "department"){
                                        return props.modelFilter2Department
                                    }else if(fil1Box.currentValue === "name"){
                                        return /*props.modelFilter2PosLevel*/[]
                                    }
                                })
                            }
                        }
                        TextField{
                            id: fil2NameField
                            visible: fil1Box.currentValue === "name"
                            width: 140
                            placeholderText: "Employee Name"
                            // onAccepted: {
                            //     console.debug(text)
                            // }
                            // onTextChanged: {
                            //     console.debug(text)
                            // }
                        }
                    }
                }

                Rectangle{
                    height: 40
                    width: 120
                    color: "grey"
                    opacity: applyMA.pressed ? 0.5 : 1
                    Text{
                        height: parent.height
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Apply"
                    }
                    MouseArea{
                        id: applyMA
                        anchors.fill: parent
                        onClicked: {
                            let fil2 = fil2Box.currentValue
                            if(fil2NameField.visible){
                                fil2 = fil2NameField.text
                            }
                            ReadJsonFromFile.filterEmployeeData(fil1Box.currentValue, fil2)
                        }
                    }
                }
            }
        }
        Rectangle{
            Layout.minimumWidth: 1
            Layout.fillHeight: true
            color: "grey"
        }
        Item{
            id: itemRight
            Layout.fillWidth: true
            Layout.fillHeight: true

            Column{
                spacing: 10
                Column{
                    Text{
                        text: "Filtered Data"
                        padding: 5
                    }
                    Rectangle{
                        height: 1
                        width: itemRight.width
                        color: "black"
                    }
                }
                Column{
                    spacing: 5
                    Repeater{
                        model: ReadJsonFromFile.pEmployeeDataJsonArrayFiltered
                        Row{
                            //spacing: 2
                            Text{
                                text: index+1 + ")"
                                padding: 5
                            }
                            Column{
                                spacing: 0
                                Row{
                                    Text{
                                        width: 100
                                        text: "Name"
                                        padding: 5
                                    }
                                    Text{
                                        text: ": " + modelData.name
                                        padding: 5
                                    }
                                }
                                Row{
                                    Text{
                                        width: 100
                                        text: "Department"
                                        padding: 5
                                    }
                                    Text{
                                        text: ": " + modelData.department
                                        padding: 5
                                    }
                                }
                                Row{
                                    Text{
                                        width: 100
                                        text: "Job Title"
                                        padding: 5
                                    }
                                    Text{
                                        text: ": " + modelData.job_title
                                        padding: 5
                                    }
                                }
                                Row{
                                    Text{
                                        width: 100
                                        text: "Position Level"
                                        padding: 5
                                    }
                                    Text{
                                        text: ": " + modelData.position_level
                                        padding: 5
                                    }
                                }
                                Row{
                                    Text{
                                        width: 100
                                        text: "Employment Status"
                                        padding: 5
                                    }
                                    Text{
                                        text: ": " + modelData.employment_status
                                        padding: 5
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Settings{
        id: settings

        property alias width: window.width
        property alias height: window.height
    }

    QtObject{
        id: props

        property var modelFilter1: [
            {"text": "Position Level",      "id": "position_level"},
            {"text": "Job title",           "id": "job_title"},
            {"text": "Employment status",   "id": "employment_status"},
            {"text": "Department",          "id": "department"},
            {"text": "Name",                "id": "name"},
        ]
        property var modelFilter2PosLevel: [
            {"text": "1"},
            {"text": "2"},
            {"text": "3"},
            {"text": "4"},
            {"text": "5"},
        ]
        property var modelFilter2JobTitle: [
            {"text": "Chief Marketing Officer"},
            {"text": "Marketing Coordinator"},
            {"text": "Marketing Assistant"},
            {"text": "Marketing Intern"},
            {"text": "Help Desk"},
            {"text": "Production Manager"},
            {"text": "Line Coordinator"},
            {"text": "Operator"},
            {"text": "Junior Operator"},
            {"text": "Quality Assurance"},
            {"text": "Procurement"},
            {"text": "Cleaner"},
            {"text": "Software Engineer"},
            {"text": "Junior SoftwareEngineer"},
            {"text": "Senior Tester"},
            {"text": "Project Manager"},
            {"text": "Senior Software Engineer"},
            {"text": "Principal Engineer"},
            {"text": "Scrum Master"}
        ]
        property var modelFilter2EmpStatus: [
            {"text": "full-time"},
            {"text": "contract"},
            {"text": "casual"},
            {"text": "part-time"}
        ]
        property var modelFilter2Department: [
            {"text": "Marketing"},
            {"text": "Production"},
            {"text": "R&D"}
        ]

        function onJsonDataInitFinished(data){
            //            console.debug(JSON.stringify(data))
            //            ReadJsonFromFile.filterEmployeeData("name", "Jarwo Likitung")
        }
        function onJsonDataFilteredFinished(data){
            //            console.debug(JSON.stringify(data))
        }
    }

    Component.onCompleted: {
        ReadJsonFromFile.sEmployeeDataJsonArrayChanged.connect(props.onJsonDataInitFinished)
        ReadJsonFromFile.sEmployeeDataJsonArrayFilteredChanged.connect(props.onJsonDataFilteredFinished)

        let jsonFiles = []
        jsonFiles.push(":/employee_data/dep_mark.json")
        jsonFiles.push(":/employee_data/dep_prod.json")
        jsonFiles.push(":/employee_data/dep_rnd.json")
        const strList = jsonFiles
        //        console.debug(strList)
        ReadJsonFromFile.initJsonDataFromFiles(strList);
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#808080";height:1000}
}
##^##*/
