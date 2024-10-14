#include <iostream>

void PrintArray(int * Array, int Size) {
    for (int i = 0; i < Size; i++) {
        std::cout << Array[i] << " ";
    }
    std::cout << "\n";
}

std::string CheckQSAccuracy(int * Array, int Size) {
    for (int i = 1; i < Size; i++) {
        if (Array[i] < Array[i - 1]) {
            return "There is a bug in the quicksort";
        }
    }

    return "Quicksort works flawlessly!";
}

void QuickSort(int * Array, int Size, int PivotIndex, int StartingIndex, int EndingIndex) {
    if (EndingIndex - StartingIndex < 1 || StartingIndex >= EndingIndex || StartingIndex < 0 
    || EndingIndex <= 0) {
        return;
    } else if (StartingIndex >= Size || EndingIndex >= Size || PivotIndex >= Size) {
        return;
    }

    int LeftGreaterIndex = StartingIndex;
    int RightSmallerIndex = EndingIndex - 1;
    int PivotValue = Array[PivotIndex];
    int NewSwapIndex = StartingIndex;

    bool LeftIndexFound = false;
    bool RightIndexFound = false;

    std::swap(Array[PivotIndex], Array[EndingIndex]);

    while (RightSmallerIndex > LeftGreaterIndex) {
        while (LeftGreaterIndex < EndingIndex) {
            if (Array[LeftGreaterIndex] > PivotValue) {
                LeftIndexFound = true;
                break;
            }

            LeftGreaterIndex++;
        }

        if (LeftIndexFound == false) {
            NewSwapIndex = LeftGreaterIndex;
            break;

        } else {
            LeftIndexFound = false;
        }

        while (RightSmallerIndex > LeftGreaterIndex) {
            if (Array[RightSmallerIndex] < PivotValue) {
                RightIndexFound = true;
                break;
            }

            RightSmallerIndex--;
        }

        if (RightIndexFound == false) {
            NewSwapIndex = LeftGreaterIndex;
            break;

        } else {
            RightIndexFound = false;
        }

        std::swap(Array[LeftGreaterIndex], Array[RightSmallerIndex]);
        NewSwapIndex = LeftGreaterIndex + 1;

        LeftGreaterIndex++;
        RightSmallerIndex--;
    }

    while (NewSwapIndex <= EndingIndex) {
        if (Array[NewSwapIndex] >= Array[EndingIndex]) {
            break;
        }

        NewSwapIndex++;
    }

    std::swap(Array[NewSwapIndex], Array[EndingIndex]);

    StartingIndex = EndingIndex - (EndingIndex - StartingIndex);
    PivotIndex = StartingIndex + 1;


    QuickSort(Array, Size, PivotIndex, StartingIndex, NewSwapIndex - 1);
    QuickSort(Array, Size, NewSwapIndex + 2, NewSwapIndex + 1, NewSwapIndex + (EndingIndex - NewSwapIndex));
}
