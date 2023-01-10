// Function: a simple AI where the robot (H) renews its energy with batteries (0)
// Note: attributes of robot are randomized, but the best performing robots pass their
// "genes" to the next generation
// 
// final.cpp
// Luke Villanueva, CISP 400
// 5/17/21


#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using std::cout;
using std::string;
using std::ostream;
using namespace std::this_thread;
using namespace std::chrono;


// RNG >= lo and <= hi; lo and hi are > 0 
// NOTE: srand(time(0))
int RandomNumber(int lo, int hi)
{
    // Return invalid if: hi<lo, lo<1, or hi>100
    try
    {
        if(hi<lo || hi<1)
            throw (hi);
        else if(lo<0)
            throw (lo);
    }

    catch(int n)
        {
            cout << "ERROR: Invalid inputs for RandomNumber"
             << ". Returning -1...";
            return -1;
        }

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

    // switch elems at two given indices
    void switchElems(int ind1, int ind2)
    {
        type temp = listPtr[ind1];

        listPtr[ind1] = listPtr[ind2];

        listPtr[ind2] = temp;
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


// enumeration of grid for the Map
// Represents the states of the grid space
enum grid { SPACE, WALL, BATTERY, ROBOT};

// helper for Map
// randomizer to pick a grid state: space or battery
// from 1-100; if num <= 40, make battery
// returns grid state
grid rollGridState()
{
    int num = RandomNumber(1,100);

    // rolled battery
    if(num <= 40)
        return BATTERY;

    // rolled space
    return SPACE;
}

// helper for Map
// RNG for gene state
grid rollGene()
{
    int num = RandomNumber(0,2);

    if(num == SPACE)
        return SPACE;
    if(num == WALL)
        return WALL;
    else
        return BATTERY;
}

// enumeration of grid for Robots
enum direction { NORTH, EAST, SOUTH, WEST };

// randomizer to pick a direction
direction rollDirection()
{
    int num = RandomNumber(0,3);

    // rolled north
    if(num == 0)
        return NORTH;

    // rolled east
    else if(num == 1)
        return EAST;

    // rolled south
    else if(num == 2)
        return SOUTH;

    // rolled west
    else
        return WEST;
}


// Map class - uses grid data type
// makes a map of 40x50
class Map
{

    private:
    grid** arrPtr;
    int row, col;

    public:

    // default constructor
    Map()
    {
        // dimensions excluding outer walls
        row = 11;
        col = 11;

        // creates ptr to pointers
        arrPtr = new grid*[row];
        for(int i = 0; i<row; i++)
        {
            // creates arrays for each pointers
            // making a 2d array dynamically
            arrPtr[i] = new grid[col];
        }
        

        // fill up map with spaces and walls
        for(int i = 0; i<row; i++)
        {
            for(int j = 0; j<col; j++)
            {

                // makes walls if ends of map
                if(j==0 || j==col-1 || i==0 || i==row-1)
                {
                    arrPtr[i][j]=WALL;
                }
                else
                {
                    arrPtr[i][j]=SPACE;
                }

            }
        }



    }

    // destructor
    ~Map()
    {
        for(int i = 0; i<row; i++)
        {
            // deleting each 2d array
            delete [] arrPtr[i];
            arrPtr[i] = nullptr;
        }

        // deleting entire array
        delete [] arrPtr;
        arrPtr = nullptr;
    }

    // spawn Batteries at a rate
    // batteries don't spawn next to each other
    void spawnBatteries()
    {
        int batteryRate = 20;
        //int wallRate = 10;

        for(int i = 1; i<row-1; i++)
        {
            for(int j = 1; j<col-1; j++)
            {
                if(RandomNumber(1,100)<=batteryRate)
                {
                    arrPtr[i][j] = BATTERY;
                    // if not @ end of map
                    if(j!=col-2)
                        j++;
                }

                /**
                // spawns walls
                if(RandomNumber(1,100)<=wallRate)
                {
                    arrPtr[i][j]=WALL;
                }
                **/
            }
        }

    }

    // clears all of map within boundaries 
    void clearMap()
    {
        for(int i = 1; i<row-1; i++)
        {
            for(int j = 1; j<col-1; j++)
            {
                arrPtr[i][j]=SPACE;
            }
        }
    }

    // get state of grid
    grid gridState(int row, int col)
    {
        try
        {
            return arrPtr[row][col];
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    int getRow()
    {return row;}

    int getCol()
    {return col;}

    grid** getGridPtr()
    {return arrPtr;}

};


/*********************
 * ROBOT CLASS 
*********************/
//! Remember to set the Map and spawn the Robots
class Robot
{

    protected:
    int energy, maxEnergy, turnsAlive, row, col, 
        genes, directions; // robot data
    bool alive;
    double fitness;
    int north, south, east, west; // robot's sensors
    //? j1 = north, j2 = south, j3 = east, j4 = west

    // concept: each i is a direction, i has j's for sensors
    int** geneArr; // gene 2d array
    direction* directionArr; // corresponding direction,array for genePtr
    // map pointer
    Map* map;

    // param: ID of gene strain needing to check
    bool isUniqueGene(int gene)
    {
        // check if repeats; if yes, reroll
        // parses thru all genes except most recent one
        // i is gene, j is direction in gene
        for(int i = 0; i<gene; i++)
        {
            int matches = 0;

            for(int j = 0; j<directions; j++)
            {
                // if any gene is the same as the 
                // current one, have to reroll
            
                if(geneArr[i][j]==geneArr[gene][j])
                    matches++;
            }

            // if all match, it is same gene
            if(matches==directions)
                return false;
        }

        // else, it is unique
        return true;

    }

    public:

    // default constructor
    Robot()
    {
        alive = true;

        energy = 5;
        maxEnergy = 0;
        fitness = 0;

        genes = 16;
        directions = 4;

        turnsAlive = 0;

        // declaring and prepping gene 2d array
        geneArr = new int*[genes];
        for(int i = 0; i<genes; i++)
        {
            geneArr[i] = new int[directions];
        }

        // declaring and prepping direction array
        directionArr = new direction[genes];

        // initializing random genes
        // goes thru all genes and rolls genes

        // start off with initial gene
        for(int j = 0; j<directions; j++)
        {
            int num = RandomNumber(0,2);
            geneArr[0][j] = num;
        }
        // initializing rest of the genes from 2nd index
        for(int i = 1; i<genes; i++)
        {
            do
            {
                for(int j = 0; j<directions; j++)
                {
                    int num = RandomNumber(0,2);
                    geneArr[i][j] = num;
                }
            } while (!isUniqueGene(i));
            // rerolls if it's not unique
        }

        //initializing random directions
        for(int i = 0; i<genes; i++)
        {
            directionArr[i] = rollDirection();
        }

    }

    // destructor
    ~Robot()
    {
        for(int i = 0; i<directions; i++)
        {
            delete geneArr[i];
            geneArr[i] = nullptr;
        }

        delete [] geneArr;
        geneArr = nullptr;
    }

    // copy constructor
    Robot(Robot &obj)
    {
        // It's alive I hope
        alive = obj.alive;

        energy = obj.energy;

        fitness = obj.fitness;

        maxEnergy = obj.maxEnergy;

        turnsAlive = obj.turnsAlive;

        // copies map ptr
        map = obj.map;

        // copies # of genes
        genes = obj.genes;

        // copies # of directions
        directions = obj.directions;

        // makes new geneArr and copies each gene
        geneArr = new int*[genes];
        for(int i = 0; i<genes; i++)
        {
            geneArr[i] = new int[directions];
        }
        // copying...
        for(int i = 0; i<genes; i++)
        {
            for(int j = 0; j<directions; j++)
            {
                geneArr[i][j] = obj.geneArr[i][j];
            }
        }
        
        // makes new directionARR and copies each direction
        directionArr = new direction[genes];
        for(int i = 0; i<genes; i++)
        {
            directionArr[i]=obj.directionArr[i];
        }

        row = obj.row;

        col = obj.col;

    }


    // move
    void move()
    {
        int buffer = 1;

        // Robot moves if alive
        if(alive == true)
        {
            // the gene that matches sensors
            int matchingGene;
            bool matched = false;
    
            for(int i = 0; i<genes; i++)
            {
                int matches = 0;
    
                if(north == geneArr[i][0])
                {
                    matches++;
    
                    if(south == geneArr[i][1])
                        matches++;
    
                    if(east == geneArr[i][2])
                        matches++;
    
                    if(west == geneArr[i][3])
                        matches++;
                }
    
                // if all directions match the sensors,
                // found the gene
                if(matches==directions)
                {
                    matchingGene = i;
                    matched = true;
                    break;
                }
            }
    
            direction action;
    
            // Robot knows what to do
            if(matched==true)
                action = directionArr[matchingGene];
    
            // if matched false, do last gene
            if(matched==false)
                action = directionArr[genes-1];
    
            // move up
            if(action==NORTH)
            {
                // move away from wall
                if(north==WALL)
                    row+=buffer;
    
                // move up
                else
                row--;
            }
            // move down
            else if(action==SOUTH)
            {
                // move away from wall
                if(south==WALL)
                    row-=buffer;
                        
                // move down
                else
                row++;
            }
            // move right
            else if(action==EAST)
            {
                // move away from wall
                if(east==WALL)
                    col-=buffer;
    
                // move right
                else
                col++;
            }
            // move left
            else if(action==WEST)
            {
                // move away from wall 
                if (west==WALL)
                    col+=buffer;
    
                // move left
                else
                col--;
            }
    
    
            // robot has moved, used energy
            energy--;
    

            // moves robot if on a wall
            if(row >= map->getRow()-1)
                row-=buffer;
            else if(row <= 0)
                row+=buffer;
            else if(col >= map->getCol()-1)
                col-=buffer;
            else if(col <= 0)
                col+=buffer;
    

            // grid status checks
            // if Robot is ON TOP OF Battery, add to energy
            // also, move to 1 to random direction
            if(map->gridState(row,col)==BATTERY)
            {
                energy+=5;
                maxEnergy+=5;

                // move because Robot is on battery
                // SHARING IS CARING
                scan();
                if(north==WALL)
                    row+=buffer;
                else if(south==WALL)
                    row-=buffer;
                else if(east==WALL)
                    col-=buffer;
                else if (west==WALL)
                    col+=buffer;
                else
                {
                    direction tempDir = rollDirection();
                    if(tempDir==NORTH)
                        row--;
                    else if(tempDir==SOUTH)
                        row++;
                    else if(tempDir==EAST)
                        row++;
                    else if(tempDir==WEST)
                        row--;
                }
            }

            // if Robot used all energy, it's dead
            if(energy<=0)
                alive = false;

            // end robot's turn
            turnsAlive++;
        }
    }

    // gets grid space info from surroundings
    void scan()
    {
        north = map->gridState(row-1,col);
        south = map->gridState(row+1,col);
        east = map->gridState(row,col+1);
        west = map->gridState(row,col-1);
    }

    // returns life state of robot
    bool isAlive()
    {return alive;}

    void setMapPtr(Map* m)
    {map = m;}

    void setAlive(bool b)
    {alive = b;}

    void setEnergy(int n)
    {energy = n;}

    // param: dimensions of grid
    void spawn(int x, int y)
    {
        int buffer = 2;
        // initializing random position on grid
        // based on rowxcol grid
        // repeats if space taken
        do
        { 
            row = RandomNumber(buffer, x-buffer);
            col = RandomNumber(buffer, y-buffer);
        } while (!isGridFree(row,col));
    }

    double getFitness()
    {return fitness;}

    int getEnergy()
    {return energy;}

    int getRow()
    {return row;}

    int getCol()
    {return col;}

    int getNumOfGenes()
    {return genes;}

    int getNumofDirections()
    {return directions;}

    int** getGenePtr()
    {return geneArr;}

    direction* getDirectionArr()
    {return directionArr;}

    Map* getMapPtr()
    {return map;}

    int getTurns()
    {return turnsAlive;}

    // calculates fitness score of robot out of 100
    void calcFitness()
    {
        fitness = (((double)maxEnergy)/(turnsAlive*5))*100;
    }

    // helper for Robot - helps spawnpoint
    // checking if grid space is taken
    bool isGridFree(int row, int col)
    {
        // if it's a space, it's free
        if(map->gridState(row,col)==SPACE)
            return true;
        
        // if not, then it's not free
        return false;
    }

    // assignment operator overload
    // copies over data to current obj and returns obj
    Robot& operator=(Robot& obj)
    {
        // It's alive I hope
        alive = obj.alive;

        energy = obj.energy;

        fitness = obj.fitness;

        maxEnergy = obj.maxEnergy;

        turnsAlive = obj.turnsAlive;

        // copies map ptr
        map = obj.map;

        // copies # of genes
        genes = obj.genes;

        // copies # of directions
        directions = obj.directions;

        // makes new geneArr and copies each gene
        geneArr = new int*[genes];
        for(int i = 0; i<genes; i++)
        {
            geneArr[i] = new int[directions];
        }
        // copying...
        for(int i = 0; i<genes; i++)
        {
            for(int j = 0; j<directions; j++)
            {
                geneArr[i][j] = obj.geneArr[i][j];
            }
        }
        
        // makes new directionARR and copies each direction
        directionArr = new direction[genes];
        for(int i = 0; i<genes; i++)
        {
            directionArr[i]=obj.directionArr[i];
        }

        row = obj.row;

        col = obj.col;

        return *this;
    }

};


/*********************
 * END OF ROBOT CLASS 
*********************/


// helper for breed()
// randomly mutates genes of Robot
// param: Robot child, mutation rate
//! Note: input rate as INTEGER
void mutate(Robot& child,int rate)
{
    int mutations = (int)(((double)rate/100)*child.getNumOfGenes()+1);

    for(int i = 0; i<mutations; i++)
    {
        int targetGene = RandomNumber(0,child.getNumOfGenes()-1);

        //mutate all details in gene
        for(int j = 0; j<child.getNumofDirections(); j++)
        {
            child.getGenePtr()[targetGene][j] = RandomNumber(0,3);
        }
        //mutate direction of gene
        child.getDirectionArr()[targetGene] = rollDirection();
    }
}


// Robot Functions

void breed(Robot& child, Robot& r1, Robot& r2)
{
    for(int i = 0; i<child.getNumOfGenes(); i++)
    {
        for(int j = 0; j<child.getNumofDirections(); j++)
        {
            // every 0 or even gene, get from Father
            if(i==0 || i%2==0)
            {
                child.getGenePtr()[i][j]=r1.getGenePtr()[i][j];
                child.getDirectionArr()[i]=r1.getDirectionArr()[i];
            }
    
            // every odd gene, get from Mother
            else
            {
                child.getGenePtr()[i][j]=r2.getGenePtr()[i][j];
                child.getDirectionArr()[i]=r2.getDirectionArr()[i];
            }
        }
    }

    mutate(child,5);
}

// End of Robot Functions 


// Map Functions - Using Robots

// helper for display()
// find Robot in array given position on map
// returns index of robot in DynamicArray, given coords on map
int indOfRobotAt(int row, int col, DynamicArray<Robot>&arr)
{
    // parse thru arr, find robot with same coords
    // return index of found robot
    for(int i = 0; i<arr.getLength(); i++)
    {
        if(arr.getElem(i).getRow()==row &&
           arr.getElem(i).getCol()==col)
           return i;
    }

    // if not found, return -1
    return -1;
}


// updating grid objs on Map with Robots' data
// param: Map ptr, DynamicArray of robots, index of Robot
void updateMap(Map* map,DynamicArray<Robot>&RobotArr, int ind)
{
    grid** mapPtr = map->getGridPtr();

    // cleans Robots from map
    for(int i = 1; i<map->getRow()-1; i++)
    {
        for(int j = 1; j<map->getCol()-1; j++)
        {
            if(mapPtr[i][j] == ROBOT)
                mapPtr[i][j]=SPACE;
        }
    }

    // updates Robot's location
    int row = RobotArr.getElem(ind).getRow();
    int col = RobotArr.getElem(ind).getCol();

    mapPtr[row][col] = ROBOT;

}



// displays map
// map, robot arr, index of displayed robot
void display(Map* map, DynamicArray<Robot>&RobotArr, int ind)
{
    cout << "\nRobot Energy: " << RobotArr.getElem(ind).getEnergy();

    int row = map->getRow();
    int col = map->getCol();

    grid** arrPtr = map->getGridPtr();

    // map spacing
    cout << "\n\n";

    for(int i = 0; i<row; i++)
    {
        for(int j = 0; j<col; j++)
        {

            // space grid
            if(arrPtr[i][j]==SPACE)
            {
                cout << " ";
            }

            // wall grid
            else if(arrPtr[i][j]==WALL)
            {
            // left border for wall
            // makes vertical wall
                if(j==0)
                {
                    cout << "|";
                }

                // right border for wall
                // makes vertical wall and moves next line
                else if(j==col-1)
                {
                    cout << "|" << "\n";
                }

                // rest of the wall
                else
                {
                    cout << "_";
                }
            }

            // robot grid
            else if(arrPtr[i][j]==ROBOT) // && RobotArr.getElem(indOfRobotAt(i,j,RobotArr)).isAlive())
            {
                    cout << "H";
            }

            // battery grid
            else if(arrPtr[i][j]==BATTERY)
            {
                cout << "O";
            }

            else
                cout << " ";

        }
    }

    // map spacing
    cout << "\n\n";

}

// End of Map Functions - Using Robots



// Functions Prototypes
void ProgramGreeting();
int endOfGen(DynamicArray<Robot>&, milliseconds, int);
bool allDead(DynamicArray<Robot>&);
void showBest(DynamicArray<Robot>&, milliseconds);
void getMostTurns(DynamicArray<Robot>&, int&);


// every turn, robots breed
// every generation is every 100 turns
int main()
{
    // seed RNG
    srand(time(0));
    // how fast simulation is
    auto speed = milliseconds(500);
    // initial population amount
    int initPop = 200;
    // max amount of turns per generation
    int maxTurns = 50;
    //turns
    int turns = 0;
    // generation counter
    int generation = 1;
    // highest amount of turns survived out of all bots
    int highestTurns = 0;

    ProgramGreeting();

    // SETUP SIMULATION

    // make arr for Robots and Map
    // arr for Robots in current generation
    DynamicArray<Robot>RobotArr;

    // add 200 robots onto array (all robots in generation)
    // initial population of 200 Robots
    for(int i = 0; i<initPop; i++)
    {
        Robot* robot = new Robot;
        RobotArr.addEnd(*robot);
    }

    // assigns all robots to their map; spawns all robots on their map
    for(int i = 0; i<RobotArr.getLength(); i++)
    {
        // make new map
        Map* map = new Map;
        map->spawnBatteries();
        // assign map
        RobotArr.getElem(i).setMapPtr(map);
        RobotArr.getElem(i).spawn(map->getRow(),map->getCol());
    }

    // END SETUP SIMULATION

    int choice;

    do
    {
        // while all have energy, make robots move
        while(!allDead(RobotArr) && turns<=maxTurns)
        {  
            for(int i = 0; i<RobotArr.getLength(); i++)
            {
                RobotArr.getElem(i).scan();
                RobotArr.getElem(i).move();
            }
            turns++;
        }

        // updates mostTurns
        for(int i = 0; i<RobotArr.getLength(); i++)
        {
            getMostTurns(RobotArr,highestTurns);
        }

        choice = endOfGen(RobotArr, speed, generation);
        generation++;
        turns = 0;
    } while(choice==1);
    
    cout << "\n\nMost Turns (# of times Robot moved) Surivived for One Robot: " <<highestTurns;

    cout << "\n\nEnding Program...\n";
    return 0;
}

// Program Greeting
void ProgramGreeting()
{
    cout << "\nWelcome to the Robot Evolution Simulator!"
         << "\nNote: Try not to scroll!"
            "\nThe Robots are 'H' and Batteries are 'O'"
            "\nProgram will load in a few seconds..."
         << "\n";
    sleep_for(seconds(3));
}

// parses through Robots and gets highest turn out of all them
void getMostTurns(DynamicArray<Robot>&arr, int &mostTurns)
{
    for(int i = 0; i<arr.getLength(); i++)
    {
        if(arr.getElem(i).getTurns()>mostTurns)
            mostTurns=arr.getElem(i).getTurns();
    }
}

bool allDead(DynamicArray<Robot>&arr)
{
    for(int i = 0; i<arr.getLength(); i++)
    {
        // if one is alive, then not all are dead
        if(arr.getElem(i).isAlive()==true)
            return false;
    }
    return true;
}

// helper function
// sorts Robots by fitness score
void sortByFitness(DynamicArray<Robot>&arr)
{
    bool sorted = false;
    while(sorted==false)
    {
        sorted = true;
        // from first to second to last
        // (prevents out of bounds error)
        for(int i = 0; i<arr.getLength()-1; i++)
        {
            if(arr.getElem(i).getFitness()>
               arr.getElem(i+1).getFitness())
               {
                   arr.switchElems(i,i+1);
                   sorted = false;
               }
        }
    }
}

//! summarizes generation data; calcs/averages fitness
// makes new generation and culls bottom 50%
int endOfGen(DynamicArray<Robot>&arr, milliseconds speed, int generation)
{
    double total = 0;
    string s = "";

    for(int i = 0; i<arr.getLength(); i++)
    {
        arr.getElem(i).calcFitness();
        total+=arr.getElem(i).getFitness();
    }

    // sorts Robots from lowest fitness to highest
    sortByFitness(arr);

    // showcase the best
    showBest(arr, speed);

    // prep for next generation
    cout << "\nGeneration #"<<generation<<"'s Fitness score: "
         <<(total/arr.getLength())<<" out of 100";

    cout << "\nEnter Q if you want to exit..."
         << "\nPress Enter to continue to the next generation...";
    std::getline(std::cin,s);

    if(s=="Q"||s=="q")
        return 0;

    // cull the bottom 50%

    // get pop count of half
    int finalPop = arr.getLength()/2;
    // add 1 if odd population
    if(finalPop%2!=0)
        finalPop++;

    // remove bottom 50% of Pop, leaving finalPop of Robots
    for(int i = 0; i<arr.getLength()-finalPop; i++)
        arr.subtractStart();

    // breed new generation

    // from first to 2nd to last
    // (based on duos)
    for(int i = 0; i<finalPop-1; i+=2)
    {

            Robot* child = new Robot;
            Map* newMap = new Map;
            breed(*child,arr.getElem(i),arr.getElem(i+1));
            child->setMapPtr(newMap);
            child->spawn(child->getMapPtr()->getRow(),child->getMapPtr()->getCol());
            arr.addStart(*child);
    }

    // resetting all population
    for(int i = 0; i<arr.getLength(); i++)
    {
        arr.getElem(i).setEnergy(5);
        arr.getElem(i).setAlive(true);
        arr.getElem(i).getMapPtr()->clearMap();
        arr.getElem(i).getMapPtr()->spawnBatteries();
    }

    cout << "\nNext Generation's Simulation will begin in a few seconds..."
         << "\n";
    sleep_for(seconds(2));

    return 1;
}

// ASSUMES: arr is already sorted from worst to best
// doesn't change the data of the robot, just showcases it
void showBest(DynamicArray<Robot>&arr, milliseconds speed)
{

    int ind = (arr.getLength()-1);

    Map* map = arr.getElem(ind).getMapPtr();

    int row = map->getRow();

    int col = map->getCol();

    // spawn Robot
    arr.getElem(ind).spawn(row,col);

    // set energy of robot
    arr.getElem(ind).setEnergy(5);

    // turn on robot
    arr.getElem(ind).setAlive(true);

    // while robot alive
    //!NOTE: Constant max turns
    for(int i = 0; (arr.getElem(ind).getEnergy()>0 && i<10); i++)
    {
        // turn count
        cout << "\nMove #"<<i+1; 

        // show grid
        updateMap(map,arr,ind);
        display(map,arr,ind);

        // scanning environment
        arr.getElem(ind).scan();

        // move Robot
        arr.getElem(ind).move();

        // delay
        sleep_for(speed);
    }
    // repeat until out of energy
    
}