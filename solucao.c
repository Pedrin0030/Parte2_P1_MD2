#include <stdio.h>
#include <stdbool.h>



// Calcula o mdc 
int encontrar_mdc(int a, int b) {
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

// Verifica se dois números são primos entre si
bool verificar_coprimos(int num1, int num2) {
    return encontrar_mdc(num1, num2) == 1;
}

// Encontra o inverso modular usando o algoritmo estendido de Euclides
int calcular_inverso(int num, int modulo) {
    int m0 = modulo;
    int y = 0, x = 1;
    
    if (modulo == 1) return 0;

    while (num > 1) {
        // Divisão e troca de valores - método de Euclides
        int quociente = num / modulo;
        int temp = modulo;
        
        modulo = num % modulo;
        num = temp;
        
        temp = y;
        y = x - quociente * y;
        x = temp;
    }
    
    // Ajuste para garantir valor positivo
    if (x < 0) x += m0;
    
    return x;
}

// Verifica se um número é primo (teste simples)
bool teste_primalidade(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Calcula a função totiente φ(n) - versão simplificada
int funcao_totiente(int n) {
    int resultado = n;
    
    // Fatoração por números primos
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            resultado -= resultado / p;
        }
    }
    
    if (n > 1)
        resultado -= resultado / n;
    
    return resultado;
}

// Exponenciação modular eficiente
int potencia_modular(int base, int expoente, int modulo) {
    int resultado = 1;
    base = base % modulo;
    
    while (expoente > 0) {
        if (expoente % 2 == 1)
            resultado = (resultado * base) % modulo;
        
        expoente = expoente >> 1;
        base = (base * base) % modulo;
    }
    
    return resultado;
}


int main() {
    printf("\n=== Cálculo de Divisão Modular e Exponenciação ===\n");
    printf("Disciplina: Matemática Discreta II - Prof. Cristiane\n\n");
    
    // Passo 1: Entrada dos valores para divisão modular
    printf("Vamos começar com a divisão modular H/G em Zn\n");
    printf("Por favor, informe:\n");
    printf("Valor de H: ");
    int H; scanf("%d", &H);
    printf("Valor de G: ");
    int G; scanf("%d", &G);
    printf("Valor de n: ");
    int n; scanf("%d", &n);
    
    // Validação básica
    if (n <= 1) {
        printf("\nOps! O valor de n deve ser maior que 1.\n");
        return 1;
    }
    
    // Ajuste para trabalhar no Zn
    H = (H % n + n) % n;
    G = (G % n + n) % n;
    
    printf("\n=== Passo 1: Verificando condições para divisão ===\n");
    if (!verificar_coprimos(G, n)) {
        printf("Não é possível dividir %d por %d em Z%d\n", H, G, n);
        printf("Motivo: MDC(%d,%d) = %d (precisaria ser 1)\n", G, n, encontrar_mdc(G, n));
        return 0;
    }
    printf("Tudo certo! Podemos dividir %d por %d em Z%d\n", H, G, n);
    
    printf("\n=== Passo 2: Calculando o inverso modular ===\n");
    int inverso_G = calcular_inverso(G, n);
    printf("O inverso de %d em Z%d é: %d\n", G, n, inverso_G);
    
    printf("\n=== Passo 3: Calculando a divisão modular ===\n");
    int a = (H * inverso_G) % n;
    if (a < 0) a += n; // Garante valor positivo
    printf("Resultado da divisão: %d / %d ≡ %d em Z%d\n", H, G, a, n);
    
    // Parte opcional da exponenciação
    printf("\nDeseja calcular uma exponenciação modular com o resultado? (S/N): ");
    char opcao;
    scanf(" %c", &opcao);
    
    if (opcao == 'S' || opcao == 's') {
        printf("\n=== Cálculo de Exponenciação Modular ===\n");
        printf("Usando a = %d como base\n", a);
        printf("Informe o expoente x: ");
        int x; scanf("%d", &x);
        printf("Informe o módulo n1: ");
        int n1; scanf("%d", &n1);
        
        if (n1 <= 1) {
            printf("\nO módulo n1 deve ser maior que 1!\n");
            return 1;
        }
        
        printf("\n=== Passo 4: Verificando condições ===\n");
        if (!verificar_coprimos(a, n1)) {
            printf("Não podemos aplicar Fermat/Euler pois MDC(%d,%d) = %d\n", 
                  a, n1, encontrar_mdc(a, n1));
            return 0;
        }
        printf("Condições satisfeitas! Podemos continuar...\n");
        
        printf("\n=== Passo 5: Escolhendo o método ===\n");
        int x1;
        if (teste_primalidade(n1)) {
            printf("%d é primo - usando Pequeno Teorema de Fermat\n", n1);
            x1 = n1 - 1;  // Fermat: x₁ = n₁ - 1
        } else {
            printf("%d não é primo - usando Teorema de Euler\n", n1);
            x1 = funcao_totiente(n1);  // Euler: x₁ = φ(n₁)
            printf("φ(%d) = %d\n", n1, x1);  // Mostra explicitamente que calculamos φ(n₁)
        }
        
        printf("\n=== Passo 6: Decompondo o expoente ===\n");
        int q = x / x1;
        int r = x % x1;
        printf("Decomposição: %d = %d * %d + %d\n", x, x1, q, r);
        
        printf("\n=== Passo 7: Calculando as partes ===\n");
        int parte1 = potencia_modular(a, x1, n1);
        printf("a^x1 mod n1 = %d^%d mod %d = %d\n", a, x1, n1, parte1);
        
        int parte2 = potencia_modular(parte1, q, n1);
        printf("(a^x1)^q mod n1 = %d^%d mod %d = %d\n", parte1, q, n1, parte2);
        
        int parte3 = potencia_modular(a, r, n1);
        printf("a^r mod n1 = %d^%d mod %d = %d\n", a, r, n1, parte3);
        
        printf("\n=== Resultado Final ===\n");
        int resultado = ((long)parte2 * parte3) % n1;
        printf("%d^%d mod %d ≡ %d\n", a, x, n1, resultado);
    }
    
    printf("\n=== Fim ===\n");

    
    return 0;
}
