#include <memory>
#include <QtTest>
#include <QCoreApplication>

#include "../../testlib/testlib.hpp"
#include "../../lib/register_user.hpp"
#include "../../lib/config.hpp"

// add necessary includes here

class userAdding : public QObject
{
    Q_OBJECT

public:
    userAdding();
    ~userAdding();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_nullInputUser_data();
    void test_nullInputUser();
    void test_correctInputUser_data();
    void test_correctInputUser();
    void test_prohibitedInputUser_data();
    void test_prohibitedInputUser();
private:
    std::unique_ptr<register_user> m_dlg;
};

void userAdding::initTestCase()
{
    m_dlg.reset(new register_user);
}

void userAdding::cleanupTestCase()
{
    m_dlg.reset();
}
//пустые поля
void userAdding::test_nullInputUser_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("password");
    QTest::addColumn<QString>("number");
    QTest::addColumn<QString>("inn");
    QTest::addColumn<QString>("bank_num");
    QTest::addColumn<QString>("city");

    QTest::newRow("empty name") << "" << "halva_super" << "+79509819203" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("empty password") << "Halva" << "" << "+79509819203" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("empty number") << "Halva" << "halva_super" << "" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("empty inn") << "Halva" << "halva_super" << "+79509819203" <<
                                   "" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("empty bank_num") << "Halva" << "halva_super" << "+79509819203" <<
                                   "9187654321" << "" << "Krasnoyarsk";
    QTest::newRow("empty city") << "Halva" << "halva_super" << "+79509819203" <<
                                   "9187654321" << "12345678222987654321" << "";
}

void userAdding::test_nullInputUser()
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
//end
//правильность ввода
void userAdding::test_correctInputUser_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("password");
    QTest::addColumn<QString>("number");
    QTest::addColumn<QString>("inn");
    QTest::addColumn<QString>("bank_num");
    QTest::addColumn<QString>("city");

    QTest::newRow("size name > 20") << "KlavaYKlaviYkralaKarali124124154" << "halva_super" << "+79509819203" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("size password less") << "Halva" << "123" << "+79509819203" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("size password large") << "Halva" << "123456789012345678901234563414124" << "+79509819203" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("size inn != 10") << "Halva" << "halva_super" << "+79509819203" <<
                                   "99876543214141414" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("size num != 12") << "Halva" << "halva_super" << "+795098192034444" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("size num[0] != '+'") << "Halva" << "halva_super" << "895098192043" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("size bank_num != 20") << "Halva" << "halva_super" << "+79509819203" <<
                                   "9187654321" << "1234567822298765432122442" << "Krasnoyarsk";
    QTest::newRow("size adress > 30") << "Halva" << "halva_super" << "+79509819203" <<
                                   "9187654321" << "12345678222987654321" << "KrasnoyarskKrasnoyarskKrasnoyarsk";
}

void userAdding::test_correctInputUser()
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
//end
//Уникальность ввода данных
void userAdding::test_prohibitedInputUser_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("password");
    QTest::addColumn<QString>("number");
    QTest::addColumn<QString>("inn");
    QTest::addColumn<QString>("bank_num");
    QTest::addColumn<QString>("city");

    QTest::newRow("prohibited name (admin)") << config::nameAdmin << "halva_super" << "+79509819203" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("prohibited name (managers)") << config::nameManagers << "halva_super" << "+79509819203" <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("prohibited BankNum") << "Halva" << "halva_super" << "+79509819203" <<
                                   "9187654321" << config::bankNumCallCenter << "Krasnoyarsk";
    QTest::newRow("prohibited INN") << "Halva" << "halva_super" << "+79509819203" <<
                                   config::innCallCenter << "12345678222987654321" << "Krasnoyarsk";
    QTest::newRow("prohibited number") << "Halva" << "halva_super" << config::numberCallCenter <<
                                   "9187654321" << "12345678222987654321" << "Krasnoyarsk";
}

void userAdding::test_prohibitedInputUser()
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

userAdding::userAdding()
{

}

userAdding::~userAdding()
{

}

QTEST_MAIN(userAdding)

#include "tst_useradding.moc"
