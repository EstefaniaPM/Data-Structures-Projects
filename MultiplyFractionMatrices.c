// Estefania Pitol Martinez A01551688
// Fernanda Montano Rios 	A01730440
// 11 October 2017
#include <stdio.h>
#include <stdlib.h>

struct fraction {
	int num, den;
};

// Gets the greatest common divisor of two numbers
// Parameter a - first number
// Parameter b - second number
// Returns - gcd
int gcd(int a, int b) {
	if(b == 0)
       return a;
   	else
       return gcd(b, a % b);
}

// Simplifies the fraction
// Parameter p - pointer to the fraction
void simplify(struct fraction *p) {
	int g;
	g = gcd(p -> num, p -> den);
	p -> num /= g;
	p -> den /= g;
}

// Sums up two fractions
// Parameter p1 - pointer to the first fraction
// Parameter p2 - pointer to the second fraction
// Parameter p3 - pointer to where the result will be stored
void sum(struct fraction *p1, struct fraction *p2, struct fraction *p3) {
 	int n, d;
	n = (p1 -> num * p2 -> den) + (p2 -> num * p1 -> den);
	d = p1 -> den * p2 -> den;
	p3 -> num = n;
	p3 -> den = d;
}

// Multiply two fractions
// Parameter p1 - pointer to the first fraction
// Parameter p2 - pointer to the second fraction
// Parameter p3 - pointer to where the result will be stored
void mul(struct fraction *p1, struct fraction *p2, struct fraction *p3) {
	int n, d;
	n = p1 -> num * p2 -> num;
	d = p1 -> den * p2 -> den;
	p3 -> num = n;
	p3 -> den = d;
}

// Reads the fractions and add them to the matrix
// Parameter p - pointer to the matrix
// Parameter r - rows of the matrix
// Parameter c - columns of the matrix
void readMatrix(struct fraction *p, int r, int c) {
	int n, d, i;
	for(int i = 0; i < r*c; i++) {
		scanf("%d", &n);
		scanf("%d", &d);
		(*p).num = n;
		(*p).den = d;
		p++;
	}
}

// Counts the digits of a number
// Parameter n - number
// Returns - number of digits
int countDigits(int n) {
	int counter;
	counter = 1;
    while(n / 10 != 0) {
        n /= 10;
        counter++;
    }
	return counter;
}

// Gets the largest number of digits in the numerators of the Fraction matrix
// Parameter p - pointer to the matrix
// Parameter r - rows of the matrix
// Parameter c - columns of the matrix
// Returns - largest number of digits
int maxLengthNum(struct fraction *p, int r, int c) {
	int max, i;
	max = 0;
	for(i = 0; i < r*c; i++) {
		if(p -> num > max)
			max = p -> num;
		p++;
	}
	return countDigits(max);
}

// Gets the largest number of digits in the denominators of the Fraction matrix
// Parameter p - pointer to the matrix
// Parameter r - rows of the matrix
// Parameter c - columns of the matrix
// Returns - largest number of digits
int maxLengthDen(struct fraction *p, int r, int c) {
	int max, i;
	max = 0;
	for(i = 0; i < r*c; i++) {
		if(p -> den > max)
			max = p -> den;
		p++;
	}
	return countDigits(max);
}

// Prints the fraction matrix using a format
// Parameter p - pointer to the matrix
// Parameter r - rows of the matrix
// Parameter c - columns of the matrix
void printMatrix(struct fraction *p, int r, int c) {
	int i, j, maxNum, maxDen, spacesn, spacesd, k, thereIsANegative, numNeg;
	thereIsANegative = 0;
	numNeg = 0;
	struct fraction *p2;
	p2 = p;
	for(int i = 0; i < r*c; i++) {
		simplify(p2);
		if((p2 -> num < 0 && p2 -> den < 0) || (p2 -> num >= 0 && p2 -> den < 0)) {
			p2 -> num -= (p2 -> num) * 2;
			p2 -> den -= (p2 -> den) * 2;
		}
		//if(p2 -> den < 0) {
		//	p2 -> num *= -1;
		//	p2 -> den *= -1;
		//}
		if(p2 -> num < 0) {
			thereIsANegative = 1;
			if(p2 -> num < numNeg)
				numNeg = p2 -> num;
		}
		p2++;
	}
	maxNum = maxLengthNum(p, r, c);
	maxDen = maxLengthDen(p, r, c);
	if(thereIsANegative == 1 && countDigits(abs(numNeg)) >= maxNum)
		maxNum++;
	for(i = 0; i < r; i++) {
		for(j = 0; j < c; j++) {
			spacesn = maxNum - countDigits(p -> num);
			spacesd = maxDen - countDigits(p -> den);
			if(p -> num < 0)
				spacesn--;
			for(k = 0; k < spacesn; k++)
				printf(" ");
			printf("%d/", p -> num);
			for(k = 0; k < spacesd; k++)
				printf(" ");
			printf("%d  ", p -> den);
			p++;
		}
		printf("\n");
	}
}

// Multiply two fraction matrices
// Parameter p1 - pointer to the first fraction
// Parameter p2 - pointer to the second fraction
// Parameter p3 - pointer to where the result will be stored
// Parameter r1 - rows of the first matrix
// Parameter c1 - columns of the first matrix
// Parameter c2 - columns of the second matrix
void multiply(struct fraction *p1, struct fraction *p2, struct fraction *p3, int r1, int c1, int c2){
    struct fraction totalSum, aux;
    totalSum.num = 0;
	totalSum.den = 1;
    for(int i = 0; i < r1; i++){
        for(int j = 0; j < c2; j++) {
            for(int k = 0; k < c1; k++) {
            	mul((p1 + ((i * c1) + k)), (p2 + ((k * c2) + j)), &aux);
            	sum(&aux, &totalSum, &totalSum);
            }
            (p3 + ((i * c2) + j)) -> num = totalSum.num;
            (p3 + ((i * c2) + j)) -> den = totalSum.den;
            totalSum.num = 0;
            totalSum.den = 1;
        }
    }
}

// Principal method for the program execution
// Returns - 0
int main() {
	int r1, c1, r2, c2;
	printf("Number of rows in the first matrix:\n");
	scanf("%d", &r1);
	printf("Number of columns in the first matrix:\n");
	scanf("%d", &c1);
	printf("Number of rows in the second matrix:\n");
	scanf("%d", &r2);
	printf("Number of columns in the second matrix:\n");
	scanf("%d", &c2);
	if(c1 == r2) {
		struct fraction m1[r1][c1], m2[r2][c2], m3[r1][c2];
        printf("Insert the fractions for the first matrix:\n");
        readMatrix((struct fraction *)m1, r1, c1);
        printf("Insert the fractions for the second matrix:\n");
        readMatrix((struct fraction *)m2, r2, c2);
        printf("\n");
        printMatrix((struct fraction *)m1, r1, c1);
        printf("\nX\n\n");
        printMatrix((struct fraction *)m2, r2, c2);
        printf("\n=\n\n");
        multiply((struct fraction *)m1, (struct fraction *)m2, (struct fraction *)m3, r1, c1, c2);
        printMatrix((struct fraction *)m3, r1, c2);
	}
	else
		printf("The operation is impossible\n");
	return 0;
}