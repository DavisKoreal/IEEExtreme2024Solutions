#include <iostream>
#include <vector>

using namespace std;

static int boxSize = 20;
static int lasersA = 0;
static int lasersB = 0;

class Holder{
    public:
    string type;
    int value;
    Holder(){
        type = "";
        value = 0;
    }
    Holder(string type, int value) {
        this->type = type;
        this->value = value;
    }
};

class Function{
    // string name;
    public:

    double gradient;
    int y;
    int x;
    Function(){
        y = 0;
        x = 0;
        gradient = 0;
    }
    Function(int y, int x) {
        this->y = y;
        this->x = x;
        gradient = this->y / this->x;
    }

};

class Laser{
    public:
        Function function;
        Holder holder;
    Laser(){
        function = Function();
        holder = Holder();
    }

    Laser(Holder holder) {
        this->holder = holder;
        this->function = getFunction();
    }

    Function getFunction() {
        Function function = Function();
        if (holder.type == "U") 
        {
            function.x = holder.value;
            function.y = boxSize;
        } 
        else if (holder.type == "L") {
            function.y = holder.value;
            function.y = boxSize;
        }
        else if (holder.type == "R") {
            function.y = holder.value;
            function.y = boxSize;
        }
        return function;
    }

};

// a function that divides a string based on spaces
Holder divideString(const std::string& input) {
    size_t spacePos = input.find(' ');
    if (spacePos == std::string::npos) {
        // No space found, return the original string and an empty string
        cout<<"No spaces has been found";
        return Holder();
    }
    std::string firstPart = input.substr(0, spacePos);
    std::string secondPart = input.substr(spacePos + 1);
    return Holder(firstPart, stoi(secondPart));
}


int main() {
    static vector<Laser> lasers;
    cout << "Hello, World!" << endl;
    cout<<"Enter boxsize " << endl;
    cin >> boxSize;
    cout << "Enter the number of lasers from A: "<< endl;
    cin >> lasersA;
    cout << "Enter the number of lasers from B: " << endl;
    cin >> lasersB;

    for (int i = 0; i < lasersA; i++){
        string input = "";
        cout << "Enter the cred of laser %d from A: \n", (i+1);
        cin >> input;
        if (input == ""){
            cout << "No input";
            return 0;
        }
        // divide this string called input into two strings divided by a space between
        Holder holder = divideString(input);
        Laser laser = Laser(holder);
        lasers.push_back(laser);
    }
}