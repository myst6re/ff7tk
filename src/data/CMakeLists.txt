# SPDX-FileCopyrightText: Chris Rizzitello <sithlord48@gmail.com>
# SPDX-License-Identifier: MIT

find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    Core5Compat
    Svg
    Xml
)
set(UTILS ON CACHE BOOL "Build ff7tkUtils Lib" FORCE)
find_library(ff7tkUtils ${CMAKE_BINARY_DIR}/src/utils)

add_subdirectory(crypto)

find_package( ZLIB REQUIRED)
sbom_add(PACKAGE ZLIB VERSION ${ZLIB_VERSION})

if(ZLIB_FOUND)
    define_property(GLOBAL PROPERTY zlib_target BRIEF_DOCS "zlib dll path" FULL_DOCS "zlib.dll path")
    if(EXISTS ${ZLIB_ROOT}/bin/zlib.dll)
        set_property(GLOBAL APPEND PROPERTY zlib_target "${ZLIB_ROOT}/bin/zlib.dll")
    elseif(EXISTS ${ZLIB_ROOT}/bin/zlib1.dll)
        set_property(GLOBAL APPEND PROPERTY zlib_target "${ZLIB_ROOT}/bin/zlib1.dll")
    elseif(EXISTS ${ZLIB_ROOT}/bin/libzlib.dll)
        set_property(GLOBAL APPEND PROPERTY zlib_target "${ZLIB_ROOT}/bin/libzlib.dll")
    elseif(EXISTS ${ZLIB_ROOT}/bin/libzlib1.dll)
        set_property(GLOBAL APPEND PROPERTY zlib_target "${ZLIB_ROOT}/bin/libzlib1.dll")
    endif()
endif()

set ( ff7tkData_SRC
        FF7Achievements.cpp  FF7Char.cpp     FF7FieldItemList.cpp
        FF7Item.cpp          FF7Location.cpp
        FF7Save.cpp          FF7SaveInfo.cpp FF7Text.cpp
        SaveIcon.cpp         FF7ItemModel.cpp FF7String.cpp
)

set (ff7tkData_HEADERS
    FF7FieldItemList.h  FF7Materia.h   FF7Save_Types.h  Type_FF7CHAR.h FF7String.h
    FF7Achievements.h  FF7Item.h           FF7Save.h      FF7Text.h        Type_FF7CHOCOBO.h
    FF7Char.h          FF7Location.h       FF7SaveInfo.h  SaveIcon.h       Type_materia.h
    FF7ItemModel.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkdata_export.h
)

set ( ff7tkData_RESOURCES
        ${CMAKE_SOURCE_DIR}/src/icons/achievements.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/characters.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/chocobo.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/common.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/items.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/locations.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/materia.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/psxButtons.qrc
)

set (ff7tkData_PublicLIBLINKS
      Qt::Core
      Qt::Xml
      Qt::Svg
      Qt::Core5Compat
      ZLIB::ZLIB
)

set (ff7tkData_PrivateLIBLINKS
    CRYPTO
)

MAKE_LIBRARY(ff7tkData ff7tk/data)
