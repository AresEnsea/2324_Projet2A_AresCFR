#L'image servant de base
FROM ros:humble

#Installation d'outils qui pourront etre utiles par la suite
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y git && apt-get install -y python3-pip
RUN apt-get install -y i2c-tools && apt-get install -y nano
RUN rm -rf /var/lib/apt/lists/*

#Pour retirer l'erreur "setup.py is deprecated" lors du build
RUN pip install setuptools==58.2.0

# Installation de curl et des pilotes Phidget
RUN apt-get update && apt-get install -y curl \
    && curl -fsSL https://www.phidgets.com/downloads/setup_linux | bash - \
    && apt-get install -y libphidget22 libphidget22-dev
RUN pip install Phidget22

# Installation de tf_transformations
RUN apt-get install ros-humble-tf-transformations
RUN pip install transforms3d

# Installation de pyserial
RUN pip install pyserial

# Installation de pigpio
RUN pip install pigpio

#Activation de ROS2 pour ne pas avoir a le faire a chaque lancement
RUN /bin/bash -c "source /opt/ros/humble/setup.bash"

# Changement du repertoire de travail
WORKDIR /root

#Creation du workspace ROS2
RUN git clone https://github.com/Creesix/Ugway.git
