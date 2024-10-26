#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
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
};

struct TwoViate{
    Point one = Point();
    Point two=Point();
    double distance = 40000;
};


vector<Triviate> Triviates;
vector<Point> originalFriends;


vector<Point> Friends;

int friendssize = 0;



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
    return abs(distanceA - distanceB);
}

Point findMostDensePoint(){
    //set all density to zero
    for(Point i: Friends){
        i.density = 0;
    }

    //populate density
    for(int i = 0; i < Friends.size(); i++)
    {
        for (int j = 0; j < Friends.size(); j++)
        {
            if (j != i)
            {
                double distance = findDistance(Friends[i], Friends[j]);
                double densityy = 1/pow(2.1,distance);
                Friends[i].density+= densityy;
            }
            else{
                continue;
            }
        }
    }

    // sort the vector by density
    sort(Friends.begin(), Friends.end(), [](const Point& a, const Point& b) { return a.density > b.density; });
    // for(int i = 0; i < Friends.size(); i++)
    // {
    //     //cout<<"Point "<<i+1<<": "<<Friends[i].x<<", "<<Friends[i].y<<", "<<Friends[i].density<<endl;
    // }

    //return most dense point
    return Friends[0];
}

void log(string log){
    //cout<<log<<endl;
}

int main() {

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
    // print("vector populated");
    //cout << "vector populated" << endl;

    while(Triviates.size()<(friendssize/3))
    {
        // log("\n\nstart of loop");
        //cout<<"Size of friends " << Friends.size() << endl;
        for(int i = 0;i< Friends.size();i++)
        {
            //cout<<"Point "<<i+1<<": "<<Friends[i].x<<", "<<Friends[i].y<<", "<<Friends[i].density << ", "<<Friends[i].distance <<endl;
        }
        //get most dense vector
        Point mostDense = findMostDensePoint();
        // Point mostDense = Friends[0];
        // log("most dense found");

        //cout << "Most dense point is: "<<mostDense.x<<", "<<mostDense.y<<", "<<mostDense.density<<endl;
        // populate nearby friends to the current most dense point
        // vector<Point> nearbyFriends;
        vector<TwoViate> twoViates;

        // populate twoviates for the most dense point
        for(int i = 0; i < Friends.size(); i++)
        {
            for(int j = 0; j < Friends.size(); j++)
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
        for(int i = 0; i < twoViates.size(); i++)
        {
            double distanceSimilarity = findDistanceSimilarity(mostDense, twoViates[i]);
            twoViates[i].distance = distanceSimilarity;
        }

        // sort twoviates by distance
        sort(twoViates.begin(), twoViates.end(), [](const TwoViate& a, const TwoViate& b) { return a.distance < b.distance; });
        for(int i = 0; i < twoViates.size(); i++)
        {
            cout<<"Point "<<i+1<<": "<<twoViates[i].one.x<<", "<<twoViates[i].one.y<<", "<<twoViates[i].two.x<<", "<<twoViates[i].two.y<<", "<<twoViates[i].distance<<endl;
        }
        //cout<<"size of nearby friends before pop "<< nearbyFriends.size() << endl;
        // for(int i = 0; i < Friends.size(); i++)
        // {
        //     if (Friends[i] == mostDense)
        //     {
        //         //cout << "equal to most dense " << Friends[i].x<<", "<<Friends[i].y<<" and "<<mostDense.x<<", "<<mostDense.y<< endl;
        //         Friends[i].distance = 10000;
        //         nearbyFriends.push_back(Friends[i]);
        //     }
        //     else
        //     {
        //         //cout << "NOT equal to most dense " << Friends[i].x<<", "<<Friends[i].y<<" and "<<mostDense.x<<", "<<mostDense.y<< endl;
        //         double distance = findDistance(mostDense, Friends[i]);
        //         Friends[i].distance = distance;
        //         nearbyFriends.push_back(Friends[i]);
        //     }
        // }
        //cout<<"size of nearby friends after population "<< nearbyFriends.size() << endl;


        //sort nearbyFRiends by distance
        // sort(nearbyFriends.begin(), nearbyFriends.end(), [](const Point& a, const Point& b) { return a.distance < b.distance; });
        // print nearby friends
        // for(int i = 0; i < Friends.size(); i++)
        // {
        //     //cout<<"Point "<<i+1<<": "<<nearbyFriends[i].x<<", "<<nearbyFriends[i].y<<", "<<nearbyFriends[i].distance<< ", d " << nearbyFriends[i].density<<endl;
        // }

        // choose the two nearest neighbors and add them fo triviates
        Triviate currentTri;
        currentTri.one = mostDense;
        currentTri.two = twoViates[0].one;
        currentTri.three = twoViates[0].two;
        Triviates.push_back(currentTri);

        //remove chosen points
        //cout<<"Size of friends before release op " << Friends.size() << endl;
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

        //cout<<"releasing " << Friends[0].x << ", " << Friends[0].y<<endl;
        Friends.erase(Friends.begin());
        //cout<<"Size of friends after release op " << Friends.size() << endl;
        //cout<< "End of loop " << endl;

    }
    vector<vector<int>> output;
    //cout<< "Size of output before " << output.size()<< endl;
    int iteration = 0;
    for(Triviate i: Triviates){
        vector<int> line;
        // //cout<<"("<<i.one.x<<","<<i.one.y<<") ("<<i.two.x<<","<<i.two.y<<") ("<<i.three.x<<","<<i.three.y<<")"<<endl;
        line.push_back(getIndex(originalFriends,i.one));
        line.push_back(getIndex(originalFriends,i.two));
        line.push_back(getIndex(originalFriends,i.three));
        output.push_back(line);
    }
    //cout<< "Size of output after " << output.size()<< endl;


    for(int i =0; i< output.size();i++)
    {
        for(int j = 0; j < output[i].size(); j++)
        {
            cout << output[i][j]<< " ";
        }
        cout<<endl;
    }

    return 0;
}
