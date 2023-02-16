#include <bits/stdc++.h>

using namespace std;

long long rax, rcx, rbx, rdx, rsp, rbp, rsi, rdi, r8, r9, r10, r11, r12, r13, r14;//program register
int ZF = 1, SF, OF;//condition code
long long PC;//PC
int stat = 1;//state
map<long long, long long> DMEM;//memory
long long* reg[15] = {&rax, &rcx, &rdx, &rbx, &rsp, &rbp, &rsi, &rdi, &r8, &r9, &r10, &r11, &r12, &r13, &r14};
int f = 0;

void read(vector<char>&);

int change(int);

void run(vector<char>&);

bool jug(int);

long long read_const(vector<char>&);

void output();

void output()
{
	if(f)
	{
		printf(",");
	}
	f = 1;
	printf("{\"PC\": %lld, \"REG\": {\"rax\": %lld, \"rcx\": %lld, \"rdx\": %lld, \"rbx\": %lld, \"rsp\": %lld, \"rbp\": %lld, \"rsi\": %lld, \"rdi\": %lld, \"r8\": %lld, \"r9\": %lld, \"r10\": %lld, \"r11\": %lld, \"r12\": %lld, \"r13\": %lld, \"r14\": %lld}, \"MEM\": {", PC, rax, rcx, rdx, rbx, rsp, rbp, rsi, rdi, r8, r9, r10, r11, r12, r13, r14);
	map<long long, long long>::iterator last;
	int flag = 0;
	for(map<long long, long long>::iterator iter = DMEM.begin(); iter != DMEM.end(); iter++)
	{
		if(iter != DMEM.begin())
		{
			if(last->second == 0)
			{
				DMEM.erase(last);
			}
		}
		if(iter->second)
		{
			if(flag)
			{
				printf(", ");
			}
			printf("\"%lld\": %lld", iter->first * 8, iter->second);
			flag = 1;
		}
		last = iter;
	}
	printf("}, \"CC\": {\"ZF\": %d, \"SF\": %d, \"OF\": %d}, \"STAT\": %d}", ZF, SF, OF, stat);
}

int change(int c)
{
	if(c >= 'a')
	{
		return c - 'a' + 10;
	}
	else
	{
		return c - '0';
	}
}

long long read_const(vector<char>& ctx, int j)
{
	long long constant = 0;
	for(int i = 0; i != 8; i++)
	{
		long long temp = ctx[PC + i + j];
		if(temp < 0)
		{
			temp += 256;
		}
		constant += (temp << (i * 8));
	}
	return constant;
}

void read(vector<char>& ctx)
{
	while(1)
	{
		int c, d;
		while(c = getchar())
		{
			while(c == ' ')
			{
				while(c = getchar())
				{
					if(c == '\n')
					{
						break;
					}
				}
			}
			if(c == '0')
			{
				getchar();
				break;
			}
			else if(c == -1)
			{
				for(int i = 0; i != ctx.size(); i++)
				{
					long long temp = ctx[i];
					if(temp < 0)
					{
						temp += 256;
					}
					DMEM[i / 8] += (temp << ((i % 8) * 8));
				}
				return;
			}
		}
		long long int pos;
		scanf("%x", &pos);
		getchar();
		getchar();
		for(int i = ctx.size(); i < pos; i++)
		{
			ctx.push_back(0);
			
		}
		while((c = getchar()) != ' ')
		{
			d = getchar();
			c = change(c);
			d = change(d);
			ctx.push_back((c << 4) + d);
		}
		while(1)
		{
			if((c = getchar()) == '\n')
			{
				break;
			}
		}
	}
	
}

bool jug(int i)
{
	switch(i)
	{
		case 0:
			return true;
			break;
		case 1:
			return SF || ZF;
			break;
		case 2:
			return SF;
			break;
		case 3:
			return ZF;
			break;
		case 4:
			return !ZF;
			break;
		case 5:
			return !SF;
			break;
		case 6:
			return !SF && !ZF;
			break;
		default:
			stat = 4;
			output();
			return 1;
	}
}

