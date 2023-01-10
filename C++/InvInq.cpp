// Function: Inventory app using OOP and C++
// 
// InvInq.cpp
// Luke Villanueva, CISP 400
// 3/14/2021

//! DEV NOTES: Input validation only for ID, Quantity, and
//!            Wholesale Cost

//! Retail is treated like wholesale, and dates are
//! completely unchecked

//! Pardon the amount of lines; it's mostly due to the
//! amount of overloaded constructors and validation methods
//! in the classes

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::ostream;
using std::istream;



/*************
 * DATE CLASS
*************/
//! Input Validation for Date class is not developed
// Specification B1 - Date class
class Date
{
    private:
        // Private variables
        string month, day, year;

        // Private Functions
        // Input validation for month
        bool isMonthValid(string m)
        {
            if(m.length()>2)
                return true;
            return false;
        }
        // Input validation for day
        bool isDayValid(string d)
        {
            // If day is longer than 2, it's invalid
            if(d.length()>2)
                return false;

            // If day has any letters, it's invalid
            for(long unsigned int i = 0; i < d.length(); i++)
            {
                if(isalpha(d[i]))
                    return false;
            }

            // If day is more than 31, it's invalid
            double dblDay = std::stod(d);
            if(dblDay<0 || dblDay>31)
                return false;

            // else it's valid
            return true;
        }

    public:

        // Constructors

        Date()
        {
            month = "January";
            day = "1";
            year = "2021";
        }
        Date(string m)
        {
            month = m;
            day = "1";
            year = "2021";
        }
        Date(string m, string d)
        {
            month = m;
            day = d;
            year = "2021";
        }
        Date(string m, string d, string y)
        {
            month = m;
            day = d;
            year = y;
        }

        // Functions

        string entireDate()
        {
            string s = month + " " + day + ", " + year;
            return s;
        }

        // Setters
        // WARNING: THESE ARE NOT VALIDATED INPUTS
        void setDay(string d)
        {
            day = d;
        }

        void setMonth(string m)
        {
            month = m;
        }

        void setYear(string y)
        {
            year = y;
        }

        // declare friend function
        friend ostream &operator<<(ostream&, const Date&);
        friend istream &operator>>(istream&, Date&);

        // Specification B2 - ComponentTest method in Date
        void ComponentTest()
        {
            cout << "\n----------------------------------";
            cout << "\nDate Component Test";
            cout << "\nCommencing self diagnosis #1...";
            Date test("January","1","2021");
            if(test.entireDate()=="January 1, 2021")
            {
                cout << "\nTesting: success";
            }
            else
            {
                cout << "\nTesting: failure"
                     << "\nExpected results: January 1, 2021"
                     << "\nResults: " << test.entireDate();
            }

            cout << "\nCommencing self diagnosis #2...";
            Date test1("December");
            if(test1.entireDate()=="December 1, 2021")
            {
                cout << "\nTesting: success";
            }
            else
            {
                cout << "\nTesting: failure"
                     << "\nExpected results: December 1, 2021"
                     << "\nResults: " << test1.entireDate();
            }

            // end of self test
            cout << "\nCompleted self diagnosis.";
            cout << "\n----------------------------------";
        }
        // end of Specification B2 - ComponentTest method in Date
};
// end of Specification B1 - Date class





/*************
 * ITEM CLASS
*************/

// Item class - has all data for inventory management
// Prereq's: assumes the date is inputted M/D/Y
class Item
{
    private:
    int id, quantity; // item id number, & quantity at hand
    double wSale, retail; // wholesale & retail
    Date date; // date added to inventory
    
    public:

    // constructors

    // default
    Item()
    {
        id = 0;
        quantity = 0;
        wSale = 0.0;
        retail = 0.0;
    }

    // only id
    Item(string i)
    {
        // if id is not valid, make it empty value
        if(!validId(i))
        {
            id = 0;
        }

        // else, have it be equal to input
        //convert i to int first
        int iInt = std::stoi(i);

        id = iInt;
        quantity = 0;
        wSale = 0.0;
        retail = 0.0;
    }

