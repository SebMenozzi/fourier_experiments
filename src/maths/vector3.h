#pragma once

#include <cmath>
#include <iostream>

namespace maths
{
    class Vector3
    {
        public:
            Vector3(): _data{0, 0, 0} {}

            Vector3(const double x, const double y, const double z)
            {
                _data[0] = x;
                _data[1] = y;
                _data[2] = z;
            }

            Vector3(const double e)
            {
                _data[0] = e;
                _data[1] = e;
                _data[2] = e;
            }

            inline double x() const
            {
                return _data[0];
            }

            inline double y() const
            {
                return _data[1];
            }

            inline double z() const
            {
                return _data[2];
            }

            inline Vector3 operator-() const
            {
                return Vector3(-x(), -y(), -z());
            }

            inline double operator[](std::size_t i) const
            {
                return _data[i];
            }

            inline double& operator[](std::size_t i)
            {
                return _data[i];
            };

            inline bool operator==(const Vector3 &v)
            {
                return (x() == v.x() && y() == v.y() && z() == v.z());
            }

            // ?= operator with vector
            inline Vector3& operator+=(const Vector3 &v);
            inline Vector3& operator-=(const Vector3 &v);
            inline Vector3& operator*=(const Vector3 &v);
            inline Vector3& operator/=(const Vector3 &v);

            // ?= operator with scalar
            inline Vector3& operator+=(const double e);
            inline Vector3& operator-=(const double e);
            inline Vector3& operator*=(const double e);
            inline Vector3& operator/=(const double e);

            // Other useful methods
            inline double squared_length() const;
            inline double length() const;
            inline Vector3 unit_vector() const;
            inline bool near_zero() const;

            // Static methods
            inline static double dot_product(const Vector3 &v1, const Vector3 &v2);
            inline static Vector3 cross_product(const Vector3 &v1, const Vector3 &v2);

        private:
            double _data[3];
    };

    // Operator vector & scalar

    inline Vector3 operator+(const Vector3 &v, const double e)
    {
        return Vector3(v.x() + e, v.y() + e, v.z() + e);
    }
    inline Vector3 operator+(const double e, const Vector3 &v)
    {
        return v + e;
    }

    inline Vector3 operator-(const Vector3 &v, const double e)
    {
        return v + (-e);
    }
    inline Vector3 operator-(const double e, const Vector3 &v)
    {
        return v - e;
    }

    inline Vector3 operator*(const Vector3 &v, const double e)
    {
        return Vector3(v.x() * e, v.y() * e, v.z() * e);
    }
    inline Vector3 operator*(const double e, const Vector3 &v)
    {
        return v * e;
    }

    inline Vector3 operator/(const Vector3 &v, const double e)
    {
        return Vector3(v.x() / e, v.y() / e, v.z() / e);
    }
    inline Vector3 operator/(const double e, const Vector3 &v)
    {
        return Vector3(e / v.x(), e / v.y(), e / v.z());
    }

    // Operator vector & vector

    inline Vector3 operator+(const Vector3 &v1, const Vector3 &v2)
    {
        return Vector3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
    }

    inline Vector3 operator-(const Vector3 &v1, const Vector3 &v2)
    {
        return v1 + (-v2);
    }

    inline Vector3 operator*(const Vector3 &v1, const Vector3 &v2)
    {
        return Vector3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
    }

    inline Vector3 operator/(const Vector3 &v1, const Vector3 &v2)
    {
        return v1 * (1 / v2);
    }

    // Operator ?= with vector

    inline Vector3& Vector3::operator+=(const Vector3 &v)
    {
        _data[0] += v.x();
        _data[1] += v.y();
        _data[2] += v.z();

        return *this;
    }
    inline Vector3& Vector3::operator-=(const Vector3 &v)
    {
        return *this += -v;
    }
    inline Vector3& Vector3::operator*=(const Vector3 &v)
    {
        _data[0] *= v.x();
        _data[1] *= v.y();
        _data[2] *= v.z();

        return *this;
    }
    inline Vector3& Vector3::operator/=(const Vector3 &v)
    {
        return *this *= 1.0 / v;
    }

    // Operator ?= with scalar

    inline Vector3& Vector3::operator+=(const double e)
    {
        _data[0] += e;
        _data[1] += e;
        _data[2] += e;

        return *this;
    }
    inline Vector3& Vector3::operator-=(const double e)
    {
        return *this += -e;
    }
    inline Vector3& Vector3::operator*=(const double e)
    {
        _data[0] *= e;
        _data[1] *= e;
        _data[2] *= e;

        return *this;
    }
    inline Vector3& Vector3::operator/=(const double e)
    {
        return *this *= 1 / e;
    }

    // Useful methods

    inline double Vector3::squared_length() const
    {
        return x() * x() + y() * y() + z() * z();
    }
    inline double Vector3::length() const
    {
        return std::sqrt(squared_length());
    }
    inline Vector3 Vector3::unit_vector() const
    {
        return (*this) / length();
    }
    inline bool Vector3::near_zero() const
    {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;

        return (fabs(x()) < s && fabs(y()) < s && fabs(z()) < s);
    }

    // Static methods

    inline double Vector3::dot_product(const Vector3 &v1, const Vector3 &v2)
    {
        return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
    }
    inline Vector3 Vector3::cross_product(const Vector3 &v1, const Vector3 &v2)
    {
        return Vector3(
            (v1.y() * v2.z() - v1.z() * v2.y()),
            -(v1.x() * v2.z() - v1.z() * v2.x()),
            (v1.x() * v2.y() - v1.y() * v2.x())
        );
    }
}