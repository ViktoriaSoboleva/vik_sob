#include "vector.hpp"

#include <iostream>

using biv::Vector;

// Инициализация статической константы — начальная ёмкость буфера.
// static-член класса нельзя инициализировать внутри объявления класса,
// поэтому делаем это здесь, в .cpp файле.
template<typename T>
const std::size_t Vector<T>::START_CAPACITY = 4;

// Конструктор: выделяем динамический массив на capacity элементов.
// capacity уже инициализирован значением START_CAPACITY (из заголовка),
// size = 0 — вектор пустой.
template<typename T>
Vector<T>::Vector() {
	arr = new T[capacity];
}

// Деструктор: освобождаем память, выделенную под массив.
// Вызывается автоматически при выходе объекта из области видимости.
template<typename T>
Vector<T>::~Vector() {
	delete[] arr;
}

// Возвращает текущее количество элементов в векторе.
// noexcept — гарантируем, что исключений не будет.
template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
	return size;
}

// Проверяет, есть ли элемент с заданным значением в векторе.
// Линейный поиск: перебираем все элементы от 0 до size-1.
// Возвращает true при первом совпадении, false если не нашли.
template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
	for (std::size_t i = 0; i < size; ++i) {
		if (arr[i] == value) {
			return true;
		}
	}
	return false;
}

// Вставляет элемент value на позицию position, сдвигая остальные вправо.
// Возвращает false, если position > size (недопустимая позиция).
template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
	// Позиция может быть от 0 до size включительно.
	// position == size означает вставку в конец (как push_back).
	if (position > size) {
		return false;
	}

	// Если массив заполнен — нужно расширить буфер.
	if (size == capacity) {
		// Удваиваем ёмкость — стандартная стратегия роста,
		// обеспечивает амортизированную O(1) для push_back.
		capacity *= 2;

		// Выделяем новый массив большего размера.
		T* new_arr = new T[capacity];

		// Копируем все существующие элементы в новый массив.
		for (std::size_t i = 0; i < size; ++i) {
			new_arr[i] = arr[i];
		}

		// Освобождаем старый массив и переключаемся на новый.
		delete[] arr;
		arr = new_arr;
	}

	// Сдвигаем элементы вправо, начиная с конца, освобождая место на position.
	// Идём справа налево, чтобы не затереть ещё не сдвинутые элементы.
	for (std::size_t i = size; i > position; --i) {
		arr[i] = arr[i - 1];
	}

	// Записываем новый элемент на освобождённую позицию.
	arr[position] = value;

	// Увеличиваем счётчик элементов.
	++size;
	return true;
}

// Выводит содержимое вектора в формате [a, b, c].
template<typename T>
void Vector<T>::print() const noexcept {
	std::cout << "[";
	for (std::size_t i = 0; i < size; ++i) {
		if (i > 0) std::cout << ", "; // разделитель между элементами
		std::cout << arr[i];
	}
	std::cout << "]\n";
}

// Добавляет элемент в конец вектора.
// Делегирует в insert(size, value) — вставка сразу после последнего элемента.
template<typename T>
void Vector<T>::push_back(const T& value) {
	insert(size, value);
}

// Удаляет первый найденный элемент с заданным значением.
// Возвращает true если элемент был найден и удалён, false если не найден.
template<typename T>
bool Vector<T>::remove_first(const T& value) {
	for (std::size_t i = 0; i < size; ++i) {
		if (arr[i] == value) {
			// Сдвигаем все элементы после найденного влево на одну позицию,
			// тем самым "затирая" удаляемый элемент.
			// Условие j + 1 < size защищает от выхода за границу массива.
			for (std::size_t j = i; j + 1 < size; ++j) {
				arr[j] = arr[j + 1];
			}

			// Уменьшаем счётчик — последний элемент теперь "вне" вектора.
			--size;
			return true;
		}
	}
	return false;
}