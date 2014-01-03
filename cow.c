#include <mini-os/lib.h>

char getchar(void);
void getline(char *);

#define PRG_SIZE 250
#define MEM_SIZE 250

int prg[PRG_SIZE];

int mem[MEM_SIZE];
int mem_pos = 0;
int reg = -1;

const char instrs[][4] =
	{
		"moo",
		"mOo",
		"moO",
		"mOO",
		"Moo",
		"MOo",
		"MoO",
		"MOO",
		"OOO",
		"MMM",
		"OOM",
		"oom"
	};

void remove_white(char in[], int *pos) {
	for(; in[*pos] == ' '; (*pos)++);
}

int read_instr(char in[], int *pos) {
	char instr[4];
	int r_pos, c_pos;
	
	remove_white(in, pos);

	for(r_pos = 0; r_pos < 3; r_pos++) {
		if((instr[r_pos] = in[*pos + r_pos]) == 0) {
			return -1;
		}
	}
	instr[3] = '\0';
	*pos += 3;

	for(c_pos = 0; c_pos < (sizeof(instrs) / sizeof(instrs[0])); c_pos++) {
		if(strcmp(instrs[c_pos], instr) == 0)
			return c_pos;
	}

	return -1;

}

void reset_prg(void) {
	int i;
	
	for(i = 0; i < PRG_SIZE; i++)
		prg[i] = -1;
}

void parse(char *input) {
	int s_pos = 0, p_pos = 0;
	
	reset_prg();

	while((prg[p_pos++] = read_instr(input, &s_pos)) != -1);
	prg[p_pos] = -1;
	
}

int getint(void) {
	int x = 0;
	char buf[40];
	int i;

	getline(buf);

	for(i = 0; buf[i] != '\n'; i++)
		x = (x * 10) + (buf[i] - '0');

	return x;
}

int exec_cmd(int cmd, int pc) {
	switch(cmd) {
		case 0:
			for(pc -= 2; prg[pc] != 7; pc--);
			break;
		case 1:
			mem_pos--;
			pc++;
			break;
		case 2:
			mem_pos++;
			pc++;
			break;
		case 3:
			pc = exec_cmd(mem[mem_pos], pc);
			break;
		case 4:
			if(!mem[mem_pos])
				mem[mem_pos] = getchar();
			else
				printk("%c", (char) mem[mem_pos]);
			pc++;
			break;
		case 5:
			mem[mem_pos]--;
			pc++;
			break;
		case 6:
			mem[mem_pos]++;
			pc++;
			break;
		case 7:
			if(!mem[mem_pos])
				for(pc += 2; prg[pc] != 0; pc++);
			pc++;
			break;
		case 8:
			mem[mem_pos] = 0;
			pc++;
			break;
		case 9:
			if(reg == -1)
				reg = mem[mem_pos];
			else {
				mem[mem_pos] = reg;
				reg = -1;
			}
			pc++;
			break;
		case 10:
			printk("%d\n", mem[mem_pos]);
			pc++;
			break;
		case 11:
			mem[mem_pos] = getint();
			pc++;
			break;
	}

	return pc;
}

void exec(void) {
	int pc;
	for(pc = 0; prg[pc] != -1; pc = exec_cmd(prg[pc], pc));
}

int cow_interpreter(void) {
	char in[800];

	while(1) {
		getline(in);
		parse(in);
		exec();
	}

	return 0;
}
