/*
 * queue.h
 *
 *  Created on: May 10, 2017
 *      Author: mina
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include<iostream>

using namespace std;

class dequeue {
    friend ostream & operator <<(ostream &os,dequeue &d);
    public:
        dequeue(int size); //constructor
        ~dequeue(){ delete [] storage; } //destructor
        void push_front(int data);
        void push_back(int data);
        int pop_back();
        int pop_front();
        int get(int index);
        int set(int index, int val);
        int swap(int index);

        int & operator[] (int index);

    //private:
        int size;
        int curr_front,curr_back;
        int * storage;
};


dequeue:: dequeue(int psize){
    curr_back=0;
    curr_front=0;
    storage = new int [psize];
    size = psize;

	for(int i=0; i<size; i++)
	{
		storage[i]=-1;
	}
}

void dequeue:: push_front(int data){
    storage[curr_front]=data;
    curr_front++;
}

void dequeue:: push_back(int data){

    storage[curr_back]=data;
    curr_back--;
}

int dequeue:: pop_front(){
    curr_front++;
    return storage[curr_front];
}

int dequeue:: pop_back(){

	//storage[curr_back] = 0;
    return storage[curr_back];--curr_back;
}

int dequeue:: get(int index)
{
	if(curr_front == 0)
		return -1;
	else if(index == -1)
		return storage[curr_front-1];
	else
		return storage[index];
}

int dequeue:: set(int index, int val)
{
	return storage[index] = val;
}

int dequeue:: swap(int index)
{
	for(int i=index;i<curr_front;i++)
	{
		storage[i] = storage[i+1];
	}

	curr_front--;
	return 0;
}


int & dequeue::operator[] (int index)
{
	if(index < 0 || index >size)
	{
		cout<<"Error \n";
		//return ;
	}
	else
	{
		return storage[index];
	}

}


ostream & operator <<(ostream &os,dequeue &d)
{

//	os << "[ ";
	for(int i=0; i<d.size; i++)
	{
		if(d[i] != -1)
		{
			os << d[i] << " ";
		}

	}
//	os << "]" ; //<< endl;
	return os;

}






#endif /* QUEUE_H_ */
