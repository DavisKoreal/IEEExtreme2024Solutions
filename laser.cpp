#include <iostream>
#include <vector>
#include <string>
// #include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

static int boxSize = 20;
static int lasersA = 0;
static int lasersB = 0;


struct Line {
    double a;  // slope
    double b;  // y-intercept
    
    Line(double slope, double intercept) : a(slope), b(intercept) {}
};

struct Point {
    double x;
    double y;
    
    // Custom comparator for storing points in a set
    bool operator<(const Point& other) const {
        // Using small epsilon for floating-point comparison
        const double EPSILON = 1e-10;
        if (std::abs(x - other.x) > EPSILON) return x < other.x;
        return y < other.y;
    }
    
    bool operator==(const Point& other) const {
        const double EPSILON = 1e-10;
        return std::abs(x - other.x) < EPSILON && std::abs(y - other.y) < EPSILON;
    }
};
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

    float gradient;
    float y;
    float x;
    float startx;
    float starty;

    Function(){
        y = 0;
        x = 0;
        startx = 0;
        starty = 0;
        gradient = 0.0;
    }

    void getGradient(){
        gradient = ((y-starty) / (x-startx));
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
            if (holder.source == "A"){
                functionn.startx = 0;
                functionn.starty = 0;
                functionn.x = holder.value;
                functionn.y = boxSize;
            }
            else if (holder.source == "B"){
                functionn.startx = holder.value;
                functionn.starty = boxSize;
                functionn.x = boxSize;
                functionn.y = 0;
            }
        } 
        else if (holder.type == "L") {
                functionn.startx = 0;
                functionn.starty = holder.value;
                functionn.x = boxSize;
                functionn.y = 0;
        }
        else if (holder.type == "R") {
                functionn.startx = 0;
                functionn.starty = 0;
                functionn.x = boxSize;
                functionn.y = holder.value;
        }
        functionn.getGradient();
        this->function = functionn;
    }

};

std::vector<Point> findIntersections(const std::vector<Line>& lines) {
    std::set<Point> intersections;  // Using set to avoid duplicate points
    
    // Compare each pair of lines
    for (size_t i = 0; i < lines.size(); ++i) {
        for (size_t j = i + 1; j < lines.size(); ++j) {
            // Check if lines are parallel
            if (std::abs(lines[i].a - lines[j].a) < 1e-10) {
                // If parallel and have same y-intercept, they're the same line
                // We skip this case as it would mean infinite intersection points
                continue;
            }
            
            // Calculate intersection point
            // For y = a1x + b1 and y = a2x + b2
            // a1x + b1 = a2x + b2
            // x = (b2 - b1)/(a1 - a2)
            double x = (lines[j].b - lines[i].b) / (lines[i].a - lines[j].a);
            double y = lines[i].a * x + lines[i].b;
            
            intersections.insert({x, y});
        }
    }
    
    // Convert set to vector for return
    return std::vector<Point>(intersections.begin(), intersections.end());
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
        cout << "START ";
        cout<< "( "<<lasers[i].function.startx << ","<<lasers[i].function.starty<<")";
        cout << "END ";
        cout<< "( "<<lasers[i].function.x << ","<<lasers[i].function.y<<")";
        cout << "GRAD " << lasers[i].function.gradient;
        cout << "TYPE: "<< lasers[i].holder.source << lasers[i].holder.type << " "<< "\n";
    }

    Function upperLimit = Function();
    upperLimit.startx = 0;
    upperLimit.starty = boxSize;
    upperLimit.x = boxSize;
    upperLimit.y = boxSize;

    Function lowerLimit = Function();
    lowerLimit.startx = 0;
    lowerLimit.starty = 0;
    lowerLimit.x = boxSize;
    lowerLimit.y = 0;

    Function leftLimit = Function();
    leftLimit.startx = 0;
    leftLimit.starty = 0;
    leftLimit.x = 0;
    leftLimit.y = boxSize;

    Function rightLimit = Function();
    rightLimit.startx = boxSize;
    rightLimit.starty = 0;
    rightLimit.x = boxSize;
    rightLimit.y = boxSize;





// Example usage
    std::vector<Line> lines = {
        Line(2, 1),   // y = 2x + 1
        Line(-1, 4),  // y = -x + 4
        Line(1, 0),   // y = x
        Line(0, 2),   // y = 2
        Line(3, -2),  // y = 3x - 2
        Line(-2, 6),  // y = -2x + 6
        Line(1.5, 3), // y = 1.5x + 3
        Line(-0.5, 1),// y = -0.5x + 1
        Line(2.5, 0), // y = 2.5x
        Line(1, 2)    // y = x + 2
    };
    
    std::vector<Point> result = findIntersections(lines);
    
    // // Sort points by x-coordinate for cleaner output
    // std::sort(result.begin(), result.end(), 
    //     [](const Point& a, const Point& b) { return a.x < b.x; });
    
    // Print results
    for (const auto& point : result) {
        printf("Intersection at (%.2f, %.2f)\n", point.x, point.y);
    }
    
    return 0;
}