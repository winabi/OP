#include <iostream>


struct Students
{
    unsigned int studentID;
    char surname[20];
    int grades[8];
};  

int strlen(const char* str) {
    int counter = 0;

    while (*str != '\0'){
        counter++;
        str++;
    }
    return counter;

}

void printStudent(const Students& student)
{
    std::printf("\033[3m Student ID number: \033[0m %d. \033[3m Surname:  \033[0m %s. \033[3m Grades for the last session as an array of integers: \033[0m   ",
        student.studentID, student.surname); 
    for (int i = 0; i < 8; i++)
    {
        std::printf("%d ", student.grades[i]);
    }

    std::printf("\n");
}

void sortBySurname(Students** arr, int size)
{
    bool mustSort;  
                   
    do
    {
        mustSort = false;

        for (int i = 0; i < size - 1; i++)
        {
            int one = strlen(arr[i] -> surname);
            int two = strlen(arr[i + 1]-> surname);
            if (strlen(arr[i] -> surname) > strlen(arr[i + 1]-> surname))
            {
                Students* temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                mustSort = true;

            }
        }
    } 
    while (mustSort);
}

void printStudentArray(Students** arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printStudent(*arr[i]);
        
    }
}


void printIf(const Students studentss[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (studentss[i].studentID%2!=0) {
            printStudent(studentss[i]);
        }
    }
}

int main()
{
    std::setlocale(LC_ALL, "UKRAINIAN");
    const int n = 4;
    
    Students studentss[n] = { 
        { 83182387, "Hryhorieva", {100,100,100,100,100,100,100,100}},
        { 72381738, "Ivaniv", {100,100,100,100,100,100,100,100} },
        { 54618213, "Kychma", {100,100,100,100,100,100,100,100} },
        { 54622213, "Konstantinov", {100,100,100,100,100,100,100,100} }
    };
    
    
    Students* pointers[n];
    for (int i = 0; i < n; i++)
    {
        pointers[i] = &studentss[i];
    }

    std::printf(" \033[1m An example of a function that displays student data in the console \033[0m \n");
    printStudent(studentss[0]);

    std::printf("\n \033[1m A function that sorts an array by the following attribute: By increasing length of the last name \033[0m \n");
    sortBySurname(pointers, n);
    printStudentArray(pointers, n);

    std::printf("\n \033[1m A function that searches for student data that meets the following condition: With odd student ID numbers \033[0m \n"); 
    printIf(studentss, n);

    return 0;
}