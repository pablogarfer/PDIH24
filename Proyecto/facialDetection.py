import cv2

#Se carga el clasificador Haar (https://github.com/opencv/opencv/tree/master/data/haarcascades)
cascadeClassifier = cv2.CascadeClassifier('haarcascade_frontalface_alt.xml')

#Se inicia la webcam
webcam = cv2.VideoCapture(0) 

#Bucle infinito para capturar frame a frame
while(1):
    #Se captura un frame de la webcam para analizar
    valid, img = webcam.read()
    
    if valid:
        #Se convierte la imagen a escala de grises
        img_gris  = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        
        #Usando el clasificador se detectan las caras
        coord_caras = cascadeClassifier.detectMultiScale(
            img_gris,
            scaleFactor=1.1,
            minNeighbors=5,
            minSize=(30, 30),
            #flags=cv2.cv.CV_HAAR_SCALE_IMAGE
            )
        
        #Cada cara encontrada se va a marcar con un recuadro rojo
        for(x,y,w,h) in coord_caras: 
            cv2.rectangle(img,  (x, y), (x+w, y+h),(0,0,255),3)
        
        #En una ventana nueva se muestra el resultado
        cv2.imshow('Webcam', img)  
        
        #Se establece la tecla ESC como condición de parada del programa
        key = cv2.waitKey(5) & 0xFF
        if key == 27:
            cv2.destroyAllWindows()
            break
        
webcam.release()