typedef struct {
   int x;
   int y;
} ms;

intint main(int a, int b)
{
    ms var[5];
    ms (*ptr)[]=&var;
    var[0].x=a;
    var[0].y=b;
    //@ assert (*ptr)[0].x == a;
    return 0;
}
