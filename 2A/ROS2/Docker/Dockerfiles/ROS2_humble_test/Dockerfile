#L'image servant de base
FROM ros:humble

#Installation d'outils qui pourront etre utiles par la suite
RUN apt-get update && apt-get install -y git && apt-get install -y python3-pip
RUN apt-get install -y i2c-tools && apt-get install -y nano
RUN rm -rf /var/lib/apt/lists/*

#Activation de ROS2 pour ne pas avoir a le faire a chaque lancement
RUN /bin/bash -c "source /opt/ros/humble/setup.bash"

#Creation d'un workspace ROS2
RUN mkdir -p ~/ros2_ws/src
