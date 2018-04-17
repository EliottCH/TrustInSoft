#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>

#define STACK_SIZE 10

typedef struct {
  int16_t top;
  uint8_t elements[STACK_SIZE];
} myStack;

typedef enum {
  STACK_STATUS_BAD  = 0,
  STACK_STATUS_OK   = 1,
  STACK_STATUS_FULL = 2,
  STACK_STATUS_EMPTY = 3
} e_stack_op_status;

typedef enum {
  FALSE   =0,
  TRUE    =1
} e_bool;

/*@
  predicate isStackEmpty(myStack *pStack) = pStack->top == -1;
  predicate isStackFull(myStack *pStack) = pStack->top >= STACK_SIZE -1
  predicate isStackOK(myStack *pStack) = (-1 <= pStack->top < STACK_SIZE) && (\initialized(pStack->elements));
*/

/*@requires isStackOK(s_pStack);
  @assigns \nothing;
  @ensures isStackEmpty(s_pStack) ==> \result == TRUE;
  @ensures !isStackEmpty(s_pStack) ==> \result == FALSE;
*/
e_bool isEmpty(myStack *s_pStack){
  if(s_pStack->top == -1){
    return TRUE;
  } else {
    return FALSE;
  }
}

/*@requires isStackOK(s_pStack);
  @assigns \nothing;
  @ensures isStackFull(s_pStack) ==> \result == TRUE;
  @ensures !isStackFull(s_pStack) ==> \result == FALSE;
*/
e_bool isFull(myStack *s_pStack){
  if(s_pStack->top >= STACK_SIZE -1){
    return TRUE;
  } else {
    return FALSE;
  }
}

/*@requires isStackOK(s_pStack);
  @assigns s_pStack->top;
  @ensures s_pStack->top = -1;
*/
void initMyStack(myStack *s_pStack){
  s_pStack->top = -1;
}

/*@requires isStackOK(s_pStack);
  @assigns s_pStack->top;
  @ensures !isStackEmpty(s_pStack) ==> ( s_pStack->top == \old(s_pStack->top) - 1 && \result == s_pStack->elements[s_pStack->top+1] )
  @ensures isStackEmpty(s_pStack) ==> \result == 0;
*/
uint8_t popMyStack(myStack *s_pStack){
  if(!isEmpty(s_pStack)){
    s_pStack->top -= 1;
    return s_pStack->elements[s_pStack->top+1];
  }
  return 0;
}

/*@requires isStackOK(s_pStack); 
  @assigns s_pStack->top, s_pStack->elements[\at(s_pStack->top, Post)]
  @ensures isStackFull(s_pStack) ==> \result == STACK_STATUS_FULL;
  @ensures !isStackFull(s_pStack) ==> (s_pStack->top == \old(s_pStack->top) + 1 && s_pStack->elements[\at(s_pStack->top,Post)] == pElement)
*/
e_stack_op_status pushMyStack(myStack *s_pStack, uint8_t pElement){
  if(isFull(s_pStack)){
    return STACK_STATUS_FULL;
  } else {
    s_pStack->top += 1;
    s_pStack->elements[s_pStack->top] = pElement;
  }
}

/*@requires isStackOK(s_pStack); 
  @assigns \nothing;
  @ensures isStackEmpty(s_pStack) ==> \result == STACK_STATUS_EMPTY;
  @ensures isStackFull(s_pStack) ==> \result == STACK_STATUS_FULL;
  @ensures ( !isStackEmpty(s_pStack) && !isStackFull(s_pStack) ) ==> \result == STACK_STATUS_OK;
*/
e_stack_op_status printMyStack(myStack *s_pStack){
	if(isEmpty(s_pStack)){
		printf("The stack is empty\n");
		return STACK_STATUS_EMPTY;
	} else {
		for(int i=0;i<s_pStack->top+1; i++){
			printf("stack[%i] = %x\n", i, s_pStack->elements[i]);
		}
		if (isFull(s_pStack)){
			printf("The stack is full\n");
			return STACK_STATUS_FULL;
		} else {
			return STACK_STATUS_OK;
		}
	}
	return STACK_STATUS_BAD;
}

int main(void){
  e_stack_op_status stat;
  uint8_t popValue;
  myStack s_Stack;

  printf("init\n");
  initMyStack(&s_Stack);
  stat = printMyStack(&s_Stack);

  printf("push(0xAA)\n");
  stat = pushMyStack(&s_Stack,0xAA);
  stat = printMyStack(&s_Stack);

  printf("push(0xBB)\n");
  stat = pushMyStack(&s_Stack,0xBB);
  stat = printMyStack(&s_Stack);

  printf("pop()\n");
  popValue = popMyStack(&s_Stack);
  stat = printMyStack(&s_Stack);

  printf("pop()\n");
  popValue = popMyStack(&s_Stack);
  stat = printMyStack(&s_Stack);
  return 0;
}
