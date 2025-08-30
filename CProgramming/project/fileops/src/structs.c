#include <stdio.h>
#include <string.h>

int main(){
    
    struct employee {
        char name[50];
        int hireDate;
        float salary;
    };

    struct employee emp1;
    strcpy(emp1.name, "Bharath");
    emp1.hireDate = 12;
    emp1.salary = 120.42;

    printf("Employee %s, was hired on %d, on a salary of %f\n",emp1.name, emp1.hireDate, emp1.salary);

    struct employee emp2 = {"Kavery", 42, 999.89};
    printf("Employee %s, was hired on %d, on a salary of %f\n",emp2.name, emp2.hireDate, emp2.salary);


    struct employee emp3;
    printf("Enter emp3's name: ");
    scanf("%s", emp3.name);
    printf("Enter emp3's hire date: ");
    scanf("%i", &emp3.hireDate);
    printf("Enter emp3's salary: ");
    scanf("%f", &emp3.salary);

    printf("Employee %s, was hired on %d, on a salary of %f\n",emp3.name, emp3.hireDate, emp3.salary);

    
    return 0;
}
