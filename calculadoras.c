#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Funções de Pilha
void push(Stack *s, double value) {
    if (s->top < MAX_EXPR_LENGTH - 1) {
        s->top++;
        s->items[s->top] = value;
    } else {
        fprintf(stderr, "Erro: Pilha cheia\n");
        exit(EXIT_FAILURE);
    }
}

double pop(Stack *s) {
    if (s->top >= 0) {
        double value = s->items[s->top];
        s->top--;
        return value;
    } else {
        fprintf(stderr, "Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

double peek(Stack *s) {
    if (s->top >= 0) {
        return s->items[s->top];
    } else {
        fprintf(stderr, "Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

int is_empty(Stack *s) {
    return s->top == -1;
}

// Funções de Avaliação de Expressão em Notação Pós-fixada
double evaluate_postfix(char *expression) {
    Stack stack;
    stack.top = -1;

    char *token = strtok(expression, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&stack, atof(token));
        } else {
            double operand2 = pop(&stack);
            double operand1 = pop(&stack);
            double result;

            switch (token[0]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                case '^':
                    result = pow(operand1, operand2);
                    break;
                case 'l': // log or ln
                    if (token[1] == 'o') { // log
                        result = log10(operand1);
                    } else { // ln
                        result = log(operand1);
                    }
                    break;
                case 's': // sen or sin
                    if (token[1] == 'e') { // sen
                        result = sin(operand1);
                    } else { // sin
                        result = sin(operand1 * M_PI / 180); // Convertendo para radianos
                    }
                    break;
                case 'c': // cos
                    result = cos(operand1 * M_PI / 180); // Convertendo para radianos
                    break;
                case 't': // tg or tan
                    if (token[1] == 'g') { // tg
                        result = tan(operand1 * M_PI / 180); // Convertendo para radianos
                    } else { // tan
                        result = tan(operand1);
                    }
                    break;
                default:
                    fprintf(stderr, "Erro: Operador inválido\n");
                    exit(EXIT_FAILURE);
            }

            push(&stack, result);
        }
        token = strtok(NULL, " ");
    }

    return pop(&stack);
}

// Função para converter Expressão Infixa para Pós-fixada
void infix_to_postfix(char *infix, char *postfix) {
    Stack stack;
    stack.top = -1;
    char *output = postfix;
    char *token = strtok(infix, " ");

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            strcat(output, token);
            strcat(output, " ");
        } else if (strchr("+-*/^", token[0]) != NULL) {
            while (!is_empty(&stack) && stack.items[stack.top] != '(' &&
                   ((token[0] != '^' && strchr("+-*/", stack.items[stack.top]) != NULL) ||
                    (token[0] == '^' && stack.items[stack.top] == '^'))) {
                char op[3] = {pop(&stack), '\0'};
                strcat(output, op);
                strcat(output, " ");
            }
            push(&stack, token[0]);
        } else if (strchr("lsc", token[0]) != NULL) {
            push(&stack, token[0]);
        } else if (token[0] == '(') {
            push(&stack, '(');
        } else if (token[0] == ')') {
            while (!is_empty(&stack) && stack.items[stack.top] != '(') {
                char op[3] = {pop(&stack), '\0'};
                strcat(output, op);
                strcat(output, " ");
            }
            pop(&stack); // Removendo o '(' da pilha
        } else {
            fprintf(stderr, "Erro: Caractere inválido na expressão\n");
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, " ");
    }

    while (!is_empty(&stack)) {
        char op[3] = {pop(&stack), '\0'};
        strcat(output, op);
        strcat(output, " ");
    }
}