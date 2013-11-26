/*
  A1 Synchronization problem code
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


#define MAX_STUDENTS 1000 // Maximum number of students in the simulation

typedef struct { //Information for each student
  char gender; //b or g
  int arrival_time;  // time between the arrival of this student and the previous student
} student_info;

//Commandline parameters
int max_groups; //Maximum number of groups to form
int group_size; //Size of each group

//You are responsible for maintaining and updating the following variables
int total_groups; //Complete groups formed so far (<= max_groups)
int grouped; //Number of students added to current group (<= group_size)

//Add further variables here, including synchronization variables


//Read student data and initialize variables

int initialize(student_info *si, char *filename) {
  FILE *fp;
  if (!(fp = fopen(filename, "r"))) {
    perror ("initialize");
    exit(EXIT_FAILURE);
  }
  int i =0;
  //Each line of the file contains b or g followed by
  //the number of seconds to wait after the previous student.
  while ( (i < MAX_STUDENTS) && 
   (fscanf(fp, "%c%d\n", &si[i].gender, &si[i].arrival_time) != EOF)) {   
    i++;
  }
  fclose(fp);
  return i;
}

//Code for boys

void * boy(void * num) {
  //Code executed by an arriving boy.
  //Write this!
}  

//Code for girls

void * girl(void * num) {
  //Code executed by an arriving boy.
  //Write this!
}  

int main(int argc, char * argv[]) {
  void * (*func) (void*);
  int i, num_students;
  char *filename;
  char gender;
  pthread_t tids[MAX_STUDENTS];
  student_info s_info[MAX_STUDENTS];
  if (argc != 4) {
    printf ("Usage: groups <student_file> <group_size> <max_groups>\n");
    exit (EXIT_FAILURE);
  }
  filename = argv[1];
  group_size = atoi (argv[2]);
  max_groups = atoi(argv[3]);

  num_students = initialize(s_info, filename);
  if (num_students > MAX_STUDENTS || num_students <= 0) {
    printf("Error: bad number of students read from input file.\n");
    exit (EXIT_FAILURE);
  }

  printf("Simulating with %d students ...\n", num_students);
  //Add code here to initialize synchronization variables
  
  //Create student threads
  for (i = 0; i < num_students; i++) {
    sleep(s_info[i].arrival_time); //Wait for arrival
    gender = s_info[i].gender;
    if (gender == 'b') {
      func = boy; 
      printf ("\nStudent %d (boy) enters the room...\n", i);
    } else {
      func = girl;
      printf ("\nStudent %d (girl) enters the room...\n", i);
    }
    if(pthread_create(&tids[i], NULL, func, (void*)i)) {
      printf("\n ERROR creating thread %d.\n", i);
      exit(EXIT_FAILURE);
    }
  }
  //Wait for all threads to terminate
  for (i = 0; i < num_students; i++) {
    if(pthread_join(tids[i], NULL)) {
      printf("\n ERROR joining thread %d\n.", i);
      exit(EXIT_FAILURE);
    }
  }
  printf ("Simulation complete!\n");
  
  return 0;
}
