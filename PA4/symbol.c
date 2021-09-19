#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Debug.h"
#include "symbol.h"

/** @file symbol.c
 *  @brief You will modify this file and implement the symbol.h interface
 *  @details Your implementation of the functions defined in symbol.h.
 *  You may add other functions if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file. The reference implementation added approximately
 *  110 lines of code to this file. This count includes lines containing
 *  only a single closing bracket (}).
 * <p>
 * @author <b>Elita Danilyuk</b>
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  (1 << 16)

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** defines data structure used to store nodes in hash table */
typedef struct node {
  struct node* next;     /**< linked list of symbols at same index */
  int          hash;     /**< hash value - makes searching faster  */
  symbol_t     symbol;   /**< the data the user is interested in   */
} node_t;

/** defines the data structure for the hash table */
struct sym_table {
  int      capacity;    /**< length of hast_table array                  */
  int      size;        /**< number of symbols (may exceed capacity)     */
  node_t** hash_table;  /**< array of head of linked list for this index */
  char**   addr_table;  /**< look up symbols by addr                     */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */
static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}


/** DONE-@todo implement this function Part A */
sym_table_t* symbol_init (int capacity) {
  sym_table_t* newSymTable = (sym_table_t *)calloc(1, sizeof(sym_table_t));
  
  newSymTable -> capacity = capacity;
  newSymTable -> size = 0;

  char **u = (char**) calloc(65535, sizeof(node_t*));  //2^16 from symTab.html
  newSymTable -> addr_table = u;
  
  node_t** n = (node_t**) calloc(capacity, sizeof(node_t*)); 
  newSymTable -> hash_table = n;

  return newSymTable;
}


/** DONE-@todo implement this function */
void symbol_term (sym_table_t* symTab) {
  symbol_reset(symTab);
  
  // hash table
  free(symTab->hash_table);
  symTab->hash_table = NULL;

  // address table
  free(symTab-> addr_table);
  symTab->addr_table = NULL;
  
  // symTab
  free(symTab);
  symTab = NULL;
}


/** DONE-@todo implement this function */
void symbol_reset(sym_table_t* symTab) {
  for(int i = 0; i < symTab->capacity; i++){
    if(symTab->hash_table[i] == NULL){
      continue;
    }else if ((symTab->hash_table[i] != NULL) && (symTab->hash_table[i]->next != NULL)) {
      node_t* n = symTab->hash_table[i];
      node_t* next;
      while(n != NULL){
        next = n->next;
        free(n->symbol.name);
        n->symbol.name = NULL;
        free(n);
        n = next;
      }
      symTab->hash_table[i] = NULL;
    }else{
      free(symTab->hash_table[i]->symbol.name);
      symTab->hash_table[i]->symbol.name = NULL;
      free(symTab->hash_table[i]);
      symTab->hash_table[i] = NULL;
    }
    symTab->size = 0;
  }
}


/** DONE-@todo implement this function Part A*/
int symbol_add (sym_table_t* symTab, const char* name, int addr) {
  int index = symbol_hash(name) % symTab -> capacity;
  int hash = symbol_hash(name);

  // empty table if null else continue
  if(symTab -> hash_table[index] == NULL){
    node_t* newnode = (node_t*) malloc(sizeof (node_t));
    char* sym = strdup(name);
    newnode -> symbol.name = sym;
    newnode -> symbol.addr = addr;
    newnode -> next = NULL;
    newnode -> hash = symbol_hash(name);
    symTab -> hash_table[index] = newnode;
    symTab -> size++;
    symTab -> addr_table[addr] = sym;    //addr or sym??
    return 1;
  }else{
    // if element does not exist, add
    if (symbol_search(symTab, name, &hash, &index) == NULL){
      // is element in bounds
      if(symTab -> capacity > index){
        node_t* newnode = (node_t*) malloc(sizeof(node_t));
        char* sym = strdup(name);
        newnode -> symbol.name = sym;
        newnode -> symbol.addr = addr;
        newnode -> next = symTab -> hash_table[index];
        newnode -> hash = symbol_hash(name);
        symTab -> hash_table[index] = newnode;
        symTab -> size++;
        symTab -> addr_table[addr] = sym;
        return 1;
      }
    }else{
      // table contains element already
      return 0;
    }
  }
  
  return 0;
}


