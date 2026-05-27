<div align="center">
  <img src="https://img.shields.io/badge/PROGRAMA-DO_PIAUÍ_PARA_O_MUNDO_2026-00562C?style=for-the-badge&logo=github&logoColor=white" alt="Do Piauí para o Mundo">
  <img src="https://img.shields.io/badge/TRILHA-HACKATHON_ENSINO_SUPERIOR-1A365D?style=for-the-badge" alt="Trilha Superior">
  <br><br>
  <h1>PROJETO <span style="color:#1A365D">A.T.L.A.S.</span></h1>
  <h3><b>Sistema de Assistência em Terapia e Locomoção Adaptativa</b></h3>
  <p><i>Desenvolvido por acadêmicos do PIT (Piauí Instituto de Tecnologia) como solução de tecnologia assistiva para reabilitação pediátrica.</i></p>
</div>

---

<table>
  <tr>
    <td bgcolor="#EBF8FF"><font color="#2B6CB0"><b>NOTA DE ARQUITETURA:</b> Este repositório hospeda o MVP funcional da solução técnica, compreendendo o software de processamento tridimensional de imagem (Python) e o firmware de controle de potência de hardware (C++/Arduino), conectados via protocolo de comunicação serial sem fio.</font></td>
  </tr>
</table>

---

## <span style="color:#00562C">1. Contextualização e Justificativa</span>

A cinesioterapia pediátrica convencional representa um desafio significativo no desenvolvimento motor de crianças neurodivergentes e neurotípicas. Por ser baseada em exercícios analógicos e repetitivos, o tratamento frequentemente gera desinteresse, fadiga crônica e resistência ativa por parte dos pacientes, culminando na quebra ou abandono voluntário do acompanhamento clínico.

De acordo com o referencial teórico do projeto, essa interrupção gera sérios impactos interligados:
* **Impacto Biológico:** Favorecimento da poda sináptica (perda de conexões neurais recém-formadas por falta de estímulo) e o avanço de encurtamentos musculares severos.
* **Impacto Psicológico:** Frustração e estresse infantil durante as sessões.
* **Impacto Socioeconômico:** Sobrecarga emocional e financeira sobre os cuidadores, agravada pelo custo proibitivo das tecnologias assistivas importadas disponíveis no mercado nacional.

O **Projeto A.T.L.A.S.** mitiga esse cenário ao aplicar a Visão Computacional para criar um ambiente de reabilitação completamente não invasivo (sem fios ou sensores colados ao corpo), mascarando o esforço mecânico da terapia através de uma dinâmica gamificada.

---

## <span style="color:#0F4C81">2. Stack Tecnológica Detalhada</span>

O ecossistema foi construído utilizando componentes de alta acessibilidade para garantir a viabilidade econômica do protótipo:

* **Ambiente Python (v3.10+):** Central lógica responsável por rodar o pipeline de processamento digital de imagem.
* **OpenCV (opencv-python):** Responsável por gerenciar a webcam do computador host, capturar a matriz de pixels brutos em tempo real e realizar a conversão do espaço de cor BGR para RGB.
* **MediaPipe Hands (mediapipe):** Framework utilizado para interceptar os frames tratados e realizar o rastreamento topológico da mão do paciente através da extração de 21 pontos articulados tridimensionais (Landmarks) em coordenadas cartesianas.
* **PySerial:** Módulo responsável pelo controle de I/O, gerenciando a abertura da porta serial virtual (COM) e a transmissão dos pacotes de dados via Bluetooth.
* **Firmware C++ (Arduino IDE):** Código nativo em C++ embutido no microcontrolador para leitura activa do buffer serial e modulação por largura de pulso (PWM).

---

## <span style="color:#C05621">3. Engenharia e Análise do Diagrama de Arquitetura</span>

Abaixo está a representation oficial do fluxo de dados do sistema (conforme o arquivo `diagrama.jpeg` integrado ao repositório):

<div align="center">
  <img src="./diagrama.jpeg" alt="Diagrama de Arquitetura da Solução A.T.L.A.S." width="85%">
</div>

### Explicação Detalhada do Fluxograma: A Dinâmica de Causa e Efeito

O sistema opera em uma malha de feedback fechada baseada em ações físicas e respostas mecânicas estruturadas da seguinte forma:

