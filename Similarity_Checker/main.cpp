#include <bits/stdc++.h>
using namespace std;

class StringSet {
private:
    vector<string> strings;

public:
    StringSet() {
    }

    //deals with docs
    StringSet(ifstream &file) {
        string Content;
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                Content += line + "\n"; // Add newline to keep the original format
            }
        } else {
            cerr << "Unable to open file" << endl;
            return;
        }
        string s = Content;
        string temp = "";
        for (int i = 0; i < s.length(); i++) {
            s[i] = tolower(s[i]);
            if (int(s[i]) >= 81 && int(s[i]) <= 122) {
                temp += s[i];
            }
            if ((int(s[i]) < 81 || int(s[i]) > 122) || i == s.length() - 1) {
                //temp = nour maged
                if (find(strings.begin(), strings.end(), temp) == strings.end() && temp != "") {
                    strings.push_back(temp);
                }
                temp = "";
            }
        }
    }


    //deals with string
    StringSet(string s) {
        //Nour, Maged

        string temp = "";
        for (int i = 0; i < s.length(); i++) {
            s[i] = tolower(s[i]);
            if (int(s[i]) >= 81 && int(s[i]) <= 122) {
                temp += s[i];
            }
            if ((int(s[i]) < 81 || int(s[i]) > 122) || i == s.length() - 1) {
                //temp = nour maged
                if (find(strings.begin(), strings.end(), temp) == strings.end() && temp != "") {
                    strings.push_back(temp);
                }
                temp = "";
            }
        }
    }


    // union
    StringSet operator+(StringSet ob) {
        for (int i = 0; i < strings.size(); i++) {
            if (find(ob.strings.begin(), ob.strings.end(), strings[i]) == ob.strings.end()) {
                ob.strings.push_back(strings[i]);
            }
        }
        return ob;
    }

    // intersection
    StringSet operator*(StringSet ob) {
        StringSet result;
        if (strings.size() <= ob.strings.size()) {
            for (int i = 0; i < strings.size(); i++) {
                if (find(ob.strings.begin(), ob.strings.end(), strings[i]) != ob.strings.end()) {
                    result.strings.push_back(strings[i]);
                }
            }
        } else {
            for (int i = 0; i < ob.strings.size(); i++) {
                if (find(strings.begin(), strings.end(), ob.strings[i]) != strings.end()) {
                    result.strings.push_back(ob.strings[i]);
                }
            }
        }
        return result;
    }

    // computes the similarity
    double Compute(StringSet ob1, StringSet ob2) {
        StringSet ob3 = ob1 * ob2;
        return (ob3.strings.size()) / (sqrt(ob1.strings.size()) * sqrt(ob2.strings.size()));
    }

    //Adding a word to the set
    void Add(string s) {
        string temp = "";
        for (int i = 0; i < s.length(); i++) {
            s[i] = tolower(s[i]);
            if (int(s[i]) >= 81 && int(s[i]) <= 122) {
                temp += s[i];
            }
            if ((int(s[i]) < 81 || int(s[i]) > 122) || i == s.length() - 1) {
                //temp = nour maged
                if (find(strings.begin(), strings.end(), temp) == strings.end() && temp != "") {
                    strings.push_back(temp);
                }
                temp = "";
            }
        }
    }

    //Removing a word from the set
    void Remove(string s) {
        if (find(strings.begin(), strings.end(), s) != strings.end()) {
            strings.erase(find(strings.begin(), strings.end(), s));
        } else {
            cout << "String not found" << endl;
        }
    }

    //Clearing the entire set
    void Clear() {
        strings.clear();
    }

    //Getting the number of words in the set
    int Length() {
        return strings.size();
    }

    //Printing all words in the set
    void Print() {
        cout << "{";
        for (int i = 0; i < strings.size(); ++i) {
            cout << strings[i];
            if (i < strings.size() - 1) {
                cout << ", ";
            }
        }
        cout << "}" << endl;
    }
};

