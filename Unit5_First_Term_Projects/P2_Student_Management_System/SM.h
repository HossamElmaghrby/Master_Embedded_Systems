/*
 * SM.h
 *
 *  Created on: Sep 7, 2023
 *      Author: elmag
 */

#ifndef SM_H_
#define SM_H_

#define Dprintf(...) fflush(stdout);printf(__VA_ARGS__);fflush(stdout);

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NAME_SIZE 20
#define COURSES_NUMBER 5

typedef struct
{
	char first_name[NAME_SIZE] ;
	char last_name[NAME_SIZE] ;
	int roll_number ;
	float GPA ;
	int courses_ids[COURSES_NUMBER];
}Student_t;

typedef struct
{
   Student_t *head ;
   Student_t *tail ;
   int length ;
   int count ;
}Student_manager_t;

typedef enum
{
	NO_ERROR,
	EMPTY_QUEUE,
	FULL_QUEUE,
	NULL_QUEUE
}QUEUE_status ;
 // --------------------main functions-------------------------------
QUEUE_status students_init(Student_manager_t* students, Student_t*student, int num_of_std);

void Add_Student_form_file(Student_manager_t* students);

void Add_Student_Manualy(Student_manager_t* students);

void Find_Student_using_id(Student_manager_t* students);

void Find_Student_using_name(Student_manager_t* students);

void Find_Student_registered_in_a_course(Student_manager_t* students);

void Count_of_student();

void dequeue(Student_manager_t *students);

void Update_student(Student_manager_t *students);

void show_students(Student_manager_t *students);


//----------------------------Auxiliary Functions--------------------
QUEUE_status Is_Full_List(Student_manager_t *students);

QUEUE_status Is_Empty_List(Student_manager_t *students);

void enqueue(Student_manager_t *students,Student_t student);

bool search_student_by_roll(Student_manager_t *students,int roll_num);

void print_student(Student_t *student);

void print_students_count(Student_manager_t *students);

void shift_left(Student_manager_t *students , Student_t *student );

void update_student_file(Student_manager_t *students);

#endif /* SM_H_ */
