
static_assert(std::is_trivially_copy_constructible_v<my_int>);
static_assert(std::is_trivially_move_constructible_v<my_int>);
static_assert(std::is_trivially_copy_assignable_v<my_int>);
static_assert(std::is_trivially_move_assignable_v<my_int>);
static_assert(std::is_trivially_destructible_v<my_int>);
static_assert(std::is_nothrow_swappable_v<my_int>);

#define JOIN(x,y) x##y
#define FUNCNAME(x) JOIN(run_,x)

#define INNER(x) #x
#define TOSTR(x) INNER(x)

#include <iostream>

#ifndef LIBUNDERTEST
#error LIBUNDERTEST not defined
#endif

#include <cassert>

// inspired by cppreference.com -> void_t
template<typename, typename, typename, typename = std::void_t<>>
struct has_op : std::false_type {};
template<typename OP, typename T1, typename T2>
struct has_op<OP, T1, T2, std::void_t<decltype(OP()(std::declval<T1>(),std::declval<T2>()))>> : std::true_type {};

template<typename OP, typename T1, typename T2>
inline constexpr bool has_op_v = has_op<OP,T1,T2>::value;

template<typename OP, typename T1, typename T2, typename R>
inline constexpr bool has_op_result_v = std::is_same_v<R, decltype(OP()(std::declval<T1>(),std::declval<T2>()))>;

struct lshift {
    template<typename T1, typename T2>
    auto && operator()(T1 && t1, T2 && t2) {
        return std::forward<T1>(t1) << std::forward<T2>(t2);
    }
};

namespace {
int test_add_ints(const my_int & i1, const my_int & i2) {
    auto ret = getWrappedValue(i1+i2);
    static_assert(std::is_same_v<decltype(ret),int>);
    return ret;
}


void test_my_int() {
    static_assert(has_op_result_v<std::plus<>, my_int, my_int, my_int>);
    static_assert(!has_op_v<std::plus<>, my_int, int>);

    static_assert(has_op_v<std::plus<>, my_int, my_int>);
    static_assert(has_op_v<std::minus<>, my_int, my_int>);
    static_assert(has_op_v<std::multiplies<>, my_int, my_int>);
    //static_assert(has_op_v<std::divides<>, my_int, my_int>);
    //static_assert(has_op_v<std::modulus<>, my_int, my_int>);

    static_assert(has_op_v<std::equal_to<>, my_int, my_int>);
    static_assert(has_op_v<std::not_equal_to<>, my_int, my_int>);
    static_assert(has_op_v<std::less<>, my_int, my_int>);
    static_assert(has_op_v<std::greater<>, my_int, my_int>);
    static_assert(has_op_v<std::less_equal<>, my_int, my_int>);
    static_assert(has_op_v<std::greater_equal<>, my_int, my_int>);


    static_assert(has_op_result_v<lshift, std::ostream&, my_int, std::ostream&>);

    my_int i1(0);
    my_int i2(3);

    auto i3 = i1 + i2;
    static_assert(std::is_same_v<decltype(i3),my_int>);

    std::cout << i3 << std::endl;
    // not all libs constexpr, so "usual" assert
    assert(my_int(5)+my_int(7) == my_int(12));

    assert(test_add_ints(my_int(3), my_int(5)) == 8);

    my_int i4{7};
    auto ii4 = getWrappedValue(i4);
    static_assert(std::is_same_v<decltype(ii4), int>);
    assert(ii4 == 7);

    }

    void test_position_offset() {
        static_assert(has_op_v<std::plus<>, offset, offset>);
        static_assert(has_op_v<std::minus<>, offset, offset>);
        static_assert(has_op_result_v<std::plus<>, offset, offset, offset>);
        static_assert(has_op_result_v<std::minus<>, offset, offset, offset>);

        static_assert(has_op_v<std::multiplies<>, offset, int>);
        static_assert(has_op_v<std::multiplies<>, int, offset>);
        static_assert(has_op_result_v<std::multiplies<>, offset, int, offset>);
        static_assert(has_op_result_v<std::multiplies<>, int, offset, offset>);

        static_assert(!has_op_v<std::plus<>, position, position>);
        static_assert(has_op_v<std::plus<>, position, offset>);
        static_assert(has_op_v<std::plus<>, offset, position>);
        static_assert(has_op_result_v<std::plus<>, position, offset, position>);
        static_assert(has_op_result_v<std::plus<>, offset, position, position>);

        static_assert(has_op_v<std::minus<>, position, position>);
        static_assert(has_op_result_v<std::minus<>, position, position, offset>);

        position p1(2);
        offset o1(3);

        std::cout << p1 << " + " << o1 << " -> " << (p1+o1) << std::endl;

        auto o2 = position(5) - position(3);

        static_assert(std::is_same_v<decltype(o2), offset>);

        std::cout << (p1+o2) << std::endl;


        {
            position p1(7);
            auto o = p1 - position(2);
            auto p3 = p1 + o;

            //auto pe = position(3) + position(4);

            static_assert(std::is_same_v<decltype(o), offset>);
            static_assert(std::is_same_v<decltype(p3), position>);
        }
    }


    void test_price_amount() {
        static_assert(has_op_v<std::plus<>, amount, amount>);
        static_assert(has_op_v<std::plus<>, price, price>);

        static_assert(has_op_v<std::minus<>, amount, amount>);
        static_assert(has_op_v<std::minus<>, price, price>);

        static_assert(has_op_v<std::multiplies<>, amount, price>);
        static_assert(has_op_v<std::multiplies<>, price, amount>);
        static_assert(has_op_result_v<std::multiplies<>, price, amount, price>);

        static_assert(has_op_v<std::multiplies<>, int, amount>);
        static_assert(has_op_v<std::multiplies<>, amount, int>);
        static_assert(!has_op_v<std::multiplies<>, amount, amount>);

        static_assert(has_op_v<std::modulus<>, amount, int>);
        static_assert(has_op_v<std::divides<>, amount, int>);

        amount a5(5);
        price p7(7);

        auto p1 = a5 * p7;
        assert(p1 == price(35));

        auto p2 = ((a5 / 4) * 3 + a5 % 4) * p7;
        assert(p2 == price(28));

        assert(a5 == amount(5));
        assert(p7 == price(7));
    }
}

void FUNCNAME(LIBUNDERTEST) () {
    std::cout << TOSTR(LIBUNDERTEST) << std::endl;

    test_my_int();
    test_position_offset();
    test_price_amount();
}