    // id & quantity
    Item(string i, string q)
    {
        // if id is not valid, make it empty value
        if(!validId(i))
        {
            id = 0;
        }
        // if q is not valid, make it empty
        if(!validQuantity(q))
        {
            quantity = 0;
        }

        // else, have them be equal to input
        //convert i to int
        int iInt = std::stoi(i);
        //convert q to int
        int qInt = std::stoi(q);

        id = iInt;
        quantity = qInt;
        wSale = 0.0;
        retail = 0.0;
    }
    
    // id, quantity, & wholesale cost
    Item(string i, string q, string w)
    {
        // if id is not valid, make it empty value
        if(!validId(i))
        {
            id = 0;
        }
        // if q is not valid, make it empty
        if(!validQuantity(q))
        {
            quantity = 0;
        }
        // if w is not valid, make it empty
        if(!validWSale(w))
        {
            wSale = 0.0;
        }

        // else, have them be equal to input
        //convert i to int
        int iInt = std::stoi(i);
        //convert q to int
        int qInt = std::stoi(q);
        //convert w to double
        double wDbl = std::stod(w);

        id = iInt;
        quantity = qInt;
        wSale = wDbl;
        retail = 0.0;
    }

    // id, quantity, wholesale cost, & retail cost
    Item(string i, string q, string w, string r)
    {
        // if id is not valid, make it empty value
        if(!validId(i))
        {
            id = 0;
        }
        // if q is not valid, make it empty
        if(!validQuantity(q))
        {
            quantity = 0;
        }
        // if w is not valid, make it empty
        if(!validWSale(w))
        {
            wSale = 0.0;
        }
        if(!validRetail(r))
        {
            retail = 0.0;
        }

        // else, have them be equal to input
        //convert i to int
        int iInt = std::stoi(i);
        //convert q to int
        int qInt = std::stoi(q);
        //convert w to double
        double wDbl = std::stod(w);
        //convert r to double
        double rDbl = std::stod(r);

        id = iInt;
        quantity = qInt;
        wSale = wDbl;
        retail = rDbl;
    }

    // id, quantity, wholesale cost, retail cost, and date
    Item(string i, string q, string w, string r, 
         string day, string month, string year)
    {
        // if id is not valid, make it empty value
        if(!validId(i))
        {
            id = 0;
        }
        // if q is not valid, make it empty
        if(!validQuantity(q))
        {
            quantity = 0;
        }
        // if w is not valid, make it empty
        if(!validWSale(w))
        {
            wSale = 0.0;
        }
        if(!validRetail(r))
        {
            retail = 0.0;
        }

        // else, have them be equal to input
        //convert i to int
        int iInt = std::stoi(i);
        //convert q to int
        int qInt = std::stoi(q);
        //convert w to double
        double wDbl = std::stod(w);
        //convert r to double
        double rDbl = std::stod(r);

        id = iInt;
        quantity = qInt;
        wSale = wDbl;
        retail = rDbl;
        date.setDay(day);
        date.setMonth(month);
        date.setYear(year);
    }

    // Input Validations

    // Specification B4 - Inventory Entry Input Validation
    bool validId(string n)
    {
        // invalid id: more than 5 digits, not all numbers
        if(n.length()>5)
        {
            cout << "\nERROR: Invalid ID input";
            return false;
        }

        for(long unsigned int i = 0; i<n.length(); i++)
        {
            if(!isdigit(n[i]))
            {
                cout << "\nERROR: Invalid ID input";
                return false;
            }
        }

        // all else, return true
        return true;
    }

    bool validQuantity(string q)
    {
        // check if input is all numbers
        for(long unsigned int i = 0; i < q.length(); i++)
        {
            if(!isdigit(q[i]))
            {
                cout << "\nERROR: Invalid quantity";
                return false;
            }
        }

        // convert to int
        int qInt = std::stoi(q);

        // check if input is negative
        if(qInt<0)
        {
            cout << "\nERROR: Invalid quantity";
            return false;
        }

        // all else, return true
        return true;
    }

