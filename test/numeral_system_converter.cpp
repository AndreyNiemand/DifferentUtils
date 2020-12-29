#include <QTest>

#include "numeral_system_converter.h"

using std::operator""s;


class test_numeral_system_converter: public QObject
{
    Q_OBJECT

private slots:

    void test_cpp_interface_to_base()
    {
        const auto v1 = nsc::number_t("34", 16);
        const nsc::number_t v2 = 0x34;

        QCOMPARE(v1, 0x34);
        QCOMPARE(v2, 0x34);

        //QCOMPARE(v1.to_base(1),  v2.to_base(1));
        QCOMPARE(v1.to_base(2),  v2.to_base(2));
        QCOMPARE(v1.to_base(3),  v2.to_base(3));
        QCOMPARE(v1.to_base(4),  v2.to_base(4));
        QCOMPARE(v1.to_base(5),  v2.to_base(5));
        QCOMPARE(v1.to_base(6),  v2.to_base(6));
        QCOMPARE(v1.to_base(7),  v2.to_base(7));
        QCOMPARE(v1.to_base(8),  v2.to_base(8));
        QCOMPARE(v1.to_base(9),  v2.to_base(9));
        QCOMPARE(v1.to_base(10), v2.to_base(10));
        QCOMPARE(v1.to_base(11), v2.to_base(11));
        QCOMPARE(v1.to_base(12), v2.to_base(12));
        QCOMPARE(v1.to_base(13), v2.to_base(13));
        QCOMPARE(v1.to_base(14), v2.to_base(14));
        QCOMPARE(v1.to_base(15), v2.to_base(15));

        //QCOMPARE(v1.to_base(-1),  v2.to_base(-1));
        QCOMPARE(v1.to_base(-2),  v2.to_base(-2));
        QCOMPARE(v1.to_base(-3),  v2.to_base(-3));
        QCOMPARE(v1.to_base(-4),  v2.to_base(-4));
        QCOMPARE(v1.to_base(-5),  v2.to_base(-5));
        QCOMPARE(v1.to_base(-6),  v2.to_base(-6));
        QCOMPARE(v1.to_base(-7),  v2.to_base(-7));
        QCOMPARE(v1.to_base(-8),  v2.to_base(-8));
        QCOMPARE(v1.to_base(-9),  v2.to_base(-9));
        QCOMPARE(v1.to_base(-10), v2.to_base(-10));
        QCOMPARE(v1.to_base(-11), v2.to_base(-11));
        QCOMPARE(v1.to_base(-12), v2.to_base(-12));
        QCOMPARE(v1.to_base(-13), v2.to_base(-13));
        QCOMPARE(v1.to_base(-14), v2.to_base(-14));
        QCOMPARE(v1.to_base(-15), v2.to_base(-15));
    }

private:

    static constexpr auto getConverterToN(int N)
    {
        return [N](int n)
        {
            nsc::nsc_number_t num = nsc::nsc_convert_toi(N, n);
            char buf[256];
            nsc::nsc_to_string(num, buf);
            free(num.buf);
            return std::string(buf);
        };
    }

    static constexpr auto getConverterFromN(int N)
    {
        return [N](std::string_view n)
        {
            std::remove_pointer_t<decltype(nsc::nsc_number_t::buf)> buf[256];
            nsc::nsc_number_t num;
            num.buf = buf;
            nsc::nsc_parse(&n.front(), &num);
            return nsc::nsc_convert_fromi(N, num);
        };
    }

private slots:

    void test_10_to_2_int()
    {
        constexpr auto from10to2 = getConverterToN(2);

        QCOMPARE(from10to2(0), "0");
        QCOMPARE(from10to2(1), "1");
        QCOMPARE(from10to2(2), "10");
        QCOMPARE(from10to2(3), "11");
        QCOMPARE(from10to2(4), "100");
        QCOMPARE(from10to2(5), "101");
        QCOMPARE(from10to2(6), "110");
        QCOMPARE(from10to2(7), "111");
        QCOMPARE(from10to2(8), "1000");

        QCOMPARE(from10to2(-0), "0");
        QCOMPARE(from10to2(-1), "-1");
        QCOMPARE(from10to2(-2), "-10");
        QCOMPARE(from10to2(-3), "-11");
        QCOMPARE(from10to2(-4), "-100");
        QCOMPARE(from10to2(-5), "-101");
        QCOMPARE(from10to2(-6), "-110");
        QCOMPARE(from10to2(-7), "-111");
        QCOMPARE(from10to2(-8), "-1000");
    }

    void test_10_to_16_int()
    {
        constexpr auto from10to2 = getConverterToN(16);

        QCOMPARE(from10to2(0), "0");
        QCOMPARE(from10to2(1), "1");
        QCOMPARE(from10to2(2), "2");
        QCOMPARE(from10to2(3), "3");
        QCOMPARE(from10to2(4), "4");
        QCOMPARE(from10to2(5), "5");
        QCOMPARE(from10to2(6), "6");
        QCOMPARE(from10to2(7), "7");
        QCOMPARE(from10to2(8), "8");
        QCOMPARE(from10to2(9), "9");
        QCOMPARE(from10to2(10), "A");
        QCOMPARE(from10to2(11), "B");
        QCOMPARE(from10to2(12), "C");
        QCOMPARE(from10to2(13), "D");
        QCOMPARE(from10to2(14), "E");
        QCOMPARE(from10to2(15), "F");
        QCOMPARE(from10to2(16), "10");
        QCOMPARE(from10to2(17), "11");

        QCOMPARE(from10to2(-0), "0");
        QCOMPARE(from10to2(-1), "-1");
        QCOMPARE(from10to2(-2), "-2");
        QCOMPARE(from10to2(-3), "-3");
        QCOMPARE(from10to2(-4), "-4");
        QCOMPARE(from10to2(-5), "-5");
        QCOMPARE(from10to2(-6), "-6");
        QCOMPARE(from10to2(-7), "-7");
        QCOMPARE(from10to2(-8), "-8");
        QCOMPARE(from10to2(-9), "-9");
        QCOMPARE(from10to2(-10), "-A");
        QCOMPARE(from10to2(-11), "-B");
        QCOMPARE(from10to2(-12), "-C");
        QCOMPARE(from10to2(-13), "-D");
        QCOMPARE(from10to2(-14), "-E");
        QCOMPARE(from10to2(-15), "-F");
        QCOMPARE(from10to2(-16), "-10");
        QCOMPARE(from10to2(-17), "-11");
    }

    void test_2_to_10_int()
    {
        constexpr auto from2to10 = getConverterFromN(2);

        QCOMPARE(from2to10("0"), 0);
        QCOMPARE(from2to10("1"), 1);
        QCOMPARE(from2to10("10"), 2);
        QCOMPARE(from2to10("11"), 3);
        QCOMPARE(from2to10("100"), 4);
        QCOMPARE(from2to10("101"), 5);
        QCOMPARE(from2to10("110"), 6);
        QCOMPARE(from2to10("111"), 7);
        QCOMPARE(from2to10("1000"), 8);

        QCOMPARE(from2to10("-0"), -0);
        QCOMPARE(from2to10("-1"), -1);
        QCOMPARE(from2to10("-10"), -2);
        QCOMPARE(from2to10("-11"), -3);
        QCOMPARE(from2to10("-100"), -4);
        QCOMPARE(from2to10("-101"), -5);
        QCOMPARE(from2to10("-110"), -6);
        QCOMPARE(from2to10("-111"), -7);
        QCOMPARE(from2to10("-1000"), -8);
    }
};

QTEST_MAIN(test_numeral_system_converter)
#include "numeral_system_converter.moc"
