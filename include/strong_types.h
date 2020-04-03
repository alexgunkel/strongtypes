#ifndef LIST_STRONG_TYPES_H
#define LIST_STRONG_TYPES_H

#include <ostream>

template <typename T, typename P>
class Type {
    T obj;
public:
    Type() = default;
    explicit Type(const T&& o): obj{o} {};
    explicit Type(const T& o): obj{o} {};

    Type<T, P> &operator=(const Type<T, P> &other) {
        if (&other == this) {
            return *this;
        }

        obj = other.obj;
        return *this;
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
        os << "obj: " << type.obj;
        return os;
    }

    Type<T, P> operator+(const Type<T, P> &other) const {
        return Type<T, P>{obj+other.obj};
    };
};

#define STRONG_TYPE(name, type) using name = Type<type, struct Type##name>;

#endif //LIST_STRONG_TYPES_H
