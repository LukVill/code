// Function: a "Pokemon"-esque simulator
// where you have to take care of your Hokeemon
// or else they die
// 
//  hokeemon.cpp
// Luke Villanueva, CISP 400
// 4/25/2021

#include <iostream>
#include <string>
#include <ctime>
#include <memory>
using std::cout;
using std::string;
using std::ostream;
using std::unique_ptr;

// helper function for all RNG purposes in program
int RandomNumber(int lo, int hi)
{
    // Return invalid if: hi<lo, lo<1
    if(hi<lo || lo<0)
        return -1;

    // Difference between hi and lo
    int diff = hi-lo; 

    // Random num generated
    int num = rand()%(diff+1)+lo;

    // Return random num if it's less or equal to 100
    return num;
}


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
        if(n<0 || n>length-1)
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
        if(!validIndex(num))
            cout << "\nERROR: Invalid index, RETURNING INVALID INDEX";
        return *(listPtr+num);

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

    // Component Testing, ARRAY OF INT
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

        test.addStart(5);

        // testing addStart() & getElem()
        if(test.getElem(0)==5)
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
        return *(listPtr+num);
    }

    // External Function Declarations
    template <typename T>
    friend ostream& operator<<(ostream&, const DynamicArray<T>&);

    /*************************
     * END OF ADAPTABILITY FUNCTIONS
    *************************/



};

ostream& operator<<(ostream& os, DynamicArray<int>&arr)
{
    if(arr.getLength()==0)
        os << "\nERROR: Array is empty";
    else
    {
        os << "\nArray contents: ";
        for(int i = 0; i<arr.getLength(); i++)
        {
            os << "\n" << arr[i];
        }
    }
    return os;
}


/**********************
 * END OF DYNAMIC ARRAY CLASS 
**********************/


// Specification C2 - Creature Class

/***************************
 * CREATURE ABSTRACT CLASS
***************************/


class Creature
{

    protected:
    int hunger, boredom, eyes, tails, horns;
    string name,species;
    bool dead;

    public:

    // default constructor
    Creature()
    {
        // generates random num between 0-5
        hunger = RandomNumber(1,4);
        boredom = RandomNumber(1,4);

        // traits initialization
        eyes = 0;
        tails = 0;
        horns = 0;

        name = "";
        species = "";

        dead = false;
    }

    // Specification A2 - Copy Constructor

    // copy constructor
    Creature(Creature& obj)
    {
        // generates random num between 0-5
        hunger = RandomNumber(1,4);
        boredom = RandomNumber(1,4);

        // traits initialization
        eyes = obj.getEyes();
        tails = obj.getTails();
        horns = obj.getHorns();

        name = obj.getName();
        species = obj.getSpecies();

        dead = false;
    }

    // end of Specification A2 - Copy Constructor

    virtual void Listen()
    {
        if(boredom<=20)
        {
            cout << "\nMy hunger is at " << hunger
             << "\nMy boredom is at " << boredom;
        }
        // boredom exceeding 20
        else
        {
            cout << "\nI'm so bored! Ugh!";
        }
    }

    virtual void Appearance()
    {
        cout << "\n" << name << " has:"
             << std::endl << eyes << " eye(s)"
             << std::endl << tails << " tail(s)"
             << std::endl << horns << " horn(s)";
    }

    // Specification B2 - Virtual Class Creature

    // feed the Hokeemon
    virtual void Feed() = 0;

    // play with Hokeemon
    virtual void Play() = 0;

    // get behavior details on Hokeemon
    virtual void Data() = 0;

    // end of Specification B2 - Virtual Class Creature

    // Specification C1 - PassTime()

    // when time passes, hunger lessens and boredom grows
    void PassTime()
    {
        // Specification A4 - Write a Lambda
        auto decreaseInt = [](int var){return var-1;};
        // end of Specification A4 - Write a Lambda

        hunger = decreaseInt(hunger);
        boredom++;

        if(hunger<=0)
            dead = true;

        if(boredom >=20)
        {
            // makes it so creature is just exceeding
            // so boredom can be fixable
            boredom = 21;
        }
    }

    // end of Specification C1 - PassTime()

    // FUNCTIONS

    int getEyes()
    {return eyes;}

    int getTails()
    {return tails;}

    int getHorns()
    {return horns;}

    // gets hunger lvl
    int getHunger()
    {return hunger;}

    // gets boredom lvl
    int getBoredom()
    {return boredom;}

