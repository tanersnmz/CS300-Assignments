/*******************************************************************************************************************
Purpose: 
This program is a simplified version of the search engine which stores the data in Hash Table and the Binary Search Tree. 
Additionally, it displays the speed of some of the operations on these two data structures that are used for the implementation.

Author: Taner Giray Sonmez

Date: 8/05/2022

******************************************************************************************************************/


#include "BinaryTree.h"
#include "BinaryTree.cpp"

#include "HashTable.h"
#include "HashTable.cpp"

#include <string>
#include <iostream>

#include <algorithm> // I used the algorithm library for some string manipulations.

#include <fstream>
#include <sstream> // I used this library for some string manipulations as well.
#include <chrono>

#include "myStructs.h" // This contains the structs that I created.

#pragma comment(linker, "/HEAP:40000000") 
#pragma comment(linker, "/STACK:40000000") 

using namespace std;


/*
This function removes non-alphabetic characters, blanks from the string and also makes it lowercase.
*/
string removeNonAlpha(string word)
{
    for (int j = 0; j < word.size(); j++) {        
        if ( word[j] < 'A' || word[j] > 'Z'  && word[j] < 'a' || word[j] > 'z' ) 
        {  
            word.erase(j, 1);
            j--;
        }
    }
	transform(word.begin(), word.end(), word.begin(), ::tolower); // Makes it lowercase.
	remove(word.begin(), word.end(), ' '); // Removes spaces.
    return word;
}


WordItem temp;
BinarySearchTree<WordItem> BST(temp);
HashTable<WordItem> HT(temp,53);


int uniqueWordCounter=0;




