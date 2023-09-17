/*
 * SM.c
 *
 *  Created on: Sep 7, 2023
 *      Author: elmag
 */

#include "SM.h"


QUEUE_status students_init(Student_manager_t* students, Student_t*student, int num_of_std)
{

	students->head =student ;
	students->tail =student ;
	students->length =num_of_std ;
	students->count=0 ;

	if(students->head && students->length)
		return NO_ERROR ;
	else
		return NULL_QUEUE ;
}

void Add_Student_form_file(Student_manager_t* students)
{
	if(Is_Full_List(students)==FULL_QUEUE)
	{
		return ;
	}

  FILE *ReadFromFile ;
  ReadFromFile =fopen("students.txt" , "r");

	if(ReadFromFile == NULL)
	{
		Dprintf("\n [ERROR] students.txt file not found. \n");

		return;
	}

	while(!feof(ReadFromFile))
	{
		int roll_num ;
		Student_t student ;
		fscanf(ReadFromFile,"%d" ,&roll_num);

		if(search_student_by_roll(students, roll_num))
		{
			Dprintf("\n[ERROR] Roll number %d is already taken\n",roll_num);

			fscanf(ReadFromFile, "%*[^\n]");

			continue;
		}

        student.roll_number =roll_num ;
		fscanf(ReadFromFile, "%s", student.first_name);
		fscanf(ReadFromFile, "%s", student.last_name);
		fscanf(ReadFromFile, "%f", &student.GPA);

		// Reading course IDs
		for (int i = 0; i < COURSES_NUMBER; ++i)
		{
			fscanf(ReadFromFile, "%d", &student.courses_ids[i]);
		}
		enqueue(students, student);
		printf("\n[INFO] Roll number %d is saved successfully\n", student.roll_number);
	}
	printf("\n[INFO] Students details are saved successfully\n");

	fclose(ReadFromFile);
	print_students_count(students);
}
void Add_Student_Manualy(Student_manager_t* students)
{
	int roll_num ;
	if(Is_Full_List(students)==FULL_QUEUE)
	{
		return ;
	}

	Dprintf("\n=== Enter student data ===\n");
	Dprintf("\tEnter roll number: ");
	scanf("%d",&roll_num);

	Student_t student ;

	if(search_student_by_roll(students, roll_num))
	{
		Dprintf("\n[ERROR] Roll number %d is already taken\n", roll_num);
		return;
	}
	student.roll_number =roll_num ;

	Dprintf("\tEnter first name: ");
	scanf("%s", student.first_name);

	Dprintf("\tEnter second name: ");
	scanf("%s", student.last_name);

	Dprintf("\tEnter GPA: ");
	scanf("%f", &student.GPA);

	Dprintf("\tEnter Courses IDs\n");
	for (int i = 0; i < COURSES_NUMBER; ++i)
	{
		Dprintf("\t\tEnter Courses no.%d: ",i+1);
		scanf("%d", &student.courses_ids[i]);
	}
	enqueue(students, student);
	Dprintf("\n[INFO] Student details us saved successfully\n");

	print_students_count(students);
}

void Find_Student_using_id(Student_manager_t* students)
{
	if(Is_Empty_List(students)==EMPTY_QUEUE || Is_Empty_List(students)==NULL_QUEUE)
	{
		return ;
	}
	int roll_num ,flag=0;
	Dprintf("\nEnter roll number: ");
	scanf("%d", &roll_num);

	Student_t *student =students->head ;

	for(int i = 0 ; i<students->count ;i++)
	{
		if(student->roll_number==roll_num)
		{
			print_student(student);
			flag=1;
			break ;
		}
		student++;
	}
	if(flag==0)
	{
		Dprintf("\n[ERROR] Roll number %d in not found\n", roll_num);
	}
}

void Find_Student_using_name(Student_manager_t* students)
{
	if(Is_Empty_List(students)==EMPTY_QUEUE || Is_Empty_List(students)==NULL_QUEUE)
	{
		return ;
	}
	char name[NAME_SIZE];
	int flag=0;
	Dprintf("\nEnter First Name: ");
	scanf("%s",name);

	Student_t *student = students->head;

	for(int i = 0 ; i<students->count ;i++)
	{
		if(!strcmp(student->first_name , name))
		{
			print_student(student);
			flag=1;
		}
		student++;
	}
	if(flag==0)
	{
		Dprintf("\n[ERROR] %s in not found\n",name);
	}
}