    // Specification A1 - Critter Name

    // gets name of Hokeemon
    string getName()
    {return name;}

    // end of Specification A1 - Critter Name

    // gets name of species of Hokeemon
    string getSpecies()
    {return species;}

    bool getDead()
    {return dead;}

    // sets name of Hokeemon
    void setName(string s)
    {name = s;}

    // sets name of species of Hokeemon
    void setSpecies(string s)
    {species = s;}

    void setHunger(int n)
    {hunger = n;}

    void setBoredom(int n)
    {boredom = n;}

    void setDead(bool b)
    {dead = b;}

    void setEyes(int n)
    {eyes = n;}

    void setTails(int n)
    {tails = n;}

    void setHorns(int n)
    {horns = n;}
};

/***********************************
 * END OF CREATURE ABSTRACT CLASS
***********************************/

// end of Specification C2 - Creature Class

/****************************************
 * NORMA CLASS - CHILD OF CREATURE CLASS
****************************************/


// Specification B1 - Child Class

// a normal hokeemon
class Norma : public Creature
{
    private:

    public:

    // default constructor
    Norma()
    {
        name = "Norma";
        species = "Norma";
        eyes = 1;
    }

    // copy constructor (copies Creature into Norma)
    Norma(Creature* c)
    {
        // generates random num between 0-5
        hunger = RandomNumber(1,4);
        boredom = RandomNumber(1,4);

        // traits initialization
        eyes = c->getEyes();
        tails = c->getTails();
        horns = c->getHorns();

        name = c->getName();
        species = c->getSpecies();

        dead = false;
    }

    void Feed()
    {
        hunger += RandomNumber(4,5);
        cout << "\n*bites* Yum! Thank you!";
    }

    void Play()
    {
        boredom -= RandomNumber(5,7);
        cout << "\nYay! That was fun! Thank you!";
    }

    void Data()
    {
        cout << "\nThis is a very obedient creature."
             << "\nVery docile and gentle, "
                "it can be easily fed and played with";
    }

    // Specification B4 - Overload + Operator

    // returns a creature ptr to be transformed into creature
    Creature* operator+(Creature* obj)
    {
        Creature* c;

        // Norma + Norma
        if(obj->getSpecies()=="Norma")
        {
            *c = *obj;
        }

        if(obj->getSpecies()=="Pleyo" || obj->getSpecies()=="Angan")
        {
            // copies everything first
            *c = *obj;

            // combines both traits
            c -> setEyes(eyes + (obj->getEyes()));
            c -> setTails(tails + (obj->getTails()));
            c -> setHorns(horns + (obj->getHorns()));

            // Norma + Pleyo
            if(obj->getSpecies()=="Pleyo")
                c -> setName("Pleyo");

            // Norma + Angan
            if(obj->getSpecies()=="Angan")
                c -> setName("Angan");
        }

        return c;
    }

    // end of Specification B4 - Overload + Operator

    // Specification B3 - Overload Assignment Operator

    Norma operator=(Creature* c)
    {
        Norma obj;

        // generates random num between 0-5
        obj.setHunger(RandomNumber(1,4));
        obj.setBoredom(RandomNumber(1,4));

        // traits initialization
        obj.setEyes(c->getEyes());
        obj.setTails(c->getTails());
        obj.setHorns(c->getHorns());

        obj.setName(c->getName());
        obj.setSpecies(c->getSpecies());

        obj.setDead(false);

        return obj;
    } 

    // end of Specification B3 - Overload Assignment Operator

    void ComponentTest()
    {
        Norma test;
        cout << "\n-------------------------------------"
             << "\nCommencing Norma class testing...";

        // tests basic initialization     
        cout << "\nTest #1: ";

        if(test.getName()=="Norma"&&test.getSpecies()=="Norma")
        {
            cout << "successful";
        }
        else
        {
            cout << "failed"
                 << "\nExpected: Name = Norma, Species = Norma"
                 << "\nResults: Name = " << test.getName()
                 << ", Species = " << test.getSpecies();
        }

        // tests changing information
        cout << "\nTest #2: ";

        test.setName("Test Name");
        test.setSpecies("Test Species");

        if(test.getName()=="Test Name"&&test.getSpecies()=="Test Species")
        {
            cout << "successful";
        }
        else
        {
            cout << "failed"
                 << "\nExpected: Name = Test Name, Species = Test Species"
                 << "\nResults: Name = " << test.getName()
                 << ", Species = " << test.getSpecies();
        }

        // tests PassTime() which has lambda function
        cout << "\nTest #3: ";

        int initialHunger = test.getHunger();

        test.PassTime();

        int nextHunger = test.getHunger();

        if(nextHunger==(initialHunger-1))
        {
            cout << "successful";
        }
        else
        {
            cout << "failed"
                 << "\nExpected: Hunger = " << initialHunger
                 << "\nResults: Hunger = " << nextHunger;
        }

        // testing completed
        cout << "\nNorma class testing completed..."
             << "\n-------------------------------------";
    }


