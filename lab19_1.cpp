#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename.c_str());
    string line;
    char format[] = "%[^:]: %d %d %d";
    while(getline(source, line)){
        const char *text = line.c_str();
        char name[100];
        int score1, score2, score3;
        sscanf(text, format, &name, &score1, &score2, &score3);
        names.push_back(name);
        scores.push_back(score1+score2+score3);
        grades.push_back(score2grade(score1+score2+score3));
    }
}

void getCommand(string &command, string &key){
    string line;
    cout << "Please input your command: ";
    getline(cin, line);
    int end_command = line.find_first_of(" ");
    command = line.substr(0, end_command);
    key = line.substr(end_command+1, line.length());
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------" << endl;
    bool flag = false;
    for(unsigned int i=0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            flag = true;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
        }
    }
    if(flag == false) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------" << endl;
    bool flag = false;
    int key_length = key.length();
    char *char_key = new char[key_length];
    for(int i=0; i < key_length; i++) char_key[i] = key[i];
    for(unsigned int i=0; i < grades.size(); i++){
        if(grades[i] == *char_key){
            flag = true;
            cout << names[i] << " (" << scores[i] << ")" << endl;
        }
    }
    if(flag == false) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
    delete [] char_key;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
