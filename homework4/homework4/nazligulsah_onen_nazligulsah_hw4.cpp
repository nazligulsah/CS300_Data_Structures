//
//  main.cpp
//  homework4
//
//  Created by Gülşah Önen on 19.05.2021.
//

#include <iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include <ctime>
#include <chrono>

using namespace std;
struct Phonebook{
    string fullname;     // to sort alpthetical and search i need
    string phone;
    string city;
};

void openFile(string filename, ifstream &input, vector<Phonebook> &vec){
    string name,surname,phone,city;
    string line;
    Phonebook subject;
    input.open(filename.c_str());
    if(input.fail()){
        cout << "file cannot opened!" << endl;  // check  is file  open
    }
    else{
        while(getline(input,line)){
            stringstream ss(line);
            ss >> name >> surname >> phone >> city ;
            subject.fullname = name +" " + surname;   // create fullname
            for (int x=0; x<subject.fullname.length(); x++)
                    subject.fullname[x] = toupper(subject.fullname[x]);
            subject.phone = phone;
            subject.city = city;
            vec.push_back(subject);
        }
    }
    input.close();
}

// insertion sort depend on fullname
template <typename Comparable>
void insertionSort (vector <Comparable> & a)
{
    int j;
    // loop over the passes
    for (int p = 1;  p < a.size(); p++)
    {
        Comparable tmp = a[p];
        // loop over the elements
        for (j = p; j > 0 &&  tmp.fullname < a[j-1].fullname; j--)
            a[j] = a[j -1];
        a[j] = tmp;
    }
}
// swap for heap sort
template <typename Comparable>
inline void swap( Comparable & obj1,
                 Comparable & obj2 )
{
    Comparable tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}
inline int leftChild( int i )
{
    return 2*i+1;
}

template <typename Comparable>  // for deleteMax
// a is the array, i is the position to percolate down from
// n is the logical size of the array
void percDown( vector<Comparable> & a, int i, int n )
{
    int child;
    Comparable tmp;
    for (tmp=a[i] ; leftChild(i) < n; i = child )
    {
        child = leftChild(i);
        if ( child != n-1 && a[ child  ].fullname < a[ child+1 ].fullname )
            child++;
        if ( a[child ].fullname > tmp.fullname )
            a[i] = a[ child ];
        else
            break;
    }
    a[ i ] = tmp;
}

