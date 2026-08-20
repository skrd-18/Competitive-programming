#include <bits/stdc++.h>

using namespace std;

int partition(std::vector<int> &v, int left, int right)
{
    int pivot_val = v[left]; // Choose the first value as the pivot value, usually
    int low = left + 1;
    int high = right;
    while (low <= high)
    {
        // the low pointer moves until it find an element larger than the pivot
        while (low <= right && v[low] <= pivot_val)
        {
            low++;
        }
        // the high pointer moves until it find an element smaller than the pivot
        while (high >= left + 1 && v[high] > pivot_val)
        {
            high--;
        }
        if (low <= high)
        {
            // swap
            std::swap(v[low], v[high]);
        }
    }

    // The main loop has finished. high is the correct final position for the pivot.
    // Swap the pivot (which is still at v[left]) with the element at v[high].
    std::swap(v[left], v[high]);

    return high;
}

int main(int argc, char const *argv[])
{
    // Optimize standard I/O operations for competitive programming, kattis
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::vector<int> v;

    v = {99, 4, 1, 6, 5}; // A good test case with duplicates and unsorted data.

    // Quickselect the k-th smallest item in the array.
    // For k=2, we are looking for the 2nd smallest element (rank 1 in 0-based index).
    if (v.empty())
    {
        return 0;
    }
    int left = 0;
    int right = v.size() - 1;
    int k = 5; // Find the 5th smallest element

    if (k < 1 || k > v.size())
    {
        cout << "Invalid k value" << endl;
        return 1;
    }

    int target_idx = k - 1; // Convert 1-based k to 0-based index

    while (left <= right)
    {
        // partition() returns the exact final position of the pivot
        int pivot_idx = partition(v, left, right);
        if (pivot_idx == target_idx)
        {
            cout << "The " << k << "-th smallest element is: " << v[pivot_idx] << endl;
            return 0;
        }
        else if (pivot_idx > target_idx)
        {
            // Search on the left side of the array
            right = pivot_idx - 1;
        }
        else
        {
            // Search on the right side of the array
            left = pivot_idx + 1;
        }
    }
    return 0;
}
