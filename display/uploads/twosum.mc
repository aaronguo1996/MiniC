
void printInteger(integer i);
void print(string str);

integer[] a := { 0, 2, 32, 23, 5, 2490, 4859, 24, 545, 3, 4, 6, 8, 423, 67, 345, 543, 233, 17, 18, 39, 21, 66, 9, 0, 49, 53, 77, 14, 20 };
integer[] b := {0,1,2,3,4};

boolean find(integer target, integer[] array,integer len){
    integer i := 0;
    integer[] hash := new integer[5000];


    for (i := 0; i < 5000; i++) {
        hash[i]:= -1;
    }

    for (i := 0; i < len; i++) {
        if(array[i]<target){
            if (hash[target - array[i]] !=-1) {
                print("the sum of ");
                printInteger(target);
                print(" is\nindex[");
                printInteger(hash[target - array[i]]);
                print("] ");
                printInteger(target-array[i]);
                print(" and index[");
                printInteger(i + 1);
                print("] ");
                printInteger(array[i]);
                print("\n\n");
                return true;
            }
        hash[array[i]] := i + 1;
        }
    }
    print("cannot find two sums of target ");
    printInteger(target);
    print("\n\n");
    return false;
}

find(55,a,30);//index 3 and index 4
find(111,a,30);//not found
find(2495,a,30);//index 5 and index 6
find(20,a,30);//index 10 and index 19
find(7,b,5);//index 4 and index 5
find(10,b,5);//not found