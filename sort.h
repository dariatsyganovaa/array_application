#pragma once

void swap(int* first_num, int* second_num);
void shuffle(int* mass, int size);
int check_sorting(int* mass, int size);
void hoara_sort(int* mass, int size, unsigned long long* swps, unsigned long long* cmps);
void bubble_sort(int* mass, int size, unsigned long long* swps, unsigned long long* cmps);
void optimized_bubble_sort(int* mass, int size, unsigned long long* swps_count, unsigned long long* cmps_count);
void hoara_sort_rec(int* mass, int left, int right, unsigned long long* swps, unsigned long long* cmps);
void start_sort(void(*sort)(int*, int, unsigned long long*, unsigned long long*), int* mass, int size, int* time, unsigned long long* swps, unsigned long long* cmps);
int start_sort_menu(int** mass, int* size);
void show_sort_menu();
void show_sort_result(int* mass, int size, int time, unsigned long long swps_count, unsigned long long cmps_count);
void shell_sort(int* mass, int size, unsigned long long* swps_count, unsigned long long* cmps_count);
void start_experiment(void(*sort)(int*, int, unsigned long long*, unsigned long long*), int min_size, int step_of_sizes, int count_of_experiments);
void start_test(int num, void(*sort)(int*, int, unsigned long long*, unsigned long long*), unsigned long long** characteristics, int min_size, int step_of_sizes);
void start_sort_experiments(int min_size, int step_of_sizes, int count_of_experiments);
void start_test_all(void(*sort)(int*, int, unsigned long long*, unsigned long long*), int* mass, int size, unsigned long long** characteristics, int num_sort);
void show_table_with_all_experiments_results(unsigned long long** characteristics, int min_size, int step_of_sizes, int count_of_experiments);
void show_table_with_experiments_results(unsigned long long** characteristics, int min_size, int step_of_sizes, int count_of_experiments);