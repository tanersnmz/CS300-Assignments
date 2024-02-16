/*******************************************************************************************************************
Purpose: 
This program stores the data in AVL Search Tree and the Binary Search Tree. 
Additionally, it displays the speed of some of the operations on these tree data structures that are used for the implementation.

Author: Taner Giray Sonmez

Date: 11/04/2022

******************************************************************************************************************/


#include <iostream>
#include <string>
#include <fstream>
#include "BinaryTree.h"
#include "BinaryTree.cpp"
#include "AvlTree.h"
#include "AvlTree.cpp"
#include <chrono>

#pragma comment(linker, "/HEAP:40000000") // For increasing the size of the heap.
#pragma comment(linker, "/STACK:40000000") // For increasing the size of the program stack.


using namespace std;



/*
Struct for storing items.
*/
struct item{

    string itemTitle;
    string itemInfo;

    bool operator<( const item & other) const{
        return (itemTitle<other.itemTitle) ;
    }
 
    bool operator>(const item & other) const {
        return (itemTitle > other.itemTitle);
    }

	 bool operator!=(const item & other) const {
        return (itemTitle != other.itemTitle);
    }

	 bool operator==(const item & other) const {
        return (itemTitle == other.itemTitle);
    }
};


/*
Struct for storing sections that are in AVL Tree.
*/
struct AvlSection
{
	AvlTree<item> itemTree;	
    string sectionTitle;

	AvlSection(){}

	AvlSection(string title): sectionTitle(title), itemTree()
    {};

	bool operator<( const AvlSection & other) const{
        return (sectionTitle<other.sectionTitle) ;
    }
  
    bool operator>(const AvlSection & other) const {
        return (sectionTitle > other.sectionTitle);
    }

	  bool operator==(const AvlSection & other) const {
        return (sectionTitle == other.sectionTitle);
    }

	  bool operator!=(const AvlSection & other) const {
        return (sectionTitle != other.sectionTitle);
    }
	
};

/*
Struct for storing sections that are in BS Tree.
*/
struct section {
    
    
    BinarySearchTree<item> itemTree;
    string sectionTitle;

	section(){}

	section(string title): sectionTitle(title), itemTree()
    {};
	     
    bool operator<( const section & other) const{
        return (sectionTitle<other.sectionTitle) ;
    }
  
    bool operator>(const section & other) const {
        return (sectionTitle > other.sectionTitle);
    }

	  bool operator==(const section & other) const {
        return (sectionTitle == other.sectionTitle);
    }

	  bool operator!=(const section & other) const {
        return (sectionTitle != other.sectionTitle);
    }
      
};

//These temp and temp2 are "item not found objects" for Trees.
section temp;
AvlSection temp2;
BinarySearchTree<section> Tree(temp);
AvlTree<AvlSection> ATree(temp2);


/*
Operator << for BST section.
*/
ostream& operator<<(ostream& os, const section & s)
{
	
	os << s.sectionTitle;
	return os;
	
}

/*
Operator << for AVL Tree section.
*/
ostream& operator<<(ostream& os, const AvlSection & s)
{
	
	os << s.sectionTitle;
	return os;
	
}


/*
Operator << for items.
*/
ostream& operator<<(ostream& os, const item & i)
{
	
	os << i.itemTitle;
	return os;
	
   
}