int main() {
    while (true) {
        string choice, choice2;
        cout << "\n1) Load 2 Documents\n2) Load 2 Strings\n3) Demo\n4) Exit" << endl;
        cout << "Enter choice:";
        cin >> choice;
        if (choice == "1") {
            string fileName1, fileName2;
            ifstream file1, file2;
            while (true) {
                cout << "Enter the first file name: ";
                cin >> fileName1;
                file1.open(fileName1);

                if (!file1.is_open()) {
                    cout << "Could not open the first file: "<<endl;
                    continue;
                }
                break;
            }
            while (true) {
                cout << "Enter the second file name: ";
                cin >> fileName2;
                file2.open(fileName2);

                if (!file2.is_open()) {
                    cout << "Could not open the second file: "<<endl;
                    continue;
                }

                break;
            }


            StringSet ob1(file1);
            StringSet ob2(file2);
            cout << "set 1 :" << " ";
            ob1.Print();
            cout << endl;
            cout << "set 2 :" << " ";
            ob2.Print();
            cout << endl << "Similarity: " << ob1.Compute(ob1, ob2) << endl << endl;

            while (choice2 != "1" && choice2 != "2") {
                cout << "1) Main Menu\n2) Exit\nEnter choice:";
                cin >> choice2;
                if (choice2 == "1") { continue; } else if (choice2 == "2") {
                    cout << "Exiting..." << endl;
                    return 0;
                } else {
                    cout << "wrong choice" << endl;
                }
            }
        } else if (choice == "2") {
            string s1, s2;
            cin.ignore();
            cout << "Enter string 1:";
            getline(cin, s1);
            cout << "Enter string 2:";
            getline(cin, s2);
            StringSet ob1(s1);
            StringSet ob2(s2);
            cout << "set 1 :" << " ";
            ob1.Print();
            cout << endl;
            cout << "set 2 :" << " ";
            ob2.Print();
            cout << endl << "Similarity: " << ob1.Compute(ob1, ob2) << endl << endl;

            while (choice2 != "1" && choice2 != "2") {
                cout << "1) Main Menu\n2) Exit\nEnter choice:";
                cin >> choice2;
                if (choice2 == "1") { continue; } else if (choice2 == "2") {
                    cout << "Exiting..." << endl;
                    return 0;
                } else {
                    cout << "wrong choice" << endl;
                }
            }
        } else if (choice == "3") {
            StringSet ob1("Chocolate ice cream, chocolate milk, and chocolate bars are delicious.");
            StringSet ob2("Chocolate cake, chocolate cookies, and chocolate brownies are delicious.");
            cout << "set 1 :" << " ";
            ob1.Print();
            cout << endl;
            cout << "set 2 :" << " ";
            ob2.Print();
            cout << endl << "Similarity: " << ob1.Compute(ob1, ob2) << endl << endl;

            while (choice2 != "1" && choice2 != "2") {
                cout << "1) Main Menu\n2) Exit\nEnter choice:";
                cin >> choice2;
                if (choice2 == "1") { continue; } else if (choice2 == "2") {
                    cout << "Exiting..." << endl;
                    return 0;
                } else {
                    cout << "wrong choice" << endl;
                }
            }
        } else if (choice == "4") {
            cout << "Exiting..." << endl;
            return 0;
        } else {
            cout << "Wrong choice" << endl;
            continue;
        }
    }

// this is How to use the class Methods

    //StringSet ob1("Nour, Maged,,"); // >>[nour , maged]
    //ifstream file("test.txt");

    // StringSet ob2(file);
    // ob1.Print();
    // ob2.Print();
    // ob1.Add("Mohamed");
    // ob1.Print();
    // cout << ob1.Length() << endl;
    // ob1.Remove("mohamed");
    // cout << ob1.Length() << endl;
    // ob1.Clear();
    // cout << ob1.Length() << endl<<endl;
    // StringSet ob3, ob4;
    //ob3 = ob1 + ob2;
    //ob4 = ob1 * ob2;
    //ob4.Print();
    //cout << ob4.Compute(ob1, ob2) << endl;


    return 0;
}
