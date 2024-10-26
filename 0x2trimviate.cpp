#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <set>
#include <cmath>

using namespace std;
static int minrand = 1;
static int maxrand = 100;

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

struct Triviate{
    Point one = Point();
    Point two=Point();
    Point three=Point();
    double onetwo = 0;
    double onethree = 0;
    double twothree = 0;
    double max = 0;
    double min = 0;

    bool operator == (const Triviate& other) const {
        return ((one == other.one && two == other.two && three == other.three)
        ||(one == other.one && two == other.three && three == other.two)
        ||(one == other.two && two == other.one && three == other.three)
        ||(one == other.three && two == other.two && three == other.one));
    }
};


vector<Triviate> Triviates;
vector<Point> originalFriends;
vector<Point> Friends;
int friendssize = 0;


double findDistance(Point a, Point b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}



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


int main() {

    vector<vector<int>> output;
    std::set <Triviate> TriviateSet;

    // int maxinput;
    cin>>friendssize;
    // for(int i =0; i< ;i++){
    //     int a, b;
    //     cin >> a >> b;
    //     //cout<<a <<" "<<b;
    // }

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

    for (int i = 0; i < Friends.size(); i++)
    {
        for (int j = 0; j < Friends.size(); j++)
        {
           for(int k = 0; k < Friends.size(); k++)
           {
               if (j != i && k != i && k != j)
               {
                   Triviate currentTri;
                   currentTri.one = Friends[i];
                   currentTri.two = Friends[j];
                   currentTri.three = Friends[k];
                   if(TriviateSet.find(currentTri) == TriviateSet.end())
                   {
                        Triviates.push_back(currentTri);
                   }
                   else{
                        continue;
                   }
               }
           }
        }

    }

    //populate onetwo, onethree, twothree distances
    for (int i = 0; i < Triviates.size(); i++)
    {
        Triviates[i].onetwo = findDistance(Triviates[i].one, Triviates[i].two);
        Triviates[i].onethree = findDistance(Triviates[i].one, Triviates[i].three);
        Triviates[i].twothree = findDistance(Triviates[i].two, Triviates[i].three);
        if(Triviates[i].onetwo > Triviates[i].onethree && Triviates[i].onetwo > Triviates[i].twothree)
        {
            Triviates[i].max = Triviates[i].onetwo;
            if (Triviates[i].onethree > Triviates[i].twothree)
            {
                Triviates[i].min = Triviates[i].twothree;
            }
            else
            {
                Triviates[i].min = Triviates[i].onethree;
            }
        }
        else if(Triviates[i].onethree > Triviates[i].onetwo && Triviates[i].onethree > Triviates[i].twothree)
        {
            Triviates[i].max = Triviates[i].onethree;
            if (Triviates[i].onetwo > Triviates[i].twothree)
            {
                Triviates[i].min = Triviates[i].twothree;
            }
            else
            {
                Triviates[i].min = Triviates[i].onetwo;
            }
        }
        else if (Triviates[i].twothree > Triviates[i].onetwo && Triviates[i].twothree > Triviates[i].onethree)
        {
            Triviates[i].max = Triviates[i].twothree;
            if (Triviates[i].onetwo > Triviates[i].onethree)
            {
                Triviates[i].min = Triviates[i].onethree;
            }
            else
            {
                Triviates[i].min = Triviates[i].onetwo;
            }
        }
    }

    // sort triviates by ( max - min )
    sort(Triviates.begin(), Triviates.end(), [](const Triviate& a, const Triviate& b) { return (a.max - a.min) < (b.max - b.min); });
    
    // print triviates
    for(int i = 0; i < Triviates.size(); i++)
    {
        cout<<"Point "<<i+1<<": "<<Triviates[i].one.x<<", "<<Triviates[i].one.y<<", "<<Triviates[i].two.x<<", "<<Triviates[i].two.y<<", "<<Triviates[i].three.x<<", "<<Triviates[i].three.y<<", "<<Triviates[i].max<<", "<<Triviates[i].min << "   "<<Triviates[i].max - Triviates[i].min<<endl;
    }


    return 0;
}
