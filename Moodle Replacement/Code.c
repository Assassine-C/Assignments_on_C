#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Exam_Type{
    WRITTEN,
    DIGITAL
};

// Union stores either duration of exam or software of exam
union ExamInfo{
    int duration;
    char software[256];
};

struct Student{
    int student_id;
    char name[256];
    char faculty[256];
};

struct Exam{
    int exam_id;
    enum Exam_Type exam_type;
    union ExamInfo exam_info;
};

struct ExamGrade{
    int exam_id;
    int student_id;
    int grade;
};

// Function takes a sting of duration and checks (40 <= duration <= 180)
int check_duration(char info[256]){
    int duration = atoi(info);
    if ((duration >= 40) && (duration <= 180)){
        return 1;
    } return -1; 
}

// Function takes string of name
// Function return -1 if name include something else of letters or name is not under
// conditions of length otherwise (if everything is OK) function return 1 
int check_name(char name[256]){
    for (int i = 0; i < strlen(name); i++){
        if ((name[i] < 65) || (name[i] > 122) || ((90 < name[i]) && (name[i] < 97))){
            return -1;
        }
    }
    if ((strlen(name) > 1) && (strlen(name) < 20)){
        return 1;
    } return -1;
}

// Function takes string of fuculty
// Function return -1 if faculty include something else of letters or faculty is not under
// conditions of length otherwise (if everything is OK) function return 1 
int check_faculty(char faculty[256]){
    for (int i = 0; i < strlen(faculty); i++){
        if ((faculty[i] < 65) || (faculty[i] > 122) || ((90 < faculty[i]) && (faculty[i] < 97))){
            return -1;
        }
    }
    if ((strlen(faculty) > 4) && (strlen(faculty) < 30)){
        return 1;
    } return -1;
}

// Function takes string of software
// Function return -1 if software include something else of letters or software is not under
// conditions of length otherwise (if everything is OK) function return 1 
int check_software(char software[256]){
    for (int i = 0; i < strlen(software); i++){
        if ((software[i] < 65) || (software[i] > 122) || ((90 < software[i]) && (software[i] < 97))){
            return -1;
        }
    }
    if ((strlen(software) > 2) && (strlen(software) < 20)){
        return 1;
    } return -1;
}

// Function strings of exam type and exam info
// Function return -3 if input of exam type include something else of allowed types
// Function return -4 if exam info (duration) does not match the conditions
// Function return -5 if exam info (software) does not match the conditions
// Function return 1 if everything is OK
int check_type_of_exam(char type_of_exam[256], char exam_info[256]){
    if (strcmp(type_of_exam, "WRITTEN") != 0 && strcmp(type_of_exam, "DIGITAL") != 0){
        return -3;
    } else if (strcmp(type_of_exam, "WRITTEN") == 0){
        if (check_duration(exam_info) == -1){
            return -4;
        } return 1;
    } else if (strcmp(type_of_exam, "DIGITAL") == 0){
        if (check_software(exam_info) == -1){
            return -5;
        } return 1;
    }
}

// Function takes integer student_id, array of all students, and integer number of students
// Function return -2 if student id does not match the condition (0 < id < 1000)
// Function return -1 if student id is in our database
// Function return 1 if student id is not in our database
int check_student_id(int id, struct Student students[1000], int number_of_students){
    if ((id <= 0) || (id >= 1000)){
        return -2;
    }
    if (number_of_students != 0){
        for (int i = 0; i < number_of_students; i++){
            if (students[i].student_id == id){
                return -1;
            }
        }
    } return 1;
}

// Function takes integer exam_id, array of all exams, and integer number of exams
// Function return -2 if exam id does not match the condition (0 < id < 500)
// Function return -1 if exam id is in our database
// Function return 1 if exam id is not in our database
int check_exam_id(int id, struct Exam exams[1000], int number_of_exams){
    if ((id <= 0) || (id >= 500)){
        return -2;
    }
    if (number_of_exams != 0){
        for (int i = 0; i < number_of_exams; i++){
            if (exams[i].exam_id == id){
                return -1;
            }
        }
    } return 1;
}

