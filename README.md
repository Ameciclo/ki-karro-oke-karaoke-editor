# Ki-Karro-Okê Karaoke Editor

![Screenshot](example/screenshots/4.jpeg "Screenshot")

**Ki-Karro-Okê Karaoke Editor** é o fork da Ameciclo para o projeto Ki-Karro-Okê, baseado no [Karaoke Lyric Editor](https://github.com/gyunaev/karlyriceditor) de George Yunaev.

O programa permite editar, sincronizar e exportar letras para karaokê em diversos formatos. Entre os formatos suportados estão LRC, LRCv2, UltraStar e CD+G, além de exportação em vídeo. Diferentemente de uma letra comum, uma letra para karaokê precisa de marcações de tempo que indiquem quando cada linha ou palavra deve aparecer e ser destacada durante a reprodução.

Este fork está sendo usado pela Ameciclo para produzir e ajustar paródias do Ki-Karro-Okê, com foco em fluxo de edição, pré-visualização e tradução da interface para `pt_BR`.

O projeto original é distribuído sob a licença `GNU GPL v3`, e este fork segue a mesma licença.

## Recursos

- Suporte a internacionalização e codificação UTF-8.
- Reprodução de áudio e vídeo sem depender de player externo.
- Exportação para LRC, UltraStar, CD+G e vídeo.
- Importação de letras em múltiplos formatos.
- Ferramentas de edição com desfazer/refazer e marcação de tempo durante a reprodução.
- Janela de pré-visualização para testar a letra sincronizada.
- Configurações específicas de projeto, aparência e exportação.
- Validação de erros comuns no arquivo de letra.

## Recursos Utilizados Neste Fork

Estas são as principais melhorias já incorporadas ao fluxo do Ki-Karro-Okê:

- Tradução da interface para português do Brasil (`pt_BR`).
- Importação de arquivos `SRT`.
- Quebra automática de blocos longos de letra.
- Filtro para mostrar todos os formatos suportados na importação.
- Destaque da marcação de tempo atual no editor durante a reprodução.
- Navegação entre marcações de tempo e linhas de letra.
- `Ctrl` + clique em marcações de tempo para buscar a posição da música.
- Novos modos de layout da pré-visualização.
- Modo de linhas deslizantes na visualização da letra.
- Aplicação dos modos de pré-visualização também na exportação de vídeo e inserção de imagem.
- Reorganização da interface com menu `View`, dock de preview e barras de ferramentas divididas.
- Ações rápidas de configuração no menu de ajustes.
- Controles de aparência movidos para as configurações do projeto.
- Alinhamento entre aparência da pré-visualização e da exportação.
- Ajuste relativo de tamanho de fonte para encaixe em preview e exportação.

## Compilação

Para compilar o projeto, você precisa de:

- Qt 6.5 ou superior
- GStreamer 1.0 ou superior

O comando abaixo deve funcionar:

```bash
qmake && make
```

## Screenshots

![Screenshot](example/screenshots/1.jpeg "Screenshot")
![Screenshot](example/screenshots/2.jpeg "Screenshot")
![Screenshot](example/screenshots/3.jpeg "Screenshot")
![Screenshot](example/screenshots/5.jpeg "Screenshot")

## Licença

Este programa é software livre e é distribuído sob a `GNU General Public License version 3 (GPLv3)`.

Isso significa, em particular, que você pode:

- usar o software
- estudar seu funcionamento
- modificar o código
- redistribuir cópias e versões modificadas

Ao redistribuir, é preciso respeitar os termos da GPL e manter a disponibilização do código-fonte correspondente.

## Créditos

- Projeto original: George Yunaev
- Fork e adaptações para o Ki-Karro-Okê: Ameciclo
