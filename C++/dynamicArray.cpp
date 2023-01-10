//! dynamicArray.cpp
//! Luke Villanueva


/**********************************************
 * Program Description:
 * Custom-made class for an array able to dynamically change size
 * Including: iostream
 * Using: std::string, std::cout, std::ostream
**********************************************/

#include <iostream>
using std::string;
using std::cout;
using std::ostream;

/**********************
 * DYNAMIC ARRAY CLASS
**********************/


template <typename type>
class DynamicArray
{
private:
    int length; // actual amount of objects in array
    int arrSize; // amount of declared spots in array (+1 of length)
    type* listPtr; // ptr to the array

    // Private Functions

    // validity check for getElem
    bool validIndex(int n)
    {
        if (n<0 || n>length - 1)
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

    // destructor
    ~DynamicArray()
    {
        delete[] listPtr;
        listPtr = nullptr;
    }

    // int input
    DynamicArray(int num)
    {
        length = num;
        arrSize = num + 1;
        listPtr = new type[arrSize];
    }

    // double input
    DynamicArray(double num)
    {
        num = (int)(num);
        length = num;
        arrSize = num + 1;
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
        type* temp = new type[arrSize + 1];

        // increment size
        arrSize++;

        // last element of length is the new element
        temp[length] = e;

        // copy the rest of old arr to new arr
        for (int i = 0; i < length; i++)
        {
            temp[i] = listPtr[i];
        }

        // delete old array
        delete[] listPtr;

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
        if (arrSize > 1 && length > 0)
        {
            // allocate temp array w/ 1 less than size
            type* temp = new type[arrSize - 1];

            // copy old arr to new arr except for last item
            for (int i = 0; i < length - 1; i++)
            {
                temp[i] = listPtr[i];
            }

            // delete old arr
            delete[] listPtr;

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
        type* temp = new type[arrSize + 1];

        // increment size
        arrSize++;

        // first element of length is the new element
        temp[0] = e;

        // copy the rest of old arr to new arr
        for (int i = 0; i < length; i++)
        {
            // temp at ind 1 and old at ind 0
            temp[i + 1] = listPtr[i];
        }

        // delete old array
        delete[] listPtr;

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
        if (validIndex(num))
        {
            // allocate temp array
            type* temp = new type[arrSize - 1];

            // decrement arrSize
            arrSize--;

            // copy first half of array
            for (int i = 0; i < num; i++)
            {
                temp[i] = listPtr[i];
            }

            // copy second half of array
            for (int i = num + 1; i < length; i++)
            {
                temp[i - 1] = listPtr[i];
            }

            // delete old array
            delete[] listPtr;

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
        if (arrSize > 1 && length > 0)
        {
            // allocate temp array w/ 1 less than size
            type* temp = new type[arrSize - 1];

            // copy old arr to new arr except for first item
            for (int i = 1; i < length; i++)
            {
                temp[i - 1] = listPtr[i];
            }

            // delete old arr
            delete[] listPtr;

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
        if (!validIndex(num))
            cout << "\nERROR: Invalid index, RETURNING INVALID INDEX";
        return *(listPtr + num);

    }

    // get at given DOUBLE index 
    type& getElem(double num)
    {
        int n = (int)(num);
        if (validIndex(num))
            return *(listPtr + n);
        else
            cout << "\nERROR: Invalid index";
    }

    // switch elems at two given indices
    void switchElems(int ind1, int ind2)
    {
        type temp = listPtr[ind1];

        listPtr[ind1] = listPtr[ind2];

        listPtr[ind2] = temp;
    }

    // replace elem at given DOUBLE index 

    // display array

    // reset arr, length is 0

    // resize arr, second param to fill empty slots

    // get arr length
    int getLength()
    {
        return length;
    }

    // get array memory location
    type* getAddress()
    {
        return listPtr;
    }

    // Overloaded Functions

    // Component Testing, ARRAY OF INT
    void ComponentTest()
    {
        DynamicArray test;

        cout << "\n----------------------------------------"
            << "\nCommencing DynamicArray Testing...";

        cout << "\nTest #1: ";

        // testing default initialization
        if (test.getLength() == 0)
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

        test.addStart(5);

        // testing addStart() & getElem()
        if (test.getElem(0) == 5)
        {
            cout << "success";
        }
        else
        {
            cout << "failure"
                << "\n Expected: 5"
                << "\nActual: " << getElem(0);
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
        return *(listPtr + num);
    }

    // External Function Declarations
    template <typename T>
    friend ostream& operator<<(ostream&, const DynamicArray<T>&);

    /*************************
     * END OF ADAPTABILITY FUNCTIONS
    *************************/



};

ostream& operator<<(ostream& os, DynamicArray<int>& arr)
{
    if (arr.getLength() == 0)
        os << "\nERROR: Array is empty";
    else
    {
        os << "\nArray contents: ";
        for (int i = 0; i < arr.getLength(); i++)
        {
            os << "\n" << arr[i];
        }
    }
    return os;
}


/**********************
 * END OF DYNAMIC ARRAY CLASS
**********************/



int main()
{
    DynamicArray<int> arr;

    arr.addStart(1);
    arr.addStart(2);

    cout << arr;

    arr.switchElems(0, 1);

    cout << arr;

    return 0;
}