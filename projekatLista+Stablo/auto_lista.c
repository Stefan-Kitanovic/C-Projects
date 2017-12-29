#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 20+1

typedef struct auto_st {
	char marka[MAX_NAZIV];
	int kubikaza;
	int godiste;
	struct auto_st *next;
} AUTO;

void init_list(AUTO **head) {
	*head = NULL;
}

void add_to_list(AUTO *new, AUTO **head) {
	if(*head == NULL) { // List is empty
		*head = new;
	} else {
		AUTO *last = *head;
		while(last->next != NULL) { // Find the last item in the list
			last = last->next;
		}
		last->next = new;
	}
}

AUTO *create_new_item(char marka[], int kubikaza, int godiste) {
	AUTO *new = (AUTO *)malloc(sizeof(AUTO));
	if (new == NULL) {
		printf("Not enough RAM!\n");
		exit(21);
	}

	strcpy(new->marka, marka);
	new->kubikaza = kubikaza;
	new->godiste = godiste;

	new->next = NULL;

	return new;
}

void read_list_from(FILE *in, AUTO **head) {
	char tmp_marka[MAX_NAZIV];
	int tmp_kubikaza;
	int tmp_godiste;
	
	while(fscanf(in, "%s %d %d", tmp_marka, &tmp_kubikaza, &tmp_godiste) != EOF) {
		AUTO *new = create_new_item(tmp_marka, tmp_kubikaza, tmp_godiste);
		add_to_list(new, head);
	}
}

void save_item_to(FILE *out, AUTO *x) {
	fprintf(
		out, "%s %u %u\n", 
		x->marka, x->kubikaza, x->godiste
	);
}

void save_list_to(FILE *out, AUTO *head) {
	while(head != NULL) {
		save_item_to(out, head);
		head = head->next;
	}
}

void destroy_list(AUTO **head) {
	if(*head != NULL) {
		destroy_list(&((*head)->next));
		free(*head);
		*head = NULL;
	}
}

FILE *safe_fopen(char *filename, char *mode, int error_code) {
	FILE *fp = fopen(filename, mode);
	if (fp == NULL) {
		printf("Can't open '%s'!\n", filename);
		exit(error_code);
	}
	return fp;
}

AUTO *get_najnoviji_auto(AUTO *head, int max_kubikaza) {
	if (head == NULL) { // List is empty
		return NULL;
	}

	AUTO *best = NULL;
	while(head != NULL) {
		if (head->kubikaza <= max_kubikaza) { // Samo automobili sa OK kubikazom
			if (best == NULL) { // Pre ovoga nije bilo automobila sa OK kubikazom
				best = head;
			} else if (head->godiste > best->godiste) { // Nadjen noviji automobil sa OK kubikazom
				best = head;
			}
		}
		
		head = head->next;
	}

	return best;
}

int main(int arg_num, char *args[]) {
	if (arg_num != 4) {
		printf("USAGE: %s MAX_KUBIKAZA IN_FILENAME OUT_FILENAME\n", args[0]);
		exit(11);
	}

	int max_kubikaza = atoi(args[1]);
	char *in_filename = args[2];
	char *out_filename = args[3];

	FILE *in  = safe_fopen(in_filename,  "r", 1);
	FILE *out = safe_fopen(out_filename, "w", 2);

	AUTO *head;
	init_list(&head);

	read_list_from(in, &head);
	save_list_to(out, head);

	AUTO *best = get_najnoviji_auto(head, max_kubikaza);
	if (best == NULL) {
		fprintf(out, "\n\nNema automobila sa zadatom max kubikazom\n");
	} else {
		fprintf(out, "\n\nNajnoviji auto sa kubikazom ne vecom od %d:\n", max_kubikaza);
		save_item_to(out, best);
	}

	destroy_list(&head);
	
	fclose(in);
	fclose(out);

	return 0;
}
