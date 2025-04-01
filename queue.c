#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>

void enqueue(struct queue *q, struct game_state state) {
	struct game_state *tempState = (struct game_state*)malloc(sizeof(struct game_state));
	*tempState = state;
	insert_at_tail(&(q->data), (size_t)tempState);
}

struct game_state dequeue(struct queue *q) { 
	if(q->data.head == NULL)
	{
		return (struct game_state){0};
	}
	struct game_state *tempState = (struct game_state*)remove_from_head(&(q->data));
	struct game_state state = *tempState;
	free(tempState);
	return state;
}


//outside function to check if the state is the goal
bool is_goal(struct game_state state){
	int i;
	int j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if(i == 3 && j == 3){
				if (state.tiles[i][j] != 0){
					return false;
				}
			}
			else if (state.tiles[i][j] != (i * 4 + j + 1)){
				return false;
			}
		}
	}
	return true;
}

bool is_equal(struct game_state *s1, struct game_state *s2){
        int i;
        int j;
        for (i = 0; i < 4; i++)
        {
                for (j = 0; j < 4; j++)
                {
                        
                                if (s1->tiles[i][j] != s2->tiles[i][j]){
                                        return false;
                                }
                }
        }
        return true;
}


int number_of_moves(struct game_state start) { 
	if(is_goal(start)){
		return 0;
	}
	struct queue q = {{NULL}};
	struct game_state **visited = malloc(1000000 * sizeof(struct game_state *));
	int visit = 0;
	enqueue(&q, start);
	visited[visit] = malloc(sizeof(struct game_state));
	*(visited[visit]) = start;
	visit++;

	while(q.data.head != NULL){
		struct game_state current = dequeue(&q);
		int move;

		for (move = 0; move < 4; move++)
		{
			struct game_state next = current;

			switch(move){
				case 0: 
					move_up(&next); 
					break;
				case 1:
					move_down(&next);
					break;
				case 2:
					move_left(&next);
					break;
				case 3:
					move_right(&next);
					break;
			}
			bool newState = true;
			int i;
			for (i = 0; i < visit; i++){
				if(is_equal(&next, visited[i])){
					newState = false;
					break;
				}
			}
			if(newState){
				if(is_goal(next)){
					int result = next.num_steps;
					for(i = 0; i < visit; i++){
						free(visited[i]);
					}
					free(visited);
					while(q.data.head != NULL){
						struct game_state *tempState = (struct game_state *)remove_from_head(&(q.data));
						free(tempState);
					}
					return result;
				}
				enqueue(&q, next);
				visited[visit] = malloc(sizeof(struct game_state));
				*(visited[visit]) = next;
				visit++;
			}

		}

		
	}
	int j;
	for(j = 0; j < visit; j++){
		free(visited[j]);

	}
	free(visited);
	return -1; }
