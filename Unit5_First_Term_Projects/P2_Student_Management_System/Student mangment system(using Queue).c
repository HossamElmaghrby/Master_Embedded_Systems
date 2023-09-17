/*
 ============================================================================
 Name        : Student.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "SM.h"

#define NUMBER_OF_STUDENT 50
Student_t student_Array[NUMBER_OF_STUDENT];
int main(void) {
	int choice ;
	Student_manager_t students ;

	if(students_init(&students, student_Array, NUMBER_OF_STUDENT)==NO_ERROR)
	{
       Dprintf("-----initialization List is done-----\n")
	}

	Dprintf("Welcome to the student management system\n");
	while(1)
	{
		Dprintf(" =============================\n");
		Dprintf("\n Choose on of the following options \n");
		Dprintf("\n\t 1: Add Student Manually");
		Dprintf("\n\t 2: Add Student From Text File");
		Dprintf("\n\t 3: Find Student by Roll Number");
		Dprintf("\n\t 4: Find Student by First Name");
		Dprintf("\n\t 5: Find Student by Course ID");
		Dprintf("\n\t 6: Print Students Number");
		Dprintf("\n\t 7: Delete Student by Roll Number");
		Dprintf("\n\t 8: Update Student by Roll Number");
		Dprintf("\n\t 9: View Students");
		Dprintf("\n\t 10: Exit");
		Dprintf("\n\n Enter option number: ");

		scanf("%d",&choice);
		Dprintf(" ============================= \n");

		switch(choice)
		{
		case 1:
			Add_Student_Manualy(&students);
			break ;
		case 2:
		    Add_Student_form_file(&students);
			break ;
		case 3:
			Find_Student_using_id(&students);
			break ;
		case 4:
			Find_Student_using_name(&students);
			break ;
		case 5:
			Find_Student_registered_in_a_course(&students);
			break ;
		case 6:
		    print_students_count(&students);
			break ;
		case 7:
			dequeue(&students);
			break ;
		case 8:
			Update_student(&students);
			break ;
		case 9:
			show_students(&students);
			break;
		case 10:
			update_student_file(&students);
			exit(0);
		default:
			Dprintf("\n Wrong Option: Try Again \n\n");
			break;
		}
	}
	return EXIT_SUCCESS;
}
