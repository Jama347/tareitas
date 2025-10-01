import re
patron='algo$'
palabra = "omounalgoqueesunacosaperonoesun"
resultado = re.search(patron, palabra)
print(resultado.group(0) if resultado else "No se encontró el patrón")