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


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        
        self.setGeometry(100, 100, 1300, 670)  # Définition de la taille de la fenêtre
        self.setWindowTitle("Méthode des Points de Sûreté (MPDS)")
        
        self.initUI()
    
    def initUI(self):
        scene = QGraphicsScene()
        
        # Dimensions de la grille

        grid_width = 1000
        grid_height = 667

        cell_size = 20  # Taille d'une cellule

        #Image d'arrière-plan (de dimension 1000x660)
        background_image = QGraphicsPixmapItem(QPixmap("table.jpg"))
        scene.addItem(background_image)
        
        # Création de la grille
        for x in range(0, grid_width, cell_size):
            for y in range(0, grid_height, cell_size):
                # Crée un point cliquable à chaque intersection
                point = QGraphicsEllipseItem(x, y, 5, 5)  # 5x5 pixels
                point.setBrush(Qt.gray)  
                point.setFlag(QGraphicsEllipseItem.ItemIsSelectable)  # Rendre le point cliquable
                scene.addItem(point)
        
        x_robot = 50  
        y_robot = 70  
        theta_robot = 90  
        
        # Création d'un triangle (flèche) pour le robot
        triangle = QPolygonF()
        triangle.append(QPoint(x_robot - 20, y_robot))
        triangle.append(QPoint(x_robot + 40, y_robot))
        triangle.append(QPoint(x_robot + 10, y_robot - 70))
        triangle_item = scene.addPolygon(triangle, QPen(Qt.darkGreen), QBrush(Qt.green))
        
        # Rotation du triangle pour l'angle theta_robot
        triangle_item.setTransformOriginPoint(QPoint(x_robot, y_robot))
        triangle_item.setRotation(theta_robot)
        
        view = QGraphicsView(scene, self)
        view.setAlignment(Qt.AlignLeft)
        self.setCentralWidget(view)
        

def main():
    app = QApplication(sys.argv)
    window = Window()
    window.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
