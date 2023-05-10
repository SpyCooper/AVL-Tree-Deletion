#include <iostream>
#include "avl_tree.h"
using namespace std;

void AVLTree::insert(const int newValue) {

  bool isTaller = false;
  AVLNode *newNode;
  newNode = new AVLNode(newValue);
  insertIntoAVL(root,newNode,isTaller);
  
}

void AVLTree::insertIntoAVL(AVLNode* &root, AVLNode *newNode, bool& isTaller){
  if (root == NULL){
    root = newNode;
    isTaller = true;
  }
  else if (root->value == newNode->value){
    cout << "Duplicate" << endl;
  }
  else if (root->value > newNode->value){

    insertIntoAVL(root->left, newNode,isTaller);

    if (isTaller){
      switch (root->bf)
	{
	case -1:
	  balanceFromLeft(root);
	  isTaller = false;
	  break;

	case 0:
	  root->bf = -1;
	  isTaller = true;
	  break;

	case 1:
	  root->bf = 0;
	  isTaller = false;
	}
    }
  }
  else{

    insertIntoAVL(root->right, newNode, isTaller);

    if(isTaller){
      switch(root->bf)
	{
	case -1:
	  root->bf = 0;
	  isTaller = false;
	  break;
	  
	case 0:
	  root->bf = 1;
	  isTaller = true;
	  break;
	  
	case 1:
	  balanceFromRight(root);
	  isTaller = false;
	}
    }
  }
}

void AVLTree::rotateToLeft(AVLNode* &root){
  AVLNode *p;
  
  if (root == NULL)
    cout << "Error in the tree" << endl;
  else if (root->right == NULL)
    cout << "Error in the tree: No right subtree to rotate." << endl;
  else{
    p = root->right;
    root->right = p->left;
    p->left = root;
    root = p; 
  }
}

void AVLTree::rotateToRight(AVLNode* &root){
  AVLNode *p;

  if (root == NULL)
    cout << "Error in the tree" << endl;
  else if (root->left == NULL)
    cout << "Error in the tree: No left subtree to rotate." << endl;
  else{
    p = root->left;
    root->left = p->right; 
    p->right = root;
    root = p; 
  }
}

void AVLTree::balanceFromLeft(AVLNode* &root){

  AVLNode *p;
  AVLNode *w;

  p = root->left;

  switch (p->bf)
    {
    case -1:
      root->bf = 0;
      p->bf = 0;
      rotateToRight(root);
      break;

    case 0:
      //sets the roots BF factor and the predecessor's BF factor then calls rotate to right
      root->bf = -1;
      p->bf = 1;
      rotateToRight(root);
      break; 

    case 1:
      w = p->right;

      switch (w->bf)
	{
	case -1:
	  root->bf = 1;
	  p->bf = 0;
	  break;
	case 0:
	  root->bf = 0;
	  p->bf = 0;
	  break;
	case 1:
	  root->bf = 0;
	  p->bf = -1;
	}
      
      w->bf = 0;
      rotateToLeft(p);
      root->left = p;
      rotateToRight(root);
    }
}

void AVLTree::balanceFromRight(AVLNode* &root){
  AVLNode *p;
  AVLNode *w;

  
  p = root->right;
  switch (p->bf)
    {
    case -1:
      
      w = p->left;
      switch (w->bf)
	{
	case -1:
	  root->bf = 0;
	  p->bf = 1;
	  break;
	case 0:
	  root->bf = 0;
	  p->bf = 0;
	  break;
	case 1:
	  root->bf = -1;
	  p->bf = 0;
	}
      
      w->bf = 0;
      rotateToRight(p);
      root->right = p;
      rotateToLeft(root);
      break;

    case 0:
      //sets the roots BF factor and the predecessor's BF factor then calls rotate to left
      root->bf = 1;
      p->bf = -1;
      rotateToLeft(root);
      break;

    case 1:
      root->bf = 0;
      p->bf = 0;
      rotateToLeft(root);
    }
}

void AVLTree::print(char letter){
  //checks to see what letter was entered
  if(letter == 'h')
  {
    //checks to see if the tree is empty
    if(root == NULL)
    {
      //if the tree is empty, it prints out empty
      cout << "Empty" << endl;
    }
    else
    {
      //calls the printHeight function to print the height
      printHeight(root);
      cout << endl;
    }
  }
  else if(letter == 'p')
  {
    //checks to see if the tree is empty
    if(root == NULL)
    {
      //if the tree is empty, it prints out empty
      cout << "Empty" << endl;
    }
    else
    {
      //calls printData to print the data
      printData(root);
      cout << endl;
    }
  }
}

