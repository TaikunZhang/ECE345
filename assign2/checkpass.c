#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>

//node for each slot in the hashtable
typedef struct hash_node{
	int count;
	char* word;
	struct hash_node* next;

}hash_node;
//hashtable
typedef struct passwords {
	long size;
	struct hash_node** hash_table;
}passwords;

int hash( char *str, int size);
void populate_passwords(struct passwords* passwords, char* word, int index);
void print_entry(struct hash_node* ptr);
void delete_entry(struct hash_node* ptr);
struct passwords * passwords_init(char *word_array, long size);
void passwords_destroy(struct passwords *passwords);
void check_password(passwords* passwords, char *word_array,  long size);
hash_node* passwords_lookup(passwords* passwords, char* p, long size);
char* reverse (char* s);
bool check_invalid(char* s);

//creates the hashtable based from the input textfile
struct passwords *passwords_init(char *word_array, long size)
{
	char *str = strdup(word_array);
	char *ignore = " \t\v\r\n\f";
	str = strtok(str, ignore);
	struct passwords *passwords;

	//create the hash table
	passwords = (struct passwords *)malloc(sizeof(struct passwords));
	assert(passwords);

	//dynamically allocate size number of nodes within hashtable
	passwords->hash_table = (struct hash_node **)malloc((size / 1000) * sizeof(struct hash_node *));
	assert(passwords->hash_table);
	passwords -> size = size / 1000;

	//iterate through the inputted string and parse for words
	while (str != NULL){

		int h = hash(str, size / 1000);
	    populate_passwords(passwords, str, h);
		str = strtok(NULL,ignore);

	}

	free(str);
	return passwords;
}

//inserts a hash node into the hashtable
void populate_passwords(struct passwords* passwords, char* word, int index){

	struct hash_node* current = passwords->hash_table[index];
	struct hash_node* prev = NULL;

	if (current == NULL){
		
		passwords->hash_table[index] = (struct hash_node* )malloc(sizeof(struct hash_node));
		passwords->hash_table[index]->count = 1;
		passwords->hash_table[index]->word = word;
		passwords->hash_table[index]->next = NULL;
		return;

	}

	//index is not null so iterate through nexted list
	else{
		while(current != NULL){

			//if word exists increment count and return
			if (strcmp(current->word, word) == 0){
				current->count++;
				return;
			}
			else{
				prev = current;
				current = current->next;
			}
		}
			//create new node at the end of the nextedlist
			prev->next = (struct hash_node*)malloc(sizeof(struct hash_node));
			current = prev->next;
			current->count = 1;
			current->word = word;
			current->next = NULL;

	return;
	}
}

//hashing function
//dj2b 
int hash( char *str, int size){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != 0)
    	hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash%size);
}

//prints a hashtable entry with its count
void print_entry(struct hash_node* ptr){

	struct hash_node* temp = ptr;

	while(temp != NULL){

		printf("%s:%d\n",temp->word,temp->count);
		temp = temp->next;

	}

	return;
}

void passwords_output(struct passwords *passwords)
{
	for (int i = 0; i < passwords->size; ++i){
		
		if (passwords->hash_table[i] != NULL){

			print_entry(passwords->hash_table[i]);

		}
	}
}

//destroys a hashtable slot
void delete_entry(struct hash_node* ptr){

	struct hash_node* temp = ptr;
	while (temp != NULL){

		free(temp);
		temp = temp -> next;

	} 

	return;
}
//destroys hashtable
void passwords_destroy(struct passwords *passwords)
{
	for (int i = 0; i < passwords->size; ++i){

		if (passwords->hash_table[i] != NULL){

			delete_entry(passwords->hash_table[i]);

		}
	}

	free(passwords->hash_table);
	free(passwords);
}

//hashtable lookup
hash_node* passwords_lookup(passwords* passwords, char* p, long size){
    int key = hash(p, size);

    if(passwords->hash_table[key] == NULL)return NULL;
    else{ 
    	hash_node* current = passwords->hash_table[key];
    	while (current != NULL){
			if(strcmp(current->word, p) == 0){         		
				return current;
			}
			else{                 
				current = current->next;
			}
        }
    }
	return NULL;
}

//checks if the password has complex characters and is of correct size
bool check_invalid(char* s){
    if(strlen(s) < 6 || strlen(s) > 12)
        return true;
    for (int i = 0; i < strlen(s); i++){
        if(!((s[i] >= 48 && s[i] <= 57) || (s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))){
            return true;
        }
    }
    return false;
}

//reverses string
char* reverse(char* s){
    int len = strlen(s);
    char* new = strdup(s);
    int j = 0;
    for(int i = len - 1; i >= 0; i--){
        new[j++] = s[i];
    }
    new[j] = '\0';
    return new;
}

//finds if passwords are VALID or Invalid
void check_password(passwords* passwords,char *word_array, long size){
    char *str = strdup(word_array);
	char *ignore = " \t\v\r\n\f";
	str = strtok(str, ignore);

    while (str != NULL){
        bool invalid_password = false;
        bool exists = false;
        bool reverse_exists = false;
        char* r = reverse(str);
        //printf("REVERSE IS %s, Normal is %s", r,str);
	    hash_node* node = passwords_lookup(passwords, str, size/1000);
        hash_node* r_node = passwords_lookup(passwords, r, size/1000);

        invalid_password = check_invalid(str);
        if(node->count > 1) exists = true;
        if(r_node != NULL) reverse_exists = true;

        if(invalid_password || exists || reverse_exists)
            printf("INVALID password : %s\n", str);
        else
            printf("Valid password : %s\n", str);
		str = strtok(NULL,ignore);
	}

	free(str);
}

int main(int argc, char *argv[])
{
	int fd;
	void *addr;
	struct stat sb;
	struct passwords *passwords;

	/* open file */
	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "open: %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	/* obtain file size */
	if (fstat(fd, &sb) < 0) {
		fprintf(stderr, "fstat: %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	/* map the whole file, sb.st_size is the file size. after this call, the
	   file can be accessed as an array of characters, at address addr. */
	addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (addr == MAP_FAILED) {
		fprintf(stderr, "mmap: %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	/* close the file */
	close(fd);

	passwords = passwords_init(addr, sb.st_size);
	//passwords_output(passwords);
    check_password(passwords,addr,sb.st_size);
    passwords_destroy(passwords);
    munmap(addr, sb.st_size);

	exit(0);
}