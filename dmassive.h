#pragma once

//��������� ������
void clear_memory(int* mass);
int* set_memory(int size);
int* reset_memory(int* old_mass, int old_size, int new_size);
int* reset_memory_for_delete(int* old_mass, int* old_size, int new_size, int* deleted_count);

//���������� �������
void default_init(int* mass, int size);
void user_init(int* mass, int size);
void rand_init(int* mass, int size, int min, int max);

//������� �

//������ �������
void push_front_elem(int* mass, int size, int value); //������� ������ ��������
void push_front_elems(int* mass, int size, int* values, int count);  //������� ���������� ���������

//����� �������
void push_back_elem(int* mass, int size, int value); //������� ������ ��������
void push_back_elems(int* mass, int size, int* values, int count);  //������� ���������� ���������

//�������� �������
void insert_elem(int* mass, int size, int value, int pos); //������� ������ ��������
void insert_elems(int* mass, int size, int pos, int* values, int count); //������� ���������� ���������

//�����

void found_first_elem(int* mass, int size, int value, int* found); //����� ������� ��������
void found_last_elem(int* mass, int size, int value, int* found); //����� ���������� ��������
void found_elem(int* mass, int size, int value, int* found); //����� ���� ��������� (������ ������� ����� ���������� � ������ ������� ������)
void found_elems(int* mass, int size, int* values, int values_count, int* found); //����� ���������� ���������

//��������

//������ �������
void pop_front_elem(int* mass, int size); //�������� ������ ��������
void pop_front_elems(int* mass, int size, int count);  //�������� ���������� ���������

//����� �������
void pop_back_elem(int* mass, int size); //�������� ������ ��������
void pop_back_elems(int* mass, int size, int count);  //�������� ���������� ���������

//�������� �������
void erase_elem(int* mass, int size, int pos); //�������� ������ ��������
void erase_elems(int* mass, int size, int pos, int count); //�������� ���������� ���������

//������

void replace_by_value(int* mass, int size, int value, int new_value); //������ �� ��������
void replace_by_index(int* mass, int size, int index, int new_value); //������ �� �������
void replace_by_indexes(int* mass, int size, int* indexes, int count, int* new_values); //������ �������� �� ���������� ��������

//����� ������� �� �����
void print(int* mass, int size, char sep);

