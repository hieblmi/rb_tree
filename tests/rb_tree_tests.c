#include <sys/time.h>

#include "../src/rbt.h"

#define N_TEST_NODES 10000000

typedef struct _Testrecord {
	unsigned int n_nodes;
	time_t start;
	time_t end;
} Testrecord;

void test_1(void) {
    insert("Konrad");
    print_names();
    insert("Heinrich");
    print_names();
    insert("Karl");
    print_names();
    insert("Anette");
    print_names();
    insert("Friedrich");
    print_names();
    insert("Anton");
    print_names();
    insert("Olga");
    print_names();
    insert("Eva");
    print_names();
    insert("Adam");
    print_names();
    delete("Anton");
    print_names();
}

char *rnd_string(void) {
    static char charset[] = "abcdefghijklmnopqrstuvwxyz";

    int len = rand() % MAX_NAME_LENGTH;
    char *string=(char *)malloc((len+1)*sizeof(char));
    int i;
    for(i=0; i<len; i++) {
        int letter_index = rand() % strlen(charset);
        string[i] = charset[letter_index];
    }
    debug("Generated string: %s\n", string);
    string[i] = '\0';

    return string;
}

void test_2(void) {
    time_t t;
    
    time(&t);
    srand((unsigned int) t);
    int i;
    for(i=0; i<10000;i++) {
        char *s = rnd_string();
        insert(s);
        free(s);
    }
    //print_names();
}

long long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

void insert_performance() {
	unsigned long i;	
    long long start = current_timestamp();
    long long end;
    for(i=1; i<N_TEST_NODES+1; i++) {
        char *s = rnd_string();
        if(i % 1000 == 0) {
            end = current_timestamp();
            printf("Total Nodes: %ld, Time to insert 10000 more nodes: %llu milliseconds\n", i, end-start);
            start = current_timestamp();
       } else {
           insert(s);
       }
       free(s);
   }  

}

void performance_tests() {
	insert_performance();	
}

int main() {

	// test_1();
    // test_2();
    performance_tests();

    return 0;    
}