void Find_Student_registered_in_a_course(Student_manager_t* students)
{

	if(Is_Empty_List(students)==EMPTY_QUEUE || Is_Empty_List(students)==NULL_QUEUE)
	{
		return ;
	}
	int course_id ,num_of_registers = 0;
	Dprintf("\nEnter Course ID: ");
	scanf("%d", &course_id);
	Student_t *student = students->head ;

	for(int i = 0; i<students->count ;i++)
	{
		for(int j = 0 ; j < COURSES_NUMBER; j++)
		{
			if(student->courses_ids[j] == course_id)
			{
				Dprintf("The student details are\n");
				Dprintf("\tFirst Name: %s\n", student->first_name);
				Dprintf("\tLast Name: %s\n", student->last_name);
				Dprintf("\tRoll Number: %d\n", student->roll_number);
				Dprintf("\tGPA: %0.1f\n", student->GPA);
				Dprintf("\tCourses IDs are\n");
				Dprintf("----------------------\n");
				num_of_registers++ ;
				break ;
			}
		}
		student++;
	}

	if(num_of_registers == 0)
	{
		Dprintf("\n[ERROR] Course id %d is not found\n", course_id);
	}
	else
	{
		Dprintf("\n[INFO] Total number of students enrolled: %d\n", num_of_registers);
	}
}

void print_students_count(Student_manager_t *students)
{
	int counter = students->count;
	int length = students->length;

	Dprintf("----------------------\n");
	printf("[INFO] Total number of students is %d\n", counter);
	printf("[INFO] You can add up to %d students\n", length);
	printf("[INFO] You can add %d more students\n", length - counter);

}

void dequeue(Student_manager_t *students)
{
	if(Is_Empty_List(students)==EMPTY_QUEUE || Is_Empty_List(students)==NULL_QUEUE)
	{
		return;
	}

	int roll_num ;
	Student_t *student = students->head ;

	Dprintf("\nEnter roll number: ");
	scanf("%d", &roll_num);

	for(int i = 0; i < students->length ; i++)
	{
		if(student->roll_number == roll_num)
		{
			shift_left(students, student);
			Dprintf("\n[INFO] The Roll Number is removed successfully\n");
			print_students_count(students);
			return ;
		}
		student++;
	}
	Dprintf("\n[ERROR] This Roll Number %d not found\n",roll_num);
}

void Update_student(Student_manager_t *students)
{
	if(Is_Empty_List(students)==EMPTY_QUEUE || Is_Empty_List(students)==NULL_QUEUE)
	{
		return;
	}
	int roll_num ;
	Dprintf("\n=== Enter student data ===\n");
	Dprintf("\tEnter roll number: ");
	scanf("%d",&roll_num);
	Student_t *student =students->head ;
	for(int i =0 ;i<students->count ; i++)
	{
		if(student->roll_number == roll_num)
		{
			int choice ,roll_num ,i;
			print_student(student);

			Dprintf("\nWhich date do you want to change ?\n");
			Dprintf("\t 1: The Roll Number\n");
			Dprintf("\t 2: The First Name\n");
			Dprintf("\t 3: The Second Name\n");
			Dprintf("\t 4: The GPA Score\n");
			Dprintf("\t 5: The Courses ID\n");
			Dprintf("Enter your option: ");

			scanf("%d",&choice);
			switch (choice)
			{
			case 1:
				Dprintf("Enter the new roll number: ");
				scanf("%d",&roll_num);

				if(search_student_by_roll(students, roll_num))
				{
					Dprintf("\n[ERROR] This Roll Number %d is exist\n",roll_num);
					break ;
				}
				student->roll_number = roll_num;
				Dprintf("\n[INFO] The Roll Number %d in updated successfully\n", roll_num);
				break;
			case 2:
				Dprintf("Enter the new first name: ");
				scanf("%s", student->first_name);
				Dprintf("\n[INFO] The First Name %s in updated successfully\n",student->first_name);
				break;

			case 3:
				Dprintf("Enter the new last name: ");
				scanf("%s", student->last_name);
				Dprintf("\n[INFO] The Last Name %s in updated successfully\n",student->last_name);
				break;

			case 4:
				Dprintf("Enter the new GPA: ");
				scanf("%f", &student->GPA);
				Dprintf("\n[INFO] The GPA Score %0.1f in updated successfully\n", student->GPA);
				break;

			case 5:
				Dprintf("Enter the course number from %d to %d: ", 1, COURSES_NUMBER);
				scanf("%d", &i);
				Dprintf("Enter the new course id: ");
				scanf("%d", &student->courses_ids[i - 1]);
				Dprintf("\n[INFO] The Course ID %d in updated successfully\n", student->courses_ids[i - 1]);
				break;
			default:
				break;
			}
			return;
		}
		student++;
	}
	Dprintf("\n[ERROR] This Roll Number %d not found\n",roll_num);

}

