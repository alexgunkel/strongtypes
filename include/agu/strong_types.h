#ifndef LIST_STRONG_TYPES_H
#define LIST_STRONG_TYPES_H

#include <ostream>

namespace agu {
    enum class ConversionType {
        None,
        Explicit,
        Implicit
    };

    template<typename T, typename P, ConversionType CONVERSION = ConversionType::None>
    class Type {
        T obj;
    public:
        Type() = default;

        Type(const Type &other) = default;

        template<ConversionType USE = CONVERSION, std::enable_if_t<USE != ConversionType::Implicit, int> = 0>
        constexpr explicit Type(const T &&o) noexcept : obj{o} {};

        template<ConversionType USE = CONVERSION, std::enable_if_t<USE == ConversionType::Implicit, int> = 0>
        constexpr Type(const T &&o) noexcept : obj{o} {};

        template<ConversionType USE = CONVERSION, std::enable_if_t<USE != ConversionType::Implicit, int> = 0>
        constexpr explicit Type(const T &o) noexcept : obj{o} {};

        template<ConversionType USE = CONVERSION, std::enable_if_t<USE == ConversionType::Implicit, int> = 0>
        constexpr Type(const T &o) noexcept : obj{o} {};

        Type &operator=(const Type<T, P> &other) noexcept {
            if (&other == this) {
                return *this;
            }

            obj = other.obj;
            return *this;
        };

        template<ConversionType USE = CONVERSION, std::enable_if_t<USE == ConversionType::Explicit, int> = 0>
        explicit operator T() const noexcept {
            return obj;
        };

        template<ConversionType USE = CONVERSION, std::enable_if_t<USE == ConversionType::Implicit, int> = 0>
        operator T() const noexcept {
            return obj;
        };

        inline const T &get() const noexcept {
            return obj;
        };

        bool operator==(const Type &rhs) const noexcept {
            return obj == rhs.obj;
        }

        bool operator!=(const Type &rhs) const noexcept {
            return !(rhs == *this);
        }

        bool operator<(const Type &rhs) const noexcept {
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

        friend std::istream &operator>>(std::istream &is, Type &type) {
            is >> type;
            return is;
        }

        constexpr Type<T, P> operator+(const Type<T, P> &other) const {
            return Type<T, P>{obj + other.obj};
        };

        template <class Integer, std::enable_if_t< std::is_integral_v<Integer>>* = nullptr >
        friend constexpr Type<T, P> operator*(const Type<T, P> &left, const Integer &right) {
            auto result = left;
            for (Integer i = 1; i < right; ++i) {
                result.obj += left.obj;
            }

            return result;
        };

        template <class Integer, std::enable_if_t< std::is_integral_v<Integer>>* = nullptr >
        friend constexpr Type<T, P> operator*(const Integer &left, const Type<T, P> &right) {
            auto result = right;
            for (Integer i = 1; i < left; ++i) {
                result.obj += right.obj;
            }

            return result;
        };
    };

    template<class S, class T, class ... Args>
    static constexpr S emplace(Args&&... args) {
        return S(T(std::forward<Args>(args) ...));
    };
}

#define STRONG_TYPE(name, type) using name = ::agu::Type<type, struct Type##name>;
#define CONVERTIBLE_STRONG_TYPE(name, type) using name = ::agu::Type<type, struct Type##name, ::agu::ConversionType::Explicit>;
#define IMPLICIT_STRONG_TYPE(name, type) using name = ::agu::Type<type, struct Type##name, ::agu::ConversionType::Implicit>;

#endif
