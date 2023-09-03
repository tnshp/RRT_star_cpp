#ifndef VECTOR_OPERATIONS_H
#define VECTOR_OPERATIONS_H
#include<iostream>
#include<vector>
#include<math.h>

using namespace std;



template<class T> void print(vector<T> X, int M = 5){
    int m = X.size();
    if(m < M){
        M = m;
    }
    for(int i =0; i < M ; i++){
        cout << X[i] << " ";
    }
    cout << endl;
}
template<class T>void print(vector<vector<T>> X, int M = 5, int N  = 5){

    int m = X.size();
    if(m < M){
        M = m;
    }
    int n = X[0].size();
    if(n < N){
        N = n;
    }
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            cout << X[i][j] << " ";
        }
        cout << endl;
    }
}
template<class T> T dot(vector<T> X1, vector<T> X2){
    T dist = 0;
    try{
        if(X1.size() == X2.size()){
            for(int i = 0; i < X1.size(); i++){
                dist += X2[i] * X1[i];
            }
        }else{
            cout << "array size doesn't match: " << endl;
            throw(X1.size());
        }
    }catch(int num){

    }
    return dist;
}
template<class T> T distance(vector<T> X1,vector<T> X2 ){

    T dist = 0;
    try{
        if(X1.size() == X2.size()){
            vector<float> X;
            for(int i = 0; i < X1.size(); i++){
                X.push_back(X2[i] - X1[i]);
                //cout << X2[i] - X1[i];
            }
        //cout << "dot: " << dot(X,X) <<endl;
        dist = dot(X, X);
            // return dist;
        }else{
            throw(X1.size());
        }
    }catch(int num){
        cout << "array size doesnt match: " << num << endl;
    }
    return dist;
}
template<class T> vector<T> operator +(vector<T> A, vector<T> B){
    int n = A.size();
    try{
        if(B.size() != n);
            throw n;
    }catch(int num){
        //cout << "add: vector size does not match: " << num << " " << B.size() << endl;
    }
    vector<T> X;
    for(int i = 0; i< n; i++  ){
        X.push_back(A[i] + B[i]);
    }

    return X;
}
template<class T> vector<T> operator -(vector<T> A, vector<T> B){
    int n = A.size();
    try{
        if(B.size() != n);
            throw n;
    }catch(int num){
        //cout << "add: vector size does not match: " << num << " " << B.size() << endl;
    }
    vector<T> X;
    for(int i = 0; i< n; i++  ){
        X.push_back(A[i] - B[i]);
    }

    return X;
}
template<class T> vector<T> operator /(vector<T> A, T B){
    int n = A.size();
    vector<T> X;
    for(int i = 0; i< n; i++  ){
        X.push_back(A[i] / B);
    }

    return X;
}
template<class T> vector<T> operator *(vector<T> A, T B){
    int n = A.size();
    vector<T> X;
    for(int i = 0; i< n; i++  ){
        X.push_back(A[i] / B);
    }

    return X;
}


#endif // VECTOR_OPERATIONS_H
