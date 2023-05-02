#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>

template<typename T>
concept FloatingType = std::floating_point<T> || std::integral<T>;

template <typename T>
class MatrixRow;

template <typename T>
class Matrix;

template<template <typename> class Container, typename Class_T, typename T = Class_T>
concept ContainerRequires = std::is_same_v<Container<T>, MatrixRow<T>> || std::is_same_v<Container<Class_T>, Matrix<Class_T>>;

#endif // CONCEPTS_H
