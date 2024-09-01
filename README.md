# Simulação de Realização de Exames de Raio-X
Este trabalho prático de programação visa simular o processo de exames de raio-X de tórax e diagnóstico em um hospital, com foco na organização das filas em diferentes etapas. Pacientes chegam ao hospital e são atendidos conforme a disponibilidade dos equipamentos. Uma IA sugere diagnósticos preliminares, e os exames são encaminhados para laudo médico.

## Arquivos do código
### `Patient`
#### Estrutura `Patient`
| Variáveis | Tipo |Função |
| :---:        |     :---:      | :---: |
| id  | int | Armazena a Identificação Única do paciente   |
| nome   | char* | Armazena o nome do paciente     |
| hora_chegada     | int      | Armazena o tempo de chegada do paciente      |

#### Funções do `Patient` 
| Funções | Descrição | Parâmetros | Retorna |
|:---:|:---:|:---:|:---:|
| create_patient | Cria um novo paciente | int id , char *nome, int hora_chegada e int tempo_de_espera| Patient* |
| get_patient_id | Retorna o id do paciente | Patient *patient | int |
| get_patient_name | Retorna o nome do paciente | Patient *patient | const char*  |
| print_patient | Imprime na tela as informações do paciente | Patient *patient | void |
| destroy_patient | Destroí o registro de um paciente | Patient *patient | void |
| database_patient | Registra no db.patient.txt as informações do paciente | Patient *patient | void |
### `Exam`
#### Estrutura `Exam`
| Variáveis | Tipo |Função |
| :---:        |     :---:      | :---: |
| id  | int | Armazena a Identificação Única do paciente   |
| nome   | char* | Armazena o nome do paciente     |
| hora_chegada     | int      | Armazena o tempo de chegada do paciente      |

#### Funções do `Patient` 
| Funções | Descrição | Parâmetros | Retorna |
|:---:|:---:|:---:|:---:|
| create_patient | Cria um novo paciente | int id , char *nome, int hora_chegada e int tempo_de_espera| Patient* |
| get_patient_id | Retorna o id do paciente | Patient *patient | int |
| get_patient_name | Retorna o nome do paciente | Patient *patient | const char*  |
| print_patient | Imprime na tela as informações do paciente | Patient *patient | void |
| destroy_patient | Destroí o registro de um paciente | Patient *patient | void |
| database_patient | Registra no db.patient.txt as informações do paciente | Patient *patient | void |

## Como executar:
- 1º Baixe e descompacte o código;
- 2º No terminal linux, execute: make.
  
## Criadores:
- Allicia Rocha
- Vitor Ramos