    friend ostream& operator<<(ostream& os, Norma obj);
};

// Specification C4 - Overload <<

ostream& operator<<(ostream&os, Norma obj)
{
    os << "\n" << obj.name << " the " << obj.species
       << "\nHunger Lvl: " << obj.hunger
       << "\nBoredom Lvl: " << obj.boredom;
    return os;
}

// end of Specification C4 - Overload <<

// end of Specification B1 - Child Class


/***********************************************
 * END OF NORMA CLASS - CHILD OF CREATURE CLASS
***********************************************/


/***********************************************
 * PLEYO CLASS - CHILD OF CREATURE CLASS
***********************************************/

// Specification A3 - Second Child Class

// playful Hokeemon that won't eat until they're entertained
class Pleyo : public Creature
{

    private:

    public:

    // default constructor
    Pleyo()
    {
        name = "Pleyo";
        species = "Pleyo";
        eyes = 2;
        tails = 1;
    }

    // copy constructor (copies Creature into Pleyo)
    Pleyo(Creature* c)
    {
        // generates random num between 0-5
        hunger = RandomNumber(1,4);
        boredom = RandomNumber(1,4);

        // traits initialization
        eyes = c->getEyes();
        tails = c->getTails();
        horns = c->getHorns();

        name = c->getName();
        species = c->getSpecies();

        dead = false;
    }

    void Feed()
    {
        if(boredom > 10)
        {
            cout << "\nI don't want to eat! I want to play!";
        }
        else
        {
            hunger += RandomNumber(4,5);
            cout << "\n*nom nom nom* Delicious!";
        }
    }

    void Play()
    {
        boredom -= RandomNumber(5,7);
        cout << "\nHaha!!! That was crazy!!!";
    }

    void Data()
    {
        cout << "\nThis is a very playful creature."
             << "\nVery observant and excitable, "
                "it may be difficult to feed it without "
                "\nplaying with it.";
    }

    // returns a creature ptr to be transformed into creature
    Creature* operator+(Creature* obj)
    {
        Creature* c;

        // Norma + Norma
        if(obj->getSpecies()=="Pleyo")
        {
            *c = *obj;
        }

        if(obj->getSpecies()=="Norma" || obj->getSpecies()=="Angan")
        {
            // copies everything first
            *c = *obj;

            // combines both traits
            c -> setEyes(eyes + (obj->getEyes()));
            c -> setTails(tails + (obj->getTails()));
            c -> setHorns(horns + (obj->getHorns()));

            // Norma + Pleyo
            if(obj->getSpecies()=="Norma")
                c -> setName("Norma");

            // Norma + Angan
            if(obj->getSpecies()=="Angan")
                c -> setName("Angan");
        }

        return c;
    }

    Pleyo operator=(Norma c)
    {
        Pleyo obj;

        // generates random num between 0-5
        obj.setHunger(RandomNumber(1,4));
        obj.setBoredom(RandomNumber(1,4));

        // traits initialization
        obj.setEyes(c.getEyes());
        obj.setTails(c.getTails());
        obj.setHorns(c.getHorns());

        obj.setName(c.getName());
        obj.setSpecies(c.getSpecies());

        obj.setDead(false);

        return obj;
    }  

    Pleyo operator=(Creature* c)
    {
        Pleyo obj;

        // generates random num between 0-5
        obj.setHunger(RandomNumber(1,4));
        obj.setBoredom(RandomNumber(1,4));

        // traits initialization
        obj.setEyes(c->getEyes());
        obj.setTails(c->getTails());
        obj.setHorns(c->getHorns());

        obj.setName(c->getName());
        obj.setSpecies(c->getSpecies());

        obj.setDead(false);

        return obj;
    } 