//Main part for creating Trees and printing desired outputs.
int main() {
	
	
	section new_section1;
	AvlSection new_section2;



	string theLast="";
  
    string line;
    ifstream input;
    string fileName= "data.txt";
    input.open(fileName.c_str());
	 
	 
	 
	long long avlTimerWhileCreating=0,bstTimerWhileCreating=0;
	
	
	cout << "Welcome to the Notebook!" << endl;
	

    while (getline(input,line)) {
		
		if (line.find('-') == string::npos && line!=theLast )
		{
			
			
			new_section1.sectionTitle=line;
			new_section2.sectionTitle=line;

			auto startAVL = chrono::high_resolution_clock::now();
			ATree.insert(new_section2);
			auto endAVL =chrono::high_resolution_clock::now();
			avlTimerWhileCreating += (endAVL-startAVL).count() / 1000.0;

			if (theLast!="")
			{
				cout << "Section " << "\""<< theLast <<  "\""<<" has been inserted into the AVL notebook."<<endl;
				cout <<"[AVL] Elapsed time: " << avlTimerWhileCreating << " microseconds"<<endl;
			}
			
			auto startBST = chrono::high_resolution_clock::now();
			Tree.insert(new_section1);
			auto endBST =chrono::high_resolution_clock::now();
			bstTimerWhileCreating += (endBST-startBST).count() / 1000.0;

			if (theLast!="")
			{
				cout << "Section " << "\""<< theLast <<  "\""<<" has been inserted into the BST notebook."<<endl;
				cout <<"[BST] Elapsed time: " << bstTimerWhileCreating << " microseconds"<<endl;
			}
		
			
			cout <<endl;
			avlTimerWhileCreating=0;
			bstTimerWhileCreating=0;
			
			

			theLast=line;
		}
		
		
        if (line.find('-') == string::npos) { 
	
			new_section1.sectionTitle=line;
			new_section2.sectionTitle=line;

	
        }
        else{

			item new_item1,new_item2;
			int startingInfoIdx =line.find('-',1);
			string textItemTitle = line.substr(1,startingInfoIdx-1);
			string textItemInfo = line.substr(startingInfoIdx+1);
			
			new_item1.itemTitle = textItemTitle;
			new_item1.itemInfo= textItemInfo;

			new_item2.itemTitle = textItemTitle;
			new_item2.itemInfo= textItemInfo;
			
	
			auto startBST = chrono::high_resolution_clock::now();
			section toChange1 =Tree.find(new_section1);
			Tree.remove(new_section1);
			toChange1.itemTree.insert(new_item1);
			Tree.insert(toChange1);
			auto endBST =chrono::high_resolution_clock::now();
			bstTimerWhileCreating += (endBST-startBST).count() / 1000.0;


			auto startAVL = chrono::high_resolution_clock::now();
			AvlSection toChange2 = ATree.find(new_section2);
			ATree.remove(new_section2);	
			toChange2.itemTree.insert(new_item2);
			ATree.insert(toChange2);
			auto endAVL =chrono::high_resolution_clock::now();
			avlTimerWhileCreating += (endAVL-startAVL).count() / 1000.0;
        
        }
     
    }
    cout << "Section " << "\""<< theLast <<  "\""<<" has been inserted into the AVL notebook."<<endl;
	cout <<"[AVL] Elapsed time: " << avlTimerWhileCreating << " microseconds"<<endl;
	cout << "Section " << "\""<< theLast <<  "\""<<" has been inserted into the BST notebook."<<endl;
	cout <<"[BST] Elapsed time: " << bstTimerWhileCreating << " microseconds"<<endl;
	cout <<endl;
			
    
    input.close();//The ending point of the creating Trees.


	cout <<"MENU"<<endl;
	cout << "Please enter an input between [1 - 6]:"<<endl;
	cout << "1- Display the sections [AVL]"<<endl;
	cout << "2- Display the sections [BST]"<<endl;
	cout << "3- Select a section"<<endl;
	cout << "4- Add new section"<<endl;
	cout << "5- Delete a section"<<endl;
	cout << "6- Exit"<<endl;
	int userChoice=0;

	while (userChoice!=6)
	{
		cout<< "Input: ";
		cin>> userChoice;
		
		if (userChoice==2)
		{
			cout << endl;
			cout<<"*****"<<endl;
			Tree.printTree();
			cout<<"*****"<<endl;
			
		}
		if (userChoice==1)
		{
			cout << endl;
			cout<<"*****"<<endl;
			ATree.printTree();
			cout<<"*****"<<endl;
			
		}
		if (userChoice==4)
		{
			string userTitleChoice;
			cout <<"Enter a title for the section: " ;			cin.ignore();			getline(cin,userTitleChoice);
			cin.clear();
			//cin>>userTitleChoice;
			section userTitleChoiceSection1(userTitleChoice);
			AvlSection userTitleChoiceSection2(userTitleChoice);
			
			

			if (Tree.find(userTitleChoiceSection1).sectionTitle == userTitleChoice)
			{
				cout<<"Section "<<"\""<<userTitleChoice << "\""<< " already exists."<<endl;
			}
			else
			{
				Tree.insert(userTitleChoiceSection1);
				ATree.insert(userTitleChoiceSection2);
				cout <<"The new section "<<"\""<< userTitleChoice <<"\""<<" has been inserted."<<endl;
			}
			

		}

		if (userChoice==5)
		{
			string userTitleChoice;
			cout <<"Enter the title of the section: " ;			cin.ignore();			getline(cin,userTitleChoice);
			cin.clear();
			//cin>>userTitleChoice;
			section userTitleChoiceSection1(userTitleChoice);
			AvlSection userTitleChoiceSection2(userTitleChoice);
			if (Tree.find(userTitleChoiceSection1).sectionTitle == userTitleChoice)
			{
				Tree.remove(userTitleChoiceSection1);
				ATree.remove(userTitleChoiceSection2);
				cout<<"The section has been deleted."<<endl;
			}
			else
			{
				
				cout <<"Section "<<"\""<< userTitleChoice <<"\""<<" does not exist."<<endl;
			}

		}

		if (userChoice==3)
		{
	
			userChoice=0;
			string userTitleChoice;
			cout <<"Enter the title of the section: " ;			cin.ignore();			getline(cin,userTitleChoice);
			cin.clear();
			//cin>>userTitleChoice;
			
			section userTitleChoiceSection1(userTitleChoice);
			AvlSection userTitleChoiceSection2(userTitleChoice);
			if (Tree.find(userTitleChoiceSection1).sectionTitle == userTitleChoice)
			{
				cout <<endl;
				cout <<"Selected section -> " <<userTitleChoice<<endl;			
				cout << "Please enter an input between [1 - 7]:"<<endl;
				cout << "1- Display the items [AVL]"<<endl;
				cout << "2- Display the items [BST]"<<endl;
				cout << "3- Display the information of a item"<<endl;
				cout << "4- Add new item"<<endl;
				cout << "5- Update the information of a item"<<endl;
				cout << "6- Delete an item" <<endl;
				cout << "7- Return to main menu"<<endl;
			
			
				while (userChoice!=7)
				{
					cout<< "Input: ";
					cin>> userChoice;
					

					if (userChoice==2)
					{
						cout << endl;
						cout <<"*****"<<endl;
						Tree.find(userTitleChoiceSection1).itemTree.printTree();
						cout <<"*****"<<endl;
						cout << endl;
						
					}
					else if (userChoice==1)
					{
						
						cout << endl;
						cout <<"*****"<<endl;
						ATree.find(userTitleChoiceSection2).itemTree.printTree();
						cout <<"*****"<<endl;
						cout << endl;
						
					}
					else if (userChoice==5)
					{
						cout << "Enter the title of the item: ";
						string titleOfItem;						cin.ignore();						getline(cin,titleOfItem);
						cin.clear();
						//cin >> titleOfItem;
						item userChoiceItem;
						userChoiceItem.itemTitle=titleOfItem;

						
						auto startBST = chrono::high_resolution_clock::now();
						Tree.find(userTitleChoiceSection1).itemTree.find(userChoiceItem);
						auto endBST =chrono::high_resolution_clock::now();
						long long bstimer = (endBST-startBST).count() / 1000.0;

						auto startAVL = chrono::high_resolution_clock::now();
						ATree.find(userTitleChoiceSection2).itemTree.find(userChoiceItem);
						auto endAVL =chrono::high_resolution_clock::now();
						long long avltimer = (endAVL-startAVL).count() / 1000.0;
						


						cout << "[AVL] Elapsed time: "<<avltimer << " microseconds" <<endl;
						cout << "[BST] Elapsed time: "<< bstimer<< " microseconds" << endl;
						if (Tree.find(userTitleChoiceSection1).itemTree.find(userChoiceItem).itemTitle == titleOfItem)
						{
							cin.clear();
							string newItemInformation;
							cout << "Enter the new information: ";						    getline(cin,newItemInformation);
							
							//cin >> newItemInformation;


							section toChange1 = Tree.find(userTitleChoiceSection1);
							AvlSection toChange2 = ATree.find(userTitleChoiceSection2);

							item itemToBeUpdated = toChange1.itemTree.find(userChoiceItem);
							itemToBeUpdated.itemInfo=newItemInformation;

							toChange1.itemTree.remove(userChoiceItem);
							toChange1.itemTree.insert(itemToBeUpdated);

							toChange2.itemTree.remove(userChoiceItem);
							toChange2.itemTree.insert(itemToBeUpdated);

							ATree.remove(userTitleChoiceSection2);
							Tree.remove(userTitleChoiceSection1);
							Tree.insert(toChange1);
							ATree.insert(toChange2);
							cout << "The content " << titleOfItem << " has been updated." << endl;


							cout << endl;						
						}
						else
						{
							cout <<"Item "<< "\""<< titleOfItem <<"\""<< " does not exist in the "<< "\""<<userTitleChoice<< "\"." <<endl;
							cout << endl;
						}
					}

					else if (userChoice==6)
					{
						cout << "Enter the title of the item: ";
						string titleOfItem;						cin.ignore();						getline(cin,titleOfItem);
						cin.clear();
						//cin >> titleOfItem;
						item userChoiceItem;
						userChoiceItem.itemTitle=titleOfItem;
						if (Tree.find(userTitleChoiceSection1).itemTree.find(userChoiceItem).itemTitle == titleOfItem)
						{
							
							
							
							item itemToBeDeleted;
							itemToBeDeleted.itemTitle=titleOfItem;
							
							auto startBST = chrono::high_resolution_clock::now();
							section toChange1 = Tree.find(userTitleChoiceSection1);
							toChange1.itemTree.remove(itemToBeDeleted);
							Tree.remove(userTitleChoiceSection1);
							Tree.insert(toChange1);
							auto endBST =chrono::high_resolution_clock::now();
							long long bstimer = (endBST-startBST).count() / 1000.0;

							
							auto startAVL = chrono::high_resolution_clock::now();
							AvlSection toChange2 = ATree.find(userTitleChoiceSection2);		
							toChange2.itemTree.remove(itemToBeDeleted);
							ATree.remove(userTitleChoiceSection2);						
							ATree.insert(toChange2);							
							auto endAVL =chrono::high_resolution_clock::now();
							long long avltimer = (endAVL-startAVL).count() / 1000.0;
							
							cout << "[AVL] Elapsed time: "<< avltimer<< " microseconds"<< endl;
							cout << "[BST] Elapsed time: "<< bstimer << " microseconds"<<endl;
							cout << "The item " << "\""<< titleOfItem <<"\""<< " has been deleted." <<endl;
							cout <<endl;
						}
						else
						{
							cout <<"Item "<< "\""<< titleOfItem <<"\""<< " does not exist in the "<< "\""<<userTitleChoice<< "\"." <<endl;
							cout << endl;
						}
					}
					else if (userChoice==4)
					{
						cout << "Enter a title for the item: ";
						string titleOfItem;						cin.ignore();						getline(cin,titleOfItem);
						cin.clear();
						//cin >> titleOfItem;
						item userChoiceItem;
						userChoiceItem.itemTitle=titleOfItem;

						if (Tree.find(userTitleChoiceSection1).itemTree.find(userChoiceItem).itemTitle == titleOfItem)
						{
							cout <<"Item "<< "\""<< titleOfItem <<"\""<< " already exist in the "<< "\""<<userTitleChoice<< "\"." <<endl;
							cout << endl;
						}
						else
						{
							
							string description;
							cin.clear();
							cout << "Enter a description for the item: ";						    getline(cin,description);
							//cin >> description;
							item itemToBeInserted;
							itemToBeInserted.itemInfo=description;
							itemToBeInserted.itemTitle=titleOfItem;

							auto startBST = chrono::high_resolution_clock::now();
							Tree.find(userTitleChoiceSection1).itemTree.find(userChoiceItem);
							section toChange1 = Tree.find(userTitleChoiceSection1);
							toChange1.itemTree.insert(itemToBeInserted);
							Tree.remove(userTitleChoiceSection1);
							Tree.insert(toChange1);
							auto endBST =chrono::high_resolution_clock::now();
							long long bstimer = (endBST-startBST).count() / 1000.0;

							auto startAVL = chrono::high_resolution_clock::now();
							ATree.find(userTitleChoiceSection2).itemTree.find(userChoiceItem);
							AvlSection toChange2 = ATree.find(userTitleChoiceSection2);				
							toChange2.itemTree.insert(itemToBeInserted);
							ATree.remove(userTitleChoiceSection2);
							ATree.insert(toChange2);
							auto endAVL =chrono::high_resolution_clock::now();
							long long avltimer = (endAVL-startAVL).count() / 1000.0;

							cout << "[AVL] Elapsed time: "<<  avltimer <<" microseconds"<<endl;
							cout << "[BST] Elapsed time: "<< bstimer <<" microseconds"<<endl;
							cout << "The new item " << "\""<< titleOfItem <<"\""<< " has been inserted." <<endl;
							cout <<endl;
						}
					}
					else if (userChoice==3)
					{
						cout << "Enter the title of the item: ";
						string titleOfItem;						cin.ignore();						getline(cin,titleOfItem);
						cin.clear();
						//cin >> titleOfItem;
						item userChoiceItem;
						userChoiceItem.itemTitle=titleOfItem;

						auto startAVL = chrono::high_resolution_clock::now();
						ATree.find(userTitleChoiceSection2).itemTree.find(userChoiceItem).itemInfo;
						auto endAVL =chrono::high_resolution_clock::now();
						long long avltimer = (endAVL-startAVL).count() / 1000.0;

						
						
						auto startBST = chrono::high_resolution_clock::now();
						Tree.find(userTitleChoiceSection1).itemTree.find(userChoiceItem).itemInfo;
						auto endBST =chrono::high_resolution_clock::now();
						long long bstimer = (endBST-startBST).count() / 1000.0;

						cout << "[AVL] Elapsed time: "<< avltimer << " microseconds"<<endl;
						cout << "[BST] Elapsed time: "<< bstimer << " microseconds"<<endl;

						if (Tree.find(userTitleChoiceSection1).itemTree.find(userChoiceItem).itemTitle == titleOfItem)
						{
							cout <<Tree.find(userTitleChoiceSection1).itemTree.find(userChoiceItem).itemInfo<<endl;
							cout << endl;
						}
						else
						{
							cout << "Invalid title." << endl;
							cout << endl;
						}
					}
					else if (userChoice==7)
					{
						//cout <<endl;
						cout <<"MENU"<<endl;
						cout << "Please enter an input between [1 - 6]:"<<endl;
						cout << "1- Display the sections [AVL]"<<endl;
						cout << "2- Display the sections [BST]"<<endl;
						cout << "3- Select a section"<<endl;
						cout << "4- Add new section"<<endl;
						cout << "5- Delete a section"<<endl;
						cout << "6- Exit" <<endl;
					}
				}
			}

			else
			{				
				cout <<"Invalid title!"<<endl;
			}

		}

		cout << endl;
	}
  
    return 0;
}
