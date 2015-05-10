/*
   orange.c
   
   Developed by xymostech on 5/24/11
   
   Calculates the number of ways to place oranges in bowls
   Such that the distance between two oranges A and B does not equal
   the distance between either A or B and a third orange C
   
   Takes about 2 seconds to run on a 2.5 GHz processor
*/

#include <stdio.h>
#include <string.h>

// The number of bowls and oranges
#define BOWLS 40
#define ORANGES 9

// Checklist of places where oranges can go.
// 0 means an orange can go there
// not a boolean, because more than one orange can block off a 
// certain spot, so it has to allow for numbers greater than 1
char checklist[BOWLS];

// current positions of the oranges
int orange_pos[ORANGES];

// Gets an open spot from the checklist, starting at pos 'start'
// Returns -1 if no spot is found
int get_next_open(int start)
{
	while(start<BOWLS)
	{
		if(!checklist[start++])
			return start-1;
	}
	return -1;
}

// fills out checklist for orange number 'orange'
void generate_checklist(int orange)
{
	int i;
	int double_current_pos = 2*orange_pos[orange];
	int check_pos;
	
	// check off the current spot (because there's an orange already there)
	++checklist[orange_pos[orange]];
	
	// goes through all the oranges before it, and finds what spots are at
	// an equal distance, and checks those off
	for(i=0; i<orange; ++i)
	{
		check_pos = double_current_pos-orange_pos[i];
		
		if(check_pos < BOWLS)
		{
			++checklist[check_pos];
		}
	}
}

// uses checkoff_list to undo the places checked off by orange number 'orange'
void reset_checklist(int orange)
{
	int i;
	int double_current_pos = 2*orange_pos[orange];
	int check_pos;
	
	--checklist[orange_pos[orange]];
	
	for(i=0; i<orange; ++i)
	{
		check_pos = double_current_pos-orange_pos[i];
		
		if(check_pos < BOWLS)
		{
			--checklist[check_pos];
		}
	}
}

// prints the current configuration
void print_config()
{
	// holds an 'O' for the spots where the oranges are
	char orange_config[BOWLS+1];
	
	// holds an 'x' for every spot in the checklist that is open
	char checklist_config[BOWLS+1];
	int i;
	
	memset(orange_config, '-', BOWLS);
	orange_config[BOWLS] = '\0';
	
	memset(checklist_config, '-', BOWLS);
	checklist_config[BOWLS] = '\0';
	
	for(i=0; i<ORANGES; ++i)
	{
		orange_config[orange_pos[i]] = 'O';
	}
	
	for(i=0; i<BOWLS; ++i)
	{
		if(!checklist[i])
			checklist_config[i] = 'x';
	}
	
	printf("%s\t%s\n", orange_config, checklist_config);
}

int main()
{
	int current_orange = 0;
	int ways = 0;
	
	memset(checklist, 0, BOWLS);
	
	orange_pos[0] = -1;
	
	// repeats while there are still oranges that can be placed
	// so if the current orange drops below 0, no more spots are available
	while(current_orange >= 0)
	{
		// finds a new place for the current orange
		orange_pos[current_orange] = get_next_open(orange_pos[current_orange]+1);
		
		// if it couldn't find a place for it, drop down an orange
		if(orange_pos[current_orange] < 0)
		{
			--current_orange;
			
			// doesn't reset for the last orange, because there are no more oranges
			// to be placed, so the checklist is never updated for the last orange
			if(current_orange < ORANGES-1) 
				reset_checklist(current_orange);
		}
		else
		{
			// if it found a place, and it is the last orange, this is a solution
			if(current_orange == ORANGES-1)
			{
				++ways;
				// uncomment this to print out the solutions
				// print_config();
			}
			// otherwise, mark off the checklist, and go up an orange
			else
			{
				generate_checklist(current_orange);
				// the next orange must be at least as far as the current orange
				orange_pos[current_orange+1] = orange_pos[current_orange];
				++current_orange;
			}
		}
	}
	
	printf("%i ways\n", ways);
	
	return 0;
}