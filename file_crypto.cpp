#include<iostream>
#include<fstream>
#include<string>
using namespace std;



char** initialize(char **M)
	{
		for(int i=0;i<16;i++)
		{
			for(int j=0;j<95;j++)
			{
				M[i][j]=j+32;
			}
		}
	return M;
	}




char** Rshift(char *K,char **M,int shift)
	{
		int ascii;
		char temp[95];
		for(int i=0;i<16;i++)
		{
			for(int j=0;j<95;j++)
			{
				temp[j]=M[i][j];
			}
			ascii=K[(i+shift)%16];
			int position;
			position=ascii%95;
			for(int j=0;j<95;j++)
			{
				M[i][position]=temp[j];
				position=(position+1)%95;
			}
		}
		return M;
	}




char** Lshift(char *K,char **M,int shift)
	{
		int ascii;
		char temp[95];
		for(int i=0;i<16;i++)
		{
			ascii=K[(i+shift)%16];
			ascii=ascii%95;
			for(int j=0;j<95;j++)
			{
				temp[j]=M[i][ascii];
				ascii=(ascii+1)%95;
			}
			for(int j=0;j<95;j++)
			{
				M[i][j]=temp[j];
			}
		}
		return M;
	}




char* translation(char *A1,char **M,int i)
	{
		char Kts[16];
		for(int j=0;j<16;j++)
		{
			Kts[j]=M[i][j];
			A1[j]=A1[j]^Kts[j];
		}
		return A1;
	}



char* transposing(char *A1,char **M,int i)
	{
		char Ktp[4];
		char A2[8];
		char A3[8];
		char temp1[16];
		char temp2[8];
		char temp3[8];



		for(int j=0;j<4;j++)
		{
			Ktp[j]=M[i][j];
		}



		int position;
		position=Ktp[0]%16;


		for(int j=0;j<16;j++)
		{

			temp1[position]=A1[j];
			position=(position+1)%16;
		}

		for(int j=0;j<8;j++)
		{
			A2[j]=temp1[j];

		}
		for(int j=8;j<16;j++)
		{
			A3[j-8]=temp1[j];

		}
		position=Ktp[1]%8;
		for(int j=0;j<8;j++)
		{
			temp2[position]=A2[j];
			position=(position+1)%8;
		}
		position=Ktp[2]%8;
		for(int j=0;j<8;j++)
		{
			temp3[position]=A3[j];
			position=(position+1)%8;
		}

		for(int j=0;j<8;j++)
		{
			A1[j]=temp2[j];
		}
		for(int j=0;j<8;j++)
		{
			A1[j+8]=temp3[j];
		}
		position=Ktp[3]%16;
		for(int j=0;j<16;j++)
		{
			temp1[position]=A1[j];
			position=(position+1)%16;
		}
		for(int j=0;j<16;j++)
		{
			A1[j]=temp1[j];
		}
		return A1;
	}


char* De_translation(char* C,char** M,int i)
	{
		char Kts[16];
		for(int j=0;j<16;j++)
		{
			Kts[j]=M[i][j];
			C[j]=C[j]^Kts[j];
		}
		return C;
	}

char* De_transposing(char* C,char** M,int i)
	{
		char Ktp[4];
		char C2[8];
		char C3[8];
		char temp1[16];
		char temp2[8];
		char temp3[8];



		for(int j=0;j<4;j++)
		{
			Ktp[j]=M[i][j];
		}

		int position;
		position=Ktp[3]%16;

		for(int j=0;j<16;j++)
		{

			temp1[j]=C[position];
			position=(position+1)%16;
		}




		for(int j=0;j<8;j++)
		{
			C2[j]=temp1[j];
		}

		for(int j=8;j<16;j++)
		{
			C3[j-8]=temp1[j];
		}

		position=Ktp[1]%8;

		for(int j=0;j<8;j++)
		{

			temp2[j]=C2[position];
			position=(position+1)%8;
		}


		position=Ktp[2]%8;
		for(int j=0;j<8;j++)
		{

			temp3[j]=C3[position];
			position=(position+1)%8;
		}
		for(int j=0;j<8;j++)
		{
			C[j]=temp2[j];
		}
		for(int j=0;j<8;j++)
		{
			C[j+8]=temp3[j];
		}
		position=Ktp[0]%16;
		for(int j=0;j<16;j++)
		{
			temp1[j]=C[position];
			position=(position+1)%16;
		}
		for(int j=0;j<16;j++)
		{
			C[j]=temp1[j];
		}
		return C;
	}








