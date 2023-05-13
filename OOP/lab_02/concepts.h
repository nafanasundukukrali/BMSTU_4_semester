#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>
#include <iterator>

template<typename T>
concept MatrixType = requires (T a) {
    std::copyable<T>;
    std::equality_comparable<T>;
    { a + a } -> std::convertible_to<T>;
    { a * a } -> std::convertible_to<T>;
    { a - a } -> std::convertible_to<T>;
    { a / a } -> std::convertible_to<T>;
};

template<typename T, typename U>
concept FriendlyRange = requires(U &u) {
    { u.begin() } -> std::input_iterator;
    { u.end() } -> std::sentinel_for<decltype(u.begin())>;
    std::constructible_from<T, typename std::iterator_traits<decltype(u.begin())>::reference>;
};

template<typename T, typename U>
concept SumType = requires(T &t, U &u) {
    {t + u} -> std::convertible_to<T>;
};

template <MatrixType T>
class MatrixRow;

template <MatrixType T>
class Matrix;

template<template <typename> class Container, typename Class_T, typename T = Class_T>
concept ContainerRequires = std::is_same_v<Container<T>, MatrixRow<T>>
                            || std::is_same_v<Container<Class_T>, Matrix<Class_T>>;


#endif // CONCEPTS_H
