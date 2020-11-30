/*******************************************************************************

  OOP PROJECT 
  INHERITANCE AND FILE HANDLING IN C++
  TITLE :- STUDENT DATABASE

******************************************************************************/


#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <string.h>

using namespace std;

char file[20];

class security
{
public :
    char ID[20];
    int pass;

    security()
    {
        pass = 0;
    }
    int secur();
    void access();
    void changePass();
};


class student : public security
{
private :
    char name[40];
    int roll;
    int gr_no;
    int date;
    int month;
    int year;
    char att;

public :
    student()
    {
        roll = 0;
        gr_no = 0;
        strcpy(name,"Student");
        date = 0;
        month = 0;
        year = 0;
        att = 'X';
    }
    void getdata();
    void showdata();
    int storedata();
    int veiwStoredata();
    int validDOB();
    void menu();
    int searchData(int);
    void deleteData(int);
    void editData(int);
    void update();
    void attendence();
    void markAttendence();
    void presentStud();
};


void security::access()                                                  // set a new password
{
    ofstream fout;                                                       // declaring object object of ofstream class to write data inside the file
    cout<< "\n\n\t\t CREATING NEW ID\n";
    i:cout<< "\n\t Enter New ID : ";
    cin>> ID;
    if(strlen(ID)< 6)
    {
        cout<< "\n\n\t -> Create strong ID\n";
        goto i;
    }
    p:cout<< "\n\t Enter New Password (6 digits) : ";
    cin>> pass;
    if(pass < 111111)
    {
        cout<< "\n\n\t -> Create strong Password\n";
        goto p;
    }
    fout.open("Security",ios::app);                                    // open file named security in append mode
    fout.write((char*)this,sizeof(*this));                             // write in the file which is stored in the object of security class
    fout.close();                                                      //close the file
    cout<< "\n\n\t\t----> New ID Created <----\n";
}


int security::secur()
{
    char ID1[20];
    int pass1;
    ifstream fin;                                                       // declaring pointer of ifstream class
    ofstream fout;
    fout.open("Security",ios::app);                                     // open the file, if the file is not present it will be created
    fout.close();
    s:fin.open("Security",ios::ate);                                    // open the file in update mode (pointer is at the end)
    if(fin.tellg() == 0)                                                // check whether the file is empty or not
    {
        fin.close();
        access();
    }
    else
        fin.close();

    fin.open("Security",ios::in);                                       // open file in read mode
    fin.read((char*)this,sizeof(*this));                                // read data from the file and store it in object of security class
    cout<< "\n\t Enter ID : \t";
    cin>> ID1;
    cout<< "\n\t Enter Password(6 digit) : ";
    cin>> pass1;

    if(strcmp(ID,ID1) == 0 && pass1 == pass)                            // check whether the ID & Password is correct or not
    {
        cout<< "\n\n\t\t -------:> VERIFICATION SUCCESSFULL <:-------\n";
        return (1);
    }
    return (0);
}


void security::changePass()
{
    char tempid[20];
    int tpass;

    ifstream fin;
    ofstream fout;
    fin.open("Security",ios::in);                                       // open file in read mode
    fin.read((char*)this,sizeof(*this));                                // read data from the file and store it in the object
    cout<< "\n\n -:> Enter Previous ID & Password\n";
    cout<< "\n\t Enter ID : \t";
    cin>> tempid;
    cout<< "\n\t Enter Password : ";
    cin>> tpass;
    fin.close();

    if(strcmp(ID,tempid) == 0 && pass == tpass)                         // compare whether the ID & Password matches
    {
        cout<< "\n\n\t ---:> VERIFIED <:---\n";
        cout<< "\n\t Enter New ID : ";                                  // set new ID & password
        cin>> ID;
        i:if(strlen(ID)< 6)
        {
            cout<< "\n\n\t -> Create strong ID\n";
            goto i;
        }
        p:cout<< "\n\t Enter New Password (6 digits) : ";
        cin>> pass;
        if(pass < 111111)
        {
            cout<< "\n\n\t -> Create strong Password\n";
            goto p;
        }
        fout.open("Security",ios::out);                                 // open file in out mode(previous written data inside the file is lost)
        fout.write((char*)this,sizeof(*this));                          // new ID & Password is written inside the file
        fout.close();
        cout<< "\n\n\t\t ----:> ID-PASSWORD CHANGED SUCCESSFULLY <:----\n";
    }
    else
        cout<< "\n\n\t\t --:> Process FAILED\n";
}


