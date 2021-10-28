#include <QtTest>
#include <QCoreApplication>
#include "../LibrarySearchingProject/librarysearchingproject.h"

// add necessary includes here

class autotest : public QObject
{
    Q_OBJECT
    LibrarySearchingProject Lib;

public:
    autotest();
    ~autotest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

autotest::autotest()
{

}

autotest::~autotest()
{

}

void autotest::initTestCase()
{
    QCOMPARE(Lib.maxProgress(), 50);
}

void autotest::cleanupTestCase()
{

}

void autotest::test_case1()
{

}

QTEST_MAIN(autotest)

#include "tst_autotest.moc"
