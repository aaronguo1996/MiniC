void print(string str);
void printInteger(integer i);

integer quickSort(integer[] a, integer low, integer high)
{ 
    low1 := 0;
    if (low >= high)
    {
        return; 
    } 
    integer first := low;
    integer last := high;
integer key := a[first];

    while (first < last)
    { 
        while (first < last && a[last] >= key)
        { 
            last--;
        }
        
        a[first] := a[last];
        
        while(first < last && a[first] <= key)
        {
            first++;        
        }        
        
        a[last] := a[first];       
        }
    
        a[first] := key;   
        quickSort(a, low, first-1);    
        quickSort(a, first+1, high);    
        return 0;
}

integer[] array := { -1, 2, 32, 23, 5, 2490, 4859, 24, 545, 3, 4, 6, 8, 423, 67, 345, 543, 233, 17, 18, 39, 21, 66, 9, 0, 49, 53, 77, 14, 20 };
quickSort(array, 0, 29);

integer i := 0;
for ( ;i < 30; i++)
{
print(" ");
//print("a");
    
printInteger(array[i]);
}
print("\n");