    void ComponentTest()
    {
        Pleyo test;
        cout << "\n-------------------------------------"
             << "\nCommencing Pleyo class testing...";

        // tests basic initialization     
        cout << "\nTest #1: ";

        if(test.getName()=="Pleyo"&&test.getSpecies()=="Pleyo")
        {
            cout << "successful";
        }
        else
        {
            cout << "failed"
                 << "\nExpected: Name = Pleyo, Species = Pleyo"
                 << "\nResults: Name = " << test.getName()
                 << ", Species = " << test.getSpecies();
        }

        // tests changing information
        cout << "\nTest #2: ";

        test.setName("Test Name");
        test.setSpecies("Test Species");

        if(test.getName()=="Test Name"&&test.getSpecies()=="Test Species")
        {
            cout << "successful";
        }
        else
        {
            cout << "failed"
                 << "\nExpected: Name = Test Name, Species = Test Species"
                 << "\nResults: Name = " << test.getName()
                 << ", Species = " << test.getSpecies();
        }

        // tests PassTime() which has lambda function
        cout << "\nTest #3: ";

        int initialHunger = test.getHunger();

        test.PassTime();

        int nextHunger = test.getHunger();

        if(nextHunger==(initialHunger-1))
        {
            cout << "successful";
        }
        else
        {
            cout << "failed"
                 << "\nExpected: Hunger = " << initialHunger
                 << "\nResults: Hunger = " << nextHunger;
        }

        // testing completed
        cout << "\nPleyo class testing completed..."
             << "\n-------------------------------------";
    }

    friend ostream& operator<<(ostream& os, Pleyo obj);
};

ostream& operator<<(ostream&os, Pleyo obj)
{
    os << "\n" << obj.name << " the " << obj.species
       << "\nHunger Lvl: " << obj.hunger
       << "\nBoredom Lvl: " << obj.boredom;
    return os;
}

// end of Specification A3 - Second Child Class

/***********************************************
 * END OF PLEYO CLASS - CHILD OF CREATURE CLASS
***********************************************/


/***********************************************
 * ANGAN CLASS - CHILD OF CREATURE CLASS
***********************************************/

// irritable creature that prioritizes food
class Angan : public Creature
{

    private:

    public:

    // default constructor
    Angan()
    {
        name = "Angan";
        species = "Angan";
        horns = 2;
    }

    // copy constructor (copies Creature into Norma)
    Angan(Creature* c)
    {
        // generates random num between 0-5
        hunger = RandomNumber(1,4);
        boredom = RandomNumber(1,4);

        // traits initialization
        eyes = c->getEyes();
        tails = c->getTails();
        horns = c->getHorns();

        name = c->getName();
        species = c->getSpecies();

        dead = false;
    }

    void Feed()
    {
        hunger += RandomNumber(4,5);
        cout << "\n*chomp* It's good food.";
    }

    void Play()
    {
        if(hunger<10)
        {
            cout << "\n...Food first. *snarl*";
        }
        else
        {
            boredom -= RandomNumber(5,7);
            cout << "\nI feel strong!";
        }
    }

    void Data()
    {
        cout << "\nThis is a very irritable creature."
             << "\nVery agressive and headstrong,"
                "it will be difficult to play with it "
                "\nif it's hungry.";
    }

        // returns a creature ptr to be transformed into creature
    Creature* operator+(Creature* obj)
    {
        Creature* c;

        // Norma + Norma
        if(obj->getSpecies()=="Angan")
        {
            *c = *obj;
        }

        if(obj->getSpecies()=="Norma" || obj->getSpecies()=="Pleyo")
        {
            // copies everything first
            *c = *obj;

            // combines both traits
            c -> setEyes(eyes + (obj->getEyes()));
            c -> setTails(tails + (obj->getTails()));
            c -> setHorns(horns + (obj->getHorns()));

            // Norma + Pleyo
            if(obj->getSpecies()=="Norma")
                c -> setName("Norma");

            // Norma + Angan
            if(obj->getSpecies()=="Pleyo")
                c -> setName("Pleyo");
        }

        return c;
    }

    Angan operator=(Norma c)
    {
        Angan obj;

        // generates random num between 0-5
        obj.setHunger(RandomNumber(1,4));
        obj.setBoredom(RandomNumber(1,4));

        // traits initialization
        obj.setEyes(c.getEyes());
        obj.setTails(c.getTails());
        obj.setHorns(c.getHorns());

        obj.setName(c.getName());
        obj.setSpecies(c.getSpecies());

        obj.setDead(false);

        return obj;
    }  

