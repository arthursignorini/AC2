// Definição dos pinos que controlam os LEDs no Arduino
int led_vermelho = 13;  // Pino do LED vermelho
int led_amarelo  = 12;  // Pino do LED amarelo
int led_verde    = 11;  // Pino do LED verde
int led_azul     = 10;  // Pino do LED azul

// Variáveis
String memoria[100];   // Memória para armazenar as instruções
String entrada = "";   // Variável para armazenar a entrada do usuário
const int inicio_dados = 4; // Endereço onde começam os dados na memória
int contador_instrucao = 0; // Contador de instruções carregadas na memória
int contador_programa = inicio_dados; // Contador para o andamento do programa
char operacao  = 0; // Operação a ser executada
char operandoX = 0; // Operando X (A)
char operandoY = 0; // Operando Y (B)

// Declaração das funções que serão utilizadas no código
void carregar_memoria();
void carregar_instrucao_na_memoria(String entrada);
void executar_instrucao();
String realizar_instrucao(char X, char Y, char W);
int hexadecimal_para_inteiro(char hexc);
void atualizar_leds(char resultado);
String decimal_para_binario(int valor);
void imprimir_memoria(int endereco);
void imprimir_memoria();

// Função de configuração inicial
void setup() {
    Serial.begin(9600);  // Inicializa a comunicação serial com taxa de 9600 bps
    pinMode(led_vermelho, OUTPUT);  // Configura o pino do LED vermelho como saída
    pinMode(led_amarelo, OUTPUT);   // Configura o pino do LED amarelo como saída
    pinMode(led_verde, OUTPUT);     // Configura o pino do LED verde como saída
    pinMode(led_azul, OUTPUT);      // Configura o pino do LED azul como saída
    carregar_memoria(); // Carrega a memória com valores iniciais
}

// Função que é executada repetidamente
void loop() {
    // Verifica se há dados disponíveis para leitura na porta serial
    if (Serial.available() > 0) {
        entrada = Serial.readString();  // Lê a entrada do usuário como uma string
        carregar_instrucao_na_memoria(entrada); // Carrega as instruções na memória
        executar_instrucao();  // Executa as instruções carregadas
    }
}

// Função para carregar valores iniciais na memória
void carregar_memoria() {
    memoria[0] = contador_programa; // Endereço do programa
    memoria[1] = "0";  // Valor inicial para o LED
    memoria[2] = "0";  // Valor inicial do operando X
    memoria[3] = "0";  // Valor inicial do operando Y
}

// Função para carregar as instruções na memória
void carregar_instrucao_na_memoria(String entrada) {   
    int tamanho = entrada.length();  // Obtém o tamanho da string de entrada
    int i = 0;  // Inicializa o índice da entrada
    while (i < tamanho) {
        if (contador_instrucao < 100) {  // Verifica se há espaço na memória
            memoria[inicio_dados + contador_instrucao] = entrada.substring(i, i + 3); // Carrega cada instrução
            contador_instrucao++;  // Incrementa o contador de instruções
            i += 4;  // Avança o índice de 4 em 4 (3 caracteres + 1 separador)
        } else {
            Serial.println("Memória cheia!");  // Exibe uma mensagem de erro se a memória estiver cheia
            i = tamanho;  // Interrompe o loop se a memória estiver cheia
        }
    }
}

// Função para executar as instruções carregadas
void executar_instrucao() {

    // Exibe a memória carregada no console serial
    Serial.print(memoria[0] + "|");
    Serial.print(memoria[1] + "|");
    Serial.print(memoria[2] + "|");
    Serial.print(memoria[3] + "|");
    for (int i = inicio_dados; i < inicio_dados + contador_instrucao; i++) {
        Serial.print(memoria[i] + "|");
    }
    Serial.println();
    String instrucao = "";  // Inicializa a variável para a instrução
    delay(4000);  // Aguarda 4 segundos


    // Executa as instruções enquanto houver instruções na memória
    while (contador_programa < (inicio_dados + contador_instrucao)) {

        int cont = contador_programa + 1;
       
        memoria[0] = String(cont);  // Armazena o endereço da instrução em hexadecimal
        instrucao = memoria[contador_programa];  // Carrega a instrução a ser executada

        // Extrai os operandos e a operação da instrução
        operandoX = instrucao.charAt(0);
        operandoY = instrucao.charAt(1);
        operacao  = instrucao.charAt(2);

        // Realiza a instrução e obtém o resultado
        String resultado = realizar_instrucao(operandoX, operandoY, operacao);
        operacao = resultado.charAt(0);  // Atualiza o resultado da operação

        // Armazena os resultados na memória
        memoria[1] = operacao;
        memoria[2] = operandoX;
        memoria[3] = operandoY;

        // Atualiza os LEDs com base no resultado da operação
        atualizar_leds(hexadecimal_para_inteiro(operacao));
        imprimir_memoria(contador_programa);  // Imprime a memória no console
        delay(4000);  // Aguarda 4 segundos

        contador_programa++;  // Incrementa o contador de programa
    }
    Serial.println("Fim das instruções!");  // Exibe mensagem indicando o fim das instruções
}

