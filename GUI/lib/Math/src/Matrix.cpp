/*
** EPITECH PROJECT, 2024
** Matrix.cpp
** File description:
** math
*/

#include "Matrix.hpp"

math::Matrix::Matrix(int x, int y) : matrix(std::vector<std::vector<double>>(x, std::vector<double>(y, 0))) {};
math::Matrix::Matrix(const math::Matrix &other) : matrix(other.matrix) {}

math::Matrix::~Matrix() {}


math::Matrix math::Matrix::operator*(const math::Matrix &other) const
{
    if (sizeY() != other.sizeX())
        throw Error("Matrix::operator* : Invalid matrix size");

    Matrix result(sizeX(), other.sizeY());

    for (std::size_t i = 0; i < sizeX(); i++) {
        for (std::size_t j = 0; j < other.sizeY(); j++) {
            double sum = 0;
            for (std::size_t k = 0; k < sizeY(); k++) {
                sum += get(i, k) * other.get(k, j);
            }
            result.set(i, j, sum);
        }
    }

    return result;
}

math::Matrix math::Matrix::operator+(const math::Matrix &other) const
{
    if (sizeX() != other.sizeX() || sizeY() != other.sizeY())
        throw Error("Matrix::operator+ : Invalid matrix size");

    Matrix result(sizeX(), sizeY());

    for (std::size_t i = 0; i < sizeX(); i++) {
        for (std::size_t j = 0; j < sizeY(); j++) {
            result.set(i, j, get(i, j) + other.get(i, j));
        }
    }

    return result;
}

math::Matrix math::Matrix::operator-(const math::Matrix &other) const
{
    if (sizeX() != other.sizeX() || sizeY() != other.sizeY())
        throw Error("Matrix::operator- : Invalid matrix size");

    Matrix result(sizeX(), sizeY());

    for (std::size_t i = 0; i < sizeX(); i++) {
        for (std::size_t j = 0; j < sizeY(); j++) {
            result.set(i, j, get(i, j) - other.get(i, j));
        }
    }

    return result;
}

math::Matrix math::Matrix::operator*(double value) const
{
    Matrix result(sizeX(), sizeY());

    for (std::size_t i = 0; i < sizeX(); i++) {
        for (std::size_t j = 0; j < sizeY(); j++) {
            result.set(i, j, get(i, j) * value);
        }
    }

    return result;
}

math::Matrix math::Matrix::operator/(double value) const
{
    if (value == 0)
        throw Error("Matrix::operator/ : Division by zero");

    Matrix result(sizeX(), sizeY());

    for (std::size_t i = 0; i < sizeX(); i++) {
        for (std::size_t j = 0; j < sizeY(); j++) {
            result.set(i, j, get(i, j) / value);
        }
    }

    return result;
}

math::Matrix math::Matrix::operator=(const math::Matrix &other)
{
    matrix = other.matrix;
    return *this;
}

math::Matrix math::Matrix::operator=(const std::vector<std::vector<double>> &other)
{
    matrix = other;
    return *this;
}

math::Matrix math::Matrix::transpose()
{
    Matrix transposed(sizeY(), sizeX());

    for (std::size_t i = 0; i < sizeX(); i++) {
        for (std::size_t j = 0; j < sizeY(); j++) {
            transposed.set(j, i, get(i, j));
        }
    }

    return transposed;
}

std::vector<double> &math::Matrix::operator[](std::size_t index)
{
    if (index >= sizeX())
        throw Error("Matrix::operator[] : Index out of range");

    return matrix[index];
}

std::size_t math::Matrix::sizeX() const
{
    return matrix.size();
}

std::size_t math::Matrix::sizeY() const
{
    return matrix[0].size();
}

double math::Matrix::get(int x, int y) const
{
    return matrix[x][y];
}

void math::Matrix::set(int x, int y, double value)
{
    matrix[x][y] = value;
}

math::Matrix::Matrix(std::vector<std::vector<double>> &matrix) : matrix(matrix) {}


math::Matrix transposeMatrix(const math::Matrix& matrix) {
    math::Matrix transposed(3, 3);
    for (std::size_t i = 0; i < 3; i++) {
        for (std::size_t j = 0; j < 3; j++) {
            transposed.set(j, i, matrix.get(i, j));
        }
    }
    return transposed;
}