char* Encryption(char* K,char** M,char* P)
	{
		char* CL1=new char[16];
		char* A1=new char[16];
		int i;

		int j;
		for(i=0;i<16;i++)
		{
			j=P[i]-32;
			CL1[i]=M[i][j];
		}

		for(i=0;i<16;i++)
		{ 
			A1[i]=CL1[i];
		}

		for(int i=0;i<8;i++)
		{





			A1=translation(A1,M,i);

			A1=transposing(A1,M,i);
		
		}
return A1;
		
	}



int search(char** M,char* C1,int i)
	{
		int j;
		for(j=0;j<95;j++)
		{
			if(C1[i]==M[i][j])
			{
				break;
			}
		}
		return j;
	}  		








char* Decryption(char* K,char** M,char* C)
	{

		char* CL1=new char[16];
		char* C1=new char[16];
		int i;




		for(i=0;i<16;i++)
		{ 
			C1[i]=C[i];
		}

		for(int i=7;i>=0;i--)
		{
			C1=De_transposing(C1,M,i);
			C1=De_translation(C1,M,i);



		}

	int j;
		for(i=0;i<16;i++)
		{
			j=search(M,C1,i);
			j=j+32;
			C[i]=j;
		}

		return C;
	}
			



	
int main()
{

	char* K=new char[16];
	char** M=new char*[16];
	for(int i=0;i<16;i++)
	M[i]=new char[95];
	char* P=new char[16];
	char* A1=new char[16];

	fstream fin;

	int choice;

	cout<<"1-Encrypt the file"<<endl;
	cout<<"2-Decrypt the file"<<endl;
	cout<<"Enter your choice:";

	cin>>choice;
	M=initialize(M);

	string encry;
	string decry;
	string inputFilename;
	string outputFilename;


	M=Rshift(K,M,1);
	M=Rshift(K,M,0);

	if(choice==1)
	{


		cout<<"Enter the key"<<"\n";
		for(int i=0;i<16;i++)
		{
			cin>>K[i];
		} 

		int i=0;
		char temp;

		cout<<"Enter the Input File name:";
		cin>>inputFilename;
		cout<<"Enter the Output File name:";
		cin>>outputFilename;

		ofstream fout(outputFilename.c_str());

		fin.open(inputFilename.c_str(),ios::in);
		while(fin.good())
		{
			i=0;
			if(!fin.good()) break;
			while(i<16)
			 {	
				temp= fin.get();
				if(!fin.good()||(temp==3))
				{
					break;
				}
				else if((temp<32)||(temp>127))
				{	
					P[i]=' ';
				}
				else if((temp>31)&&(temp<128))
				{	
					P[i]=temp;
				}

			 	i++;
			 }

			if(!fin.good()) {
			while((i<16)&&(i>1)){P[i]=' ';i++;}
					}
			if(i==1) break;


			A1=Encryption(K,M,P);

			for(int i=0;i<16;i++)
        		{
        		    fout<<A1[i];
        		}
			
		}
		fin.close();
		fout.close();


	}


	if(choice==2)
		{
			
			cout<<"Enter the key"<<"\n";
			for(int i=0;i<16;i++)
			{
				cin>>K[i];
			}

			int i=0;
			char temp;
			cout<<"Enter the Input Filename:";
			cin>>inputFilename;
			cout<<"Enter the Output Filename:";
			cin>>outputFilename;
			ofstream fout(outputFilename.c_str());


			fin.open(inputFilename.c_str(),ios::in);
			while(!fin.eof())
			{
				i=0;
				while(i<16)
				 {	
					temp= fin.get();
			if(!fin.good()) break;
					P[i]=temp;
			 	i++;
			 }
			if(!fin.good()) break;

			A1=Decryption(K,M,P);

			for(int i=0;i<16;i++)
        		{
        		    fout<<A1[i];
        		}
		
		}
		fin.close();
		fout.close();

	}
	return 0;

}
