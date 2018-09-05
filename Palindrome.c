// Estefania Pitol Martinez 	A01551688
// Fernanda Montano Rios 		A01730440
#include <stdio.h>

// This program receives a string of chars and outputs if it is a palindorm or not
int main(int argc, char const *argv[]){
	
	int cases;
	scanf("%d\n", &cases);

	int i;
	for(i = 0; i < cases; i++){
		char str[1025];
		fgets(str, 1024, stdin);

		char *p1, *p2;
		p1 = str;
		p2 = str;

		while(*p2 != '\0')
			p2++;
		p2-=2;

		int isPalindrome = 0;

		while(p1 < p2){
			if(*p1 != *p2){
				isPalindrome = 1;
				break;
			}
			p1++;
			p2--;
		}

		if(isPalindrome == 0)
			printf("YES\n");
		else
			printf("NO\n");
	}
}