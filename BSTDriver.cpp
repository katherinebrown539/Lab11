#include "BinarySearchTree.h"
#include "BinaryTreeIterator.h"
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "CD.h"
using CSC2110::CD;

#include <iostream>
using namespace std;

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }

   delete iter;
}

bool isSorted(CD** cds, int n)
{
	int comp;
	for(int i = 0; i < n-2; i++)
	{
		comp = cds[i]->compare_items(cds[i], cds[i+1]);
		if(comp > 0) return false;
	}
	
	return true;
}

void displayTitles(CD** cds, int num_items)
{
	for(int i = 0; i < num_items; i++)
   {
	   cout << i+1 << ". ";
	   (cds[i]->getKey())->displayString();
		cout << endl;
   }
   cout << endl;
}

int main()
{
   //the unsorted ListArray of cds
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   int num_items = cds->size();
   cout << num_items << endl;
   cout << endl;

   //test the binary search tree
   //insert all of the cds
   ListArrayIterator<CD>* iter = cds->iterator();
   BinarySearchTree<CD>* bst = new BinarySearchTree<CD>(&CD::compare_items, &CD::compare_keys);
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      bst->insert(cd);
   }
   delete iter;
	bool sorted = false;
   
   //DO THIS
   //test your tree sort method
   CD** unsorted_cds = cds->toArray();
   displayTitles(unsorted_cds, num_items);

	if(isSorted(unsorted_cds, num_items))
	{
		cout << "Sorted\n";
	}
	else
	{
		cout << "Not sorted\n";
	}
   
   CD** sorted_cds = bst->treeSort(unsorted_cds, num_items, CD::compare_items, CD::compare_keys);
   displayTitles(sorted_cds, num_items);

   if(isSorted(sorted_cds, num_items))
	{
		cout << "Sorted\n";
	}
	else
	{
		cout << "Not sorted\n";
	}
	
   deleteCDs(cds);
   delete cds;
   return 0;
}
