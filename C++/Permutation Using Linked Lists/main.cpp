// Function: To permutate different versions of CATMAN using customized version of a LinkedList

#include <iostream>
#include "permute.h"
using std::cout;

int main()
{

	// Set Up

	Permute* arr[9] = 
	{ new Permute("", ""), new Permute("", "CATMAN"), new Permute("C", "ATMAN"),
	  new Permute("CA", "TMAN"),new Permute("CAT", "MAN"),new Permute("CATM", "AN"),
	  new Permute("CATMA", "N"), new Permute("CATMAN", "") };
	
	// go through every permute object
	for (int i = 0; i < 8; i++)
	{
		// for max # in row
		int rowMax = 0;
		// current Permutation object
		Permute* currPerm = arr[i];

		// label the strings
		cout << "String 1 for this object is: " << currPerm->getFirstString() << "\n";
		cout << "String 2 for this object is: " << currPerm->getSecondString() << "\n";

		// set up permute object
		currPerm->setupPermList();
		currPerm->permutation(0);

		// if total permutations > 100, break a line every 9 permutations
		// else, break a line every 4 permutations
		if (currPerm->getTotal() > 100)
			rowMax = 9;
		else
			rowMax = 4;

		// ------------------------

		// print 

		// if there are perms, print #, and then print perms
		if (currPerm->getTotal() != 0)
		{
			// label perm number
			cout << "The total possible permutation is " << currPerm->getTotal() << "\n";
			// plural or not plural
			if (currPerm->getTotal() <= 1)
				cout << "That is: " << "\n";
			else
				cout << "They are: " << "\n";

			// print out permutations
			for (int j = 0; j < currPerm->getTotal();j++)
			{
				// if just finished a multiple of rowMax, print break line
				if (j > 0 && j % rowMax == 0)
					cout << "\n";

				currPerm->print(j);
				// print 2 spaces
				cout << "  ";
			}
		}
		// if no perms, print out label for no perms
		else
		{
			cout << "There is no permutation." << "\n";
		}

		cout << "\n\n\n";

	}

	return 0;
}