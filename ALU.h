#pragma once
class ALU
{
public:
	ALU();

	int addTowscomplement(int a, int b);
	int bitwiseAnd(int a, int b);
	int bitwiseOr(int a, int b);
    int rotateRight(int value, int shiftCount);
	int addFloatingPoint(int a, int b);

};