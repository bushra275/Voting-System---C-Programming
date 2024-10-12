//HEADER FILES
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <time.h>

//FUNCTION PROTOTYPES
int admin();
int user();
int agecheck(int,int,int);
int registerVoter();
int createElectionScheduele();
int registerCandidate();
int NewCandidateList(int);
int CandidateList(int);
int DelCandidate();
int voterSNO();
int updateVoterList();
int searchVoterList();
int CastVote();
int DisplayVoteResult();

//structure for Date of Birth
struct DOB
	{
		int year;
		int month;
		int day;
	};
	
//Structure for User Information
struct UserInfo
{
	char Name[30];
	char address[40];
	char password[20];
	struct DOB DOB;				//Structure Variable Declared
};

//structure for candidate information
struct CandidateInfo
{
	char Name[40];
	char Party[30];
	char location[30];
	struct DOB DOB;
};

//Main Function
int main()
{
	int x;										//Variable Declared
	choose:
	printf("Enter 1 for admin and 2 for user:");
	scanf("%d",&x);								//Take input from user
	switch(x)
	{
		case 1:
			admin();
			break;
		case 2:
			user();
			break;
		default:
			printf("INVALID INPUT\n");
			goto choose;
	}
	return 0;
}
//Function For Admin
int admin()
{
	int x;
	char Userpass[20],CorrectPass[20];
	FILE* pwd;
	pwd=fopen("password.txt","r");
	fgets(CorrectPass,sizeof(CorrectPass),pwd);
	fclose(pwd);
	pass:
	printf("\nEnter Password for Admin Access :");
	scanf("%s",Userpass);
	if(strcmp(Userpass,CorrectPass)==0)
	{
		printf("\nLogin as Admin sucessfull");
	}
	else
	{
		printf("\nPassword Incorrect.\nTry Again");
		goto pass;
	}

   
	AdminProcess:
    printf("1. Create Election Schedule\n");
    printf("2. Add the Candidate\n");
    printf("3. Register the Voter\n");
    printf("4. Update the Voter Details\n");
    printf("5. Search the Voter Details\n");
    
    printf("6. Back to Main Menu\n");
    printf("Enter your choice:");
	scanf("%d",&x);
	switch(x)
	{
		case 1:
			createElectionScheduele();
			break;
		case 2:
			registerCandidate();
			break;
		case 3:
			registerVoter();
			break;
		case 4:
			updateVoterList();
			break;
		case 5:
			searchVoterList();
			break;
		case 6:
			goto AdminProcess;
			break;
		default:
			printf("\nINVALID INPUT!");
			goto AdminProcess;
	}
	return 0;
}
//Function For User
int user()
{
	int x;
	UserMenu:
	printf("1. Cast Vote\n");
    printf("2. Display the Vote Result\n");
    printf("3. Back to the Main Menu\n");
    printf("Enter your option:");
	scanf("%d",&x);
	switch(x)
	{
		case 1:
			CastVote();
			break;
		case 2:
			DisplayVoteResult();
			break;
		case 3:
			goto UserMenu;
		default:
			printf("INVALID INPUT\n");
			goto UserMenu;
	}
}
//Function to Check Age
int agecheck(int year,int month,int day)
{
    time_t ts;
    struct tm *ct;
    int age;
    ts=time(NULL);
    ct=localtime(&ts);
    age=(ct->tm_year+1900)-year;
    if (ct->tm_mon<month-1||(ct->tm_mon==month-1&&ct->tm_mday<day)) 
	{
        age--;
    }
    if(age<18)
    {
    	return 0;	
	}
	else
	{
		return 1;
	}
}
//function to register Voters
int registerVoter()
{
	int i, age, check, num, SNO;
    FILE* voterlist=fopen("voterlist.txt","a");
    printf("Enter the number of voters to register: ");
    scanf("%d",&num);
    struct UserInfo s1[num];
    for(i=0;i<num;i++)
	{
        printf("Enter Voter's name:");
        scanf("%s",&s1[i].Name);
        printf("Enter Voter's Date of birth(YYYY/MM/DD):");
        scanf("%d/%d/%d",&s1[i].DOB.year,&s1[i].DOB.month,&s1[i].DOB.day);
        printf("Enter Voter's address:");
        scanf("%s",&s1[i].address);
        printf("Enter password:");
        scanf("%s",&s1[i].password);
        SNO=voterSNO();
        if(agecheck(s1[i].DOB.year,s1[i].DOB.month,s1[i].DOB.day)==1)
		{
            fprintf(voterlist, "%-20d%-20s%d-%d-%-20d%-20s%-20s\n", SNO, s1[i].Name, s1[i].DOB.year, s1[i].DOB.month,s1[i].DOB.day, s1[i].address, s1[i].password);
            printf("\nVoter Registration Successful.\n");
            SNO++;
        }
		else
		{
            printf("\nVoter must be at least 18 years of age.\n");
        }
    }
    fclose(voterlist);
    return 0;
}
//function to get Voter's SNO
int voterSNO()
{
	int lastNum;
	FILE *SNO=fopen("voterlist.txt","a");
    if (SNO==NULL)
	{
        printf("File cannot be opened\n");
        return 1;
    }
    fseek(SNO,sizeof(int),SEEK_END);
    if(ftell(SNO)!=0)
	{
        fread(&lastNum,sizeof(int),1,SNO);
    }
    fclose(SNO);
    return lastNum+1;
}
//Function to create Election Schduele
int createElectionScheduele()
{
	int i, n;
    char Constituency[40],Date[10];
    FILE* schedule=fopen("schedule.txt","w");
    fprintf(schedule,"%-20s%-20s","Constituency","Date");
    printf("Enter number of Constituency:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
	{
        printf("Enter Constituency %d:",i+1);
        scanf("%s",Constituency);
        printf("Enter election Date for %s(YYYY/MM/DD):",Constituency);
        scanf("%s",Date);
        fprintf(schedule,"%-20s%-20s",Constituency,Date);
    }
    fclose(schedule);
	return 0;
}
//Function to register Candidates
int registerCandidate()
{
	int s,n;
    invalid:
    printf("Enter 1 to create a new candidate list\n 2 to update an existing candidate list\n 3 to delete a candidate :");
    scanf("%d",&s);
    if (s==1||s==2)
	{
        printf("Enter number of candidates to register:");
        scanf("%d",&n);
    }
    switch(s)
	{
        case 1:
            NewCandidateList(n);
            break;
        case 2:
            CandidateList(n);
            break;
        case 3:
            DelCandidate();
            break;
        default:
            goto invalid;
            break;
    }
    return 0;
}
//Function to make a new Candidate List
int NewCandidateList(int n)
{
	int i;
    struct CandidateInfo Info[n];
    FILE* candidate=fopen("candidate_list.txt","w");
    for(i=0;i<n;i++)
	{
        printf("Enter Candidate Name:");
        scanf("%s",Info[i].Name);
        printf("Enter Political Party:");
        scanf("%s",Info[i].Party);
        printf("Enter Candidacy Location:");
        scanf("%s",Info[i].location);
        printf("Enter Candidate Date of Birth(YY/MM/DD):");
        scanf("%d/%d/%d",&Info[i].DOB.year,&Info[i].DOB.month,&Info[i].DOB.day);
        if (agecheck(Info[i].DOB.year,Info[i].DOB.month,Info[i].DOB.day))
		{
            fprintf(candidate,"%-20s%-20s%-20s%-20d-%d-%d\n",Info[i].Name,Info[i].Party,Info[i].location,Info[i].DOB.day, Info[i].DOB.month, Info[i].DOB.year);
            printf("\nCandidate Registration Successful.\n");
        }
		else
		{
            printf("\nCandidate must be at least 18 years of age to be eligible to vote.\n");
        }
    }
    fclose(candidate);
    return 0;
}
//Function to update existing Candidate list
int CandidateList(int n)
{
	
	int i;
    struct CandidateInfo Info[n];
    FILE* candidate=fopen("candidate_list.txt","a");
    for(i=0;i<n;i++)
	{
        printf("Enter Candidate Name:");
        scanf("%s",Info[i].Name);
        printf("Enter Political Party:");
        scanf("%s",Info[i].Party);
        printf("Enter Candidacy Location:");
        scanf("%s",Info[i].location);
        printf("Enter Candidate Date of Birth(YY/MM/DD):");
        scanf("%d/%d/%d",&Info[i].DOB.year,&Info[i].DOB.month,&Info[i].DOB.day);
        if(agecheck(Info[i].DOB.year, Info[i].DOB.month, Info[i].DOB.day))
		{
            fprintf(candidate, "%-20s%-20s%-20s%-20d-%d-%d\n",Info[i].Name,Info[i].Party,Info[i].location,Info[i].DOB.day,Info[i].DOB.month,Info[i].DOB.year);
            printf("\nCandidate Registration Successful.\n");
        }
		else
		{
            printf("\nCandidate must be at least 18 years of age to be eligible to vote.\n");
        }
    }
    fclose(candidate);
    return 0;
}
//Function to Delete a Candidate
int DelCandidate()
{
	int i,index;
    char name[100];
    FILE *file,*temp;
    printf("Enter candidate name to delete :");
    getchar();
    fgets(name,sizeof(name),stdin);
    strtok(name,"\n");
    file=fopen("candidate_list.txt","r");
    temp=fopen("temp.txt","w");
    if(file==NULL)
	{
        printf("Error opening file.\n");
        return 1;
    }
    char line[256];
    while(fgets(line,sizeof(line),file))
	{
        if(strstr(line,name)==NULL)
		{
            fputs(line,temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove("candidate_list.txt");
    rename("temp.txt","candidate_list.txt");
    printf("Candidate %s deleted successfully.\n",name);
    return 0;
}
//Function to update Voter Details
int updateVoterList()
{
	int sno,num_voters,i;
    FILE *file,*temp;
    char name[50],address[50],password[50];
    struct DOB dob;
    file=fopen("voterlist.txt", "r");
    if(file==NULL)
	{
        printf("Error! File cannot be opened.\n");
        return 1;
    }
    temp=fopen("temp_voterlist.txt","w");
    if (temp==NULL)
	{
        printf("Error creating temporary file.\n");
        fclose(file);
        return 1;
    }
    printf("Enter Voter's Serial Number to update:");
    scanf("%d",&sno);
    fscanf(file,"%*[^\n]\n");
    while
	(fscanf(file,"%d%s%d-%d-%d%s%s%s",&num_voters,name,&dob.year,&dob.month,&dob.day,address,password)==7)
	{
        if(num_voters==sno)
		{
            printf("Enter Voter's new name:");
            scanf("%s",name);
            printf("Enter Voter's new Date of Birth(YYYY/MM/DD):");
            scanf("%d/%d/%d",&dob.year,&dob.month,&dob.day);
            printf("Enter Voter's new address:");
            scanf("%s",address);
            printf("Enter Voter's new password:");
            scanf("%s",password);
        }
        fprintf(temp,"%-20d%-20s%-20d-%d-%d%-20s%-20s%-20s\n",num_voters,name,dob.year,dob.month,dob.day,address,password);
    }
    fclose(file);
    fclose(temp);
    remove("voterlist.txt");
    rename("temp_voterlist.txt","voterlist.txt");
    printf("Voter details updated successfully.\n");
    return 0;
}
//Function to Search Voter
int searchVoterList()
{
	int sno,num_voters,i;
    FILE *file,*temp;
    char name[50],address[50],password[50];
    struct DOB dob;
    file=fopen("voterlist.txt","r");
    if(file==NULL)
	{
        printf("Error opening file.\n");
        return 1;
    }
    temp=fopen("temp_voterlist.txt","w");
    if(temp==NULL)
	{
        printf("Error creating temporary file.\n");
        fclose(file);
        return 1;
    }
    printf("Enter Voter's Serial Number to update:");
    scanf("%d",&sno);
    fscanf(file,"%*[^\n]\n");
    while (fscanf(file,"%d%s%d-%d-%d%s%s%s",&num_voters,name,&dob.year,&dob.month,&dob.day,address,password)==7)
	{
        if (num_voters == sno)
		{
            printf("Enter Voter's new name:");
            scanf("%s",name);
            printf("Enter Voter's new Date of Birth (YYYY/MM/DD):");
            scanf("%d/%d/%d",&dob.year,&dob.month,&dob.day);
            printf("Enter Voter's new address:");
            scanf("%s",address);
            printf("Enter Voter's new password:");
            scanf("%s",password);
        }
        fprintf(temp,"%-20d%-20s%-20d-%d-%d%-20s%-20s%-20s\n",num_voters,name,dob.year,dob.month,dob.day,address,password);
    }
    fclose(file);
    fclose(temp);
    remove("voterlist.txt");
    rename("temp_voterlist.txt", "voterlist.txt");
    printf("Voter details updated successfully.\n");
    return 0;
}
//Function to Cast Vote
int CastVote()
{
	return 0;
}
// Function to Display Vote Result
int DisplayVoteResult()
{
	FILE* file;
    char vote[100];
    file=fopen("votecount.txt","r");
    if(file==NULL)
	{
        printf("Error opening file.\n");
        return 1;
    }
    printf("Vote Results:\n");
    while(fgets(vote,sizeof(vote),file))
	{
        printf("%s", vote);
    }
   fclose(file);
}