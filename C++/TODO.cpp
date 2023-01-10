// Function: TODO list class using OOP
// 
//  TODO.cpp
// Luke Villanueva, CISP400
// 4/4/21


#include <iostream>
#include <ctime>
#include <fstream>
using std::string;
using std::cout;
using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::cin;



/*************
 * DATE CLASS
*************/


class Date
{

    private:
    time_t now; // seconds since Jan. 1 1970
    tm* dt; // formatted time
    int d, m, y;

    public:

    // default constructor
    Date()
    {
        // current amount of seconds
        now = time(0);

        // formatted time object
        dt = localtime(&now);

        m = (1+(dt->tm_mon));

        d = (dt->tm_mday);

        y = (1900+(dt->tm_year));
    }

    // copy constructor
    Date(const Date& obj)
    {
        d = obj.d;
        m = obj.m;
        y = obj.y;
        dt = obj.dt;
        now = obj.now;
    }

    // returns month as int
    int month()
    {
        return m;
    }

    // returns day as int
    int day()
    {
        return d;
    }

    // returns year as int
    int year()
    {
        return y;
    }

    // sets day
    void setDay(int n)
    {d = n;}

    // sets month
    void setMonth(int n)
    {m = n;}

    // sets year
    void setYear(int n)
    {y = n;}

    // tests Date object
    void ComponentTest()
    {
        Date test;
        cout << "\n----------------------------------------"
             << "\nCommencing Date class test..."
             << "\nTest #1: ";

        // tests Day of date
        if(d == (dt->tm_mday))
        {
            cout << "success";
        }
        else
        {
            cout << "failure"
                 << "\nExpected: " << (dt->tm_mday)
                 << "\nActual: " << d;
        }

        cout << "\nTest #2: ";

        // tests Month of date
        if(m == (1+(dt->tm_mon)))
        {
            cout << "success";
        }
        else
        {
            cout << "failure"
                 << "\nExpected: " << (1+(dt->tm_mon))
                 << "\nActual: " << m;
        }

        cout << "\nTest #3: ";

        // tests year of date
        if(y == (1900+(dt->tm_year)))
        {
            cout << "success";
        }
        else
        {
            cout << "failure"
                 << "\nExpected: " << (1900+(dt->tm_year))
                 << "\nActual: " << y;
        }

        // end of testing
        cout << "\nDate class testing completed"
             << "\nEnding class testing..."
             << "\n----------------------------------------";
    }

    friend istream& operator>>(istream&,Date);
    friend ifstream& operator>>(ifstream&, Date);

};

istream& operator>>(istream& os, Date obj)
{
    os >> obj.d >> obj.m >> obj.y;
    return os;
}

ostream& operator<<(ostream& os, Date dt)
{
    os << dt.day() << "/" << dt.month() << "/" << dt.year();
    return os;
}

ifstream& operator>>(ifstream& in, Date dt)
{
    in >> dt.d >> dt.m >> dt.y;
    return in;
}

ofstream& operator<<(ofstream& out, Date dt)
{
    out << dt.day() << "\n" << dt.month() << "\n"
        << dt.year() << "\n";
    return out;
}

/********************
 * END OF DATE CLASS
********************/





/*************
 * TO DO CLASS
*************/


class TODO
{

    private:
    string todo, id;
    // Specification A3 - System Date
    Date dt;
    // end of Specification A3 - System Date

    public:

    // Constructors

    // empty, filled with dummy data
    TODO()
    {
        todo = "N/A";
        id = "0";
    }

    // Specification A4 - Overload Constructor

    // with initial input of TODO, ID, and date object
    TODO(string itm, string n)
    {
        todo = itm;
        id = n;
    }

    // end of Specification A4 - Overload Constructor

    // Specification A1 - Overload Copy Constructor

    TODO(const TODO& obj)
    {
        todo = obj.todo;
        id = obj.id;
        dt = obj.dt;
    }

    // end of Specification A1 - Overload Copy Constructor

    // end of Constructors


    // returns TODO as string
    string getTODO()
    {return todo;}

    // returns id of TODO
    string getID()
    {return id;}

    // set TODO
    void setTODO(string s)
    {todo = s;}

    // set id of TODO
    void setID(string s)
    {id = s;}

