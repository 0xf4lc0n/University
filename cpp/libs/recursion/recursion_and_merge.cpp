#include "recursion_and_merge.h"
#include "../input_sanitization/input_sanitization.tcc"
namespace rw = recursion::wrappers;
namespace ra = recursion::auxiliary;

int rw::f_wielomian(int n, const int *a, int x) {
    if (n == 0) {
        return a[n];
    } else {
        return a[n] * ra::pow(x, n) + rw::f_wielomian(n - 1, a, x);
    }
}

const int *rw::f_maximum(int N, const int *t) {
    if (N < 0 and t == nullptr) {
        return nullptr;
    } else if (N == 1) {
        return &t[0];
    } else {
        return &ra::max(t[N - 1], *rw::f_maximum(N - 1, t));
    }
}

int rw::f_newton(int N, int K) {
    if (K <= N and N <= 33) {
        if (K == 0 or K == N) {
            return 1;
        } else {
            return rw::f_newton(N - 1, K - 1) + rw::f_newton(N - 1, K);
        }
    } else if (N < K) {
        return 0;
    } else {
        return -1;
    }
}

unsigned int rw::f_srednia_warunkowa(double &s, bool (*f)(int), const int *b, const int *e) {
    int valid_values = ra::valid_elements(b, e, f);

    if (valid_values) {
        s = double(ra::conditional_sum(b, e, f)) / valid_values;
        return valid_values;
    } else {
        return 0;
    }
}


bool rw::f_suma_wazona(double &s, const double *b, const double *e, const double *a) {
    bool valid_values = ra::is_positive(b, e);
    double sum_of_weights = ra::sum(b, e);

    if (valid_values and sum_of_weights <= 1) {
        s = ra::weighted_sum(b, e, a);
        s += ra::last_element(b, e, a) * (1 - sum_of_weights);
        return true;
    } else {
        return false;
    }
}

int ra::pow(int x, int y) {
    if (y == 0) {
        return 1;
    } else {
        return x * ra::pow(x, y - 1);
    }
}

double ra::weighted_sum(const double *b, const double *e, const double *a) {
    if (b == e - 1) {
        return *b * *a;
    } else {
        return *b * *a + ra::weighted_sum(b + 1, e, a + 1);
    }
}


double ra::last_element(const double *b, const double *e, const double *a) {
    if (b == e - 1) {
        return *(a + 1);
    } else {
        return ra::last_element(b + 1, e, a + 1);
    }
}

bool ra::is_positive(const double *b, const double *e) {
    if (b == e - 1) {
        return *b >= 0.0;
    } else {
        return (*b >= 0.0) * ra::is_positive(b + 1, e);
    }
}

double ra::sum(const double *b, const double *e) {
    if (b == e - 1) {
        return *b;
    } else {
        return *b + ra::sum(b + 1, e);
    }
}

int ra::valid_elements(const int *b, const int *e, bool (*f)(int)) {
    if (b == e - 1) {
        return f(*b);
    } else {
        return f(*b) + ra::valid_elements(b + 1, e, f);
    }
}


int ra::conditional_sum(const int *b, const int *e, bool (*f)(int)) {
    if (b == e - 1) {
        return (f(*b)) ? *b : 0;
    } else {
        if (f(*b)) {
            return *b + ra::conditional_sum(b + 1, e, f);
        }
    }
    return 0;
}

int merge::merge_sort(std::vector<int> &num_array, std::vector<int> &temp, int start_index, int end_index) {
    int inversions = 0;
    int middle_index = 0;

    if (end_index > start_index) {
        middle_index = (start_index + end_index) / 2;

        inversions += merge_sort(num_array, temp, start_index, middle_index);
        inversions += merge_sort(num_array, temp, middle_index + 1, end_index);
        inversions += merge_arrays(num_array, temp, start_index, middle_index + 1, end_index);
    }
    return inversions;
}

int merge::merge_arrays(std::vector<int> &num_array, std::vector<int> &temp, int start_index, int middle_index,
                        int end_index) {
    int local_num_arr_start = start_index;
    int local_num_arr_middle = middle_index;
    int local_temp_arr_start = start_index;
    int inversions = 0;

    while ((local_num_arr_start <= middle_index - 1) && (local_num_arr_middle <= end_index)) {
        if (num_array[local_num_arr_start] <= num_array[local_num_arr_middle]) {
            temp[local_temp_arr_start++] = num_array[local_num_arr_start++];
        } else {
            temp[local_temp_arr_start++] = num_array[local_num_arr_middle++];
            inversions = inversions + (middle_index - local_num_arr_start);
        }
    }

    while (local_num_arr_start <= middle_index - 1)
        temp[local_temp_arr_start++] = num_array[local_num_arr_start++];

    while (local_num_arr_middle <= end_index)
        temp[local_temp_arr_start++] = num_array[local_num_arr_middle++];

    for (int i = start_index; i <= end_index; i++) {
        num_array[i] = temp[i];
    }

    return inversions;
}
