//�e��:fetch:1 cycle�BExection:2�B5 cycle �BWrite back: 1 cycle�A�B�n�A���@��cycle�~�i�H����value
//reg��l��0 2 4 6 8 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Instruction.h"
#include "Register.h"
#include "ReservationStation.h"
#include <iomanip>
using namespace std;

void readFile(vector <Instruction> &insts);
Instruction converInst(string input,vector <Instruction>& insts);
void output(ReservationStation RS[],int cycle);

int numAddRS = 3;
int numMulRS = 2;
int addCycle = 5;
int mulCycle = 19;
Register* registers[6];

int main(void)
{
	for (int i = 1; i <= 5; i++)
	{
		registers[i] = new Register((i - 1) * 2);
	}
	vector <Instruction> insts;
	ReservationStation RS[2];
	RS[0].set(numAddRS,addCycle);
	RS[1].set(numMulRS,mulCycle);
	readFile(insts);
	int cycle = 1;
	int index = 0;
	int done = 0;
	while (done != insts.size())
	{
		if (index <insts.size())
		{
			if (insts[index].getType() == "ADD" && !RS[0].full())
			{
				insts[index].setCycle(cycle);
				if (RS[0].insertInst(insts[index], cycle, "ADD"))
					index++;
			}
			else if(insts[index].getType() == "MUL" && !RS[1].full())
			{
				insts[index].setCycle(cycle);
				if (RS[1].insertInst(insts[index], cycle, "ADD"))
					index++;
			}
		}
		if (RS[0].update(cycle))
			done++;
		if (RS[1].update(cycle))
			done++;
		output(RS, cycle);
		cycle++;
	}
	system("pause");
	return 0;
}

void readFile(vector <Instruction>& insts)
{
	ifstream inFile("Input.txt", ios::in);
	if (!inFile)
	{
		cout << "Input.txt could not be openend!" << endl;
		exit(1);
	}
	vector <string> input;
	string temp;
	while (getline(inFile, temp))
		input.push_back(temp);
	for (int i = 0; i < input.size(); i++)
		insts.push_back(converInst(input[i],insts));
}

Instruction converInst(string input, vector <Instruction>& insts)
{
	string temp;
	string Opterator;
	vector <string> regs;
	string reg;
	string imm;
	int i = 0;
	while (input[i] != ' ')
		Opterator.push_back(input[i++]);
	i++;//remove ' '
	i++;//romove 'F'
	reg.push_back(input[i]);
	regs.push_back(reg);
	reg.clear();
	i += 4;//remove " ,F"
	reg.push_back(input[i]);
	regs.push_back(reg);
	reg.clear();
	i += 3;
	if (input[i] == 'F')
	{
		i++;
		reg.push_back(input[i]);
		regs.push_back(reg);
	}
	else
	{
		imm.push_back(input[i]);
	}

	if (regs.size() == 3)
	{
		Instruction temp(Opterator, stoi(regs[0]), stoi(regs[1]), stoi(regs[2]));
		return temp;
	}
	else
	{
		Instruction temp(Opterator, stoi(regs[0]), stoi(regs[1]), imm);
		return temp;
	}
}

void output(ReservationStation RS[], int cycle)
{
	cout << endl << "Cycle: " << cycle << endl << endl;
	cout << "   _ RF __" << endl;
	for (int i = 1; i < 6; i++)
		cout << 'F' << i << " |" << setw(4) << registers[i]->getValue() << " |" << endl;
	cout << "   -------" << endl;
	cout << endl;
	cout << "   _ RAT __" << endl;
	for (int i = 1; i < 6; i++)
		cout << 'F' << i << " |" << setw(4) << registers[i]->getName() << " |" << endl;
	cout << "   -------" << endl;
	cout << endl;
	cout << "    _ RS _________________" << endl;
	for (int i = 0; i < RS[0].getSize(); i++)
	{
		Instruction temp = RS[0].getInstruction(i);
		cout << "RS" << i + 1 << " |"
			<< setw(5) << temp.getSymbol() << " |"
			<< setw(5) << temp.getReg(1) << " |"
			<< setw(5) << temp.getReg(2) << " |" << endl;
	}
	cout << "    ----------------------" << endl;
	RS[0].outputBuffer();
	cout << endl;
	cout << "    ______________________" << endl;
	for (int i = 0; i < RS[1].getSize(); i++)
	{
		Instruction temp = RS[1].getInstruction(i);
		cout << "RS" << i + 4 << " |"
			<< setw(5) << temp.getSymbol() << " |"
			<< setw(5) << temp.getReg(1) << " |"
			<< setw(5) << temp.getReg(2) << " |" << endl;
	}
	cout << "    ----------------------" << endl;
	RS[1].outputBuffer();
	cout << endl << "--------------------" << endl ;
}