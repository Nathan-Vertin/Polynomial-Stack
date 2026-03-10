/*
Nathan Vertin
Assignment 3
CS 1121
2/24/2026
*/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;



//----------------------structs------------------------------
struct polynomial{
	bool negative;
	long int coefficient;
	polynomial * next;
	polynomial * last;
	int degree;
	polynomial(long int num, int pow);//first
	polynomial(long int num, int pow, polynomial ** loc);//additional
	void printItem();
	void print();
	void hiterm(){printItem();}
	void loterm();
	void neg();
	void size();
	void add(polynomial ** head);
	void derive();
	void rotc();
};

struct polys{
	polys * next;
	polynomial * head;
	polys(string str);//first
	polys(string str, polys * b);//aditional
	void makePoly(string,polynomial **);
	polynomial * addAll();
};

//----------------------function declerations----------------
long int strToInt(string str);
void delPolynomial(polynomial ** a);
void delPolys(polys ** a);

//----------------------polynomial methods-------------------
polynomial::polynomial(long int num, int pow)//first
{
	next = NULL;
	last = NULL;
	if(num<0)
		negative = true;
	coefficient = num;
	degree = pow;
}
polynomial::polynomial(long int num, int pow, polynomial ** head)//aditional
//moves down a polynomial link list to find its spot, by degree
{
	polynomial * loc = *head;
	next = NULL;
	last = NULL;
	bool same = false;
	if(num<0)
		negative = true;
	coefficient = num;
	degree = pow;
	while(next == NULL && last == NULL && !same){
		if(loc->degree > degree)
			if(loc->next != NULL)
				loc = loc->next;
			else{
				loc->next = this;
				last = loc;
			}
		else if(loc->degree < degree){
			next = loc;
			last = loc->last;
			loc->last = this;
			if(last != NULL)
				last->next = this;
			else
				*head = this;
		}
		else{
			loc->coefficient += coefficient;
			if(loc->coefficient < 0)
				loc->negative = true;
			else
				loc->negative = false;
			same = true;
		}
	}
}

void polynomial::printItem()
//prints polynomial that the method was called from
{
	if(coefficient != 0)
	{
		if(coefficient != 1 || degree == 0)
		{
			if(coefficient == -1 && degree != 0)
				cout << "-";
			else
				cout << coefficient;
		}
		if(degree != 0)
		{
			cout << "x";
			if(degree != 1)
				cout << degree;
		}
	}
}
void polynomial::print()
//prints all polynomials in list from the one called
{
	printItem();
	for(polynomial * target = next; target != NULL; target = target->next)
	{
		if(!target->negative && target->coefficient != 0)
			cout << "+";
		target->printItem();
	}
}

void polynomial::neg()
//negates all of polynomials in list
{
	for(polynomial * tmp = this; tmp != NULL; tmp=tmp->next)
	{
		tmp->coefficient*=-1;
		if(tmp->negative == false)
			tmp->negative = true;
		else
			tmp->negative = false;
	}
}

void polynomial::size()
//cout size of polynomial list
{
	int i = 0;
	for(polynomial * tmp = this; tmp != NULL;tmp=tmp->next)
		if(tmp->coefficient != 0)
			i++;
	cout << "Polynomial ";
	print();
	cout << " has " << i << " terms";
}

void polynomial::loterm()
//cout lowest degree term in polynomial list
{
	if(next != NULL)
		next->loterm();
	else
	{
		if(coefficient != 0)
		{
			printItem();
		}
		else
			last->printItem();
	}
}

void polynomial::add(polynomial ** head)
//Adds each object of the polynomial it is called from to the head.
{
	if(next != NULL)
		next->add(head);
	new polynomial(coefficient,degree,head);
}

void polynomial::derive()
//takes the derivative of all polynomials in list
{
	for(polynomial * tmp = this; tmp != NULL;tmp = tmp->next)
	{
		tmp->coefficient *= tmp->degree;
		tmp->degree -= 1;
	}
}

void polynomial::rotc()
//rotates all of the coefficients to the right and loops back
{
	bool negA;
	bool neg = negative;
	int numA;
	int num = coefficient;
	for(polynomial * tmp = next; tmp != NULL;tmp = tmp->next)
	{
		if(tmp->coefficient != 0)
		{
			negA = tmp->negative;
			numA = tmp->coefficient;
			tmp->negative = neg;
			tmp->coefficient = num;
			neg = negA;
			num = numA;
		}
	}
	coefficient = num;
	negative = neg;
}

//----------------------polys methods------------------------
polys::polys(string str)//first
//creates polynomial from string
{
	head = NULL;
	next = NULL;
	makePoly(str,&head);
}
polys::polys(string str, polys * b)//additional
//Make new polys point to prior polys
{
	head = NULL;
	next = b;
	makePoly(str,&head);
}

