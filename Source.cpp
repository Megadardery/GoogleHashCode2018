#include <bits/stdc++.h>
#include <string>

using namespace std;

struct point {
	int x;
	int y;
};

struct Ride
{
	point startPos;
	point endPos;
	int startTime;
	int endTime;
	int index;
	int distance;

};

struct Car
{
	point pos = { 0, 0 };
	int busyUntil = 0;
	vector<int> taken;

};

int distance(point a, point b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

point carpos;

bool sortFunc(Ride x, Ride y) {
	return x.startTime < y.startTime;
}

int main() {
	long long score = 0;
	for (char letter = 'A'; letter < 'F'; ++letter) {
		cerr << letter << endl;
		string inn = "D:\\Desktop\\hash code\\in\\";
		inn += letter;
		string outt = "D:\\Desktop\\hash code\\";
		outt += letter;

		freopen(inn.c_str(), "r", stdin);
		freopen(outt.c_str(), "w", stdout);

		int rows, cols, vehicles, n, bonus, steps;
		cin >> rows >> cols >> vehicles >> n >> bonus >> steps;
		vector<Ride> rides(n);
		vector<Car> cars(vehicles);

		for (int i = 0; i < n; ++i) {
			point startPos, endPos;
			int startTime, endTime;
			cin >> startPos.x >> startPos.y;
			cin >> endPos.x >> endPos.y;
			cin >> startTime >> endTime;
			Ride myride = { startPos, endPos, startTime, endTime };
			myride.distance = distance(startPos, endPos);
			myride.index = i;
			rides[i] = myride;
		}
		int currRide = 0;
		int step = 0;

		while (step < steps && rides.size() != 0) {		

			int minStep = INT_MAX;
			for (int i = 0; i < vehicles; i++) {
				if (cars[i].busyUntil <= step) {
					carpos = cars[i].pos;
					currRide = min_element(rides.begin(), rides.end(), sortFunc) - rides.begin();

					int reachTime = step + distance(cars[i].pos, rides[currRide].startPos);
					if (reachTime <= rides[currRide].startTime) {
						score += bonus;
						reachTime = rides[currRide].startTime;
					}
					int totalTime = reachTime + rides[currRide].distance;
					if (totalTime < rides[currRide].endTime) {
						cars[i].busyUntil = totalTime;
						cars[i].taken.push_back(rides[currRide].index);
						score += rides[currRide].distance;
					}
					rides.erase(rides.begin() + currRide);
					if (rides.size() == 0) break;
					currRide++;

					if (minStep > cars[i].busyUntil)
						minStep = cars[i].busyUntil;

				}
			}
			step = minStep;
		}

		for (int i = 0; i < vehicles; ++i) {
			cout << cars[i].taken.size() << " ";
			for (int j = 0; j < cars[i].taken.size(); ++j) {
				cout << cars[i].taken[j] << " ";
			}
			cout << endl;
		}
	}
	cerr << score;

}