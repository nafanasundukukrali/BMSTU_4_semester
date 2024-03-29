#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>
#include <iterator>

template<typename T>
concept MatrixType = requires {
    std::semiregular<T>;
};

template<typename T, typename U>
concept FriendlyMatrixType = requires {
    std::constructible_from<U, T>;
};

template<typename T>
concept MatrixEqualityOperationRequires = requires {
    MatrixType<T>;
    std::equality_comparable<T>;
};

template<typename T, typename U>
concept MatrixSumOperationRequires = requires(T a, U b) {
    FriendlyMatrixType<T, U>;
    {a + b} -> std::convertible_to<T>;
};

template<typename T, typename U>
concept MatrixMulOperationRequires = requires(T a, U b) {
    FriendlyMatrixType<T, U>;
    {a * b} -> std::convertible_to<T>;
};

template<typename T, typename U>
concept MatrixSubOperationRequires = requires(T a, U b) {
    FriendlyMatrixType<T, U>;
    {a - b} -> std::convertible_to<T>;
};

template<typename T>
concept MatrixOnlyFloatPointingRequires = requires {
    std::floating_point<T>;
};

template<typename T, typename U>
concept MatrixDivOperationRequires = requires(T a, U b) {
    MatrixOnlyFloatPointingRequires<T>;
    MatrixOnlyFloatPointingRequires<U>;
    {a / b} -> std::convertible_to<T>;
};

template<typename T>
concept FriendlyRange = requires(T &u) {
    { u.begin() } -> std::input_iterator;
    { u.end() } -> std::sentinel_for<decltype(u.begin())>;
    std::constructible_from<T, typename std::iterator_traits<decltype(u.begin())>::reference>;
};

template<typename T, typename U>
concept FriendlyContainer = requires (U &u) {
    FriendlyRange<U>;

    { u.empty() } noexcept -> std::same_as<bool>;
    { u.get_rows_count() } noexcept -> std::same_as<typename T::size_type>;
    { u.get_columns_count() } noexcept -> std::same_as<typename T::size_type>;
};

template<typename T, typename U>
concept SumType = requires(T &t, U &u) {
    {t + u} -> std::convertible_to<T>;
};

template <MatrixType T>
class Matrix;

#endif // CONCEPTS_H