void run(vector<char>& ctx)
{
	int code, func, reg1, reg2;
	long long constant;
	long long result;
	while(1)
	{
		if(PC >= ctx.size())
		{
			output();
			return;
		}
		code = (ctx[PC] >> 4) & 15;
		func = ctx[PC] & 15;
		switch(code)
		{
			case 0:
				stat = 2;
				output();
				return;
				break;
			case 1:
				PC++;
				output();
				break;
			case 2:
				reg1 = (ctx[PC + 1] >> 4) & 15;
				reg2 = ctx[PC + 1] & 15;
				if(jug(func))
				{
					if(stat == 4)
					{
						output();
						return;
					}
					**(reg + reg2) = **(reg + reg1);
				}
				PC += 2;
				output();
				break;
			case 3:
				reg2 = ctx[PC + 1] & 15;
				constant = read_const(ctx, 2);
				**(reg + reg2) = constant;
				PC += 10;
				output();
				break;
			case 4:
				reg1 = (ctx[PC + 1] >> 4) & 15;
				reg2 = ctx[PC + 1] & 15;
				constant = read_const(ctx, 2);
				if((**(reg + reg2) + constant) < 0)
				{
					stat = 3;
					output();
					return;
				}
				DMEM[(**(reg + reg2) + constant) / 8] = **(reg + reg1);
				PC += 10;
				output();
				break;
			case 5:
				reg1 = (ctx[PC + 1] >> 4) & 15;
				reg2 = ctx[PC + 1] & 15;
				constant = read_const(ctx, 2);
				if((**(reg + reg2) + constant) < 0)
				{
					stat = 3;
					output();
					return;
				}
				**(reg + reg1) = DMEM[(**(reg + reg2) + constant) / 8];
				PC += 10;
				output();
				break;
			case 6:
				reg1 = (ctx[PC + 1] >> 4) & 15;
				reg2 = ctx[PC + 1] & 15;
				switch(func)
				{
					case 0:
						result = **(reg + reg2) + **(reg + reg1);
						if(**(reg + reg2) > 0 && **(reg + reg1) > 0 && result <= 0 || **(reg + reg2) < 0 && **(reg + reg1) < 0 && result >= 0)
						{
							OF = 1;
						}
						else
						{
							OF = 0;
						}
						ZF = (result == 0);
						SF = (result < 0);
						**(reg + reg2) = result;
						PC += 2;
						output();
						break;
					case 1:
						result = **(reg + reg2) - **(reg + reg1);
						if(**(reg + reg2) > 0 && **(reg + reg1) < 0 && result <= 0 || **(reg + reg2) < 0 && **(reg + reg1) > 0 && result >= 0)
						{
							OF = 1;
						}
						else
						{
							OF = 0;
						}
						ZF = (result == 0);
						SF = (result < 0);
						**(reg + reg2) = result;
						PC += 2;
						output();
						break;
					case 2:
						result = **(reg + reg2) & **(reg + reg1);
						OF = 0;
						ZF = (result == 0);
						SF = (result < 0);
						**(reg + reg2) = result;
						PC += 2;
						output();
						break;
					case 3:
						result = **(reg + reg2) ^ **(reg + reg1);
						OF = 0;
						ZF = (result == 0);
						SF = (result < 0);
						**(reg + reg2) = result;
						PC += 2;
						output();
						break;
					default:
						stat = 4;
						output();
						return;
				}
				break;
			case 7:
				constant = read_const(ctx, 1);
				if(jug(func))
				{
					PC = constant;
				}
				else
				{
					PC += 9;
				}
				output();
				break;
			case 8:
				constant = read_const(ctx, 1);
				rsp -= 8;
				if(rsp < 0)
				{
					stat = 3;
					output();
					return;
				}
				DMEM[rsp / 8] = PC + 9;
				PC = constant;
				output();
				break;
			case 9:
				if(rsp < 0)
				{
					stat = 3;
					output();
					return;
				}
				PC = DMEM[rsp / 8];
				rsp += 8;
				output();
				break;
			case 10:
				reg1 = (ctx[PC + 1] >> 4) & 15;
				if(rsp <= 0)
				{
					rsp -= 8;
					stat = 3;
					output();
					return;
				}
				DMEM[rsp / 8 - 1] = **(reg + reg1);
				rsp -= 8;
				PC += 2;
				output();
				break;
			case 11:
				reg1 = (ctx[PC + 1] >> 4) & 15;
				rsp += 8;
				**(reg + reg1) = DMEM[rsp / 8 - 1];
				PC += 2;
				output();
				break;
			case 12:
				reg2 = ctx[PC + 1] & 15;
				constant = read_const(ctx, 2);
				switch(func)
				{
					case 0:
						result = **(reg + reg2) + constant;
						if(**(reg + reg2) > 0 && constant > 0 && result <= 0 || **(reg + reg2) < 0 && constant < 0 && result >= 0)
						{
							OF = 1;
						}
						else
						{
							OF = 0;
						}
						ZF = (result == 0);
						SF = (result < 0);
						**(reg + reg2) = result;
						PC += 10;
						output();
						break;
					case 1:
						result = **(reg + reg2) - constant;
						if(**(reg + reg2) > 0 && constant < 0 && result <= 0 || **(reg + reg2) < 0 && constant > 0 && result >= 0)
						{
							OF = 1;
						}
						else
						{
							OF = 0;
						}
						ZF = (result == 0);
						SF = (result < 0);
						**(reg + reg2) = result;
						PC += 10;
						output();
						break;
					case 2:
						result = **(reg + reg2) & constant;
						OF = 0;
						ZF = (result == 0);
						SF = (result < 0);
						**(reg + reg2) = result;
						PC += 10;
						output();
						break;
					case 3:
						result = **(reg + reg2) ^ constant;
						OF = 0;
						ZF = (result == 0);
						SF = (result < 0);
						**(reg + reg2) = result;
						PC += 10;
						output();
						break;
					default:
						stat = 4;
						output();
						return;
				}
				break;
			default:
				stat = 4;
				output();
				return;
		}
	}
}