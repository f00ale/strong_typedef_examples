#include <stype.h>

template<typename T>
constexpr const auto getWrappedValue(const T & st) {
    return st.get();
}

using namespace stype;

using my_int = type<int, struct my_int_tag, outputable, equality_compareable<>, compareable<>, add<>, sub<>, multiply<>>;

using offset = type<int, struct offset_tag, outputable, add<>, multiply<self, int>, sub<>>;
using position = type<int, struct position_tag, outputable, add<self, offset>, sub<offset>>;

using amount = type<int, struct amount_tag, outputable, equality_compareable<>, add<>, sub<>, multiply<self,int>, divide<self,self,int>, modulus<self,self,int>>;
using price = type<int, struct amount_tag, outputable, equality_compareable<>, add<>, sub<>, multiply<self,amount>>;

#define LIBUNDERTEST stype
#include "common.cpp"
