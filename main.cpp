#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
    int weight; // وزن نقطه (1 برای شعبه‌های استارباکس، 2 برای مترو، و 3 برای پمپ بنزین)

    Point(double x, double y, int weight) : x(x), y(y), weight(weight) {}
};

// محاسبه فاصله اقلیدسی بین دو نقطه
double euclidean_distance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

// الگوریتم دایکسترا برای پیدا کردن بهترین نقطه
int find_optimal_location(const Point& new_branch, const vector<Point>& important_points) {
    vector<double> distances(important_points.size(), INFINITY);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    pq.push({0.0, 0}); // شروع از نقطه شعبه اولیه

    while (!pq.empty()) {
        int current_point = pq.top().second;
        double current_distance = pq.top().first;
        pq.pop();

        if (current_distance > distances[current_point]) {
            continue;
        }

        for (int i = 0; i < important_points.size(); ++i) {
            double dist = euclidean_distance(important_points[current_point], important_points[i]);
            double total_distance = current_distance + dist;

            if (total_distance < distances[i]) {
                distances[i] = total_distance;
                pq.push({total_distance, i});
            }
        }
    }

    double min_weighted_distance = INFINITY;
    int optimal_location = -1;

    for (int i = 0; i < important_points.size(); ++i) {
        double weighted_distance = distances[i] / important_points[i].weight;
        if (weighted_distance < min_weighted_distance) {
            min_weighted_distance = weighted_distance;
            optimal_location = i;
        }
    }

    return optimal_location;
}

int main() {
    vector<Point> important_points = {
        // مختصات نقاط پمپ بنزین
        Point(2, 4, 3),
        Point(5, 15, 3),
        Point(6, 7, 3),
        Point(10, 8, 3),
        // مختصات نقاط مترو
        Point(3.5, 5, 2),
        Point(4, 19, 2),
        Point(1.5, 11, 2),
        Point(11, 1.5, 2),
        Point(8, 1, 2),
        Point(12, 10, 2),
        // مختصات نقاط استارباکس
        Point(7, 5, 1),
        Point(8.5, 16, 1),
        Point(2.5, 9, 1),
        Point(3, 3, 1)
    };

    // مختصات شعبه جدید
    Point new_branch(9, 12, 1);

    int optimal_location = find_optimal_location(new_branch, important_points);
    cout << "Best point among 5 efficient points: (" << important_points[optimal_location].x << ", " << important_points[optimal_location].y << ")" << endl;

    return 0;
}

