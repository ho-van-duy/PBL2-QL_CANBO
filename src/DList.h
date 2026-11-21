#ifndef DLIST_H
#define DLIST_H

#include <iostream>

template <typename T>
class DNode {
public:
    T         data;
    DNode<T>* prev;
    DNode<T>* next;

    DNode() : prev(nullptr), next(nullptr) {}
    DNode(const T& d, DNode<T>* p = nullptr, DNode<T>* n = nullptr)
        : data(d), prev(p), next(n) {}
};

template <typename T>
class DList {
private:
    DNode<T>* head;
    DNode<T>* tail;
    int       soLuong;

public:
    DList();
    ~DList();

    int  size() const;
    bool isEmpty() const;

    void themDau(const T& data);
    void themCuoi(const T& data);

    bool xoa(const T& khoa, bool (*bangNhau)(const T&, const T&));

    void sapXep(bool (*soSanh)(const T&, const T&));

    DNode<T>* getHead() const;
    DNode<T>* getTail() const;
};

template <typename T>
DList<T>::DList() : head(nullptr), tail(nullptr), soLuong(0) {}

template <typename T>
DList<T>::~DList() {
    while (head) {
        DNode<T>* tam = head;
        head = head->next;
        delete tam;
    }
    tail = nullptr;
    soLuong = 0;
}

template <typename T>
int DList<T>::size() const { return soLuong; }

template <typename T>
bool DList<T>::isEmpty() const { return soLuong == 0; }

template <typename T>
void DList<T>::themDau(const T& data) {
    DNode<T>* nutMoi = new DNode<T>(data, nullptr, head);
    if (head) head->prev = nutMoi;
    else      tail = nutMoi;
    head = nutMoi;
    soLuong++;
}

template <typename T>
void DList<T>::themCuoi(const T& data) {
    DNode<T>* nutMoi = new DNode<T>(data, tail, nullptr);
    if (tail) tail->next = nutMoi;
    else      head = nutMoi;
    tail = nutMoi;
    soLuong++;
}

template <typename T>
bool DList<T>::xoa(const T& khoa, bool (*bangNhau)(const T&, const T&)) {
    for (DNode<T>* p = head; p; p = p->next) {
        if (bangNhau(p->data, khoa)) {
            if (p->prev) p->prev->next = p->next;
            else         head = p->next;
            if (p->next) p->next->prev = p->prev;
            else         tail = p->prev;
            delete p;
            soLuong--;
            return true;
        }
    }
    return false;
}

template <typename T>
void DList<T>::sapXep(bool (*soSanh)(const T&, const T&)) {
    for (DNode<T>* i = head; i && i->next; i = i->next) {
        for (DNode<T>* j = i->next; j; j = j->next) {
            if (soSanh(j->data, i->data)) {
                T tam = i->data;
                i->data = j->data;
                j->data = tam;
            }
        }
    }
}

template <typename T>
DNode<T>* DList<T>::getHead() const { return head; }

template <typename T>
DNode<T>* DList<T>::getTail() const { return tail; }

#endif
