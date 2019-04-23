/* Name: Tran Anh Loc
Date: Friday, April 5, 2019
*/
#include <iostream>
#include <sys/time.h>
#include <vector>
#include <fstream>

using namespace std;

/* Function prototypes */
void selectionSort(vector<int> & vec);
int findSmallest(vector<int> & vec, int p1, int p2);
void swap(int & x, int & y);

void insertionSort(vector<int> & vec);

void mergeSort(vector<int> & vec);
void merge(vector<int> & vec, vector<int> & v1, vector<int> & v2);

void quickSort (vector<int>& vec);
void sort(vector<int>& vec, int start, int finish);
int partition(vector<int>& vec, int start, int finish);

/* Main function
 * Create a new csv file to store all the results
 * The reason why i choose csv file is it's the file format that i can use
 * in my graphing tool (R Studio)
*/
int main()
{
  cout << "Because of the large test size, this program will take long time to run" << endl;
  cout << "Click on the testresult.csv file in the folder to see the progress of the test" << endl;
  cout << "This program will print out done at the end of the test" << endl;
  timeval timeBefore, timeAfter; // timeval type defined in sys/time.h
  long diffSeconds, diffUSeconds; // elapsed seconds and microseconds
  double time;
  ofstream output("testresult.csv");
  output << "Type" << "," << "Length" << "," << "Time" << endl;
  // for loop to increase the size of the test vector
  for( int j = 1000; j <= 100000; j = j + 1000 )
  {
    vector<int> vec(j);
    vector<int> vec1(j);
    vector<int> vec2(j);
    vector<int> vec3(j);
    // create four new vectors with random number inside it with the
    // pre assigned size
    for( int i = 0; i < j; ++i ) {
    // have to creates 4 vectors to avoid previously sorted list
        vec[i] = rand();
        vec1[i] = rand();
        vec2[i] = rand();
        vec3[i] = rand();
    }
    // test all the sorting algorithm

    gettimeofday(&timeBefore, NULL); // get the time before
    mergeSort(vec2);
    gettimeofday(&timeAfter, NULL); // get the time after
    diffSeconds = timeAfter.tv_sec - timeBefore.tv_sec; // elapsed seconds
    diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec; // elapsed microseconds
    time = diffSeconds + diffUSeconds / 1000000.0; // total elapsed time
    output << "Merge Sort" << "," << j << "," << time << endl;
    //
    gettimeofday(&timeBefore, NULL); // get the time before
    quickSort(vec3);
    gettimeofday(&timeAfter, NULL); // get the time after
    diffSeconds = timeAfter.tv_sec - timeBefore.tv_sec; // elapsed seconds
    diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec; // elapsed microseconds
    time = diffSeconds + diffUSeconds / 1000000.0; // total elapsed time
    output << "Quick Sort" << "," << j << "," << time << endl;

    gettimeofday(&timeBefore, NULL); // get the time before
    selectionSort(vec);
    gettimeofday(&timeAfter, NULL); // get the time after
    diffSeconds = timeAfter.tv_sec - timeBefore.tv_sec; // elapsed seconds
    diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec; // elapsed microseconds
    time = diffSeconds + diffUSeconds / 1000000.0; // total elapsed time
    output << "Selection Sort" << "," << j << "," << time << endl;

    gettimeofday(&timeBefore, NULL); // get the time before
    insertionSort(vec1);
    gettimeofday(&timeAfter, NULL); // get the time after
    diffSeconds = timeAfter.tv_sec - timeBefore.tv_sec; // elapsed seconds
    diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec; // elapsed microseconds
    time = diffSeconds + diffUSeconds / 1000000.0; // total elapsed time
    output << "Insertion Sort" << "," << j << "," << time << endl;

  }
  cout << "Done" << endl;
  output.close();
  return 0;
}

