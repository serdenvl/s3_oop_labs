#pragma once
#include <iostream>

namespace some_namespace {

    class some_vector
    {
    private:
        size_t id;
        double x, y, z;


    public:
        some_vector(double x = 0.0, double y = 0.0, double z = 0.0);

        some_vector(const some_vector& other);

        ~some_vector();

        friend std::ostream& operator<<(std::ostream& output, const some_vector& it);

        some_vector& operator=(const some_vector&);

        double get_x() const;
        double get_y() const;
        double get_z() const;

        void set_x(double val);
        void set_y(double val);
        void set_z(double val);

        double len() const;

        some_vector& scalar_prod(double a);

        some_vector& norm();
    };

    some_vector sum_vectors(const some_vector& a, const some_vector& b);

    some_vector sub_vectors(const some_vector& a, const some_vector& b);

    some_vector prod_vectors(const some_vector& a, const some_vector& b);

    double scalar_prod_vectors(const some_vector& a, const some_vector& b);

    double cos_between_vectors(const some_vector& a, const some_vector& b);

    double sin_between_vectors(const some_vector& a, const some_vector& b);

    double angle_between_vectors(const some_vector& a, const some_vector& b);

}