template <typename Comparable>
void heapSort(vector<Comparable> & a)
{
    // buildHeap
    for ( int i = a.size()/2; i >=0; i--)
        percDown(a, i, a.size());

    // sort
    for ( int j = a.size() -1; j >0; j--)
    {
        std::swap(a[0], a[j]); // swap max to the last pos.
        percDown(a, 0, j); // re-form the heap
    }
}
template <typename Comparable>
void merge(vector<Comparable> & arr, int start, int mid, int end)
{
    int start2 = mid + 1;
    if (arr[mid].fullname <= arr[start2].fullname) {
        return;
    }
    while (start <= mid && start2 <= end) {
        if (arr[start].fullname <= arr[start2].fullname) {
            start++;
        }
        else {
            Comparable value = arr[start2];
            int index = start2;
            while (index != start) {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[start] = value;
            // Update all the pointers
            start++;
            mid++;
            start2++;
        }
    }
}
template <typename Comparable>
void mergeSort(vector<Comparable> & arr, int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
template <typename Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    for ( int p = left + 1; p <= right; p++ )
    {
        Comparable tmp = a[ p ];
        int j;

        for ( j = p; j > left && tmp.fullname < a[ j - 1 ].fullname; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}

template <typename Comparable>
const Comparable & median( vector<Comparable> & a,
                          int left, int right )
{
    Comparable tmp;
    int center = ( left + right ) / 2;
    if ( a[ center ].fullname < a[ left ].fullname ){
        std::swap(a[center], a[left]); }
    if ( a[ right ].fullname < a[ left ].fullname ){
        std::swap(a[right], a[left]); }
    if ( a[ right ].fullname < a[ center ].fullname){
        std::swap(a[right], a[center]); }

    // Place pivot at position right - 1
    std::swap(a[center], a[right-1]);
    return a[ right - 1 ];
}

template <typename Comparable>
void quicksort( vector<Comparable> & a, int left, int right )
{
    if ( left + 10 <= right )
    {
        Comparable pivot = median( a, left, right );
        // Begin partitioning
        int i = left, j = right - 1;
        for ( ; ; )
        {
            while ( a[ ++i ].fullname < pivot.fullname ) { }
            while ( pivot.fullname < a[ --j ].fullname ) { }
            if ( i < j ){
                std::swap(a[i], a[j]); }
            else
                break;
        }
        std::swap(a[i], a[right-1]);
        // Restore pivot

        quicksort( a, left, i - 1 );       // Sort small elements
        quicksort( a, i + 1, right );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

template <typename Comparable>
void quickSort( vector<Comparable>  &a )
{
    quicksort( a, 0, a.size( ) - 1 );
}
// sorting vector and time
template <typename T>
void sortingVectors(vector<Phonebook> &quickVec, vector<Phonebook> &mergeVec, vector<Phonebook> &heapVec,
                    vector<Phonebook> &insertVec, T &qtime, T &mtime, T &htime, T &itime){

                        cout<<endl<<"Sorting the vector copies" <<endl<<
                            "======================================"<<endl;

                        auto startTime1=std::chrono::high_resolution_clock::now();
                        quickSort(quickVec);
                        auto endTime1=std::chrono::high_resolution_clock::now();
                        auto qutime=(std::chrono::duration_cast<std::chrono::nanoseconds>(endTime1 - startTime1).count());
                        qtime=qutime;

                        auto startTime2=std::chrono::high_resolution_clock::now();
                        mergeSort(mergeVec, 0, mergeVec.size()-1);
                        auto endTime2=std::chrono::high_resolution_clock::now();
                        auto metime=(std::chrono::duration_cast<std::chrono::nanoseconds>(endTime2 - startTime2).count());
                        mtime=metime;

                        auto startTime3=std::chrono::high_resolution_clock::now();
                        heapSort(heapVec);
                        auto endTime3=std::chrono::high_resolution_clock::now();
                        auto hetime=(std::chrono::duration_cast<std::chrono::nanoseconds>(endTime3 - startTime3).count());
                        htime=hetime;

                        auto startTime4=std::chrono::high_resolution_clock::now();
                        insertionSort(insertVec);
                        auto endTime4=std::chrono::high_resolution_clock::now();
                        auto intime=(std::chrono::duration_cast<std::chrono::nanoseconds>(endTime4 - startTime4).count());
                        itime=intime;

                        cout<<"Quick Sort Time: "<<qtime<<" Nanoseconds"<<endl
                            <<"Insertion Sort Time: "<<itime<<" Nanoseconds"<<endl
                            <<"Merge Sort Time: "<<mtime<<" Nanoseconds"<<endl
                            <<"Heap Sort Time: "<<htime<<" Nanoseconds"<<endl;
}
void speedUpSorting (long long int &qtime, long long int &mtime, long long int &htime, long long int& itime){
    cout<<endl<<"SpeedUps between Sorting Algorithms"<<endl<<"======================================"<<endl;
    cout<<"(Insertion Sort/ Quick Sort) SpeedUp = "<<(double)itime/(double)qtime<<endl;
    cout<<"(Merge Sort / Quick Sort) SpeedUp = "<<(double)mtime/(double)qtime<<endl;
    cout<<"(Heap Sort / Quick Sort) SpeedUp = "<<(double)htime/(double)qtime<<endl;
}
// is it can be searchable search=Gulsen Demiröz name = Gulsen Demir
bool isSearh(string name, string search){
    if(name.length() >= search.length()){
        return true;
    }
    return false;
}
template <typename Comparable>
vector<int> binarySearch(vector<Comparable> &arr, int l, int r, string x, vector<int> &found)
{
    for (int i=0; i<x.length(); i++)
            x[i] = toupper(x[i]);
   if (r >= l ) {
        int mid = l + (r - l) / 2;
        if (arr[mid].fullname.substr(0,x.length()) == x && isSearh(arr[mid].fullname.substr(0,x.length()), x)) {
            found.push_back(mid); //we need to search around with for loops
           
            for (int i=1; arr[mid+i].fullname.substr(0,x.length()) == x &&  isSearh(arr[mid+1].fullname.substr(0,x.length()), x) && i<arr.size(); i++)
                found.push_back(mid+i);
           
            for (int j=1; arr[mid-j].fullname.substr(0,x.length()) == x &&  isSearh(arr[mid-j].fullname.substr(0,x.length()), x)&& mid-j>0; j++)
                found.push_back(mid-j);
            
            return found;}
        else if (arr[mid].fullname.substr(0,x.length()) > x &&  isSearh(arr[mid].fullname.substr(0,x.length()), x))
            return binarySearch(arr, l, mid - 1, x, found);

        else return binarySearch(arr, mid + 1, r, x, found);
    }
   
    return found;
}
template <typename Comparable>
vector<int> sequentialSearch(vector<Comparable> &arr, string x, vector<int> &found){
    for (int i=0; i<x.length(); i++)
            x[i] = toupper(x[i]);
    for(int i=0; i < arr.size() ; i++){
        if(arr[i].fullname.substr(0,x.length()) == x && isSearh(arr[i].fullname.substr(0,x.length()), x)){
            found.push_back(i);
        }
    }
    return found;
}

void searchingName(string search, vector<Phonebook> &sortedArray ,long long int &btime, long long int &stime){
    int N=1000;
   
    cout<<endl<<"Searching for " << search <<endl<<
        "======================================" << endl;
    vector<int> bs;
    auto startTime1=std::chrono::high_resolution_clock::now();
    for (int i=0; i<N; i++)
        binarySearch(sortedArray, 0, sortedArray.size()-1, search, bs);
    auto endTime1=std::chrono::high_resolution_clock::now();
    auto vectime=(std::chrono::duration_cast<std::chrono::nanoseconds>(endTime1 - startTime1).count())/N;
    btime=vectime;
    
    cout << "Search results for Binary Search:" << endl;
    vector<int> j;
    binarySearch(sortedArray, 0, sortedArray.size()-1, search, j);
    sort(j.begin(), j.end());
    if(j.size() == 0){
        for (int x=0; x<search.length(); x++)
                search[x] = toupper(search[x]);
        cout << search << " does NOT exist in the dataset" << endl;
    }
    else{
    for(int i=0; i < j.size() ; i++){
          cout << sortedArray[j[i]].fullname << " "<< sortedArray[j[i]].phone << " " <<sortedArray[j[i]].city << endl;
         }
    }
    cout << endl << "Binary Search Time: " << btime << " Nanoseconds" << endl;
    
    
    vector<int> ss;
    auto startTime2=std::chrono::high_resolution_clock::now();
    for (int i=0; i<N; i++)
        sequentialSearch(sortedArray, search, ss);
    auto endTime2=std::chrono::high_resolution_clock::now();
    auto vtime=(std::chrono::duration_cast<std::chrono::nanoseconds>(endTime2 - startTime2).count())/N;
    stime=vtime;
    
    cout << endl << "Search results for Sequential Search:" << endl;
    vector<int> i;
    sequentialSearch(sortedArray, search, i);
   
    if(i.size() == 0){
        for (int x=0; x<search.length(); x++)
                search[x] = toupper(search[x]);
        cout << search << " does NOT exist in the dataset" << endl;
    }
    else{
    for(int j=0; j < i.size() ; j++){
          cout << sortedArray[i[j]].fullname << " "<< sortedArray[i[j]].phone << " " <<sortedArray[i[j]].city << endl;
         }
    }
    cout << endl << "Sequential Search Time: " << stime << " Nanoseconds" << endl;
    
    cout<<endl<<"SpeedUp between Search Algorithms " << endl<<
        "======================================" << endl;
    cout <<"(Sequential Search/ Binary Search) SpeedUp = " << double(stime)/double(btime) << endl;
}


int main() {
    string filename;
    string search;
    ifstream input;
    long long int itime, qtime, mtime, htime, btime, stime;
    vector<int> j, i;
    vector<Phonebook> insertionVec;
    vector<Phonebook> quickVec;
    vector<Phonebook> mergeVec;
    vector<Phonebook> heapVec;
   
    
    cout << "Please enter the contact file name: "<< endl;
    cin >> filename;
   
    openFile(filename, input,insertionVec);
   // insertionSort(insertionVec);
    openFile(filename, input,quickVec);
   // quickSort(quickVec);
    openFile(filename, input,mergeVec);
   // mergeSort(mergeVec, 0, mergeVec.size()-1);
    openFile(filename, input,heapVec);
  //  heapSort(heapVec);
   
    cout << "Please enter the word to be queried :" << endl;
    getline(cin, search);
    getline(cin, search);
    sortingVectors(quickVec, mergeVec, heapVec, insertionVec, qtime, mtime, htime, itime);
    searchingName(search, quickVec ,btime, stime);
    // seed up for sorting
    speedUpSorting(qtime, mtime, htime, itime);
    return 0;
}

