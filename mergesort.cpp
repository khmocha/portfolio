#include <iostream>

void PrintArray(int * Array, int Size) {
    for (int i = 0; i < Size; i++) {
        std::cout << Array[i] << " ";
    }

    std::cout << std::endl;
}

std::string CheckSortedAccuracy(int * Array, int Size) {
    for (int i = 1; i < Size; i++) {
        if (Array[i] < Array[i - 1]) {
            return "There is a bug in the sort";
        }
    }

    return "Sort works flawlessly !";
}

void MergeSort(int * Array, int Size, int StartingIndex, int EndingIndex) {
    int MidIndex = StartingIndex + ((EndingIndex - StartingIndex) / 2);

    if (EndingIndex - StartingIndex < 1) {
        return;
    }

    MergeSort(Array, Size, StartingIndex, MidIndex);
    MergeSort(Array, Size, MidIndex + 1, EndingIndex);

    int LeftHalfSize = MidIndex - StartingIndex;
    int RightHalfSize = EndingIndex - (MidIndex + 1);
    int FullSize = (EndingIndex - StartingIndex) + 1;
    int LeftHalfIndex = 0;
    int RightHalfIndex = 0;
    int * TempArray = new int [FullSize];
    int CurrentIndex = 0;
    
    while (LeftHalfIndex <= LeftHalfSize && RightHalfIndex <= RightHalfSize) {
        if (Array[StartingIndex + LeftHalfIndex] > Array[MidIndex + 1 + RightHalfIndex]) {
            TempArray[CurrentIndex] = Array[MidIndex + 1 + RightHalfIndex];
            RightHalfIndex++;
        } else {
            TempArray[CurrentIndex] = Array[StartingIndex + LeftHalfIndex];
            LeftHalfIndex++;
        }

        CurrentIndex++;
    }

    if (LeftHalfIndex <= LeftHalfSize) {
        for (int i = StartingIndex + LeftHalfIndex; i <= StartingIndex + LeftHalfSize; i++) {
            TempArray[CurrentIndex] = Array[i];
            CurrentIndex++;
        }
    } else {
        for (int i = MidIndex + 1 + RightHalfIndex; i <= MidIndex + 1 + RightHalfSize; i++) {
            TempArray[CurrentIndex] = Array[i];
            CurrentIndex++;
        }
    }

    CurrentIndex = 0;

    for (int i = StartingIndex; i <= EndingIndex; i++) {
        Array[i] = TempArray[CurrentIndex++];
    }

    delete [] TempArray;
    TempArray = nullptr;
}
