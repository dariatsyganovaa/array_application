#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "dmassive.h"  


#define STEP_OF_CAPACITY 15

//выделение памяти
void clear_memory(int* mass) {
	if (mass != NULL) {
		free(mass);
	}
}
int* set_memory(int size) {
	int* mass, capacity = (size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
	mass = (int*)malloc(sizeof(int) * capacity);
	return mass;
}
int* reset_memory(int* old_mass, int old_size, int new_size) { //O(n) worst, O(1) best
	int old_capacity = (old_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY,
		new_capacity = (new_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;

	if (old_capacity < new_capacity) {
		int* new_mass = set_memory(new_size);
		for (int i = 0; i < old_size; i++) {
			new_mass[i] = old_mass[i];
		}
		clear_memory(old_mass);
		return new_mass;
	}
	return old_mass;
}
int* reset_memory_for_delete(int* old_mass, int* old_size, int new_size, int* deleted_count) {
	if (*old_size - *deleted_count == 0) {
		int* new_mass = set_memory(*old_size - *deleted_count);
		*old_size = 0; 
		*deleted_count = 0;
		return new_mass;
	}
	if (*deleted_count >= 0.10 * (*old_size) || *deleted_count >= 1000) {
		int* new_mass = set_memory(*old_size - *deleted_count);
		for (int i = 0, j = 0; i < *old_size; i++) {
			if (old_mass[i] != NULL) {
				new_mass[j] = old_mass[i];
				j++;
			}
		}
		*old_size = *old_size - *deleted_count;
		*deleted_count = 0;
		clear_memory(old_mass); 
		return new_mass;
	}
	return old_mass; 
}

//заполнение массива
void default_init(int* mass, int size) {
	for (int i = 0; i < size; i++) { 
		mass[i] = i + 1;
	}
}
void user_init(int* mass, int size) {
	for (int i = 0; i < size; i++) {
		scanf_s("%d", &mass[i]);
	}
}
void rand_init(int* mass, int size, int min, int max) {
	for (int i = 0; i < size; i++) {
		mass[i] = min + rand() % (max - min + 1);
	}
}

//вставка 
void push_front_elem(int* mass, int size, int value) {
	for (int i = size - 1; i > 0; i--) {
		mass[i] = mass[i - 1];
	}
	mass[0] = value;
}
void push_front_elems(int* mass, int size, int* values, int count) { 
	for (int i = size - 1; i > count - 1; i--) {
		mass[i] = mass[i - count];
	}
	for (int i = 0; i < count; i++) {
		mass[i] = values[i];
	}
}
void push_back_elem(int* mass, int size, int value) {
	mass[size - 1] = value;
}
void push_back_elems(int* mass, int size, int* values, int count) { 
	for (int i = size - count; i < size; i++) {
		mass[i] = values[i - (size - count)]; 
	}
}
void insert_elem(int* mass, int size, int value, int pos) { 
	for (int i = size - 1; i > pos; i--) { 
		mass[i] = mass[i - 1];
	}
	mass[pos] = value; 
}
void insert_elems(int* mass, int size, int pos, int* values, int count) { 
	for (int i = 0; i <= size - count - pos; i++) {
		mass[size - i] = mass[size - count - i]; 
	}
	for (int i = pos; i < pos + count; i++) {
		mass[i] = values[i - pos]; 
	}
}

// поиск
void found_first_elem(int* mass, int size, int value, int* found) { //О(n)
	found[0] = 0; 
	for (int i = 0; i < size; i++) {
		if (mass[i] == value) {
			found[++found[0]] = i;
			break;
		}
	}
}
void found_last_elem(int* mass, int size, int value, int* found) {
	found[0] = 0;
	for (int i = size - 1; i > 0; i--) { 
		if (mass[i] == value) { 
			found[++found[0]] = i;
			break;
		}
	}
}
void found_elem(int* mass, int size, int value, int* found) {
	found[0] = 0;
	for (int i = 0; i < size; i++) {
		if (mass[i] == value) {
			found[++found[0]] = i;
		}
	}
}
void found_elems(int* mass, int size, int* values, int count, int* found) {
	found[0] = 0; 
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < count; j++) {
			if (mass[i] == values[j]) {
				found[++found[0]] = i; 
				break; 
			}
		}
	}
}

// удаление
void pop_front_elem(int* mass, int size) { //О(k)
	int first_not_null = 0;
	while (mass[first_not_null] == NULL) {
		first_not_null++; 
	}
	mass[first_not_null] = NULL;

}
void pop_front_elems(int* mass, int size, int count) {
	for (int i = 0; i < size - count; i++) {
		mass[i] = mass[i + count];
	}
	for (int i = size - count; i < size; i++) {
		mass[i] = NULL;
	}
}
void pop_back_elem(int* mass, int size) {
	int last_not_null = size - 1; 
	while (mass[last_not_null] == NULL) {
		last_not_null--;
	}
	mass[last_not_null] = NULL;
}
void pop_back_elems(int* mass, int size, int count) {
	for (int i = size - count; i < size; i++) {
		mass[size - 1] = NULL;
	}
}
void erase_elem(int* mass, int size, int pos) { 
	int pos_not_null = pos - 1;
	while (mass[pos_not_null] == NULL) {
		pos_not_null++;
	}
	mass[pos_not_null] = NULL; 
} 
void erase_elems(int* mass, int size, int pos, int count) {
	for (int i = pos - 1; i < pos + count - 1; i++) {
		mass[i] = NULL;
	}
}

// замена
void replace_by_value(int* mass, int size, int value, int new_value) {
	for (int i = 0; i < size; i++) {
		if (mass[i] == value) {
			mass[i] = new_value;
		}
	}
}

void replace_by_index(int* mass, int size, int index, int new_value) {
	if (index >= 0 && index < size) {
		mass[index] = new_value;
	}
	else {
		printf("Индекс вне диапазона!\n");
	}
}

void replace_by_indexes(int* mass, int size, int* indexes, int count, int* new_values) {
	for (int i = 0, j = 0 ; i < size && j < count; i++) {
		if (i == indexes[j]) {
			mass[i] = new_values[j];
			j++;
		}
	}
}

//вывод массива на экран
void print(int* mass, int size, char sep) {
	if (mass == NULL || size <= 0) return;
	if (mass[size - 1] == NULL) {
		for (int i = 0; i < size - 2; i++) {
			if (mass[i] != NULL) {
				printf("%d%c ", mass[i], sep);
			}
		}
		if (mass[size - 2] != NULL) {
			printf("%d", mass[size - 2]);
		}
	}
	else {
		for (int i = 0; i < size - 1; i++) {
			if (mass[i] != NULL) {
				printf("%d%c ", mass[i], sep);
			}
		}
		if (mass[size - 1] != NULL) {
			printf("%d", mass[size - 1]);
		}
	}
}
