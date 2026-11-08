#pragma once
class Register
{
private:
	int value;
public:
	Register();

	int read() const;
	void write(int v);

};

