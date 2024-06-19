#include <stdio.h>
#include <stdlib.h>
#include "calculadora.h"

int main() {
    char infix_expr[MAX_EXPR_LENGTH];
    char postfix_expr[MAX_EXPR_LENGTH] = "";

    printf("Digite a expressão infixada (use espaço como separador entre os operandos e operadores): ");
    fgets(infix_expr, sizeof(infix_expr), stdin);
    infix_expr[strcspn(infix_expr, "\n")] = '\0'; // Remover o '\n' do final da string

    infix_to_postfix(infix_expr, postfix_expr);
    printf("Notação pós-fixada: %s\n", postfix_expr);

    double result = evaluate_postfix(postfix_expr);
    printf("Resultado: %.6f\n", result);

    return 0;
}