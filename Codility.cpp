#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <iostream> // cout

using namespace std;

// OddOccurrencesInArray Submitted in: C++ 100%
int OddOccurrencesInArray(vector<int> &A) {
    vector<int> v(A);
    sort(v.begin(), v.end());
    int count = 1;
    for (unsigned int i = 1; i < v.size(); i++) {
        if (v[i] != v[i - 1]) {
            if (count == 1) {
                return v[i - 1];
            }
            count = 1;
        } else {
            count = (count == 0) ? 1 : 0;
        }
    }
    return v.back();
}

// TapeEquilibrium Submitted in: C++ 100%
int TapeEquilibrium(vector<int> &A) {
    long int sum = 0;
    for (int a : A) {
        sum += a;
    }
    long int diff;
    long int diff_min = 1000 * A.size();
    long int right = sum;
    for (unsigned int i = 0; i < A.size() - 1; i++) {
        right = right - A[i];
        diff = abs(sum - 2 * right);
        if (diff < diff_min) {
            diff_min = diff;
        }
    }
    return (int) diff_min;
}

// Nesting Submitted in: C++ 100%
int Nesting(string &S) {
    vector<char> list;
    for (char c : S) {
        if (c == '(') {
            list.push_back(c);
        } else {
            if (c == ')' && !list.empty() && list.back() == '(') {
                list.pop_back();
            } else {
                return 0;
            }
        }
    }
    if (!list.empty()) {
        return 0;
    }
    return 1;
}

// MinAvgTwoSlice Submitted in: C++ 100%
// The trick to this problem is that the min average slice also cannot be longer than 3.
// So we only have to calculate the avg of the slices of length 2 and 3.
// No matter which way we split up this array, if the slices aren't exactly the same,
// then one of them must have a lower average than the full slice.
int MinAvgTwoSlice(vector<int> &A) {
    int p = 0;
    double avg_min = 10000, avg2, avg3;
    unsigned long n = A.size();
    for (int i = 0; i < n - 1; i++) {
        avg2 = (A[i] + A[i + 1]) / 2.0;
        if (avg2 < avg_min) {
            avg_min = avg2;
            p = i;
        }
        if (i + 2 < n) {
            avg3 = (A[i] + A[i + 1] + A[i + 2]) / 3.0;
            if (avg3 < avg_min) {
                avg_min = avg3;
                p = i;
            }
        }
        //cout << "avg_min: " << avg_min << endl;
    }
    return p;
}

// EquiLeader Submitted in: C++ 100%
int EquiLeader(vector<int> &A) {
    map<int, set<int>> counter;
    for (int i = 0; i < A.size(); i++) {
        counter[A[i]].insert(i);
    }

    int value = 0;
    long occur = 0;
    long occur_max = 0;
    for (auto &pair : counter) {
        occur = pair.second.size();
        if (occur > occur_max) {
            value = pair.first;
            occur_max = occur;
        }
    }

    int num_of_leader = 0;
    occur = 0;
    for (unsigned int i = 0; i < A.size() - 1; i++) {
        if (A[i] == value) {
            occur++;
        }
        if (occur * 1.0 / (i + 1) > 0.5 && (occur_max - occur) * 1.0 / (A.size() - i - 1) > 0.5) {
            num_of_leader++;
        }
        /*
        cout << i << ' ';
        cout << occur*1.0/(i+1) << ' ';
        cout << (occur_max-occur)*1.0/(A.size()-i-1) << ' ';
        cout << num_of_leader << ' ';
        cout << endl;
        */
    }
    return num_of_leader;
}

//Dominator Submitted in: C++ 100%
//important: use the think of stack to redo!
//see "The Leader" in codility.py
int Dominator(vector<int> &A) {
    map<int, set<int>> counter;
    for (unsigned int i = 0; i < A.size(); i++) {
        counter[A[i]].insert((int) i);
    }

    unsigned long occur_max = 0;
    set<int> *result = nullptr;
    for (auto &pair : counter) {
        if (pair.second.size() > occur_max) {
            occur_max = pair.second.size();
            result = &pair.second;
        }
    }

    if (result != nullptr && occur_max * 1.0 / A.size() > 0.5) {
        return *(*result).begin();
    }
    return -1;
}

//MaxSliceSum Submitted in: C++ 100%
int MaxSliceSum(vector<int> &A) {
    int result = A[0];
    int max_prev = 0;
    for (int a : A) {
        max_prev = max(a, max_prev + a);
        result = max(result, max_prev);
    }
    return result;
}