void student::getdata()                                             // accept student data
{
    int i = 0;
    cout<< "\n\tEnter Name : ";
    cin.ignore();
    cin.getline(name,39);

    r:cout<< "\tEnter Roll no. : ";
    cin>> roll;
    if(233001 > roll || 233067 < roll ){                            // validation for roll no.
        cout<< "\n\t -> Invalid Roll no.\n\n";
        goto r;
    }

    g:cout<< "\tEnter GR no. : ";                                   // validation for GR no.
    cin>> gr_no;
    if(21910001 > gr_no || 21911500 < gr_no){
        cout<< "\n\t -> Invalid GR no.\n\n";
        goto g;
    }

    d:cout<< "\n\tEnter DOB :\n";
    cout<< "\t\t Date : ";
    cin>> date;
    cout<< "\t\t Month : ";
    cin>> month;
    cout<< "\t\t Year : ";
    cin>> year;
    i = validDOB();
    if(i != 1){
        goto d;
    }
}


int student::validDOB()                                               // validation for DOB
{
    int i = 0;
    if(year>=1999 && year<=2003)
{
//check month
if(month>=1 && month<=12)
{
//check days
if((date>=1 && date<=31) && (month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)){
    //cout<<"Date is valid.\n";
    return (1);
}

else if((date>=1 && date<=30) && (month==4 || month==6 || month==9 || month==11)){
    //cout<< "Date is valid.\n";
    return (1);
}

else if((date>=1 && date<=28) && (month==2)){
    //cout<< "Date is valid.\n";
    return(1);
}

else if(date==29 && month==2 && (year%400==0 ||(year%4==0 && year%100!=0))){
    //cout<< "Date is valid.\n";
    return (1);
}
else{
    cout<< "\n\t -> Date is invalid\n";
    return (0);
}
}
else
{
    cout<< "\n\t -> Month is not valid\n";
    return (0);
}
}
else
{
    cout<< "\n\t -> Year is not valid\n";
    return (0);
}
}


void student::showdata()                                   // Display record present inside the object
{
    cout<< "\t\t " << name << "\t " << roll << "\t\t " << gr_no << "\t " << date << "/" << month << "/" << year << "\n";
}


int student::storedata()                                   // store data present in object to the file
{

    if(roll == 0 && gr_no == 0)                            // check whether the data is initialized or not
    {
        cout<< "\n\n\t  -> Data is NOT Initialized !!!!\n";
        return (0);
    }
    if(strlen(file) == 0)
    {
        cout<< "\nEnter Name of the file : ";
        cin>> file;
    }

    ofstream fout;
    fout.open(file,ios::app);
    fout.write((char*)this,sizeof(*this));
    fout.close();

    return (1);
}


int student::veiwStoredata()
{
    int ch, i;
    ifstream fin;
    /*cout<< "\n\nDo you want to display same file ?\n\t 1. Yes\t 2. No\n\nChoice : ";
    cin>> ch;
    if(ch == 2)
    {
        cout<< "\nEnter Name of the Another file : ";
        cin>> file;
    }*/
    i = 0;
    fin.open(file,ios::in);
    if(!fin)                                                                // check weather file is present or not
    {
        cout<< "\n\n\t  -> File NOT Found !!!!\n";
        return (0);
    }
    fin.read((char*)this,sizeof(*this));                                    // read first data from the file
    while(!fin.eof())                                                       // loop is executed until the pointer reaches to its end(end of file)
    {
        i++;
        cout<< "\t" << i << ")";
        showdata();
        fin.read((char*)this,sizeof(*this));                                 // read the next data
    }
    fin.close();
    return (1);
}


