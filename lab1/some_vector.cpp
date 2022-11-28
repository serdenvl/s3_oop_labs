#include "some_vector.h"

#include <iostream>
using namespace std;

#define _USE_MATH_DEFINES
#include <math.h>

#include <string>
#include <sstream>

static size_t ID = 0;

namespace some_namespace {

    double some_vector::get_x() const { return x; }
    double some_vector::get_y() const { return y; }
    double some_vector::get_z() const { return z; }

    void some_vector::set_x(double val) { x = val; }
    void some_vector::set_y(double val) { y = val; }
    void some_vector::set_z(double val) { z = val; }

    some_vector::some_vector(double x, double y, double z) : x(x), y(y), z(z), id(++ID)
    {
        std::cout << "Constructor"
            << " "
            << "vector(" << x << ":" << y << ":" << z << ")"
            << " "
            << "[" << "#" << id << " | " << this << "]"
            << std::endl;
    }

    some_vector::some_vector(const some_vector& other) : x(other.x), y(other.y), z(other.z), id(++ID)
    {
        std::cout << "Constructor"
            << " "
            << "vector(" << "#" << id << " | " << &other << ")"
            << " "
            << "[" << "#" << id << " | " << this << "]"
            << std::endl;
    }

    some_vector::~some_vector()
    {
        std::cout << "Destructor"
            << " "
            << "vector"
            << " "
            << "[" << "#" << id << " | " << this << "]"
            << std::endl;
    }

    some_vector& some_vector::operator=(const some_vector& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    double some_vector::len() const
    {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }

    some_vector& some_vector::scalar_prod(double a)
    {
        x *= a; 
        y *= a; 
        z *= a; 
        return *this;
    }

    some_vector& some_vector::norm()
    {
        return scalar_prod(1 / len());
    }

    std::ostream& operator<<(std::ostream& output, const some_vector& it)
    {
        return output << it.x << " " << it.y << " " << it.z;
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
        double comps_a[3] = { a.get_x(), a.get_y(), a.get_z() };
        double comps_b[3] = { b.get_x(), b.get_y(), b.get_z() };

        double buf[3];
        for (size_t i = 0; i < 3; ++i)
            buf[i] = comps_a[(i + 1) % 3] * comps_b[(i + 2) % 3] - comps_a[(i + 2) % 3] * comps_b[(i + 1) % 3];
        
        return some_vector(buf[0], buf[1], buf[2]);
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
        double x_ = cos_between_vectors(a, b);
        double y_ = sin_between_vectors(a, b);
        return atan2(y_, x_) * 180 / M_PI;
    }
}