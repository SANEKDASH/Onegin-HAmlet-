#include <stdio.h>

void insertionSort(int a[], int n);

int binarySearch(int a[], int item,
                 int low, int high);

int main()
{

    int a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    insertionSort(a, 10);

    for (int i = 0; i < 10; i++)
    {
        printf("%d - %d\n", i, a[i]);
    }

}

int binarySearch(int a[], int item,
                 int low, int high)
{
    if (high <= low)
    {
        return (item > a[low]) ? (low + 1) : low;
    }

    int mid = (low + high) / 2;

    if (item == a[mid])
    {
        return mid + 1;
    }

    if (item > a[mid])
    {
        return binarySearch(a, item, mid + 1, high);
    }

    return binarySearch(a, item, low, mid - 1);
}

// Function to sort an array a[] of size 'n'
void insertionSort(int a[], int n)
{
    int i, loc, j, k, selected;

    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        selected = a[i];

        // find location where selected should be inserted
        loc = binarySearch(a, selected, 0, j);

        // Move all elements after location to create space
        while (j >= loc)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = selected;
    }
}
