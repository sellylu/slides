#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<double> xn, hn;
vector<int> yn;

vector<double> split(const string &s, char const delim) {
    vector<double> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        stringstream tmp;
        double num;
        tmp << item;
        tmp >> num;
        elems.push_back(num);
    }
    return elems;
}

void conv() {
    int const N  = xn.size() + hn.size() - 1;
    for(int i = 0; i < N; i++) {
        int const jmn = (i >= hn.size() - 1)? i - (hn.size() - 1) : 0;
        int const jmx = (i <  xn.size() - 1)? i : xn.size() - 1;
        double tmp = 0;
        for(int j = jmn; j <= jmx; j++ )
            tmp += (xn[j] * hn[i - j]);
        yn.push_back(tmp);
    }
}

template<typename E>
void findEdge(vector<E> f) {
    for(int i = 1; i < f.size()-1; i++) {
        if(f[i] == f[i-1] && f[i] != f[i+1])
            cout << i << " ";
        if(f[i] != f[i-1] && f[i] == f[i+1])
            cout << i << " ";
    }
    cout << endl << "End Find Signal Edge" << endl;
}

int main()
{
    fstream file;
    string tmp;

    file.open("xn.dat", ios::in);
    file >> tmp;
    xn = split(tmp, ',');
    file.close();

    cout << "Start Find Signal Edge of xn:" << endl;
    findEdge(xn);

    file.open("hn.dat", ios::in);
    file >> tmp;
    hn = split(tmp, ',');
    file.close();

    conv();

    file.open("yn.dat", ios::out);
    for(int i = 0; i < yn.size(); i++)
        if(i != yn.size()-1)
            file << yn[i] << ",";
    file << yn[yn.size()-1];

    cout << "Start Find Signal Edge of yn:" << endl;
    findEdge(yn);

    return 0;
}

