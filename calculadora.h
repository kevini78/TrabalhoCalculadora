#ifndef CALCULADORA_H
#define CALCULADORA_H

#define MAX_EXPR_LENGTH 100


typedef struct {
    double items[MAX_EXPR_LENGTH];
    int top;
} Stack;


void push(Stack *s, double value);
double pop(Stack *s);
double peek(Stack *s);
int is_empty(Stack *s);


double evaluate_postfix(char *expression);


void infix_to_postfix(char *infix, char *postfix);

#endif 