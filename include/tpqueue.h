// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <cassert>

struct SYM {
  char ch;
  int prior;
};

template<typename T, int size>
class TPQueue {
  // реализация шаблона очереди с приоритетом на кольцевом буфере
 private:
  T* arr;
  //arr = new T[sizeA];
  int sizeM; // максимальное количество элементов в очереди размер(массива)
  int begin, end;
  int count; // счетчик элементов

 public:
  // конструктор по умолчанию
  TPQueue():sizeM(size), begin(0), end(0), count(0) {
    arr = new T[sizeM+1];
  }
  void push(const T& item) {
    // проверяем, ести ли свободное место в очереди
    int cur = end;
    assert(count < sizeM);
    if (count != 0) {
      for (int i = begin; i < end; i++) {
        if (item.prior > arr[i].prior) {
          cur = i;
          break;
        }
      }
    }
    if (count != 0) {
      for (int i = end; i > cur; i--)
        arr[i] = arr[i - 1];
    }
    arr[cur] = item;
    count++;
    end++;
    // проверка кругового заполнения очереди
    if (end > sizeM)
      end -= sizeM + 1; // возвращаем end на начало очереди
  }
  const T& pop() {
    // проверяем, есть ли в очереди элементы
    assert(count > 0);
    //T item = arr[begin++];
    count--;
    // проверка кругового заполнения очереди
    if (begin > sizeM)
      begin -= sizeM + 1; // возвращаем begin на начало очереди
    return arr[begin++];
  }
  // функция чтения элемента на первой позиции
  char get() const {
    // проверяем, есть ли в очереди элементы
    assert(count > 0);
    return arr[begin].ch;
  }
  // функция проверки очереди на пустоту
  bool isEmpty() const {
    return count == 0;
  }
  // функция проверки очереди на заполненность
  bool isFull() const {
    return count == sizeM;
  }
  // деструктор класса Queue
  ~TPQueue() {
    delete[] arr;
  }
};

#endif  // INCLUDE_TPQUEUE_H_
