# :heart: Projeto Oxímetro com Medição de Batimentos Cardíacos e Comunicação MQTT

## :sparkles: Descrição do Projeto
Este projeto implementa um sistema de monitoramento de batimentos cardíacos e níveis de oxigênio no sangue (SpO2) utilizando um oxímetro MAX30100. Os dados coletados são exibidos em um display LCD 16x2 e enviados via protocolo MQTT para um broker. Ideal para aplicações de saúde doméstica ou monitoramento remoto de pacientes.

## :computer: Software e Documentação de Código
O código está dividido em duas partes principais:
1. **Monitoramento e Exibição**: Realiza a leitura dos sinais vitais usando o sensor MAX30100, exibe os valores no display LCD, calcula médias ponderadas para evitar leituras esporádicas e envia os dados em formato JSON através da porta serial.
2. **Comunicação MQTT**: Utiliza a conectividade Wi-Fi do módulo ESP8266 para conectar-se a uma rede e enviar os dados coletados para um servidor MQTT. Este segmento também é responsável por receber e processar comandos e dados enviados de volta ao dispositivo.

### :hammer_and_wrench: Estrutura do Código
- Inicialização e configuração do hardware.
- Leitura contínua dos dados de batimento cardíaco e SpO2.
- Cálculo de média ponderada para estabilizar as leituras.
- Envio de dados via JSON e MQTT para processamento ou monitoramento remoto.
- Monitoramento de conexão com o servidor MQTT e reconexão automática, se necessário.

## :gear: Hardware Utilizado
- **ESP8266**: Módulo Wi-Fi para controle e comunicação.
- **MAX30100**: Sensor para medição de pulso e SpO2.
- **LCD 16x2**: Display para exibição dos dados.
- **Conexões**: Cabos e conexões adequadas para interligar o ESP8266, o sensor MAX30100 e o LCD.

### :wrench: Montagem
O sensor MAX30100 é conectado ao ESP8266, controlando a coleta e processamento dos dados. O LCD exibe as informações processadas para o usuário. A alimentação é fornecida via USB ou fonte externa, dependendo da montagem final.

## :link: Interfaces, Protocolos e Módulos de Comunicação
- **I2C**: Comunicação entre o ESP8266 e o LCD.
- **Serial**: Para debug e envio inicial dos dados em formato JSON.
- **Wi-Fi (TCP/IP)** e **MQTT**: Para envio de dados a um servidor ou nuvem.

### :satellite: Configuração MQTT
- **Servidor MQTT**: `192.168.1.6`
- **Tópico MQTT**: `sensor/data`

## :rocket: Uso do Projeto
Para utilizar este projeto, clone o repositório e carregue os códigos fornecidos nos arquivos ao ESP8266. Certifique-se de que todas as conexões de hardware estejam corretas e que o dispositivo esteja conectado à mesma rede Wi-Fi que o broker MQTT. O sistema começará automaticamente a monitorar, exibir e transmitir os dados coletados.

Este projeto é uma excelente base para desenvolver sistemas de monitoramento de saúde mais complexos ou para integrar com sistemas domésticos inteligentes, melhorando o cuidado e o bem-estar do usuário.

![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)
![Compatibility](https://img.shields.io/badge/compatibility-ESP8266-orange.svg)
