/*
 ============================================================================
 Name        : Student_data_base.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "SLL_Student.h"
 Student_SLL* students_list=NULL ;
int main(void) {

	while(1)
	{
		Dprintf("=======================\n");
		Dprintf("Choose an option");
		Dprintf("\n\t1: Add Student ");
		Dprintf("\n\t2: Delete Student");
		Dprintf("\n\t3: View students");
		Dprintf("\n\t4: Delete all");
		Dprintf("\n\t5: View student");
		Dprintf("\n\t6: Number of students");
		Dprintf("\n\t7: View student form end");
		Dprintf("\n\t8: Middle of list");
		Dprintf("\n\t9: Reverse list");
		Dprintf("\n\t10: exit");
		Dprintf("\nEnter option number: ");
		int choice;
		scanf("%d",&choice);
        Dprintf("=======================\n");
		switch(choice)
		{
		case 1:
			Add_Student();
			break;
		case 2:
			Delete_Student();
			break;
		case 3:
			View_Students();
			break;
		case 4:
			Delete_All();
			break;
		case 5:
			GetNth(students_list);
			break;
		case 6:
			number_of_student();
			break;
		case 7:
			GetNth_from_end(students_list);
			break;
		case 8:
			middle_of_list();
		    break;
		case 9:
			Reverse_list();
		    break;
		case 10:
			exit(0);
			break;
		default:
			Dprintf("invalid choice... Try Again\n");
			break;
		}
	}
	return EXIT_SUCCESS;
}
