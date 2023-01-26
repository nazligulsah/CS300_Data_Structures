//
//  main.cpp
//  cs300
//
//  Created by Gülşah Önen on 23.03.2021.
//

#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct StackNode {
    T x_coordinate;
    T y_coordinate;
    bool  *visited;
    bool *has_pawn;
};
int main() {
   int n;
    int p;
    cout << "Please enter the size of the board (n): ";
    cin >> n;
    while (!(4 < n && n < 12)){
        cout << "Please enter the size of the board (n): ";
        cin >> n;
    }
    cout << "Please enter the number of the pawns (p): ";
    cin >> p;
    while (!( p <=3*n)){
        cout << "Please enter the number of the pawns (p): ";
        cin >> p;
    }
    int mat[n][n];
    for (int i = 0; i <n; i++){
        for (int j = 0; j < n; j++){
                 mat[i][j]=0;
            cout << mat[i][j] << " " ;
        }
         cout << endl;
         }
    
    
    return 0;
}
