#include <iostream>

using namespace std;
const int SIZE = 5;

void fill_arr(int []); //输入数组
void show_arr(const int []); // 显示数组
void revalue(int [],short index); //修改值

int sum_arr(int []); // function protype 
int main(){
    
    int a[SIZE];
    fill_arr(a);

    cout << "sum(a) = " << sum_arr(a) << endl;


    return 0;
}

void fill_arr(int arr[SIZE]){
    cout << "Enter memers of arr : ";

    for (int i = 0 ; i < SIZE ; i++ ){
        cout << "i = " << i << endl;
        
        while (!(cin >> arr[i])){
            cin.clear();//reset
            
            while(cin.get() != '\n')
                continue;
            cout << "reinput a number(int) :";
            
        }
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
}






int sum_arr(int in_arr[SIZE] ){
    int result = 0;
    for ( int i = 0 ; i < SIZE ; i++)
        result += in_arr[i];
    return result;
}
