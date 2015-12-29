void print(string str);
void printInteger(integer i);

integer reverseInteger(integer a)
{
    if (a = 0) {
        return a;
    }
    boolean flag := false;
    if (a < 0) {
        flag := true;
        a := -a;
    }
    integer b := 0;
    while (a > 0)
    {
        b := b * 10;
        b := b + a % 10;
        a := a / 10;
    }
    if (flag) {
        b := -b;
    }
    return b;
}

integer x := 123;
integer y := -123;
integer z := 0;
integer m := 39;
integer n := 91;

//print("reverse 123 is ");
printInteger(reverseInteger(x));
print("\n\n");
//print("reverse -123 is ");
printInteger(reverseInteger(y));
print("\n\n");
//print("reverse 0 is ");
printInteger(reverseInteger(z));
print("\n\n");
//print("reverse 39 is ");
printInteger(reverseInteger(m));
print("\n\n");
//print("reverse 91 is ");
printInteger(reverseInteger(n));