// Function takes integer grade and checks (0 <= grade <= 100)
int check_grade(int grade){
    if ((grade >= 0) && (grade <= 100)){
        return 1;
    } return -1; 
}

// Function takes integer student_id, array of all students, and integer number of students
// Function finds the index of student with id in array of all students and return it
int search_student(int student_id, struct Student students[1000],  int number_of_student){
    for (int i = 0; i < number_of_student; i++){
        if (students[i].student_id == student_id){
            return i;
        }
    }
}

// Function takes integer exam_id, array of all exams, and integer number of exams
// Function finds the index of exam with id in array of all exams and return it
int search_exam(int exam_id, struct Exam exams[1000],  int number_of_exam){
    for (int i = 0; i < number_of_exam; i++){
        if (exams[i].exam_id == exam_id){
            return i;
        }
    }
}

// Function takes integer student_id, , integer exam_id, array of all grades, and integer number of grades
// Function finds the index of grade of particular student and exam in array of all grades and return it
int search_exam_grade(int student_id, int exam_id, struct ExamGrade grades[1000], int number_of_grade){
    for (int i = 0; i < number_of_grade; i++){
        if ((grades[i].student_id == student_id) && (grades[i].exam_id == exam_id)){
            return i;
        }
    }
}


int main(){
    // Open input and output files for reading and writing
    FILE* input;
    FILE* output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    // Create variables of numbers and arrays of students, exams, and grades to store data of it
    int number_of_students = 0;
    int number_of_exams = 0;
    int number_of_grade = 0;
    struct Student students[1000];
    struct Exam exams[1000];
    struct ExamGrade grades[1000];

    // Read command of string and complete tasks of the command, until there is command "END"
    char command[256];
    fscanf(input, "%s", command);
    int flag = 0;
    while (strcmp(command, "END") != 0){

        // Read student_id, name, and faculty from input file, check that all elements match the conditions
        // If there is an error, write to output about it
        // Otherwise add new student to array of students and write about successful command implementation
        if (strcmp(command, "ADD_STUDENT") == 0){
            int student_id;
            char name[256];
            char faculty[256];
            fscanf(input, "%d%s%s", &student_id, name, faculty);
            if (check_student_id(student_id, students, number_of_students) == -2){
                fprintf(output, "Invalid student id\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_student_id(student_id, students, number_of_students) == -1){
                fprintf(output, "Student: %d already exists\n", student_id);
                fscanf(input, "%s", command);
                continue;
            } else if (check_name(name) == -1){
                fprintf(output, "Invalid name\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_faculty(faculty) == -1){
                fprintf(output, "Invalid faculty\n");
                fscanf(input, "%s", command);
                continue;
            }
            students[number_of_students].student_id =  student_id;
            strcpy(students[number_of_students].name, name);
            strcpy(students[number_of_students].faculty, faculty);
            number_of_students++;
            fprintf(output, "Student: %d added\n", student_id);
            fscanf(input, "%s", command);

        // Read examt_id, exam_type, and exam_info from input file, check that all elements match the conditions
        // If there is an error, write to output about it
        // Otherwise add new exam to array of exams and write about successful command implementation
        } else if (strcmp(command, "ADD_EXAM") == 0){
            int exam_id;
            char exam_type[256];
            char exam_info[256];
            fscanf(input, "%d%s%s", &exam_id, exam_type, exam_info);
            if (check_exam_id(exam_id, exams, number_of_exams) == -1){
                fprintf(output, "Exam: %d already exists\n", exam_id);
                fscanf(input, "%s", command);
                continue;
            } else if (check_exam_id(exam_id, exams, number_of_exams) == -2){
                fprintf(output, "Invalid exam id\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_type_of_exam(exam_type, exam_info) == -3){
                fprintf(output, "Invalid exam type\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_type_of_exam(exam_type, exam_info) == -4){
                fprintf(output, "Invalid duration\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_type_of_exam(exam_type, exam_info) == -5){
                fprintf(output, "Invalid software\n");
                fscanf(input, "%s", command);
                continue;
            }
            exams[number_of_exams].exam_id =  exam_id;
            if (strcmp(exam_type, "WRITTEN") == 0){
                exams[number_of_exams].exam_type = 0;
                exams[number_of_exams].exam_info.duration = atoi(exam_info);
            } else {
                exams[number_of_exams].exam_type = 1;
                strcpy(exams[number_of_exams].exam_info.software, exam_info);
            }
            number_of_exams++;
            fprintf(output, "Exam: %d added\n", exam_id);
            fscanf(input, "%s", command);

        // Read exam_id, student_id, and grade from input file, check that all elements match the conditions
        // If there is an error, write to output about it
        // Otherwise add new grade to array of grades and write about successful command implementation
        } else if (strcmp(command, "ADD_GRADE") == 0){
            int exam_id;
            int student_id;
            int grade;
            fscanf(input, "%d%d%d", &exam_id, &student_id, &grade);
            if (check_exam_id(exam_id, exams, number_of_exams) == -2){
                fprintf(output, "Invalid exam id\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_exam_id(exam_id, exams, number_of_exams) == 1){
                fprintf(output, "Exam not found\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_student_id(student_id, students, number_of_students) == -2){
                fprintf(output, "Invalid student id\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_student_id(student_id, students, number_of_students) == 1){
                fprintf(output, "Student not found\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_grade(grade) == -1){
                fprintf(output, "Invalid grade\n");
                fscanf(input, "%s", command);
                continue;
            }
            grades[number_of_grade].exam_id =  exam_id;
            grades[number_of_grade].student_id =  student_id;
            grades[number_of_grade].grade =  grade;
            number_of_grade++;
            fprintf(output, "Grade %d added for the student: %d\n", grade, student_id);
            fscanf(input, "%s", command);

        // Read student_id and check that element matches the conditions
        // If there is an error, write to output about it
        // Otherwise write to output student_id, name, and faculty
        } else if (strcmp(command, "SEARCH_STUDENT") == 0){
            int student_id;
            fscanf(input, "%d", &student_id);
            if (check_student_id(student_id, students, number_of_students) == -2){
               fprintf(output, "Invalid student id\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_student_id(student_id, students, number_of_students) == 1){
                fprintf(output, "Student not found\n");
                fscanf(input, "%s", command);
                continue; 
            }
            int i = search_student(student_id, students, number_of_students);
            fprintf(output, "ID: %d, Name: %s, Faculty: %s\n", student_id, students[i].name, students[i].faculty);
            fscanf(input, "%s", command);

        // Read exam_id, student_id and check that elements match the conditions
        // If there is an error, write to output about it
        // Otherwise write to output exam_id, student_id, name of student, student's grade, type anf info of exam
        } else if (strcmp(command, "SEARCH_GRADE") == 0){
            int exam_id;
            int student_id;
            fscanf(input, "%d%d", &exam_id, &student_id);
            if (check_exam_id(exam_id, exams, number_of_exams) == -2){
                fprintf(output, "Invalid exam id\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_exam_id(exam_id, exams, number_of_exams) == 1){
                fprintf(output, "Exam not found\n");
                fscanf(input, "%s", command);
                continue; 
            }else if (check_student_id(student_id, students, number_of_students) == -2){
                fprintf(output, "Invalid student id\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_student_id(student_id, students, number_of_students) == 1){
                fprintf(output, "Student not found\n");
                fscanf(input, "%s", command);
                continue; 
            }
            int i = search_student(student_id, students, number_of_students);
            int j = search_exam_grade(student_id, exam_id, grades, number_of_grade);
            int k = search_exam(exam_id, exams, number_of_exams);
            char exam_type[256];
            if (exams[k].exam_type == 0){
                char exam_type[256] = "WRITTEN";
                fprintf(output, "Exam: %d, Student: %d, Name: %s, Grade: %d, Type: %s, Info: %d\n", 
            exam_id, student_id, students[i].name, grades[j].grade, exam_type, exams[k].exam_info.duration);
            } else {
                char exam_type[256] = "DIGITAL";
                fprintf(output, "Exam: %d, Student: %d, Name: %s, Grade: %d, Type: %s, Info: %s\n", 
            exam_id, student_id, students[i].name, grades[j].grade, exam_type, exams[k].exam_info.software);
            }
            fscanf(input, "%s", command);

        // Read exam_id, new type, and new info of exam, then check that elements match the conditions
        // If there is an error, write to output about it
        // Otherwise update information of exam in array of exam and write about successful command implementation
        } else if (strcmp(command, "UPDATE_EXAM") == 0){
            int exam_id;
            char new_exam_type[256];
            char new_exam_info[256];
            fscanf(input, "%d%s%s", &exam_id, new_exam_type, new_exam_info);
            if (check_type_of_exam(new_exam_type, new_exam_info) == -3){
                fprintf(output, "Invalid exam type\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_type_of_exam(new_exam_type, new_exam_info) == -4){
                fprintf(output, "Invalid duration\n");
                fscanf(input, "%s", command);
                continue;
            } else if (check_type_of_exam(new_exam_type, new_exam_info) == -3){
                fprintf(output, "Invalid software\n");
                fscanf(input, "%s", command);
                continue;
            }
            int i = search_exam(exam_id, exams, number_of_exams);
            if (strcmp(new_exam_type, "WRITTEN") == 0){
                exams[number_of_exams].exam_type = 0;
                exams[number_of_exams].exam_info.duration = atoi(new_exam_info);
            } else {
                exams[number_of_exams].exam_type = 1;
                strcpy(exams[i].exam_info.software, new_exam_info);
            }
            fprintf(output, "Exam: %d updated\n", exam_id);
            fscanf(input, "%s", command);

        // Read exam_id, student_id, and new grade, then check that new grade matches the conditions
        // If there is an error, write to output about it
        // Otherwise update information of student's grade in array of grades and write about successful command implementation
        } else if (strcmp(command, "UPDATE_GRADE") == 0){
            int exam_id;
            int student_id;
            int new_grade;
            fscanf(input, "%d%d%d", &exam_id, &student_id, &new_grade);
            if (check_grade(new_grade) == -1){
                fprintf(output, "Invalid grade\n");
                fscanf(input, "%s", command);
                continue;
            }
            int i = search_exam_grade(student_id, exam_id, grades, number_of_grade);
            grades[i].grade = new_grade;
            fprintf(output, "Grade %d updated for the student: %d\n", new_grade, student_id);
            fscanf(input, "%s", command);

        // Read student_id from input file and delete student's id from all arrays
        // In this program delete student's id equal to delete student and all information of the grades
        // Write to output file about successful command implementation
        } else if (strcmp(command, "DELETE_STUDENT") == 0){
            int student_id;
            fscanf(input, "%d", &student_id);
            for (int i = 0; i < number_of_students; i++){
                if (students[i].student_id == student_id){
                    students[i].student_id = 0;
                    break;
                }
            }
            for (int i = 0; i < number_of_grade; i++){
                if (grades[i].student_id == student_id){
                    grades[i].student_id = 0;
                    grades[i].exam_id = 0;
                    grades[i].grade = 0;
                }
            }
            fprintf(output, "Student: %d deleted\n", student_id);
            fscanf(input, "%s", command);

        // Write to output list of students' ids, names, faculties from array of students
        } else if (strcmp(command, "LIST_ALL_STUDENTS") == 0){
            for (int i = 0; i < number_of_students; i++){
                if (students[i].student_id != 0){
                    fprintf(output, "ID: %d, Name: %s, Faculty: %s\n", students[i].student_id, students[i].name, students[i].faculty);
                }
            }
            fscanf(input, "%s", command);
        }
    }

    // Close the input and output files
    fclose(input);
    fclose(output);
    return 0;
}