int main (){
	
	//BELOW PART FOR CREATING HASH TABLE AND TREE.
	cout << "Enter number of input files: ";
	int numberOfInputFiles;
	cin >>numberOfInputFiles;
	vector<string> inputFiles;
	for (int i = 0; i < numberOfInputFiles; i++)
	{
		cout <<"Enter " << i+1 << ". file name: "; 
		string fileName;
		cin >> fileName;
		inputFiles.push_back(fileName);
	}
	for (int a = 0; a < numberOfInputFiles; a++)
	{			
		ifstream input;
		input.open(inputFiles[a].c_str());
		string word;	
		while (input >>word)
		{		
			string s = word;
			vector<string> words;
			for (int i = 0; i < s.length(); i++)
			{
				if (s[i] < 'A' || s[i] > 'Z' && s[i] < 'a' || s[i] > 'z')
				{  
					s[i] = ',';														  					
				}
			}
			stringstream parsing(s);
			while (parsing.good())
			{
				string parsedString;
				getline(parsing,parsedString,',');
				if (removeNonAlpha(parsedString).size()!=0)
				{
					words.push_back(removeNonAlpha(parsedString));
				}			
			}						
			for (int i = 0; i < words.size(); i++)
			{
				WordItem toFind;
				toFind.word= words[i];
				WordItem wordItem = BST.find(toFind); 							
				if (wordItem.word == words[i] ) 
				{		
					bool check = false;
					for (int c = 0; c <wordItem.listOfDocuments.size() ; c++)
					{
						if (wordItem.listOfDocuments[c].documentName == inputFiles[a])
						{
							check = true;
							wordItem.listOfDocuments[c].count++;
							WordItem toRemove = wordItem;
							BST.remove(toRemove);
							BST.insert(wordItem);
							HT.remove(toRemove);
							HT.insert(wordItem);
						}
					}
					if (!check)
					{
						WordItem toRemove = wordItem;
						BST.remove(toRemove);
						HT.remove(toRemove);
						DocumentItem newDoc;
						newDoc.count=1;
						newDoc.documentName= inputFiles[a];
						wordItem.listOfDocuments.push_back(newDoc);
						HT.insert(wordItem);
						BST.insert(wordItem);											
					}
				}
				else
				{										
					uniqueWordCounter++;									
					WordItem newItem;
					newItem.word = words[i];
					DocumentItem newDocument;
					newDocument.documentName = inputFiles[a];
					newDocument.count=1;
					newItem.listOfDocuments.push_back(newDocument);
					BST.insert(newItem);
					HT.insert(newItem);
				}
			}			
			parsing.clear();
			parsing.seekg(0);			
		}	
		input.close();
		input.clear();
		input.seekg(0);							
	}
	cout << endl;
	cout << "After preprocessing, the unique word count is " << uniqueWordCounter<<"." <<" Current load ratio is " << endl;
	cout << (double(uniqueWordCounter)) / HT.arrSize() <<endl;



	//BELOW IS PART FOR TAKING THE QUERY AND MANIPULATING STRINGS IN THE QUERY AS DESIRED.
	cout << "Enter queried words in one line: ";
	string queriedWords;
	cin.ignore();
	getline(cin,queriedWords);
	cin.clear();
	string ss =queriedWords;
	vector<string> wordsQuery;
	for (int i = 0; i < ss.length(); i++)
	{
		if (ss[i] < 'A' || ss[i] > 'Z' && ss[i] < 'a' || ss[i] > 'z')
		{  
			ss[i] = ',';		
		}
	}
	stringstream parsingQuery(ss);
	while (parsingQuery.good())
	{
		string parsedString;
		getline(parsingQuery,parsedString,',');
		if (removeNonAlpha(parsedString).size()!=0)
		{
			 wordsQuery.push_back(removeNonAlpha(parsedString));
		}
			
	}
	parsingQuery.clear();
	


	long long BSTIMER=0;
	long long HTIMER=0;
	

	//THIS PART IS SEARCHING EVERY STRING IN THE QUERY AND FINDING THAT THEY ARE IN TEXT FILES OR NOT.
	//IF THEY ARE IN THE TEXT FILE, THEN IT ADDS THE NECESSARY TXT FILE INTO THE VECTOR(containInput).
	vector<string> containInput;
	for (int i = 0; i < inputFiles.size(); i++)
	{
		int nc=0;
		string ifile = inputFiles[i];
		
		for (int j= 0; j < wordsQuery.size(); j++)
		{
			WordItem a,toFinder1,toFinder2;
			a.word=wordsQuery[j];			
			auto start = chrono::high_resolution_clock::now();
			for (int i = 0; i < 1000; i++)
			{
			   toFinder1 = BST.find(a);
			}
			auto BSTTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() -start);
			BSTIMER += BSTTime.count() / 1000.0;

			start = chrono::high_resolution_clock::now();
			for (int i = 0; i < 1000; i++)
			{
			   toFinder2 = HT.find(a);
			}
			auto HTTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() -start);
			HTIMER += HTTime.count() / 1000.0;
			for (int e = 0; e < toFinder1.listOfDocuments.size(); e++)
			{
				if (toFinder1.listOfDocuments[e].documentName==ifile)
				{
					nc++;
				}
			}
		}
		
		if (nc==wordsQuery.size())
		{
			containInput.push_back(ifile);
		}
	}
	



	

    //BELOW IS PART FOR SEARCHING IN THE TREE AND CALCULATING THE TIME.
	auto start = chrono::high_resolution_clock::now();
	for (int o = 0; o < 1000; o++)
	{

		if (containInput.size()==0)
		{
			cout << "No document contains the given query" << endl;
			break;
		}


		for (int l = 0; l < containInput.size(); l++)
		{
			for (int k = 0; k < wordsQuery.size(); k++)
			{
				WordItem a;
				a.word=wordsQuery[k];
				WordItem toFinder1 = BST.find(a);
				DocumentItem b;
				for (int e = 0; e < toFinder1.listOfDocuments.size(); e++)
				{
					if (toFinder1.listOfDocuments[e].documentName==containInput[l])
					{
						b =toFinder1.listOfDocuments[e];
					}
				}
				
				if (wordsQuery.size()>1)
				{
					
					if (k==0)
					{
						if (o==0)
							cout  << "in Document " <<  containInput[l]<< ", "+ wordsQuery[k] << " found " + to_string(b.count) +" times,";
					}
					else if (k>0)
					{
						if (k== wordsQuery.size()-1)
						{
							if (o==0)
							cout <<  " " <<wordsQuery[k] << " found " <<to_string( b.count) << " times."<<endl;
						}
						else
						{
							if (o==0)
							cout <<  " " <<wordsQuery[k] << " found " <<to_string( b.count) << " times,";
						}
					
					}
					
				}

				else
				{
					if (o==0)
					cout << "in Document " + containInput[l]+ ", "+ wordsQuery[k] + " found " + to_string(b.count) +" times." << endl;
				}
			}
		}		
	}
	auto BSTTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() -start);
	BSTIMER += BSTTime.count() / 1000.0;

	
	//BELOW IS PART FOR SEARCHING IN THE HASH TABLE AND CALCULATING THE TIME.
	start = chrono::high_resolution_clock::now();
	for (int o = 0; o < 1000; o++)
	{
		if (containInput.size()==0)
		{
			cout << "No document contains the given query" << endl;
			break;
		}


		for (int l = 0; l < containInput.size(); l++)
		{
			for (int k = 0; k < wordsQuery.size(); k++)
			{
				WordItem a;
				a.word=wordsQuery[k];
				WordItem toFinder1 = HT.find(a);
				DocumentItem b;
				for (int e = 0; e < toFinder1.listOfDocuments.size(); e++)
				{
					if (toFinder1.listOfDocuments[e].documentName==containInput[l])
					{
						b =toFinder1.listOfDocuments[e];
					}
				}
				
				if (wordsQuery.size()>1)
				{
					
					if (k==0)
					{
						if (o==0)
							cout  << "in Document " <<  containInput[l]<< ", "+ wordsQuery[k] << " found " + to_string(b.count) +" times,";
					}
					else if (k>0)
					{
						if (k== wordsQuery.size()-1)
						{
							if (o==0)
							cout <<  " " <<wordsQuery[k] << " found " <<to_string( b.count) << " times."<<endl;
						}
						else
						{
							if (o==0)
							cout <<  " " <<wordsQuery[k] << " found " <<to_string( b.count) << " times,";
						}
					
					}
					
				}

				else
				{
					if (o==0)
					cout << "in Document " + containInput[l]+ ", "+ wordsQuery[k] + " found " + to_string(b.count) +" times." << endl;
				}
			}
		}		
	}
	auto HTTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() -start);
	HTIMER += HTTime.count() / 1000.0;
	
	
	cout <<endl;
	cout<<"Time: " << BSTIMER<<endl;
	cout <<endl;
	cout << "Time: " << HTIMER << endl;
	cout << "Speed Up: " << double(BSTIMER) / HTIMER << endl;
	
	return 0;
}
