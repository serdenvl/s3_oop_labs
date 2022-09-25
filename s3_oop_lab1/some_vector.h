#pragma once

#include <iostream>
#include <string>

namespace some_namespace {

    class some_vector
    {
    private:
        double x, y, z;


    public:
        some_vector(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z)
        {
            std::cout << "Constructor"
                << " "
                << "[" << this << "]"
                << " "
                << "vector(" << x << " : " << y << " : " << z << ")"
                << std::endl;
        }

        some_vector(const some_vector& it) : x(it.get_x()), y(it.get_y()), z(it.get_z())
        {
            std::cout << "Constructor"
                << " "
                << "[" << this << "]"
                << " "
                << "vector(" << &it << ")"
                << std::endl;
        }

        ~some_vector()
        {
            std::cout << "Destructor"
                << " "
                << "[" << this << "]"
                << " "
                << "vector"
                << std::endl;
        }

        some_vector operator=(const some_vector&) const;

        double get_x() const;
        double get_y() const;
        double get_z() const;

        void set_x(double val);
        void set_y(double val);
        void set_z(double val);

        double len() const;

        some_vector copy() const;

        some_vector scalar_prod(double a) const;

        some_vector norm() const;
    };

    some_vector sum_vectors(const some_vector& a, const some_vector& b);

    some_vector sub_vectors(const some_vector& a, const some_vector& b);

    some_vector prod_vectors(const some_vector& a, const some_vector& b);

    double scalar_prod_vectors(const some_vector& a, const some_vector& b);

    double cos_between_vectors(const some_vector& a, const some_vector& b);

    double sin_between_vectors(const some_vector& a, const some_vector& b);

    double angle_between_vectors(const some_vector& a, const some_vector& b);

}