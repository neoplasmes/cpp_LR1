#include <iostream>
#include <random>
#include <iomanip>
#include <cstdlib>

using namespace std;

random_device dev;
mt19937 gen(dev());
int random_int(int min, int max){
    uniform_int_distribution<> dist(min,max);

    return dist(gen);
}

template <typename T>
void singlePrint(T a){
    cout << a << "\n";
}

template <typename T>
void mySwap(T &a, T &b){
    T memo = a;
    a = b;
    b = memo;
}

template <typename T>
void printArr(vector<T> arr){
    int lenght = arr.size();
    for (int i = 0; i < lenght; i++){
        cout << arr.at(i) << " ";
    }
    cout << "\n";
}


//Quicksort
template <typename T>
int split(vector<T> &arr, int start, int end) {
    int randIndex = random_int(start, end);
    //int pivot = arr.at(randIndex);
    //mySwap(arr.at(randIndex), arr.at(end));
    int pivot = arr.at(end);

    int i = 0;
    for (int scan = 0; scan < end; scan++){
        if(arr.at(scan) <= pivot){
            mySwap(arr.at(scan), arr.at(i));
            i++;
        }
    }

    mySwap(arr.at(i), arr.at(end));

    return i;
}

template <typename T>
void quicksort(vector<T> &arr, int start, int end){
    //srand(time(0));
    if(end > start) {
        int splitIndex = split(arr, start, end);

        quicksort(arr, start, splitIndex - 1);
        quicksort(arr, splitIndex, end);
    }
}
//End of quicksort




//Binary insertion sort
template <typename T>
int binarySearch(vector<T> arr, T item, int start, int end) {
    if (end <= start)
        return (item > arr.at(start)) ? (start + 1) : start;

    int mid = (start + end) / 2;
 
    if (item == arr.at(mid))
        return mid + 1;
 
    if (item > arr.at(mid)){
        return binarySearch(arr, item, mid + 1, end);
    } else {
        return binarySearch(arr, item, start, mid - 1);
    }
}

template <typename T>
void binaryInsertionSort(vector<T> &arr, int lenght, int left = 0, int right = -1) {
    int j, key, position;
    right = (right == -1) ? (lenght) : right;

    for (int i = left+1; i < right; i++) {
        key = arr.at(i);
        if(key > arr.at(i - 1)) continue;

        j = i - 1;
        position = binarySearch(arr, key, left, j);
        while(j >= position) {
            arr.at(j+1) = arr.at(j);
            j--;
        }      
        arr.at(j+1) = key;
    }
}
//End of binary insertion sort

//mergesort
template <typename T>
void merge(vector<T> &arr, int left, int mid, int right){
    int len1 = mid - left + 1;
    int len2 = right - mid;

    vector<T> sub1, sub2;
    for (int i = 0; i < len1; i++){
        sub1.push_back(arr.at(left + i));
    }
    for (int i = 0; i < len2; i++){
        sub2.push_back(arr.at(mid + 1 + i));
    }
    int i1 = 0, i2 = 0, origin = left;
    while ((i1 < len1) && (i2 < len2)) {
        if(sub1.at(i1) <= sub2.at(i2)){
            arr.at(origin) = sub1.at(i1);
            i1++;
        } else {
            arr.at(origin) = sub2.at(i2);
            i2++;
        }
        origin++;
    }

    //копируем остатки потому что например весь первый массив может быть меньше второго. остатки должны быть только у одного массива по идее.
    while(i1 < len1){arr.at(origin++) = sub1.at(i1++);}
    while(i2 < len2){arr.at(origin++) = sub2.at(i2++);}

}


template <typename T>
void mergesort(vector<T> &arr, int left, int right){
    /*if((right - left + 1) <= 32){
        binaryInsertionSort(arr, 0, left, right + 1);
        return;
    }*/
    if(left >= right) return;

    int mid = left + (right - left) / 2;
    mergesort(arr, left, mid);
    mergesort(arr, mid+1, right);
    merge(arr, left, mid, right);
}


vector<int> createRandomVectorInt(int lenght){
    vector<int> arr;

    for (int i = 0; i < lenght; i++){
        arr.push_back(random_int(0, 100000));
    }

    return arr; 
}

int main(){
    vector<int> test1 = createRandomVectorInt(25);
    vector<int> test2 = createRandomVectorInt(25);
    vector<int> test3 = createRandomVectorInt(120);

    cout << "Показываю, что оно сортирует\n\nvector before quicksort: \n";
    printArr(test1);
    quicksort(test1, 0, test1.size() - 1);
    cout << "\nafter\n";
    printArr(test1);

    cout << "\n\nvector before binaryInsertionSort: \n";
    printArr(test2);
    binaryInsertionSort(test2, test2.size());
    cout << "\nafter\n";
    printArr(test2);

    cout << "\n\nvector before mergesort: \n";
    printArr(test3);
    mergesort(test3, 0, test3.size() - 1);
    cout << "\nafter\n";
    printArr(test3);
    cout << "\n\n\n";



    for (double i = 1; i < 11; i++){
        int len = (int)exp(i);
        vector<int> arr = createRandomVectorInt(len);
        clock_t time = clock();
        quicksort(arr, 0, arr.size() - 1);
        time = clock() - time;
        cout << "vector " << len << " elements long sorted with quicksort for ";
        cout << setprecision(15) << (float)time/CLOCKS_PER_SEC << "s\n";
    }

    cout << "\n\n\n";

    for (double i = 1; i < 10; i++){
        int len = (int)exp(i);
        vector<int> arr = createRandomVectorInt(len);
        clock_t time = clock();
        binaryInsertionSort(arr, arr.size());
        time = clock() - time;
        cout << "vector " << len << " elements long sorted with BinaryInsertionSort for ";
        cout << setprecision(15) << (float)time/CLOCKS_PER_SEC << "s\n";
    }

    cout << "\n\n\n";

    for (double i = 1; i < 11; i++){
        int len = (int)exp(i);
        vector<int> arr = createRandomVectorInt(len);
        clock_t time = clock();
        mergesort(arr, 0, len-1);
        time = clock() - time;
        cout << "vector " << len << " elements long sorted with mergesort for ";
        cout << setprecision(15) << (float)time/CLOCKS_PER_SEC << "s\n";
    }
}