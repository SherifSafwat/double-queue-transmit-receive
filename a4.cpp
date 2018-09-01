//============================================================================
// Name        : a4.cpp
// Author      : mina
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "queue.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <typeinfo>
#include <iomanip>
#include <cstdlib>
#include <cmath>
//#include <ctgmath>

using namespace std;

int initSeq;
int seqNumBits;
int winSizeBits;
int winSize;
int qStart;
int qEnd;
int iExp;
int nDel;
int winStart;
int winEnd;

dequeue *qR;
dequeue *qW;

//fstream //outFile1;


int wSort()
{
	int con=-1;

	for(int i=qW->curr_front-1;i>0 ;i--)
	{
		if(qW->get(i-1) < qEnd)
		if(qW->get(i) < qW->get(i-1))
		{
			con = qW->get(i-1);
			qW->set((i-1), qW->get(i));
			qW->set(i, con);
		}
	}

	return 0;
}

int DeleteFnR(int n)
{
	int nStart = 0;
	int bWrap = 0;



	if (qR->get(-1) == -1) // check top
	{
		nStart = initSeq; // + winSize -1;

	}
	else
	{
		if(qR->get(-1) == qEnd)
		{
			nStart = 0;
		}
		else
		{
			nStart = qR->get(-1)+1; // + winSize -1;
		}
	}


	if( (nStart + winSize-1) > qEnd )  //may be put in q
	{
		bWrap = 1;
	}
	else
	{
		bWrap = 0;
	}

	if (bWrap == 1)
	{



		//if( (n < nStart) && (n > (winSize - (nStart - qEnd) )) )
		//if( (n < nStart-1) && (n > (winSize - (qEnd - nStart) )) )
		if( (n < nStart) && (n > (nStart + winSize - qEnd-2)) )
		{
			nDel++;
			return -1;
		}

	}
	else
	{
		if( (n < nStart) || (n > (nStart + winSize-1)) || (n > qEnd)  )
		{
			nDel++;
			return -1;
		}

	}


	return 0;
}


int DeleteFnW(int n)
{

	if(qW->curr_front >= winSize-1)
	{
		nDel++;
		return -1;
	}

	for(int i=0;i< qW->curr_front;i++)
	{
		if(qW->get(i) == n)
		{
			nDel++;
			return -1;
		}
	}



	return 0;
}

int check(int pargc)
{

	//outFile1 << "T1 " << qR[0] << qR->curr_front<< endl;
	//outFile1 << "T1 " << qW[0] << qW->curr_front<< endl;

	for(int i=0;i<qW->curr_front;i++)
	{

		if( (qR->get(-1) != -1) && (qW->get(i) == (qR->get(-1) + 1)) )
		{
			qR->push_front(qW->get(i));
			qW->swap(i);
			check(0);
		}
		else if( (qR->get(-1) != -1) && (qR->get(-1) == qEnd) && ( qW->get(i) == 0 ) )
		{
			qR->push_front(qW->get(i));
			qW->swap(i);
			check(0);
		}


	}

	//outFile1 << "T2 " << qR[0] << qR->curr_front<< endl;
	//outFile1 << "T2 " << qW[0] << qW->curr_front<< endl;

	return 0;
}

int Process(int argc,char *argv[])
{


	for(int i=5;i< argc;i++)
	{
		//outFile1 << "T " << qR[0] << " " << qR->curr_front<< endl;
		//outFile1 << "T " << qW[0] << " " << qR->curr_front<< endl;

		if( DeleteFnR(atoi(argv[i])) == 0 )
		{

			if( (qR->get(-1) == -1) && atoi(argv[i]) == initSeq )
			{
				qR->push_front(atoi(argv[i]));
				check(argc);
				//i++;
			}
			else
			{

				//check(argc);

				//if( (qR->get(-1) != -1) && ( (atoi(argv[i]) == (qR->get(-1) + 1)) || atoi(argv[i]) == qEnd-1 ) )
				if( (qR->get(-1) != -1) &&  (atoi(argv[i]) == (qR->get(-1) + 1)) )
				{

					qR->push_front(atoi(argv[i]));
					check(argc);

					/*if(DeleteFn(atoi(argv[i])) == 0)
					{
						qR->push_front(atoi(argv[i]));
					}*/
				}
				else if( (qR->get(-1) != -1) && (qR->get(-1) == qEnd) && ( atoi(argv[i]) == 0 ) )
				{
					qR->push_front(atoi(argv[i]));

					check(argc);
				}
				else
				{
					//swap();
					if( DeleteFnW(atoi(argv[i])) == 0)
					{
						qW->push_front(atoi(argv[i]));
						wSort();
					}

					//if(DeleteFn(atoi(argv[i])) == 0)
						//qW->push_front(atoi(argv[i]));
				}

			}

		}

		//outFile1 << "E " << qR[0] << " " << qR->curr_front<< endl;
		//outFile1 << "E " << qW[0] << " " << qR->curr_front<< endl;

	}

	//check(argc);

	if(qR->get(-1) == qEnd)
		cout << "R " << qR[0] << "E " << "0" << " W " << qW[0] << "D# " << nDel;
	else if(qR->get(-1) == -1)
		cout << "R " << qR[0] << "E " << initSeq << " W " << qW[0] << "D# " << nDel;
	else
		cout << "R " << qR[0] << "E " << (qR->get(-1) + 1) << " W " << qW[0] << "D# " << nDel;


	return 0;
}

