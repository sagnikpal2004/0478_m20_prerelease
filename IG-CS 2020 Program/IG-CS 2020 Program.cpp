#include <iostream>
#include <string>
using namespace std;

double inputCheck(int a = 1, int b = NULL, string Statmnt = "Choose an option");
bool inputCheck(string Statmnt = "Choose an option");

const string carModel[3] = { "Hatchback", "Saloon", "Estate" };	//Details of car (Model, Price, Choice)
const double carPrice[3] = { 535000, 495000, 625000 };
int carChoice = 0;

const string extra[5] = { "Set of luxury seats", "Satellite navigation", "Parking sensors", "Bluetooth connectivity", "Sound system" };
const double extraPrice[5] = { 45000, 5500, 10000, 350, 1000 };	//Details of optional extras (Names, Price, input, Choice)
double extraTotal = 0; 
int extraInput = 6;
bool extraChoice[5] = { 0, 0, 0, 0, 0 };

double fullPrice = 0;	//Non-discounted price (extraTotal + carPrice[carChoice])
bool repeatCust = NULL, trade_true = NULL;
double tradeInAmount = 0, discountCar = 0, discountExtras = 0;	//Discounts
double finalAmount = 0;	//Discounted price (finalAmount - (discountCar + discountExtras))

bool repeat = true;
int paymentMethod = 0, months = 0;	//Payment details
double pay = 0, cashback = 0;

