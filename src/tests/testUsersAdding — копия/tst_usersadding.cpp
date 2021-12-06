#include <QtTest>
#include "../../testlib/testlib.hpp"
#include "../../lib/register_user.hpp"

// add necessary includes here

class usersAdding : public QObject
{
    Q_OBJECT

public:
    usersAdding();
    ~usersAdding();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_nullInputUser_data();
    void test_nullInputUser();
    //void test_correctInputUser_data();
    //void test_correctInputUser();
private:
    std::unique_ptr<register_user> m_dlg;
};

void usersAdding::initTestCase()
{
    m_dlg.reset(new register_user);
}

void usersAdding::cleanupTestCase()
{
    m_dlg.reset();
}

void usersAdding::test_nullInputUser_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("password");
    QTest::addColumn<QString>("number");
    QTest::addColumn<QString>("inn");
    QTest::addColumn<QString>("bank_num");
    QTest::addColumn<QString>("city");

    QTest::newRow("empty name") << "" << "halva_super" << "+79509819203" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("empty password") << "Halve" << "" << "+79509819203" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("empty number") << "Halve" << "halva_super" << "" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("empty inn") << "Halve" << "halva_super" << "+79509819203" <<
                                   "" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("empty bank_num") << "Halve" << "halva_super" << "+79509819203" <<
                                   "9187654321" << "" << "Krasnoyarsk";
    QTest::newRow("empty city") << "Halve" << "halva_super" << "+79509819203" <<
                                   "9187654321" << "12345678222987654321" << "";
}

void usersAdding::test_nullInputUser()
{
    QFETCH(QString, name);
    QFETCH(QString, password);
    QFETCH(QString, number);
    QFETCH(QString, inn);
    QFETCH(QString, bank_num);
    QFETCH(QString, city);
    user user;
    m_dlg->setUser(&user);
    QSignalSpy spy(m_dlg.get(), &register_user::accepted);
    m_dlg->setName(name);
    m_dlg->setPassword(password);
    m_dlg->setNumber(number);
    m_dlg->setInn(inn);
    m_dlg->setBankNum(bank_num);
    m_dlg->setCity(city);
    m_dlg->open();
    QTimer::singleShot(0, [=]()
    {
        Testlib::accept_active_message_box();
        m_dlg->reject();
    });
    m_dlg->accept();
    QVERIFY2(spy.count() == 0, "Incorrect (NULL value) user accepted");
}

//void usersAdding::test_correctInputUser_data()
//{
//    QTest::addColumn<QString>("name");
//    QTest::addColumn<QString>("password");
//    QTest::addColumn<QString>("number");
//    QTest::addColumn<QString>("inn");
//    QTest::addColumn<QString>("bank_num");
//    QTest::addColumn<QString>("city");

//    QTest::newRow("empty name") << "" << "halva_super" << "+79509819203" <<
//                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
//    QTest::newRow("empty password") << "Halve" << "" << "+79509819203" <<
//                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
//    QTest::newRow("empty number") << "Halve" << "halva_super" << "" <<
//                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
//    QTest::newRow("empty inn") << "Halve" << "halva_super" << "+79509819203" <<
//                                   "" << "12345678222987654321" << "Krasnoyarsk";
//    QTest::newRow("empty bank_num") << "Halve" << "halva_super" << "+79509819203" <<
//                                   "9187654321" << "" << "Krasnoyarsk";
//    QTest::newRow("empty city") << "Halve" << "halva_super" << "+79509819203" <<
//                                   "9187654321" << "12345678222987654321" << "";
//}

//void usersAdding::test_correctInputUser()
//{
//    QFETCH(QString, name);
//    QFETCH(QString, password);
//    QFETCH(QString, number);
//    QFETCH(QString, inn);
//    QFETCH(QString, bank_num);
//    QFETCH(QString, city);
//    user user;
//    m_dlg->setUser(&user);
//    QSignalSpy spy(m_dlg.get(), &register_user::accepted);
//    m_dlg->setName(name);
//    m_dlg->setPassword(password);
//    m_dlg->setInn(inn);
//    m_dlg->setBankNum(bank_num);
//    m_dlg->setCity(city);
//    m_dlg->open();
//    QTimer::singleShot(0, [=]()
//    {
//        Testlib::accept_active_message_box();
//        m_dlg->reject();
//    });
//    m_dlg->accept();
//    QVERIFY2(spy.count() == 0, "Incorrect (NULL value) user accepted");
//}

usersAdding::usersAdding()
{

}

usersAdding::~usersAdding()
{

}

QTEST_APPLESS_MAIN(usersAdding)

#include "tst_usersadding.moc"
