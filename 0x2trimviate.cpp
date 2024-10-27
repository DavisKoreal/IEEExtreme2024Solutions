#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <set>
#include <cmath>

using namespace std;

struct Point {
    double x=0;
    double y=0;
    double density = 0;
    double distance = 0;

    bool operator==(const Point& other) const {
        // Use small epsilon for floating point comparison
        const double EPSILON = 1e-10;
        return (std::abs(x - other.x) < EPSILON) && (std::abs(y - other.y) < EPSILON);
    }
};

double findDistance(Point a, Point b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

struct Triviate{
    Point one = Point();
    Point two=Point();
    Point three=Point();
    double onetwo = 0;
    double onethree = 0;
    double twothree = 0;
    double max = 0;
    double min = 0;
    double stability = 0;

    double maxDistance(){
        double max = 0;
        if (onetwo > max){
            max = onetwo;
        }
        if (onethree > max){
            max = onethree;
        }
        if (twothree > max){
            max = twothree;
        }
        return max;
    }

    double minDistance(){
        double min = 0;
        if (onetwo < min){
            min = onetwo;
        }
        if (onethree < min){
            min = onethree;
        }
        if (twothree < min){
            min = twothree;
        }
        return min;
    }

    double getDistance(){
        return maxDistance() - minDistance();
    }

    double getOneThree(){
        return findDistance(this->one, this->three);
    }

    double getOneTwo(){
        return findDistance(this->one, this->two);
    }

    double getTwoThree(){
        return findDistance(this->two, this->three);
    }

    Triviate(Point one, Point twoo, Point three){
        this->one = one;
        this->two = twoo;
        this->three = three;
        onetwo = getOneTwo();
        onethree = getOneThree();
        twothree = getTwoThree();
        max = maxDistance();
        min = minDistance();
        stability = getDistance();
    }

    Triviate(){
        one = Point();
        two = Point();
        three = Point();
        onetwo = 0;
        onethree = 0;
        twothree = 0;
        max = 0;
        min = 0;
        stability = 0;
    }
};

struct StateViate{
    Triviate one = Triviate();
    Triviate two = Triviate();
    Triviate three = Triviate();
    double cost = 0;

    double getCost(){
        return one.stability + two.stability + three.stability;
    }
    StateViate(Triviate one, Triviate two, Triviate three){
        this->one = one;
        this->two = two;
        this->three = three;
        cost = getCost();
    }
    StateViate(Point one1, Point two1, Point three1, Point one2, Point two2, Point three2, Point one3, Point two3, Point three3){
        this->one = Triviate(one1, two1, three1);
        this->two = Triviate(one2, two2, three2);
        this->three = Triviate(one3, two3, three3);
        cost = getCost();
    }
    StateViate(){
        one = Triviate();
        two = Triviate();
        three = Triviate();
        cost = 0;
    }
};



int getIndex(vector<Point> v, Point K)
{
    auto it = find(v.begin(), v.end(), K);

    // If element was found
    if (it != v.end()) 
    {
       // calculating the index
        // of K
        int index = it - v.begin();
        //cout<<"index " << index<< endl;
        return index;
    }
    else {
        // If the element is not
        // present in the vector
        return -1;
    }
}

int generateRandomNumber() {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_real_distribution<> distr(0, 10); // Define the range
    return distr(gen);
}


int main() {

    vector<vector<int>> output;
    vector<Point> Friends;

    long unsigned int friendssize = 0;
    cin>>friendssize;

    //populate friends vector
    for(long unsigned int i = 0; i < friendssize; i++)
    {
        int a, b;
        cin >> a >> b;
        Point point;
        point.x = a;
        point.y = b;
        Friends.push_back(point);
    }

    double bestCost = 1000000000;
    double lastcost = 100000;
    StateViate bestState = StateViate();
    int consecutivenegatives = 0;
    bool lastWasNegative = false;

    while (consecutivenegatives < 21){
        int randNumber = generateRandomNumber();
        cout<< randNumber << endl;
    }
    return 0;
}
