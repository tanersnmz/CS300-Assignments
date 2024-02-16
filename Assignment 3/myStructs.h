#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

#include <string>
#include <vector>

using namespace std;

//These are the structs that I created for storing the data.

struct DocumentItem {

	string documentName; 
	int count; 

	bool operator<( const DocumentItem & other) const{
		return (documentName<other.documentName) ;
    }
 
    bool operator>(const DocumentItem & other) const {
        return (documentName > other.documentName);
    }

	 bool operator!=(const DocumentItem & other) const {
        return (documentName != other.documentName);
    }

	 bool operator==(const DocumentItem & other) const {
        return (documentName == other.documentName);
    }

};
struct WordItem {

	string word; 
	vector<DocumentItem> listOfDocuments; 


	bool operator<( const WordItem & other) const{
		return (word<other.word) ;
    }
 
    bool operator>(const WordItem & other) const {
        return (word > other.word);
    }

	 bool operator!=(const WordItem & other) const {
        return (word != other.word);
    }

	 bool operator==(const WordItem & other) const {
        return (word == other.word);
    }
};

#endif