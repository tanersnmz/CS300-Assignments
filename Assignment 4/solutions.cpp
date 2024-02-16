/*******************************************************************************************************************
Purpose: 
This program is for comparing different sorting algorithms and different searching algorithms.
It displays the speed of sorting algorithms and searching algorithms that are used for the implementation.

Author: Taner Giray Sonmez

Date: 2/06/2022

******************************************************************************************************************/

#include "Sortings.cpp" // It contains Sorting Algorithms.
#include <iostream>
#include <string>
#include <fstream> // For operating over input the file.
#include <sstream> // For input data manipulations.
#include <chrono> // For measuring the time.
#include "strutils.h" // For input and output manipulations.

using namespace std;

//This struct keeps the information in the input file.
//I also overloaded some operators.
struct Phonebook {
    string firstName;
    string lastName;
    string phone;
    string city;
    
    bool operator <= (const Phonebook & rhs) {
        string rhsUserName= rhs.firstName + rhs.lastName;
        string lhsUserName = firstName + lastName;
        return (lhsUserName <= rhsUserName);
    }
    
    bool operator >= (const Phonebook & rhs) {
        string rhsUserName= rhs.firstName + rhs.lastName;
        string lhsUserName = firstName + lastName;
        return (lhsUserName >= rhsUserName);
    }
    
    bool operator < (const Phonebook & rhs) {
        string rhsUserName= rhs.firstName + rhs.lastName;
        string lhsUserName = firstName + lastName;
        return (lhsUserName < rhsUserName);
    }
    
    bool operator > (const Phonebook & rhs) {
        string rhsUserName= rhs.firstName + rhs.lastName;
        string lhsUserName = firstName + lastName;
        return (lhsUserName > rhsUserName);
    }
    
};

// Classic Binary Search From CS201.
// pre: list.size() == # elements in list
// post: returns index of key in list, -1 if key not found
int bsearch(const vector<Phonebook>& list, const string & key){

    int low = 0;                   // leftmost possible entry
    int high = list.size()-1;      // rightmost possible entry
    int mid;                       // middle of current range

    while (low <= high){
        mid = (low + high)/2;
        if ( (list[mid].firstName+list[mid].lastName) == key)       // found key, exit search
           return mid;
        else if ( (list[mid].firstName+list[mid].lastName) < key)   // key in upper half
           low = mid + 1;
        else                        // key in lower half
           high = mid - 1;
    }
    return -1;                      // not in list
}

// This is a Partial Binary Search that was implemented for homework purposes.
// If the key exists in the data, it returns the list of indexes for the key value.
// If the key does not exist in the data, then it returns an empty list.
vector<int> bsearchWithPartial(const vector<Phonebook>& list, const string & key){
   
    

	int high = list.size()-1;      // rightmost possible entry
    int mid;                       // middle of current range
    int low = 0;                   // leftmost possible entry
   

	vector<int> binarySearchLocations; // Vector stores the indexes.

    while (low <= high){
        mid = (low + high)/2;
        if ( list[mid].firstName.find(key) != string::npos)  {
        
            
            while (mid>=0 && list[mid].firstName.find(key) != string::npos ) mid--;
            mid++;
            
            while (mid <= list.size()-1 && list[mid].firstName.find(key) != string::npos) {
                binarySearchLocations.push_back(mid);
                mid++;
            }
            return binarySearchLocations;
            
            
        }     // found key, exit search
           
        else if ( (list[mid].firstName) < key)   // key in upper half
           low = mid + 1;
        else                        // key in lower half
           high = mid - 1;
    }
    
    
    
    return binarySearchLocations;
}

// Classic Sequential Search From CS201.
// pre: list.size() == # elements in list
// post: returns index of key in list, -1 if key not found
int sequentialSearch(const vector<Phonebook>& list, const string& key){
    int location =-1;
    for (int i=0; i<list.size(); i++) {
        if ( (list[i].firstName+list[i].lastName) == key) {
            location =i;
        }
    }
    return location;
}

// This is a Partial Sequential Search that was implemented for homework purposes.
// If the key exists in the data, it returns the list of indexes for the key value.
// If the key does not exist in the data, then it returns an empty list.
vector<int> sequentialSearchWithPartial(const vector<Phonebook>& list, const string& key){           
    vector<int> sequentialSearchLocations;
    for (int i=0; i<list.size(); i++) {
        if ( list[i].firstName.find(key) != string::npos) {
            sequentialSearchLocations.push_back(i);
        }
    }
    return sequentialSearchLocations;
}




