
#include "doubly_linked_list.hpp"

#include <iostream>

using biv::DoublyLinkedList;

// Деструктор: освобождает память всех узлов списка.
// Проходим по списку от begin до конца, удаляя каждый узел.
// Важно сохранить указатель на следующий узел ДО удаления текущего,
// иначе после delete current->next станет недоступен.
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node* current = begin;
	while (current != nullptr) {
		Node* next = current->next; // сохраняем следующий до удаления
		delete current;
		current = next;             // переходим к следующему
	}
}

// Возвращает количество элементов в списке.
// Единственный способ узнать размер — пройти весь список,
// так как отдельный счётчик size не хранится.
// O(n) по времени.
template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
	std::size_t count = 0;
	Node* current = begin;
	while (current != nullptr) {
		++count;
		current = current->next;
	}
	return count;
}

// Проверяет, есть ли в списке узел с заданным значением.
// Линейный поиск от begin к end.
// Возвращает true при первом совпадении, false если не нашли.
template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
	Node* current = begin;
	while (current != nullptr) {
		if (current->value == value) {
			return true;
		}
		current = current->next;
	}
	return false;
}

// Выводит содержимое списка в формате [a, b, c].
// Флаг first нужен чтобы не печатать ", " перед самым первым элементом.
template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
	std::cout << "[";
	Node* current = begin;
	bool first = true;
	while (current != nullptr) {
		if (!first) std::cout << ", "; // разделитель между элементами
		std::cout << current->value;
		first = false;
		current = current->next;
	}
	std::cout << "]\n";
}

// Добавляет новый узел с заданным значением в конец списка.
// Два случая:
//   1. Список пуст (end == nullptr) — новый узел становится единственным,
//      begin и end указывают на него.
//   2. Список не пуст — новый узел присоединяется после текущего end:
//      node->prev = старый end
//      старый end->next = node
//      end = node
template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
	Node* node = new Node(value); // создаём узел, prev и next = nullptr

	if (end == nullptr) {
		// Список был пуст — новый узел единственный
		begin = end = node;
	}
	else {
		// Привязываем новый узел к хвосту списка
		node->prev = end;   // новый узел смотрит назад на бывший конец
		end->next = node;   // бывший конец смотрит вперёд на новый узел
		end = node;         // обновляем указатель на конец списка
	}
}

// Удаляет первый найденный узел с заданным значением.
// Возвращает true если узел найден и удалён, false если не найден.
//
// При удалении узла нужно "перешить" связи соседей,
// чтобы они указывали друг на друга, минуя удаляемый узел.
// Четыре случая для указателей begin/end:
//   - удаляем не первый узел: prev->next перенаправляем на next
//   - удаляем первый узел (prev == nullptr): begin сдвигается на next
//   - удаляем не последний узел: next->prev перенаправляем на prev
//   - удаляем последний узел (next == nullptr): end сдвигается на prev
template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
	Node* current = begin;
	while (current != nullptr) {
		if (current->value == value) {

			// --- Перешиваем левую связь ---
			if (current->prev != nullptr) {
				// Есть левый сосед — он теперь смотрит вперёд на правого соседа
				current->prev->next = current->next;
			}
			else {
				// Удаляем первый узел — begin сдвигаем на следующий
				begin = current->next;
			}

			// --- Перешиваем правую связь ---
			if (current->next != nullptr) {
				// Есть правый сосед — он теперь смотрит назад на левого соседа
				current->next->prev = current->prev;
			}
			else {
				// Удаляем последний узел — end сдвигаем на предыдущий
				end = current->prev;
			}

			// Освобождаем память удалённого узла
			delete current;
			return true;
		}
		current = current->next;
	}

	// Элемент не найден
	return false;
}