    // set Date of TODO
    void setDate(int day, int month, int year)
    {
        dt.setDay(day);
        dt.setMonth(month);
        dt.setYear(year);
    }

    // get day from Date in TODO
    int getDay()
    {
        return dt.day();
    }

    // get month from Date in TODO
    int getMonth()
    {
        return dt.month();
    }

    // get year from Date in TODO
    int getYear()
    {
        return dt.year();
    }

    // Specification C3 - Test TODO's

    // tests TODO class
    void ComponentTest()
    {

        cout << "\n----------------------------------------"
             << "\nCommencing TODO class testing..."
             << "\nTest #1: ";

        // test 1 - testing default constructor

        TODO obj1;

        if(obj1.getID()=="0" && obj1.getTODO()=="N/A")
        {
            cout << "success";
        }
        else
        {
            cout << "failure"
                 << "\nExpected: ID = 0 and TODO = N/A"
                 << "\nResults: ID = " << obj1.getID() 
                 << " and TODO = " << obj1.getTODO();
        }

        // test 2 - testing overloaded constructor

        TODO obj2("Test","25");

        cout << "\nTest #2: ";

        if(obj2.getID()=="25" && obj2.getTODO()=="Test")
        {
            cout << "success";
        }
        else
        {
            cout << "failure"
                 << "\nExpected: ID = 25 and TODO = Test"
                 << "\nResults: ID = " <<obj2.getID()
                 << " and TODO = " << obj2.getTODO();
        }

        // test 3 - testing setTODO()

        cout << "\nTest #3: ";

        TODO obj3;

        obj3.setTODO("Setting TODO");

        if(obj3.getID()=="0" && obj3.getTODO()=="Setting TODO")
        {
            cout << "success";
        }
        else
        {
            cout << "failure"
                 << "\nExpected: ID = 0 and TODO = Setting TODO"
                 << "\nResults: ID = " << obj3.getID()
                 << " and TODO = " << obj3.getTODO();
        }

        // test 4 - testing setID()

        cout << "\nTest #4: ";

        TODO obj4;

        obj4.setID("0505");

        if(obj4.getID()=="0505" && obj4.getTODO()=="N/A")
        {
            cout << "success";
        }
        else
        {
            cout << "failure"
                 << "\nExpected: ID = 0505 and TODO = N/A"
                 << "\nResults: ID = " << obj4.getID()
                 << " and TODO = " << obj4.getTODO();
        }

        // test 5 - testing date in TODO

        cout << "\nTest #5: ";

        TODO obj5;

        obj5.setDate(1,1,2002);

        if(obj5.getDay()==1 && 
           obj5.getMonth()==1 && 
           obj5.getYear()==2002)
        {
            cout << "success";
        }
        else
        {
            cout << "failure"
                 << "\nExpected: Day = 1, Month = 1, Year = 2002"
                 << "\nResults: Day = " << obj5.getDay()
                 << ", Month = " << obj5.getMonth()
                 << ", Year = " << obj5.getYear();
        }

        // end of testing
        cout << "\nEnding class testing...";

    }

    // end of Specification C3 - Test TODO's

    // Overloads

    // Specification A2 - Overload Assignment Operator

    void operator=(const TODO& obj)
    {
        todo = obj.todo;
        id = obj.id;
        dt = obj.dt;
    }

    // end of Specification A2 - Overload Assignment Operator

    friend ostream& operator<<(ostream&,TODO);
    friend istream& operator>>(istream&,TODO);
    friend ofstream& operator<<(ofstream&,TODO);
    friend ifstream& operator>>(ifstream&,TODO);

    // end of Overloads



};

// Specification C1 - Overload <<

ostream& operator<<(ostream& os, TODO obj)
{
    os << "\nTODO: " << obj.todo
       << "\nID: " << obj.id
       << "\nDate: " << obj.dt; 
    return os;
}

// end of Specification C1 - Overload <<

// Specification C2 - Overload >>

istream& operator>>(istream& os, TODO obj)
{
    os >> obj.todo >> obj.id >> obj.dt;
    return os;
}

// end of Specification C2 - Overload >>

ofstream& operator<<(ofstream& out, TODO obj)
{
    out << obj.todo << "\n" << obj.id << "\n" 
        << obj.dt << "\n";
    return out;
}