// MaxDoubleSliceSum Submitted in: C++ 100%
int MaxDoubleSliceSum(vector<int> &A) {
    int double_slice_sum_max = 0;
    int left_slice_sum[A.size()], right_slice_sum[A.size()];
    left_slice_sum[0] = 0, right_slice_sum[A.size() - 1] = 0;
    for (unsigned long i = 1, j = A.size() - 2; i < A.size(); i++, j--) {
        left_slice_sum[i] = max(left_slice_sum[i - 1] + A[i], 0);
        right_slice_sum[j] = max(right_slice_sum[j + 1] + A[j], 0);
    }
    /*
    for(int s: right_slice_sum){
        cout << s << ' ';
    }
    */
    for (unsigned int i = 1; i < A.size() - 1; i++) {
        double_slice_sum_max = max(double_slice_sum_max,
                                   left_slice_sum[i - 1] + right_slice_sum[i + 1]);
    }
    return double_slice_sum_max;
}

// CountFactors Submitted in: C++
int CountFactors(int N) {
    int k = 0;
    int i = 1;
    auto sqrt_n = (int) sqrt(N);
    while (i <= sqrt_n) {
        if (N % i == 0) {
            k += 2;
        }
        i++;
    }
    if (sqrt_n * sqrt_n == N) {
        k -= 1;
    }
    return k;
}

// MinPerimeterRectangle Submitted in: C++ 100%
int MinPerimeterRectangle(int N) {
    auto a = (int) sqrt(N);
    while (N % a != 0) {
        a--;
    }
    return 2 * (a + N / a);
}

// Peaks Submitted in: C++ 100%
int Peaks(vector<int> &A) {
    vector<int> peak_indices;
    long len = A.size();
    for (int i = 1; i < len - 1; i++)
        if (A[i - 1] < A[i] && A[i] > A[i + 1])
            peak_indices.push_back(i);

    if (peak_indices.empty())
        return 0;

    int num_of_block = 0;
    for (int j = peak_indices[0] + 1; j <= len / 2; j++) {
        if (len % j == 0) {
            for (auto k : peak_indices) {
                if (j * num_of_block <= k && k <= j * (num_of_block + 1) - 1) {
                    num_of_block++;
                } else if (k <= j * num_of_block - 1) {
                    continue;
                } else {
                    break;
                }
            }
            if (num_of_block == len / j) {
                return num_of_block;
            } else {
                num_of_block = 0;
            }
        }
    }
    return 1;
}

// Flags Submitted in: C++ 100%
int Flags(vector<int> &A) {
    vector<int> peaks;
    for (int i = 1; i < A.size() - 1; i++)
        if (A[i - 1] < A[i] && A[i] > A[i + 1])
            peaks.push_back(i);

    if (peaks.size() <= 2)
        return (int) peaks.size();

    int flag_max = (int) sqrt(peaks[peaks.size() - 1] - peaks[0]) + 1;
    for (int k = flag_max; k >= 2; k--) {
        int position_count = 1;
        int position_current = peaks[0];
        for (unsigned int i = 1; i < peaks.size(); i++) {
            if (peaks[i] - position_current >= k) {
                position_count++;
                position_current = peaks[i];
            }
        }
        if (position_count >= k) return k;
    }
    return 2;
}

// Missing the lowest number
int FindMissingNumber(int arr[] , int size, int base = 1) {
    // Find the lowest missing number in the range [base, base + arr.length -1]
    // l and r are the left and right position in arr.
    // Position l is the current element being processed.
    // From Position r-1 inclusively, all elements have already processed and discarded.
    // arr[0..l-1] must not contain any duplicated elements,
    // and satisfy the strict increment of 1 one after another
    // beginning with base:
    // arr[0] = base
    // arr[1] = base + 1
    // ...
    // arr[l] = base + l
    int l = 0;
    int r = size;
    while (l < r) {
        if (arr[l] == base + l){
            l++;
        } else if (arr[l] < base || arr[l] > base+r-1 || arr[l] == arr[arr[l] - base]) {
            // arr[l] is either out of range, or a duplicate element in arr[0..l-1]
            arr[l] = arr[--r];
        } else {
            // Move arr[l] to the position in which it should be
            std::swap(arr[l], arr[arr[l] - base]);
            // Equivalent the following. Note: A[left] must be change at the end.
            // int temp = A[A[left]-1];
            // A[A[left]-1] = A[left];
            // A[left] = temp;
        }
    }
    return base + l;
}
