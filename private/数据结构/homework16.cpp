/* 7-4 Document Distance (35 分)
Plagiarism is a form of academic dishonesty. To fight with such misconducts, 
plagiarism checkers are developed to compare any submitted article with all the articles stored in a database. 
The key is that given two documents, how to judge their similarity, or in other words, document distance? 
The document distance can be measured with their word metrics. 
In this project, you are supposed to write a program to calculate the distance of any given pair of documents.
Some important terms are defined as follows:
Word: is a continuous sequence of alphanumeric characters. 
For example, the phrase "the course data structure is fun" consists of 6 distinct words. 
Here we can assume that no word contains more than 20 characters.
Word frequency: denoted by FD(w) is the number of times the word w occurs in a document D.
Document distance metric: is defined to be the inner product of the two vectors containing the word frequencies for all words in two documents. 
	Denote the frequency vector for document Di by F(Di)=(Fi(w1),⋯,Fi(wn))T, 
	then the metric is given by (F(D1),F(D2))=(i:1->n)∑F1(wi)F2(wi). 
	In other words, the document distance metric is the projection of vector F(D1) onto F(D2), or vice versa.
Angle metric: is the angle between the vectors F(D1) and F(D2) which gives an indication of overlap between the two documents D1and D2. 
The angle can be computed by the following formula:θ(D1,D2)=arccos(∣∣F(D1)∣∣⋅∣∣F(D2)∣∣(F(D1),F(D2)))
where θ∈[0,π/2] and ∣∣⋅∣∣ can be any norm of a vector. To be more specific, here we use the 2-norm which is defined by ∣∣F(D)∣∣=(F(D),F(D)).
Input Specification:
Each input file contains one test case. 
For each case, the first line of input contains a positive integer N (≤100) which is the number of text files to be processed. 
Then N blocks follow, each contains a file. 
The first line of each file contains the title of the article (string of no more than 6 characters without any space), 
and the last line contains a single character #. 
After the file blocks, there is a line containing a positive integer M (≤100,000), followed by M lines of inquiries. 
Each inquiry gives a pair of file names separated by a space. The size of the largest test case is about 1 MB.
Output Specification:
For each inquiry, print in a line Case #: *, 
where # is the test case number starting from 1 and * is the document distance value accurate up to 3 decimal places.
Note: Your stemming algorithm must be able to handle "es", "ed", "ing", "ies" and must be case-insensitive. 
Stop words are not supposed to be ignored and must be treated as normal words.
Sample Input:       Sample Output:
3                   Case 1: 0.841
A00                 Case 2: 0.785
A B C
#
A01
B C D
#
A02
A C
D A
#
2
A00 A01
A00 A02      */
/* 此题满分35分，最终得分只有19分，鲜绿的大✖️极其醒目 */
#include<stdio.h>
#include<string.h>
#include<math.h>
//struct passage to store data
struct Passage{
	char Name[5];
	char Word[100];
	int weight[100];
};
struct Passage F[100];
int main(){
	double ModuleOfVector(int file); //tow functions to calculate results
	double MultOfVectors(int file1,int file2);
	int NumOfFiles; //number of files.
	double result[100]; //store the result[i] for case i
	int i,j,m,n;
	int file1,file2,Case; //file number and case number
	char f1[5],f2[5]; //store the name of file1 and file2 (when compare)
	int flag;
	scanf("%d",&NumOfFiles); //input the number of files
	for(i=0;i<NumOfFiles;i++){
		//Input data in to Passage b
		scanf("%s",F[i].Name);
		getchar(); //This getchar() can free the '\n' in cache. Otherwise it will assign to the next scanf of getchar operation.
		j=0; //initialize input
		F[i].Word[j] = getchar();
		while(F[i].Word[j] != '#'){
			if(F[i].Word[j]=='\n' || F[i].Word[j]==' ')
				j--;
			j++;
			scanf("%c",&F[i].Word[j]);
		}
		if(j == 0) //if a file is empty
			printf("File is null!\n");
		//Calcute the weight of word. If two word are the same, the later one's weight will be 0.
		for(m=0;m<j;m++){
			F[i].weight[m] = 0;
			for(n=0;n<j;n++){
				if(F[i].Word[m] == F[i].Word[n])
					F[i].weight[m]++;
			}
			for(n=0;n<j;n++){
				if(F[i].Word[m] == F[i].Word[n])
					if(F[i].weight[m] > 1 && m > n){
						F[i].weight[m]=0;
						break;
					}
			}
		}
	}
	//input the number of case
	scanf("%d",&Case);
	for(i=0;i<Case;i++){
		//Input the name of two files. Find their number.
		scanf("%s%s",f1,f2);
		flag=0;
		for(j=0;j<NumOfFiles;j++){
			if(strcmp(F[j].Name,f1) == 0){
				file1=j;
				flag++;
			}
			if(strcmp(F[j].Name,f2) == 0){
				file2=j;
				flag++;
			}
		}
		if(flag != 2) //if any one in the two files doesn't exist. print "File not exist!\n "
			printf("File not exist!\n");
		result[i] = acos(MultOfVectors(file1,file2) / (ModuleOfVector(file1)*ModuleOfVector(file2))); //Use acos() to calculate the result
	}
	//print result of cases
	for(i=0;i<Case;i++)
		printf("Case %d: %.3lf\n",i+1 ,result[i]);
	//print result in suitable form
	return 0;
}
//This function returns the module of vector
double ModuleOfVector(int file){
	int i=0;
	double module=0;
	while(F[file].Word[i] != '#'){
		module += F[file].weight[i]*F[file].weight[i];
		i++;
	}
	return sqrt(module);
}
//This function returns the multiplication of vectors
double MultOfVectors(int file1,int file2){
	int i,j;
	double mult=0;
	for(i=0;F[file1].Word[i] != '#';i++ )
		for(j=0;F[file2].Word[j] != '#';j++ ){
			if(F[file1].Word[i] == F[file2].Word[j]){
				mult += F[file1].weight[i] * F[file2].weight[j];
			}
		}
		return mult;
}