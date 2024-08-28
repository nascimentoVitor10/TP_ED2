# Simulação de Realização de Exames de Raio-X (parte 2)
## Visão Geral
Este trabalho prático de programação visa simular o processo de exames de raio-X de tórax e diagnóstico em um hospital, com foco na organização das filas em diferentes etapas. Pacientes chegam ao hospital e são atendidos conforme a disponibilidade dos equipamentos. Uma IA sugere diagnósticos preliminares, e os exames são encaminhados para laudo médico.
## Principais estruturas de dados
- Patient: representa um paciente, contendo atributos como name (nome), birthdate (data de nascimento), e hora_de_chegada e tempo_de_espera.
- Exam: representa um exame, armazenando informações sobre o paciente e o diagnóstico preliminar. Essa estrutura é composta pelo id (identificação única do exame), rx_id (identificação única da máquina de raio-X), patient_id (identificação única do paciente), condition_IA (pré-diagnóstico produzido pela IA) e priority (representa a pioridade de atendimento do pré-diagnóstico produzido pela IA).
- Report: representa o laudo final do paciente. Essa estrutura é composta pelo id (identificação única do laudo), exam_id (identificação única do exame), condition (o diagnóstico do paciente) e pelo timestramp. 
## Principais decisões de implementação
- Filas de espera: Optou-se por utilizar uma implementação de filas FIFO para simular o fluxo de pacientes e exames, garantindo que a ordem de chegada e pioridades sejam respeitadam.
- Diagnóstico Automatizado: A IA foi implementada sendo responsável por fornecer diagnósticos preliminares com base na lista de patologias fornecidas pelo professor.
- Modularidade: O projeto foi dividido em módulos para melhorar a organização e facilitar a manutenção do código.
## Como executar:
- 1º Baixe e descompacte o código;
- 2º No terminal linux, execute: make.
## Criadores:
- Allicia Rocha
- Vitor Ramos
