#ifndef LIST_STRONG_TYPES_H
#define LIST_STRONG_TYPES_H

#include <ostream>

enum ConversionType {
    None,
    Explicit,
    Implicit
};

template <typename T, typename P, ConversionType CONVERSION = None>
class Type {
    T obj;
public:
    Type() = default;

    template<ConversionType USE = CONVERSION, std::enable_if_t<USE != Implicit, int> = 0>
    explicit Type(const T&& o): obj{o} {};

    template<ConversionType USE = CONVERSION, std::enable_if_t<USE == Implicit, int> = 0>
    Type(const T&& o): obj{o} {};

    template<ConversionType USE = CONVERSION, std::enable_if_t<USE != Implicit, int> = 0>
    explicit Type(const T& o): obj{o} {};

    template<ConversionType USE = CONVERSION, std::enable_if_t<USE == Implicit, int> = 0>
    Type(const T& o): obj{o} {};

    Type& operator=(const Type<T, P> &other) {
        if (&other == this) {
            return *this;
        }

        obj = other.obj;
        return *this;
    };

    template<ConversionType USE = CONVERSION, std::enable_if_t<USE == Explicit, int> = 0>
    explicit operator T() const {
        return obj;
    };

    template<ConversionType USE = CONVERSION, std::enable_if_t<USE == Implicit, int> = 0>
    operator T() const {
        return obj;
    };

    inline const T &get() const {
        return obj;
    };

    bool operator==(const Type &rhs) const {
        return obj == rhs.obj;
    }

    bool operator!=(const Type &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Type &rhs) const {
        return obj < rhs.obj;
    }

    bool operator>(const Type &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Type &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Type &rhs) const {
        return !(*this < rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Type &type) {
        os << type.obj;
        return os;
    }

    Type<T, P> operator+(const Type<T, P> &other) const {
        return Type<T, P>{obj+other.obj};
    };
};

#define STRONG_TYPE(name, type) using name = Type<type, struct Type##name>;
#define CONVERTIBLE_STRONG_TYPE(name, type) using name = Type<type, struct Type##name, Explicit>;
#define IMPLICIT_STRONG_TYPE(name, type) using name = Type<type, struct Type##name, Implicit>;

#endif //LIST_STRONG_TYPES_H
