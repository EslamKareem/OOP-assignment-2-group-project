#pragma once
class ALU
{
public:
	ALU();

	int addTwosComplement(int a, int b);
	int addFloat(int a, int b);
	int bitOr(int a, int b);
	int bitAnd(int a, int b);
	int bitXor(int a, int b);
	int rotateRight(int value, int steps);

private:
	double toFloat(int bits);
	int fromFloat(double value);

};