ifstream& operator>>(ifstream& in, TODO obj)
{
    in >> obj.todo >> obj.id >> obj.dt;
    return in;
}

/********************
 * END OF TODO CLASS
********************/




/**********************
 * DYNAMIC ARRAY CLASS 
**********************/


template <typename type>
class DynamicArray
{
    private:
    int length; // actual amount of objects in array
    int arrSize; // amount of declared spots in array (+1 of length)
    type *listPtr; // ptr to the array

    // Private Functions

    // validity check for getElem
    bool validIndex(int n)
    {
        if(n<0 || n>=length)
            return false;
        return true;
    }

    // end of Private Functions


    public:


    /***************
     * CONSTRUCTORS 
    ***************/


    // default constructor
    DynamicArray()
    {
        length = 0;
        arrSize = 1;
        listPtr = new type[arrSize];
    }

    // copy constructor

    // destructor
    ~DynamicArray()
    {
        delete [] listPtr;
        listPtr = nullptr;
    }

    // int input
    DynamicArray(int num)
    {
        length = num;
        arrSize = num+1;
        listPtr = new type[arrSize];
    }

    // double input
    DynamicArray(double num)
    {
        num = (int)(num);
        length = num;
        arrSize = num+1;
        listPtr = new type[arrSize];
    }


    /**********************
     * END OF CONSTRUCTORS
    **********************/



    /************
     * FUNCTIONS
    ************/


    // User Accessible Functions

    // add to array's end
    void addEnd(type e)
    {
        // allocate temp array w/ 1 more than size
        type* temp = new type[arrSize+1];

        // increment size
        arrSize++;

        // last element of length is the new element
        temp[length] = e;

        // copy the rest of old arr to new arr
        for(int i = 0; i < length; i++)
        {
            temp[i] = listPtr[i];
        }

        // delete old array
        delete [] listPtr;

        // change ptr from old array to new array
        listPtr = temp;

        // change temp ptr point to null
        temp = nullptr;

        // increment length
        length++;
    }

    // subtract array's end
    void subtractEnd()
    {
        // check if size is already at minimum
        // subtract if there's space still
        if(arrSize > 1 && length > 0)
        {
            // allocate temp array w/ 1 less than size
            type* temp = new type[arrSize-1];

            // copy old arr to new arr except for last item
            for(int i  = 0; i < length-1; i++)
            {
                temp[i] = listPtr[i];
            }

            // delete old arr
            delete [] listPtr;

            // change ptr from old arr to new arr
            listPtr = temp;

            // decrement length
            length--;

            // decrement arrSize
            arrSize--;
        }
        else
        {
            cout << "\nERROR: Array is already at minimum size";
        }
    }

    // add to array's beginning
    void addStart(type e)
    {
        // allocate temp array w/ 1 more than size
        type* temp = new type[arrSize+1];

        // increment size
        arrSize++;

        // first element of length is the new element
        temp[0] = e;

        // copy the rest of old arr to new arr
        for(int i = 0; i < length; i++)
        {
            // temp at ind 1 and old at ind 0
            temp[i+1] = listPtr[i];
        }

        // delete old array
        delete [] listPtr;

        // change ptr from old array to new array
        listPtr = temp;

        // change temp ptr point to null
        temp = nullptr;

        // increment length
        length++;
    }

    // subtract elem at given index
    void subtractAt(int num)
    {
        if(validIndex(num))
        {
            // allocate temp array
            type* temp = new type[arrSize-1];

            // decrement arrSize
            arrSize--;

            // copy first half of array
            for(int i = 0; i<num; i++)
            {
                temp[i] = listPtr[i];
            }

            // copy second half of array
            for(int i = num+1; i<length; i++)
            {
                temp[i-1] = listPtr[i];
            }

            // delete old array
            delete [] listPtr;

            // change ptr from old arr to new arr
            listPtr = temp;

            // change temp ptr to null
            temp = nullptr;

            // decrement length
            length--;
        }
        else
        cout << "\nERROR: Invalid index";
    }

