#include <iostream>
#include <vector>
#include <cmath>
#include<fstream>
#include <string>
#include <iomanip>

using namespace std;

class rectangle
{
public:
    vector<float> X1;
    vector<float> X2;
    rectangle(vector<float> R1, vector<float> R2){
        X1 = R1; X2 = R2;
    }

    bool check(vector<float> X){
        if( ( X[0] >= X1[0] && X[0] <= X2[0] ) && ( X[1] >= X1[1] && X[1] <= X2[1] )){
            return true;
        }else{
            return false;
        }
    }
};


void print(vector<float> X, int M = 5);
void print(vector<vector<float>> X, int M = 5, int N  = 5);
void print(vector<int> X, int M = 5);

void writeToCSV(const std::string& filename, const std::vector<std::vector<float>>& data) ;

float dot(vector<float> X1, vector<float> X2);
float distance(vector<float> X1,vector<float> X2 );
vector<float> operator +(vector<float> A, vector<float> B);
vector<float> operator -(vector<float> A, vector<float> B);
vector<float> operator /(vector<float> A, float B);
vector<float> operator *(vector<float> A, float B);

vector<float> randomVector(vector<float> min, vector<float> max);
int find_closest_point(vector<float> point, vector<vector<float>> X);
vector<float> unit_point(vector<float> origin, vector<float> point, float lambda_ = 1);
bool check_obstacles(vector<rectangle> obs, vector<float> new_point);
vector<int> neighbourhood(vector<float> point,float radius, vector<vector<float>> X);
void file_write(vector<vector<float>> X,vector<int> idx, vector<int> path,vector<float> c1,vector<float> c2,vector<rectangle> obs);


int main(){
    vector<vector<float>> X;

    vector<float> start = {150,150};
    vector<float> corner1  = {0,0};
    vector<float> corner2  = {400,400};

    vector<int> idx = {-1};
    vector<int> path_len = {0};

    rectangle O1({10,20},{180,100});
    rectangle O2({100,200}, {150, 370});
    rectangle O3({220,100}, {350, 250});
    rectangle O4({200,300}, {350, 350});
    vector<rectangle> obs= {O1,O2, O3, O4};

    X.push_back(start);
    float lambda_ = 10;
    int max_iterations = 1000   ;
    float nradius =20;

    for(int i = 1; i < max_iterations; i++){
        auto rand_point = randomVector(corner1, corner2);
        auto index = find_closest_point(rand_point, X);
        vector<float> new_point;

        if(distance(rand_point, X[index]) > lambda_)
            new_point = unit_point(X[index], rand_point, lambda_);
        else
            new_point = rand_point;
        if(!check_obstacles(obs, new_point)){
            int new_index; 
            int min_path = 100000;
            auto npoints = neighbourhood(new_point, nradius, X);
            cout << "new_point : ";
            print(new_point);
            cout << "neighbourhood : " ;
            print(npoints);
            for(auto& i:npoints){
                if( path_len[i] < min_path){
                    min_path = path_len[i];
                    new_index = i;
                }
            }
            cout << "new Index: " << new_index <<endl;
            X.push_back(new_point);
            idx.push_back(new_index);
            path_len.push_back(path_len[new_index] + 1);
        }
    }
    // print(X, 100,20);
    // print(idx, 20);
    // print(path_len, 20);

    file_write(X,idx,path_len, corner1, corner2, obs);

    return 0;
}


