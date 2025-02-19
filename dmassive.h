#pragma once

//выделение памяти
void clear_memory(int* mass);
int* set_memory(int size);
int* reset_memory(int* old_mass, int old_size, int new_size);
int* reset_memory_for_delete(int* old_mass, int* old_size, int new_size, int* deleted_count);

//заполнение массива
void default_init(int* mass, int size);
void user_init(int* mass, int size);
void rand_init(int* mass, int size, int min, int max);

//вставка в

//начало массива
void push_front_elem(int* mass, int size, int value); //вставка одного элемента
void push_front_elems(int* mass, int size, int* values, int count);  //вставка нескольких элементов

//конец массива
void push_back_elem(int* mass, int size, int value); //вставка одного элемента
void push_back_elems(int* mass, int size, int* values, int count);  //вставка нескольких элементов

//середина массива
void insert_elem(int* mass, int size, int value, int pos); //вставка одного элемента
void insert_elems(int* mass, int size, int pos, int* values, int count); //вставка нескольких элементов

//поиск

void found_first_elem(int* mass, int size, int value, int* found); //поиск первого элемента
void found_last_elem(int* mass, int size, int value, int* found); //поиск последнего элемента
void found_elem(int* mass, int size, int value, int* found); //поиск всех элементов (размер массива будет находиться в первой нулевой ячейке)
void found_elems(int* mass, int size, int* values, int values_count, int* found); //поиск нескольких элементов

//удаление

//начало массива
void pop_front_elem(int* mass, int size); //удаление одного элемента
void pop_front_elems(int* mass, int size, int count);  //удаление нескольких элементов

//конец массива
void pop_back_elem(int* mass, int size); //удаление одного элемента
void pop_back_elems(int* mass, int size, int count);  //удаление нескольких элементов

//середина массива
void erase_elem(int* mass, int size, int pos); //удаление одного элемента
void erase_elems(int* mass, int size, int pos, int count); //удаление нескольких элементов

//замена

void replace_by_value(int* mass, int size, int value, int new_value); //замена по значению
void replace_by_index(int* mass, int size, int index, int new_value); //замена по индексу
void replace_by_indexes(int* mass, int size, int* indexes, int count, int* new_values); //замена элемента по нескольким индексам

//вывод массива на экран
void print(int* mass, int size, char sep);

