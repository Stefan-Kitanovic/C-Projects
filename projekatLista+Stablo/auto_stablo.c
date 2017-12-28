#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 20+1

typedef struct auto_st {
	char marka[MAX_NAZIV];
	int kubikaza;
	int godiste;
	struct auto_st *left;
	struct auto_st *right;
} AUTO;

void init_tree(AUTO **root) {
	*root = NULL;
}

void add_to_tree(AUTO *new, AUTO **root) {
	if(*root == NULL) { // Tree is empty
		*root = new;
	} else if (new->kubikaza <= (*root)->kubikaza) {
		add_to_tree(new, &((*root)->left));
	} else if (new->kubikaza > (*root)->kubikaza) {
		add_to_tree(new, &((*root)->right));
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

	new->left = NULL;
	new->right = NULL;

	return new;
}

void read_tree_from(FILE *in, AUTO **root) {
	char tmp_marka[MAX_NAZIV];
	int tmp_kubikaza;
	int tmp_godiste;
	
	while(fscanf(in, "%s %d %d", tmp_marka, &tmp_kubikaza, &tmp_godiste) != EOF) {
		AUTO *new = create_new_item(tmp_marka, tmp_kubikaza, tmp_godiste);
		add_to_tree(new, root);
	}
}

void save_item_to(FILE *out, AUTO *x) {
	fprintf(
		out, "%s %u %u\n", 
		x->marka, x->kubikaza, x->godiste
	);
}

void save_tree_to(FILE *out, AUTO *root) {
	if(root != NULL) {
		save_tree_to(out, root->left);
		save_item_to(out, root);
		save_tree_to(out, root->right);
	}
}

void destroy_tree(AUTO **root) {
	if(*root != NULL) {
		destroy_tree(&((*root)->left));
		destroy_tree(&((*root)->right));
		free(*root);
		*root = NULL;
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

AUTO *get_najnoviji_auto(AUTO *root, int max_kubikaza) {
	if (root == NULL) { // Tree is empty
		return NULL;
	}

	AUTO *best = NULL;
	if (root->kubikaza <= max_kubikaza) { // Ovaj automobil ima OK kubikazu
		best = root;
	}

	AUTO *left = get_najnoviji_auto(root->left, max_kubikaza);
	if (left != NULL) { // Nadjen OK automobil u levom podstablu
		if (best == NULL || left->godiste > best->godiste) { // Nadjen noviji automobil sa OK kubikazom
			best = left;
		}
	}

	// Posto stablo nije perfektno balansirano, postoji mogucnost da se trazeni automobil nalazi i u desnom podstablu
	AUTO *right = get_najnoviji_auto(root->right, max_kubikaza);
	if (right != NULL) { // Nadjen OK automobil u desnom podstablu
		if (best == NULL || right->godiste > best->godiste) { // Nadjen noviji automobil sa OK kubikazom
			best = right;
		}
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

	AUTO *root;
	init_tree(&root);

	read_tree_from(in, &root);
	save_tree_to(out, root);

	AUTO *best = get_najnoviji_auto(root, max_kubikaza);
	if (best == NULL) {
		fprintf(out, "\n\nNema automobila sa zadatom max kubikazom\n");
	} else {
		fprintf(out, "\n\nNajnoviji auto sa kubikazom ne vecom od %d:\n", max_kubikaza);
		save_item_to(out, best);
	}

	destroy_tree(&root);

	fclose(in);
	fclose(out);

	return 0;
}
