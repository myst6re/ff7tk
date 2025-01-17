//    SPDX-FileCopyrightText: 2021 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <QObject>

#include "../../src/data/Type_FF7CHAR.h"
#include "../../src/data/FF7Char.h"

class FF7Char_Test : public QObject
{
    Q_OBJECT
private slots:
/*~~~~~~~~Tests Assumed to be run in order~~~~~~~~~~~~~~~~~*/
    void initTestCase();
    void test_fromByteArray();
    void test_toByteArray();

private:
    QString qt5Warning = QStringLiteral("Known to Fail on Qt5 Windows.");
    FF7CHAR FF7CHARCloud;
    FF7CHAR _charData;
    const QByteArray _cloudData = QByteArray::fromRawData("\x00\x63\x64\x5D\x64\x62\x3D\x1D\x9B\x87\x68\x18\xC2\xE5\x04\xFB\x23\x4C\x4F\x55\x44\xFF\xFF\x00\x00\xFF\xFF\xFF\x0F\x1B\x12\x00\xFE\x3D\xDB\x02\x35\x0C\x14\x00\x0E\x00\x2D\x00\x0F\x27\xAE\x23\xE7\x03\x6D\x03\x00\x00\x00\x00\x0F\x27\xE7\x03\x01\x20\xDF\x00\x49\x00\x00\x00\x1B\xFF\xFF\xFF\x49\x90\x01\x00\x1C\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x30\x82\x14\x00\xFF\xFF\xFF\xFF\x5A\x26\x02\x00\x15\xFF\xFF\xFF\x08\xFF\xFF\xFF\x01\xFF\xFF\xFF\x0B\xFF\xFF\xFF\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x00\x00\x00\x00", 132);
};
