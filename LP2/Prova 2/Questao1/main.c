/*
(Questão 1 - 5 pontos) Faça um programa em C/C++ que crie um arquivo de texto 
que funcionará como um dicionário contendo todas as strings com 4 caracteres 
alfabéticos maiúsculos (de "AAAA" a "ZZZZ"). Cada letra do alfabeto (de A a
Z) deverá ter sua parte do dicionário gerada por uma thread individual, de tal 
forma que esta thread gere todas as strings iniciadas por aquela letra (ex. a 
thread que gerará as strings começando com a letra 'C' gerará as strings de 
"CAAAA" a "CZZZZ"). Depois que todas as threads geram suas partes, a thread 
principal deve gerar um arquivo de texto contendo o dicionário inteiro. 
*/