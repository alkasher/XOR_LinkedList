#pragma once
#include "LinkedList.hpp"
void test1() {
    std::cout << "test1";
    int* a = new int[4];
    for (int i = 0; i < 4; ++i) {
        a[i] = i;
    }
    LinkedList<int> list(a, 4);
    list.print();
    for (int i = 4; i < 7; ++i)
        list.push_back(i);
    list.print();
}

void test2() {
    std::cout << "test2\n";
    LinkedList<int> list;
    std::cout << "size " << list.size();
    list.push_back(5);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.push_back(6);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.push_back(8);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();

}

void test3() {
    std::cout << "test3\n";
    LinkedList<int> list;
    list.insert(0,1);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.insert(1, 0);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.insert(0, 2);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.insert(3, 4);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.insert(3, 5);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.insert(2, 6);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.insert(5, 7);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
}

void test4() {
    std::cout << "test4";
    int* a = new int[10];
    for (int i = 0; i < 10; ++i) {
        a[i] = i;
    }
    LinkedList<int> list(a, 10);
    list.print();
    list.remove(9);
    list.print();
    list.remove(0);
    list.print();
    list.remove(1);
    list.print();
    list.remove(list.size()-2);
    list.print();
    list.remove(3);
    list.print();
    list.remove(3);
    list.print();
    list.remove(2);
    list.print();
    list.remove(2);
    list.print();
    list.remove(0);//list.remove(1);
    list.print();
    list.remove(0);
    list.print();

}