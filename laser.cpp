#include <iostream>
#include <vector>
#include <string>

using namespace std;

static int boxSize = 20;
static int lasersA = 0;
static int lasersB = 0;

class Holder{
    public:
    string source;
    string type;
    int value;
    Holder(){
        type = "";
        value = 0;
        source = "";
    }
    Holder(string type_, int value_, string source_) {
        this->type = type_;
        this->value = value_;
        this->source = source_;
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

};

class Laser{
    public:
        Function function;
        Holder holder;
    Laser(){
        function = Function();
        holder = Holder();
    }
    Laser(Holder h){
        holder = h;
        getFunction();
    }

    void getFunction() {
        Function functionn = Function();
        if (holder.type == "U") 
        {
            functionn.x = holder.value;
            functionn.y = boxSize;
            if (holder.source == "A"){
                functionn.gradient = ((functionn.y - 0)/ (functionn.x - 0));
            }
            else if (holder.source == "B"){
                functionn.gradient = ((0 - functionn.y)/ (0 - functionn.y));
            }
        } 
        else if (holder.type == "L") {
            functionn.y = holder.value;
            functionn.x = boxSize;
            if (holder.source == "A"){
                functionn.gradient = ((functionn.y - 0)/ (functionn.x - 0));
            }
            else if (holder.source == "B"){
                functionn.gradient = ((0 - functionn.y)/ (0 - functionn.y));
            }
        }
        else if (holder.type == "R") {
            functionn.y = holder.value;
            functionn.x = boxSize;
            if (holder.source == "A"){
                functionn.gradient = ((functionn.y - 0)/ (functionn.x - 0));
            }
            else if (holder.source == "B"){
                functionn.gradient = ((0 - functionn.y)/ (0 - functionn.y));
            }
        }
        this->function = functionn;
    }

};

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
        string inputA;
        int inputB;
        cout << "Enter first cred of laser "<< i+1 << " from A: \n";
        cin >> inputA;
        cout << "Enter second cred of laser "<< i+1 << " from A: \n";
        cin >> inputB;

        // divide this string called input into two strings divided by a space between
        Holder holder = Holder(inputA,inputB, "A");
        Laser laser = Laser(holder);
        lasers.push_back(laser);
    }
    for (int i = 0; i < lasersB; i++){
        string inputA;
        int inputB;
        cout << "Enter first cred of laser "<< i+1 << " from A: \n";
        cin >> inputA;
        cout << "Enter second cred of laser "<< i+1 << " from A: \n";
        cin >> inputB;

        // divide this string called input into two strings divided by a space between
        Holder holder = Holder(inputA,inputB, "B");
        Laser laser = Laser(holder);
        lasers.push_back(laser);
    }

    for (int i = 0; i< lasers.size(); i ++)
    {
        cout << " index ";
        cout << " gradient "<<lasers[i].function.gradient;
        cout << " y "<<lasers[i].function.y;
        cout << " x "<<lasers[i].function.x;
        cout << " " << lasers[i].holder.type << " " << lasers[i].holder.value << "\n";
    }
}