polynomial * polys::addAll()
//Adds all polys in a list
{
	polynomial * tmp = head;
	cout << "  ";
	head->print();
	cout << endl;
	for(polys * a = next; a != NULL;a = a->next)
	{
		cout << "+ ";
		a->head->print();
		cout << endl;
		a->head->add(&tmp);
	}
	return tmp;
}

void polys::makePoly(string str, polynomial ** head){
//Makes Polynomial from a string
	bool end = false;
	bool first = true;
	string a,b;
	long int a1,b1;
	for(int i = 0; i < str.size(); i++){
		if(str[i] == 'x'){
                        end = true;
                        i++;
                }
                if(end == true && (str[i] == '+' || str[i] == '-')){
			end = false;
			a1 = strToInt(a);
			b1 = strToInt(b);
			if(first){
				*head = new polynomial(a1,b1);
				first = false;
			}else
				new polynomial(a1,b1,head);
			b = "";
			a = "";
                }
                if(end == false)
                        a += str[i];
                else
                        b += str[i];
        }
        a1 = strToInt(a);
        b1 = strToInt(b);
	if(first)
		*head = new polynomial(a1,b1);
	else
	        new polynomial(a1,b1,head);
}


int main(int size, char ** text){
	polys * head = NULL;
	string action;
	text++;
	ifstream fin(*text);
	while(fin.peek() != EOF){
		fin >> ws; //remove any extra spacing
		fin >> action;
		cout << "Command: \"" << action << "\"" << endl;
		if(action[0] == '+' || action[0] == '-'){
			if(head == NULL)
				head = new polys(action);
			else
				head = new polys(action, head);
		}
		if(action == "print"){
			if(head == NULL)
				cout << "print: Stack is empty.";
			else
				head->head->print();
			cout << endl;
		}
		if(action == "derive"){
			if(head == NULL)
				cout << "derive: Stack is empty." << endl;
			else
				head->head->derive();
		}
		if(action == "pop"){
			if(head == NULL)
				cout << "print: Stack is empty." << endl;
			else
			{
				polys * tmp;
				tmp = head->next;
				delPolynomial(&(head->head));
				delete head;
				head = tmp;
			}
		}
		if(action == "rotc"){
			if(head == NULL)
				cout << "rotc: Stack is empty." << endl;
			else
				head->head->rotc();
		}
		if(action == "topcopy"){
			if(head == NULL)
				cout << "topcopy: Stack is empty." << endl;
			else
			{
				polys * tmp = new polys("+0x0");
				head->head->add(&(tmp->head));
				tmp->next = head;
				head = tmp;
			}
		}
		if(action == "hiterm"){
			if(head == NULL)
				cout << "hiterm: Stack is empty.";
			else
				head->head->hiterm();
			cout << endl;
		}
		if(action == "loterm"){
			if(head == NULL)
				cout << "loterm: Stack is empty.";
			else
				head->head->loterm();
			cout << endl;
		}
		if(action == "neg"){
			if(head == NULL)
				cout << "neg: Stack is empty." << endl;
			else
				head->head->neg();
		}
		if(action == "size"){
			if(head == NULL)
				cout << "size: Stack is empty.";
			else
				head->head->size();
			cout << endl;
		}
		if(action == "add"){
			if(head == NULL)
				cout << "add: Stack is empty.";
			else
			{
				polynomial * tmp = head->addAll();
				cout << "= ";
				tmp->print();
				delPolys(&head);
			}
			cout << endl;
		}
		fin >> ws;//remove extra spacing before eof check
	}
	cout << "finished." << endl;
}


void delPolynomial(polynomial ** a){
	polynomial * tmp;
	while((*a)->next != NULL){
		tmp = (*a)->next;
		delete (*a);
		(*a) = tmp;
	}
	delete (*a);
	*a = NULL;
}

void delPolys(polys ** a){
	polys * tmp;
	while((*a)->next != NULL){
		tmp = (*a)->next;
		delPolynomial(&((*a)->head));
		delete *a;
		*a = tmp;
	}
	delete *a;
	*a = NULL;
}


long int strToInt(string str){//makes int in string into int
        long int num = 0;
        int size = str.size();
        int start = 0;
        int digit = 1;
        if(str[0] == '-'){
                digit = -1;
                start = 1;
                }
        else if(str[0] == '+'){
                digit = 1;
                start = 1;
                }
        for(int i = start;i < size; i++){
                long int dig = digit;
                int exp = size-1-i;
                while(exp != 0){
                        dig *= 10;
                        exp -= 1;
                }
        num += (dig * (str[i] -'0'));
        }
        return num;
}