// Função para realizar a operação de acordo com os operandos e a operação fornecida
String realizar_instrucao(char X, char Y, char W) {
    int resultado = 0;  // Inicializa o resultado da operação
    int A = hexadecimal_para_inteiro(X);  // Converte o operando X de hexadecimal para inteiro
    int B = hexadecimal_para_inteiro(Y);  // Converte o operando Y de hexadecimal para inteiro

    // Realiza a operação de acordo com o valor de W (código da operação)
    switch (W) {
        case '0': resultado = 0; break;
        case '1': resultado = 1; break;
        case '2': resultado = A; break;
        case '3': resultado = B; break;
        case '4': resultado = ~A; break;
        case '5': resultado = ~B; break;
        case '6': resultado = A & (~B); break;
        case '7': resultado = (~A) & B; break;
        case '8': resultado = (A & ~B) | (~A & B); break;
        case '9': resultado = (A & ~B) | (~A & B); break;
        case 'A': resultado = ~((A & ~B) | (~A & B)); break;
        case 'B': resultado = A & B; break;
        case 'C': resultado = ~(A & B); break;
        case 'D': resultado = ~(A | B); break;
        case 'E': resultado = A | B; break;
        case 'F': resultado = ~((~A) | (~B)); break;
        default:
            Serial.println("Instrução inválida!");  // Exibe mensagem de erro se a operação for inválida
            break;
    }
    
    // Verifica se o resultado é negativo e ajusta o valor
    if (resultado < 0) {
        resultado += 16;  // Ajuste para valores positivos no intervalo de 0 a 15
    }

    // Retorna o resultado da operação em formato hexadecimal
    return String(resultado, HEX);
}

// Função para converter um caractere hexadecimal para inteiro
int hexadecimal_para_inteiro(char hexc) {
    if (hexc >= '0' && hexc <= '9') return hexc - '0';  // Converte números de '0' a '9'
    if (hexc >= 'A' && hexc <= 'F') return 10 + (hexc - 'A');  // Converte letras de 'A' a 'F'
    if (hexc >= 'a' && hexc <= 'f') return 10 + (hexc - 'a');  // Converte letras de 'a' a 'f'
    return -1;  // Retorna -1 se o caractere não for válido
}

// Função para atualizar os LEDs com base no valor do resultado
void atualizar_leds(int resultado) {
    String binario = decimal_para_binario(resultado);  // Converte o valor para binário
    // Atualiza os LEDs de acordo com os bits do resultado
    digitalWrite(led_vermelho, binario.charAt(0) == '1' ? HIGH : LOW); 
    digitalWrite(led_amarelo, binario.charAt(1) == '1' ? HIGH : LOW); 
    digitalWrite(led_verde, binario.charAt(2) == '1' ? HIGH : LOW); 
    digitalWrite(led_azul, binario.charAt(3) == '1' ? HIGH : LOW); 
}

// Função para converter um número decimal para binário (4 bits)
String decimal_para_binario(int valor) {
    String binario = "";
    for (int i = 0; i < 4; i++) { 
        binario = String(valor % 2) + binario;  // Adiciona o bit atual ao início da string binária
        valor /= 2;  // Divide o valor por 2 para obter o próximo bit
    }   
    return binario;  // Retorna a string binária
}

// Função para imprimir a memória de uma posição específica
void imprimir_memoria(int endereco) {
    int tamanho = inicio_dados + contador_instrucao;  // Tamanho total da memória utilizada
    for (int i = 0; i < tamanho; i++) {
        if (i >= 4 && i == endereco) Serial.print("->");  // Indica o endereço atual
        Serial.print(memoria[i] + "|");  // Exibe o valor armazenado na memória
    }
    Serial.println();  // Nova linha após imprimir a memória
}

// Função para imprimir toda a memória
void imprimir_memoria() {
    int tamanho = inicio_dados + contador_instrucao;  // Tamanho total da memória utilizada
    for (int i = 0; i < tamanho; i++) {
        Serial.print(memoria[i] + "|");  // Exibe o valor armazenado na memória
    }
    Serial.println();  // Nova linha após imprimir a memória
}