    // subtract array's beginning
    void subtractStart()
    {
        // check if size is already at minimum
        // subtract if there's space still
        if(arrSize > 1 && length > 0)
        {
            // allocate temp array w/ 1 less than size
            type* temp = new type[arrSize-1];

            // copy old arr to new arr except for first item
            for(int i  = 1; i < length; i++)
            {
                temp[i-1] = listPtr[i];
            }

            // delete old arr
            delete [] listPtr;

            // change ptr from old arr to new arr
            listPtr = temp;

            // decrement length
            length--;

            // decrement arrSize
            arrSize--;
        }
        else
        {
            cout << "\nERROR: Array is already at minimum size";
        }
    }

    // add elem at given index

    // get at given index
    type& getElem(int num)
    {
        if(validIndex(num))
            return *(listPtr+num);
        else 
        {
            cout << "\nERROR: Invalid index. Returning first element...";
            return listPtr[0];
        }
    }

    // get at given DOUBLE index 
    type& getElem(double num)
    {
        int n = (int)(num);
        if(validIndex(num))
            return *(listPtr+n);
        else
            cout << "\nERROR: Invalid index";
    }

    // replace elem at given index

    // replace elem at given DOUBLE index 

    // display array

    // reset arr, length is 0

    // resize arr, second param to fill empty slots

    // get arr length
    int getLength()
    {return length;}

    // get array memory location
    type* getAddress()
    {return listPtr;}

    // Overloaded Functions

    // Component Testing - assuming that array is of INTS
    void ComponentTest()
    {
        DynamicArray test;
        
        cout << "\n----------------------------------------"
             << "\nCommencing DynamicArray Testing...";

        cout << "\nTest #1: ";

        // testing default initialization
        if(test.getLength()==0)
        {
            cout << "success";
        }
        else
        {
            cout << "failure"
                 << "\nExpected: 0"
                 << "\nActual: " << test.getLength(); 
        }

        cout << "\nTest #2: ";

        DynamicArray<int> test1;

        test1.addStart(5);

        // testing addStart() & getElem()
        if(test1.getElem(0)==5)
        {
            cout << "success";
        }
        else
        {
            cout << "failure"
                 << "\n Expected: 5"
                 << "\nActual: " << test1.getElem(0);
        }

        // end of testing
        cout << "\nDynamicArray class testing completed"
             << "\nEnding class testing..."
             << "\n----------------------------------------";
    }


    /*******************
     * END OF FUNCTIONS 
    *******************/



    /*************************
     * ADAPTABILITY FUNCTIONS
    *************************/

    // Operator Overloads

    // access element with brackets
    type& operator[](const int num)
    {
        return *(listPtr+num);
    }

    // External Function Declarations
    template <typename T>
    friend ostream& operator<<(ostream&, const DynamicArray<T>&);

    /*************************
     * END OF ADAPTABILITY FUNCTIONS
    *************************/



};

ostream& operator<<(ostream& os, DynamicArray<TODO>&arr)
{
    if(arr.getLength()==0)
        os << "\nERROR: Array is empty";
    else
    {
        os << "\nArray contents: ";
        for(int i = 0; i<arr.getLength(); i++)
        {
            os << "\n" << arr[i].getTODO();
        }
    }
    return os;
}


/**********************
 * END OF DYNAMIC ARRAY CLASS 
**********************/





// Function Prototypes

void ProgramGreeting();
void UnitTest();
string menu();
int findHighestID(DynamicArray<TODO>&);
bool validCommand(string);

// end of Function Prototypes





/*******
 * MAIN
*******/