AVLNode* AVLTree::getPred(AVLNode* node)
{
  //makes a temporary node the points at the left child
  AVLNode* temp = node->left;
  //as long as the left subtree isn't empty
  if (temp != NULL)
  {
    //if the left child of the original node is not a leaf node
    if(temp->right != NULL)
    {
      //this will continue moving down the left subtree on the right side to get the predecessor, until it hit's a leaf node
      while(temp->right != NULL)
      {
        temp = temp->right;
      }
    }
  }
  //returns the predecessor or NULL if that was what the left child of the original node was
  return temp; 

}

void AVLTree::remove(int badValue){
  bool isShorter = false;
  remove(root,badValue, isShorter);
}

//need to update the root's bf factor
void AVLTree::remove(AVLNode* &root, int badValue, bool& isShorter)
{
  //is the root isn't in the tree, it ends the function
  if(root == NULL)
  {
    return;
  }
  //if the current node's value is more than the value we want to remove, it goes to the left child
  else if(root->value > badValue)
  {
    //recursively calls remove
    remove(root->left, badValue, isShorter);

    //checks to see if the BF factor needs to be changed
    if(isShorter)
    {
      //changes the bf factor based on the original bf factor
      switch (root->bf)
      {
        case -1:
          root->bf = 0;
          isShorter = false;
          break;
        case 0:
          root->bf = 1;
          isShorter = false;
          break;
        case 1:
          balanceFromRight(root);
          isShorter = false;
          break;
      }
    }
  }
  //if the current node's value is less than the value we want to remove, it goes to the right child
  else if(root->value < badValue)
  {
    //recursively calls remove function
    remove(root->right, badValue, isShorter);

    //checks to see if the BF factor needs to be changed
    if(isShorter)
    {
      //switches the bf factor based on it's previous value
      switch (root->bf)
      {
        case -1:
          balanceFromLeft(root);
          isShorter = true;
          break;
        case 0:
          root->bf = -1;
          isShorter = false;
          break;
        case 1:
          root->bf = -1;
          isShorter = true;
          break;
      }
    }
  }
  //the current node contains the value we want to remove
  else if(root->value == badValue)
  {
    //case 1: if the node is a leaf node, we just remove it
    if(root->left == NULL && root->right == NULL)
    {
      AVLNode* temp = root;
      root = NULL;
      delete temp;
      isShorter = true;
      return;
    }
    //case 2: the current node only has a right child
    else if(root->left == NULL && root->right != NULL)
    {
      //copies all the data over from the right child to the current node then removes the right child
      AVLNode* temp = root->right;
      root->value = temp->value;
      root->left = temp->left;
      root->bf = temp->bf;
      root->right = temp->right;
      delete temp;
      isShorter = true;
    }
    //case 3: the current node only has a left child
    else if(root->left != NULL && root->right == NULL)
    {
      //copies all the data over from the left child to the current node then removes the left child
      AVLNode* temp = root->left;
      root->value = temp->value;
      root->left = temp->left;
      root->bf = temp->bf;
      root->right = temp->right;
      delete temp;
      isShorter = true;
    }
    //case 4: the current node has 2 children
    else
    {
      //gets the predecessor of the current node and inputs the value of the pred into the current node
      AVLNode* pred = getPred(root);
      root->value = pred->value;

      //removes the predecessor from the left subtree of the current node
      remove(root->left, pred->value, isShorter);

      //checks to see if the function was shortened
      if(isShorter == true)
      {
        //readjusts the bf factor of the node after deletion
        switch(root->bf)
        {
          case -1:
            root->bf = 0;
            isShorter = true;
            break;
          case 0:
            root->bf = 1;
            isShorter = false;
            break;
          case 1:
            balanceFromRight(root);
            isShorter = false;
            break;
        }
      }
    }
  }
}

void AVLTree::printData(AVLNode* &root)
{
  //checks to make sure it is not at the end of the tree
  if(root == NULL)
  {
    return;
  }
  else
  {
    //prints the data in the left node, the current node, then the right node
    printData(root->left);
    cout << root->value << " ";
    printData(root->right);
  }
}

void AVLTree::printHeight(AVLNode* &root)
{
  //checks to make sure it is not at the end of the tree
  if(root == NULL)
    return;
  else
  {
    //prints the height of the left node
    printHeight(root->left);
    
    //prints out the current height-1, as it was printing all nodes 1 higher than they should be
    int curHeight = checkHeight(root);
    cout << curHeight-1 << " ";
    //prints the height of the right node
    printHeight(root->right);
  }
}

int AVLTree::checkHeight(AVLNode* &root)
{
  //if the root is pointing at NULL, it is at the end of the tree
  if(root == NULL)
  {
    //it returns the height of the node that points here
    return 1;
  }
  else
  {
    //checks the left and right rights
    int left = checkHeight(root->left);
    int right = checkHeight(root->right);

    //sets the max height to 1
    int max = 1;

    //sets the max height as whatever the greater side of the tree is + 1
    if(left > right)
    {
      max = max + left;
    }
    else if(right > left)
    {
      max = max + right;
    }
    else
    {
      max = max + left;
    }

    //returns the max height
    return max;
  }
}