int main() {

	//Vectors that I am going to sort.
    vector<Phonebook> insertionSortVector;
    vector<Phonebook> mergeSortVector;
    vector<Phonebook> quickSortVector;
    vector<Phonebook> heapSortVector;
    
	//Taking the input.
    string fileName,queriedWord;
    cout << "Please enter the contact file name: ";
    cin >> fileName;
    cout << "Please enter the word to be queried: ";
    cin.ignore();
    getline(cin, queriedWord);
    stringstream parse(queriedWord);
    string wantedName,wantedSurname;
    parse >> wantedName >> wantedSurname;
    
    
   
    //Parsing the input in the desired format and putting it into necessary vectors.
    ifstream input;
    string line;
    input.open(fileName.c_str());
    while (getline(input,line)) {       
        string name,surname,phonenumber,city;
        stringstream ss(line);        
        ss>> name >>surname >> phonenumber >> city;       
        Phonebook person;
        person.firstName= name;
        person.lastName = surname;
        person.phone = phonenumber;
        person.city = city;       
        insertionSortVector.push_back(person);
        mergeSortVector.push_back(person);
        quickSortVector.push_back(person);
        heapSortVector.push_back(person);
        
    }           
    input.close();   
    cout << endl;


    cout <<"Sorting the vector copies" <<endl;
    cout << "======================================"<<endl;

	
	
    //Calculations of the average timing for quick sort (in 20 trials).
    auto startQ = chrono::high_resolution_clock::now();
	for (int i = 0; i < 19; i++){
		vector<Phonebook> trial = quickSortVector;
		quicksort(trial);
	}
    quicksort(quickSortVector);
    auto QTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startQ);
    cout << "Quick Sort Time: " << QTime.count() / 20.0 << " Nanoseconds"<< endl;
    
    
    //Calculations of the average timing for insertion sort (in 20 trials).
    auto startI = chrono::high_resolution_clock::now();
	for (int i = 0; i < 19; i++){
		vector<Phonebook> trial = insertionSortVector;
		insertionSort(trial);
	}
    insertionSort(insertionSortVector);
    auto ITime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startI);
    cout << "Insertion Sort Time: " << ITime.count() / 20.0 << " Nanoseconds"<< endl;
    
    
    //Calculations of the average timing for merge sort (in 20 trials).
    auto startM = chrono::high_resolution_clock::now();
	for (int i = 0; i < 19; i++){
		vector<Phonebook> trial = mergeSortVector;
		mergeSort(trial);
	}
    mergeSort(mergeSortVector);
    auto MTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startM);
    cout << "Merge Sort Time: " << MTime.count() / 20.0 << " Nanoseconds"<< endl;
    
    
    //Calculations of the average timing for heap sort (in 20 trials).
    auto startH = chrono::high_resolution_clock::now();
	for (int i = 0; i < 19; i++){
		vector<Phonebook> trial = heapSortVector;
		heapsort(trial);
	}
    heapsort(heapSortVector);
    auto HTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startH);
    cout << "Heap Sort Time: " << HTime.count() / 20.0 << " Nanoseconds"<< endl;
    
    cout << endl;
   
    
	//If the search is not a partial search.
    if (wantedSurname.length()!=0) {
        cout << "Searching for " << wantedName << " " <<wantedSurname<< endl;
        cout << "======================================"<< endl;
         
		//The value that we are searching for.
        string key = wantedName+wantedSurname;

		//Inially, I set them as not found.
        int locationFromBinarySearch=-1;
        int locationFromSequentialSearch=-1;

		//Number of trials for searching.
        int N=1000;
        
		//Calculations of the average timing for binary search (in 1000 trials).
        auto startB = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++)
            locationFromBinarySearch= bsearch(insertionSortVector, key);
        auto BTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startB);
        
        //Calculations of the average timing for sequential search (in 1000 trials).
        auto startS = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++)
            locationFromSequentialSearch =sequentialSearch(insertionSortVector, key);
        auto STime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startS);
        
        //If the input data does not exist in the dataset (This is for binary search).
        if (locationFromBinarySearch==-1) {
            ToUpper(wantedName);
            ToUpper(wantedSurname);
            cout << wantedName << " " << wantedSurname << " does NOT exist in the dataset"<<endl;
            cout << "Binary Search Time: " << BTime.count()/ N << " Nanoseconds" << endl;
            cout << endl;
            
        }
		//If the input data exists in the dataset (This is for binary search).
        else{
            ToUpper(wantedName);
            ToUpper(wantedSurname);
            cout << wantedName << " " << wantedSurname <<" "<< insertionSortVector[locationFromBinarySearch].phone << " " << insertionSortVector[locationFromBinarySearch].city << endl;
            cout << "Binary Search Time: " << BTime.count()/ N << " Nanoseconds" << endl;
            cout << endl;
            
        }
		//If the input data does not exist in the dataset (This is for sequential search).
        if (locationFromSequentialSearch==-1) {
            cout << "Search results for Sequential Search:"<<endl;
            ToUpper(wantedName);
            ToUpper(wantedSurname);
            cout << wantedName << " " << wantedSurname << " does NOT exist in the dataset"<<endl;
            cout << endl;
            cout << "Sequential Search Time:: " << STime.count()/ N << " Nanoseconds" << endl;
        }
		//If the input data exists in the dataset (This is for sequential search).
        else{
            cout << "Search results for Sequential Search:"<<endl;
            ToUpper(wantedName);
            ToUpper(wantedSurname);
            cout << wantedName << " " << wantedSurname << " "<< insertionSortVector[locationFromBinarySearch].phone << " " << insertionSortVector[locationFromBinarySearch].city << endl;
            cout << "Sequential Search Time: " << STime.count()/ N << " Nanoseconds" << endl;
        }

		//Displaying speed-ups.
        cout << endl;
        cout << "SpeedUp between Search Algorithms"<<endl;
        cout << "======================================"<< endl;
        cout <<"(Sequential Search/ Binary Search) SpeedUp = " << double(STime.count()) / BTime.count() << endl;
        cout << endl;
        cout << "SpeedUps between Sorting Algorithms"<<endl;
        cout << "======================================"<< endl;
        cout << "(Insertion Sort/ Quick Sort) SpeedUp = "<< double(ITime.count()) / QTime.count()<< endl;
        cout << "(Merge Sort / Quick Sort) SpeedUp = "<< double(MTime.count()) / QTime.count() << endl;
        cout << "(Heap Sort / Quick Sort) SpeedUp = "<< double(HTime.count()) / QTime.count() <<endl;
    }
	//If the search is a partial search.
    else{

		//Vectors for storing partial search indexes.
        vector<int> LocationsInSequential;
        vector<int> LocationsInBinary;
        
        cout << "Searching for " << wantedName << " " <<wantedSurname << endl;
        cout << "======================================"<< endl;
        
		//The partial value that we are searching for.
        string key = wantedName+wantedSurname;

		//Number of trials for searching.
        int N=1000;
        
        //Calculations of the average timing for partial binary search (in 1000 trials).
        auto startB = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++)            
			LocationsInBinary = bsearchWithPartial(insertionSortVector, wantedName);
        auto BTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startB);
        
        
        //Calculations of the average timing for partial sequential search (in 1000 trials).        
        auto startS = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++)           
			LocationsInSequential = sequentialSearchWithPartial(insertionSortVector, wantedName);
        auto STime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startS);
        
        //If the input data does not exist in the dataset (This is for partial binary search).
        if (LocationsInBinary.size()==0) {
            ToUpper(wantedName);
            ToUpper(wantedSurname);
            cout << wantedName << " " << wantedSurname << " does NOT exist in the dataset"<<endl;
            cout << "Binary Search Time: " << BTime.count()/ N << " Nanoseconds" << endl;
            cout << endl;
            
        }
		//If the input data exists in the dataset (This is for partial binary search).
        else{
            ToUpper(wantedName);
            ToUpper(wantedSurname);
            for (int i=0; i<LocationsInBinary.size(); i++) {
                int location = LocationsInBinary[i];
                string fname =insertionSortVector[location].firstName;
                ToUpper(fname);
                string lname =insertionSortVector[location].lastName;
                ToUpper(lname);
                 cout << fname << " " << lname << " "<< insertionSortVector[location].phone << " " << insertionSortVector[location].city << endl;
            }
            cout << "Binary Search Time: " << BTime.count()/ N << " Nanoseconds" << endl;
            cout << endl;
            
        }
       
        //If the input data does not exist in the dataset (This is for partial sequential search).
        if (LocationsInSequential.size()==0) {
            cout << "Search results for Sequential Search:"<<endl;
            ToUpper(wantedName);
            ToUpper(wantedSurname);
            cout << wantedName << " " << wantedSurname << " does NOT exist in the dataset"<<endl;
            cout << endl;
            cout << "Sequential Search Time: " << STime.count()/ N << " Nanoseconds" << endl;
        }
		//If the input data exists in the dataset (This is for partial sequential search).
        else{
            cout << "Search results for Sequential Search:"<<endl;
            ToUpper(wantedName);
            ToUpper(wantedSurname);
            for (int i=0; i<LocationsInSequential.size(); i++) {
                int location = LocationsInSequential[i];
                string fname =insertionSortVector[location].firstName;
                ToUpper(fname);
                string lname =insertionSortVector[location].lastName;
                ToUpper(lname);
                 cout << fname << " " << lname << " "<< insertionSortVector[location].phone << " " << insertionSortVector[location].city << endl;
            }
            cout << "Sequential Search Time: " << STime.count()/ N << " Nanoseconds" << endl;
        }

		//Displaying speed-ups.
        cout << endl;
        cout << "SpeedUp between Search Algorithms"<<endl;
        cout << "======================================"<< endl;
        cout <<"(Sequential Search/ Binary Search) SpeedUp = " << double(STime.count()) / BTime.count() << endl;
        cout << endl;
        cout << "SpeedUps between Sorting Algorithms"<<endl;
        cout << "======================================"<< endl;
        cout << "(Insertion Sort/ Quick Sort) SpeedUp = "<< double(ITime.count()) / QTime.count()<< endl;
        cout << "(Merge Sort / Quick Sort) SpeedUp = "<< double(MTime.count()) / QTime.count() << endl;
        cout << "(Heap Sort / Quick Sort) SpeedUp = "<< double(HTime.count()) / QTime.count() <<endl;
        
    }

    return 0;
}



