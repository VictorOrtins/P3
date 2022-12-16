sexo = []
altura = []

numero_pessoas = 4

for i in range(numero_pessoas):
    sexo.append(input("Digite o sexo: "))
    altura.append(float(input("Digite a altura: ")))

maior = 0
menor = 0

maior_sexo = ""
menor_sexo = ""

for i in range(numero_pessoas):
    temp_sexo = sexo[i]
    temp_altura = altura[i]

    if i == 0:
        maior = temp_altura
        menor = temp_altura

        maior_sexo = temp_sexo
        menor_sexo = temp_sexo
        continue

    if temp_altura > maior:
        maior = temp_altura
        maior_sexo = temp_sexo
    elif temp_altura < menor:
        menor = temp_altura
        menor_sexo = temp_sexo


print(f"Maior indivíduo: {maior} e {maior_sexo}")
print(f"Menor indivíduo: {menor} e {menor_sexo}")

num_feminino = 0
num_masculino = 0

total_altura_masculino = 0
total_altura_feminino = 0

for i in range(numero_pessoas):
    if sexo[i] == "F":
        num_feminino += 1
        total_altura_feminino += altura[i]
    elif sexo[i] == "M":
        num_masculino += 1
        total_altura_masculino += altura[i]

print(f"Média F: {total_altura_feminino/num_feminino}")
print(f"Média M: {total_altura_masculino/num_masculino}")



    

    