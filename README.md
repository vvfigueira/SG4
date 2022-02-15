# SG4
## Sobre
  Este projeto está sendo desenvolvido, dentro de uma Iniciação Científica, com o objetivo de simular, com o auxílio do conjunto de bibliotecas [Geant4](https://geant4.web.cern.ch/), um detector a gás multi-cátodo em modo de operação de emissão de elétrons únicos; o objetivo é auxiliar a seleção de pulsos verdadeiros de elétrons emitidos do cátodo de alumínio, via efeito fotoelétrico. Foi tomado como modelo os detectores utilizados em [KOPOLOV, et all](https://doi.org/10.1016/j.nima.2018.09.075) e [KOPOLOV, et all](https://arxiv.org/abs/1603.08657).
## Requisitos
  O requisito principal para o funcionamento é uma instalação de Geant4, caso todas suas dependências sejam instaladas não será necessário nenhum outro requisito.
## Compilação
  Caso possua uma instalação das bibliotecas CLHEP fora do diretório de instalação do Geant4, é necessário definir uma variável de ambiente `CLHEP_INCLUDE_DIR=[CLHEP_install_dir]/include/`, e também exportar as bibliotecas `export LD_LIBRARY_PATH=[CLHEP_install_dir]/lib/:${LD_LIBRARY_PATH}`.
  A compilação segue o método padrão do `cmake`, basta executar dentro da pasta desejada para a construção do projeto `cmake [path_to_CMakeLists.txt]` seguido de `make`, isto irá criar o arquivo binário `build` e copiar os arquivos de script `run.mac` e `vis.mac`.
## Uso
  A aplicação possui dois modos de uso, com janela gráfica, e somente batch. Caso seja executado apenas `./build` o projeto será inicializado em modo de janela gráfica, caso seja provido um arquivo de macro, ex.: `run.mac`, executar `./build run.mac` fará o projeto ser executado em modo batch.
## Características
  Atualmente o projeto está definido como um cilindro de alumínio completo de gás Neônio, 1 torr de pressão e 300 K de temperatura, em seu interior, à distâncias de 96 mm e 20 mm do centro do detector estâo posicionados respectivamente os cátodos externo e interno, sendo ambos compostos de 60 fios distribuídos uniformemente pela circunferência. No centro temos o ânodo de ouro.
  O campo elétrico foi definido como sendo radial uniforme por toda a extensão do gás, da forma: 
```
E = cnst*/r
```
  Com a constante sendo 12500 Volts.
  É possível alterar os valores de pressão, temperatura e constante de campo via comandos no arquivo de macro, como consta no exemplo `run.mac`. Atualmente, os arquivos de saída do programa são apenas da energia dos elétrons capturados pelo ânodo, esses arquivos são nomeados com a situação da tomada de dados; exemplo, a simulação é inicializada com 3 runs, a primeira na situação de 1 torr, 300 K, 10 kV, a segunda na situação de 1 torr, 250 K, 5 kV e a última como 0.5 torr, 300 K, 5kV. Serão criados os arquivos `1torr.txt`, `0.5torr.txt`, `300K.txt`, `250K.txt`, `10kV.txt`, `5kV.txt` e `Histo2D.txt`; cada um destes contém os valores de energias obtidos para todas as runs na qual o parâmetro da simulação utilizado foi o nome do arquivo, já o arquivo `Histo2D.txt` contém dados de energia e suas pressões correspondentes para confeccionar um histograma 2D.
