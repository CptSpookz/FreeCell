[![GitHub tag](https://img.shields.io/github/tag/Alynva/FreeCell.svg)](https://github.com/Alynva/FreeCell/tags) [![Codacy grade](https://img.shields.io/codacy/grade/ad0f531c54c748269e35392ea2f79756.svg)](https://www.codacy.com/app/Alynva/FreeCell?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Alynva/FreeCell&amp;utm_campaign=Badge_Grade)

# FreeCell

## Repositório do Projeto 1 da disciplina Estrutura de Dados

O objetivo deste projeto é demonstrar a aplicação do primeiro tópico de Estruturas de Dados, Pilha. Para tal usaremos como modelo o jogo de cartas individual Freecell, cuja estrutura é composta de 8 pilhas intermediárias de cartas que estão inicialmente desordenadas e 4 pilhas finais, inicialmente vazias, que deverão ser compostas por cartas de um único naipe para acabar o jogo.

Estrutura de Dados do jogo:
- 8 Pilhas intermediárias serão usadas para o início do jogo e para movimentação inicial das cartas. A regra dessas 8 pilhas é que uma carta só pode ser movimentada se for colocada em cima de outra de valor diretamente maior. Assim, mesmo começando ordenadas aleatoriamente na mesa, as pilhas feitas pelo jogador ficarão em ordem decrescente de valor de cima pra baixo. A segunda regra dessas pilhas é que só pode ser colocada uma carta em cima da outra se elas forem de cores diferentes. Essas duas regras são de simples implementação, apenas sendo necessário um atributo Cor ou Naipe e um valor numérico para cada uma delas, e as operações feitas para se movimentar cartas únicas são simplesmente Pop(x) na pilha original e Push(x) na pilha de destino.
- 4 Espaços de valor único para movimentação extra. Inicialmente vazios. (Acho que esses 4 podem ser simplesmente variáveis ou então Pilhas de valor único que operam simplesmente com Pop() e Push() de uma carta só)
- 4 Pilhas finais, usadas para ordenar as cartas dos 4 naipes e terminar o jogo. Essas pilhas ao contrário das intermediárias são ordenadas em forma crescente, começando no Ás e terminando no Rei, inicialmente vazias. Sua regra é que todas podem ser inicialmente usadas por qualquer naipe, mas após receberem a primeira carta, só poderão receber cartas do naipe da mesma. Só utilizarão Push(), visto que é o destino final das cartas do baralho.