void print(vector<float> X, int M ){
    int m = X.size();
    if(m < M){
        M = m;
    }
    for(int i =0; i < M ; i++){
        cout << X[i] << " ";
    }
    cout << endl;
}
void print(vector<vector<float>> X, int M , int N ){
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
void print(vector<int> X, int M ){
    int m = X.size();
    if(m < M){
        M = m;
    }
    for(int i =0; i < M ; i++){
        cout << X[i] << " ";
    }
    cout << endl;
}

void writeToCSV(const std::string& filename, const std::vector<std::vector<float>>& data) {
    std::ofstream outputFile(filename);

    if (!outputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            outputFile << std::fixed << std::setprecision(2) << row[i]; // Set precision for floating-point numbers
            if (i < row.size() - 1) {
                outputFile << ",";
            }
        }
        outputFile << "\n";
    }

    outputFile.close();
}
float dot(vector<float> X1, vector<float> X2){
    float dist = 0;
    try{
        if(X1.size() == X2.size()){
            for(int i = 0; i < X1.size(); i++){
                dist += X2[i] * X1[i];
                //cout << X2[i] << " " << X1[i] << " " << dist  << endl;
            }
        }else{
            throw(X1.size());
        }
    }catch(int num){
        cout << "array size doesn't match: " << num << endl;
    }
    return dist;
}
float distance(vector<float> X1,vector<float> X2 ){

    float dist = 0;
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
vector<float> operator +(vector<float> A, vector<float> B){
    int n = A.size();
    try{
        if(B.size() != n);
            throw n;
    }catch(int num){
        //cout << "add: vector size does not match: " << num << " " << B.size() << endl;
    }
    vector<float> X;
    for(int i = 0; i< n; i++  ){
        X.push_back(A[i] + B[i]);
    }

    return X;
}
vector<float> operator -(vector<float> A, vector<float> B){
    int n = A.size();
    try{
        if(B.size() != n);
            throw n;
    }catch(int num){
        //cout << "add: vector size does not match: " << num << " " << B.size() << endl;
    }
    vector<float> X;
    for(int i = 0; i< n; i++  ){
        X.push_back(A[i] - B[i]);
    }

    return X;
}
vector<float> operator /(vector<float> A, float B){
    int n = A.size();
    vector<float> X;
    for(int i = 0; i< n; i++  ){
        X.push_back(A[i] / B);
    }

    return X;
}
vector<float> operator *(vector<float> A, float B){
    int n = A.size();
    vector<float> X;
    for(int i = 0; i< n; i++  ){
        X.push_back(A[i] * B);
    }

    return X;
}
vector<float> randomVector(vector<float> min, vector<float> max){

    vector<float> vect;
    auto arraySize = min.size();
    for(int i = 0; i < arraySize; i++){
        float num = (float(rand()) / float(RAND_MAX)) * max[i] + min[i];
        vect.push_back(num);
    }
    return vect;
}
int find_closest_point(vector<float> point, vector<vector<float>> X){
    float min_dist = 100000;
    int count = 0;
    int ans;
    for (const auto& i :X){
        float dist = distance(i, point);

        if(dist < min_dist){
            min_dist =dist;
            ans = count;
        }
        count += 1;
    }
    return ans;
}
vector<float> unit_point(vector<float> origin, vector<float> point, float lambda_){
    auto dir = point - origin;
    auto dist = distance(origin,point);
    auto unit_dist = dir /sqrt(dist);
    // cout << dist << endl;
    // print(unit_dist);
    auto new_point = origin + (unit_dist * lambda_);
    return new_point;
}
bool check_obstacles(vector<rectangle> obs, vector<float> new_point){

    for(int i = 0; i < obs.size(); i++){
        if(obs[i].check(new_point))
            return true;
    }
    return false;
}
vector<int> path_trace(vector<float> point,vector<vector<float>> X, vector<int> idx){

    vector<int> path;
    auto closest_point = find_closest_point(point, X);
    int current_point = closest_point;
    int prev_point;
    while( prev_point != -1){
        path.push_back(current_point);
        prev_point = idx[current_point];
    }

    return path;
}
vector<int> neighbourhood(vector<float> point,float radius, vector<vector<float>> X){
    vector<int> npoints;
    float r =radius * radius;
    for(int i = 0; i < X.size(); i++){
        if(distance(point, X[i]) <= r)
            npoints.push_back(i);
    }
    return npoints;
}

void file_write(vector<vector<float>> X, vector<int> idx,vector<int> path, vector<float> c1,vector<float> c2,vector<rectangle> obs){
    string points = "RRT_star_points.txt";
    string environment = "RRT_star_environment.txt";

    for(int i = 0; i < X.size(); i++){
        X[i].push_back(idx[i]);
        X[i].push_back(path[i]);
    }
    writeToCSV(points, X);

    vector<vector<float>> env;
    env.push_back(c1);
    env.push_back(c2);

    for(int i = 0; i < obs.size(); i++){
        env.push_back(obs[i].X1);
        env.push_back(obs[i].X2);
    }
    writeToCSV(environment, env);
}
