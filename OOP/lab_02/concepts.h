#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>

template<typename T>
concept FloatingType = std::floating_point<T>;

template <typename T>
class MatrixRow;

template <typename T>
class Matrix;

template<template <typename U> class Container, typename T>
concept ContainerRequires = std::is_same_v<Container<T>, Matrix<T>> || std::is_same_v<Container<T>, MatrixRow<T>>;

#endif // CONCEPTS_H
