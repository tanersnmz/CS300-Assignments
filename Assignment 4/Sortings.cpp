#include <vector>

using namespace std;

/*
These are the sorting algorithms that I took from the lecture slides with slight changes.
*/



/*
Internal insertion sort routine for subarrays
a is an array of Comparable items.
*/
template <class Comparable>
void insertionSort(vector <Comparable> & a)
{
	unsigned int j, p;
	for (p = 1; p < a.size(); p++)
	{
		Comparable tmp = a[p];
		for (j = p; j > 0 &&  tmp < a[j - 1]; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

//This is for heap sort.
inline int leftChild(const int & i)
{
	return 2 * i + 1;
}

//Standart swap function.
template <class Comparable>
inline void swapElements(Comparable & x, Comparable & y)
{
	Comparable temp = x;
	x = y;
	y = temp;
}


// for deleteMax
// a is the array, i is the position to percolate down from
// n is the logical size of the array
template <class Comparable>
void percDown(vector<Comparable> & a, int i, int n)
{
    int child;
    Comparable tmp;
    for (tmp = a[i]; leftChild(i) < n; i = child)
    {
        child = leftChild(i);
        if (child != n - 1 && a[child] < a[child + 1])
            child++;
        if (a[child] > tmp)
            a[i] = a[child];
        else
            break;
    } 
    a[i] = tmp;
}

//Heap Sort Algorithm.
template <class Comparable>
void heapsort(vector<Comparable> & a)
{
	// buildHeap
	for (int i = a.size()/2; i >= 0; i--)
		percDown(a, i, a.size());
	// sort
	for (int j = a.size() - 1; j > 0; j--)
	{
  	     swapElements(a[0], a[j]);// swap max to the last pos
         percDown(a, 0, j); // re-form the heap
	}
}


/*
This is an inplace merge sort.
Internal method that merges two sorted halves of a subarray.
a is an array of Comparable items.
leftPos is the left-most index of the subarray.
rightPos is the index of the start of the second half.
rightEnd is the right-most index of the subarray.
*/
template <class Comparable>
void merge(vector<Comparable>& a, int leftPos, int rightPos, int rightEnd) {

	int counter =0;
	int lastTermIdxCheck=0;
	Comparable tempElement;
	int leftEnd = rightPos - 1;

	for (; leftPos <= leftEnd && rightPos <= rightEnd ; )
	{
		if(a[leftPos] <= a[rightPos]){
			counter++;
			leftPos++;
		}			
		else 
		{
			tempElement = a[leftPos];
			a[leftPos] = a[rightPos];
			for (int j = rightPos; j > leftPos; j--) a[j] = a[j - 1];							
			leftPos++;
			a[leftPos] = tempElement;			
			rightPos++;
			leftEnd++;
			counter--;
		}	
		lastTermIdxCheck++;
	}	
}


/*
Internal method that makes recursive calls.
a is an array of Comparable items.
left is the left-most index of the subarray.
right is the right-most index of the subarray.
*/
template <class Comparable>
void mergeSort(vector<Comparable>& a, int left, int right) {
	if (left < right) {
		int center = (left + right) / 2;
		mergeSort(a, left, center);
		mergeSort(a, center + 1, right);
		merge(a, left, center + 1, right);
	}
}


/*
Mergesort algorithm (driver).
*/
template <class Comparable>
void mergeSort(vector<Comparable>& a) {
	mergeSort(a, 0, a.size() - 1);
}


/*
This is for picking the pivot in the quick sort.
Return median of left, center, and right.
Order these and hide the pivot.
*/
template <class Comparable>
const Comparable & median3(vector<Comparable> & a, const int & left, const int & right)
{
	int center = (left + right) / 2;
	if (a[center] < a[left])
		swapElements(a[left], a[center]);
	if (a[right] < a[left])
		swapElements(a[left], a[right]);
	if (a[right] < a[center])
		swapElements(a[center], a[right] );
	swapElements(a[center], a[right - 1]);
	return a[right - 1];
}


/*
Internal insertion sort routine for subarrays
that is used by quicksort.
a is an array of Comparable items.
left is the left-most index of the subarray.
right is the right-most index of the subarray.
*/
template <class Comparable>
void insertionSort(vector<Comparable> & a, const int & left, const int & right)
{
	int j, p;
    for (p = left + 1; p <= right; p++)
    {
        Comparable tmp = a[p];
        for (j = p; j > left && tmp < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = tmp;
	}
}


/*
Internal quicksort method that makes recursive calls.
Uses median-of-three partitioning and a cutoff of 10.
a is an array of Comparable items.
left is the left-most index of the subarray.
right is the right-most index of the subarray.
*/
template <class Comparable>
void quicksortP(vector<Comparable> & a, const int &left, const int & right)
{
	if (left + 10 <= right)
	{
		Comparable pivot = median3(a, left, right);
		int i = left, j = right - 1;
        for (;;)
        {
            while (a[++i] < pivot) {}
            while (pivot < a[--j]) {}
            if (i < j)
				swapElements(a[i], a[j]);
            else
				break;
        }

		swapElements(a[i], a[right - 1]);
		quicksortP(a, left, i - 1);
		quicksortP(a, i + 1, right);
	}
	else
		insertionSort(a, left, right);
}


//It calls internal quicksort method.
template <class Comparable>
void quicksort(vector<Comparable> & a)
{
	quicksortP(a, 0, a.size() - 1);
}
