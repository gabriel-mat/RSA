# RSA algorithm implementation

Implemente o algoritmo de criptografia RSA com suporte a chaves de 512, 1024 e 2048
bits, utilizando a biblioteca GMP. Sua implementação deve ter dois programas que rodam separados:

**1. Gerar um par de chaves RSA** e apresentar a chave na saída padrão com os parâmetros
na seguinte ordem, um por linha:

- Base numérica utilizada para apresentar os parâmetros: 10 (decimal), 16 (hexa)
- Módulo (valor de ‘n’ na base indicada)
- Expoente público (valor de ‘e’ na base indicada)
- Expoente privado (valor de ‘d’ na base indicada)
- Primo p (valor do 1o primo gerador de ‘n’ na base indicada)
- Primo q (valor do 2o primo gerador de ‘n’ na base indicada)

A geração da chave pode utilizar o gerador de números primos e números aleatórios
do GMP, mas deve utilizar sua implementação do Algoritmo de Euclides Estendido
para calcular a expoente privado. Fica flexível como fornecer o tamanho da chave ao
programa.

---

**2. Realizar a cifragem ou decifragem RSA**, utilizando o algoritmo do Quadrado e Multiplicação e receber os seguintes parâmetros da entrada padrão, um por linha:

- Base numérica utilizada para apresentar os parâmetros: 10 (decimal), 16 (hexa)
- Módulo (valor de ‘n’ na base indicada)
- Expoente (valor de ‘e’ ou ‘d’ na base indicada)
- Mensagem (valor de ‘m’ ou ‘c’ na base indicada)

Considerando ‘m’ a mensagem em texto claro e ‘c’ a mensagem em texto cifrado, tal
que:

c = m<sup>e</sup> mod n \
m = c<sup>d</sup> mod n

O algoritmo deve apresentar na saída padrão:
- Base numérica utilizada para apresentar os parâmetros: 10 (decimal), 16 (hexa)
- Mensagem (valor de ‘m’ ou ‘c’ na base indicada)