* **A Causa (Entrada e Processamento de Dados):**
  Durante a sessão de fisioterapia, o paciente realiza o movimento gestual prescrito no campo de visão da Webcam. O OpenCV captura essa sequência de frames e a envia para o MediaPipe Hands, que mapeia instantaneamente a anatomia da mão do usuário. 
  
  O script Python executa uma análise geométrica baseada em regras matemáticas estritas sobre os 21 pontos mapeados (medindo a distância pixelar entre os nós dos dedos). Quando o paciente atinge a abertura ou o posicionamento correto da mão exigido pelo exercício, a lógica do script é validada e gera um comando de direção correspondente, transmitido como um caractere serial específico (como o caractere 'F' para frente).

* **O Efeito (Comunicação e Atuação Mecânica):**
  O caractere gerado é imediatamente injetado na porta serial e transmitido sem fio via Bluetooth através do protocolo serial de radiofrequência (RFCOMM). O receptor acoplado ao protótipo capta o sinal e o transfere para o Arduino Uno.
  
  O firmware do Arduino interpreta o caractere recebido e aciona os pinos digitais de controle de velocidade e direção conectados ao driver Ponte H L298N. A Ponte H libera a corrente de potência necessária para ativar os Motores CC, fazendo com que o Carrinho se desloque fisicamente para a frente. 
  
  Esse movimento do robô atua como um feedback lúdico visual imediato para a criança. Ao perceber que o seu movimento corporal controla o veículo, o paciente recebe um estímulo cognitivo positivo, gerando o efeito terapêutico desejado: aumento do engajamento, extensão do tempo de foco na sessão e continuidade do tratamento voluntário.

---

## <span style="color:#9B2C2C">4. Módulo de Hardware e Atuação Física</span>

Abaixo está o registro visual do protótipo robótico móvel (carrinho adaptado) desenvolvido para a validação do MVP em ambiente clínico:

<div align="center">
  <img src="./hardware.jpeg" alt="Protótipo do Carrinho Robótico A.T.L.A.S." width="65%">
</div>

### Componentes e Conexões Técnicas

<table>
  <tr>
    <td bgcolor="#FFF5F5"><font color="#9B2C2C"><b> CONTROLADOR E POTÊNCIA:</b> O coração do carrinho é composto por um microcontrolador <b>Arduino Uno</b>, encarregado de ler o sinal do receptor Bluetooth, e pela <b>Ponte H L298N</b>, que funciona como o driver de corrente isolada para proteger o microcontrolador e alimentar os motores CC.</font></td>
  </tr>
  <tr>
    <td bgcolor="#F0FFF4"><font color="#22543D"><b> COMUNICAÇÃO SEM FIO:</b> A recepção de dados utiliza um módulo <b>Bluetooth HC-05 (ou HC-06)</b> configurado em modo Slave, operando a uma taxa de transmissão padrão de 9600 bps na porta serial de hardware (RX/TX).</font></td>
  </tr>
</table>

---

## <span style="color:#2B6CB0">5. Desenvolvedores e Colaboradores</span>

O desenvolvimento técnico deste MVP foi realizado de forma colaborativa pela equipe de acadêmicos do projeto.

<table align="center">
  <tr>
    <td align="center" width="180px">
      <a href="https://github.com/Renataoliver-dev">
        <img src="https://img.shields.io/badge/RO-Renata_Oliver-1A365D?style=for-the-badge&logo=github" alt="Renata Badge"><br><br>
        <sub><b>@Renataoliver-dev</b></sub>
      </a>
    </td>
    <td align="center" width="180px">
      <a href="https://github.com/miguelolvr">
        <img src="https://img.shields.io/badge/MO-Miguel_Oliver-00562C?style=for-the-badge&logo=github" alt="Miguel Badge"><br><br>
        <sub><b>@miguelolvr</b></sub>
      </a>
    </td>
    <td align="center" width="180px">
      <a href="https://github.com/snmaccall">
        <img src="https://img.shields.io/badge/SM-snmaccall-C05621?style=for-the-badge&logo=github" alt="Colega Badge"><br><br>
        <sub><b>@snmaccall</b></sub>
      </a>
    </td>
  </tr>
</table>

<br>

* **Professora Orientadora:** Isamara da Silva Nascimento (PIT)

---
<div align="center">
  <small>Repositório acadêmico oficial submetido à avaliação da banca examinadora da 6ª Fase do Programa Do Piauí para o Mundo 2026.</small>
</div>
