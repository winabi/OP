#ifndef lib_h
#define lib_h

// заміна елемента
template <typename T>
void swap_parts(T *arr, int size, int start_idx, int end_idx)
{
    if (start_idx >= end_idx)
    {
        throw -2;
    }

    int part_size = (end_idx - start_idx + 1) / 2;
    for (int i = 0; i < part_size; i++)
    {
        T tmp = arr[start_idx + i];
        arr[start_idx + i] = arr[end_idx - i];
        arr[end_idx - i] = tmp;
    }
}

// пошук елемента за значенням
template <typename T>
int find_element(T *arr, const T &value, int size)
{
    int search = false;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value)
        {
            search = true;
            return i;
        }
    }

    if (!search)
    {
        throw -1;
    }
}

// заміна парних з непарними
template <typename T>
void swap_couples(T *arr, int size)
{
    for (int i = 1; i < size; i += 2)
    {
        T tmp = arr[i - 1];
        arr[i - 1] = arr[i];
        arr[i] = tmp;
    }
}

#endif