    bool validWSale(string w)
    {
        int dots = 0; // counter for decimals

        // check if just all numebrs and decimals
        for(long unsigned int i = 0; i<w.length(); i++)
        {
            // if char is a decimal
            if(w[i]=='.')
                dots++;
            // if char is not a digit or a decimal
            if(!isdigit(w[i]) && w[i]!='.')
            {
                cout << "\nERROR: Invalid wholesale";
                return false;
            }
        }

        // invalid if more than 1 decimal
        if(dots>1)
        {
            cout << "\nERROR: Invalid wholesale";
            return false;
        }

        // all else, it's valid
        return true;

    }

    bool validRetail(string r)
    {
        int dots = 0; // counter for decimals

        // check if just all numebrs and decimals
        for(long unsigned int i = 0; i<r.length(); i++)
        {
            // if char is a decimal
            if(r[i]=='.')
                dots++;
            // if char is not a digit or a decimal
            if(!isdigit(r[i]) && r[i]!='.')
            {
                cout << "\nERROR: Invalid wholesale";
                return false;
            }
        }

        // invalid if more than 1 decimal
        if(dots>1)
        {
            cout << "\nERROR: Invalid wholesale";
            return false;
        }

        // all else, it's valid
        return true;
    }

    // date's overloaded functions
    //! Validates only day
    bool validDateDay(string d)
    {
        // invalid if more than 2 length 
        if(d.length()>2)
        {
            cout << "\nERROR: Invalid day for date";
            return false;
        }
        
        //invalid if not all integers
        for(long unsigned int i = 0; i<d.length(); i++)
        {
            if(!isdigit(d[i]))
            {
                cout << "\nERROR: Invalid day for date";
                return false;
            }
        }

        // all else, it is valid
        return true;
    }
    // end of Specification B4 - Inventory Entry Input Validation

    //? DEV NOTE: maybe will continue the rest of 
    //? validDate overloads


    // Functions - Setters

    void setId(string i)
    {
        // if id is not valid, make it empty value
        if(validId(i))
        {
            int iInt = std::stoi(i);

            id = iInt;
        }
    }

    void setQuantity(string q)
    {
        // if q is not valid, make it empty
        if(validQuantity(q))
        {
            int qInt = std::stoi(q);

            quantity = qInt;
        }
    }

    void setWSale(string w)
    {
        if(validWSale(w))
        {
            double wDbl = std::stod(w);

            wSale = wDbl;
        }
    }

    void setRetail(string r)
    {
        if(validRetail(r))
        {
            double rDbl = std::stod(r);

            retail = rDbl;
        }
    }

    // set day of date
    void setDateDay(string d)
    {
        date.setDay(d);
    }

    // set day and month of date
    void setDateMonth(string m)
    {
        date.setMonth(m);
    }

    // set day, month, and year of date
    void setDateYear(string y)
    {
        date.setYear(y);
    }


    // Functions - Getters
    int getId()
    {return id;}

    int getQuantity()
    {return quantity;}

    double getWSale()
    {return wSale;}

    double getRetail()
    {return retail;}

    Date getDate()
    {return date;}


    // Component Test - Self Diagnosis
    void ComponentTest()
    {
        cout << "\n\n-------------------------------------";
        cout << "\nCommencing Item Self Diagnosis...";
        Item test("12","20","12.05","20.25","2","February",
                  "2021");
        // id test
        cout << "\nID Test: ";
        if(test.getId()==12)
            cout << "Successful";
        else 
            cout << "Fail\nExpected: 12\nResults: " << test.getId();
        
        // quantity test
        cout << "\nQuantity Test: ";
        if(test.getQuantity()==20)
            cout << "Successful";
        else 
            cout << "Fail\nExpected: 20\nResults: " << test.getQuantity();

        // wholesale test
        cout << "\nWholesale Test: ";
        if(test.getWSale()==12.05)
            cout << "Successful";
        else
            cout << "Fail\nExpected: 12.05\nResults: " << test.getWSale();
        
        cout << "\n\nEnding Item Self Diagnosis...";
        cout << "\n\n-------------------------------------";
    }


