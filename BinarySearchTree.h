#if !defined (BINARYSEARCHTREE_H)
#define BINARYSEARCHTREE_H

#if DEBUG

#include <iostream>
using namespace std;
#endif

#include "BinaryTreeIterator.h"
#include "TreeNode.h"
#include "Text.h"
#include "Line.h"
#include "Drawable.h"
using CSC2110::String;

template < class T >
class BinarySearchTree : public Drawable
{

   private:
      TreeNode<T>* root;
      int sze;
      void destroyItem(TreeNode<T>* tNode);
      void destroy();

      TreeNode<T>* insertItem(TreeNode<T>* tNode, T* item);
	   //todo: done
      TreeNode<T>* removeItem(TreeNode<T>* tNode, String* sk);
	   //todo: done
      TreeNode<T>* removeNode(TreeNode<T>* tNode);
	   //todo: done
      TreeNode<T>* removeLeftMost(TreeNode<T>* tNode);
	   //todo: done
      T* findLeftMost(TreeNode<T>* tNode);

      TreeNode<T>* getRootNode();
      void setRootNode(TreeNode<T>* tNode);
      int getHeight(TreeNode<T>* tNode);
      bool isBalanced(TreeNode<T>* tNode);

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (String* key, T* item);

      virtual void drawRec(TreeNode<T>* tNode, Cairo::RefPtr<Cairo::Context> cr, Line* line, int x_parent, int x_curr, int y_curr);

   public:
      BinarySearchTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));
      ~BinarySearchTree();

      bool isEmpty();
      void makeEmpty();

      T* retrieve(String* search_keys);
      void insert(T* item);
	  //todo: done
      void remove(String* search_keys);

      BinaryTreeIterator<T>* iterator();
      T* getRootItem();
      int getHeight();
      bool isBalanced();

	  //todo: done
      T** toArray();
	  //todo
      static T** treeSort(T** items, int num_itemss, int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));

      virtual void draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height);
      virtual void mouseClicked(int x, int y);
};