    Angan operator=(Creature* c)
    {
        Angan obj;

        // generates random num between 0-5
        obj.setHunger(RandomNumber(1,4));
        obj.setBoredom(RandomNumber(1,4));

        // traits initialization
        obj.setEyes(c->getEyes());
        obj.setTails(c->getTails());
        obj.setHorns(c->getHorns());

        obj.setName(c->getName());
        obj.setSpecies(c->getSpecies());

        obj.setDead(false);

        return obj;
    }    


    void ComponentTest()
    {
        Angan test;
        cout << "\n-------------------------------------"
             << "\nCommencing Angan class testing...";

        // tests basic initialization     
        cout << "\nTest #1: ";

        if(test.getName()=="Angan"&&test.getSpecies()=="Angan")
        {
            cout << "successful";
        }
        else
        {
            cout << "failed"
                 << "\nExpected: Name = Angan, Species = Angan"
                 << "\nResults: Name = " << test.getName()
                 << ", Species = " << test.getSpecies();
        }

        // tests changing information
        cout << "\nTest #2: ";

        test.setName("Test Name");
        test.setSpecies("Test Species");

        if(test.getName()=="Test Name"&&test.getSpecies()=="Test Species")
        {
            cout << "successful";
        }
        else
        {
            cout << "failed"
                 << "\nExpected: Name = Test Name, Species = Test Species"
                 << "\nResults: Name = " << test.getName()
                 << ", Species = " << test.getSpecies();
        }

        // tests PassTime() which has lambda function
        cout << "\nTest #3: ";

        int initialHunger = test.getHunger();

        test.PassTime();

        int nextHunger = test.getHunger();

        if(nextHunger==(initialHunger-1))
        {
            cout << "successful";
        }
        else
        {
            cout << "failed"
                 << "\nExpected: Hunger = " << initialHunger
                 << "\nResults: Hunger = " << nextHunger;
        }

        // testing completed
        cout << "\nAngan class testing completed..."
             << "\n-------------------------------------";
    }

    friend ostream& operator<<(ostream& os, Angan obj);
};

ostream& operator<<(ostream&os, Angan obj)
{
    os << "\n" << obj.name << " the " << obj.species
       << "\nHunger Lvl: " << obj.hunger
       << "\nBoredom Lvl: " << obj.boredom;
    return os;
}

/***********************************************
 * END OF ANGAN CLASS - CHILD OF CREATURE CLASS
***********************************************/

// TRANSFORMATION FUNCTIONS
Norma makeNormaCreature(Creature* c)
{
    Norma n;
    n = c;
    return n;
}

Pleyo makePleyoCreature(Creature* c)
{
    Pleyo p;
    p = c;
    return p;
}

Angan makeAnganCreature(Creature* c)
{
    Angan a;
    a = c;
    return a;
}

// Prototypes
void ProgramGreeting();
void UnitTest();
int menu(DynamicArray<Creature*>&);
void PassTime(DynamicArray<Creature*>&);
void deathCheck(DynamicArray<Creature*>&);
string evolution(string,string);
void breed(DynamicArray<Creature*>&,Creature*);


/************
 * MAIN
************/


int main()
{
    // random seed for RNG
    srand(time(0));

    // Program Greeting
    ProgramGreeting();

    // testing all classes
    UnitTest();

    // make array Hokeemon
    DynamicArray<Creature*>arr;

    Creature* cptr;

    Norma hokee1;
    Pleyo hokee2;
    Angan hokee3;

    cptr = &hokee1;
    arr.addEnd(cptr);

    cptr = &hokee2;
    arr.addEnd(cptr);

    cptr = &hokee3;
    arr.addEnd(cptr);

    int playGame = menu(arr);

    if(playGame==0)
    {
        cout << "\n\n------------------------------------------"
             << "\nThank you for playing Hokeemon!"
             << "\nSee you again!" << std::endl;
    }
}


/************
 * END OF MAIN
************/

// Specification C3 - Validate Input

// helper function to validate action on Hokeemon in menu()
bool validAction(string choice)
{
    // if user inputted in correct menu letter
    if(choice.length()==1 &&
       (choice == "a"|| choice == "A" ||
       choice == "d" || choice == "D" ||
       choice == "n" || choice == "N" ||
       choice == "l" || choice == "L" ||
       choice == "f" || choice == "F" ||
       choice == "p" || choice == "P" ||
       choice == "b" || choice == "B"))
       return true;
    // else, it is invalid
    return false;
}


