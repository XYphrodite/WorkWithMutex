#include <iostream>
#include<thread>
#include<chrono>
#include<mutex>
#include<Windows.h>
using namespace std;

mutex mtx;
mutex mtx2;

class Var {
    //int number;
    int V;
public:
    int getV() {
        mtx2.lock();
        V++;
        mtx2.unlock();
        return V;

    }

};

class Arr
{
public:
    Arr(int size, Var* v) {
        this->size = size;
        arr = new int[size];
        this->v = v;
    };
    ~Arr() {
        delete[] arr;
    };

    void fillArr() {
        //mtx.lock();
        for (int i = 0; i < size; i++) {
            Sleep(20);

            int a = v->getV();
            
            //fill(a, i);
            arr[i] = a;
            
        }
        //mtx.unlock();
    };

    int* getArr() {
        return arr;
    };

private:
    int size;
    int* arr;
    Var* v;
    void fill(int a,int n) {
        //mtx.lock();
        arr[n] = a;
        //mtx.unlock();
    }
};


int main()
{
    int size = 50;
    Var* v = new Var();
    Arr* arr1 = new Arr(size, v);
    Arr* arr2 = new Arr(size, v);
    Arr* arr3 = new Arr(size, v);
    Arr* arr4 = new Arr(size, v);
    //arr1->fillArr();
    //arr2->fillArr();
    //arr3->fillArr();
    thread td1(&Arr::fillArr, arr1);
    thread td2(&Arr::fillArr, arr2);
    thread td3(&Arr::fillArr, arr3);
    thread td4(&Arr::fillArr, arr4);
    td1.join();
    td2.join();
    td3.join();
    td4.join();
    //system("Pause");
    int* arr_1 = arr1->getArr();
    int* arr_2 = arr2->getArr();
    int* arr_3 = arr3->getArr();
    int* arr_4 = arr4->getArr();
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ")\t" << arr_1[i] << "\t" << arr_2[i] << "\t" << arr_3[i]<< "\t" << arr_4[i] << endl;
    }
    delete[] arr_1, arr_2, arr_3, arr_4;
}
