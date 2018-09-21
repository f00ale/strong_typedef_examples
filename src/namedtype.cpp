
#include <utility>

#include <named_type.hpp>

template<typename T, typename Parameter, template<typename> class... Skills>
const T &
getValue(const ::fluent::NamedType<T, Parameter, Skills...> & nt)
noexcept(noexcept(nt.get()))
{ return nt.get(); }

template<typename T>
const T &
getValue(const T & t)
noexcept
{ return t; }

template<typename M>
struct MixedAddable {
    template<typename T>
    struct type : public ::fluent::crtp<T, type>{
        friend T operator+(type const & self, M const & other) { return T(self.underlying().get() + getValue(other)); }
        friend T operator+(M const & other, type const & self) { return T(getValue(other) + self.underlying().get()); }
    };
};

template<typename M>
struct MixedMultiplicable {
    template<typename T>
    struct type : public ::fluent::crtp<T, type>{
        friend T operator*(type const & self, M const & other) { return T(self.underlying().get() * getValue(other)); }
        friend T operator*(M const & other, type const & self) { return T(getValue(other) * self.underlying().get()); }
    };
};

template<typename M>
struct MixedDivision {
    template<typename T>
    struct type : public ::fluent::crtp<T, type>{
        friend T operator/(type const & self, M const & other) { return T(self.underlying().get() / getValue(other)); }
    };
};

template<typename M>
struct MixedModulus {
    template<typename T>
    struct type : public ::fluent::crtp<T, type>{
        friend T operator%(type const & self, M const & other) { return T(self.underlying().get() % getValue(other)); }
    };
};

template<typename M>
struct SubtractToType {
    template<typename T>
    struct type : public ::fluent::crtp<T, type> {
        friend M operator-(const type & t1, const type & t2) { return M(t1.underlying().get() - t2.underlying().get()); }
    };
};

template<typename T>
constexpr const auto getWrappedValue(const T & st) {
    return st.get();
}

// types

using namespace fluent;

using my_int = NamedType<int, struct my_int_tag, Printable, Addable, Subtractable, Multiplicable, Comparable>;

using offset = NamedType<int, struct offset_tag, Printable, Addable, Subtractable, MixedMultiplicable<int>::type>;
using position = NamedType<int, struct position_tag, Printable, MixedAddable<offset>::type, SubtractToType<offset>::type>;

using amount = NamedType<int, struct amount_tag, Printable, Comparable, Addable, Subtractable, MixedMultiplicable<int>::type, MixedDivision<int>::type, MixedModulus<int>::type>;
using price = NamedType<int, struct price_tag, Printable, Comparable, Addable, Subtractable, MixedMultiplicable<amount>::type>;

/*
template<typename T>
struct OffsetAddable : crtp<T, OffsetAddable> {
    T operator+(offset const &off) const { return T(this->underlying().get() + off.get()); }
    friend T operator+(offset const &off, T const & self) { return T(self.underlying().get() + off.get()); }
};
template<typename T>
struct SubtractToOffset : crtp<T, SubtractToOffset> {
    offset operator-(T const &other) const { return offset(this->underlying().get() - other.get()); }
    //friend offset operator-(T const &other) const { return offset(this->underlying().get() - other.get()); }
};

using position = NamedType<int, struct position_tag, Printable, OffsetAddable, SubtractToOffset>;
*/

#define LIBUNDERTEST namedtype
#include "common.cpp"
