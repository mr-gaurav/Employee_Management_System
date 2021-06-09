#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct EmployeeData
{
    char Employee_Firstname[10];
    char Employee_Lastname[10];
    int Employee_age;
    char Employee_designation[20];
    float Employee_salary;
};

void main()
{

    FILE *filePtr, *tempfilePtr;
    const char *filename = "EmployeeDatabase.dat";
    const char *tempfilename = "temp.dat";
    int count;

    struct EmployeeData Employee;
    long int SizeofStructEmployee = sizeof(Employee);
    char modify_employee_name[10], delete_employee_name[10];

    filePtr = fopen(filename, "rb+");
    if (filePtr == NULL)
    {
        filePtr = fopen(filename, "wb+");
        if (filePtr == NULL)
        {
            printf("SORRY! UNABLE TO OPEN %s\n", filename);
            exit(1);
        }
    }

    printf("===========Welcome To Employee Management System==============\n");
    char Choice, nextChoice;

    while (1)
    {
        fseek(filePtr, 0, SEEK_END);
        printf("\n1. Add a new Employee. ");
        printf("\n2. Remove an existing Employee. ");
        printf("\n3. Modify an employee details. ");
        printf("\n4. Print all employee details. ");
        printf("\n5. Exit. ");
        printf("\n\nEnter your choice: ");
        fflush(stdin);
        scanf("%c", &Choice);

        switch (Choice)
        {
        case '1': //add employee
            nextChoice = 'y';

            while (nextChoice == 'y' || nextChoice == 'Y')
            {
                fflush(stdin);
                printf("\nEnter Employee First Name: ");
                scanf("%s", &Employee.Employee_Firstname);
                printf("Enter Employee Last Name: ");
                scanf("%s", &Employee.Employee_Lastname);
                printf("Enter Employee Age: ");
                scanf("%d", &Employee.Employee_age);
                printf("Enter Employee Designation: ");
                scanf("%s", &Employee.Employee_designation);
                printf("Enter Employee salary: ");
                scanf("%f", &Employee.Employee_salary);

                fwrite(&Employee, SizeofStructEmployee, 1, filePtr);
                printf("\n %s is successfully added as a new Employee!", Employee.Employee_Firstname);

                printf("\nDo you want to add another Employee?(y/n): ");
                fflush(stdin);
                scanf("\n%c", &nextChoice);
            }
            break;

        case '2': //delete employee
            nextChoice = 'y';

            while (nextChoice == 'y' || nextChoice == 'Y')
            {
                printf("\nEnter the name of Employee you want to delete: ");
                fflush(stdin);
                scanf("%s", &delete_employee_name);

                tempfilePtr = fopen(tempfilename, "wb+");
                fseek(filePtr, 0, SEEK_SET);
                while (fread(&Employee, SizeofStructEmployee, 1, filePtr) == 1)
                {
                    if (strcmp(Employee.Employee_Firstname, delete_employee_name) != 0)
                    {
                        fwrite(&Employee, SizeofStructEmployee, 1, tempfilePtr);
                    }
                }
                // fseek(tempfilename, 0, SEEK_SET);
                // if (tempfilename == EOF)
                //     printf("%s does not found in the Database!", delete_employee_name);
                // else
                //     printf("\n %s removed successfully!", delete_employee_name);

                fclose(filePtr);
                fclose(tempfilePtr);
                remove(filename);
                rename(tempfilename, filename);
                filePtr = fopen(filename, "rb+");

                printf("\n %s removed successfully!", delete_employee_name);
                printf("\nDo you want to remove another Employee?(y/n): ");
                fflush(stdin);
                scanf("\n%c", &nextChoice);
            }

            break;

        case '3': //modify employee details
            nextChoice = 'y';
            while (nextChoice == 'y' || nextChoice == 'Y')
            {

                printf("Enter the Employee's first name you want to modify: ");
                fflush(stdin);
                scanf("%s", &modify_employee_name);
                rewind(filePtr); // or instead we can use fseek(filePtr, 0, SEEK_SET);

                while (fread(&Employee, sizeof(Employee), 1, filePtr) == 1)
                {
                    if (strcmp(Employee.Employee_Firstname, modify_employee_name) == 0)
                    {
                        printf("\n## Now, Modifing the details of Employee %s %s ##", Employee.Employee_Firstname, Employee.Employee_Lastname);
                        printf("\nEnter Changed First Name: ");
                        scanf("%s", &Employee.Employee_Firstname);
                        printf("Enter Changed Last Name: ");
                        scanf("%s", &Employee.Employee_Lastname);
                        printf("Enter Changed Age: ");
                        scanf("%d", &Employee.Employee_age);
                        printf("Enter Changed Designation: ");
                        scanf("%s", &Employee.Employee_designation);
                        printf("Enter Changed salary: ");
                        scanf("%f", &Employee.Employee_salary);

                        fseek(filePtr, -SizeofStructEmployee, SEEK_CUR);
                        fwrite(&Employee, SizeofStructEmployee, 1, filePtr);
                        printf("\n Employee details updated successfully!");

                        printf("\nDo you want to add another Employee?(y/n): ");
                        fflush(stdin);
                        scanf("\n%c", &nextChoice);
                        break;
                    }
                }
            }
            break;

        case '4': //print whole database
            fseek(filePtr, 0, SEEK_SET);
            count = 1;
            printf("\n\n##########################################################\n");
            printf("############## Printing the Database of Employee #############\n");
            while (fread(&Employee, SizeofStructEmployee, 1, filePtr) == 1)
            {
                printf("\n------------------------------------------------");
                printf("\nEmployee Count: %d", count++);
                printf("\nEmployee Name= %s %s", Employee.Employee_Firstname, Employee.Employee_Lastname);
                printf("\nAge: %d", Employee.Employee_age);
                printf("\nDesignation : %s", Employee.Employee_designation);
                printf("\nSalary : INR %.2f", Employee.Employee_salary);
                printf("\n------------------------------------------------\n");
            }
            printf("\n\n################  END  ##########################\n");
            break;

            //exit
        case '5':
            fclose(filePtr);
            exit(0);
        default:
            break;
        }
    }
}