/** DONE-@todo implement this function Part A */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index) {
  *hash = symbol_hash(name);

  *index = *hash % (symTab->capacity);
  if(symTab->hash_table[*index] == NULL){
      return NULL;
  }

  for(int i = 0; i < symTab->capacity; i++){
    node_t* n = symTab->hash_table[i];
    while(n != NULL){
      int result = strcasecmp(name, n->symbol.name);  //compare with strcasecomp
      if(result == 0){
        return n;
      }else{
        n = n->next;
      }
    } //while
  } //for

  return NULL;
}


/** DONE-@todo implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
  int hash = symbol_hash(name);
  int index = hash % symTab->capacity;
  
  node_t* n = symbol_search(symTab, name, &hash, &index);
  hash = n->hash;

  return &(symTab->hash_table[index]->symbol);
}


/** DONE-@todo implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
  if (symTab->addr_table[addr] == NULL){
    return NULL;
  }else{
    return symTab->addr_table[addr];
  }
}


/** DONE-@todo implement this function Part A*/
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {
  if(symTab->capacity == 1){
    node_t* n = symTab->hash_table[0];
    while(n != NULL){
      (*fnc)(&(n->symbol),data);

      if(n->next == NULL){
        break;
      }else{
        n = n->next;
      }
    }
  }else{
    for(int i = 0; i < symTab->capacity; i++){
      node_t* n = symTab->hash_table[i];  
      while(n != NULL){
        (*fnc)(&(n->symbol),data);

        if(n->next == NULL){
            break;
        }else{
          n = n->next;
        }
      } //end while
    }//end for
  }//end if-else
}


/** DONE-@todo implement this function */
int symbol_size (sym_table_t* symTab) {
  return symTab->size;
}


/** DONE-@todo implement this function */
int compare_names (const void* vp1, const void* vp2) {
  symbol_t* sym1 = *((symbol_t**) vp1);
  symbol_t* sym2 = *((symbol_t**) vp2);
  
  char* a = (sym1->name);
  char* b = (sym2->name);
  
  return strcasecmp(a, b);
}


/** DONE-@todo implement this function */
int compare_addresses (const void* vp1, const void* vp2) {
  symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this
  symbol_t* sym2 = *((symbol_t**) vp2);
  int a = (sym1->addr) - (sym2->addr);
  
  if(a != 0){
    return a;
  }else{ 
    return compare_names(&sym1, &sym2);
  }
}


/** DONE-@todo implement this function */
symbol_t** symbol_order (sym_table_t* symTab, int order) {
  // will call qsort with either compare_names or compare_addresses
  symbol_t** s = (symbol_t**)calloc(symTab->size, sizeof(symbol_t*));
  int j = 0;

  for(int i = 0; i < symTab->capacity; i++){
    node_t* n = symTab->hash_table[i];
    if(symTab->hash_table[i] == NULL){
      continue;
    }else{  
      while(n != NULL){
        s[j] = &(n->symbol);
        j += 1;

        if(n->next == NULL){
            break;
        }else{
          n = n->next;
        }
      } //end while
    } //end if-else
  } //end for
   
  if(order == 0 && s[0] != NULL){
    return s;
  }else if(order == 1 && s[0] != NULL){
    qsort(s, symTab->size, sizeof(symbol_t*), compare_names);
    return s;
  }else if(order == 2 && s[0] != NULL){
    qsort(s, symTab->size, sizeof(symbol_t*), compare_addresses);
    return s;
  }else{
    return NULL; }
  
  return NULL;
}

