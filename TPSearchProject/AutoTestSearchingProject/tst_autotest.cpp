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
    ~autotest() override;

private slots:
    void initTestCase();
};

autotest::autotest()
{
    Lib.setMaxProgress(50);
}

autotest::~autotest()
{

}

void autotest::initTestCase()
{
    QCOMPARE(Lib.maxProgress(), 50);
}

QTEST_MAIN(autotest)

#include "tst_autotest.moc"
