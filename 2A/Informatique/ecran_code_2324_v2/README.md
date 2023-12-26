# Présentation du projet
Globalement tout ce joue dans strategie.c, score.c et le dossier image.

Dans strategie.c il y a la création des boutons et leurs attribution de couleur, il y a plusieur couleur comme le jaune -> LV_PALETTE_YELLOW ou encore le bleu -> LV_PALETTE_BLUE
toute les couleur disponible sont dans un enum que vous pourrez trouver dans la librairie lv_style.h
Il est important de noter que la couleur noir dans lv_style.h est LV_PALETTE_NONE
une fois un bouton sélectionné et que vous appuyé sur "confirmer" un envoie série est réalisé vers la carte principale sous la forme de "%d \r\n".
le %d envoyer sera la valeur du bouton sélectionné

Pour changer l'image de fond il faut changer le code c de TableRedi.c, en gros vous prenez une image .png qui tiens sur l'écran de 480x272 et vous allez sur ce site :
https://lvgl.io/tools/imageconverter
Sur le site vous uplodé votre image préalablement nommé TableRedi.png, ce sera plus simple car en gardant le nom du .c vous pourrez simplement récupérer
le txt générer par le site et copier puis écraser le précédent code dans TableRedi.c . Le process est le même pour changer les chiffres du score et tout est
dans le dossier Image.

score.c justement, en fait il fonctionne avec une interruption sur le RX qui utilise un callback. Donc dés qu'il reçois un char correspondant à un chiffre il l'affichera.
Je me souviens plus trop mais il me semble que ça affiche ce que vous envoyé genre vous envoyé "10" en série ça affichera 10 sur le score


# LVGL ported to STM32F746 Discovery

This is LVGL ported to [STM32F746G-DISCO](https://www.st.com/en/evaluation-tools/32f746gdiscovery.html) using 
[CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) or IAR Embedded Workbench.

## Try it with just a few clicks!

1. Download [lv_stm32f746.bin.zip](https://nightly.link/lvgl/lv_port_stm32f746_disco/workflows/stm32_port/master/lv_stm32f746.bin.zip) and extract the binary inside.
2. Plug in the Discovery board.
3. Copy the binary to the `DIS_F746NG` drive provided by the board's USB interface.

![image](https://user-images.githubusercontent.com/42941056/103720909-71ef5400-4f9a-11eb-8d31-0420c5794b52.png)


# How to compile and make changes
1. Clone (or download) this GitHub repository to a folder on your computer and update the submodules:
`git clone --recursive https://github.com/lvgl/lv_port_stm32f746_disco.git`
2. Open or import the project.
  * CubeIDE
    1. Install [CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html).
    2. Import the project into your workspace.
  * IAR Embedded Workbench

    * Open IAR workspace at `ide/iar/stm32f746_disco_lvgl.eww`

      **NOTE**: LVGL does **NOT** support the 'multi-file compilation' mode.
3. Connect the Discovery board
4. Build and run!

# How to build using VSCode and Devcontainers

## Prerequisits
* [Visual Studio Code](https://code.visualstudio.com/Download)
* [Visual Studio Code Extension : Remote - Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) 
* [Docker Desktop](https://docs.docker.com/desktop/)

## Using Devcontainers
For the background to Microsoft's Development containers see [here](https://code.visualstudio.com/docs/remote/containers)

At the project root, open the project using VSCode
```
$ code .
```

VSCode will then pop up a dialog:
```
Folder contains a Dev Container configuration file. Reopen folder to develop in a container
```
Select *Reopen in Container*

First time through this will build a Docker image from scratch using `.devcontainer/Dockerfile` - this may take a couple of minutes as it includes downloading the `gcc-arm-none-eabi` toolset from `developer.arm.com`. This build is a one-off operation.

Once VSCode has created the Docker image and launched the container, open a new Terminal window (using the VSCode menu). You are now working in an Ubuntu based envrionment.

## To Build

There is a build script supplied. Simply run
```
$ ./build.sh
```
This will create the artifacts:

* `build/debug/lv_stm32f746.elf` 
* `build/debug/lv_stm32f746.bin`

To rebuild, simple repeat:
```
$ ./build.sh
```

If you add new files, then run:
```
$ ./build.sh reset
```


## Debugging

To debug from within the container, `OpenOCD` need to run locally to connect to the target board.

In a terminal window run
```
openocd -f Release/stm32f7.cfg
```
OpenOCD will then wait on port `3333` for a gdb connection
```
Info : starting gdb server for stm32f7x.cpu on 3333
Info : Listening on port 3333 for gdb connections
```

In VSCode/devcontainer select the Run/Debug option `Debug (Remote OpenOCD)`. 

The container uses `arm-none-eabi-gdb` to connect to OpenOCD on port `3333` to reflash the board and support source-level debug.
