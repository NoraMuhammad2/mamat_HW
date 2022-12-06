
#include "linked-list.h"
#include "grades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct course{
    int course_grade;
    char *course_name;
} Course;

typedef struct student{
    int id;
    char *student_name;
    struct list* listCourse;//defining a list of the courses for each student
} Student;

typedef struct grades{
    struct list* students;
} Grade;


int clone_course(Course *source, Course **dist){ 
    Course* copy= malloc(sizeof(Course));
    copy->course_grade = source->course_grade;
    copy->course_name = (char*)malloc(strlen(source->course_name)+1);
    strcpy(copy->course_name,source->course_name);
    *dist=copy;
    return 0;
    }
void destroy_course(Course *Mycourse);
void destroy_student(Student *Mystudent);

int  clone_student(Student *source, Student **dist){
    Student* copy= malloc(sizeof(Student));
    copy->id = source->id;
    copy->student_name = (char*)malloc((strlen(source->student_name) + 1));
    strcpy(copy->student_name,source->student_name);
    copy->listCourse= list_init((element_clone_t)clone_course,
                                     (element_destroy_t)destroy_course );
    struct iterator *source_it = list_begin(source->listCourse);
    struct iterator *check_it = list_begin(copy->listCourse);
    Course *source_course=list_get(source_it);
    int listSI=(int)list_size(source->listCourse);
    if(listSI) {
        list_push_front(copy->listCourse, source_course);
        check_it = list_begin(copy->listCourse);
    }
    int i=0;
    while(i<listSI-1){// copying each index in the list
    	source_it = list_next(source_it);
        source_course = list_get(source_it);
        list_insert(copy->listCourse,check_it,source_course);
        check_it = list_next(check_it);
        i++;
     }   
    *dist=copy;
    return 0;  
}

void destroy_course(Course *Mycourse){ 
    free(Mycourse->course_name);// because we use malloc
    free(Mycourse);
}

void destroy_student(Student *Mystudent){ 
    list_destroy(Mystudent->listCourse);// because we use malloc
    free(Mystudent->student_name);
    free(Mystudent);
}
void grades_destroy(struct grades *grades){
	list_destroy(grades->students);
	free(grades);
}
struct grades* grades_init(){
    Grade* grades_aux=malloc(sizeof (Grade));
    element_clone_t t1 = (element_clone_t) clone_student;
    element_destroy_t t2 = (element_destroy_t) destroy_student;
    grades_aux->students= list_init(t1, t2);
    return grades_aux;
    }
    
int grades_add_student(struct grades *grades, const char *name, int id){

	if(!grades){
        return 1;//failed
        }
	if (id<=0){
     	return 1;//failed
		}              
    struct iterator *index =list_begin(grades->students);
    // we will use this in order to check our current student
    Student *check_student;
    while(index!=NULL)
    {
        check_student=list_get(index);
        if(check_student->id==id)// if this is true then the id was inserted 
        {
            return  1;//failure;
        }
        index=list_next(index);
    }
    // if we get here then we will add a new student.
    Student *Mystudent=(struct student*)malloc(sizeof(Student));
    int Myname_len = (int)strlen(name) + 1;
    Mystudent->student_name=(char*)malloc(Myname_len);
     if(Mystudent == NULL) //checking that malloc worked correctly
        return 1;
    Mystudent->id=id;
    strcpy(Mystudent->student_name,name);
    Mystudent ->listCourse = list_init((element_clone_t)clone_course,
                                          (element_destroy_t)destroy_course);
    if((list_push_back(grades->students, Mystudent))==0){
        free(Mystudent->student_name);
        list_destroy(Mystudent->listCourse);
        free(Mystudent);
        
        return 0;
    }
    //if we get here then list_push_back failed 
    free(Mystudent->student_name);
    list_destroy(Mystudent->listCourse);
    free(Mystudent);
        
        return 1;
}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
                     
	if(!grades){
        return 1;
    }
	if (id<=0){
     return 1;
	}  
	if((grade<0) || (grade>100)){
 	 return 1;
 	}
 
  struct iterator *index =list_begin(grades->students);
      Student *check_student;
      Course *check_course;
  
     while(index!=NULL){
        check_student=list_get(index);
        if(check_student->id==id){
        struct iterator *index2 =list_begin(check_student->listCourse);
          while(index2!=NULL){
          check_course=list_get(index2);
          if(!strcmp(check_course->course_name,name)){ 
          return 1;
          }
          index2= list_next(index2);
          }
          //if we get here then, the course not found. 
          Course *Mycourse=(struct course*)malloc(sizeof(Course));
          int Mycourse_len = (int)strlen(name) + 1;
          Mycourse->course_name=(char*)malloc(Mycourse_len);
          if(Mycourse == NULL) //checking that malloc worked correctly
           return 1;
          Mycourse->course_grade=grade;
         strcpy(Mycourse->course_name,name);
         if((list_push_back(check_student->listCourse, Mycourse))==0){
          free(Mycourse->course_name);
          free(Mycourse);
           return 0;
        }
        //if we get here then list_push_back failed
          else{
          free(Mycourse->course_name);
          free(Mycourse);
          return 1;
          }
        }
        else {
        index= list_next(index);
        
        }
  }
  return 1;           
 }

