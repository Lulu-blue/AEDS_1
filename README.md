# Simulação de Propagação de Incêndios

##  Introdução

Neste repositório é feita uma simulação da propagação de incêndios em uma floresta e a tentativa de sobrevivência de um animal em meio ao fogo. A lógica principal é a criação de um ambiente em que um animal precisa se mover tentando escapar do fogo, utilizando a estratégia de se movimentar pelo melhor caminho possível com base na condição das suas casas vizinhas nas quatro direções ortogonais. O ambiente é criado com base nas informações dadas por um arquivo, que traz informações possibilitando a criação de um espaço 2D (uma matriz).

Também é possível ver e analisar a propagação do fogo utilizando a propagação do vento ou apenas com base em todas as direções ortogonais.
A simulação é controlada por um número máximo de interações, podendo parar de executar quando fogo para de propagar ou quando animal morre, e o movimento é gerenciado por decisões automáticas em torno da posição do animal.

---

##  Metodologia 

![Metodologia usada para criar o codigo](imagens_do_README\obsidian.png)

A imagem acima mostra por numeração quais foram os passos usados para realizar a implementação do código.

- **0. Manipulação de arquivo:**
    - **Pegar Matriz:**
        - A partir de um arquivo `input.dat`, é pega a primeira linha com a altura, comprimento, e as coordenadas do fogo.
        - Nas próximas linhas do arquivo, carregamos o mapa gerando uma matriz de char com as informações do terreno (`0` - vazio, `1` - Árvore saudável, `2` - fogo, `3` - Árvore queimada, `4` - Água).
    - **Salvar a matriz**
        - Em seguida foi feita a função de salvar todas as informações em um arquivo `output.dat`, nele colocamos a lista onde mostra todas as alterações feitas na matriz, a matriz atual, o número da interação e as coordenadas do animal.

- **1. Simulação do fogo:**
    ![Fogo](imagens_do_README\fogo.png)
    - 2: Foi criado um arquivo `fila.c` para as posições do fogo fossem salvas em uma fila, e seguindo a fila o primeiro iria propagar o fogo, os novos fogos iriam para o final da fila e assim por diante.
    - 3: Sem o vento, o fogo irá propagar em todas as posições ortogonais. Inicialmente foi pensado em utilizar quatro if para analisar se o fogo poderia ir para os quatro lados, mas depois foi pensado em uma maneira mais eficiente e mais rápida utilizando dois for, já que dessa forma seria mais fácil de encontrar possíveis erros e entender de maneira mais rápida o código.
    - 4: Agora com o vento, o fogo só poderia propagar em posições específicas na qual seria escolhida pelo usuário. Para isso foi criada uma struct de coordenadas onde o usuário, em um vetor, colocaria quais coordenadas o fogo se propagaria(baixo(1,0), direita(0,1), cima(-1,0), esquerda(0,-1)).
    - 5: A função `FogoVento` foi uma adequação da função `FogoSemVento`, na qual ao invés de usar as posições ortogonais usaria os vetores com as coordenadas específicas do vento (lembrando que se a coordenada do vento fosse (0,0), seria como se não houvesse vento ali).

- **6. Movimento do animal:**
  ![Animal](imagens_do_README\animal.png)
  - 7, 8 e 9: A função `interacaoAgua` foi a primeira criada. Nela eu mudo todas as posições que eram 2 para 3 e tiro essas posições da fila que guarda todos os fogos para que ele não se propague.
  - 10: A lógica usada na função `andar`, responsável pela movimentação do animal, inicia vendo se o animal está em uma água (4), e se ela está lá por 3 interações, se for a primeira interação, a função `interacaoAgua` é ativada e retorna avisando que já é a segunda interação, já na segunda ela só aumenta fazendo com que seja a terceira, assim, por meio de if, ele entenderá que agora terá que andar.
  - 11: Para que o animal possa andar, foi feita uma função para que retorne a melhor coordenada para o animal se mover baseado em prioridades (preferência por células mais seguras).
  - 12: Para que o animal ande, ele cria uma fila, que guarda todas as posições ortogonais(usando a mesma lógica da propagação do fogo) de onde eu posso andar descartando a opção 2 e olhar se está fora dos parâmetros, depois é verificado se existe alguma opção pra andar(se não houver o animal morre), depois a fila das casas vizinhas é mandada para a função prioridade que retorna a coordenada com a prioridade maior.
  - No fim disso tudo, ele retorna o passo que foi dado para que atualize a posição do animal.

- **13. Configurações:**
  ![Configuração](imagens_do_README\configuração.png)
   - 14: As configurações são a parte mais rápida porque nela foi usada a struct coordenada para que o usuário possa colocar as coordenadas do animal, do vento(lembrando que 0,0 representa sem vento e as opções são: baixo(1,0), direita(0,1), cima(-1,0), esquerda(0,-1)), e o número de interações máximas. Todas essas funções retornam as informações colocadas nela para que possam ser usadas no `Run.c`.


