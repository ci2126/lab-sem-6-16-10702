#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///Modelo de Representación:
typedef struct nodoc {
	char* key;
	struct nodoc* sig;
} Nodoc;

typedef struct cab {
	//int size;
	Nodoc* alpha;
} Cab;

typedef Cab* Lista;

//Operaciones del tipo abstrato Lista

//Constructores:

//Recibe una cadena y a donde apunta
Nodoc* newNodoc(char* c, Nodoc* sig){
	Nodoc* p = malloc(sizeof(Nodoc));
	p->key = malloc(sizeof(c));
	strcpy(p->key, c);
	p->sig = sig;
	return p;
}

//Crea una lista vacía L con L->alpha == NULL
Lista newLista(){
	Lista L = malloc(sizeof(Cab));
	L->alpha = NULL;
	return L;
}

void addCab(char* k, Lista L){
	Nodoc* p = newNodoc(k, L->alpha);
	L->alpha = p;
//L->alpha = newNodoc(k, L->alpha); ???
}

void addCol(char* k, Lista L){
	if(L->alpha == NULL){
	L->alpha = newNodoc(k, NULL);
	}
	else{
	Nodoc *p = L->alpha;
	while(p->sig != NULL) p = p->sig;
	p->sig = newNodoc(k, NULL);
	}
}
//Observadores:
int esVacia(Lista L){
	return L->alpha == NULL;
}

int estaEn(char* k, Lista L){
	Nodoc* p = L->alpha;
	while(p != NULL && strcmp(p->key, k) != 0) p = p->sig;
	return p != NULL;
}

int estaEnRAux(char* k, Nodoc* n){
	if(n == NULL) return 0;
	else if(strcmp(n->key, k) == 0) return 1;
	else return estaEnRAux(k, n->sig);
}

int estaEnR(char* k, Lista L){
	return estaEnRAux(k, L->alpha);
}

void printLista(Lista L){
	if (L->alpha == NULL) printf("\n[]");
	else {
		Nodoc* p = L->alpha;
		printf("\n[");
		while( p->sig != NULL){
			printf("%s, ", p->key);
			p = p->sig;
		}
	printf("%s]", p->key);
	}
}

///Destructores...
void delete(char* key, Lista L){
	if( L->alpha == NULL) return;
	Nodoc* p = L->alpha;
	if(strcmp(p->key, key) == 0){
	L->alpha = p->sig;
	free(p);
	}
	else {
		while(p->sig != NULL && strcmp(p->sig->key, key) != 0){
			p = p->sig;
		}
		if(p->sig != NULL) {
			Nodoc* q = p->sig;
			p->sig = q->sig;
			free(q);
		}
	}
}

Lista clonar(const Lista L){
	Lista M = newLista();
	Nodoc *p = L->alpha;	
	while(p!=NULL){
		addCol(p->key,M);
		p = p->sig;
	}
	return M;
}

Lista size(const Lista L){
	int cnt = 0;
	Nodoc* p = L->alpha;
	while(p != NULL){
		cnt++;
		p = p->sig;
	}
	return cnt;
}

Lista merge(const Lista L, const Lista M){
	Nodoc *p = L->alpha;
	Nodoc *q = M->alpha;
	Lista N = newLista();
	while (p!=NULL && q!=NULL){
		if(strcmp(p->key,q->key)<=0){
			addCol(p->key, N);
			p = p->sig;
		}else{
			addCol(q->key, N);
			q = q->sig;
		}
	}
	while(p!=NULL){
		addCol(p->key, N);
		p = p->sig;
	}
	while(q!=NULL){
		addCol(q->key, N);
		q = q->sig;
	}
	return N;
}

void insertOrdLista(int x, const Lista L){
	Nodoc *p,*q,*b;
  	int k;
  	q = malloc(sizeof(Nodoc)); 
  	q->key = x; 
  	q->sig = NULL;
  	if (L->alpha == NULL) {
    	L->alpha = q;
    	return L;
  	}
  	b = NULL;
  	p = L->alpha;
  	k = 0;
  	while (p != NULL && k == 0) {
    	if (strcmp(x,p->key) <= 0) k = 1;
    	else {
      		b = p;
      		p = p->sig;
    	}
  	}
  	if (b == NULL) { 
    	q->sig = L->alpha;
    	L->alpha = q;
  	}else{ 
    	b->sig = q;
    	q->sig = p;
  	}
  	return L;
}

void ordenarLista(Lista L){
	if(L != NULL){
		Nodoc *p, *c, *k = NULL;
		p = L->alpha;
		while(p != (L->alpha)->sig){
			c = p->sig;
			while(c != NULL){
				if(p->key > c->key){
					k = p->key;
					p->key = c->key;
					c->key = k;
				}
				c = c->sig;
			}
			p = p->sig;
		}
	}else{
		printf("\nLista no inicializada(Lista vacia).");
	}
}

//programa de pruebas...
int main(void){
	Lista L = newLista();
	printLista(L);
	addCab("Marzo", L);
	addCab("Febrero", L); 
	addCab("Enero", L);
	addCol("Abril", L);
	printLista(L);
	delete("Abril", L);
	printLista(L);
	int K = size(L);
	printf("\nEl tamanio de la lista L es: %d",K);
	if(estaEn("Mes", L)) printf("\nSi se encuentra dentro de la lista");
	else printf("\nNo se encuentra dentro de la lista");
	insertOrdLista("Abril",L);
	printLista(L);
	
	printf("\n");
	Lista N = newLista();
	printLista(N);
	addCol("1", N);
	addCol("3", N);
	addCol("5", N);
	addCol("7", N);
	printLista(N);
	
	printf("\n");
	Lista M = newLista();
	printLista(M);
	addCol("2", M);
	addCol("4", M);
	addCol("6", M);
	addCol("8", M);
	printLista(M);
	
	printf("\n");
	Lista J = merge(N,M);
	printLista(J);
	
	printf("\n");
	Lista O = newLista();
	printLista(O);
	addCol("53", O);
	addCol("24", O);
	addCol("44", O);
	addCol("2", O);
	printLista(O);
	ordenarLista(O);
	printLista(O);
}