int grades_print_student(struct grades *grades, int id){
	
	if(!grades){
	return 1;
	}
	if(id <=0){
	return 1;
	}
	Student *aux_student;
    Course *aux_course;
	struct iterator *index = list_begin(grades->students);
    while(index!=NULL)
    {
        aux_student = list_get(index);
        if(aux_student->id == id)
        {	
        	int current_id=aux_student->id;
            printf("%s %d:",aux_student->student_name,current_id);
            struct iterator *index2 = list_begin(aux_student->listCourse);
            // we print the first course here to prevent adding ","
            if(index2!=NULL){ 
            	aux_course = list_get(index2);
            	int current_grade=aux_course->course_grade;
      	    	printf(" %s %d",aux_course->course_name,current_grade);
    	       index2 = list_next(index2);
    	       }
            while(index2!=NULL)
            {
            	printf(",");
                aux_course = list_get(index2);
            	int current_grade=aux_course->course_grade;
                printf(" %s %d",aux_course->course_name,current_grade);
                index2 = list_next(index2);
            }
            printf("\n");// we passed on all the grades of the current student
            return 0;
        }
        else
        {
            index = list_next(index);
        }
    }
    return 1;// if we get here then something failed..
}

int grades_print_all(struct grades *grades){
if(!grades){
return 1;
}
struct iterator *index =list_begin(grades->students);
Student *My_student;
while (index){
My_student= list_get(index);
grades_print_student(grades, My_student->id);
index= list_next(index);

}
return 0;

}

 float grades_calc_avg(struct grades *grades, int id, char **out){

	if(!grades){
	*out=NULL;
	return -1;//false
	}
	if(id <=0){
	*out=NULL;
	return -1;//false
	}
	int count=0;
	int total=0;
	struct iterator *index = list_begin(grades->students);
	Student *aux_student;
	Course *aux_course;
	 while(index!=NULL)
    {
        aux_student = list_get(index);
        if(aux_student->id == id)
        {
        	*out = (char *)malloc((strlen(aux_student->student_name)+1));
        	// copy the name of the student to out.
        	strcpy(*out,aux_student->student_name);	
            struct iterator *index2 = list_begin(aux_student->listCourse);
            // count all the grades of the current student
           while(index2!=NULL){ 
            	aux_course = list_get(index2);
            	int current_grade=aux_course->course_grade;
    	        index2 = list_next(index2);// go for the next grade.
    	        total=total+current_grade; //count the sum of the grades.
    	        count++;//count the grades number.
    	       }
    	       if(count==0){//there is no grades!!
    	       return 0;
    	       }
    //if we get here then we ended counting the grades of the current student
    	       float avr=((float)total/(float)count);
    	       return avr;   
        }
        else // go for the next student.
        {
            index = list_next(index);
        }
    }
    return -1;//if we get here then something failed
}
	
	

