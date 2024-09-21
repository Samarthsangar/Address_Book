/*----------------------------------------------------ADDRESS BOOK-----------------------------------------------------------------*/
/*
Name : Samarth Rajendra Sangar.
Date : 28/08/2024
Project name : Address Book.
Sample input : --------Menu---------
               1.Adding_details
               2.Print_details
               3.Search_details
               4.Edit_details
               5.Delete_details
               Enter your choice : 3
Sample output : --------Menu---------
                1.Mobile
                2.Email
                Enter any one : 1
                Enter Mobile Number to check detail's: 9527148421
                ------------------------------------------------------------------------------
                ----------------------------------Address Book--------------------------------
                ------------------------------------------------------------------------------
                Name                Mobile              Email                         Address
                ------------------------------------------------------------------------------
                Samarth             9527148421          samarthsangar01@gmail.com     Kolhapur
                ------------------------------------------------------------------------------
                Do you want to continue (Y/N) : N
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Unicolour.h"                   //Header file for colour the prompt

struct Addressbook                      //stucture of name Addressbook
{
    char name[30];                      //stucture of member's
    char mobile[12];
    char email[35];
    char address[20];
};

//function prototype's
int backcheking(struct Addressbook ,int *, char *, char *);
int checking_mobile_emeil(char *,int );
int ascending(char,char);
int decending(char,char);
void loading(int);
void sort(int (*)(char,char));
void Adding_ditail(struct Addressbook , int *, int);
void Print_ditail(struct Addressbook , int *);
void Search_ditail(struct Addressbook , int *);
void Edit_ditail(struct Addressbook , int *);
void Delete_ditail(struct Addressbook , int *);

int main()
{
    struct Addressbook user;              //structure variable decleration
    static int user_count=0;
    char ch;
    int choice,repeat=1;
    loading(repeat);                      //function call loading data from main file to temp file
    while(repeat)
    {                                     //running loop with infinite iteration
        system("clear");
        printf(BRED"\n--------Menu---------\n"reset);
        printf(RED"1.Adding_details\n2.Print_details\n3.Search_details\n4.Edit_details\n5.Delete_details\n6.Exit\n");
        printf(WHT"Enter your choice : "reset);
        scanf("%d",&choice);               //taking a choice from user and based on choice function call
        switch(choice)
        {
            case 1 :
                    {   system("clear");
                        int count;
                        printf(BRED"How many number of information you want to add : "reset);
                        scanf("%d",&count);
                        printf(BRED"-->Adding %d details : \n"reset,count);
                        Adding_ditail(user,&user_count,count);                       //function call for adding data into file
                        break;
                    }
            case 2 :
                    Print_ditail(user,&user_count);              //function call for printing data
                    break;
            case 3 :
                    Search_ditail(user,&user_count);             //function call for search details
                    break;
            case 4 :
                    Edit_ditail(user,&user_count);               //function call for edit details
                    break;
            case 5 :
                    Delete_ditail(user,&user_count);             //function call for delete details
                    break;
            case 6 :
                    goto label4;
                    break;
            default :
                    printf(RED"Invalid choice \n");
        }
        printf(BRED"Do you want to continue (Y/N) : "reset);              //taking input for continue
        scanf(" %c",&ch);
        ch=='y'||ch=='Y'?(repeat):(repeat=0);
    }
    label4 :
    loading(repeat);                                             //function call before termination of program to load data on main file
}

void loading(int repeat)                                         //called function for load data based on condition
{
    char ch;
    if(repeat)                                                   //chcek parameter value load data 
    {
        FILE *fptr1=fopen("Addressbook.csv","r");
        FILE *fptr2=fopen("temp.csv","w");
        while((ch=fgetc(fptr1))!=EOF)                            //if 1 load data from main file to temp file
        {
            fputc(ch,fptr2);
        }
        fclose(fptr1);
        fclose(fptr2);
    }
    else                                                         //else load data from temp file to main file
    {
        FILE *fptr1=fopen("temp.csv","r");
        FILE *fptr2=fopen("Addressbook.csv","w");
        while((ch=fgetc(fptr1))!=EOF)
        {
            fputc(ch,fptr2);
        }
        fclose(fptr1);
        fclose(fptr2);
    }
}

int backcheking(struct Addressbook user,int *user_count, char *ch1 , char *ch2)   //called function to search detils and return value
{
    system("clear");  
    FILE *fptr=fopen("temp.csv","r");                            //opening temp file in reading mode
    fscanf(fptr,"%d",user_count);                                //fetching count to cursor move forword and skip this count
    while(!(feof(fptr)))                                         //running while loop at the EOF
    {
        fscanf(fptr,"\n%[^,],%[^,],%[^,],%[^\n]",user.name,user.mobile,user.email,user.address);        //fetching data in the file and storing into variable
        if(strcmp(ch1,user.mobile)==0 || strcmp(ch2,user.email)==0)     //compare data and if equal then print data and stop loop
        {
            system("clear");                                     //printing prompt to the user
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            printf(BWHT"\n--------------------------------"BRED"Address Book"BWHT"-------------------------------------\n");
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            printf(URED"Name\t\tMobile\t\tEmail\t\t\t\tAddress\n"reset);
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            printf(WHT"%-15.15s %-15.15s %-31.31s %-20.20s\n",user.name,user.mobile,user.email,user.address);
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            return 1;
        }
    }
    fclose(fptr);
    return 0;
}

int checking_mobile_emeil(char *ch, int pre)              //called function check mobile number and email
{
    if(pre)                   //cehck mobile and return value
    {
        for(int i=0; ch[i]!=0; i++)
        {
            if(strlen(ch)>10 || strlen(ch)<10)
                    return 1;
            if(!(ch[i]<='9' && ch[i]>='0'))
                    return 1;
        }
    }
    else{                                      //check email and return value
            char *ch1="@", *ch2=".com";
            if((((strstr(ch,ch1))==NULL) || ((strstr(ch,ch2))==NULL)))
                    return 1;
    }
    return 0;
}

int ascending(char a,char b)                //for acsending
{
    return a>b;
}

int decending(char a,char b)               //for Descending
{
    return a<b;
}

void sort(int (*f)(char,char))             //called function 
{
    char temp[40];
    int user_count;
    FILE *fptr=fopen("temp.csv","r");                           //opeing temp file in reading mode to fetch data
    fscanf(fptr,"%d",&user_count);                               //fetching count to cursor move forword and skip this count
    struct Addressbook user1[user_count];
    for(int i=0; i<user_count; i++)                                        //running while loop at the EOF
    {
        fscanf(fptr,"\n%[^,],%[^,],%[^,],%[^\n]",user1[i].name,user1[i].mobile,user1[i].email,user1[i].address);       //fetching data in file and storing into variable
    }
    fclose(fptr);
    for(int i=0; i<user_count-1; i++)                //sort the array
    {
        for(int j=0; j<user_count-i-1; j++)
        {
            char ch1,ch2;
            sscanf(user1[j].name,"%c",&ch1);
            sscanf(user1[j+1].name,"%c",&ch2);
            if(f(ch1,ch2))
            {
                strcpy(temp,user1[j].name);
                strcpy(user1[j].name,user1[j+1].name);
                strcpy(user1[j+1].name,temp);
                strcpy(temp,user1[j].mobile);
                strcpy(user1[j].mobile,user1[j+1].mobile);
                strcpy(user1[j+1].mobile,temp);
                strcpy(temp,user1[j].email);
                strcpy(user1[j].email,user1[j+1].email);
                strcpy(user1[j+1].email,temp);
                strcpy(temp,user1[j].address);
                strcpy(user1[j].address,user1[j+1].address);
                strcpy(user1[j+1].address,temp);
            }
        }
    }
    fptr=fopen("temp.csv","w");                           //opeing temp file in reading mode to fetch data
    fprintf(fptr,"%d",user_count);
    for(int i=0; i<user_count; i++)                                        //running while loop at the EOF
    {
        fprintf(fptr,"\n%s,%s,%s,%s",user1[i].name,user1[i].mobile,user1[i].email,user1[i].address);       //fetching data in file and storing into variable
    }
    fclose(fptr);                                         //close file
}

void Adding_ditail(struct Addressbook user, int *user_count, int count)            //called function to add details
{
    char *ch1=calloc(20,sizeof(char));
    char *ch2=calloc(20,sizeof(char));
    char *ch3=calloc(20,sizeof(char));
    char *ch4=calloc(20,sizeof(char));
    for(int i=*user_count; i<(*user_count)+count; i++)           //runing loop and adding details
    {
        printf(URED"----------- detail's %d ------------\n"reset,i+1);
        label9 :
        printf(RED"Enter Name "URED"(name start with capital latter)"RED" : "reset);
        scanf(" %[^\n]",user.name);
        char ch;
        sscanf(user.name,"%c",&ch);
        if(!(ch>=65 && ch<=90))
        {
            printf(BHRED"Error : First letter is not "URED"capital"reset BHRED" (A-Z)\n"reset);
            goto label9;
        }
        label :
        printf(RED"Enter Mobile number : "reset);
        scanf(" %[^\n]",user.mobile);
        int Pre=checking_mobile_emeil(user.mobile,1);            //function call to check mobile number
        if(Pre)
        {
            printf(BRED"Enter Valid mobile please\n"reset);
            goto label;
        }
        label7 :
        printf(RED"Enter Email address : "reset);
        scanf(" %[^\n]",user.email);
        Pre=checking_mobile_emeil(user.email,0);                     //function call to check email
        if(Pre)
        {
            printf(BRED"Enter Valid email please (missing @ & .com)\n"reset);
            goto label7;
        }
        printf(RED"Enter Address : "reset);
        scanf(" %[^\n]",user.address);
        strcpy(ch1,user.name);                                          //storing details in other variables
        strcpy(ch2,user.mobile);
        strcpy(ch3,user.email);
        strcpy(ch4,user.address);
        int res=backcheking(user,user_count,ch2,ch3);                   //function call to check details
        strcpy(user.name,ch1);                                          //copy data in struct member variables
        strcpy(user.mobile,ch2);
        strcpy(user.email,ch3);
        strcpy(user.address,ch4);
        if(res==0)
        {
            FILE *fptr=fopen("temp.csv","a");                            //opening temp file in append mode for appending data
            fprintf(fptr,"\n%s,%s,%s,%s",user.name,user.mobile,user.email,user.address);     //storing input data in temp file
            fclose(fptr);                                               //closing file
        }
        else{
            printf(BHRED"You entered data is already available in the data base\nPlease add new details only\n\n"reset);
            i--;
        }
    }
    (*user_count)+=count;
    FILE *fptr=fopen("temp.csv","r+");                                //opening file in reading & writing mode to override only count
    fprintf(fptr,"%d",*user_count);
    fclose(fptr);
    loading(0);                                                 //function call to load data into main file
    printf(MAG"Information sucessfully added\n"reset);
}

void Print_ditail(struct Addressbook user, int *user_count)             //called function to print data 
{
    system("clear");                                         //clearing screen and printing prompt on screen
    int ser=4;
    printf(BRED"\n--------Menu---------\n"reset);            //printing prompt to user
    printf(RED"Which formate you want to see information\n1.Ascending order (A-Z)\n2.Descending order (Z-A)\n3.Regular Formate\n4.Exit\n"reset);
    printf(WHT"Enter any one : "reset);
    scanf("%d",&ser);
    if(ser==1)                                               //based on value function call
        sort(ascending);
    else if(ser==2)
        sort(decending);
    else if(ser==4)
        return;
    else if(ser>4)
    {
        printf(BHRED"Invalid entry !\n"reset);
        return;
    }                                                         //printing data
    printf(BWHT"\n---------------------------------------------------------------------------------\n");
    printf(BWHT"\n--------------------------------"BRED"Address Book"BWHT"-------------------------------------\n");
    printf(BWHT"\n---------------------------------------------------------------------------------\n");
    printf(URED"Name\t\tMobile\t\tEmail\t\t\t\tAddress\n"reset);
    printf(BWHT"\n---------------------------------------------------------------------------------\n");
    FILE *fptr=fopen("temp.csv","r");                           //opeing temp file in reading mode to fetch data
    fscanf(fptr,"%d",user_count);                               //fetching count to cursor move forword and skip this count
    while(!(feof(fptr)))                                        //running while loop at the EOF
    {
        fscanf(fptr,"\n%[^,],%[^,],%[^,],%[^\n]",user.name,user.mobile,user.email,user.address);       //fetching data in file and storing into variable
        printf(WHT"%-15.15s %-15.15s %-31.31s %-20.20s\n",user.name,user.mobile,user.email,user.address);  //printing data into sreen stored into variable
    }
    printf(BWHT"\n---------------------------------------------------------------------------------\n");
    fclose(fptr);                                                //closing the file
}

void Search_ditail(struct Addressbook user, int *user_count)     //called function to search deatils
{
    system("clear");                                             //clear screen
    int ser,flag=0;
    char ch[30]={0};
    printf(BRED"\n--------Menu---------\n"reset);                         //printing prompt to user
    printf(RED"1.Mobile\n2.Email\n3.All address details of Perticular location\n");
    printf(WHT"Enter any one : "reset);
    scanf("%d",&ser);
    printf(BMAG"Enter %s to check detail's: "reset,ser==1?"Mobile number":ser==2?"Email":"Address");
    scanf(" %[^\n]",ch);                                         //taking input from user
    FILE *fptr=fopen("temp.csv","r");                            //opening temp file in reading mode
    fscanf(fptr,"%d",user_count);                                //fetching count to cursor move forword and skip this count
    printf(BWHT"\n---------------------------------------------------------------------------------\n");
    printf(BWHT"\n--------------------------------"BRED"Address Book"BWHT"-------------------------------------\n");
    printf(BWHT"\n---------------------------------------------------------------------------------\n");
    printf(URED"Name\t\tMobile\t\tEmail\t\t\t\tAddress\n"reset);
    printf(BWHT"\n---------------------------------------------------------------------------------\n");
    while(!(feof(fptr)))                                         //running while loop at the EOF
    {
        fscanf(fptr,"\n%[^,],%[^,],%[^,],%[^\n]",user.name,user.mobile,user.email,user.address);        //fetching data in the file and storing into variable
        if(strcmp(ch,user.mobile)==0 || strcmp(ch,user.email)==0 || strcmp(ch,user.address)==0)     //compare data and if equal then print data and stop loop
        {   flag=1;                                                                    
            printf(WHT"%-15.15s %-15.15s %-31.31s %-20.20s\n",user.name,user.mobile,user.email,user.address);
        }
    }
    printf(BWHT"\n---------------------------------------------------------------------------------\n"reset);
    if(flag==0)
        printf(BHRED"No details found,You entered invalid %s to check detail's\n"reset,ser==1?"Mobile number":ser==2?"Email":"Address");          //if details not fount print prompt
    fclose(fptr);                                                //close file
}

void Edit_ditail(struct Addressbook user, int *user_count)       //called function to edit details
{
    system("clear");                                //clearing screen
    int ser,flag=0,i,valid=1;
    char ch[30]={0};
    char c;
    printf(BRED"\n--------Menu---------\n"reset);            //printing prompt to user
    printf(RED"1.Mobile\n2.Email\n");
    printf(WHT"Enter any one : "reset);
    scanf("%d",&ser);
    printf(BMAG"Enter %s to change perticular detail's: "reset,ser==1?"Mobile number":"Email"reset);
    scanf(" %[^\n]",ch);                           //taking input from user
    FILE *fptr1=fopen("temp.csv","r");             //opening temp file in reading mode
    FILE *fptr2=fopen("Addressbook.csv","w");      //opening main file in writing mode to overwrite data
    fscanf(fptr1,"%d",user_count);                 //fetching count and storing into variable
    fprintf(fptr2,"%d",*user_count);
    while(!(feof(fptr1)))                          //running loop at the EOF
    {
        system("clear");
        fscanf(fptr1,"\n%[^,],%[^,],%[^,],%[^\n]",user.name,user.mobile,user.email,user.address);   //faeching data and store into variable's
        if(strcmp(ch,user.mobile)==0 || strcmp(ch,user.email)==0)                  //compare data
        {                                          //print prompt to the user
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            printf(BWHT"\n--------------------------------"BRED"Address Book"BWHT"-------------------------------------\n");
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            printf(URED"Name\t\tMobile\t\tEmail\t\t\t\tAddress\n"reset);
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            printf(WHT"%-15.15s %-15.15s %-31.31s %-20.20s\n",user.name,user.mobile,user.email,user.address);
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            label1 :
            printf(BRED"\n--------Menu---------\n"reset);                             //printing prompt to user and taking input
            printf(RED"1.Name\n2.Mobile_number\n3.Email\n4.Address\nWhat you want to edit : "reset);
            scanf("%d",&flag);
            printf(BHRED"Do you want to continue to edit "URED"%s"reset BHRED" detail's (Y/N) : "reset,user.name);
            scanf(" %c",&c);
            if(c!='y' &&  c!='Y')
                goto label2;
            if(flag==1)                                       //based on input editing perticular details
            {
                printf(RED"Add new name : "reset);
                scanf(" %[^\n]",user.name);
            }
            else if(flag==2)
            {
                label5 :
                printf(RED"Add new mobile number : "reset);
                scanf(" %[^\n]",user.mobile);
                int Pre=checking_mobile_emeil(user.mobile,1);      //function call to check mobile number
                if(Pre)
                {
                    printf(URED"Enter Valid mobile please\n"reset);
                    goto label5;
                }
            }
            else if(flag==3)
            {
                label6 :
                printf(RED"Add new email address : "reset);
                scanf(" %[^\n]",user.email);
                int Pre=checking_mobile_emeil(user.email,0);        //function call to check email
                if(Pre)
                {
                    printf(URED"Enter Valid email please (missing @ & .com)\n"reset);
                    goto label6;
                }
            }
            else if(flag==4)
            {
                printf(RED"Add new address : "reset);
                scanf(" %[^\n]",user.address);
            }
            else                                        //else printing invalid choice
            {
                printf(BRED"Invalid choice\n"reset);
                goto label1;
            }
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            printf(BWHT"\n--------------------------------"BRED"Address Book"BWHT"-------------------------------------\n");
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            printf(URED"Name\t\tMobile\t\tEmail\t\t\t\tAddress\n"reset);
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            printf(WHT"%-15.15s %-15.15s %-31.31s %-20.20s\n",user.name,user.mobile,user.email,user.address);
            printf(BWHT"\n---------------------------------------------------------------------------------\n"reset);                              
            label2 :
            valid=0;
        }
        fprintf(fptr2,"\n%s,%s,%s,%s",user.name,user.mobile,user.email,user.address);    //storing data into main file
    }
    if(valid)                     //based on condition printing prompt
    {
        printf(BHRED"You entered invalid %s to check detail's\n"reset,ser==1?"Mobile number":"Email");
        return;
    }
    fclose(fptr1);                //close both files
    fclose(fptr2);
    loading(1);                   //loading function call to store data from main file to temp file
    c=='y' || c=='Y' ? printf(MAG"Sucessfully Edited\n"reset):0;
}

void Delete_ditail(struct Addressbook user, int *user_count)       //called function to delete details
{
    system("clear");              //clearing screen
    int ser,valid=1;
    char ch[30]={0};
    char c;
    printf(BRED"\n--------Menu---------\n"reset);            //prompt to user
    printf(RED"1.Mobile\n2.Email\n");
    printf(WHT"Enter any one : "reset);
    scanf("%d",&ser);                 //taking input from user
    if((ser!=1) && (ser!=2))          //based upon input print promt otherwise go forword
    {
        printf(BHRED"Invalid Entry\n"reset);
        return;
    }
    printf(BMAG"Enter %s to change perticular detail's: "reset,ser==1?"Mobile number":"Email"reset);
    scanf(" %[^\n]",ch);                 //taking input from user
    FILE *fptr1 =fopen("temp.csv","r");      //opning temp file in reading mode
    FILE *fptr2 =fopen("Addressbook.csv","w");   //opening main file in writing mode
    fscanf(fptr1,"%d",user_count);               //fetching count and storing into variable
    fprintf(fptr2,"%d",*user_count);
    while(!(feof(fptr1)))                        //running at the EOF
    {
        fscanf(fptr1,"\n%[^,],%[^,],%[^,],%[^\n]",user.name,user.mobile,user.email,user.address);   //faeching data and store into variable's
        if((strcmp(ch,user.mobile)==0) || (strcmp(ch,user.email)==0))             //compare data
        {
            system("clear");                    //system clear and prompt to the user
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            printf(BWHT"\n--------------------------------"BRED"Address Book"BWHT"-------------------------------------\n");
            printf(BWHT"\n---------------------------------------------------------------------------------\n");
            printf(URED"Name\t\tMobile\t\tEmail\t\t\t\tAddress\n"reset);
            printf(BWHT"\n---------------------------------------------------------------------------------\n"reset);
            printf(WHT"%-15.15s %-15.15s %-31.31s %-20.20s\n",user.name,user.mobile,user.email,user.address);
            printf(BWHT"\n---------------------------------------------------------------------------------\n\n"reset);
            printf(BHRED"Do you want to delete this "URED"%s"reset BHRED" contact (Y/N) : "reset,user.name);
            scanf(" %c",&c);
            if(c=='y' || c=='Y')
            {
                valid=0;
                continue;                                                 //if data match then skip this and goto next iteration
            }
            valid=0;
        }
        fprintf(fptr2,"\n%s,%s,%s,%s",user.name,user.mobile,user.email,user.address);     //storing data into file
    }
    if(valid)                         //based upon condition print prompt
    {
        printf(BHRED"Invalid %s you give to change perticular detail's: \n"reset,ser==1?"Mobile number":"Email"reset);
        return;
    }
    fclose(fptr1);                    //closing both file
    fclose(fptr2);
    if(c!='y' && c!='Y' )
        goto label;
    fptr2=fopen("Addressbook.csv","r+");        //opeing main file in reading and writing mode to update count value
    fprintf(fptr2,"%d",(*user_count)-=1);
    fclose(fptr2);                    //closing file
    printf(MAG"Information Sucessfully deleted !\n"reset);
    label:
    loading(1);                       //loading function call to store data from main file to temp file
}

/*---------------------------------------------------------------------------------------------------------------------------------------------*/