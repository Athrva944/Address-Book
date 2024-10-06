

/*
Description:addressbok main project
 */
#include<stdio.h>
#include<string.h>
#include<stdio_ext.h>
struct data
{
	char name[30];
	char mobile[11];
	char email[30];
	char address[50];
};
void add_contact();
void copy(FILE* , FILE* );
void search();
void print();
void delete();
void edit();
int main()
{
	char ch='y';
	int choice;
	while(ch=='y' || ch=='Y')
	{
		choice=0;
		printf("1>Add Contacts\n2>Search contact\n3>Print data\n4>Edit data\n5>Delete\nEnter your choice: ");
		scanf("%d",&choice);
		printf("-----------------------------------------------------------\n");
		switch(choice)
		{
			case 1:
				add_contact();
				break;
			case 2:
				search();
				break;
			case 3:
				print();
				break;
			case 4:
				edit();
				break;
			case 5:
				delete();
				break;
			default:
				__fpurge(stdin);
				printf("Invalid choice\n"); 
		}
		printf("Do you want to continue (y/n): ");
		scanf(" %c",&ch);
	}
}
void add_contact()
{
	struct data contacts;
	FILE *ptr=fopen("main.csv","r");
	FILE *ptr1=fopen("temp.csv","w");
	if(ptr==NULL)
	{
		printf("Data is empty");
		return;
	}
	int count;
	fscanf(ptr,"%d\n",&count);
	fprintf(ptr1,"%d\n",count+1);
	for(int i=0;i<count;i++)
	{
		fscanf(ptr,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		fprintf(ptr1,"%s,%s,%s,%s\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
	}
	char str1[40];
	printf("Enter the name: ");
	scanf(" %[a-z A-Z]",str1);
	__fpurge(stdin);
	char str2[10];
num1:
	printf("Enter mobile number: ");
	scanf(" %[0-9]",str2);
	__fpurge(stdin);
	//	fseek(ptr,2,SEEK_SET);
	int flag;
	for(int i=0;i<count;i++)
	{
		flag=0;
		fscanf(ptr,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		if(strcmp(str2,contacts.mobile)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		printf("This Number already exists\n           Try Agian          \n");
		goto num1;
	}
	int n=strlen(str2);
	if(n>10 || n<10)
	{
		printf("Entered number should be in 10 digits.Enter correctly!\n       Try Again      \n");
		goto num1;
	}
	strcpy(contacts.mobile,str2);
	char str3[40];
email1:
	printf("Enter the email: ");
	scanf(" %[^\n]",str3);
	char str[30];
	strcpy(str,str3);
	char *p;
	p=strchr(str,'@');
	if(p!=NULL)
	{
		if(p[1]=='.')
		{
			printf("Error!!!After @ put atleast one character before .com\n");
			goto email1;
		}
		else if((p[1]>='a' && p[1]<='z') || (p[1]>='A' && p[1]<='Z'));

	}		else
	{
		printf("Error!!!Entered character after @ is not alphabetic,put alphabets.\n");
		goto email1;
	}
	int flag3;
	for(int i=0;i<count;i++)
	{
		flag3=0;
		fscanf(ptr,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		if(strcmp(str3,contacts.email)==0)
		{
			flag3=1;
			break;
		}
	}
	if(flag3==1)
	{
		printf("This email ID already exists\n        Try again        \n");
		goto email1;
	}
	strcpy(contacts.email,str3);
	strcpy(contacts.name,str1);
	printf("Enter Address: ");
	scanf(" %[^\n]",contacts.address);
	fprintf(ptr1,"%s,%s,%s,%s\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
	fclose(ptr);
	fclose(ptr1);
	ptr=fopen("main.csv","w");
	ptr1=fopen("temp.csv","r");
	copy(ptr,ptr1);
	fclose(ptr);
	fclose(ptr1);
}
void copy(FILE *ptr,FILE *ptr1)
{
	char ch;
	while((ch=fgetc(ptr1))!=EOF)
	{
		fputc(ch,ptr);
	}
}
void search()
{
	struct data contacts;

	FILE *ptr=fopen("main.csv","r");
	
	char new_name[30],new_mobile[11];
	
	int count;
	
	printf("Enter the name: ");
	scanf(" %[^\n]",new_name);
	
	fscanf(ptr,"%d\n",&count);
	
	int flag=0;
	for(int i=0;i<count;i++)
	{
		fscanf(ptr,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		if(strcmp(new_name,contacts.name)==0)
		{
			flag++;
		}
	}
	fclose(ptr);
	
	ptr=fopen("main.csv","r");
	fscanf(ptr,"%d\n",&count);
	if(flag==0)
	{
		printf("User doesn't exist\n");
		return;
	}
	else if(flag==1)
	{
		for(int i=0;i<count;i++)
		{
			fscanf(ptr,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
			if(strcmp(new_name,contacts.name)==0)
			{
				printf("%s,%s,%s,%s\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
			}
		}
	}
	else
	{
		int temp=0;

		printf("This name matches more than once,so enter mobile number to get the details: ");
		scanf(" %[^\n]",new_mobile);
		for(int i=0;i<count;i++)
		{	
			fscanf(ptr,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
			if(strcmp(new_name,contacts.name)==0 && strcmp(new_mobile,contacts.mobile)==0)
			{
				printf("%s,%s,%s,%s\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
				temp=1;
			}
		}
		if(temp==0)
		{
			printf("This mobile number doesn't exist in data!!!Enter correctly\n");
		}

	}
	fclose(ptr);
}
void print()
{
	struct data contacts;
	FILE *ptr=fopen("main.csv","r");
	int count;
	fscanf(ptr,"%d\n",&count);
	for(int i=0;i<count;i++)
	{	
		fscanf(ptr,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		printf("Name : %s\nMobile : %s\nEmail : %s\nAddress : %s\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		printf("---------------------------------------------------\n");
	}
	fclose(ptr);
}
void edit()
{
	int var=1;
	int opt;
	int count;
	char new_name[30];
	char new_mobile[10];
	char new_mobile1[10];
	char new_email[30];
	char new_address[30];
	struct data contacts;
	FILE *ptr=fopen("main.csv","r");
	FILE *ptr1=fopen("temp.csv","w");
	printf("Enter the mobile number of the person,whom data you want to edit: ");
	scanf(" %[^\n]",new_mobile);
	fscanf(ptr,"%d\n",&count);
	fprintf(ptr1,"%d\n",count);
	int flag=0;
	for(int i=0;i<count;i++)
	{
		fscanf(ptr,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		if(strcmp(new_mobile,contacts.mobile)==0)
		{
		printf("Name : %s\nMobile : %s\nEmail : %s\nAddress : %s\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
		printf("---------------------------------------------------\n");
			flag=1;
			while(var)
			{
				printf("1: Name\n2: Email\n3: Address\n4:Mobile\n5: Exit!\n");
				printf("Enter your choice: \n");
				scanf("%d",&opt);
				switch(opt)
				{
					case 1:
						printf("Enter the new name: \n");
						scanf(" %[^\n]",new_name);
						strcpy(contacts.name,new_name);
						break;
					case 2:
email2:
						printf("Enter new wmail: \n");
						scanf(" %[^\n]",new_email);
						int flag4;
						for(int i=0;i<count;i++)
						{
							flag4=0;
							if(strcmp(new_email,contacts.email)==0)
							{
								flag4=1;
								break;
							}
						}
						if(flag4==1)
						{
							printf("This email id already exists\n               Try Again                 \n");
							goto email2;
						}
						for(int i=0;new_email[i];i++)
						{
							if(new_email[i]=='@')
							{
								if(strstr(new_email,".com")!=NULL)
								{
									if(new_email[i+1]=='.')
									{
										printf("Enter correct email ID\n");
										goto email2;

									}
								}
							}

						}
						strcpy(contacts.email,new_email);
						break;
					case 3:
						printf("Enter the new address: \n");
						scanf(" %[^\n]",contacts.address);
						break;
					case 4:
new:
						printf("Enter the mobile number: ");
						scanf(" %[^\n]",new_mobile1);
						int flag5;
						for(int i=0;i<count;i++)
						{
							flag5=0;
							if(strcmp(new_mobile1,contacts.mobile)==0)
							{
								flag5=1;
								break;
							}
						}
						if(flag5==1)
						{
							printf("This mobile number already exists\nTry again\n");
							goto new;
						}
						int num2=strlen(new_mobile);
						if(num2>10 || num2<10)
						{
							printf("Enter 10 digit mobile number\nTry again\n");
							goto new;
						}
						strcpy(contacts.mobile,new_mobile);
					case 5:
						var=0;
						break;
				}
			}						
		}
		fprintf(ptr1,"%s,%s,%s,%s\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
	}
	if(flag==0)
	{
		printf("Please enter the valid mobile number!\n");
	}
	fclose(ptr);
	fclose(ptr1);
	ptr=fopen("main.csv","w");
	ptr1=fopen("temp.csv","r");
	copy(ptr,ptr1);
	fclose(ptr);
	fclose(ptr1);
}
void delete()
{
	struct data contacts;
	char new_mobile[11];
	int count;
	FILE *ptr=fopen("main.csv","r");
	FILE *ptr1=fopen("temp.csv","w");
	fprintf(ptr1," %c",'\n');	
	printf("Enter the mobile number of person,whom data you want to delete: ");
	scanf(" %[^\n]",new_mobile);
	fscanf(ptr,"%d\n",&count);
	int flag=0;
	while(!feof(ptr))
	{
		for(int i=0;i<count;i++)
		{
			fscanf(ptr,"%[^,],%[^,],%[^,],%[^\n]\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
			if(strcmp(new_mobile,contacts.mobile)==0)
			{
				flag=1;
				printf("Data Successfully Deleted!\n");
				continue;
			}
			else
			{
				fprintf(ptr1,"%s,%s,%s,%s\n",contacts.name,contacts.mobile,contacts.email,contacts.address);
			}
		}
	}
	if(flag==0)
	{
		printf("Please enter the correct number!\n");
		count=count+1;
	}
	rewind(ptr1);
	fprintf(ptr1,"%d",count-1);
	fclose(ptr);
	fclose(ptr1);
	ptr=fopen("main.csv","w");
	ptr1=fopen("temp.csv","r");
	copy(ptr,ptr1);
	fclose(ptr);
	fclose(ptr1);
}

