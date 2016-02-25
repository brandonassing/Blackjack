#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

int money;
ofstream myfile;
ifstream getfile;

static int setBet() {
	int bet;
	cout << "Enter bet: ";

	cin >> bet;
	while (bet > money || bet < 1000){
		cout << "Invalid bet" << endl;
		cout << "Enter bet: ";
		cin >> bet;
	}
	return bet;
}
void writeMoney(){

	myfile.open("Money.txt");
	myfile.clear();
	myfile << money;
	myfile.close();
}
static int checkValue(int card) {
	int value = 0;
	if (card <= 3) {
		value = 2;
	}
	else if (card <= 7) {
		value = 3;
	}
	else if (card <= 11) {
		value = 4;
	}
	else if (card <= 15) {
		value = 5;
	}
	else if (card <= 19) {
		value = 6;
	}
	else if (card <= 23) {
		value = 7;
	}
	else if (card <= 27) {
		value = 8;
	}
	else if (card <= 31) {
		value = 9;
	}
	else if (card <= 35) {
		value = 10;
	}
	else if (card <= 47) {
		value = 10;
	}
	else if (card <= 51) {
		/////////////// 11 or 1?

		value = 11;
	}
	return value;
}

static void play() {
	srand(static_cast<unsigned int>(time(NULL)));
	srand(time(NULL));
	bool dd, done = false;
	int dCard[5];
	int pCard[3];
	int cardsDrawn = 0;
	int pSum = 0, dSum = 0, dCardUsed = 0;

	int opt;
	int bet = 0;

	for (int i = 0; i < (sizeof(dCard) / sizeof(*dCard)); i++) {
		dCard[i] = rand() % 51;
		dSum += checkValue(dCard[i]);
		dCardUsed++;

		////////////CHECK DEAL////////////
		//cout << checkValue(dCard[i]) << ", ";
		/////////////////////////////////

		if (dSum >= 15){
			i = (sizeof(dCard) / sizeof(*dCard));
		}

	}
	for (int j = 0; j < 2; j++) {
		pCard[j] = rand() % 51;
		cardsDrawn++;
	}
	cout << "Money: $ " << money << endl;
	bet = setBet();
	cout << "Your Cards: ";
	for (int k = 0; k < cardsDrawn; k++) {
		cout << checkValue(pCard[k]) << ", ";
		pSum += checkValue(pCard[k]);
	}
	cout << endl;
	cout << "Dealer: " << endl;
	cout << checkValue(dCard[0]) << endl;
	cout << endl;
	/*
	if (dSum > 21) {
	cout << "Dealer bust" << endl;
	cout << "YOU WIN" << endl;
	money += bet;

	writeMoney();
	}
	*/
	//dSum = 500;
	if (pSum > 21 && dSum > 21) {
		cout << "Dealer and player bust" << endl;
		cout << "Draw" << endl;
	}
	else if (pSum > 21 && dSum <= 21){
		cout << "You bust" << endl;
		cout << "You LOSE" << endl;
		money -= bet;
		writeMoney();
	}
	else if (pSum <= 21) {
		//do{
		do{
			cout << "(1) Draw: " << endl;
			cout << "(2) Hold: " << endl;
			if (money >= 2 * bet){
				cout << "(3) Double Down: " << endl;
				dd = true;
			}
			else {
				dd = false;
			}
			cout << "Enter option: ";
			cin >> opt;

			if ((opt < 1 || opt > 3) || (!dd && opt == 3)){
				cout << "\nInvalid answer." << endl;
			}
		} while ((opt < 1 || opt > 3) || (!dd && opt == 3));
		if (opt == 1) {
			pCard[cardsDrawn] = rand() % 51;
			pSum += checkValue(pCard[cardsDrawn]);
			cardsDrawn++;
		}
		else if (opt == 2){
			//	done = true;
		}
		else if (opt == 3){
			bet += bet;
		}

		///////////////////////////////////
		//DRAW OR RAISE MORE THAN ONCE IF NOT BUST
		///////////////////////////////////


		cout << endl;
		cout << "Your cards: ";
		for (int k = 0; k < cardsDrawn; k++) {
			cout << checkValue(pCard[k]) << " ,";
		}
		cout << endl;

		cout << "Dealer: ";
		for (int l = 0; l < dCardUsed; l++){
			cout << checkValue(dCard[l]) << " ,";
		}
		cout << endl;

		cout << "P:" << pSum << endl;
		cout << "D:" << dSum << endl;
		//} while (!done);
		if (dSum > 21 && pSum <= 21 || pSum > dSum && pSum <= 21){
			if (pSum > dSum){
				cout << "YOU WIN" << endl;
			}
			else{
				cout << "Dealer bust, YOU WIN" << endl;
			}
			money += bet;
			writeMoney();
		}
		else if (pSum < dSum || pSum > 21 && dSum <= 21) {
			if (pSum < dSum){
				cout << "You LOSE" << endl;
			}
			else {
				cout << "You bust" << endl;
			}
			money -= bet;
			writeMoney();
		}
		else if (pSum == dSum || pSum > 21 && dSum > 21) {
			if (pSum > 21 && dSum > 21){
				cout << "Both players bust, DRAW" << endl;
			}
			else{
				cout << "Draw" << endl;
			}
		}

	}
	Sleep(2000);
	cout << "Money: $ " << money << endl;
	Sleep(2000);
}

void main(){
	int again = 0, again2 = 0;
	/*int x;
	cin >> x;
	if (!(cin >> x))
	{
	cin.clear();
	cin.ignore();
	cout << "Incorrect entry. Try again: ";
	}
	*/
	do {
		getfile.open("Money.txt");
		getfile.clear();
		getfile >> money;
		getfile.close();
		if (money > 0){
			play();
		}
		if (money <= 0){
			cout << "\nBANKRUPT!" << endl;
			cout << "(1) Reset Money and Play Again" << endl;
			cout << "(2) Quit" << endl;
			cout << "Enter option: ";
			//do{
			cin >> again2;
			/*
			if (!(cin >> again2))
			{
			cin.clear();
			cin.ignore();
			cout << "Invalid entry. \nEnter Option: ";
			}*/
			//} while (!(cin >> again2));
			if (again2 == 1){
				money = 5000;
				writeMoney();
				again = 1;
			}
			else if (again2 == 2){
				again = 3;
			}
		}
		else{

			do{
				cout << "\n" << "(1) Play Again" << endl;
				cout << "(2) Reset Money" << endl;
				cout << "(3) Quit" << endl;
				cout << "Enter option: ";
				//do{
				cin >> again;
				/*if (!(cin >> again))
				{
				cin.clear();
				cin.ignore();
				cout << "Invalid entry. \nEnter Option: ";
				}
				*/
				//} while (!(cin >> again));

				if (again == 2){
					money = 5000;
					writeMoney();
				}
				if (again < 1 || again > 3){
					cout << "Invalid response." << endl;
				}
			} while (again < 1 || again > 3);
		}
		cout << "________________________________________________________________" << endl;
	} while (again == 1 || again == 2);
}