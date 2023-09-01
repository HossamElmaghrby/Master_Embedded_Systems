/*
 * SLL_Student.h
 *
 *  Created on: Aug 29, 2023
 *      Author: elmag
 */

#ifndef SLL_STUDENT_H_
#define SLL_STUDENT_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define Dprintf(...) fflush(stdout);printf(__VA_ARGS__);fflush(stdout);

// Student information
typedef struct
{
	int ID ;
	char name[40];
	float height ;
}Sdata;

// node for every student
typedef struct
{
	Sdata data ;
	struct node* next;
}node;

// List of students
typedef struct
{
	node *head ;
	node *tail ;
}Student_SLL;

void fill_info();
void Add_Student();
void Delete_Student();
void View_Students();
void Delete_All();
void View_student(Sdata student);
void GetNth(Student_SLL *list);
void number_of_student();
int getcount(node*count);
void lenght_of_list();
void GetNth_from_end(Student_SLL *list);
void middle_of_list();
void Reverse_list();

#endif /* SLL_STUDENT_H_ */