int student::searchData(int key)
{
    int counter = 0;
    ifstream fin;
    fin.open(file,ios::in|ios::binary);
    if(!fin)                                                                 // check weather the file is present or not
    {
        cout<< "\n\n\t  -> File NOT Found !!!!\n";
        return (0);
    }
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(key == roll || key == gr_no)                                  // if record found then display it
            {
                cout<< "\n\n -> Record Found\n";
                showdata();
                counter++;
            }
            fin.read((char*)this,sizeof(*this));
        }
        if(counter == 0)                                                      // for no record found
            cout<< "\n\n\t -> Record NOT Found !!!\n";
        fin.close();

    return (1);
    }
}


void student::update()                                                       // update the required data
{
    int ch, i = 0;

    do
    {
        cout<< "\n\nWhat do you want to edit ?\n\n\t\t 1. Name\n\t\t 2. Roll no.\n\t\t 3. GR no.\n\t\t 4. DOB\n\t\t 5. Exit Edit\n\nChoice : ";
        cin>> ch;

        switch(ch)
        {
        case 1:
            cout<< "\n\n\t Enter New Name : ";
            cin.ignore();
            cin.getline(name,39);
            break;

        case 2:
            r:cout<< "\n\n\t Enter New Roll no. : ";
            cin>> roll;
            if(233001 > roll || 233067 < roll ){
                cout<< "\n\n\t -> Invalid Roll no.\n\n";
                goto r;
            }
            break;

        case 3:
            g:cout<< "\n\n\t Enter New GR no. : ";
            cin>> gr_no;
            if(21910001 > gr_no || 21911500 < gr_no){
                cout<< "\n\n\t -> Invalid GR no.\n\n";
                goto g;
            }
            break;

        case 4:
            d:cout<< "\n\n\t Enter New DOB :\n";
            cout<< "\n\t\t Date : ";
            cin>> date;
            cout<< "\t\t Month : ";
            cin>> month;
            cout<< "\t\t Year : ";
            cin>> year;
            i = validDOB();
            if(i != 1){
                goto d;
            }
            break;

        case 5:
            cout<< "\n\n\t\t ----:> MODIFICATION DONE <:----\n";
            break;

        default :
            cout<< "\n\t\t -> Invalid Choice\n";
        }
    }while(ch != 5);
}


void student::editData(int key)                                      // edit the record
{
    fstream fil;                                                   // declare object of fstream class
    int i;

    fil.open(file,ios::in|ios::out|ios::ate);
    fil.seekg(0);                                                  // move pointer '0' bytes ahead from start of the file
    fil.read((char*)this,sizeof(*this));
    while(!fil.eof())
    {
        if(key == gr_no)
        {
            update();
            i = fil.tellp();                                       // tell the position of the pointer
            fil.seekp(i - sizeof(*this));                          // move the pointer one record back
            fil.write((char*)this,sizeof(*this));                  // write the updated record to the file present in the object
        }
        fil.read((char*)this,sizeof(*this));
    }
    fil.close();
}