// helper function to validate input in menu()
// returns -1 if invalid, returns index of hokeemon in arr
int validChoice(DynamicArray<Creature*>&arr, string choice)
{
    bool found = false;
    int ind;

    // parses through array to see if the choice is the
    // same as Hokeemon name
    for(int i = 0; i<arr.getLength(); i++)
    {
        if(arr.getElem(i)->getName()==choice)
            {
                found = true;
                ind = i;
            }
    }

    if(found == false)
        return -1;
    return ind;
}

// end of Specification C3 - Validate Input

// helper function to print out Hokeemon in menu()
void printHokeemon(DynamicArray<Creature*>&arr)
{
    for(int i = 0; i<arr.getLength(); i++)
    {
        // prints name of Hokeemon in array
        cout << "\n" << arr.getElem(i)->getName();
    }
    cout << "\n";
}

// pick Hokeemon, then you can:
// Appearance, Data, Name, Listen, Feed, Play, Breed, Quit
// returns 1 if game continues, 0 if quit
int menu(DynamicArray<Creature*>&arr)
{
    // loops entire game until it returns
    while(1==1)
    {
    string choice; // the user's input into menu

    // if all creatures dead, end game
    if(arr.getLength()==0)
        return 0;

    // initial print out of menu
    cout << "\n------------------------------------------"
         << "\nThese are your Hokeemon:";
    // prints out Hokeemon names
    printHokeemon(arr);
    cout << "\nEnter in the Hokeemon you want to interact with"
         << "\nor type \"Q\" to quit: ";
    getline(std::cin,choice);

    // checks if user wants to quit, plays game if not
    if(choice == "Q"||choice == "q")
        return 0;

    // index of hokeemon
    int index = validChoice(arr,choice);

    // repeats menu if invalid choice
    while(index == -1)
    {
        cout << "\n------------------------------------------"
             << "\nERROR: Invalid input"
             << "\nThese are your Hokeemon:";
        // prints out Hokeemon names
        printHokeemon(arr);
        cout << "\nEnter in the Hokeemon you want to interact with"
             << "\nor type \"Q\" to quit: ";
        getline(std::cin,choice);

        // checks if user wants to quit, plays game if not
        if(choice == "Q"||choice == "q")
            return 0;

        // index of hokeemon
        index = validChoice(arr,choice);
    }

    // at this point, user wants to play game

    string action; // user's action with Hokeemon

    cout << "\n\nWhat do you want to do with " << choice << "?"
         << "\nA. Appearance"
         << "\nD. Data"
         << "\nN. Name"
         << "\nL. Listen"
         << "\nF. Feed"
         << "\nP. Play"
         //<< "\nB. Breed"
         << std::endl;
    getline(std::cin, action);

    while(!validAction(action))
    {
        cout<< "\nERROR: Invalid input"
            << "\n\nWhat do you want to do with " << choice << "?"
            << "\nA. Appearance"
            << "\nD. Data"
            << "\nN. Name"
            << "\nL. Listen"
            << "\nF. Feed"
            << "\nP. Play"
            //<< "\nB. Breed"
            << std::endl;
            getline(std::cin, action);
    }

    // at this point, user will have chosen an action to do with Hokeemon

    // runs Appearance code
    if(action == "a"|| action == "A")
    {
        arr.getElem(index)->Appearance();
    }

    // runs Data code
    if(action == "d" || action == "D")
    {
        arr.getElem(index)->Data();
    }

    // runs Name code
    if(action == "n" || action == "N")
    {
        string name;

        cout << "\nEnter the name of your Hokeemon: ";

        getline(std::cin, name);

        arr.getElem(index)->setName(name);
    }

    // runs Listen code
    if(action == "l" || action == "L")
    {
        arr.getElem(index)->Listen();
    }

    // runs Feed code
    if(action == "f" || action == "F")
    {
        arr.getElem(index)->Feed();
    }

    // runs Play code
    if(action == "p" || action == "P")
    {
        arr.getElem(index)->Play();
    }

    // runs Breed code
    if(action == "b" || action == "B")
    {
        breed(arr,arr.getElem(index));
    }

    // runs PassTime() and deathCheck()
    if(action == "l" || action == "L" ||
       action == "f" || action == "F" ||
       action == "p" || action == "P" ||
       action == "b" || action == "B")
       {
           PassTime(arr);
           deathCheck(arr);
       }
    } // end of while loop
}

