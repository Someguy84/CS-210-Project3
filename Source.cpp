#include <Python.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

int userInput;
string str;
string fileLine;

void CallProcedure(string pName) {
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("Python");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

int callIntFunc(string proc, string param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	Py_Initialize();
	pName = PyUnicode_FromString((char*)"Python");
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	Py_DECREF(pValue);
	Py_DECREF(pModule);
	Py_DECREF(pName);
	Py_Finalize();

	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

int callIntFunc(string proc, int param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	Py_Initialize();
	pName = PyUnicode_FromString((char*)"Python");
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	Py_DECREF(pValue);
	Py_DECREF(pModule);
	Py_DECREF(pName);
	Py_Finalize();

	delete[] procname;

	return _PyLong_AsInt(presult);
}


void UserMenu() {
	cout << "---------------------- User Options ----------------------" << endl;
	cout << "1: Run Report for today's sales" << endl;
	cout << "2: Display number of times a specific item was sold" << endl;
	cout << "3: Produce a histogram for today's sales" << endl;
	cout << "4: Exit" << endl;
	cout << "Enter your selection as a number: 1, 2, 3, or 4." << endl;
	cout << "-------------------------------------------------------" << endl;
	cin >> userInput;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid selection. Please enter an option 1 - 4." << endl;
		cin >> userInput;
	}

	if (userInput == 1) {
		cout << endl;
		cout << "Items sold today with Quantity: " << endl;
		CallProcedure("PurchaseCounter");
		cout << endl;
		return;
	}
	else if (userInput == 2) {
		cout << endl;
		cout << "Please enter the item name: ";
		cin >> str;
		cout << endl;
		cout << "Printing the sales for " << str << ":" << endl;
		cout << "Quantity: " << callIntFunc("SpecificItemCounter", str) << endl << endl;
		return;
	}
	else if (userInput == 3) {
		cout << endl;
		cout << "Items sold today with Quantity: " << endl;
		CallProcedure("PurchaseCounterWriter");
		ifstream frequencyFile("frequency.dat");
		string item;
		int count;
		while (getline(frequencyFile, fileLine)) {
			istringstream iss(fileLine);
			if (!(iss >> item >> count)) { break; }
			cout << item << " " << string(count, '+') << endl;
		}
		cout << endl;
		return;
	}
	else if (userInput == 4) {
		cout << endl;
		cout << "Exiting program . . . " << endl;
		exit(EXIT_SUCCESS);
	}
	else {
		cout << "Please enter an option 1 - 4 . . . " << endl << endl;
		return;
	}
}


int main() {
	while (1) {
		UserMenu();
	}

	return 0;
}