int main(int argc,char *argv[])
{


	/*if (argc == 1 )
	{

		//6 4 58 : 59 58 60 61 63 0 2 4 32
		//5 4 28 : 26 28 30 29 31 4 0 2 1
		//3 2 0 : 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
		//5 4 25 : 26 27 25 29 31 4 3 0
		//5 4 0 : 1 2 3 4 5 6 7 8 9 10 11 15 16 12
		//3    2     0 :   0    1  2  3  4  5     6   0   1   2   3   4   5   6      0   1     2
		//3 2 0 : 0 1 2 3 4 5 0 1 2 3 7 6 3 2 4
		//4 3 8 : 9 10 11 12 13 14 15 8 8 9 10 11
		//string s1 = "a 4 3 8 : 9 10 11 12 13 14 15 8 8 9 10 11";
		//3 2 0 : 0 1 2 3 4 5 0 1 2 3 7 6 3 2 4

		argc = 20;
		//argv[0] = "";
		argv[1] = "3";
		argv[2] = "2";
		argv[3] = "0";
		argv[4] = ":";
		argv[5] = "0";
		argv[6] = "1";
		argv[7] = "2";
		argv[8] = "3";
		argv[9] = "4";
		argv[10] = "5";
		argv[11] = "0";
		argv[12] = "1";
		argv[13] = "2";
		argv[14] = "3";
		argv[15] = "7";
		argv[16] = "6";
		argv[17] = "3";
		argv[18] = "2";
		argv[19] = "4";
		argv[20] = "1";
		argv[21] = "2";
		argv[6] = "1";
		argv[7] = "2";
		argv[8] = "3";
		argv[9] = "4";
		argv[10] = "5";
		argv[11] = "6";
		argv[12] = "7";
	}*/


	if ( (argc == 1 ) || (argc < 5 ) || (strcmp(argv[1]," ") == 0 ) )
	{
		cout << "Invalid Configuration";
		return 0;
	}

	if (strcmp(argv[4],":") != 0 )
	{
		cout << "Invalid Configuration";
		return 0;
	}

	///////////////////////////////////////////////////////////////////////////////////////

	if(atoi(argv[1]) == 0 && atoi(argv[2]) == 0 && atoi(argv[3]) == 0 )
	{
		cout << "Invalid Configuration";
		return 0;
	}

	if( atoi(argv[1]) == atoi(argv[2]) )
	{
		cout << "Invalid Configuration";
		return 0;
	}


	//////////////////////////////////////////////////////////////////////////////////////

	for(int i=1;i<argc;i++)
	{
		if(i != 4 && atoi(argv[i]) == 0 && strlen(argv[i]) > 1)
		{
			if(i<4)
			{
				cout << "Invalid Configuration";
				return 0;
			}
			else
			{
				cout << "Invalid Packet";
				return 0;
			}

		}
	}


	seqNumBits = atoi(argv[1]);
	qStart = 0;
	qEnd = pow(2,seqNumBits) - 1;
	winSizeBits = atoi(argv[2]);
	winSize = pow(2,winSizeBits);
	initSeq = atoi(argv[3]);
	iExp = -1;
	nDel = 0;
	winStart = initSeq;
	winEnd = initSeq;

	if(  (winSizeBits > seqNumBits ) || (initSeq > qEnd) )
	{
		cout << "Invalid Configuration";
		return 0;
	}

	for(int i=6;i<argc;i++)
	{
		if(atoi(argv[i]) > qEnd)
		{
			cout << "Invalid Packet";
			return 0;
		}

	}

	for(int i=1;i<argc;i++)
	{
		if( (i!=4) && ! isdigit(argv[i][0]) )
		{
			if (i<4)
			{
				cout << "Invalid Configuration";
				return 0;
			}
			else
			{
				cout << "Invalid Packet";
				return 0;
			}
		}
	}


	//cout << qEnd ;
	//outFile1.open ("test1.txt", std::ofstream::out ); //| std::ofstream::app);


	qR = new dequeue(argc-5);
	qW = new dequeue(argc-5);

	Process(argc,argv);

	delete qR;
	delete qW;

	return 0;
}