void ProgramGreeting()
{
    cout << "\n-------------------------------------------------------"
         << "\nHello! Welcome to Hokeemon!"
         << "\nWith Hokeemon, you can interact and care"
         << "\nfor your magical creatures."
         << "\nInstructions: \nBe wary, if you Feed, Play, or Listen, "
            "\ntime passes"
            "\nDon't let Hunger go to 0! "
            "\nYour Hokeemon will die if you do!"
         << "\nDon't let Boredom go past 20!"
         << "\nYour Hokeemon won't talk to you if they're bored."
         << "\n-------------------------------------------------------";
}

// tests Norma, Pleyo, Angan, DynamicArray
void UnitTest()
{
    DynamicArray<int> test;

    test.ComponentTest();

    Norma normaTest;

    normaTest.ComponentTest();

    Pleyo pleyoTest;

    pleyoTest.ComponentTest();

    Angan anganTest;

    anganTest.ComponentTest();
}

// will breed a new Hokeemon
void breed(DynamicArray<Creature*>&arr, Creature* h1)
{
    string choice; // user input

    // prompting user to input breeding partner
    cout << "\nWho will " 
         << h1->getName() 
         << " breed with?";
    getline(std::cin, choice);

    // index = partner
    int index = validChoice(arr, choice);

    // if input is invalid
    while(index==-1)
    {
        cout << "\nERROR: Invalid input"
             << "\nWho will " 
             << h1->getName() 
             << " breed with?\n";
             getline(std::cin, choice);
             index = validChoice(arr, choice);
    }

    // at this point, the breeding shall commence

    // initilizes partner
    Creature* h2 = arr.getElem(index);

    // initializes child
    Norma child;

    // if different species
    if(h1->getSpecies()!=h2->getSpecies())
    {
        child.setEyes(h1->getEyes()+h2->getEyes());
        child.setTails(h1->getTails()+h2->getTails());
        child.setHorns(h1->getHorns()+h2->getHorns());
    }

    // if same species
    else
    {
        child.setEyes(h1->getEyes());
        child.setTails(h1->getTails());
        child.setHorns(h1->getHorns());
    }

    child.setName("Child of "+h1->getName()+" and "+h2->getName());

    // decides child's species
    string species = evolution(h1->getName(),h2->getName());
    
    //Creature* childptr = child.get();

    if(species=="Norma")
    {
        Norma n;
        n = child;
        //cout << n;
        //n = makeNormaCreature(child);
        arr.addEnd(&n);
    }

    if(species=="Pleyo")
    {
        Pleyo p;
        p = child;
        //cout << p;
        //p = makePleyoCreature(child);
        arr.addEnd(&p);
        //cout << p.getName();
        //cout << arr.getElem(3)->getName();
    }

    if(species=="Angan")
    {
        Angan a;
        a = child;
        //a = makeAnganCreature(child);
        arr.addEnd(&a);
    }
}

// general PassTime() that applies to all creatures
// will be called after Listen(), Play(), Feed(), or Breed()
void PassTime(DynamicArray<Creature*>&arr)
{
    for(int i = 0; i<arr.getLength(); i++)
    {
        arr.getElem(i)->PassTime();
    }
}

// parses through all creatures, checking if they're dead
// if dead, will announce it's dead and removes it from array
void deathCheck(DynamicArray<Creature*>&arr)
{
    for(int i = 0; i<arr.getLength(); i++)
    {
        if(arr.getElem(i)->getDead()==true)
        {
            cout << std::endl << arr.getElem(i)->getName() 
                 << " has DIED!";
            arr.subtractAt(i);
        }
    }
}

// helper function for breed()
// decides which species a child will be
// returns the species via string
string evolution(string parent1, string parent2)
{
    // norma and pleyo = pleyo
    if((parent1=="Norma"&&parent2=="Pleyo") ||
        (parent1=="Pleyo"&&parent2=="Norma"))
    {
        return "Pleyo";
    }

    // norma and angan = norma
    if((parent1=="Norma"&&parent2=="Angan") ||
        (parent1=="Angan"&&parent2=="Norma"))
    {
        return "Norma";
    }

    // pleyo and angan = norma
    if((parent1=="Angan"&&parent2=="Pleyo") ||
        (parent1=="Pleyo"&&parent2=="Angan"))
    {
        return "Norma";
    }

    // if same species parents, return same species
    return parent1;
}