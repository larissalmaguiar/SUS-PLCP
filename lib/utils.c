#include "utils.h"

/**********************************************************************/

void time_start(time_t *t_time, clock_t *c_clock){

	*t_time = time(NULL);
	*c_clock =  clock();
}

double time_stop(time_t t_time, clock_t c_clock){

	double aux1 = (clock() - c_clock) / (double)(CLOCKS_PER_SEC);
	double aux2 = difftime (time(NULL),t_time);
	
	printf("CLOCK = %lf TIME = %lf\n", aux1, aux2);
	
	return aux1;
}


/**********************************************************************/
void die(const char* where) {

	printf("Error at %s: %s.\n",where,errno ? strerror(errno) : "errno not set");
	exit(errno?errno:1);
}
 
void dies(const char* where, char* format, ...) {

	int_t err = errno;
	va_list val;

	printf("Error at %s: %s.\n",where,errno ? strerror(errno) : "errno not set");
	va_start(val,format);
	vprintf(format,val);
	va_end(val);
	printf("\n");

	exit(err ? err : 1);
}
/**********************************************************************/
int_t print_char(char* A, int_t n){

	int_t i;
	for(i=0; i<n; i++)	
		printf("%" PRIdN ") %c\n", i, A[i]);

	printf("\n");

return 0;
}
/**********************************************************************/
unsigned char* cat_char(unsigned char** R, int_t k, size_t *n){

	(*n)++; //add 0 at the end

	int_t i, j;
	int_t l=0;
	unsigned char *str = (unsigned char*) malloc((*n+1)*sizeof(unsigned char));

	for(i=0; i<k; i++){
		int_t m = strlen((char*)R[i]);
		//removes empty strings
		if(m==0){
			(*n)--;
			continue;
		}
		for(j=0; j<m; j++){
			//removes symbols > 255
			if(R[i][j]+1<256 && R[i][j]+1>0) str[l++] = R[i][j]+1;
			else (*n)--;
		}
#if CAT == 1
    str[l++] = 1; //add 1 as separator
#endif
	}

	str[l++]=0;
  if(*n>l){
		str = (unsigned char*) realloc(str, (l)*sizeof(unsigned char));
		printf("N = %" PRIdN "\n", l);
	}
	*n = l;
	
  str[*n]=0;

return str;
}

/**********************************************************************/


