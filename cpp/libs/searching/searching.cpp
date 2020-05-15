#include "searching.h"

using namespace searching_element;
namespace wrap = searching_element::wrappers;

position binary_search::iterative_first(const array_details &arr_det, int searched_value) {
    const smart_2D &md_arr = arr_det.dimensional_array;

    if (md_arr[0].get()[0] <= searched_value and
        md_arr[arr_det.rows - 1].get()[arr_det.columns - 1] >= searched_value) {
        int start = 0, end = arr_det.columns - 1;

        for (int i = 0; i < arr_det.rows; i++) {
            int *row = md_arr[i].get();

            if (row[0] <= searched_value and row[arr_det.columns - 1] >= searched_value) {
                while (start <= end) {
                    int mid = (start + end) / 2;
                    if (row[mid] == searched_value) {
                        while (row[mid - 1] == searched_value) {
                            mid--;
                        }
                        return {i, mid};
                    } else if (row[mid] < searched_value) {
                        start = mid + 1;
                    } else {
                        end = mid - 1;
                    }
                }
            }
        }
    }
    return {-1, -1};
}


position binary_search::iterative_last(const array_details &arr_det, int searched_value) {
    const smart_2D &md_arr = arr_det.dimensional_array;

    if (md_arr[0].get()[0] <= searched_value and
        md_arr[arr_det.rows - 1].get()[arr_det.columns - 1] >= searched_value) {
        int start = 0, end = arr_det.columns - 1;

        for (int i = arr_det.rows - 1; i >= 0; i--) {
            int *row = md_arr[i].get();

            if (row[0] <= searched_value and row[arr_det.columns - 1] >= searched_value) {
                while (start <= end) {
                    int mid = (start + end) / 2;
                    if (row[mid] == searched_value) {
                        while (row[mid + 1] == searched_value) {
                            mid++;
                        }
                        return {i, mid};
                    } else if (row[mid] < searched_value) {
                        start = mid + 1;
                    } else {
                        end = mid - 1;
                    }
                }
            }
        }
    }
    return {-1, -1};
}


position binary_search::recursive::wrapper(const array_details &arr_det, int searched_value, MODE search_mode) {
    const smart_2D &md_arr = arr_det.dimensional_array;

    if (md_arr[0].get()[0] <= searched_value and
        md_arr[arr_det.rows - 1].get()[arr_det.columns - 1] >= searched_value) {
        if (search_mode == MODE::FIRST_OCCURRENCE) {
            return unpack_row_first(arr_det, 0, searched_value);
        } else {
            return unpack_row_last(arr_det, arr_det.rows - 1, searched_value);
        }
    } else {
        return {-1, -1};
    }
}

position
binary_search::recursive::unpack_row_first(const array_details &arr_det, int processed_rows, int searched_value) {
    const smart_2D &md_arr = arr_det.dimensional_array;
    const int *current_row = md_arr[processed_rows].get();

    int column = binary_search::recursive::process_row(current_row, 0, arr_det.columns - 1, searched_value);

    if (column != -1) {
        column = check_first(current_row, column, searched_value);
        return {processed_rows, column};
    } else if (processed_rows < arr_det.rows) {
        return unpack_row_first(arr_det, processed_rows + 1, searched_value);
    } else {
        return {-1, -1};
    }
}

position
binary_search::recursive::unpack_row_last(const array_details &arr_det, int processed_rows, int searched_value) {
    const smart_2D &md_arr = arr_det.dimensional_array;
    const int *current_row = md_arr[processed_rows].get();

    int column = binary_search::recursive::process_row(current_row, 0, arr_det.columns - 1, searched_value);

    if (column != -1) {
        column = check_last(current_row, column, searched_value);
        return {processed_rows, column};
    } else if (processed_rows >= 0) {
        return unpack_row_last(arr_det, processed_rows - 1, searched_value);
    } else {
        return {-1, -1};
    }
}

int binary_search::recursive::process_row(const int *column, int start, int end, int searched_value) {
    if (start <= end) {
        int mid = (start + end) / 2;
        if (column[mid] == searched_value) {
            return mid;
        } else if (column[mid] < searched_value) {
            return process_row(column, mid + 1, end, searched_value);
        } else {
            return process_row(column, start, mid - 1, searched_value);
        }
    }
    return -1;
}

int binary_search::recursive::check_first(const int *row, int column, int searched_value) {
    if (row[column - 1] == searched_value) {
        return check_first(row, column - 1, searched_value);
    } else {
        return column;
    }
}

int binary_search::recursive::check_last(const int *row, int column, int searched_value) {
    if (row[column + 1] == searched_value) {
        return check_last(row, column + 1, searched_value);
    } else {
        return column;
    }
}

position wrap::recursive_first_occurring(const array_details &arr_det, int searched_value) {
    return binary_search::recursive::wrapper(arr_det, searched_value, MODE::FIRST_OCCURRENCE);
}

position wrap::recursive_last_occurring(const array_details &arr_det, int searched_value) {
    return binary_search::recursive::wrapper(arr_det, searched_value, MODE::LAST_OCCURRENCE);
}

position wrap::iterative_first_occurring(const array_details &arr_det, int searched_value) {
    return binary_search::iterative_first(arr_det, searched_value);
}

position wrap::iterative_last_occurring(const array_details &arr_det, int searched_value) {
    return binary_search::iterative_last(arr_det, searched_value);
}
