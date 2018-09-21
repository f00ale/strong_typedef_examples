#include <strong_type.hpp>

struct self;

template <typename T, typename Tag, typename ... M>
const T & getValue(const strong::type<T, Tag, M...> & t) {
    return t.value_of();
};

template<typename T>
const T & getValue(const T & t) {return t;}

template<typename M>
struct mixed_addition {
    template<typename T>
    struct modifier {
        using O = std::conditional_t<std::is_same_v<M,self>, T, M>;
        STRONG_NODISCARD
        friend
        constexpr
        T
        operator+(const T &lh, const O &rh)
        {
            return T(value_of(lh)+value_of(rh));
        }

        template<bool cond = !std::is_same_v<O, T>>
        STRONG_NODISCARD
        friend
        constexpr
        std::enable_if_t<cond, T>
        operator+(const O &lh, const T &rh)
        {
            return T(value_of(lh)+value_of(rh));
        }
    };
};

template<typename M>
struct mixed_subtraction {
    template<typename T>
    struct modifier {
        using O = std::conditional_t<std::is_same_v<M,self>, T, M>;
        STRONG_NODISCARD
        friend
        constexpr
        T
        operator-(const T &lh, const O &rh)
        {
            return T(value_of(lh)-value_of(rh));
        }

        template<bool cond = !std::is_same_v<O, T>>
        STRONG_NODISCARD
        friend
        constexpr
        std::enable_if_t<cond, T>
        operator-(const O &lh, const T &rh)
        {
            return T(value_of(lh)-value_of(rh));
        }
    };
};

template<typename M>
struct mixed_multiplication {
    template<typename T>
    struct modifier {
        using O = std::conditional_t<std::is_same_v<M,self>, T, M>;
        STRONG_NODISCARD
        friend
        constexpr
        T
        operator*(const T &lh, const O &rh)
        {
            return T(getValue(lh)*getValue(rh));
        }

        template<bool cond = !std::is_same_v<O, T>>
        STRONG_NODISCARD
        friend
        constexpr
        std::enable_if_t<cond, T>
        operator*(const O &lh, const T &rh)
        {
            return T(getValue(lh)*getValue(rh));
        }
    };
};

template<typename M>
struct mixed_division {
    template<typename T>
    struct modifier {
        using O = std::conditional_t<std::is_same_v<M, self>, T, M>;

        STRONG_NODISCARD
        friend
        constexpr
        T
        operator/(const T &lh, const O &rh) {
            return T(getValue(lh) / getValue(rh));
        }

    };
};

template<typename M>
struct mixed_modulus {
    template<typename T>
    struct modifier {
        using O = std::conditional_t<std::is_same_v<M, self>, T, M>;

        STRONG_NODISCARD
        friend
        constexpr
        T
        operator%(const T &lh, const O &rh) {
            return T(getValue(lh) % getValue(rh));
        }

    };
};

template<typename M>
struct subtract_to_type {
    template<typename T>
    struct modifier {
        STRONG_NODISCARD
        friend
        constexpr
        M
        operator-(const T &lh, const T &rh)
        {
            return M(value_of(lh)-value_of(rh));
        }
    };
};


template<typename T>
constexpr const auto getWrappedValue(const T & st) {
    return st.value_of();
}

using namespace strong;

using my_int = type<int, struct my_int_tag, ostreamable, arithmetic, ordered>;

using offset = type<int, struct offset_tag, ostreamable, arithmetic, mixed_multiplication<int>>;

using position = type<int, struct position_tag, ostreamable, mixed_addition<offset>, subtract_to_type<offset>>;

using amount = type<int, struct amount_tag, ostreamable, mixed_addition<self>, mixed_subtraction<self>, mixed_multiplication<int>, mixed_division<int>, mixed_modulus<int>>;
using price = type<int, struct price_tag, ostreamable, mixed_addition<self>, mixed_subtraction<self>, mixed_multiplication<amount>>;

#define LIBUNDERTEST strong_type
#include "common.cpp"