    // friend declarations
    friend ostream &operator<<(ostream&, const Item&);
    friend istream &operator>>(istream&, Item&);
};




/**********************
 * DYNAMIC ARRAY CLASS
**********************/

//? NOTE: this dynamic array class is specified to hold
//? a list of ITEM objects
// Specification C2 - Dynamic Array
class DynamicArray
{
    private:
    int length; // actual number of objects
    int size = 1; // size of initialized array
    Item* listPtr;


    public:
    // contructor
    DynamicArray()
    {
        // no actual objects being stored
        length = 0;

        // initialize to 1 for buffer memory 
        listPtr = new Item[size]; 
    }

    // desctructor 
    ~DynamicArray()
    {
        // clean up allocated memory
        delete [] listPtr;
        listPtr = nullptr;
    }

    // returns length
    int getLength()
    {return (static_cast<int>(length));}

    //! This is a functions specific to Item
    // returns item object at index
    Item getItem(int index)
    {
        return listPtr[index];
    }

    // returns address of list
    Item* getAddress()
    {return listPtr;}

    // Specification C3 - Resize Array - add to end
    void add(Item item)
    {
        // allocate temp array w/ 1 more than size
        Item* temp = new Item[size+1];

        // increment size
        size++;

        // last element of length is the new Item
        temp[length] = item;

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
    // end of Specification C3 - Resize Array - add to end

    // Specification C4 - Resize Array - subtract from end
    void subtract()
    {
        // check if size is already at minimum
        // subtract if there's space still
        if(size > 1 && length > 0)
        {
            // allocate temp array w/ 1 less than size
            Item* temp = new Item[size-1];

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

            cout << "\nDeleted item...";
        }
        // else, print error message
        else
        {
            cout << "\nERROR: Array is already at minimum size";
        }
    }
    // end of Specification C4 - Resize Array - subtract from end

    // edit inventory
    // param: itm to insert in, index where item should be
    // Specification A1 - Edit Inventory
    void edit(Item itm, int ind)
    {
        // allocate temp array 
        Item* temp = new Item[size];

        // copy the first half of array
        for(int i = 0; i<ind; i++)
        {
            temp[i] = listPtr[i];
        }

        // insert object at index
        temp[ind] = itm;

        // copy the rest of the array
        for(int i = ind+1; i<size; i++)
        {
            temp[i] = listPtr[i];
        }

        // delete old arr
        delete [] listPtr;

        // change ptr from old arr to new arr
        listPtr = temp;

        cout << "\nEdited Item #" << ind+1;
    }
    // end of Specification A1 - Edit Inventory

    // Component Test - Self Diagnosis, based on Item class
    void ComponentTest()
    {
        cout << "\n\n-------------------------------------";
        cout << "\nCommencing DynamicArray (class: Item) Self Diagnosis...";
        
        // testing add()
        cout << "\nAdd() Test: ";
        DynamicArray addTest;
        Item itemTest;
        addTest.add(itemTest);
        if(addTest.getLength()==1)
            cout << "Successful";
        else
            cout << "Fail\nExpected: 1\nResults: " << addTest.getLength();

        // testing subtract()
        cout << "\nSubtract() Test (using the same test objects): ";
        addTest.subtract();
        if(addTest.getLength()==0)
            cout << "Successful";
        else
            cout << "Fail\nExpected: 0\nResults: " << addTest.getLength();


        cout << "\n\nEnding DynamicArray (class: Item) Self Diagnosis...";
        cout << "\n\n-------------------------------------";
    }

};
// end of Specification C2 - Dynamic Array





/*********************
 * OPERATOR OVERLOADS 
*********************/ 

// For Date Class:

// Specification A2 - Overload operator<<
ostream &operator<<(ostream& os, const Date& dt) 
{
    os << dt.day << " " << dt.month << " " << dt.year;
    return os;
}
// end of Specification A2 - Overload operator<<

// Specification A3 - Overload operator>>
istream &operator>>(istream& os, Date& dt)
{
    os >> dt.day >> dt.month >> dt.year;
    return os;
}
// end of Specification A3 - Overload operator>>


// For Item Class:

ostream &operator<<(ostream &os, const Item &item)
{
    os << "\nID Number: " << item.id
       << "\nQuantity: " << item.quantity
       << "\nWholesale Cost: " << item.wSale
       << "\nRetail Cost: " << item.retail
       << "\nDate Added to Inventory: " << item.date;
    return os;
}

istream &operator>>(istream &os, Item &item)
{
    os >> item.id >> item.quantity >> item.wSale
       >> item.retail >> item.date;
    return os;
}




/***********************
 * FUNCTION PROTOTYPES 
***********************/
void ProgramGreeting();
int menu();
bool isPositiveDigit(string);
void UnitTest();



/*************************************
 * MAIN FUNCTION AND HELPER FUNCTIONS
*************************************/


int main()
{
    int menuChoice; // user's choice in menu
    DynamicArray inv; //initialize dynamic array object

    // Program Greeting
    ProgramGreeting();

    // Unit test - tests all classes: Date, Item, and DynamicArray
    UnitTest();

    do
    {
        menuChoice = menu();

        // quit program
        if(menuChoice==0)
        {
            cout << "\n-----------------------------------"
                 << "\nThank you for using the "
                    "Inventory Inquisitor!"
                 << "\n-----------------------------------"
                 << "\nProgram ending...\n\n";
        }
        // add inventory
        else if(menuChoice==1)
        {
            string id, quant, wsale, retail, day, month, year;
            Item item;

            cout << "\nAdding to Inventory...";

            do
            {
                cout << "\nPlease input ID: ";
                getline(cin,id);
            }while(!item.validId(id));

            do
            {
                cout << "\nPlease input quantity: ";
                getline(cin,quant);
            } while (!item.validQuantity(quant));
            
            do
            {
                cout << "\nPlease input wholsale cost: ";
                getline(cin,wsale);
            } while (!item.validWSale(wsale));
            
            do
            {
                cout << "\nPlease input retail cost: ";
                getline(cin, retail);
            } while (!item.validRetail(retail));
            
            cout << "\nPlease input date day: ";
            getline(cin,day);

            cout << "\nPlease input date month: ";
            getline(cin, month);

            cout << "\nPlease input date year: ";
            getline(cin,year);

            // sets item data to the inputs
            item.setId(id);
            item.setQuantity(quant);
            item.setWSale(wsale);
            item.setRetail(retail);
            item.setDateDay(day);
            item.setDateMonth(month);
            item.setDateYear(year);

            //displays created item
            cout << "\n\nNew Item Info:" << item;

            // adds created item to inv
            inv.add(item);

            cout << "\n\nItem has been added!";
        }

        // subtract inventory
        else if(menuChoice==2)
        {
            inv.subtract();
        }

        // edit inventory
        else if(menuChoice==3)
        {
            if(inv.getLength()!=0)
            {
                string num="", 
                    id,quant,wsale,retail,day,month,year;

                cout << "\nEditing Inventory..."
                    << "\nWhich item number do you want to edit?";

                // user input item number
                getline(cin,num);

                // if number is not a valid item number
                // invalid if less than 1 or more than inv length
                while(!isPositiveDigit(num) || 
                std::stoi(num)<1 || 
                std::stoi(num)>inv.getLength())
                {
                    cout << "\nERROR: Invalid item number"
                        << "\nPlease try again\n";
                    getline(cin,num);
                }

                // convert input from str to int 
                // in order to get index
                int ind = std::stoi(num) - 1;

                // get item from inventory list
                Item itm;

                //prompt user to edit item
                do
                {
                    cout << "\nPlease input ID: ";
                    getline(cin,id);
                }while(!(itm.validId(id)));

                do
                {
                    cout << "\nPlease input quantity: ";
                    getline(cin,quant);
                } while (!(itm.validQuantity(quant)));
                
                do
                {
                    cout << "\nPlease input wholsale cost: ";
                    getline(cin,wsale);
                } while (!(itm.validWSale(wsale)));
                
                do
                {
                    cout << "\nPlease input retail cost: ";
                    getline(cin, retail);
                } while (!(itm.validRetail(retail)));
                
                cout << "\nPlease input date day: ";
                getline(cin,day);

                cout << "\nPlease input date month: ";
                getline(cin, month);

                cout << "\nPlease input date year: ";
                getline(cin,year);

                // sets item data to the inputs
                itm.setId(id);
                itm.setQuantity(quant);
                itm.setWSale(wsale);
                itm.setRetail(retail);
                itm.setDateDay(day);
                itm.setDateMonth(month);
                itm.setDateYear(year);

                //displays created item
                cout << "\n\nItem Info:" << itm;

                // edits the array
                inv.edit(itm,ind);

                cout << "\n\nItem has been edited!";
            }
            else
                cout << "\nThere are no items in inventory...";
        }

        // display inventory
        else if(menuChoice==4)
        {
            cout << "\n\nEntire Inventory:";

            for(int i = 0; i<inv.getLength(); i++)
            {
                cout << "\n\nItem #" << i+1
                     << "\nID: " << (inv.getItem(i)).getId()
                     << "\nQuantity: " << (inv.getItem(i)).getQuantity()
                     << "\nWholesale: " << (inv.getItem(i)).getWSale()
                     << "\nRetail: " << (inv.getItem(i)).getRetail()
                     << "\nDate: " << (inv.getItem(i)).getDate();
            }
            cout << "\n---------------------------------";
        }
    }while(menuChoice!=0);
}

// Program Greeting
void ProgramGreeting()
{
    cout << "\n---------------------------------------------"
         << "\nWelcome to the Inventory Inquisitor Program!"
         << "\nDesciption: This program is an inventory manager."
            "\nYou are able to add, delete, edit, and display"
            " the inventory"
         << "\n---------------------------------------------";
}

// Specification B3 - Menu Input Validation
bool validMenu(string c)
{
    // invalid if input is more than 1 OR choice is not valid letter
    if(c.length()==1 && 
       (c[0]=='A' ||  c[0]=='D' ||  c[0]=='E' ||  c[0]=='S' || 
       c[0]=='Q' ||  c[0]=='a' ||  c[0]=='d' ||  c[0]=='e' || 
       c[0]=='s' ||  c[0]=='q'))
        return true;

    // else, it is valid
    return false;
}
// end of Specification B3 - Menu Input Validation

// Specification C1 - Alpha Menu
// menu function returns int
// 0 - exit, 1 - add, 2 - delete, 3 - edit, 4 - display
// -1 for error
int menu()
{
    string choiceStr = "";
    char choice;

    cout << "\n\nPlease input the corresponding letter to "
            "your choice"
         << "\n<A>dd Inventory"
         << "\n<D>elete Inventory"
         << "\n<E>dit Inventory"
         << "\n<S>how Inventory"
         << "\n<Q>uit Program\n";

    getline(cin, choiceStr);
    while(!validMenu(choiceStr))
    {
        cout << "\nERROR: Invalid input. Please try again\n";
        getline(cin, choiceStr);
    }
    
    // convert choice into character
    choice = choiceStr[0];

    // decision based on letter
    if(choice == 'A' || choice == 'a')
        return 1;
    if(choice == 'D' || choice == 'd')
        return 2;
    if(choice == 'E' || choice == 'e')
        return 3;
    if(choice == 'S' || choice == 's')
        return 4;
    if(choice == 'Q' || choice == 'q')
        return 0;

    return -1;
}
// end of Specification C1 - Alpha Menu

// helper function for main()
// validates if item selection for editing is valid
bool isPositiveDigit(string n)
{
    // checks if it's a singular number
    if(n.length()>1)
        return false;
    //convert into int
    int nInt = std::stoi(n);
    // checks if non negative
    if(nInt<0)
        return false;
    // otherwise, it is valid
    return true;
}

// Specification A4 - UnitTest() method in main()
void UnitTest()
{
    // declare test objects
    Date dateTest;
    Item itemTest;
    DynamicArray arrayTest;

    // testing
    dateTest.ComponentTest();
    itemTest.ComponentTest();
    arrayTest.ComponentTest();
}
// end of Specification A4 - UnitTest() method in main()