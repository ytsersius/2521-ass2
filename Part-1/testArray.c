#include <stdio.h>

int main()  {

    double PRWArray[17];
	int i;
	for (i = 0; i < 17; i++)	{
		PRWArray[i] = 1.0/17;
        printf("%lf\n", PRWArray[i]);
	}
    return 0;
}