- **Ultimos detalhes:**
  ![Run](imagens_do_README\run.png)
  - 15: Teste das funções -> Em um main de teste foi implementado a logica previa de como seria a função run, nele foi feito teste com posições ficticias e um exemplo de mapa para ver possiveis falhas e o que faltaria para complementar essa nova função. Nessa parte foi pensado que a interação do animal deveria está logo depois da propagação do fogo para que quando ocorra a interação do fogo ocorra também uma interação do animal ao mesmo tempo.
  - 16: Salvar caminho do animal -> Foi feito uma função especifica criar a matriz do animal e ir atualizando ela de acordo com as interações e as coordenadas dele.  Após isso foi feita uma função especifica para salvar a matriz do animal e os passos dele no arquivo `output.dat`.
  -17: Função Run-> Com base no main de teste foi montado a função run, responsavel por rodar todos os arquivos para que no main só ela seja chamada. Nela o loop principal é executado até que Acabe o número máximo de interações, ou não existam mais fogos ativos, ou animal morra. Além disso o loop é usado como contador do numero de interações e o número de passos(lembrando que com um if o numerode passos so é contado se o animal muda de posição). Caso o animal morra(ou seja não tenha para onde ir) as coordenadas retornadas são (-1, -1), e com o if se isso ocorrer ele libera a fila com todos os fogos fazendo com que force a parada(aparecendo também com falha de segmtaçõa no entanto não altera a execução).

##  Qual ordem de execução do código
  ![Execução](imagens_do_README\Execução.png)
  - A ordem de execução do codigo é com base nas setas, iniciando de cima para baixo. No run se inicia o loop usando as configurações, o loop é formado pelo fogo e pelo animal, onde quando o fogo executa, o animal executa logo em seguida, fazendo com que quando ocorre uma interação na água, a do fogo no arquivo vira primeiro, e logo depois a interação da agua, por isso elas terão a mesma númeração por que foram feitas no mesmo momento. Dentro do animal tem a interação da agua e é executada detro dele quando o animal encontra a agua, e com isso ocorre o que foi dito anteriormente.
  -No inicio de tudo isso, e lido o arquivo e salvo as informações dentro dele. Dentro do fogo e da agua é salvo as interações ne outro arquivo. No final de tudo é neste mesmo arquivo novo o caminho que o animal fez, seus passos, e se ele permaneceu vivo.


### Execução:
**Expectativa:**
Para validar a metodologia, consideramos o seguinte caso:

- Um mapa carregado de `input.dat`, com áreas de vegetação, espaços vazios e lagos.
- O fogo se inicia em uma posição especifica dada pelo arquivo `input` e se propaga.
- O animal inicia em uma posição dada pelo usuario em comfiguração .

1. O fogo se espalha a cada rodada em regiões conectadas.
2. O animal tenta se mover para áreas mais seguras (não fogo) por meio de prioridades, podendo ver e escolher somente uma casa a frente.
3. Se o animal não encontrar mais rota segura, ele morre e a simulação encerra.
4. Se o animal entra em água, há um prolongamento de sua vida conforme esperado.
5. O caminho percorrido é registrado e exportado ao final.
**Sem vento:**
![Teste 1, não morreu e interagiu com água](imagens_do_README\test1.png)
![](imagens_do_README\executado1.png)

![Teste 2, morreu e não teve água](imagens_do_README\test2.png)
![](imagens_do_README\executado2.png)

**Vento:**
![Teste 4, não morreu e interagiu com água](imagens_do_README\test4.png)
![](imagens_do_README\executado4.png)

![Teste 3, morreu e não teve água](imagens_do_README\test3.png)
![](imagens_do_README\executado3.png)

**Resultado:**
- De acordo com a metodologia, observamos que o animal consegue sobreviver por alguns ciclos até ficar encurralado, momento em que morre.
- Quando consegue atingir a água, há um prolongamento de sua vida.

---

## 4. Conclusões

**Por que o uso de fila para propagação do fogo é mais eficiente que uma abordagem sequencial comum?**

- Porque a fila permite que o fogo se propaga uniformemente a partir das frentes existentes, garantindo um espalhamento natural e permitindo uma duração maior da simulação.
- Uma abordagem sequencial linha-a-linha poderia causar efeitos artificiais (propagação apenas "para baixo" ou "para direita").

**Qual a importância da estrutura `Coordenada`?**

- Ela organiza a posição (x, y) do animal e do fogo, facilitando as operações de movimentação sem necessidade de gerenciar inteiros separados. Também facilita a manipulação das informações dadas na configuração.

**Por que o animal morre quando retorna (-1, -1)?**

- No projeto, o valor (-1, -1) representa explicitamente que não há mais movimentos possíveis (todas as rotas estão bloqueadas). Ao adotar este padrão, torna-se fácil detectar o fim da simulação do animal. Como consequência o copilador retorna falha de segmentação porem não é algo que interrompe nem prejudica a execução.

**Como garantir que a simulação termina sem problemas de memória?**

- Sempre liberar as estruturas alocadas dinamicamente como filas e matrizes no final da simulação, evitando vazamentos de memória.

---

## 6. Modo de Compilação

O projeto já fornece um `Makefile` pronto para automação da compilação e execução.

As opções são:

| Comando        | Função                                                                       |
|----------------|------------------------------------------------------------------------------|
| `make clean`   | Remove todos os arquivos de compilação anteriores e o arquivo output.dat.    |
| `make`         | Compila todo o projeto e gera o binário na pasta `build/`.                   |
| `make run`     | Compila (se necessário) e executa o binário principal (`app`).               |
| `make debug`   | Compila o projeto com informações de debug ativas.                           |
| `make release` | Compila o projeto para modo de alta performance (-O3 otimizado).             |
