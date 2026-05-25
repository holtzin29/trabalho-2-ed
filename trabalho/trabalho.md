UNIVALI – Escola Politécnica – Ciência da Computação
Disciplina 23272 – Estruturas de Dados
Prof. Marcos Carrard
Atividade de Implementação 1 - Listas
LISTAS – Expressões Numéricas
EM DUPLA OU TRIO (NÃO SERÃO ACEITOS TRABALHOS INDIVIDUAIS)
DATA DE ENTREGA 25/05/2026 – ATÉ ÀS 19H – NO MATERIAL DIDÁTICO – desconto se atrasar o
envio no sistema.
APRESENTAÇÃO: DIA 25/04/2026 – DURANTE A AULA
O objetivo deste trabalho é o desenvolvimento de uma aplicação que realize a análise, conversão
e resolução de expressões numéricas com o uso de pilhas e filas.
A entrada do trabalho será uma expressão numérica formada pelos itens descritos a seguir:
operadores (+,-,*,/ e ^), digito numérico (apenas um), variáveis (apenas uma letra) e parêntese,
colchetes e chaves. Todos em qualquer quantidade.
A sua aplicação deverá, em primeiro lugar, converter a expressão data para notação polonesa
invertida e mostrá-la. Durante esse processo, erros sintáticos e de casamento ou ordem de
parêntese, colchetes e chaves devem ser detectados.
Uma vez convertida da expressão, sua aplicação deve solicitar ao usuário o valor das variáveis
identificadas na expressão (números reais) e, com esses valores, solucionar a expressão
apresentando o seu resultado final.
Por exemplo, caso a expressão fornecida seja 3 + {[5 * a] – [b / (3+c)]}, a expressão em notação
polonesa invertida a ser apresentada é 3 5 a * b 3 c + / - +. Ainda, se forem fornecidos os valores
5 para a, 8 para b e 1 para c, o valor final a ser apresentado é 26.
Deve ser implementado:
 TAD de Pilhas e Filas nas formas estática e dinâmica (2,0 pontos) com as seguintes
operações:
o Inicializar
o Inserir e retirar
o Verificar se vazia ou cheia
o Liberar memória ocupada
 Aplicação solucionando o problema (5,0 pontos) com as seguintes funções:
o Entrada de dados via teclado de forma prática;
o Análise e verificação de erros sintáticos e semânticos;
o Solicitação de valores (uma vez somente) para as variáveis em uso;
o Apresentação dos resultados;
 Apresentação em aula (peso 3,0 pontos):
o Participação de todos os integrantes na apresentação. A nota de apresentação
será realizada por integrante do grupo e será individual.
UNIVALI – Escola Politécnica – Ciência da Computação
Disciplina 23272 – Estruturas de Dados
Prof. Marcos Carrard
Atividade de Implementação 1 - Listas
Quesitos:
 Código-fonte:
o Correta implementação de todas as operações das pilhas e filas;
o Permitira a substituição da estrutura entre estática, dinâmica (ou circular) e a
aplicação deve funcionar da mesma forma;
o Adequada escolha do tipo de estrutura para cada finalidade;
o Funcionamento do programa conforme enunciado;
o Estrutura lógica de programação (indentação, comentários, nomenclatura de
termos, elementos de usabilidade, etc...);
o Não fazer uso de estruturas de dados disponíveis nas linguagens (Vector,
ArrayList e outras);
o Uso da linguagem C++ (em caso de outra linguagem, falar com o professor
antes);
 Apresentação em aula
o Participação de todos os integrantes na apresentação. A nota de apresentação
(50% do total) será única (a mesma para cada integrante). Porém, cada um
possuirá uma cota de pontuação da apresentação formada pelo restante da
nota. Essa segunda parte será individual.
o Domínio da implementação e funcionamento do programa por todos os
integrantes. O professor poderá escolher a qualquer momento da apresentação,
qual integrante deverá responder a determinado questionamento.
OBSERVAÇÕES:
 O código-fonte deve ser postado no Material Didático em um arquivo ZIP. Outro
formato terá desconto de 1 ponto. Se o professor não conseguir “abrir” o arquivo, a
nota relativa ao código-fonte será 0.
 Cadastre a sua dupla/nome no momento do envio no Material Didático. Identifique os
integrantes em um comentário no início do “main.cpp” (e outros arquivos de código-
fonte).
 Não serão aceitos trabalhos após o dia de entrega.
 Se o trabalho for apresentado, mas não for postado no Material Didático, será atribuída
nota apenas no quesito da apresentação.
 Se o trabalho for enviado no Material Didático, mas não for apresentado, será atribuída
nota apenas nos quesitos entregues (código-fonte e/ou relatório), sendo que será
descontado 1 ponto por não apresentar.
 Trabalhos com grau de similaridade terão a nota dividida pelo número de entregas
similares. Dica: não repassem código-fonte para os colegas e não poste o código em
sistemas de controle de versão publicamente.