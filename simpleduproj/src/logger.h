enum EVENT {
    CREATE,
    EXIT,
    RECV_SIGNAL,
    SEND_SIGNAL,
    RECV_PIPE,
    SEND_PIPE,
    ENTRY
};
 
/**
 * Clears the contents and opens the log file
*/
void openLogFile();

/**
 * Logs a message to the log file
*/
void logMessage(char * message);

/**
 * Closes log file descriptor
 */
void closeLog();

/*
instant – pid – action – info

• instant é o instante de tempo imediatamente anterior ao registo, medido em milissegundos e
com 2 casas decimais, tendo como referência o instante em que o programa começou a executar;

• pid é o identificador do processo que faz o registo da linha, com espaço fixo para 8 algarismos;

• action é a descrição do tipo de evento: CREATE, EXIT, RECV_SIGNAL, SEND_SIGNAL, RECV_PIPE, SEND_PIPE e ENTRY;

• info é a informação adicional para cada uma das ações:

    o CREATE – os argumentos da linha de comandos;
    o EXIT – o código de saída (exit status);
    o RECV_SIGNAL – o sinal recebido (por exemplo, SIGINT);
    o SEND_SIGNAL – o sinal enviado seguido do pid do processo a quem se destina;
    o RECV_PIPE – a mensagem recebida;
    o SEND_PIPE – a mensagem enviada;
    o ENTRY – número de bytes (ou blocos) seguido do caminho.
*/

/**
 * Logs any given event
*/
void logEVENT(enum EVENT event, int pid, char * info);

/**
 * Logs event before exiting
*/ 
void terminateProcess(int status);

/**
 *  String array to string 
*/
char * satos(char ** sa, int count);
