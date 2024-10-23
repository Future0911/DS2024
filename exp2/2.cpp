#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>

using namespace std;

int largestRectangleArea(vector<int>& heights) {
    stack<int> s;
    heights.push_back(0); // Append a zero height to flush the stack at the end
    int maxArea = 0;

    for (int i = 0; i < heights.size(); ++i) {
        while (!s.empty() && heights[s.top()] > heights[i]) {
            int h = heights[s.top()];
            s.pop();
            int width = s.empty() ? i : i - s.top() - 1;
            maxArea = max(maxArea, h * width);
        }
        s.push(i);
    }

    return maxArea;
}

vector<int> generateRandomHeights(int n) {
    vector<int> heights(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);

    for (int i = 0; i < n; ++i) {
        heights[i] = dis(gen);
    }

    return heights;
}

int main() {
    for (int i = 0; i < 10; ++i) {
        int n = rand() % 100 + 1; // 1 <= n <= 100
        vector<int> heights = generateRandomHeights(n);
        int maxArea = largestRectangleArea(heights);
        cout << "Test case " << i + 1 << ": Max Area = " << maxArea << endl;
    }
    return 0;
}