template < class T >
void BinarySearchTree<T>::remove(String* sk)
{
   //DO THIS
   #if DEBUG
   cout << "About to remove\n";
   #endif
	root = removeItem(root, sk);
	#if DEBUG
	String* k = (root->getItem())->getKey();
	k->displayString();
	#endif
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeItem(TreeNode<T>* tNode, String* sk)
{
	if(tNode == 0)
	{
		return tNode;
	}
	
   //DO THIS
   T* item = tNode->getItem();
   int comp = (*compare_keys) (sk, item);
   
   #if DEBUG
   cout << comp << endl;
   #endif
   
   if(comp == 0)
   {
	   #if DEBUG
	   cout << "Found\n";
	   #endif
	   sze--;
	  TreeNode<T>* subtree = removeNode(tNode);
	  #if DEBUG
	  cout << "About to return subtree\n";
	  #endif
	  return subtree;   	
	 
		
   }
	else if(comp < 0)
	{
		#if DEBUG
		cout << "Less than\n";
		#endif
		TreeNode<T>* sub = removeItem(tNode->getLeft(), sk);
		tNode->setLeft(sub);
		return tNode;
	}
	else
	{
	  #if DEBUG
		cout << "Greater than\n";
		#endif
		TreeNode<T>* sub = removeItem(tNode->getRight(), sk);
		tNode->setRight(sub);
		return tNode;
	}
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeNode(TreeNode<T>* tNode)
{
   if (tNode->getLeft() == NULL && tNode->getRight() == NULL)
   {
      delete tNode;
      return NULL;
   }
   else if (tNode->getLeft() == NULL)
   {
      TreeNode<T>* temp = tNode->getRight();
      delete tNode;
      return temp;
   }
   else if (tNode->getRight() == NULL)
   {
      TreeNode<T>* temp = tNode->getLeft();
      delete tNode;
      return temp;
   }
   else 
   {
      //DO THIS
	  #if DEBUG
	  cout << "In the else block\n";
	  #endif
	  
	  TreeNode<T>* right = tNode->getRight();
	  T* data = findLeftMost(right);
	  tNode->setItem(data);
	   TreeNode<T>* subtree = removeLeftMost(right);
	   tNode->setRight(subtree);
	 
   }
}

template < class T >
T* BinarySearchTree<T>::findLeftMost(TreeNode<T>* tNode)
{
   //DO THIS (use a while loop)

   #if DEBUG
   cout << "Starting while loop\n";
   int count = 0;
   #endif
	while(tNode->getLeft() != 0)
	{
		#if DEBUG
		cout << "About to assign left\n";
		#endif
		tNode = tNode->getLeft();
		#if DEBUG
		count++;
		cout << "We have been through the loop " << count << " times.\n";
		#endif
	}

	return tNode->getItem();
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeLeftMost(TreeNode<T>* tNode)
{
    //DO THIS (recursion)
	if(tNode->getLeft() == 0)
	{
		return tNode->getRight();
	}
	else
	{
		TreeNode<T>* subtree = removeLeftMost(tNode->getLeft());
		tNode->setLeft(subtree);
		return tNode;
	}
}

template < class T >
T** BinarySearchTree<T>::toArray()
{
    //DO THIS
	T** the_array = new T* [sze];
	int count = 0;
	
	BinaryTreeIterator<T>* bst_iter = iterator();
	bst_iter->setInorder();
	
	while(bst_iter->hasNext())
	{
		the_array[count] = bst_iter->next();
		count++;
	}
	
	delete bst_iter;
	return the_array;
}

template < class T >
T** BinarySearchTree<T>::treeSort(T** items, int num_itemss, int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
   //DO THIS
   //Assuming that items can be overwritten. Need to find out if I need to create a copy of stuffs
	BinarySearchTree<T>* tree = new BinarySearchTree<T> ((*comp_items), (*comp_keys));
	int first = 0;
	int last = num_itemss-1;
	int mid = (first + (last-first))/2;
	tree->insert(items[mid]);
	
	for(int c = 0; c < num_itemss; c++)
	{
		#if DEBUG
		(items[c]->getKey())->displayString();
		cout << endl; 
		#endif
		tree->insert(items[c]);
	}
	T** sorted = tree->toArray();
	
	return sorted;
}
//NO MORE DOING!!
template < class T >
BinarySearchTree<T>::BinarySearchTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
   root = NULL;
   sze = 0;

   compare_items = comp_items;
   compare_keys = comp_keys;
}

template < class T >
BinarySearchTree<T>::~BinarySearchTree()
{
   destroy();
}

template < class T >
void BinarySearchTree<T>::destroy()
{
   destroyItem(root);
}

template < class T >
void BinarySearchTree<T>::destroyItem(TreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      destroyItem(tNode->getLeft());
      destroyItem(tNode->getRight());
      delete tNode;
   }
}

template < class T >
bool BinarySearchTree<T>::isEmpty()
{
   return sze == 0;
}

template < class T >
void BinarySearchTree<T>::makeEmpty()
{
   destroy();
   root == NULL;
   sze = 0;
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::getRootNode()
{
   return root;
}

template < class T >
void BinarySearchTree<T>::setRootNode(TreeNode<T>* tNode)
{  
   root = tNode;
}

template < class T >
T* BinarySearchTree<T>::getRootItem()
{
   T* rootItem = root->getItem();
   return rootItem;
}

template < class T >
void BinarySearchTree<T>::insert(T* item)
{
   root = insertItem(root, item);
}

template < class T >
T* BinarySearchTree<T>::retrieve(String* sk)
{
   TreeNode<T>* tNode = getRootNode();

   while (tNode != NULL)
   {
      T* node_items = tNode->getItem();
      int comp = (*compare_keys) (sk, node_items);

      if (comp == 0)
      {
         //no duplicate search keys allowed, so do nothing
         return node_items;
      }
      else if (comp < 0)
      {
         tNode = tNode->getLeft();
      }
      else
      {
         tNode = tNode->getRight();
      }
   }

   return NULL; //item is not in the tree
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::insertItem(TreeNode<T>* tNode, T* item)
{
   TreeNode<T>* subtree;
   if (tNode == NULL)
   { 
      sze++;
      return new TreeNode<T>(item);
   }

   T* node_items = tNode->getItem();
   int comp = (*compare_items) (item, node_items);

   if (comp == 0)
   {
      //no duplicate search keys allowed, so do nothing
      return tNode;
   }
   else if (comp < 0)
   {
      subtree = insertItem(tNode->getLeft(), item);
      tNode->setLeft(subtree);
   }
   else
   {
      subtree = insertItem(tNode->getRight(), item);
      tNode->setRight(subtree);
   }
   
   return tNode;
}

template < class T >
BinaryTreeIterator<T>* BinarySearchTree<T>::iterator()
{
   return new BinaryTreeIterator<T>(root);
}

template < class T >
void BinarySearchTree<T>::draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height)
{
   Line line(new Color(0, 0, 0), 5.0);
   drawRec(getRootNode(), cr, &line, width, width/2, 20);
}

template < class T >
void BinarySearchTree<T>::drawRec(TreeNode<T>* tNode, Cairo::RefPtr<Cairo::Context> cr, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(cr, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), cr, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), cr, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(cr, x_curr, y_curr);
   }
}

template < class T >
void BinarySearchTree<T>::mouseClicked(int x, int y) {}

#endif
