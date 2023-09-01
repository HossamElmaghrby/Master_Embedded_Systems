/*
 * SLL_Student.c
 *
 *  Created on: Aug 29, 2023
 *      Author: elmag
 */
#include "SLL_Student.h"
extern Student_SLL *students_list ;

void fill_info(node*NewStudent)
{
	Dprintf("Enter the name: ");
	gets (NewStudent->data.name);
	gets (NewStudent->data.name);
	int ID;
	Dprintf("Enter the ID: ");
	scanf("%d",&ID);
	NewStudent->data.ID=ID;

	float height;
	Dprintf("Enter height: ");
	scanf("%f",&height);
	NewStudent->data.height=height;
}

void Add_Student()
{
	node* NewStudent ;
	NewStudent=(node*)malloc(sizeof(node));
	if(students_list==NULL) // if the list is empty
	{
		students_list=(Student_SLL*)malloc(sizeof(Student_SLL));
		students_list->head= students_list->tail=(node*)NewStudent ;
	}
	else
	{
		students_list->tail->next=NewStudent;
		students_list->tail=(node*)NewStudent;
	}
	fill_info(NewStudent);
	NewStudent->next=NULL;
}
void Delete_Student()
{
	bool is_found=false;
	if(students_list==NULL)
	{
		Dprintf("The list is already empty\n");
	}
	else
	{
		int ID ;
		Dprintf("Enter Student ID to be deleted: ");
		scanf("%d",&ID);
		node* cur=students_list->head ;
		node* prev=NULL;
		while(cur)
		{
			if(cur->data.ID==ID)
			{
				if(prev==NULL)
				{
					students_list->head=(node*)cur->next;
					if(students_list->head==NULL)
						students_list=NULL ;
				}
				else
					prev->next=cur->next;
				free(cur);
				is_found =true ;
				break;
			}
			prev =cur ;
			cur=(node*)cur->next;
		}
		if(!is_found)
		{
			Dprintf("\n cannot find student ID. \n");
		}

	}
}
void View_Students()
{
	if(students_list==NULL)
	{
		Dprintf("Empty list\n");
	}
	else
	{
		node* cur= students_list->head ;
		int count = 1;
		while(cur)
		{
			Dprintf("student number: %d \n",count++);
			Dprintf("ID: %d\n",cur->data.ID);
			Dprintf("Name: %s\n",cur->data.name);
			Dprintf("Height: %.2f\n",cur->data.height);
			cur=(node*)cur->next;
			Dprintf("   ----------------\n")
		}
	}
}
void Delete_All()
{
	if(students_list==NULL)
	{
		Dprintf("Empty list\n");
	}
	else
	{
		node* cur= students_list->head ;
		while(cur)
		{
			node* temp=cur;
			cur=(node*)cur->next;
			free(temp);
		}
		students_list=NULL;
	}
}
void View_student(Sdata student)
{

	Dprintf("ID: %d\n",student.ID);
	Dprintf("Name: %s\n",student.name);
	Dprintf("Height: %.2f\n",student.height);
	Dprintf("   ----------------\n")
}
void GetNth(Student_SLL *list)
{
	if(students_list==NULL)
	{
		Dprintf("Empty list\n");
	}
	else
	{
		int index;
		Dprintf("Enter the index of student: ");
		scanf("%d",&index);
		node* cur=list->head ;
		int count = index;
		bool isfound=true ;
		while(--count)
		{
			cur=(node*)cur->next ;
			if(cur==NULL)
			{
				Dprintf("Out of bounds\n");
				isfound=false ;
				break ;
			}
		}
		if(isfound)
		{
			Dprintf("student number: %d \n",index);
			View_student(cur->data);
		}
	}
}
int getCount(node* count)
{
	if(count==NULL)
		return 0 ;
	return 1+getCount((node*)count->next) ;
}

void number_of_student()
{
	if(students_list==NULL)
	{
		Dprintf("Empty list\n");
	}
	else
	{
		int length=getCount(students_list->head);
		Dprintf("Number of students is %d\n",length);
	}
}

void GetNth_from_end(Student_SLL *list)
{
	if(students_list==NULL)
	{
		Dprintf("Empty list\n");
	}
	else
	{
		int index;
		Dprintf("Enter the index of student: ");
		scanf("%d",&index);
		int count=index;
		node* ref =list->head ;
		node* tar =list->head ;
		int length=getCount(ref);
		if(length < index)
		{
			Dprintf("Out of bounds\n");
		}
		else
		{
			while(count--)
			{
				ref =(node*)ref->next ;
			}
			while(ref)
			{
                ref = (node*)ref->next;
                tar = (node*)tar->next;
			}
			Dprintf("student number: %d \n",(length - index + 1));
			View_student(tar->data);
		}
	}
}

void middle_of_list()
{
	if(students_list==NULL)
	{
		Dprintf("Empty list\n");
	}
	else
	{
		int count=1;
		node*fast = students_list->head;
		node*slow = students_list->head;

		while(fast!=NULL && fast->next!=NULL)
		{
			fast=(node*)fast->next;
			fast=(node*)fast->next;

			slow=(node*)slow->next;
			count++;
		}
		Dprintf("student number: %d \n",count);
		View_student(slow->data);
	}
}
void Reverse_list()
{
	if(students_list==NULL)
	{
		Dprintf("Empty list\n");
	}
	else
	{
		node* prev=NULL ;
		node* cur=students_list->head;
		node* next =NULL;
		while(cur)
		{
			next=(node*)cur->next;
			cur->next=prev;
			prev=cur;
			cur=next;
		}
		students_list->tail=students_list->head ;
		students_list->head=prev;
	}
}


