#include "some_vector.h"

#include <iostream>
using namespace std;

#define _USE_MATH_DEFINES
#include <math.h>

#include <string>
#include <sstream>

namespace some_namespace {

    double some_vector::get_x() const { return x; }
    double some_vector::get_y() const { return y; }
    double some_vector::get_z() const { return z; }

    void some_vector::set_x(double val) { x = val; }
    void some_vector::set_y(double val) { y = val; }
    void some_vector::set_z(double val) { z = val; }

    some_vector some_vector::operator=(const some_vector& other) const
    {
        return some_vector(other);
    }

    some_vector::operator std::string() const
    {
        return (stringstream() 
            << "some_vector" 
            << "[" << this << "]" 
            << "(x = " << x << ", y = " << y << ", z = " << z << ")"
            ).str();
    }

    double some_vector::len() const
    {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }

    some_vector some_vector::copy() const
    {
        return some_vector(*this);
    }

    some_vector some_vector::scalar_prod(double a) const
    {
        return some_vector(x * a, y * a, z * a);
    }

    some_vector some_vector::norm() const
    {
        return scalar_prod(1 / len());
    }

    some_vector sum_vectors(const some_vector& a, const some_vector& b)
    {
        return some_vector(a.get_x() + b.get_x(), a.get_y() + b.get_y(), a.get_z() + b.get_z());
    }

    some_vector sub_vectors(const some_vector& a, const some_vector& b)
    {
        return some_vector(a.get_x() - b.get_x(), a.get_y() - b.get_y(), a.get_z() - b.get_z());
    }

    some_vector prod_vectors(const some_vector& a, const some_vector& b)
    {
        double comps_a[3] = { a.get_y(), a.get_z(), a.get_x() };
        double comps_b[3] = { b.get_y(), b.get_z(), b.get_x() };

        double buf[3];
        for (int i = 0; i < 3; ++i)
        {
            buf[i] = comps_a[i] * comps_b[(i + 1) % 3] - comps_a[(i + 1) % 3] * comps_b[i];
        }

        return some_vector(*buf);
    }

    double scalar_prod_vectors(const some_vector& a, const some_vector& b)
    {
        double comps_a[3] = { a.get_x(), a.get_y(), a.get_z() };
        double comps_b[3] = { b.get_x(), b.get_y(), b.get_z() };

        double res = 0.0;
        for (int i = 0; i < 3; ++i)
            res += comps_a[i] * comps_b[i];

        return res;
    }

    double cos_between_vectors(const some_vector& a, const some_vector& b)
    {
        double comps_a[3] = { a.get_x(), a.get_y(), a.get_z() };
        double comps_b[3] = { b.get_x(), b.get_y(), b.get_z() };

        double prod = 0.0;
        for (int i = 0; i < 3; ++i)
        {
            prod += comps_a[i] * comps_b[i];
        }

        return prod / (a.len() * b.len());
    }

    double sin_between_vectors(const some_vector& a, const some_vector& b)
    {
        return sqrt(1 - pow(cos_between_vectors(a, b), 2));
    }

    double angle_between_vectors(const some_vector& a, const some_vector& b)
    {
        double get_x = cos_between_vectors(a, b);
        double get_y = sin_between_vectors(a, b);
        return atan2(get_y, get_x) * 180 / M_PI;
    }
}