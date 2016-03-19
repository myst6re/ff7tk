
######################################################################
#Automatically generated by qmake (2.01a) Mon Mar 26 23:01:23 2012
######################################################################

TEMPLATE= app
TARGET = ff7tkDemo
QT+= core gui xml
greaterThan(QT_MAJOR_VERSION, 4):	QT += widgets

# Input
HEADERS+=	mainwindow.h\
			../data/FF7Achievements.h\
			../data/FF7FieldItemList.h\
			../data/FF7Item.h \
			../data/FF7Location.h \
			../data/FF7Materia.h\
			../data/FF7Save.h\
			../data/FF7Save_Const.h\
			../data/FF7Save_Types.h\
			../data/FF7Text.h\
			../data/SaveIcon.h\
			../data/FF7Char.h\
			../data/Type_FF7CHAR.h\
			../data/Type_FF7CHOCOBO.h\
			../data/Type_materia.h\
			../formats/Archive.h \
			../formats/Lgp.h\
			../formats/Lgp_p.h\
			../utils/LZS.h\
			../widgets/AchievementEditor.h\
			../widgets/CharEditor.h\
			../widgets/CharManager.h\
			../widgets/ChocoboEditor.h\
			../widgets/ChocoboLabel.h\
			../widgets/ChocoboManager.h \
			../widgets/DialogPreview.h\
			../widgets/DoubleCheckBox.h\
			../widgets/ItemList.h\
			../widgets/ItemPreview.h\
			../widgets/ItemSelector.h\
			../widgets/LocationViewer.h\
			../widgets/MateriaEditor.h\
			../widgets/MenuListWidget.h\
			../widgets/MetadataCreator.h\
			../widgets/OptionsWidget.h\
			../widgets/PhsListWidget.h\
			../widgets/SlotPreview.h\
			../widgets/SlotSelect.h

FORMS+=		mainwindow.ui

SOURCES+=	main.cpp\
			mainwindow.cpp\
			../data/FF7Achievements.cpp\
			../data/FF7Char.cpp\
			../data/FF7FieldItemList.cpp\
			../data/FF7Item.cpp\
			../data/FF7Location.cpp\
			../data/FF7Materia.cpp\
			../data/FF7Save.cpp\
			../data/FF7Text.cpp\
			../data/SaveIcon.cpp\
			../formats/Archive.cpp\
			../utils/LZS.cpp\
			../formats/Lgp.cpp\
			../formats/Lgp_p.cpp\
			../widgets/AchievementEditor.cpp\
			../widgets/CharEditor.cpp\
			../widgets/CharManager.cpp\
			../widgets/ChocoboEditor.cpp\
			../widgets/ChocoboLabel.cpp\
			../widgets/ChocoboManager.cpp\
			../widgets/DialogPreview.cpp\
			../widgets/DoubleCheckBox.cpp\
			../widgets/ItemList.cpp\
			../widgets/ItemPreview.cpp\
			../widgets/ItemSelector.cpp\
			../widgets/LocationViewer.cpp\
			../widgets/MenuListWidget.cpp\
			../widgets/MateriaEditor.cpp\
			../widgets/MetadataCreator.cpp\
			../widgets/OptionsWidget.cpp\
			../widgets/PhsListWidget.cpp\
			../widgets/SlotPreview.cpp\
			../widgets/SlotSelect.cpp

RESOURCES+=\
			../icons/achievements.qrc\
			../icons/characters.qrc\
			../icons/chocobo.qrc\
			../icons/common.qrc\
			../icons/items.qrc\
			../icons/locations.qrc\
			../icons/materia.qrc\
			../icons/psxButtons.qrc

#Uncomment Below to Generate translations (currently part of black chocobo)
#TRANSLATIONS+=\
#			../lang/ff7tk_de.ts \
#			../lang/ff7tk_en.ts \
#			../lang/ff7tk_es.ts \
#			../lang/ff7tk_fr.ts \
#			../lang/ff7tk_jp.ts \
#			../lang/ff7tk_re.ts
unix:{
	#DEFINES += OPENSSL=1							# Enable openSSL support
	#LIBS += -lcrypto								# Enable crypto lib
}
win32:{
	#Set OpenSSL include & lib paths
	#THIS MUST BE CHANGED WITH YOUR OPENSSL PATHS OR YOUR BUILD WILL FAIL!!!
	#DEFINES += OPENSSL=1							# Enable openSSL support
	#INCLUDEPATH += C:/OpenSSL-Win32/include		# Be sure to change this to your openSSL include path
	#LIBS += -L"C:/OpenSSL-Win32/lib" -llibeay32	# Be sure to update this to your openSSL lib path
	#Prevent ms padding on packed structures on gcc compiler
	contains(QMAKE_COMPILER, gcc) {
	QMAKE_CXXFLAGS += -mno-ms-bitfields
	}
}
static:{ # everything below takes effect with CONFIG += static
	CONFIG += static
	CONFIG += staticlib # this is needed if you create a static library, not a static executable
	lessThan(QT_MAJOR_VERSION, 5): QTPLUGIN += qcncodecs qjpcodecs qtwcodecs qkrcodecs
	DEFINES += STATIC
	message("Static Build") # this is for information, that the static build is done
	TARGET = $$join(TARGET,,,-static) #this adds an s in the end, so you can seperate static build from non static build
}
# change the name of the binary, if it is build in debug mode
CONFIG(debug, debug|release) {TARGET = $$join(TARGET,,,-debug)}
