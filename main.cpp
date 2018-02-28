#include <iostream>
#include <fstream>

using namespace std;
struct word {
    string a;
    int b;
};

int minimum(int a, int b, int c) {
    if (a <= b && a <= c) {
        return a;
    }
    if (b <= a && b <= c) {
        return b;
    }
    return c;
}

int levenshteinDistance(string a, string b) {
    int **matrix = new int *[a.length() + 1];
    int cost;
    for (int i = 0; i <= a.length(); ++i) {
        matrix[i] = new int[b.length()];
    }
    for (int j = 0; j <= a.length(); ++j) {
        matrix[j][0] = j;
    }
    for (int k = 0; k <= b.length(); ++k) {
        matrix[0][k] = k;
    }
    for (int i = 1; i <= b.length(); ++i) {
        for (int j = 1; j <= a.length(); ++j) {
            if (a[j - 1] == b[i - 1]) {
                cost = 0;
            } else {
                cost = 1;
            }
            matrix[j][i] = minimum(matrix[j - 1][i] + 1, matrix[j][i - 1] + 1, matrix[j - 1][i - 1] + cost);
        }
    }
//    for (int i = 1; i <= b.length(); ++i) {
//        for (int j = 1; j <= a.length(); ++j) {
//            cout<<matrix[j][i]<<" ";
//        }
//        cout<<endl;
//    }
    return matrix[a.length()][b.length()];
}

int main() {
    string a, b;
    cout<<"Prosze podac slowo:"<<endl;
    cin >> a;
    fstream file;

    if (a[0] >= 97 && a[0] <= 104) {
        file.open("a-h.txt");
    } else if (a[0] > 104 && a[0] <= 112) {
        file.open("i-p.txt");
    } else {
        file.open("q-z.txt");
    }
    struct word words[3];
    words[0].b=2147483646;
    words[1].b=2147483646;
    words[2].b=2147483646;
    getline(file, b);
    int dist;
    while (b.compare("")) {
        //b.length()>=a.length() &&
        if(b.compare(a)){
            dist=levenshteinDistance(a,b);
            if(words[0].b>dist){
                words[0].b=dist;
                words[0].a=b;
            }else if(words[1].b>dist){
                words[1].b=dist;
                words[1].a=b;
            }else if(words[2].b>dist){
                words[2].b=dist;
                words[2].a=b;
            }
        }
        getline(file, b);
    }
    cout << "Proponowane wyrazy:" << endl;
    cout<<"1. "<<words[0].a<<endl<<"2. "<<words[1].a<<endl<<"3. "<<words[2].a<<endl;

    return 0;
}