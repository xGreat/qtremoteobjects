// Copyright (C) 2017 Ford Motor Company
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "rep_pods_replica.h"

#include <QTest>

#include <QByteArray>
#include <QDataStream>

class tst_pods : public QObject {
    Q_OBJECT

private Q_SLOTS:
    void testConstructors();
    void testMarshalling();
};


void tst_pods::testConstructors()
{
    PodI pi1;
    QCOMPARE(pi1.i(), 0);

    PodI pi2(1);
    QCOMPARE(pi2.i(), 1);

    PodI pi3(pi2);
    QCOMPARE(pi3.i(), pi2.i());
}

void tst_pods::testMarshalling()
{
    QByteArray ba;
    QDataStream ds(&ba, QIODevice::ReadWrite);

    {
        PodI i1(1), i2(2), i3(3), iDeadBeef(0xdeadbeef);
        ds << i1 << i2 << i3 << iDeadBeef;
    }

    ds.device()->seek(0);

    {
        PodI i1, i2, i3, iDeadBeef;
        ds >> i1 >> i2 >> i3 >> iDeadBeef;

        QCOMPARE(i1.i(), 1);
        QCOMPARE(i2.i(), 2);
        QCOMPARE(i3.i(), 3);
        QCOMPARE(iDeadBeef.i(), int(0xdeadbeef));
    }
}

QTEST_APPLESS_MAIN(tst_pods)

#include "tst_pods.moc"

