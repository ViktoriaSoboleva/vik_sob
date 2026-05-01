#include "src/vector.hpp"
#include "src/vector.cpp"
#include "src/doubly_linked_list.hpp"
#include "src/doubly_linked_list.cpp"

template class biv::Vector<int>;
template class biv::DoublyLinkedList<int>;

int main() {
    biv::Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.print();           // [1, 2, 3]
    v.insert(0, 0);
    v.print();           // [0, 1, 2, 3]
    v.remove_first(2);
    v.print();           // [0, 1, 3]

    biv::DoublyLinkedList<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(10);
    l.print();           // [10, 20, 10]
    l.remove_first(10);
    l.print();           // [20, 10]

    system("pause");
}