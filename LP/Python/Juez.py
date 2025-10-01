import re

def leerArchivo(entrada):
    """
    entrada : archivo de texto
    return : lista de listas [palabrasClave, estrofas]
    Lee el archivo de entrada y retorna las palabras clave y las estrofas
    """
    
    archivo=open(entrada, 'r', encoding='utf-8')
    contenido = archivo.read()
    lineas = contenido.split('\n') #separa el archivo por saltos de línea
    palabrasClave=[]
    for palabra in lineas[0].split(','):
        palabrasClave.append(palabra.strip().lower()) #crear lista de palabras clave
    estrofas = []
    i=1
    while i < len(lineas) and lineas[i].strip() == '':
        i += 1 
    while i < len(lineas):
        estrofaActual = []
        while i < len(lineas) and lineas[i].strip() != '':
            estrofaActual.append(lineas[i].strip())
            i += 1
        if len(estrofaActual) > 0:
            estrofas.append(estrofaActual)
        while i < len(lineas) and lineas[i].strip() == '':
            i += 1
    archivo.close()        
    return [palabrasClave, estrofas]      

def validarSimbolos(verso):
    """
    ***
    verso : str
    ***
    return : bool
    ***
    Valida que un verso contenga solo simbolos permitidos
    """  
    
    patronValido= r'^[A-Za-zÑñÁÉÍÓÚáéíóú0-9¿?¡!,.;:()\-"\' ]+$' #falto el '
    if re.match(patronValido, verso):
        return True
    else:
        return False
    
def extraerPalabraFinal(verso):
    """
    ***
    verso : str
    ***
    return : str
    ***
    Extrae la ultima palabra de un verso
    """
    versoLimpio = re.sub(r'[¿?¡!,.;:()\-" ]+$', '', verso.strip())  # Elimina signos de puntuación
    palabras = versoLimpio.split()
    if palabras:
        return palabras[-1]
    return ''

def obtenerSufijoAsonante(palabra):
    """
    palabra : str
    return : str
    """
    # Normalizar tildes
    palabraNormalizada = palabra.lower()
    palabraNormalizada = re.sub(r'[á]', 'a', palabraNormalizada)
    palabraNormalizada = re.sub(r'[é]', 'e', palabraNormalizada)
    palabraNormalizada = re.sub(r'[í]', 'i', palabraNormalizada)
    palabraNormalizada = re.sub(r'[ó]', 'o', palabraNormalizada)
    palabraNormalizada = re.sub(r'[ú]', 'u', palabraNormalizada)
    
    vocalesEncontradas = ""
    
    # Recorrer desde el final
    for i in range(len(palabraNormalizada) - 1, -1, -1):
        if palabraNormalizada[i] in 'aeiou':
            vocalesEncontradas = palabraNormalizada[i] + vocalesEncontradas
    
    return vocalesEncontradas

def clasificarRima(palabra1, palabra2):
    if palabra1 == palabra2:
        return ["Gemela", 1]
    
    # Asonantes 
    sufijo1 = obtenerSufijoAsonante(palabra1)
    sufijo2 = obtenerSufijoAsonante(palabra2)
    
    # Consonante 5+ letras
    if len(palabra1) >= 5 and len(palabra2) >= 5:
        if palabra1[-5:] == palabra2[-5:]:
            return ["Consonante", 8]
        
    # 3+ vocales asonantes
    if len(sufijo1) >= 3 and len(sufijo2) >= 3:
        if sufijo1[-3:] == sufijo2[-3:]:
            return ["Asonante", 8]
    
    # Consonante 4 letras
    if len(palabra1) >= 4 and len(palabra2) >= 4:
        if palabra1[-4:] == palabra2[-4:]:
            return ["Consonante", 5]
    
    # Consonante 3 letras
    if len(palabra1) >= 3 and len(palabra2) >= 3:
        if palabra1[-3:] == palabra2[-3:]:
            return ["Consonante", 5]
    
    # 2 vocales asonantes
    if len(sufijo1) >= 2 and len(sufijo2) >= 2:
        if sufijo1[-2:] == sufijo2[-2:]:
            return ["Asonante", 4]
    
    # 1 vocal asonante
    if len(sufijo1) >= 1 and len(sufijo2) >= 1:
        if sufijo1[-1:] == sufijo2[-1:]:
            return ["Asonante", 3]
    
    # Misma terminación (2+ letras)
    if len(palabra1) >= 2 and len(palabra2) >= 2:
        if palabra1[-2:] == palabra2[-2:]:
            return ["Misma Terminacion", 2]
    
    return ["sin Rima", 0]