void student::deleteData(int temp)
{
    ifstream fin;
    ofstream fout;
    fin.open(file,ios::in|ios::binary);                           // open record file in read mode
    if(!fin)
        cout<< "\n\n\t -> File NOT Found !!!\n";
    else
    {
        fout.open("tempFile",ios::out);                          // create a temporary file in out mode
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(gr_no == temp){
                cout<< "\n -> Record to be Deleted\n\n";
                showdata();
                cout<< "\n\n\t -> Deletion SUCCESSFULL \n";
            }
            else{
                fout.write((char*)this,sizeof(*this));          // coping data from record file to temporary file except the record which is to be deleted
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        remove(file);                                           // delete the record file
        rename("tempFile",file);                                // rename the temp file as record file
    }

}


void student::markAttendence()
{
    a:cout<< "\t " << name << "\t " << roll << "\t\t " << gr_no << "\t\t ";
    cin>> att;
    if(att == 'P'|| att == 'p'|| att == 'a'|| att == 'A'){             // validation of attendence marked
        (1);
    }
    else{
        cout<< "\n\t -:> Invalid Attendence\n\n";
        goto a;
    }
}


void student::attendence()
{
    fstream fil;
    int i, ch;

    fil.open(file,ios::in|ios::out|ios::ate);
    fil.seekg(0);                                                  //move pointer '0' bytes ahead from start of the file(means at the beginning)
    fil.read((char*)this,sizeof(*this));

    cout<< "\n------------------------------------------------------------------------------------------";
    cout<< "\n\t NAME \t\t ROLL NO. \t GR NO. \t ATTENDENCE(P/A) \n";
    cout<< "------------------------------------------------------------------------------------------\n\n";

    while(!fil.eof())
    {
        markAttendence();
        i = fil.tellp();                                       // tell the position of the pointer
        fil.seekp(i - sizeof(*this));                          // move the pointer one record back
        fil.write((char*)this,sizeof(*this));
        fil.read((char*)this,sizeof(*this));
    }
    cout<< "\n\t\t -:> ATTENDENCE MARKED SUCCESSFULLY\n";
    cout<< "\n------------------------------------------------------------------------------------------\n\n";
    fil.close();
}


void student::presentStud()
{
    int i;
    ifstream fin;
    i = 0;
    fin.open(file,ios::in|ios::binary);
    if(!fin)
    {
        cout<< "\n\n\t  -> File NOT Found !!!!\n";
        return;
    }

    cout<< "\n------------------------------------------------------------------------------------------";
    cout<< "\n\t SR. NO. \t NAME \t\t ROLL NO. \t GR NO. \t ATTENDENCE(P/A) \n";
    cout<< "------------------------------------------------------------------------------------------\n\n";
    if(att == 'X')
    {
        cout<< "\n\t  -> Attendence is NOT Marked yet !!!!\n\n";
    }

    fin.read((char*)this,sizeof(*this));
    while(!fin.eof())
    {
        if(att == 'P'|| att == 'p'){                           // check whether the student is present or not
            i++;
            cout<< "\t" << i << ")" << "\t\t " << name << "\t " << roll << "\t\t " << gr_no << "\t\t " << att << "\n";
        }
        fin.read((char*)this,sizeof(*this));
    }
    fin.close();
    cout<< "\n -:> Total No. of Students Present : " << i << "\n";
    cout<< "\n------------------------------------------------------------------------------------------\n\n";
}


void student::menu()
{
    int num, ch, i, k, key;
    int temp;
    security c1;

    cout<< "\n-----------------------------------------------------------------------------------------\n\n";
    cout<< "\t\t\t\t -:> WELCOME <:-\n";

    do
    {
        cout<< "\nTask you want to perform :-\n"
            << "\n\t\t 1. Accept Records\n\t\t 2. Display Records"
            << "\n\t\t 3. Search\n\t\t 4. Add More\n\t\t 5. Display Recently Added Data"
            << "\n\t\t 6. Edit Record\n\t\t 7. Delete Record\n\t\t 8. Attendence"
            << "\n\t\t 9. Delete File\n\t\t 10. Change ID-Password\n\t\t 11. LOG-OUT";
        cout<< "\n\nChoice : ";
        cin>> ch;

        switch(ch)
        {
        case 1:
            cout<< "\nEnter the File Name : ";
            cin>> file;
            cout<< "\nNo. of students data want to enter : ";
            cin>> num;                                                  // no. of records you want to add

            for(i=1; i<=num;i++)
            {
                cout<< "\n-> ENTER RECORD " << i<< "\n";
                getdata();
                k = storedata();
            }
            cout<< "\n\n\t  -> Data Stored SUCCESSFULLY....\n";
            cout<< "\n------------------------------------------------------------------------------------------\n\n";
            break;

        case 2:
            cout<< "\n------------------------------------------------------------------------------------------";
            cout<< "\n\tSR. NO. \t NAME \t\t ROLL NO. \t GR NO. \t DOB \n";
            cout<< "------------------------------------------------------------------------------------------\n\n";
            veiwStoredata();
            cout<< "\n------------------------------------------------------------------------------------------\n\n";
            break;

        case 3:
            cout<< "\n\nOn which you want to search ?\n\n\t 1. Roll no.\n\t 2. GR no.\n\t 3. Exit Search\n\nChoice : ";
            cin>> k;
            switch(k)
            {
            case 1:
                cout<< "\n\nEnter Roll no. to be searched : ";
                cin>> key;
                searchData(key);
                break;

            case 2:
                cout<< "\n\nEnter GR no. to be searched : ";
                cin>> key;
                searchData(key);
                break;

            case 3:
                cout<< "\n\n\t\t -> EXIT SEARCH\n";
                break;
            }
            cout<< "\n------------------------------------------------------------------------------------------\n\n";
            break;

        case 4:
            getdata();
            k = storedata();
            if(k == 1)
                cout<< "\n\n\t -> Record Added SUCCESSFULLY...\n";
            cout<< "\n------------------------------------------------------------------------------------------\n\n";
            break;

        case 5:
            cout<< "\n\n -:> Recently Added Record\n\n";
            showdata();
            cout<< "\n------------------------------------------------------------------------------------------\n\n";
            break;

        case 6:
            cout<< "\n\n\t\t ----:> EDIT <:----\n";
            cout<< "\n\nEnter the GR no. of record you want to Edit : ";
            cin>> temp;
            editData(temp);
            cout<< "\n------------------------------------------------------------------------------------------\n\n";
            break;

        case 7:
            cout<< "\n\n\t\t\t ----:> DELETE <:----\n";
            cout<< "\n\nEnter GR no. of record : ";
            cin>> temp;
            deleteData(temp);
            cout<< "\n------------------------------------------------------------------------------------------\n\n";
            break;

        case 8:
            cout<< "\n\n\t\t ----:> ATTENDENCE <:----\n";
            do
            {
                cout<< "\n\n -:> Options\n\n\t 1. Mark Attendence\n\t 2. Display List of Present Students\n\t 3. Exit Attendence\n\n Choice : ";
                cin>> k;

                switch(k)
                {
                case 1:
                    attendence();
                    break;

                case 2:
                    presentStud();
                    break;

                case 3:
                    cout<< "\n\n\t\t ---:> EXIT ATTENDENCE <:---\n\n";
                    break;

                default :
                    cout<< "\n\n\t -:> Invalid Choice !!!\n";
                    break;
                }
            }while(k != 3);

            break;

        case 9:
            k = 0;
            cout<< "\n\n\t -:> Delete File\n";
            cout<< "\nAre you sure you want to Delete this File ?\n\n\t 1. Yes\t\t 2. No\n\nChoice : ";
            cin>> k;
            if(k == 1)
            {
                remove(file);
                cout<< "\n\n\t -:> File is DELETED\n";
            }
            cout<< "\n------------------------------------------------------------------------------------------\n\n";
            break;

        case 10:
            c1.changePass();
            cout<< "\n------------------------------------------------------------------------------------------\n\n";
            break;

        case 11:
            cout<< "\n\n\t\t ----:> LOG-OUT <:----\n";
            cout<< "\n------------------------------------------------------------------------------------------\n\n";
            break;

        default :
            cout<< "\n\n\t  -> Invalid choice !!!\n";
            break;
        }
        getch();                                                       // to pause the program
        system("cls");                                                 // clear the screen

    }while(ch != 11);

}


int main()
{
    int choice, i;
    student s;
    security c1;

    cout<< "\n\t\t-------------------------:> DATABASE <:-----------------------------\n\n";

    do
    {
        cout<< "\n\t\t 1. Login\n\t\t 2. EXIT\n\n Choice : ";
        cin>> choice;

        switch(choice)
        {
        case 1:
            i = c1.secur();
            if(i == 1)
            {
                s.menu();
            }
            else
                cout<< "\n\n\t -> ADMIN ID or PASSWORD is Incorrect !!!\n";
            break;

        case 2:
            cout<< "\n\n\t\t ............ EXITING PORTAL ...........\n";
            exit(0);
            break;

        default :
            cout<< "\n\t -> Invalid Choice\n";
            break;
        }
    }while(choice != 2);

    return 0;
}