void show_students(Student_manager_t *students)
{
	if(Is_Empty_List(students)==EMPTY_QUEUE || Is_Empty_List(students)==NULL_QUEUE)
	{
		return;
	}

	Student_t *student = students->head ;
	for(int i = 0;i < students->count ; i++)
	{
		print_student(student);
		student++;
	}
}

void update_student_file(Student_manager_t *students)
{

	Student_t *student;
	FILE *WriteToFile ;
	WriteToFile = fopen("students.txt", "w");

	if(WriteToFile == NULL)
	{
		Dprintf("\n [ERROR] update_students.txt create failed. \n");
		return;
	}

	student= students->head;
	for (int i = 0; i < students->count; ++i)
	{
		fprintf(WriteToFile, "%d ", student->roll_number);
		fprintf(WriteToFile, "%s ", student->first_name);
		fprintf(WriteToFile, "%s ", student->last_name);
		fprintf(WriteToFile, "%0.1f ", student->GPA);

		for(int j = 0; j < COURSES_NUMBER ; ++j)
		{
			fprintf(WriteToFile, "%d ", student->courses_ids[j]);
		}

		fprintf(WriteToFile, "\n");
		student++;
	}
	printf("\n[INFO] Update Students details are saved in file successfully\n");

	fclose(WriteToFile);
}

QUEUE_status Is_Full_List(Student_manager_t *students)
{
	if( !students->head || !students->tail)
	{
		Dprintf("The list didn't initialize\n");
		return NULL_QUEUE ;
	}
	if(students->count>= students->length)
	{
		Dprintf("students list is full\n");
		return FULL_QUEUE;
	}
	return NO_ERROR;
}

QUEUE_status Is_Empty_List(Student_manager_t *students)
{
	if( !students->head || !students->tail)
	{
		Dprintf("The list didn't initialize\n");
		return NULL_QUEUE ;
	}
	if(students->count == 0)
	{
		Dprintf("students list is empty\n");
		return EMPTY_QUEUE;
	}
	return NO_ERROR ;
}

bool search_student_by_roll(Student_manager_t *students,int roll_num)
{
	Student_t *student = students->head ;
	for(int i = 0; i < students->length ; i++)
	{
		if(student->roll_number == roll_num)
			return true ;
		student++;
	}
	return false ;
}

void enqueue(Student_manager_t *students,Student_t student)
{
	*(students->tail) = student ;
	students->tail++ ;

	students->count++;
}

void print_student(Student_t *student)
{
	Dprintf("The student details are\n");
	Dprintf("\tFirst Name: %s\n", student->first_name);
	Dprintf("\tLast Name: %s\n", student->last_name);
	Dprintf("\tRoll Number: %d\n", student->roll_number);
	Dprintf("\tGPA: %0.1f\n", student->GPA);
	Dprintf("\tCourses IDs are\n");

	for(int i = 0; i < COURSES_NUMBER; i++)
	{
		Dprintf("\t\tCourse %d id: %d\n", i + 1, student->courses_ids[i]);
	}
	Dprintf("----------------------\n");
}

void shift_left(Student_manager_t *students , Student_t *student )
{
	while(student!=students->tail)
	{
		*(student) = *(student+1);
		student++;
	}
	students->tail--;
	students->count--;
}