#Intento de clasificar rimas usando expresiones regulares (fallido)
    '''
def clasificarRima(palabra1, palabra2):
    """
    palabra1 : str
    palabra2 : str
    return : str(tipo de rima) , int(puntaje)
    Clasifica la rima entre dos palabras
    """  
    
    if palabra1 == palabra2:
        return ["Gemela" , 1]
    
    patron5con = palabra1[-5:] + '$'        #Ordenadas de mayor a menor puntaje
    if re.search(patron5con, palabra2):
        return ["Consonante", 8]
    
    patron3aso = obtenerSufijoAsonante(palabra1) + '$'
    if re.search(patron3aso, palabra2):
        return ["Asonante", 8]
    
    patron4con = palabra1[-4:] + '$'
    if re.search(patron4con, palabra2):
        return ["Consonante", 5]
    
    patron3con = palabra1[-3:] + '$'
    if re.search(patron3con, palabra2):
        return ["Consonante", 5]
    
    patron2aso = obtenerSufijoAsonante(palabra1[-2:]) + '$'
    if re.search(patron2aso, palabra2):
        return ["Asonante", 4]
    
    patron1aso = obtenerSufijoAsonante(palabra1[-1:]) + '$'
    if re.search(patron1aso, palabra2):
        return ["Asonante", 3]
    

    if palabra1[-2:] == palabra2[-2:]:
        return ["Misma Terminacion", 2]
            
    return ["sin Rima", 0]
'''
def evaluarEstrofa(estrofa, palabrasClave):
    """
    estrofa : list de str
    palabrasClave : list de str
    return :  [int : puntaje, list de str : tiposRima, bool : tieneBonus, bool : esValida]
    Evalua una estrofa y retorna su puntaje, tipos de rima, si tiene bonus y si es valida
    """
    
    retorno = [0 , [] , False , False]
    if len(estrofa) != 4:
        return retorno
    palabrasFinales=[]
    for verso in estrofa:
        if not validarSimbolos(verso):
            return [0 , [] , False , False] 
        palabraFinal = extraerPalabraFinal(verso)
        palabrasFinales.append(palabraFinal)
    retorno[3] = True    
    i=0
    while i < len(estrofa):
        j=i+1
        while j < len(estrofa):
            rima=clasificarRima(palabrasFinales[i], palabrasFinales[j])
            retorno[0] += rima[1]
            if rima[0] != "sin Rima":
                if rima[0] not in retorno[1]:
                    retorno[1].append(rima[0])
            else:
                retorno[0] -= 2 #hace el descuento de sin rima por cada iteracion, generando errores
            j +=1
        i+=1
    for palabra in palabrasFinales:
        if palabra.lower() in palabrasClave:
            retorno[2] = True
            retorno[0] += 2        
    return retorno

def escribirArchivo(resultados):
    """
    resultados : lista de listas generadas por evaluarEstrofa
    return : None
    Genera el archivo de salida decision.txt
    """
    
    decision = open('decision.txt', 'w', encoding='utf-8')
    
    for resultado in resultados:
        linea1 = f"Estrofa {resultados.index(resultado) + 1}: "
        if resultado[3]:  # Si es valida
            puntajeFinal = round(resultado[0]/5 , 1)
            linea1 += str(puntajeFinal)+"/10"
            if resultado[2]:  # Si tiene bonus
                linea1 += " (Bonus)"
            decision.write(linea1 + '\n')    
            linea2= "Rimas: "
            if resultado[1]:
                linea2 += ', '.join(resultado[1])
            else:
                linea2 += "Sin rima"
            decision.write(linea2 + '\n')    
        else:
            linea1 += "Invalida"
            decision.write(linea1 + '\n')     
        
    decision.close()
    
"""
ejecucion del progama
"""
lectura= leerArchivo('estrofas.txt')
palabrasClave = lectura[0]
estrofas = lectura[1]
resultados = []
for estrofa in estrofas:
    resultado = evaluarEstrofa(estrofa , palabrasClave)
    resultados.append(resultado)
escribirArchivo(resultados)
        