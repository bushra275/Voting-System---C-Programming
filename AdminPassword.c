#include<stdio.h>
int main(){
	char pwd[50];
	printf("enter admin password:");
	scanf("%s",pwd);
	FILE *pwds=fopen("password.txt","w");
	fprintf(pwds,"%s",pwd);
	return 0;
}