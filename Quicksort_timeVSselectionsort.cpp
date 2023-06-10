
// problem 9.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<ctime>
#include<iomanip>
class Sorter {
public:
    virtual int  sorter( int arr[], int size) =0;
};
class QuickSort:public Sorter{
public:
    int partition1(int arr[], int l, int h)
    {
        int p = arr[l];
        int i = l;
        int j = h;
        while (i < j)
        {
            do
            {
                i++;
            } while (arr[i] <= p);
            do
            {
                j--;
            } while (arr[j] > p);

            if (i < j)
                swap(arr[i], arr[j]);
        }
        swap(arr[l], arr[j]);
        return j;
    }

    void quickSort1(int arr[], int l, int h)
    {

        if (l < h) {
            int piv = partition1(arr, l, h);
            quickSort1(arr, l, piv);
            quickSort1(arr, piv + 1, h);
        }

    }
    int  sorter(int arr[], int size) {
        quickSort1(arr, 0, size);
        
        return 0;
    }
    

};
class testbed {
public:
    int* arr;
    int** arr2;
    int set_num1;
    clock_t RunOnce(Sorter* a, int data[], int size) {
        cout << "time will be in miliseconds" << endl;
        clock_t start_time = clock();
        a->sorter(data, size);
        clock_t end_time = clock();
        clock_t res = end_time - start_time;

        return res * 1000;

    }
    clock_t RunAndAvarage(Sorter* a, string type, int min, int max, int Size, int set_num) {
        arr2=new int *[set_num];
        set_num1 = set_num;


        for (int i = 0;i < set_num;i++) {
            
            arr2[i] = new int [Size];
        }
        if (type == "random"||type=="Random")
            for (int i = 0;i < set_num;i++) {
               arr2[i] = this->GenerateRandomList(min, max, Size);
            }
        else if (type == "reverse" || type == "Reverse") {
            for (int i = 0;i < set_num;i++) {
                arr2[i] = this->GenerateReverseOrderdList(min, max, Size);
            }
        }
        clock_t start = clock();
        for (int i = 0;i < set_num;i++) {
            
            *arr2[i] = a->sorter(*arr2,Size);
        }
        clock_t end = clock();
        clock_t res = end - start;
        for (int i = 0; i < set_num; i++)
            delete[] arr2[i];
        delete[] arr2;
       
        return res * 1000;

        


    }
    
    int* GenerateRandomList(int min, int max, int size) {
       
        arr = new int[size];
        srand(time(0));
        for (int i = 0;i < size;i++) {
            arr[i]=(rand()%(max-min+1));
        }
        return arr;
        
    }
    int* GenerateReverseOrderdList(int min, int max, int size) {
        
        arr=new int[size];
        srand(time(0));
        for (int i = 0;i < size;i++) {
            arr[i]=(rand() % (max - min + 1));
        }
        
        int temp;
        int j = 0;
        for (int i = 0,  j = size - 1;i < size / 2;i++, j--) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }

            cout << endl;
        
      
        return arr;

    }
    void RunExperient(Sorter* a, string type, int min, int max, int min_val, int max_val, int sets_num, int step) {
        int first_test = 0;
        if (min_val < max_val) {
            
            first_test = this->RunAndAvarage(a, "Random", min, max, min_val, sets_num);
            cout << "SetSize:" << setw(15);
            cout << "Avarage time";
            cout << endl;
            cout << min_val << setw(15);
            cout << first_test;
            cout << endl;
        }
        else {
            cout << "Out of Range";
            return;
        }

        while (true) {

            if (min_val+step < max_val) {
                min_val += step;
                first_test = this->RunAndAvarage(a, "Random", min, max, min_val, sets_num);
                cout << min_val << setw(15);
                cout << first_test;
                cout << endl;
            }
            else
                break;
        }

    }
    
    ~testbed() {
        delete[] arr;
        for (int i = 0; i < set_num1; i++)
            delete[] arr2[i];
        delete[] arr2;
    }
};
class selectionSort :public Sorter {
public:
    int leaset=0;
    int sorter(int arr[], int size) {
        for (int i = 0;i < size - 1;i++) {
            leaset = i;
            for (int j = i + 1;j < size;j++)
                if (arr[j] < arr[leaset])
                    leaset = j;
            swap(arr[i], arr[leaset]);
        }
        return *arr;
    }
    

};

int main() {
    testbed t;
    Sorter* s = new QuickSort();
    
    
    t.RunExperient(s, "random", 1, 100000, 1,100000 , 5,5000 );
    


    



    return 0;
    }
    


