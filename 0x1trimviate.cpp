#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

struct Point {
    double x=0;
    double y=0;
    double density = 0;
    double distance = 0;

    bool operator==(const Point& other) const {
        const double EPSILON = 1e-10;
        return (std::abs(x - other.x) < EPSILON) && (std::abs(y - other.y) < EPSILON);
    }
};

struct Triviate{
    Point one = Point();
    Point two=Point();
    Point three=Point();
};

struct TwoViate{
    Point one = Point();
    Point two=Point();
    double distance = 40000;
};


vector<Triviate> Triviates;
vector<Point> originalFriends;


vector<Point> Friends;

long unsigned int friendssize = 0;



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

double findDistance(Point a, Point b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double findDistanceSimilarity(Point mostDense, TwoViate b){
    double distanceA = findDistance(mostDense, b.one);
    double distanceB = findDistance(mostDense, b.two);
    double distanceC = findDistance(b.one, b.two);
    double average = (distanceA + distanceB + distanceC) / 3;
    double totaldeviations = 0;
    totaldeviations += abs(distanceA - average);
    totaldeviations += abs(distanceB - average);
    totaldeviations += abs(distanceC - average);
    return totaldeviations;
}

Point findMostDensePoint(){
    // return Friends[0];

    // for(long unsigned int i = 0; i < Friends.size(); i++){
    //     Friends[i].density = 0;
    // }

    //populate density
    for(long unsigned int i = 0; i < Friends.size(); i++)
    {
        for (long unsigned int j = 0; j < Friends.size(); j++)
        {
            if (j != i)
            {
                double distance = findDistance(Friends[i], Friends[j]);
                double densityy = 1/distance;
                Friends[i].density+= densityy;
            }
            else{
                continue;
            }
        }
    }

    // sort the vector by density
    sort(Friends.begin(), Friends.end(), [](const Point& a, const Point& b) { return a.density < b.density; });

    return Friends[0];
}

void log(string log){
    //cout<<log<<endl;
}

int main() {

    // int maxinput;
    cin>>friendssize;

    //populate friends vector
    for(int i = 0; i < friendssize; i++)
    {
        int a, b;
        cin >> a >> b;
        // //cout<<a <<" "<<b;
        Point point;
        point.x = a;
        point.y = b;
        Friends.push_back(point);
    }
    originalFriends = Friends;

    while(Triviates.size()<(friendssize/3))
    {

        Point mostDense = findMostDensePoint();
        vector<TwoViate> twoViates;

        // populate twoviates for the most dense point
        for(long unsigned int i = 0; i < Friends.size(); i++)
        {
            for(long unsigned int j = 0; j < Friends.size(); j++)
            {
                if ((Friends[i] == mostDense) || (Friends[j] == mostDense)|| (Friends[i] == Friends[j])) 
                {
                    continue;
                }
                else{
                    TwoViate currentTwoViate;
                    currentTwoViate.one = Friends[i];
                    currentTwoViate.two = Friends[j];
                    twoViates.push_back(currentTwoViate);
                }
            }
        }

        // do a similarity population of the twoviates
        for(long unsigned int i = 0; i < twoViates.size(); i++)
        {
            double distanceSimilarity = findDistanceSimilarity(mostDense, twoViates[i]);
            twoViates[i].distance = distanceSimilarity;
        }

        // sort twoviates by distance
        sort(twoViates.begin(), twoViates.end(), [](const TwoViate& a, const TwoViate& b) { return a.distance < b.distance; });

        // choose the two nearest neighbors and add them fo triviates
        Triviate currentTri;
        currentTri.one = mostDense;
        currentTri.two = twoViates[0].one;
        currentTri.three = twoViates[0].two;
        Triviates.push_back(currentTri);

        Point elementToRemove = twoViates[0].one;
        Point elementToRemovee = twoViates[0].two;
        auto it = std::find(Friends.begin(), Friends.end(),elementToRemove);
        auto itt = std::find(Friends.begin(), Friends.end(),elementToRemovee);
        // If element is found found, erase it
        if (it != Friends.end()) {
            Friends.erase(it);
        }
        if (itt != Friends.end()) {
            Friends.erase(itt);
        }
        Friends.erase(Friends.begin());
    }
    vector<vector<int>> output;
    for(Triviate i: Triviates){
        vector<int> line;
        line.push_back(getIndex(originalFriends,i.one));
        line.push_back(getIndex(originalFriends,i.two));
        line.push_back(getIndex(originalFriends,i.three));
        output.push_back(line);
    }


    for(long unsigned int i =0; i< output.size();i++)
    {
        for(long unsigned int j = 0; j < output[i].size(); j++)
        {
            cout << output[i][j]<< " ";
        }
        cout<<endl;
    }

    return 0;
}
