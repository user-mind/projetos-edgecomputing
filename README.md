# Checkpoint 1 - O Caso de Luminosidade
Projeto de circuito para uma vinheria que busca automatizar o monitoramento de luminosiade dos vinhos armazenados na adega da vinícula. Utilizando dos conceitos aprendidos em sala de aula e pesquisas sobre o tema.

## 👥 Equipe do Projeto
* Julia Souza Costa Schiavi 
* Thayna Ferreira Lopes 
* Sofia Viegas Bomeny 
* Luís Felipe Scacchetti 
* Leonardo Eiji Kina 

## 💻 Desenvolvimento

### 🛠️ Componentes utilizadas
* Arduíno Uno 
* Protoboard
* Jumpers
* Resistores de 10 kΩ
* Leds: Verde, Amarelo e Vermelho
* **Fotorresistor LDR**
* Buzzer 

### Explicação 
<dl>

<dt><strong>Fotorresistor LDR</strong></dt>
<dd>O componente principal do circuito será o <strong>Fotorresistor LDR</strong> conectado ao pino A0 que lê tensões variáveis. Ele irá capturar a luminosadade atual do local de modo que com uma lógica adequada podemos definir em qual dos 3 estados representados por Leds <em>(OK / Alerta / Problema)</em> existentes a luz atual se adequa.</dd>

<dt><strong> Buzzer </strong></dt>
<dd> O Buzzer é utilizado para alertar o funcionário da vinheria quando a iluminosidade da adega está acima do ideal, emitindo um som agudo durante 3 segundos ou 1 segundo em uma certa frequência de <em>Hz</em> a depender da luminosidade do local. </dd>

</dl>


### Montagem do circuito
Ambiente simulado para testes do circuito 👉 **[Clique Aqui!](https://www.tinkercad.com/things/f50hGzP5thd/editel?sharecode=tgZ8qZTpCSmsnTTNP5ABrLJkDg0fndhvUkt0YviL7DE)**

![Circuito montado em simulação](image.png)

### 👩‍💻 Código do circuito
O código que executa corretamente o circuito de moniotoramento de luminosidade da vinheira Agnello está na pasta ***CP1_correto/*** com um único arquivo chamado **CP1_correto.ino** presente. Este arquivo é o que permite a IDE do arduino passar o código ao micro-computador e executar o código corretamente.

Pode também apenas clicar aqui 👉 **[CP1_correto.ino](https://github.com/user-mind/projetos-edgecomputing/blob/main/CP1_correto/CP1_correto.ino)**

## ‼️Informações Importantes

### Intervalos de luminosidade e seus valores
<dl>

<dt><strong>Led Verde</strong></dt>
<dd>Possuí luminosidade <strong><em>maior a 800</em></strong>, indicando que a iluminação atual é a ideal<dd>

<dt><strong>Led Amarelo</strong></dt>
<dd>Possuí luminosidade <strong><em>entre 800 e 600</em></strong>, indicando que a iluminação atual não está correta, porém não traz grandes riscos aos vinhos na adega.<dd>

<dt><strong>Led Vermelho</strong></dt>
<dd>Possuí luminosidade <strong><em>abaixo de 600</em></strong>, indicando que a iluminação atual está trazendo risco a aos vinhos armazenados no local em que a luz inadequada está presente. Soando um alarme para indicar o problema no local.<dd>

</dl>

### Som emitido pelo Buzzer
<dl>

<dt><strong>Som Led Amarelo</strong></dt>
<dd>Quando a iluminação do local chega ao estado de alerta, o led é ligado combinado com o som emitido pelo buzzer durante <strong><em>3 segundos em 550Hz</em></strong>, com <strong>1 segundo</strong> de intervalo.</dd>

<dt><strong>Som Led Vermelho</strong></dt>
<dd>Quando a iluminação do local está incorreta, o led é ligado combinado com o som emitido pelo buzzer durante <strong><em>1 segundo com frequência de 1000Hz</em></strong>, com intervalo de <strong>0.5 segundo</strong> entre cada som.</dd>

</dl>