int main()
{

    string menuChoice;  // user's menu choice

    // Specification C4 - TODO array
    DynamicArray<TODO> arr;
    // end of Specification C4 - TODO array

    // Program Greeting
    ProgramGreeting();

    // runs all classes' tests
    UnitTest();

    //int loading = readFile(arr);

    do
    {

        // gets user's choice for program
        menuChoice = menu();

        // Specification B1 - + Symbol

        // if the command starts with +
        if(menuChoice[0]=='+')
        {
            string todo, id;

            // gets the desired TODO to add
            todo = menuChoice.substr(1);

            // calculated the next ID to designate
            id = std::to_string(findHighestID(arr)+1);

            // makes TODO item
            TODO obj(todo, id);

            // adds TODO item to end of list
            arr.addEnd(obj);

            cout << "\nItem added!";
        }

        // end of Specification B1 - + Symbol

        // Specification B2 - ? Symbol

        // if the command starts with ?
        if(menuChoice[0]=='?')
        {
            cout << "\n\nTODO List:";

            if(arr.getLength()==0)
            {
                cout << "\nNo items available...";
            }
            else
            {
                for(int i = 0; i<arr.getLength(); i++)
                {
                    cout << "\n----------------------------------------" 
                        << arr[i] << std::endl;
                }
            }

        }

        // end of Specification B2 - ? Symbol

        // Specification B3 - - Symbol

        if(menuChoice[0]=='-')
        {
            // if id found
            bool found = false;

            // id to find in arr in int form
            int givenID = std::stoi(menuChoice.substr(1));
            // index of item to remove
            int ind;


            // find item that has same index
            for(int i = 0; i<arr.getLength(); i++)
            {
                int id = std::stoi(arr[i].getID());
                if(id==givenID)
                    {
                        ind = i;
                        // remove item from array
                        arr.subtractAt(ind);
                        found = true;
                    }
            }
            if (found == true)
            cout << "\nItem removed!";
            else
            cout << "\nERROR: Invalid index";
        }

        // end of Specification B3 - - Symbol

        // exits loop if command has !

    }while(menuChoice[0]!='!');

    //writeFile(arr);

    return 0;

}


/**************
 * END OF MAIN
**************/





/*********************
 * PROGRAM FUNCTIONS
*********************/

// Program Greeting
void ProgramGreeting()
{
    cout << "-------------------------------------------" << std::endl
         << "Welcome to TODO!" << std::endl
         << "Description: You can add, subtract, and display "
         <<  "items in the list." << std::endl
         << "-------------------------------------------";
}

// menu function
string menu()
{
    string choice;

    // print out menu
    cout << "\n\n----------------------------------------"
         << "\nTo add: +item you want to add"
         << "\nTo remove: -ID of the item"
         << "\nTo display: ?" 
         << "\nTo end program: !"<< std::endl;

    // prompt for user input for command
    getline(cin, choice);

    // repeat while choice is invalid
    while(!validCommand(choice))
    {
        cout << "\n\n----------------------------------------"
             << "\n\nERROR: Invalid command/syntax"
             << "\n\nTo add: +item you want to add"
             << "\nTo remove: -ID of the item"
             << "\nTo display: ?" 
             << "\nTo end program: !" << std::endl;
        getline(cin, choice);
    }

    return choice;
}

// helper function for Specification B1
//? note: very simple input validation
bool validCommand(string s)
{
    if (s[0]=='-')
    {
        for(long unsigned int i = 1; i<s.length(); i++)
        {
            if(!isdigit(s[i]))
                return false;
            return true;
        }
    }
    if(s[0]=='+' || 
       s[0]=='?' || 
       s[0]=='!')
    {
        return true;
    }
    else
        return false;
}

// helper function for Specification B1
int findHighestID(DynamicArray<TODO>&arr)
{
    int highest = 0;

    // gets address of list
    TODO* listPtr = arr.getAddress();

    for(int i = 0; i<arr.getLength(); i++)
    {
        int num = std::stoi(listPtr[0].getID());
        if(num>highest)
            highest = num;
    }

    return highest;
}



// write the TODO array information on disk
void writeFile(DynamicArray<TODO>&arr)
{

    // make file object
    ofstream out;

    // parse through arr and add 
    out.open("TODOdata.txt", ios::out | ios::trunc);

    for(int i = 0; i<arr.getLength(); i++)
    {
        out << arr[i];
    }

    out.close();

}

// reads the TODO array information on disk
// 0 for no existing file, 1 for existing file
int readFile(DynamicArray<TODO> &arr)
{
    
    // declares file reader object
    ifstream inFile;

    // open file in in mode
    inFile.open("TODOdata.txt",ios::in);

    // if opening file fails
    if(inFile.fail())
    {
        // end function, return 0 for no file
        return 0;
    }
    else
    {

        // while the end of file is not reached
        while(!inFile.eof())
        {

            TODO obj;

            // read file into obj
            inFile >> obj;

            // add TODO item to list
            arr.addEnd(obj);

        }

        return 1;
    }

}



// tests all classes in program
void UnitTest()
{
    TODO todo;
    Date date;
    DynamicArray<int> arr;

    todo.ComponentTest();
    date.ComponentTest();
    arr.ComponentTest();
}

/***************************
 * END OF PROGRAM FUNCTIONS
***************************/