int main() {

	//------------Car Choice------------------------------------------------------------------------------------------

	cout << "Welcome to Snazzy Autos!\n\nChoose your car model of choice:\n";
	for (int i = 1; i <= 3; i++)	//Display Car models and price
		cout << i << ". " << carModel[i - 1] << ": Rs " << (carPrice[i - 1] / 100000) << " lakh\n"; 

	carChoice = inputCheck(1, 3, "Make your choice");
	cout << "You have selected " << carModel[carChoice - 1] << " as your choice of car model.\n"; //Confirm Car model

	fullPrice = carPrice[carChoice - 1];	//Add price to fullPrice (non-discounted)
	//-------Optional extras Choice-------------------------------------------------------------------------------------

	cout << "\n-----------------------------------------------------------\n\nChoose your optional extras:\n\n";
	for (int i = 1; i <= 5; i++)
		cout << i << ". " << extra[i - 1] << ": Rs " << (extraPrice[i - 1]) << "\n";	//Display optional extras
	cout << "0. Finish selection\n";

	while (extraInput != 0) {	//Repeat until input is 0
		extraInput = inputCheck(0, 5, "Make your choice");	//Make extras choice

		if (extraInput != 0 && extraChoice[extraInput - 1] == 0) {
			cout << "Selected " << extra[extraInput - 1] << "\n";	//Displays "Selected [Optional Extra]"
			extraChoice[extraInput - 1] = 1;
			extraTotal = extraTotal + extraPrice[extraInput - 1];
		}
		else cout << "Invalid input! Please try again!\n";
	}

	fullPrice = fullPrice + extraTotal;	//Add extraTotal to fullPrice (non-discount) and display
	cout << "\n-----------------------------------------------------------\n";
	//-----------Discount questions------------------------------------------------------------------------------------------

	repeatCust = inputCheck("Have you bought a car from here before");
	trade_true = inputCheck("Do you have a car to trade in");
	if (trade_true) tradeInAmount = inputCheck(10000, 100000, "Please enter the amount offered by Snazzy Autos in Rupees");

	//-----Calculate discounts and output Order Summary----------------------------------------------------------------------

	cout << "\n-----------------------------------------------------------\n\nOrder summary:\n\nModel chosen: " << carModel[carChoice - 1] << " +Rs " << (carPrice[carChoice - 1] / 100000) << " lakh\n\nOptional extras:\n";	//Display Model
	for (int i = 0; i < 5; i++) {
		if (extraChoice[i])
			cout << (i + 1) << ". " << extra[i] << ": +Rs " << extraPrice[i] << "\n";	//Display selected extras with price
	}

	if (trade_true) {
		cout << "\nTrade In discount: -Rs " << tradeInAmount;	//Trade Amount in discountCar
		discountCar = tradeInAmount;
	}
	else {
		cout << "\nDiscount (-5%): -Rs " << (fullPrice * 5 / 100);
		discountCar = discountCar + ((carPrice[carChoice - 1]) * 5 / 100);	//No trade -5% discount on both
		discountExtras = discountExtras + (extraTotal * 5 / 100);
	}
	if (repeatCust) {
		cout << "\nRepeat Customer discount (-10%): -Rs " << (fullPrice * 10 / 100);
		discountCar = discountCar + (carPrice[carChoice - 1] * 10 / 100);	//RepeatCust -10% discount on both
		discountExtras = discountExtras + (extraTotal * 10 / 100);
	}

	finalAmount = fullPrice - (discountCar + discountExtras);	//Discounted price and display
	cout << "\n\nGrand Total: Rs " << finalAmount;

	//--------------Payment Method------------------------------------------------------------------------------------------

	do {	//Repeat until user is sure
		cout << "\n\n-----------------------------------------------------------\n\nChoose your payment method:\n\n1. Pay full amount now and get 1% cashback\n2. Equal monthly payments made over four years with no extra charge\n3. Equal monthly payments made over seven years at 5% extra cost\n";
		paymentMethod = inputCheck(1, 3, "Make your choice");	//Display paymentMethods and select

		if (paymentMethod == 1) {	//Display special offer
			cout << "\nSpecial offer for full paying customers!\nYou can choose to avail either the 1% cashback, or get the optional extras free. ";

			if ((finalAmount * 99 / 100) < (finalAmount - extraTotal + discountExtras)) {	//Display better deal first
				cout << "However, the cashback is the better deal for you.\n\nChoose your payment method:\n\n1. Get 1% cashback\n2. Chosen optional extras are free\n";
				paymentMethod = inputCheck(1, 2, "Make your choice");	//Special offer input
			}
			else {
				cout << "Getting the chosen optional extras for free is the better deal!\n\nChoose your payment method:\n\n1. Chosen optional extras are free\n2. Get 1% cashback\n";
				paymentMethod = inputCheck(1, 2, "Make your choice");	//Special offer input
				
				if (paymentMethod == 2) paymentMethod = 1;
				else paymentMethod = 2;	//Swap paymentMethod for second Special offer
			}

			if (paymentMethod == 1) { pay = finalAmount; cashback = finalAmount / 100; months = 0; }
			else { pay = finalAmount - extraTotal + discountExtras; cashback = 0; months = 0; }
		}				//Set the details for selected paymentMethod
		else if (paymentMethod == 2) { pay = finalAmount; cashback = 0; months = 48; }
		else { pay = finalAmount * 105 / 100; cashback = 0; months = 84; }
		
		cout << "\nYou pay Rs " << pay;
		if (cashback > 0) cout << " with a cashback of Rs " << cashback;	//Display payment details
		if (months > 0) cout << " over " << months << " months, with monthly installments of Rs " << pay / months;

		repeat = !(inputCheck("Are you sure with your payment method"));	//Payment confirmation
	} while (repeat);

	cout << "\nThank you!\n";
	system("pause");
}

double inputCheck(int a, int b, string Statmnt) {
//Outputs message, requests input, checks if within range
	double input = 0;

	for (;;) {
		cout << "\n" << Statmnt << ": (" << a << " - " << b << ") ";
		cin >> input;

		if (input >= a && input <= b) return input;
		else cout << "Invalid input! Please try again!\n";
	}
}

bool inputCheck(string Statmnt) {
//Outputs message, requests a binary answer
	char input = '0';

	for (;;) {
		cout << "\n" << Statmnt << "? (Y/N) ";
		cin >> input;

		if (input == 'Y' || input == 'y') return true;
		else if (input == 'N' || input == 'n') return false;
		else cout << "Invalid input. Please try again.\n";
	}
}