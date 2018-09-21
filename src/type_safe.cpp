#include <type_safe/strong_typedef.hpp>

template<typename StrongTypeArg, typename ResultType>
struct subtract_to_type {
    friend
    constexpr
    ResultType
    operator-(const StrongTypeArg & a1, const StrongTypeArg & a2)
    noexcept(noexcept(ResultType(::type_safe::get(a1)-::type_safe::get(a2))))
    {
        return ResultType(::type_safe::get(a1)-::type_safe::get(a2));
    }
};

template<typename T>
constexpr const auto getWrappedValue(const T & st) {
    return ::type_safe::get(st);
}

using namespace type_safe;

struct my_int : public strong_typedef<my_int, int>
        , public strong_typedef_op::output_operator<my_int>
        , public strong_typedef_op::integer_arithmetic<my_int>
        , public strong_typedef_op::equality_comparison<my_int>
        , public strong_typedef_op::relational_comparison<my_int>
{
    using strong_typedef::strong_typedef;
};

struct offset : public strong_typedef<offset, int>
        , public strong_typedef_op::output_operator<offset>
        , public strong_typedef_op::addition<offset>
        , public strong_typedef_op::subtraction<offset>
        , public strong_typedef_op::mixed_multiplication<offset, int>
{
    using strong_typedef::strong_typedef;
};

struct position : public strong_typedef<position, int>
        , public strong_typedef_op::output_operator<position>
        , public strong_typedef_op::mixed_addition<position, offset>
        , public strong_typedef_op::mixed_subtraction<position, offset>
        , public subtract_to_type<position, offset>
{
    using strong_typedef::strong_typedef;
};

struct amount : public strong_typedef<amount, int>
        , public strong_typedef_op::addition<amount>
        , public strong_typedef_op::subtraction<amount>
        , public strong_typedef_op::equality_comparison<amount>
        , public strong_typedef_op::mixed_multiplication<amount,int>
        , public strong_typedef_op::mixed_division<amount,int>
        , public strong_typedef_op::mixed_modulo<amount, int>
{
    using strong_typedef::strong_typedef;
};

struct price : public strong_typedef<price, int>
        , public strong_typedef_op::addition<price>
        , public strong_typedef_op::subtraction<price>
        , public strong_typedef_op::mixed_multiplication<price, amount>
        , public strong_typedef_op::equality_comparison<price>
{
    using strong_typedef::strong_typedef;
};

#define LIBUNDERTEST type_safe
#include "common.cpp"