/*
 * Function: selectionSort
 * --------------
 * Sorts a Vector<int> into increasing order.  This implementation
 * uses an algorithm called selection sort, which can be described
 * in English as follows.  With your left hand (lh), point at each
 * element in the vector in turn, starting at index 0.  At each
 * step in the cycle:
 *
 * 1. Find the smallest element in the range between your left
 *    hand and the end of the vector, and point at that element
 *    with your right hand (rh).
 *
 * 2. Move that element into its correct position by swapping
 *    the elements indicated by your left and right hands.
*/
void selectionSort(vector<int> & vec) {
   for ( int lh = 0 ; lh < vec.size() ; lh++ ) {
      int rh = findSmallest(vec, lh, vec.size() - 1);
      swap(vec[lh], vec[rh]);
   }
}

/*
 * Function: findSmallest
 * ----------------------
 * Returns the index of the smallest value in the vector between
 * index positions p1 and p2, inclusive.
*/
int findSmallest(vector<int> & vec, int p1, int p2) {
   int smallestIndex = p1;
   for ( int i = p1 + 1 ; i <= p2 ; i++ ) {
      if (vec[i] < vec[smallestIndex]) smallestIndex = i;
   }
   return smallestIndex;
}

/*
 * Function: swap
 * --------------
 * Exchanges two integer values passed by reference.
*/
void swap(int & x, int & y) {
   int temp = x;
   x = y;
   y = temp;
}

/*
 * Function: insertionSort
 * ---------------
 *
 *
 *
 *
 *
 */

void insertionSort(vector<int> & vec)
{
  int size = vec.size();
  for(int i=1; i<size; i++)
  {
    int index=i-1;
    int originalValue=vec[i];//while originalValueue is greater
    while(index>=0 && vec[index]>originalValue)
    {
      vec[index+1]=vec[index];
      index--;
    }
    vec[++index]=originalValue;
  }
}


/*
 * The merge sort algorithm consists of the following steps:
 *
 * 1. Divide the vector into two halves.
 * 2. Sort each of these smaller vectors recursively.
 * 3. Merge the two vectors back into the original one.
*/
void mergeSort(vector<int> & vec) {
   int n = vec.size();
   if (n <= 1) return;
   vector<int> v1;
   vector<int> v2;
   for (int i = 0; i < n; i++) {
      if (i < n / 2) {
         v1.push_back(vec[i]);
      } else {
         v2.push_back(vec[i]);
      }
   }
   mergeSort(v1);
   mergeSort(v2);
   vec.clear();
   merge(vec, v1, v2);
}

/*
 * Function: merge
 * ---------------
 * This function merges two sorted vectors (v1 and v2) into the
 * vector vec, which should be empty before this operation.
 * Because the input vectors are sorted, the implementation can
 * always select the first unused element in one of the input
 * vectors to fill the next position.
*/
void merge(vector<int> & vec, vector<int> & v1, vector<int> & v2) {
   int n1 = v1.size();
   int n2 = v2.size();
   int p1 = 0;
   int p2 = 0;
   while (p1 < n1 && p2 < n2) {
      if (v1[p1] < v2[p2]) {
         vec.push_back(v1[p1++]);
      } else {
         vec.push_back(v2[p2++]);
      }
   }
   while (p1 < n1) vec.push_back(v1[p1++]);
   while (p2 < n2) vec.push_back(v2[p2++]);
}

/*
 * Function: quickSort
 * This function sort the elements of the vector into
 * increasing numerical order using the quicksort algorithm.
 * In this implementation, sort is a wrapper function that calls
 * quickSort to do all the work
*/

void quickSort (vector<int>& vec){
  sort(vec, 0, vec.size() - 1);
}

void sort(vector<int>& vec, int start, int finish){
  if (start >= finish) return;
  int boundary = partition(vec, start, finish);
  sort(vec, start, boundary - 1);
  sort(vec, boundary + 1, finish);
}

int partition(vector<int>& vec, int start, int finish){
  int pivot = vec[start];
  int lh = start + 1;
  int rh = finish;
  while(true){
    while (lh < rh && vec[rh] >= pivot) rh--;
    while (lh < rh && vec[lh] < pivot) lh++;
    if (lh == rh) break;
    int tmp = vec[lh];
    vec[lh] = vec[rh];
    vec[rh] = tmp;
  }
  if (vec[lh] >= pivot) return start;
  vec[start] = vec[lh];
  vec[lh] = pivot;
  return lh;
}
