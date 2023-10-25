"""
    @file       MPDS.py  
    @author     THIONGANE Ousmane  
    @brief      
    @version    1.0  
    @date       14-10-2023  
    @copyright   
    
"""
#Importation des bibliothèques 

import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *


import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QGraphicsView, QGraphicsScene
from PyQt5.QtGui import QPixmap
from PyQt5.QtCore import Qt

class GridWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        self.setGeometry(100, 100, 1300, 670)
        self.setWindowTitle("Méthode des points de sûreté (MPDS)")
        
        self.initUI()
    
    def initUI(self):
        scene = QGraphicsScene()
        
        # Dimensions de la grille
        grid_width = 1000  # Ajustez la largeur de la grille
        grid_height = 667
        cell_size = 20

        background_image = QGraphicsPixmapItem(QPixmap("img/table.jpg"))
        scene.addItem(background_image)
        
        # Création de la grille
        for x in range(0, grid_width, cell_size):
            for y in range(0, grid_height, cell_size):
                point = QGraphicsEllipseItem(x, y, 5, 5)
                point.setBrush(Qt.gray)
                point.setFlag(QGraphicsEllipseItem.ItemIsSelectable)
                scene.addItem(point)
        
        # Charger une image pour l'arrière-plan
        
        
        # Coordonnées du robot
        x_robot = 25  # Ajustez les coordonnées x du robot
        y_robot = 125  # Ajustez les coordonnées y du robot
        theta_robot = -90  # Ajustez l'angle du robot en degrés
        
        # Charger l'image du robot
        robot_image = QGraphicsPixmapItem(QPixmap("img/robot.png"))
        # Positionner l'image du robot et le faire tourner
        robot_image.setPos(x_robot, y_robot)
        robot_image.setRotation(theta_robot)
        scene.addItem(robot_image)
        
        # Créer une vue personnalisée
        view = QGraphicsView(scene, self)
        view.setAlignment(Qt.AlignLeft)
        self.setCentralWidget(view)

def main():
    app = QApplication(sys.argv)
    window = GridWindow()
    window.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()