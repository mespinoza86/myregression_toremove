#Prototipado de matrices en octave


##Matriz original 
disp ("La matriz original es:")
A = [3,3,3,3;3,3,3,3;3,3,3,3;3,3,3,3]

function salida = suma(x,y)
    salida = x+y
end

function Mtrans_ = gtranslate(M,x,y,z)
  #glTranslate produce una translacion de x y z . 
  #La matriz actual (argumento A) es multiplicado por la matriz de translacion Mt.
  #Mfinal = M * Mt 

  disp ("##################################")
  disp ("Translacion de la matriz original:")
  disp ("Calculo de la matriz de translacion Mt:")
  disp ("   -Donde: x=2, y=3, z=4")
  
  Mt = [1,0,0,x;0,1,0,y;0,0,1,z;0,0,0,1]
  disp ("Matriz trasladada resultante: ")
  disp ("   - Mtrans_ = M*Mt ")
  Mtrans_ = M.*Mt
  disp ("##################################")
  
 end
 
 function Mescalada_ = gscaled(M,x,y,z)
  #La matriz actual es multiplicada por la matriz de escalacion Me.
  #La matriz resultante seria:

  #Mfinal = M*Me

  disp ("##################################")
  disp ("Escalacion de la matriz original:")
  disp ("Calculo de la matriz de escalacion Me:")
  disp ("   -Donde: x=2, y=3, z=4")
  Me = [x,0,0,0;0,y,0,0;0,0,z,0;0,0,0,1]
  
  disp ("Matriz escalada resultante: ")
  disp ("  - Mescalada_ = M*Mt ")
  
  Mescalada_ = M.*Me
  
  disp ("##################################")
 end
 
 function Mrotate_ = grotate(M,x,y,z,angulo)
 #gRotate produce una rotacion de un angulo en grados alredor del vector x,y,z.
 #La matriz actual (argumento A) es multiplicada por la matriz de rotacion Mr. 
 #Mfinal = M * Mr
  
 #A continuacion se genera la matriz de rotacion, donde:
 # c = cos(angulo)
 # s = sin(angulo)
 
 disp ("##################################")
 disp ("Rotacion de la matriz original:")
 disp ("Calculo de los coeficientes necesarios para la matriz de rotacion:")
 disp ("   -Donde: x=2, y=3, z=4, angulo=30")
c = cos(angulo)
s = sin(angulo)

m1 = x*x*(1-c)+c
m2 = x*y*(1-c)-z*s
m3 = x*z*(1-c)+y*s
m4 = 0

m5 = x*y*(1-c)+z*s
m6 = y*y*(1-c)+c
m7 = y*z*(1-c)-x*s
m8 = 0

m9 =  x*z*(1-c)-y*s
m10 = y*z*(1-c)+x*s
m11 = z*z*(1-c)+c
m12 = 0

 disp ("La matriz de rotacion es la siguiente:")
    
Mr = [m1,m2,m3,m4;m5,m6,m7,m8;m9,m10,m11,m12;0,0,0,1]

#La matriz resultante se obtiene multiplicando M.*Mr

disp ("La matriz con la rotacion resultante es la siguiente:")
disp ("    -Mrotate = M*Mr")

Mrotate_ = M.*Mr

end
 
gtranslate(A, 2,3,4)
gscaled(A,2,3,4)
grotate(A,2,3,4,30)

